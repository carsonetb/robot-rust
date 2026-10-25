use robot_rust::prelude::*;

fn hello_robot() {
    println!("Hello, Robot!")
}

fn main() {
    let mut state: State = State::new().unwrap();

    state.add_systems(Init, hello_robot);

    state.run();
}
