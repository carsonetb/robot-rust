use bevy_ecs::schedule::IntoScheduleConfigs;
use robot_rust::ctre::control::{PositionVoltage, VelocityVoltage};
use robot_rust::ctre::prelude::*;
use robot_rust::drivetrain::{Drivetrain, DrivingMotor, SwerveModule, TurningMotor};
use robot_rust::math::prelude::*;
use robot_rust::prelude::*;
use robot_rust::sim::runtime::BasicRuntime;

const DRIVE_PID_GAINS: PIDGains = PIDGains::new(0.0, 0.0, 0.0);
const STEER_PID_GAINS: PIDGains = PIDGains::new(10.0, 0.0, 2.0);
const DRIVE_GEAR_RATIO: f64 = 5.27;
const STEER_GEAR_RATIO: f64 = 26.09;

struct Mk5nDrivingMotor {
    pub motor: KrakenX60,
    pub control: VelocityVoltage,
}

impl Mk5nDrivingMotor {
    pub fn new(id: i32, bus: &'static str) -> Self {
        let mut motor = KrakenX60::new(id, bus).with_simulation_params(
            TalonFXMotorType::KrakenX60,
            1.0,
            0.01.moment_of_inertia(),
        );
        motor.configurator().apply(
            TalonFXConfiguration::new()
                .with_slot0(
                    Slot0Configs::new()
                        .with_pid(DRIVE_PID_GAINS)
                        .with_ks(0.19991)
                        .with_kv(0.63508)
                        .with_ka(0.07864),
                )
                .with_feedback(
                    FeedbackConfigs::new().with_sensor_to_mechanism_ratio(DRIVE_GEAR_RATIO),
                ),
        );
        Self {
            motor,
            control: VelocityVoltage::new(0.0.radians_per_second()),
        }
    }
}

impl DrivingMotor for Mk5nDrivingMotor {
    fn get_position(&mut self) -> Angle {
        self.motor.get_position()
    }

    fn get_velocity(&mut self) -> AngularVelocity {
        self.motor.get_velocity()
    }

    fn set_velocity(&mut self, velocity: AngularVelocity) {
        // self.motor
        //     .set_velocity_voltage(self.control.with_velocity(velocity));
    }

    fn simulate(&mut self) {
        self.motor.simulate();
    }
}

struct Mk5nTurningMotor {
    pub motor: KrakenX60,
    pub control: PositionVoltage,
}

impl Mk5nTurningMotor {
    pub fn new(id: i32, bus: &'static str) -> Self {
        let mut motor = KrakenX60::new(id, bus).with_simulation_params(
            TalonFXMotorType::KrakenX60,
            1.0,
            0.01.moment_of_inertia(),
        );
        motor.configurator().apply(
            TalonFXConfiguration::new()
                .with_slot0(Slot0Configs::new().with_pid(STEER_PID_GAINS))
                .with_feedback(FeedbackConfigs::new().with_rotor_to_sensor_ratio(STEER_GEAR_RATIO)),
        );
        Self {
            motor,
            control: PositionVoltage::new(0.0.radians()),
        }
    }
}

impl TurningMotor for Mk5nTurningMotor {
    fn get_position(&mut self) -> Angle {
        self.motor.get_position()
    }

    fn get_velocity(&mut self) -> AngularVelocity {
        self.motor.get_velocity()
    }

    fn set_target(&mut self, target: Angle) {
        self.motor
            .set_position_voltage(self.control.with_position(target));
    }

    fn simulate(&mut self) {
        self.motor.simulate();
    }
}

struct Mk5nDrivetrain {
    drivetrain: Drivetrain<4, Pigeon2, Mk5nTurningMotor, Mk5nDrivingMotor>,
    kinematics: SwerveDriveKinematics<4>,
}

impl Mk5nDrivetrain {
    fn new() -> Self {
        Self {
            drivetrain: Drivetrain::new(
                Pigeon2::new("*", 20),
                [
                    SwerveModule::new(
                        Mk5nTurningMotor::new(5, "*"),
                        Mk5nDrivingMotor::new(1, "*"),
                        1.9225.inches(),
                        Vec2::new(0.3145.meters(), -0.3145.meters()).angle(),
                        0.64,
                    ),
                    SwerveModule::new(
                        Mk5nTurningMotor::new(8, "*"),
                        Mk5nDrivingMotor::new(4, "*"),
                        1.9225.inches(),
                        Vec2::new(-0.3145.meters(), -0.3145.meters()).angle(),
                        0.64,
                    ),
                    SwerveModule::new(
                        Mk5nTurningMotor::new(6, "*"),
                        Mk5nDrivingMotor::new(2, "*"),
                        1.9225.inches(),
                        Vec2::new(0.3145.meters(), 0.3145.meters()).angle(),
                        0.64,
                    ),
                    SwerveModule::new(
                        Mk5nTurningMotor::new(7, "*"),
                        Mk5nDrivingMotor::new(3, "*"),
                        1.9225.inches(),
                        Vec2::new(-0.3145.meters(), 0.3145.meters()).angle(),
                        0.64,
                    ),
                ],
            ),
            kinematics: SwerveDriveKinematics::new([
                Vec2::new(0.3145.meters(), -0.3145.meters()), // front left
                Vec2::new(-0.3145.meters(), -0.3145.meters()), // front right
                Vec2::new(0.3145.meters(), 0.3145.meters()),  // back left
                Vec2::new(-0.3145.meters(), 0.3145.meters()), // back right
            ]),
        }
    }
}

fn drive_controller(
    mut controller: ResourceMut<XboxController>,
    mut drivetrain: ResourceMut<Mk5nDrivetrain>,
    mut logger: ResourceMut<Logger>,
) {
    controller.simulate();

    let speeds = ChassisSpeeds::discretize(
        controller.left_x() * 16.8.feet_per_second(),
        controller.left_y() * 16.8.feet_per_second(),
        controller.right_x() * 720.0.degrees_per_second(),
        20.0.milliseconds(),
    );
    let states = drivetrain
        .kinematics
        .to_swerve_module_states(speeds, Vec2::new(0.0.meters(), 0.0.meters()));
    drivetrain.drivetrain.set_desired_states(states);
    for (i, state) in drivetrain.drivetrain.get_states().iter().enumerate() {
        logger.append(&format!("States/{i}"), *state);
    }
    for (i, state) in states.iter().enumerate() {
        logger.append(&format!("TargetStates/{i}"), *state);
    }
    logger.append("TargetSpeeds", speeds);
}

fn drive_periodic(mut drivetrain: ResourceMut<Mk5nDrivetrain>) {
    drivetrain.drivetrain.simulate();
}

fn main() {
    let mut state: State = State::new().unwrap();
    state.subscribe();
    state.set_runtime(BasicRuntime);

    state.insert_resource(XboxController::new(0));

    state.insert_resource(Mk5nDrivetrain::new());
    // state.insert_resource(KrakenX60::new(5, "*"));
    state.add_systems(Periodic, (drive_controller, drive_periodic).chain());
    // state.add_systems(Periodic, test);

    state.run();
}
