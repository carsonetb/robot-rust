mod ffi;
mod hal;
mod motor;
mod robot;

pub use robot::{Robot, run};

pub struct MyRobot;

impl Robot for MyRobot {}

fn main() {
    run(MyRobot);
}
