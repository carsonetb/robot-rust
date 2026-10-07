pub use crate::motor::KrakenX60;
pub use robot::{Robot, run};

mod ds;
mod ffi;
mod hal;
mod motor;
mod robot;

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
