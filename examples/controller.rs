use robot_rust::prelude::*;

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

fn spin(mut robot: ResourceMut<Robot>) {
    let voltage = (robot.controller.right_trigger() * 5.0).volts();
    robot.motor.set_voltage(voltage);
}

fn main() {
    let mut state = State::new().unwrap();

    state.insert_resource(Robot::new());

    state.add_systems(TeleopPeriodic, spin);

    state.run();
}
