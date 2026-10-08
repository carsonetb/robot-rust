///! Utilities for creating an all-encompassing robot class.
use crate::{
    commands::{Command, Scheduler},
    ds::{self, AlertType},
    hal::{self, ControlWord},
};

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Mode {
    None,
    Disabled,
    Autonomous,
    Teleop,
    Test,
}

/// Trait for a robot. Not all functions need to be overriden. Your robot
/// should implement this trait and then be passed to the `run` function.
pub trait Robot: Sized {
    /// First function called, you should not interact with harder before this
    /// function or risk causing a Segmentation Fault.
    fn init(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
    /// Called when the robot moves into the disabled state.
    fn disabled_init(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
    /// Called when the robot moves into the teleop state.
    fn teleop_init(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
    /// Called when the robot moves into the autonomous state.
    fn autonomous_init(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
    /// Called when the robot moves into the test state.
    fn test_init(&mut self, state: &mut State<Self>) {
        let _ = state;
    }

    /// Called when the robot leaves the disabled state.
    fn disabled_exit(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
    /// Called when the robot leaves the teleop state.
    fn teleop_exit(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
    /// Called when the robot leaves the autonomous state.
    fn autonomous_exit(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
    /// Called when the robot leaves the test state.
    fn test_exit(&mut self, state: &mut State<Self>) {
        let _ = state;
    }

    /// Called every ~20ms regardless of the state of the robot.
    fn periodic(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
    /// Called every ~20ms when the robot is disabled.
    fn disabled_periodic(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
    /// Called every ~20ms when the robot is in the autonomous state.
    fn autonomous_periodic(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
    /// Called every ~20ms when the robot is in the teleop state.
    fn teleop_periodic(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
    /// Called every ~20ms when the robot is in the test state.
    fn test_periodic(&mut self, state: &mut State<Self>) {
        let _ = state;
    }
}

pub struct State<R: Robot> {
    scheduler: Scheduler<R>,
}

impl<R: Robot> State<R> {
    fn new() -> Self {
        Self {
            scheduler: Scheduler::new(),
        }
    }

    pub fn schedule(&mut self, robot: &mut R, command: impl Command<R> + 'static) {
        self.scheduler.schedule(command, robot);
    }
}

/// Called to run the robot. This function will block the thread and run until
/// the program is terminated.
pub fn run<R: Robot>(mut robot: R) {
    if !hal::init() {
        println!("HAL failed to initialize.");
        return;
    }
    hal::start();

    let mut state = State::new();

    robot.init(&mut state);

    let mut last_mode = Mode::None;

    loop {
        if !ds::refresh() {
            ds::alert(AlertType::Error, "DS failed to refresh data.");
            continue;
        }

        let word = ControlWord::new().unwrap();

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

        if mode != last_mode {
            match last_mode {
                Mode::Disabled => robot.disabled_exit(&mut state),
                Mode::Autonomous => robot.autonomous_exit(&mut state),
                Mode::Teleop => robot.teleop_exit(&mut state),
                Mode::Test => robot.test_exit(&mut state),
                _ => {}
            }

            match mode {
                Mode::Disabled => robot.disabled_init(&mut state),
                Mode::Autonomous => robot.autonomous_init(&mut state),
                Mode::Teleop => robot.teleop_init(&mut state),
                Mode::Test => robot.test_init(&mut state),
                _ => {}
            }
        }

        robot.periodic(&mut state);
        match mode {
            Mode::Disabled => {
                hal::observe_disabled();
                robot.disabled_periodic(&mut state)
            }
            Mode::Autonomous => {
                hal::observe_autonomous();
                robot.autonomous_periodic(&mut state)
            }
            Mode::Teleop => {
                hal::observe_teleop();
                robot.teleop_periodic(&mut state)
            }
            Mode::Test => {
                hal::observe_test();
                robot.test_periodic(&mut state)
            }
            _ => {}
        }

        last_mode = mode;
    }
}
