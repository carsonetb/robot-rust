use crate::math::prelude::*;
use crate::prelude::*;

pub trait Drivetrain {
    /// Drive with field-relative speeds and angular setpoint.
    fn drive(&mut self, vx: Velocity, vy: Velocity, setpoint: Angle);
    /// Get the robot-relative speeds of this drivetrain.
    fn get_robot_relative_speeds(&mut self) -> ChassisSpeeds;
    /// Get the field-relative speeds of this drivetrain.
    fn get_field_relative_speeds(&mut self) -> ChassisSpeeds;
    /// Get the field-relative pose of this drivetrain.
    fn get_pose(&mut self) -> Pose2D;
}

pub struct AutoPose {
    pub pose: Pose2D,
    pub entry: Option<Angle>,
    pub velocity: Velocity,
}

impl AutoPose {
    pub fn new(pose: Pose2D, velocity: Velocity) -> Self {
        Self {
            pose,
            entry: None,
            velocity,
        }
    }

    pub fn with_entry_angle(mut self, angle: Angle) -> Self {
        self.entry = Some(angle);
        self
    }
}

pub enum AutoAction {
    Follow(Pose2D),
    Run(Box<dyn FnMut(&mut StateRes)>),
    Wait(Time),
}

pub trait IntoTankAuto {
    fn into(&mut self) -> &mut TankAuto;
}

pub struct Auto {
    pub actions: Vec<AutoAction>,
}

impl Auto {
    pub fn new() -> Self {
        Self {
            actions: Vec::new(),
        }
    }

    pub fn with_pose(&mut self, pose: Pose2D) -> &mut Self {
        self.actions.insert(0, AutoAction::Follow(pose));
        self
    }

    pub fn with_action(&mut self, action: impl FnMut(&mut StateRes) + 'static) -> &mut Self {
        self.actions.insert(0, AutoAction::Run(Box::new(action)));
        self
    }
}

pub struct TankAuto {
    pub auto: Auto,
    pub velocity: LinearTrapezoidProfile,
    pub tolerance: Length,
    pub angular_tolerance: Angle,
    pub angular_velocity: AngularTrapezoidProfile,
    pub last_velocity: Velocity,
    pub last_angular_velocity: AngularVelocity,
}

impl TankAuto {
    pub fn new(
        auto: Auto,
        velocity: LinearTrapezoidProfile,
        angular_velocity: AngularTrapezoidProfile,
        tolerance: Length,
        angular_tolerance: Angle,
    ) -> Self {
        Self {
            auto,
            velocity,
            angular_velocity,
            last_velocity: 0.0.meters_per_second(),
            last_angular_velocity: 0.0.radians_per_second(),
            tolerance,
            angular_tolerance,
        }
    }
}

pub fn tank_auto<A: IntoTankAuto, D: Drivetrain>(
    mut state: StateRes,
    mut auto: ResourceMut<A>,
    mut drive: ResourceMut<D>,
) {
    let auto = auto.as_mut().into();

    while let Some(AutoAction::Run(run)) = auto.auto.actions.last_mut() {
        run.as_mut()(&mut state);
        auto.auto.actions.pop();
    }

    let angle = drive.get_pose().rotation.value;

    let Some(AutoAction::Follow(target)) = auto.auto.actions.last() else {
        drive.drive(0.0.meters_per_second(), 0.0.meters_per_second(), angle);
        return;
    };

    let current = drive.get_pose();

    let distance = current.pos.distance_to(&target.pos);
    let at_position = distance <= auto.tolerance;

    let diff = (target.pos - current.pos).angle();
    let angle_dist = if !at_position {
        let mut angle_dist = diff.relative(&current.rotation);
        if angle_dist.value.abs() > std::f64::consts::FRAC_PI_2.radians() {
            angle_dist = (diff + Rotation2D::new(180.0.degrees())).relative(&current.rotation);
        }
        angle_dist
    } else {
        target.rotation.relative(&current.rotation)
    };
    let raw_angle_difference = diff.relative(&current.rotation);
    let at_angle = angle_dist.value.abs() <= auto.angular_tolerance;

    if at_position && at_angle {
        drive.drive(0.0.meters_per_second(), 0.0.meters_per_second(), angle);
        auto.auto.actions.pop();
    }

    let angular_state = auto.angular_velocity.calculate(
        20.0.milliseconds(),
        AngularTrapezoidState::new(0.0.radians(), auto.last_angular_velocity),
        AngularTrapezoidState::new(angle_dist.value, 0.0.radians_per_second()),
    );

    let velocity = if !at_position {
        auto.velocity
            .calculate(
                20.0.milliseconds(),
                LinearTrapezoidState::new(0.0.meters(), auto.last_velocity),
                LinearTrapezoidState::new(distance, 0.0.meters_per_second()),
            )
            .velocity
            * raw_angle_difference.cos() // Scales based on how facing the point the robot is.
    } else {
        0.0.meters_per_second()
    };

    auto.last_velocity = velocity;
    auto.last_angular_velocity = angular_state.velocity;

    let field_relative_x = velocity * angle.cos();
    let field_relative_y = velocity * angle.sin();
    drive.drive(field_relative_x, field_relative_y, angular_state.position);
}

pub trait IntoSwerveAuto {
    fn into(&mut self) -> SwerveAuto;
}

pub struct SwerveAuto {
    pub auto: Auto,
}

impl SwerveAuto {
    pub fn new(auto: Auto) -> Self {
        Self { auto }
    }
}

pub fn swerve_auto<D: Drivetrain>() {}
