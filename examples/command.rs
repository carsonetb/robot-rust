use robot_rust::prelude::*;

struct SpinMotorCommand;

struct Robot {
    motor: TalonFX,
    controller: XboxController,
}

impl Robot {
    fn new() -> Self {
        Self {
            motor: TalonFX::new(1, "*"),
            controller: XboxController::new(0),
        }
    }
}

struct RobotTargets {
    voltage: Voltage,
}

fn spin(spin: Command<SpinMotorCommand>, mut targets: ResourceMut<RobotTargets>) {
    if spin.enabled() {
        targets.voltage = 5.0.volts();
    }

    if spin.just_ended() {
        targets.voltage = 0.0.volts();
    }
}

fn main() {
    let mut state = State::new().unwrap();

    state.insert_resource(Robot::new());

    state.add_systems(TeleopPeriodic, spin);

    state.run();
}
