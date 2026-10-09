use std::any::{Any, TypeId};
use std::collections::HashMap;

use crate::commands::{Command, Scheduler};
use crate::{Mode, Robot, System};

#[derive(Default)]
pub struct Database {
    db: HashMap<TypeId, Box<dyn Any>>,
}

impl Database {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn insert<T: 'static>(&mut self, item: T) -> Result<(), &'static str> {
        let id = TypeId::of::<T>();
        if self.db.contains_key(&id) {
            return Err("Already an item in the database!");
        }
        self.db.insert(id, Box::new(item));

        Ok(())
    }

    pub fn get<T: 'static>(&self) -> Option<&T> {
        self.db
            .get(&TypeId::of::<T>())
            .map(|a| a.downcast_ref().unwrap())
    }

    pub fn get_mut<T: 'static>(&mut self) -> Option<&mut T> {
        self.db
            .get_mut(&TypeId::of::<T>())
            .map(|a| a.downcast_mut().unwrap())
    }
}

pub struct State<R: Robot> {
    pub mode: Mode,
    previous_mode: Mode,
    robot_scheduler: Scheduler<R>,
    subsystems: Database,
}

impl<R: Robot> Default for State<R> {
    fn default() -> Self {
        Self {
            mode: Mode::None,
            previous_mode: Mode::None,
            robot_scheduler: Scheduler::default(),
            subsystems: Database::default(),
        }
    }
}

impl<R: Robot + 'static> State<R> {
    pub(crate) fn new() -> Self {
        Self::default()
    }

    pub(crate) fn periodic(&mut self, mode: Mode) {
        self.previous_mode = self.mode;
        self.mode = mode;
    }

    pub fn add_system<S: System<R> + 'static>(&mut self, mut subsystem: S) {
        subsystem.init(self);
        if let Err(_) = self.subsystems.insert((subsystem, Scheduler::<S>::new())) {
            panic!("Duplicate system added.");
        }
    }

    pub fn system_periodic<S: System<R> + 'static>(&mut self) {
        let mode = self.mode;
        let previous = self.previous_mode;

        let (system, scheduler) = self.get_system_mut::<S>().unwrap();

        scheduler.periodic(system);

        system.periodic(scheduler);
        match mode {
            Mode::Disabled => system.disabled_periodic(scheduler),
            Mode::Autonomous => system.autonomous_periodic(scheduler),
            Mode::Teleop => system.teleop_periodic(scheduler),
            Mode::Test => system.test_periodic(scheduler),
            _ => (),
        };

        if mode != previous {
            match previous {
                Mode::Disabled => system.disabled_exit(scheduler),
                Mode::Autonomous => system.autonomous_exit(scheduler),
                Mode::Teleop => system.teleop_exit(scheduler),
                Mode::Test => system.test_exit(scheduler),
                _ => {}
            }

            match mode {
                Mode::Disabled => system.disabled_init(scheduler),
                Mode::Autonomous => system.autonomous_init(scheduler),
                Mode::Teleop => system.teleop_init(scheduler),
                Mode::Test => system.test_init(scheduler),
                _ => {}
            }
        }
    }

    pub fn get_system<S: System<R> + 'static>(&self) -> Option<&(S, Scheduler<S>)> {
        self.subsystems.get()
    }

    pub fn get_system_mut<S: System<R> + 'static>(&mut self) -> Option<&mut (S, Scheduler<S>)> {
        self.subsystems.get_mut()
    }

    pub fn schedule(&mut self, robot: &mut R, command: impl Command<R> + 'static) {
        self.robot_scheduler.schedule(robot, command);
    }

    pub fn schedule_run(&mut self, robot: &mut R, function: impl FnMut(&mut R) + 'static) {
        self.robot_scheduler.schedule_run(robot, function);
    }
}
