use robot_rust::ctre::TalonFXMotorType;
use robot_rust::prelude::*;

#[derive(Deref, DerefMut)]
struct MyMotor(TalonFX);

fn spin(mut motor: ResourceMut<MyMotor>) {
    motor.set_voltage(12.0.volts());
    motor.simulate();
    dbg!(motor.get_velocity());
}

fn main() {
    let mut state: State = State::new().unwrap();
    state.set_runtime(BasicRuntime);
    state.subscribe();

    state.insert_resource(MyMotor(TalonFX::new(1, "*").with_simulation_params(
        TalonFXMotorType::KrakenX60,
        1.0,
        0.001.moment_of_inertia(),
    )));
    state.add_systems(TeleopPeriodic, spin);

    state.run();
}
