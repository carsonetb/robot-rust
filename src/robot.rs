use crate::{ffi::*, hal::ControlWord};

pub trait Robot {
    fn init(&mut self) {}
    fn disabled_periodic(&mut self) {}
    fn autonomous_periodic(&mut self) {}
    fn teleop_periodic(&mut self) {}
}

pub fn run<R: Robot>(mut robot: R) {
    unsafe {
        HAL_Initialize(500, 0);
        HAL_ObserveUserProgramStarting();
    }

    robot.init();

    loop {
        unsafe {
            HAL_RefreshDSData();
        }

        let control = ControlWord::new().unwrap();

        if control.enabled() {
            if control.teleop() {
                robot.teleop_periodic();
            } else if control.autonomous() {
                robot.autonomous_periodic();
            }
        } else {
            robot.disabled_periodic();
        }
    }
}
