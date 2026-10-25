use robot_rust::prelude::*;
use robot_rust::sim::runtime::BasicRuntime;

#[derive(Deref, DerefMut)]
struct MyMotor(TalonFX);

fn spin(mut motor: ResourceMut<MyMotor>) {
    motor.set_voltage(5.0.volts());
}

fn main() {
    let mut state: State = State::new().unwrap();
    // Allow simulation
    state.set_runtime(BasicRuntime);
    state.subscribe();

    state.insert_resource(MyMotor(TalonFX::new(1, "*")));
    state.add_systems(TeleopPeriodic, spin);

    state.run();
}
