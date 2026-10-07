mod ffi;
mod hal;
mod motor;
mod robot;

pub use crate::motor::KrakenX60;
use crate::motor::MotorController;
pub use robot::{Robot, run};

pub struct MyRobot {
    motor: KrakenX60,
}

impl MyRobot {
    fn new() -> Self {
        Self {
            motor: KrakenX60::new(0, "canivore"),
        }
    }
}

impl Robot for MyRobot {
    fn teleop_periodic(&mut self) {
        self.motor.set(0.2);
    }
}

fn main() {
    run(MyRobot::new());
}
