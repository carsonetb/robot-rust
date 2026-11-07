use crate::math::prelude::*;
use crate::prelude::*;

pub trait DrivingMotor {
    fn get_position(&mut self) -> Angle;
    fn get_velocity(&mut self) -> AngularVelocity;
    fn set_velocity(&mut self, velocity: AngularVelocity);
    fn simulate(&mut self) {}
}

pub trait TurningMotor {
    fn get_position(&mut self) -> Angle;
    fn get_velocity(&mut self) -> AngularVelocity;
    fn set_target(&mut self, target: Angle);
    fn simulate(&mut self) {}
}

pub trait Gyro {
    fn get_rotation(&mut self) -> Angle;
    fn get_velocity(&mut self) -> AngularVelocity;
    fn set_rotation(&mut self, angle: Angle);
    fn simulate(&mut self) {}
}

impl Gyro for Pigeon2 {
    fn get_rotation(&mut self) -> Angle {
        self.get_yaw()
    }

    fn get_velocity(&mut self) -> AngularVelocity {
        self.get_velocity_z_world()
    }

    fn set_rotation(&mut self, angle: Angle) {
        self.set_yaw(angle);
    }

    fn simulate(&mut self) {
        self.simulate();
    }
}

#[derive(Debug, Clone)]
pub struct SwerveModule<T: TurningMotor, D: DrivingMotor> {
    pub turning: T,
    pub driving: D,
    pub chassis_angle: Rotation2D,
    desired: SwerveModuleState,
    wheel_radius: Length,
    coupling_ratio: f64,
}

impl<T: TurningMotor, D: DrivingMotor> SwerveModule<T, D> {
    pub fn new(
        mut turning: T,
        mut driving: D,
        wheel_radius: Length,
        chassis_angle: Rotation2D,
        coupling_ratio: f64,
    ) -> Self {
        let state = SwerveModuleState::new(
            driving.get_velocity().to_linear(wheel_radius),
            Rotation2D::new(turning.get_position()) + chassis_angle,
        );
        Self {
            turning,
            driving,
            desired: state,
            wheel_radius,
            chassis_angle,
            coupling_ratio,
        }
    }

    pub fn state(&mut self) -> SwerveModuleState {
        SwerveModuleState::new(
            self.driving.get_velocity().to_linear(self.wheel_radius),
            Rotation2D::new(self.turning.get_position()),
        )
    }

    pub fn position(&mut self) -> SwerveModulePosition {
        SwerveModulePosition::new(
            self.driving.get_position().to_linear(self.wheel_radius),
            Rotation2D::new(self.turning.get_position()),
        )
    }

    pub fn get_desired_state(&self) -> SwerveModuleState {
        self.desired
    }

    pub fn set_desired_state(&mut self, value: SwerveModuleState) {
        let current_angle = Rotation2D::new(self.turning.get_position());
        let mut corrected = SwerveModuleState::new(value.speed, value.angle);
        corrected.optimize(current_angle);
        // corrected.cosine_scale(current_angle);

        self.driving.set_velocity(
            (corrected.speed
                + (self.turning.get_velocity() * self.coupling_ratio).to_linear(self.wheel_radius))
            .to_angular(self.wheel_radius),
        );
        self.turning.set_target(corrected.angle.value);

        self.desired = corrected;
    }

    pub fn simulate(&mut self) {
        self.driving.simulate();
        self.turning.simulate();
    }
}

pub struct Drivetrain<const N: usize, G: Gyro, T: TurningMotor, D: DrivingMotor> {
    pub gyro: G,
    pub modules: [SwerveModule<T, D>; N],
}

impl<const N: usize, G: Gyro, T: TurningMotor, D: DrivingMotor> Drivetrain<N, G, T, D> {
    pub fn new(gyro: G, modules: [SwerveModule<T, D>; N]) -> Self {
        Self { gyro, modules }
    }

    pub fn set_desired_states(&mut self, states: [SwerveModuleState; N]) {
        for (module, state) in self.modules.iter_mut().zip(states) {
            module.set_desired_state(state);
        }
    }

    pub fn get_desired_states(&self) -> [SwerveModuleState; N] {
        std::array::from_fn(|i| self.modules[i].get_desired_state())
    }

    pub fn get_states(&mut self) -> [SwerveModuleState; N] {
        std::array::from_fn(|i| self.modules[i].state())
    }

    pub fn simulate(&mut self) {
        self.gyro.simulate();
        for module in &mut self.modules {
            module.simulate();
        }
    }
}
