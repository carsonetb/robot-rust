use crate::{
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

pub trait Robot {
    fn init(&mut self) {}
    fn disabled_init(&mut self) {}
    fn teleop_init(&mut self) {}
    fn autonomous_init(&mut self) {}
    fn test_init(&mut self) {}

    fn disabled_exit(&mut self) {}
    fn teleop_exit(&mut self) {}
    fn autonomous_exit(&mut self) {}
    fn test_exit(&mut self) {}

    fn periodic(&mut self) {}
    fn disabled_periodic(&mut self) {}
    fn autonomous_periodic(&mut self) {}
    fn teleop_periodic(&mut self) {}
    fn test_periodic(&mut self) {}
}

pub fn run<R: Robot>(mut robot: R) {
    if !hal::init() {
        println!("HAL failed to initialize.");
        return;
    }
    hal::start();

    robot.init();

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
                Mode::Disabled => robot.disabled_exit(),
                Mode::Autonomous => robot.autonomous_exit(),
                Mode::Teleop => robot.teleop_exit(),
                Mode::Test => robot.test_exit(),
                _ => {}
            }

            match mode {
                Mode::Disabled => robot.disabled_init(),
                Mode::Autonomous => robot.autonomous_init(),
                Mode::Teleop => robot.teleop_init(),
                Mode::Test => robot.test_init(),
                _ => {}
            }
        }

        robot.periodic();
        match mode {
            Mode::Disabled => {
                hal::observe_disabled();
                robot.disabled_periodic()
            }
            Mode::Autonomous => {
                hal::observe_autonomous();
                robot.autonomous_periodic()
            }
            Mode::Teleop => {
                hal::observe_teleop();
                robot.teleop_periodic()
            }
            Mode::Test => {
                hal::observe_test();
                robot.test_periodic()
            }
            _ => {}
        }

        last_mode = mode;
    }
}
