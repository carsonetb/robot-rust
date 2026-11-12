use std::marker::PhantomData;

use bevy_ecs::world::World;

use crate::{
    ecs::{CommandSettings, CommandsPeriodic, CompoundCommandsPeriodic},
    prelude::*,
};

/// Used as an input to a system, gets a reference to any command registered
/// with [`State::register_command`]. Commands also have some extra functions.
pub type Command<'a, T> = Resource<'a, CommandInternal<T>>;

/// Used as an input to a system, gets a mutable reference to any command
/// registered with [`State::register_command`]. Commands also have some extra
/// functions.
pub type CommandMut<'a, T> = ResourceMut<'a, CommandInternal<T>>;

// pub(crate) struct CommandRegistry {
//     getters: HashMap<TypeId, fn(&mut World) -> Option<&mut dyn AnyCommand>>,
// }
//
// impl CommandRegistry {
//     pub(crate) fn new() -> Self {
//         Self {
//             getters: HashMap::new(),
//         }
//     }
//
//     pub(crate) fn register<C: 'static, O: AnyCommand + 'static>(&mut self) {
//         self.getters
//             .insert(TypeId::of::<C>(), Self::getter_function::<O>());
//     }
//
//     pub(crate) fn get<'a>(
//         &self,
//         id: TypeId,
//     ) -> Option<fn(&mut World) -> Option<&mut dyn AnyCommand>> {
//         self.getters.get(&id).cloned()
//     }
//
//     pub(crate) fn getter_function<C: AnyCommand + 'static>()
//     -> fn(&mut World) -> Option<&mut dyn AnyCommand> {
//         |world| {
//             world
//                 .get_non_send_mut::<C>()
//                 .map(|res| res.into_inner() as &mut dyn AnyCommand)
//         }
//     }
// }

pub(crate) trait AnyCommand {
    fn enable(&mut self);
    fn disable(&mut self);
    fn enabled(&self) -> bool;
    fn disabled(&self) -> bool {
        !self.enabled()
    }
    #[allow(unused)]
    fn just_ended(&self) -> bool;
    #[allow(unused)]
    fn just_started(&self) -> bool;
}

/// Internal data for a command wrapper. [`Command`] and [`CommandMut`] are
/// specifically used for inputs to systems, whereas this is where the actual
/// data is stored.
///
/// These values are updated in a seperate schedule, so they will always be
/// synchronized before robot code.
#[derive(DerefMut, Deref, Clone)]
pub struct CommandInternal<T> {
    #[deref]
    #[deref_mut]
    pub(crate) command: T,
    pub(crate) enabled: bool,
    pub(crate) just_ended: bool,
    pub(crate) just_started: bool,
}

impl<T> CommandInternal<T> {
    pub(crate) fn new(command: T) -> Self {
        Self {
            command,
            enabled: false,
            just_ended: false,
            just_started: false,
        }
    }

    pub fn enable(&mut self) {
        if !self.enabled {
            self.just_started = true;
        }
        self.enabled = true;
    }

    pub fn disable(&mut self) {
        if self.enabled {
            self.just_ended = true;
        }
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

impl<T> AnyCommand for CommandInternal<T> {
    fn enable(&mut self) {
        self.enable();
    }

    fn disable(&mut self) {
        self.disable();
    }

    fn enabled(&self) -> bool {
        self.enabled()
    }

    fn just_ended(&self) -> bool {
        self.just_ended()
    }

    fn just_started(&self) -> bool {
        self.just_started()
    }
}

#[derive(Debug, Clone, Copy)]
pub enum CompoundBehavior {
    Just,
    Sequence,
    Parallel,
    Race,
}

pub struct CompoundCommand<T> {
    sequence_index: usize,
    group: Vec<fn(&mut World) -> Option<&mut dyn AnyCommand>>,
    behavior: CompoundBehavior,
    _t: PhantomData<T>,
}

impl<T> Clone for CompoundCommand<T> {
    fn clone(&self) -> Self {
        Self {
            sequence_index: 0,
            group: self.group.clone(),
            behavior: self.behavior,
            _t: PhantomData,
        }
    }
}

impl<T: 'static> CompoundCommand<T> {
    pub fn new(behavior: CompoundBehavior) -> Self {
        Self {
            sequence_index: 0,
            group: Vec::new(),
            behavior,
            _t: PhantomData,
        }
    }

    pub fn add<C: 'static>(mut self) -> Self {
        self.group
            .push(Self::getter_function::<CommandInternal<C>>());
        self
    }

    pub fn add_to(self, state: &'_ mut State) -> CommandSettings<'_, Self> {
        state
            .register_command(self)
            .with_handler(CompoundCommandsPeriodic, Self::handler)
    }

    fn getter_function<C: AnyCommand + 'static>() -> fn(&mut World) -> Option<&mut dyn AnyCommand> {
        |world| {
            // println!("get {}", std::any::type_name::<C>());
            world
                .get_non_send_mut::<C>()
                .map(|res| res.into_inner() as &mut dyn AnyCommand)
        }
    }

    fn handler(world: &mut World) {
        let this = world.non_send_mut::<CommandInternal<Self>>().clone();

        if this.just_ended() {
            for getter in &this.group {
                getter(world).unwrap().disable();
            }
        }

        if this.disabled() {
            return;
        }

        if this.just_started() {
            for getter in &this.group {
                getter(world).unwrap().disable();
            }

            match this.behavior {
                CompoundBehavior::Just | CompoundBehavior::Sequence => {
                    world.non_send_mut::<CommandInternal<Self>>().sequence_index = 0;
                    if !this.group.is_empty() {
                        // println!("enable this:");
                        this.group[0](world).unwrap().enable();
                        // dbg!(this.group[0](world).unwrap().enabled());
                    }
                }
                CompoundBehavior::Parallel | CompoundBehavior::Race => {
                    for getter in &this.group {
                        getter(world).unwrap().enable();
                    }
                }
            }

            return;
        }

        let mut disable = false;
        match this.behavior {
            CompoundBehavior::Just => {
                let command = this.group[0](world).unwrap();
                if command.disabled() {
                    disable = true;
                }
            }
            CompoundBehavior::Sequence => {
                if this.sequence_index < this.group.len() {
                    let command = this.group[this.sequence_index](world).unwrap();
                    if command.disabled() {
                        world.non_send_mut::<CommandInternal<Self>>().sequence_index += 1;
                        if this.sequence_index + 1 >= this.group.len() {
                            disable = true;
                        } else {
                            this.group[this.sequence_index + 1](world).unwrap().enable();
                        }
                    }
                } else {
                    disable = true;
                }
            }
            CompoundBehavior::Parallel => {
                let mut all_disabled = true;
                for getter in &this.group {
                    if getter(world).unwrap().enabled() {
                        all_disabled = false;
                    }
                }
                disable = all_disabled;
            }
            CompoundBehavior::Race => {
                let mut any_disabled = false;
                for getter in &this.group {
                    if getter(world).unwrap().disabled() {
                        any_disabled = true;
                    }
                }
                disable = any_disabled;
            }
        }

        if disable {
            world.non_send_mut::<CommandInternal<Self>>().disable();
            for getter in &this.group {
                getter(world).unwrap().disable();
            }
        }
    }
}

#[macro_export]
macro_rules! command {
    ($state:expr, $vis:vis $Name:ident: $Type:ident($($Member:ty),*) $(.$trigger:ident($condition:expr))?) => {
        ::paste::paste! {
            struct [<$Name ID>];
            $vis type $Name = CompoundCommand<[<$Name ID>]>;
            $Name::new(CompoundBehavior::$Type)
                $(.add::<$Member>())*
                .add_to(&mut $state)
                $(.$trigger($condition))?;
        }
    };
}

//

//
// pub struct CommandGroup {
//     enabled: bool,
//     just_ended: bool,
//     just_started: bool,
//     sequence_index: usize,
//     behavior: CommandGroupBehavior,
//     commands: Vec<(Box<dyn AnyCommand>, Option<BoxedSystem<(), bool>>)>,
// }
//
// impl CommandGroup {
//     pub(crate) fn new(behavior: CommandGroupBehavior) -> Self {
//         Self {
//             enabled: false,
//             just_ended: false,
//             just_started: false,
//             sequence_index: 0,
//             behavior,
//             commands: Vec::new(),
//         }
//     }
//
//     pub fn add_command<C: AnyCommand + 'static>(&mut self, command: C) ->
// Self {         self.commands.push((Box::new(command), None));
//     }
//
//     pub fn add_commands(mut self, mut commands: Vec<Box<dyn AnyCommand>>) ->
// Self {         self.commands
//             .append(&mut commands.into_iter().map(|c| (c, None)).collect());
//         self
//     }
// }
//
// impl AnyCommand for CommandGroup {
//     fn enable(&mut self) {
//         self.enabled = true;
//         match self.behavior {
//             CommandGroupBehavior::Just => self.commands[0].enable(),
//             CommandGroupBehavior::Sequence => {
//                 self.sequence_index = 0;
//                 self.commands[0].enable();
//             }
//             CommandGroupBehavior::Parallel => {
//                 for command in &mut self.commands {
//                     command.enable();
//                 }
//             }
//             CommandGroupBehavior::Race => {
//                 for command in &mut self.commands {
//                     command.enable();
//                 }
//             }
//         }
//     }
//
//     fn disable(&mut self) {
//         self.enabled = false;
//         for command in &mut self.commands {
//             command.enable();
//         }
//     }
//
//     fn enabled(&self) -> bool {
//         self.enabled
//     }
//
//     #[allow(unused)]
//     fn just_ended(&self) -> bool {
//         self.just_ended
//     }
//
//     #[allow(unused)]
//     fn just_started(&self) -> bool {
//         self.just_started
//     }
// }
//
// enum TriggerType {
//     While,
//     On,
//     With,
//     Until,
// }
//
// pub struct CommandGroupConfigurator<'c> {
//     group: &'c mut CommandGroup,
//     index: usize,
// }
//
// impl<'c> CommandGroupConfigurator<'c> {
//     /// Add systems that will automatically enable and disable the command
//     /// based on the value of the trigger. Do not call this function twice
// for     /// the same command.
//     ///
//     /// If you wish the command to be ran when two triggers are true, or when
//     /// one of two triggers are true, you can use `trigger.and(another)` or
//     /// `trigger.or(another)`.
//     pub fn while_trigger<M, T: SystemCondition<M, ()> + Clone>(&mut self,
// trigger: T) -> &mut Self {         let mut condition =
// IntoSystem::into_system(trigger);         condition.initialize(world);
//         self
//     }
//
//     /// Add systems that will automatically enable a command when a trigger's
//     /// value gets set to true. Do not call this function twice for the same
//     /// command.
//     ///
//     /// If you wish the command to be ran when two triggers are true, or when
//     /// one of two triggers are true, you can use `trigger.and(another)` or
//     /// `trigger.or(another)`.
//     pub fn on_trigger<M, T: SystemCondition<M, ()> + Clone>(&mut self,
// trigger: T) -> &mut Self {         self.state.add_systems(
//             CommandsPeriodic,
//
// enable_command::<CommandGroup<G>>.run_if(condition_changed_to(true,
// trigger)),         );
//         self
//     }
//
//     /// Add systems that will automatically enable a command when a trigger's
//     /// value gets set to true and disable the command when the trigger's
// value     /// gets set to false. Do not call this function twice for the same
//     /// command.
//     ///
//     /// If you wish the command to be ran when two triggers are true, or when
//     /// one of two triggers are true, you can use `trigger.and(another)` or
//     /// `trigger.or(another)`.
//     pub fn with_trigger<M, T: SystemCondition<M, ()> + Clone>(&mut self,
// trigger: T) -> &mut Self {         self.state.add_systems(
//             CommandsPeriodic,
//
// enable_command::<CommandGroup<G>>.run_if(condition_changed(trigger)),
//         );
//         self
//     }
//
//     /// Add systems that will automatically disable a command when a
// trigger's     /// value get sets to true. Do not call this function twice for
// the same     /// command.
//     ///
//     /// If you wish the command to be stopped when two triggers are true, or
//     /// when one of two triggers are true, you can use
//     /// `trigger.and(another)` or `trigger.or(another)`.
//     pub fn until_trigger<M, T: SystemCondition<M, ()> + Clone>(&mut self,
// trigger: T) -> &mut Self {         self.state.add_systems(
//             CommandsPeriodic,
//             disable_command::<CommandGroup<G>>.run_if(trigger),
//         );
//         self
//     }
// }

// pub struct CommandGroup<G: IsCommandGroup> {
//     sequence_index: usize,
//     commands: Vec<TypeId>,
//     behavior: CommandGroupBehavior,
//     _g: PhantomData<G>, // Used only for unique resources.
// }
//
// impl<G: IsCommandGroup> Clone for CommandGroup<G> {
//     fn clone(&self) -> Self {
//         Self {
//             sequence_index: self.sequence_index,
//             commands: self.commands.clone(),
//             behavior: self.behavior,
//             _g: PhantomData,
//         }
//     }
// }
//
// impl<G: IsCommandGroup> CommandGroup<G> {
//     pub fn validate(&self, world: &World) {
//         for command in &self.commands {
//             world
//                 .non_send::<CommandRegistry>()
//                 .get(*command)
//                 .expect("Command group validation failed.");
//         }
//     }
// }
//
// fn get_command(world: &mut World, id: TypeId) -> &mut dyn AnyCommand {
//     world
//         .non_send_mut::<CommandRegistry>()
//         .get(id)
//         .expect("Internal error: Command escaped validation.")(world)
//     .expect("Internal error: Command was somehow removed.")
// }
//
// pub(crate) fn command_group_system<G: IsCommandGroup + 'static>(world: &mut
// World) {     // Code kinda spaghetti to make the lifetimes happy.
//     let mut command =
// world.non_send_mut::<CommandInternal<CommandGroup<G::Target>>>();
//     let disabled = command.disabled();
//     if disabled {
//         command.sequence_index = 0;
//     }
//     let command = CommandGroup::clone(&*command);
//
//     if disabled {
//         for command in command.commands {
//             get_command(world, command).disable();
//         }
//         return;
//     }
//
//     match command.behavior {
//         CommandGroupBehavior::Sequence => {
//             let running = get_command(world,
// command.commands[command.sequence_index]);             if running.disabled()
// {                 if command.sequence_index < command.commands.len() - 1 {
//                     world
//
// .non_send_mut::<CommandInternal<CommandGroup<G::Target>>>()
// .sequence_index += 1;                     get_command(world,
// command.commands[command.sequence_index + 1]).enable();                 }
// else {                     world
//
// .non_send_mut::<CommandInternal<CommandGroup<G::Target>>>()
// .disable();                 }
//             }
//         }
//         CommandGroupBehavior::Parallel => {
//             let mut all_disabled = true;
//             for command in command.commands {
//                 let command = get_command(world, command);
//                 if command.enabled() {
//                     all_disabled = false;
//                 }
//             }
//             if all_disabled {
//                 world
//
// .non_send_mut::<CommandInternal<CommandGroup<G::Target>>>()
// .disable();             }
//         }
//         CommandGroupBehavior::Race => {
//             let mut any_disabled = false;
//             for command in &command.commands {
//                 let command = get_command(world, *command);
//                 if command.disabled() {
//                     any_disabled = true;
//                     break;
//                 }
//             }
//             if any_disabled {
//                 world
//
// .non_send_mut::<CommandInternal<CommandGroup<G::Target>>>()
// .disable();                 for command in command.commands {
//                     get_command(world, command).disable();
//                 }
//             }
//         }
//         CommandGroupBehavior::Just => {
//             let command = get_command(world, command.commands[0]);
//             if command.disabled() {
//                 world
//
// .non_send_mut::<CommandInternal<CommandGroup<G::Target>>>()
// .disable();             }
//         }
//     }
// }
//
// pub trait IsCommandGroup: Sized {
//     type Target: IsCommandGroup;
//
//     fn create(behavior: CommandGroupBehavior) -> CommandGroup<Self::Target>;
// }
//
// #[macro_export]
// macro_rules! command_groups {
//     {
//         $state:ident;
//         $( $Name:ident: $Type:ident($($Of:ty),+)
// $(.$trigger_type:ident($trigger:expr))?; )+     } => {
//         $(
//             command_group!($state, $Name: $Type($($Of),+)
// $(.$trigger_type($trigger))?);         )*
//     };
// }
//
// #[macro_export]
// macro_rules! command_group {
//     ($state:expr, $Name:ident: $Type:ident($Of0:ty, $($Of:ty),+)
// $(.$trigger_type:ident($trigger:expr))? ) => {         struct $Name;
//
//         impl IsCommandGroup for $Name {
//             type Target = ($Of0, $($Of),+);
//
//             fn create(behavior: CommandGroupBehavior) ->
// CommandGroup<Self::Target> {                 Self::Target::create(behavior)
//             }
//         }
//
//         $state.
// register_command_group::<$Name>(CommandGroupBehavior::$Type)$(.
// $trigger_type($trigger))?;     };
//
//     ($state:expr, $Name:ident: $Type:ident($Of0:ty)
// $(.$trigger_type:ident($trigger:expr))? ) => {         struct $Name;
//
//         impl IsCommandGroup for $Name {
//             type Target = ($Of0,);
//
//             fn create(behavior: CommandGroupBehavior) ->
// CommandGroup<Self::Target> {                 Self::Target::create(behavior)
//             }
//         }
//
//         $state.
// register_command_group::<$Name>(CommandGroupBehavior::$Type)$(.
// $trigger_type($trigger))?;     };
// }
//
// macro_rules! tuple_command_group {
//     ($($T:ident),*) => {
//         impl<$($T: 'static,)*> IsCommandGroup for ($($T,)*)
//         {
//             type Target = Self;
//
//             fn create(behavior: CommandGroupBehavior) ->
// CommandGroup<Self::Target> {                 CommandGroup {
//                     sequence_index: 0,
//                     commands: vec![ $( TypeId::of::<$T>() ),* ],
//                     behavior,
//                     _g: PhantomData,
//                 }
//             }
//         }
//     };
// }
//
// tuple_command_group!();
// tuple_command_group!(A);
// tuple_command_group!(A, B);
// tuple_command_group!(A, B, C);
// tuple_command_group!(A, B, C, D);
// tuple_command_group!(A, B, C, D, E);
// tuple_command_group!(A, B, C, D, E, F);
// tuple_command_group!(A, B, C, D, E, F, G);
// tuple_command_group!(A, B, C, D, E, F, G, H);
