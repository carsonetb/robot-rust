pub use robot::{Robot, State, run};

use crate::ctre::KrakenX60;

mod commands;
mod ctre;
mod ds;
mod ffi;
mod hal;
mod robot;

struct MyRobot {
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
    fn teleop_init(&mut self, state: &mut State<Self>) {
        state.schedule::<Self>(self, |robot| robot.motor.set(0.0));
    }

    fn teleop_periodic(&mut self, _state: &mut State<Self>) {
        self.motor.set(0.2);
    }
}

fn main() {
    run(MyRobot::new());
}
