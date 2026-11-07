use robot_rust::prelude::*;

#[derive(Deref, DerefMut)]
struct Spinner(TalonFX);

#[derive(Reflect)]
struct SpinMotorCommand;
#[derive(Reflect)]
struct AfterwardsCommand;

fn periodic(mut controller: ResourceMut<XboxController>) {
    controller.simulate();
}

fn spin(spin: Command<SpinMotorCommand>, mut spinner: ResourceMut<Spinner>) {
    if spin.enabled() {
        spinner.set_voltage(5.0.volts());
    }

    if spin.just_ended() {
        spinner.set_voltage(0.0.volts());
    }

    spinner.simulate();
}

fn run_afterwards(after: Command<AfterwardsCommand>) {
    if after.just_started() {
        println!("The spinner stopped!")
    }
}

fn main() {
    let mut state: State = State::new().unwrap();
    state.set_runtime(BasicRuntime);

    state.insert_resource(Spinner(TalonFX::new(1, "*")));
    state.insert_resource(XboxController::new(0));

    state.add_systems(Periodic, periodic);

    state
        .register_command(SpinMotorCommand)
        .with_handler(TeleopPeriodic, spin)
        .while_trigger(XboxController::a_trigger)
        .after::<AfterwardsCommand>();
    state
        .register_command(AfterwardsCommand)
        .with_handler(TeleopPeriodic, run_afterwards);

    state.run();
}
