use robot_rust::ctre::prelude::*;
use robot_rust::prelude::*;
use uom::si::angular_acceleration::degree_per_second_squared;
use uom::si::angular_jerk::degree_per_second_cubed;
use uom::si::angular_velocity::degree_per_second;
use uom::si::f64::{AngularAcceleration, AngularJerk, AngularVelocity};

struct MyRobot {
    motor: KrakenX60,
}

impl MyRobot {
    fn new() -> Self {
        Self {
            motor: KrakenX60::new(0, "canivore"),
        }
    }
}

impl Robot for MyRobot {
    fn init(&mut self, _state: &mut State<Self>) {
        self.motor.configurator().apply(
            TalonFXConfiguration::new()
                .with_slot0(Slot0Configs::new().with_kp(120.0).with_kd(0.5))
                .with_motion_magic(
                    MotionMagicConfigs::new()
                        .with_cruise_velocity(AngularVelocity::new::<degree_per_second>(320.0))
                        .with_acceleration(AngularAcceleration::new::<degree_per_second_squared>(
                            400.0,
                        ))
                        .with_jerk(AngularJerk::new::<degree_per_second_cubed>(20.0)),
                )
                .with_feedback(
                    FeedbackConfigs::new()
                        .with_sensor_source(FeedbackSensorSource::RemoteCANcoder)
                        .with_remote_sensor_id(43)
                        .with_sensor_to_mechanism_ratio(32.0 / 12.0)
                        .with_rotor_to_sensor_ratio(4.0),
                )
                .with_motor_output(
                    MotorOutputConfigs::new()
                        .with_neutral_mode(NeutralMode::Brake)
                        .with_inverted(Direction::CounterClockwise),
                ),
        );
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
