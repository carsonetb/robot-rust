use bevy_ecs::prelude::*;
use bevy_ecs::schedule::{ScheduleLabel, SingleThreadedExecutor};
use bevy_ecs::system::ScheduleSystem;

use crate::prelude::*;
use crate::{ds, hal};

#[derive(Resource, Debug, Clone, Copy, PartialEq, Eq)]
pub enum Mode {
    None,
    Disabled,
    Autonomous,
    Teleop,
    Test,
}

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct Init;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct DisabledInit;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TeleopInit;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct AutonomousInit;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TestInit;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct DisabledExit;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TeleopExit;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct AutonomousExit;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TestExit;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct Periodic;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct DisabledPeriodic;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct AutonomousPeriodic;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TeleopPeriodic;

#[derive(ScheduleLabel, Debug, Clone, PartialEq, Eq, Hash)]
pub struct TestPeriodic;

pub struct State {
    world: World,
}

impl State {
    pub fn new() -> Option<Self> {
        if !hal::init() {
            println!("HAL failed to initialize.");
            return None;
        }
        hal::start();

        let mut world = World::new();

        world.insert_non_send(Logger::new("log.wpilog"));
        world.insert_resource(Schedules::new());

        Some(Self { world })
    }

    pub fn run(&mut self) {
        self.world.insert_resource(Mode::None);

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

    pub fn add_systems<L: ScheduleLabel + Clone, M, S: IntoScheduleConfigs<ScheduleSystem, M>>(
        &mut self,
        label: L,
        systems: S,
    ) -> &mut Self {
        let mut schedules = self.world.resource_mut::<Schedules>();

        if let Some(schedule) = schedules.get_mut(label.clone()) {
            schedule.add_systems(systems);
        } else {
            let mut schedule = Schedule::new(label.clone());
            schedule.set_executor(SingleThreadedExecutor::new());
            schedule.add_systems(systems);

            schedules.insert(schedule);
        }

        self
    }

    pub fn insert_resource<R: 'static>(&mut self, resource: R) -> &mut Self {
        self.world.insert_non_send(resource);
        self
    }
}

pub type Resource<'a, T> = NonSend<'a, T>;
pub type ResourceMut<'a, T> = NonSendMut<'a, T>;
pub type Command<'a, T> = Resource<'a, CommandInternal<T>>;

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
    pub fn enabled(&self) -> bool {
        self.enabled
    }

    pub fn just_ended(&self) -> bool {
        self.just_ended
    }

    pub fn just_started(&self) -> bool {
        self.just_started
    }
}
