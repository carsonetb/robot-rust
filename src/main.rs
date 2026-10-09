pub use commands::Scheduler;
pub use robot::{Mode, Robot, run};
pub use state::State;
pub use systems::System;

use crate::ctre::KrakenX60;

mod commands;
mod ctre;
mod ds;
mod ffi;
mod hal;
mod rev;
mod robot;
mod state;
mod systems;

struct MySystem;

impl System<MyRobot> for MySystem {}

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
    fn init(&mut self, state: &mut State<Self>) {
        state.add_system(MySystem);
    }

    fn periodic(&mut self, state: &mut State<Self>) {
        state.system_periodic::<MySystem>();
    }

    fn teleop_init(&mut self, state: &mut State<Self>) {
        state.schedule_run(self, |robot| robot.motor.set(0.0));
    }

    fn teleop_periodic(&mut self, _state: &mut State<Self>) {
        self.motor.set(0.2);
    }
}

fn main() {
    run(MyRobot::new());
}
