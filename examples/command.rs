use robot_rust::prelude::*;

#[derive(Deref, DerefMut)]
struct Spinner(TalonFX);

struct SpinMotorCommand;

fn spin(spin: Command<SpinMotorCommand>, mut spinner: ResourceMut<Spinner>) {
    if spin.enabled() {
        spinner.set_voltage(5.0.volts());
    }

    if spin.just_ended() {
        spinner.set_voltage(0.0.volts());
    }
}

fn main() {
    let mut state: State = State::new().unwrap();

    state.insert_resource(Spinner(TalonFX::new(1, "*")));
    state.insert_resource(XboxController::new(0));

    state
        .register_command(SpinMotorCommand)
        .with_handler(TeleopPeriodic, spin)
        .on_trigger(XboxController::a_trigger);

    state.run();
}
