use std::marker::PhantomData;

use super::prelude::*;

/// Class for odometry. Robot code should not use this directly---Instead, use the
/// particular type for your drivetrain (e.g., DifferentialDriveOdometry).
/// Odometry allows you to track the robot's position on the field over a course
/// of a match using readings from your wheel encoders.
///
/// Teams can use odometry during the autonomous period for complex tasks like
/// path following. Furthermore, odometry can be used for latency compensation
/// when using computer-vision systems.
///
/// ## Type parameters:
///
/// * S: Wheel speeds representation.
/// * P: Wheel positions representation.
/// * K: Kinematics implementation.
#[derive(Debug, Clone)]
pub struct Odometry<S, P, K: Kinematics<S, P>> {
    kinematics: K,
    /// Estimated position of the robot.
    pub pose: Pose2D,
    previous_wheel_positions: P,
    previous_angle: Rotation2D,
    gyro_offset: Rotation2D,
    _speeds: PhantomData<S>,
}

impl<S, P, K: Kinematics<S, P>> Odometry<S, P, K> {
    /// Constructs an Odometry object.
    ///
    /// ## Parameters:
    ///
    /// * kinematics: The kinematics for your drivetrain.
    /// * gyro_angle: The angle reported by the gyroscope.
    /// * wheel_positions: The current distances measured by each wheel.
    /// * initial_pose: The starting position of the robot on the field.

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

    /// Resets the robot's position on the field.
    ///
    /// The gyroscope angle does not need to be reset here on the user's robot
    /// code. The library automatically takes care of offsetting the gyro angle.
    ///
    /// ## Parameters
    ///
    /// * gyro_angle: The angle reported by the gyroscope.
    /// * wheel_positions: The current distances measured by each wheel.
    /// * pose: The position on the field that your robot is at.

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

    /// Resets the translation of the odometry pose.
    pub fn reset_translation(&mut self, translation: Vec2) {
        self.pose = Pose2D::new(translation, self.pose.rotation);
    }

    /// Resets the rotation of the odometry pose.
    pub fn reset_rotation(&mut self, rotation: Rotation2D) {
        self.gyro_offset = self
            .gyro_offset
            .rotated(&self.pose.rotation)
            .rotated(&rotation);
        self.pose = Pose2D::new(self.pose.pos, rotation);
        self.previous_angle = rotation;
    }

    /// Updates the robot's position on the field using forward kinematics and
    /// integration of the pose over time. This method takes in an angle parameter
    /// which is used instead of the angular rate that is calculated from forward
    /// kinematics, in addition to the current distance measurement at each wheel.
    ///
    /// Returns the new pose of the robot.
    ///
    /// ## Parameters
    ///
    /// * gyro_angle: The angle reported by the gyroscope.
    /// * wheel_positions: The current distances measured by each wheel.

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

/// Class for differential drive odometry. Odometry allows you to track the
/// robot's position on the field over the course of a match using readings from
/// 2 encoders and a gyroscope.
///
/// Teams can use odometry during the autonomous period for complex tasks like
/// path following. Furthermore, odometry can be used for latency compensation
/// when using computer-vision systems.
///
/// It is important that you reset your encoders to zero before using this class.
/// Any subsequent pose resets also require the encoders to be reset to zero.
#[derive(Debug, Clone, Deref, DerefMut)]
pub struct DifferentialDriveOdometry(
    pub  Odometry<
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

    /// Resets the robot's position on the field.
    ///
    /// IF leftDistance and rightDistance are unspecified,
    /// You NEED to reset your encoders (to zero).
    ///
    /// The gyroscope angle does not need to be reset here on the user's robot
    /// code. The library automatically takes care of offsetting the gyro angle.
    ///
    /// ## Parameters
    ///
    /// * gyro_angle: The angle reported by the gyroscope.
    /// * left: The distance traveled by the left encoder.
    /// * right: The distance traveled by the right encoder.
    /// * pose: The position on the field that your robot is at.
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

    /// Updates the robot position on the field using distance measurements from
    /// encoders. This method is more numerically accurate than using velocities to
    /// integrate the pose and is also advantageous for teams that are using lower
    /// CPR encoders.
    ///
    /// Returns the new pose of the robot.
    ///
    /// ## Parameters
    ///
    /// * gyro_angle: The angle reported by the gyroscope.
    /// * left: The distance traveled by the left encoder.
    /// * right: The distance traveled by the right encoder.
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

/// Class for swerve drive odometry. Odometry allows you to track the robot's
/// position on the field over a course of a match using readings from your
/// swerve drive encoders and swerve azimuth encoders.
///
/// Teams can use odometry during the autonomous period for complex tasks like
/// path following. Furthermore, odometry can be used for latency compensation
/// when using computer-vision systems.
///
/// ## Type parameters
///
/// * N: Number of swerve modules to use, typically 4.
#[derive(Debug, Clone, Deref, DerefMut)]
pub struct SwerveDriveOdometry<const N: usize>(
    pub Odometry<[SwerveModuleState; N], [SwerveModulePosition; N], SwerveDriveKinematics<N>>,
);

impl<const N: usize> SwerveDriveOdometry<N> {
    /// Constructs a SwerveDriveOdometry object.
    ///
    /// ## Parameters
    ///
    /// * kinematics The swerve drive kinematics for your drivetrain.
    /// * gyro_angle The angle reported by the gyroscope.
    /// * module_positions The wheel positions reported by each module.
    /// * initial_pose The starting position of the robot on the field.
    pub fn new(
        kinematics: SwerveDriveKinematics<N>,
        gyro_angle: Rotation2D,
        module_positions: [SwerveModulePosition; N],
        initial_pose: Pose2D,
    ) -> Self {
        Self(Odometry::new(
            kinematics,
            gyro_angle,
            module_positions,
            initial_pose,
        ))
    }
}

impl<const N: usize> PoseProvider for SwerveDriveOdometry<N> {
    fn get_pose(&mut self) -> Pose2D {
        self.0.pose
    }
}

#[derive(Debug, Clone)]
pub struct Odometry3D<S, P, K: Kinematics<S, P>> {
    kinematics: K,
    /// Estimated position of the robot.
    pub pose: Pose3D,
    previous_wheel_positions: P,
    previous_angle: Rotation3D,
    gyro_offset: Rotation3D,
    _speeds: PhantomData<S>,
}

impl<S, P, K: Kinematics<S, P>> Odometry3D<S, P, K> {
    pub fn new(
        kinematics: K,
        gyro_angle: Rotation3D,
        wheel_positions: P,
        initial_pose: Pose3D,
    ) -> Self {
        Self {
            kinematics,
            pose: initial_pose,
            previous_wheel_positions: wheel_positions,
            previous_angle: initial_pose.rot,
            gyro_offset: (-gyro_angle).rotate_by(initial_pose.rot),
            _speeds: PhantomData,
        }
    }

    pub fn reset_position(&mut self, gyro_angle: Rotation3D, wheel_positions: P, pose: Pose3D) {
        self.pose = pose;
        self.previous_angle = pose.rot;
        self.gyro_offset = (-gyro_angle).rotate_by(pose.rot);
        self.previous_wheel_positions = wheel_positions;
    }

    pub fn reset_pose(&mut self, pose: Pose3D) {
        self.gyro_offset = self
            .gyro_offset
            .rotate_by(-self.pose.rot)
            .rotate_by(pose.rot);
    }
}
