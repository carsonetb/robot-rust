use robot_rust::prelude::*;
use robot_rust::rev::prelude::*;

#[derive(Deref, DerefMut)]
struct MyMotor(SparkMax);

fn spin(mut motor: ResourceMut<MyMotor>) {
    motor.set_voltage(5.0.volts());
}

fn main() {
    let mut state: State = State::new().unwrap();

    state.insert_resource(MyMotor(SparkMax::new(1, MotorType::Brushless)));

    state.add_systems(TeleopPeriodic, spin);

    state.run();
}
