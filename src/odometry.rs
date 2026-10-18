use std::marker::PhantomData;

use crate::kinematics::{DifferentialDriveWheelPositions, Kinematics};
use crate::prelude::*;

#[derive(Debug, Clone)]
pub struct Odometry<S, P, K: Kinematics<S, P>> {
    kinematics: K,
    pub pose: Pose2D,
    previous_wheel_positions: P,
    previous_angle: Rotation2D,
    gyro_offset: Rotation2D,
    _speeds: PhantomData<S>,
}

impl<S, P, K: Kinematics<S, P>> Odometry<S, P, K> {
    pub fn new(
        kinematics: K,
        gyro_angle: Rotation2D,
        wheel_positions: P,
        initial_pose: Pose2D,
    ) -> Self {
        Self {
            kinematics,
            pose: initial_pose,
            previous_wheel_positions: wheel_positions,
            previous_angle: initial_pose.rotation,
            gyro_offset: (-gyro_angle).rotated(&initial_pose.rotation),
            _speeds: PhantomData,
        }
    }

    pub fn reset_position(&mut self, gyro_angle: Rotation2D, wheel_positions: P, pose: Pose2D) {
        self.pose = pose;
        self.previous_angle = pose.rotation;
        self.gyro_offset = (-gyro_angle).rotated(&pose.rotation);
        self.previous_wheel_positions = wheel_positions;
    }

    pub fn reset_pose(&mut self, pose: Pose2D) {
        self.gyro_offset = self
            .gyro_offset
            .rotated(&-self.pose.rotation)
            .rotated(&pose.rotation);
        self.pose = pose;
        self.previous_angle = pose.rotation;
    }

    pub fn reset_translation(&mut self, translation: Vec2) {
        self.pose = Pose2D::new(translation, self.pose.rotation);
    }

    pub fn reset_rotation(&mut self, rotation: Rotation2D) {
        self.gyro_offset = self
            .gyro_offset
            .rotated(&self.pose.rotation)
            .rotated(&rotation);
        self.pose = Pose2D::new(self.pose.pos, rotation);
        self.previous_angle = rotation;
    }

    pub fn update(&mut self, gyro_angle: Rotation2D, wheel_positions: P) -> Pose2D {
        let angle = gyro_angle.rotated(&self.gyro_offset);
        let mut twist = self
            .kinematics
            .to_twist2d(&self.previous_wheel_positions, &wheel_positions);
        twist.dtheta = (angle - self.previous_angle).value;

        let new_pose = self.pose.exp(&twist);

        self.previous_angle = angle;
        self.previous_wheel_positions = wheel_positions;
        self.pose = Pose2D::new(new_pose.pos, angle);

        self.pose
    }
}

#[derive(Debug, Clone, Deref, DerefMut)]
pub struct DifferentialDriveOdometry(
    Odometry<
        DifferentialDriveWheelSpeeds,
        DifferentialDriveWheelPositions,
        DifferentialDriveKinematics,
    >,
);

impl DifferentialDriveOdometry {
    pub fn new(gyro_angle: Rotation2D, left: Length, right: Length, start_pose: Pose2D) -> Self {
        Self(Odometry::new(
            DifferentialDriveKinematics::new(1.0.meters()),
            gyro_angle,
            DifferentialDriveWheelPositions::new(left, right),
            start_pose,
        ))
    }

    pub fn reset_position(
        &mut self,
        gyro_angle: Rotation2D,
        left: Length,
        right: Length,
        pose: Pose2D,
    ) {
        self.0.reset_position(
            gyro_angle,
            DifferentialDriveWheelPositions::new(left, right),
            pose,
        );
    }

    pub fn update(&mut self, gyro_angle: Rotation2D, left: Length, right: Length) -> Pose2D {
        self.0.update(
            gyro_angle,
            DifferentialDriveWheelPositions::new(left, right),
        )
    }
}

impl PoseProvider for DifferentialDriveOdometry {
    fn get_pose(&mut self) -> Pose2D {
        self.0.pose
    }
}
