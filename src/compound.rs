use std::marker::PhantomData;

use bevy_ecs::world::World;

use crate::{
    ecs::{CommandSettings, CompoundCommandsPeriodic},
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
