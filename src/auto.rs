use crate::math::prelude::*;
use crate::prelude::*;

pub trait PoseProvider {
    fn get_pose(&mut self) -> Pose2D;
}

pub struct AutoPose {
    pub pose: Pose2D,
}

impl AutoPose {
    pub fn new(pose: Pose2D) -> Self {
        Self { pose }
    }
}

enum AutoAction {
    Follow(Pose2D),
    Run(Box<dyn FnMut(&mut StateRes)>),
}

pub trait TankDrive {
    fn drive(&mut self, velocity: Velocity, rotation: AngularVelocity);
}

pub trait IntoTankAuto {
    fn into(&mut self) -> &mut TankAuto;
}

pub struct TankAuto {
    actions: Vec<AutoAction>,
    velocity: LinearTrapezoidProfile,
    angular_velocity: AngularTrapezoidProfile,
    last_velocity: Velocity,
    last_angular_velocity: AngularVelocity,
    tolerance: Length,
    angular_tolerance: Angle,
}

impl TankAuto {
    pub fn new(
        velocity: LinearTrapezoidProfile,
        angular_velocity: AngularTrapezoidProfile,
        tolerance: Length,
        angular_tolerance: Angle,
    ) -> Self {
        Self {
            actions: Vec::new(),
            velocity,
            angular_velocity,
            last_velocity: 0.0.meters_per_second(),
            last_angular_velocity: 0.0.radians_per_second(),
            tolerance,
            angular_tolerance,
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

pub fn tank_auto<A: IntoTankAuto, D: TankDrive, P: PoseProvider>(
    mut state: StateRes,
    mut auto: ResourceMut<A>,
    mut drive: ResourceMut<D>,
    mut provider: ResourceMut<P>,
) {
    let auto = auto.as_mut().into();

    while let Some(AutoAction::Run(run)) = auto.actions.last_mut() {
        run.as_mut()(&mut state);
        auto.actions.pop();
    }

    let Some(AutoAction::Follow(target)) = auto.actions.last() else {
        drive.drive(0.0.meters_per_second(), 0.0.radians_per_second());
        return;
    };

    let current = provider.get_pose();

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
        drive.drive(0.0.meters_per_second(), 0.0.radians_per_second());
        auto.actions.pop();
    }

    let angular_velocity = auto
        .angular_velocity
        .calculate(
            20.0.milliseconds(),
            AngularTrapezoidState::new(0.0.radians(), auto.last_angular_velocity),
            AngularTrapezoidState::new(angle_dist.value, 0.0.radians_per_second()),
        )
        .velocity;

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
    auto.last_angular_velocity = angular_velocity;

    drive.drive(velocity, angular_velocity);
}
