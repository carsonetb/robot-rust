use robot_rust::prelude::*;

#[derive(Deref, DerefMut)]
struct MyMotor(TalonFX);

fn spin(mut motor: ResourceMut<MyMotor>) {
    motor.set_voltage(5.0.volts());
}

fn main() {
    let mut state = State::new().unwrap();

    state.insert_resource(MyMotor(TalonFX::new(1, "*")));

    state.add_systems(TeleopPeriodic, spin);

    state.run();
}
