use robot_rust::ctre::KrakenX60;
use robot_rust::{AutoLog, Logger, Robot, State, run};

#[derive(AutoLog)]
struct MotorState {
    velocity: f64,
    angle: f64,
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
                velocity: 0.0,
                angle: 0.0,
            },
            logger: Logger::new("match.wpilog"),
        }
    }
}

impl Robot for MyRobot {
    fn periodic(&mut self, _state: &mut State<Self>) {
        // TODO: Get motor angle and velocity
        self.logger.append("Motor", &self.motor_state);
    }

    fn teleop_init(&mut self, state: &mut State<Self>) {
        state.schedule_run(self, |robot| robot.motor.set(0.0));
    }

    fn teleop_periodic(&mut self, _state: &mut State<Self>) {
        self.motor.set(0.2);
    }
}

fn main() {
    run(MyRobot::new());
}
