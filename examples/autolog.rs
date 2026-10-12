use robot_rust::prelude::*;

#[derive(AutoLog, Clone, Copy)]
struct MotorState {
    velocity: AngularVelocity,
    angle: Angle,
}

struct MyRobot {
    motor: KrakenX60,
    motor_state: MotorState,
    logger: Logger,
}

impl MyRobot {
    fn new() -> Self {
        Self {
            motor: KrakenX60::new(0, "canivore"),
            motor_state: MotorState {
                velocity: 0.0.rotations_per_second(),
                angle: 0.0.rotations(),
            },
            logger: Logger::new("match.wpilog"),
        }
    }
}

fn periodic(mut robot: ResourceMut<MyRobot>) {
    robot.motor_state = MotorState {
        velocity: robot.motor.get_velocity(),
        angle: robot.motor.get_position(),
    };

    let state = robot.motor_state;
    robot.logger.append("Motor", state);
}

fn teleop_periodic(mut robot: ResourceMut<MyRobot>) {
    robot.motor.set(0.2);
}

fn main() {
    let mut state = State::new().unwrap();

    state.add_systems(Periodic, periodic);
    state.add_systems(TeleopPeriodic, teleop_periodic);

    state.insert_resource(MyRobot::new());

    state.run();
}
