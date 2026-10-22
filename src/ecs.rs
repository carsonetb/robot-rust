use std::marker::PhantomData;

use bevy_ecs::prelude::*;
use bevy_ecs::schedule::{ScheduleLabel, SingleThreadedExecutor};
use bevy_ecs::system::{ScheduleSystem, SystemParam};

use crate::prelude::*;
use crate::{ds, hal};

/// The current mode of the robot program.
#[derive(Resource, Debug, Clone, Copy, PartialEq, Eq)]
pub enum Mode {
    None,
    Disabled,
    Autonomous,
    Teleop,
    Test,
}

/// Ran at the start of the robot program.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct Init;

/// Ran when the robot enters the disabled mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct DisabledInit;

/// Ran when the robot enters the teleop mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TeleopInit;

/// Ran when the robot enters the autonomous mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct AutonomousInit;

/// Ran when the robot enters the test mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TestInit;

/// Ran when the robot exits the disabled mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct DisabledExit;

/// Ran when the robot exits the teleop mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TeleopExit;

/// Ran when the robot exits the autonomous mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct AutonomousExit;

/// Ran when the robot exits the test mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TestExit;

/// Ran every ~20ms.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct Periodic;

/// Ran every ~20ms when the robot is in the disabled mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct DisabledPeriodic;

/// Ran every ~20ms when the robot is in the autonomous mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct AutonomousPeriodic;

/// Ran every ~20ms when the robot is in the teleop mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TeleopPeriodic;

/// Ran every ~20ms when the robot is in the test mode.
#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TestPeriodic;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
struct CommandsPeriodic;

/// Used as an input to a system, gets a reference to any resource registered
/// with [`State::insert_resource`].
pub type Resource<'a, T> = NonSend<'a, T>;

/// Used as an input to a system, gets a mutable reference to any resource registered
/// with [`State::insert_resource`].
pub type ResourceMut<'a, T> = NonSendMut<'a, T>;

/// Used as an input to a system, gets a reference to any command registered
/// with [`State::register_command`]. Commands also have some extra functions.
pub type Command<'a, T> = Resource<'a, CommandInternal<T>>;

/// Used as an input to a system, gets a mutable reference to any command registered
/// with [`State::register_command`]. Commands also have some extra functions.
pub type CommandMut<'a, T> = ResourceMut<'a, CommandInternal<T>>;

/// Internal data for a command wrapper. [`Command`] and [`CommandMut`] are
/// specifically used for inputs to systems, whereas this is where the actual
/// data is stored.
///
/// These values are updated in a seperate schedule, so they will always be
/// synchronized before robot code.
#[derive(DerefMut, Deref)]
pub struct CommandInternal<T> {
    #[deref]
    #[deref_mut]
    command: T,
    enabled: bool,
    just_ended: bool,
    just_started: bool,
}

impl<T> CommandInternal<T> {
    fn new(command: T) -> Self {
        Self {
            command,
            enabled: false,
            just_ended: false,
            just_started: false,
        }
    }

    pub fn enable(&mut self) {
        self.enabled = true;
    }

    pub fn disable(&mut self) {
        self.enabled = false;
    }

    /// If the command is currently enabled.
    pub fn enabled(&self) -> bool {
        self.enabled
    }

    /// If the command was just disabled.
    pub fn just_ended(&self) -> bool {
        self.just_ended
    }

    /// If the command was just enabled.
    pub fn just_started(&self) -> bool {
        self.just_started
    }
}

fn enable_command<C: 'static>(world: &mut World) {
    world.non_send_mut::<CommandInternal<C>>().enabled = true;
}

fn disable_command<C: 'static>(world: &mut World) {
    world.non_send_mut::<CommandInternal<C>>().enabled = true;
}

/// The owned state, used to setup a robot program.
pub struct State {
    world: World,
}

impl State {
    /// Create a new state. Can fail if the HAL fails to initialize.
    ///
    /// This method initializes the [`Logger`] resource, configuring it to use
    /// networktables. If you want to change this functionality, insert it again.
    pub fn new() -> Option<Self> {
        crate::recovery::install_signal_handler();

        if !hal::init() {
            println!("HAL failed to initialize.");
            return None;
        }
        hal::start();

        let _ = *crate::math::START_TIME;

        let mut world = World::new();

        let mut schedules = world.get_resource_or_init::<Schedules>();
        schedules.insert(Schedule::new(Init));
        schedules.insert(Schedule::new(DisabledInit));
        schedules.insert(Schedule::new(TeleopInit));
        schedules.insert(Schedule::new(AutonomousInit));
        schedules.insert(Schedule::new(TestInit));
        schedules.insert(Schedule::new(DisabledExit));
        schedules.insert(Schedule::new(TeleopExit));
        schedules.insert(Schedule::new(AutonomousExit));
        schedules.insert(Schedule::new(TestExit));
        schedules.insert(Schedule::new(Periodic));
        schedules.insert(Schedule::new(DisabledPeriodic));
        schedules.insert(Schedule::new(TeleopPeriodic));
        schedules.insert(Schedule::new(AutonomousPeriodic));
        schedules.insert(Schedule::new(TestPeriodic));
        schedules.insert(Schedule::new(CommandsPeriodic));

        world.insert_non_send(Logger::new("log.wpilog", true));

        Some(Self { world })
    }

    /// Run the main loop, starting by running the Init schedule. The loop
    /// follows a specific order:
    ///
    /// - Refresh DS data.
    /// - Update commands data.
    /// - Run *Exit schedules.
    /// - Run *Init schedules.
    /// - Run *Periodic schedules.
    /// - Run Periodic schedule.
    pub fn run(&mut self) {
        self.world.insert_resource(Mode::None);

        self.world.run_schedule(Init);

        loop {
            if !ds::refresh() {
                ds::alert(ds::AlertType::Error, "DS failed to refresh data.");
                continue;
            }

            let word = hal::ControlWord::new().unwrap();

            let mode = if word.disabled() {
                Mode::Disabled
            } else if word.autonomous() {
                Mode::Autonomous
            } else if word.teleop() {
                Mode::Teleop
            } else if word.test() {
                Mode::Test
            } else {
                Mode::None
            };

            self.world.run_schedule(CommandsPeriodic);

            let last_mode = *self.world.resource::<Mode>();
            if mode != last_mode {
                match last_mode {
                    Mode::Disabled => self.world.run_schedule(DisabledExit),
                    Mode::Autonomous => self.world.run_schedule(AutonomousExit),
                    Mode::Teleop => self.world.run_schedule(TeleopExit),
                    Mode::Test => self.world.run_schedule(TestExit),
                    _ => {}
                }

                match mode {
                    Mode::Disabled => self.world.run_schedule(DisabledInit),
                    Mode::Autonomous => self.world.run_schedule(AutonomousInit),
                    Mode::Teleop => self.world.run_schedule(TeleopInit),
                    Mode::Test => self.world.run_schedule(TestInit),
                    _ => {}
                }

                *self.world.resource_mut::<Mode>() = mode;
            }

            match mode {
                Mode::Disabled => {
                    hal::observe_disabled();
                    self.world.run_schedule(DisabledPeriodic)
                }
                Mode::Autonomous => {
                    hal::observe_autonomous();
                    self.world.run_schedule(AutonomousPeriodic)
                }
                Mode::Teleop => {
                    hal::observe_teleop();
                    self.world.run_schedule(TeleopPeriodic)
                }
                Mode::Test => {
                    hal::observe_test();
                    self.world.run_schedule(TestPeriodic)
                }
                _ => {}
            }

            self.world.run_schedule(Periodic);
        }
    }

    /// Add a system(s) that will run on a schedule. See the book chapter called
    /// `3. Systems, Resources, and Schedules` if you don't know what this is.
    pub fn add_systems<L: ScheduleLabel + Clone, M, S: IntoScheduleConfigs<ScheduleSystem, M>>(
        &mut self,
        label: L,
        systems: S,
    ) {
        StateRes::new(&mut self.world).add_systems(label, systems);
    }

    /// Insert a resource that can be used by systems using `Resource<R>` or
    /// `ResourceMut<R>`. See the book chapter called `3. Systems, Resources,
    /// and Schedules` if you don't know what this is.
    pub fn insert_resource<R: 'static>(&mut self, resource: R) {
        StateRes::new(&mut self.world).insert_resource(resource);
    }

    /// Register a command. Registering a command doesn't run it, it just spawns
    /// it in in a disabled state. If you would like to enable the command
    /// immediately, call `.enabled()` on the output of this function.
    ///
    /// Under the hood, a command is just a resource. But
    /// this also registers a special system that will help update all the
    /// command's values.
    pub fn register_command<C: 'static>(&'_ mut self, command: C) -> CommandSettings<'_, C> {
        self.add_systems(CommandsPeriodic, command_system::<C>);
        self.insert_resource(CommandInternal::new(command));
        CommandSettings::<C>::new(StateRes {
            world: &mut self.world,
        })
    }
}

/// The same as [`State`], but can be used as a parameter to a system. Because
/// of this, a [`StateRes`] can't be created nor does it have a `run` function.
///
/// To keep the commands implementation simple, and to discourage the user from
/// writing bad code, you can't register a new command using this. Remember that
/// registering a command in Rust is different than in C++ or Java. When a
/// command is registered, it is *disabled* by default, and you can enable it
/// later.
#[derive(SystemParam)]
pub struct StateRes<'w> {
    world: &'w mut World,
}

impl<'w> StateRes<'w> {
    fn new(world: &'w mut World) -> Self {
        Self { world }
    }

    /// Add a system(s) that will run on a schedule. See the book chapter called
    /// `3. Systems, Resources, and Schedules` if you don't know what this is.
    pub fn add_systems<L: ScheduleLabel + Clone, M, S: IntoScheduleConfigs<ScheduleSystem, M>>(
        &mut self,
        label: L,
        systems: S,
    ) {
        let mut schedules = self.world.resource_mut::<Schedules>();

        if let Some(schedule) = schedules.get_mut(label.clone()) {
            schedule.add_systems(systems);
        } else {
            let mut schedule = Schedule::new(label.clone());
            schedule.set_executor(SingleThreadedExecutor::new());
            schedule.add_systems(systems);

            schedules.insert(schedule);
        }
    }

    /// Insert a resource that can be used by systems using `Resource<R>` or
    /// `ResourceMut<R>`. See the book chapter called `3. Systems, Resources,
    /// and Schedules` if you don't know what this is.
    pub fn insert_resource<R: 'static>(&mut self, resource: R) {
        self.world.insert_non_send(resource);
    }
}

/// Used to apply extra settings to a command.
pub struct CommandSettings<'w, C: 'static> {
    _phantom: PhantomData<C>,
    state: StateRes<'w>,
}

impl<'w, C: 'static> CommandSettings<'w, C> {
    fn new(state: StateRes<'w>) -> Self {
        Self {
            _phantom: PhantomData,
            state,
        }
    }

    /// Enable the command immediately.
    pub fn enabled(&mut self) -> &mut Self {
        enable_command::<C>(self.state.world);
        self
    }

    /// Add a system specifically designed to respond to when this command is
    /// enabled.
    pub fn with_handler<L: ScheduleLabel + Clone, M, S: IntoScheduleConfigs<ScheduleSystem, M>>(
        &mut self,
        label: L,
        systems: S,
    ) -> &mut Self {
        self.state.add_systems(label, systems);
        self
    }

    /// Add systems that will automatically enable and disable the command
    /// based on the value of the trigger. Do not call this function twice for
    /// the same command.
    ///
    /// If you wish the command to be ran when two triggers are true, or when
    /// one of two triggers are true, you can use `trigger.and(another)` or
    /// `trigger.or(another)`.
    pub fn while_trigger<M, T: SystemCondition<M, ()> + Clone>(&mut self, trigger: T) -> &mut Self {
        self.state.add_systems(
            CommandsPeriodic,
            enable_command::<C>.run_if(trigger.clone()),
        );
        self.state
            .add_systems(CommandsPeriodic, disable_command::<C>.run_if(not(trigger)));
        self
    }

    /// Add systems that will automatically enable a command when a trigger's
    /// value gets set to true. Do not call this function twice for the same
    /// command.
    ///
    /// If you wish the command to be ran when two triggers are true, or when
    /// one of two triggers are true, you can use `trigger.and(another)` or
    /// `trigger.or(another)`.
    pub fn on_trigger<M, T: SystemCondition<M, ()> + Clone>(&mut self, trigger: T) -> &mut Self {
        self.state.add_systems(
            CommandsPeriodic,
            enable_command::<C>.run_if(condition_changed_to(true, trigger)),
        );
        self
    }

    /// Add systems that will automatically enable a command when a trigger's
    /// value gets set to true and disable the command when the trigger's value
    /// gets set to false. Do not call this function twice for the same
    /// command.
    ///
    /// If you wish the command to be ran when two triggers are true, or when
    /// one of two triggers are true, you can use `trigger.and(another)` or
    /// `trigger.or(another)`.
    pub fn with_trigger<M, T: SystemCondition<M, ()> + Clone>(&mut self, trigger: T) -> &mut Self {
        self.state.add_systems(
            CommandsPeriodic,
            enable_command::<C>.run_if(condition_changed(trigger)),
        );
        self
    }
}

#[derive(Default)]
struct CommandSystemData {
    was_enabled: bool,
}

fn command_system<C: 'static>(mut command: CommandMut<C>, mut data: Local<CommandSystemData>) {
    if command.just_started {
        command.just_started = false;
    }
    if command.just_ended {
        command.just_ended = false;
    }

    if command.enabled && !data.was_enabled {
        command.just_started = true;
    }
    if !command.enabled && data.was_enabled {
        command.just_ended = true;
    }

    data.was_enabled = command.enabled;
}
