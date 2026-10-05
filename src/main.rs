mod ffi;
mod hal;
mod motor;
mod robot;

pub use crate::motor::KrakenX60;
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

impl Robot for MyRobot {}

fn main() {
    run(MyRobot::new());
}
