use std::collections::BTreeMap;

use ordered_float::OrderedFloat;

use super::interpolation::TimeInterpolatableBuffer;
use super::prelude::*;

#[derive(Debug, Default, Clone)]
pub struct VisionUpdate {
    vision: Pose2D,
    odometry: Pose2D,
}

impl VisionUpdate {
    pub fn new(vision: Pose2D, odometry: Pose2D) -> Self {
        Self { vision, odometry }
    }

    pub fn compensate(&self, pose: Pose2D) -> Pose2D {
        let delta = self.odometry.to(&pose);
        self.vision.transformed(&delta)
    }
}

pub struct PoseEstimator<S, P, K: Kinematics<S, P>> {
    odometry: Odometry<S, P, K>,
    q: [f64; 3],
    vision_k: nalgebra::Matrix3<f64>,
    odometry_pose_buffer: TimeInterpolatableBuffer<Pose2D>,
    vision_updates: BTreeMap<ordered_float::OrderedFloat<f64>, VisionUpdate>,
    pub pose_estimate: Pose2D,
}

impl<S, P, K: Kinematics<S, P>> PoseEstimator<S, P, K> {
    pub fn new(
        odometry: Odometry<S, P, K>,
        state_std_devs: [f64; 3],
        vision_measurement_std_devs: [f64; 3],
    ) -> Self {
        let mut q = [0.0; 3];
        for i in 0..3 {
            q[i] = state_std_devs[i].powi(2);
        }

        let pose_estimate = odometry.pose;
        let mut out = Self {
            odometry,
            q,
            vision_k: nalgebra::Matrix3::zeros(),
            odometry_pose_buffer: TimeInterpolatableBuffer::new(
                1.5.seconds(),
                |left: &Pose2D, right, t| left.lerp(*right, t),
            ),
            vision_updates: BTreeMap::new(),
            pose_estimate,
        };
        out.set_vision_measurement_std_devs(vision_measurement_std_devs);
        out
    }

    pub fn set_vision_measurement_std_devs(&mut self, vision_measurement_std_devs: [f64; 3]) {
        let mut r = [0.0; 3];
        for i in 0..3 {
            r[i] = vision_measurement_std_devs[i].powi(2);
        }

        for row in 0..3 {
            if self.q[row] == 0.0 {
                self.vision_k[(row, row)] = 0.0;
            } else {
                self.vision_k[(row, row)] =
                    self.q[row] / (self.q[row] + (self.q[row] * r[row]).sqrt());
            }
        }
    }

    pub fn reset_position(&mut self, gyro_angle: Rotation2D, wheel_positions: P, pose: Pose2D) {
        self.odometry
            .reset_position(gyro_angle, wheel_positions, pose);
        self.odometry_pose_buffer.clear();
        self.vision_updates.clear();
        self.pose_estimate = self.odometry.pose;
    }

    pub fn reset_pose(&mut self, pose: Pose2D) {
        self.odometry.reset_pose(pose);
        self.odometry_pose_buffer.clear();
        self.vision_updates.clear();
        self.pose_estimate = self.odometry.pose;
    }

    pub fn reset_translation(&mut self, translation: Vec2) {
        self.odometry.reset_translation(translation);

        let latest_vision_update = if self.vision_updates.is_empty() {
            None
        } else {
            let latest = self.vision_updates.last_key_value().unwrap().clone();
            Some((latest.0.clone(), latest.1.clone()))
        };
        self.odometry_pose_buffer.clear();
        self.vision_updates.clear();

        if let Some((time, update)) = latest_vision_update {
            let update = VisionUpdate::new(
                Pose2D::new(translation, update.vision.rotation),
                Pose2D::new(translation, update.odometry.rotation),
            );
            self.vision_updates.insert(time, update.clone());
            self.pose_estimate = update.compensate(self.odometry.pose);
        } else {
            self.pose_estimate = self.odometry.pose;
        }
    }

    pub fn reset_rotation(&mut self, rotation: Rotation2D) {
        self.odometry.reset_rotation(rotation);

        let latest_vision_update = if self.vision_updates.is_empty() {
            None
        } else {
            let latest = self.vision_updates.last_key_value().unwrap().clone();
            Some((latest.0.clone(), latest.1.clone()))
        };
        self.odometry_pose_buffer.clear();
        self.vision_updates.clear();

        if let Some((time, update)) = latest_vision_update {
            let update = VisionUpdate::new(
                Pose2D::new(update.vision.pos, rotation),
                Pose2D::new(update.odometry.pos, rotation),
            );
            self.vision_updates.insert(time, update.clone());
            self.pose_estimate = update.compensate(self.odometry.pose);
        } else {
            self.pose_estimate = self.odometry.pose;
        }
    }

    pub fn sample_at(&self, timestamp: Time) -> Option<Pose2D> {
        if self.odometry_pose_buffer.is_empty() {
            return None;
        }

        let oldest_odometry_timestamp = self.odometry_pose_buffer.get_buffer().first().unwrap().0;
        let newest_odometry_timestamp = self.odometry_pose_buffer.get_buffer().last().unwrap().0;
        let timestamp = timestamp.value.clamp(
            oldest_odometry_timestamp.value,
            newest_odometry_timestamp.value,
        );

        if self.vision_updates.is_empty()
            || timestamp < **self.vision_updates.first_key_value().unwrap().0
        {
            return self.odometry_pose_buffer.sample(timestamp.seconds());
        }

        let (_, vision_update) = self
            .vision_updates
            .range(..=OrderedFloat(timestamp))
            .next_back()
            .unwrap();

        let odometry_estimate = self.odometry_pose_buffer.sample(timestamp.seconds());

        if let Some(estimate) = odometry_estimate {
            Some(vision_update.compensate(estimate))
        } else {
            None
        }
    }

    pub fn add_vision_measurement(&mut self, timestamp: Time, pose: Pose2D) {
        let buffer = self.odometry_pose_buffer.get_buffer();
        // Differs from WPILib implementation, apparently there's a bug in that.
        if buffer.is_empty() || buffer.first().unwrap().0 > timestamp {
            return;
        }

        self.clean_up_vision_updates();

        let odometry_sample = self.odometry_pose_buffer.sample(timestamp);
        let Some(odometry_sample) = odometry_sample else {
            return;
        };

        let vision_sample = self.sample_at(timestamp);
        let Some(vision_sample) = vision_sample else {
            return;
        };

        let transform = vision_sample.to(&pose);
        let k_times_transform = self.vision_k
            * nalgebra::Vector3::new(
                transform.pos.x.value,
                transform.pos.y.value,
                transform.rotation.value.value,
            );

        let scaled_transform = Pose2D::new(
            Vec2::new(k_times_transform.x.meters(), k_times_transform.y.meters()),
            Rotation2D::new(k_times_transform.z.radians()),
        );

        let vision_update = VisionUpdate::new(
            vision_sample.transformed(&scaled_transform),
            odometry_sample,
        );
        self.vision_updates
            .insert(OrderedFloat(timestamp.value), vision_update.clone());

        self.vision_updates.retain(|&k, _| *k <= timestamp.value);

        self.pose_estimate = vision_update.compensate(self.odometry.pose);
    }

    pub fn add_vision_measurement_devs(
        &mut self,
        timestamp: Time,
        pose: Pose2D,
        vision_measurement_std_devs: [f64; 3],
    ) {
        self.set_vision_measurement_std_devs(vision_measurement_std_devs);
        self.add_vision_measurement(timestamp, pose);
    }

    pub fn update(&mut self, gyro_angle: Rotation2D, wheel_positions: P) -> Pose2D {
        self.update_with_time(super::timestamp(), gyro_angle, wheel_positions)
    }

    pub fn update_with_time(
        &mut self,
        time: Time,
        gyro_angle: Rotation2D,
        wheel_positions: P,
    ) -> Pose2D {
        let odometry_estimate = self.odometry.update(gyro_angle, wheel_positions);
        self.odometry_pose_buffer
            .add_sample(time, odometry_estimate);

        if self.vision_updates.is_empty() {
            self.pose_estimate = odometry_estimate;
        } else {
            let vision_update = self.vision_updates.last_key_value().unwrap().1;
            self.pose_estimate = vision_update.compensate(odometry_estimate);
        }

        self.pose_estimate
    }

    fn clean_up_vision_updates(&mut self) {
        if self.odometry_pose_buffer.get_buffer().is_empty() {
            return;
        }

        let oldest_odometry_timestamp = self.odometry_pose_buffer.get_buffer().first().unwrap().0;

        if self.vision_updates.is_empty()
            || oldest_odometry_timestamp.value < **self.vision_updates.first_key_value().unwrap().0
        {
            return;
        }

        if let Some((&newest_needed_key, _)) = self
            .vision_updates
            .range(..=OrderedFloat(oldest_odometry_timestamp.value))
            .next_back()
        {
            self.vision_updates.retain(|&k, _| k >= newest_needed_key);
        }
    }
}

#[derive(Deref, DerefMut)]
pub struct DifferentialDrivePoseEstimator(
    PoseEstimator<
        DifferentialDriveWheelSpeeds,
        DifferentialDriveWheelPositions,
        DifferentialDriveKinematics,
    >,
);

impl DifferentialDrivePoseEstimator {
    pub fn new(gyro_angle: Rotation2D, left: Length, right: Length, initial: Pose2D) -> Self {
        Self(PoseEstimator::new(
            DifferentialDriveOdometry::new(gyro_angle, left, right, initial).0,
            [0.02, 0.02, 0.01],
            [0.1, 0.1, 0.1],
        ))
    }

    pub fn new_stds(
        gyro_angle: Rotation2D,
        left: Length,
        right: Length,
        initial: Pose2D,
        state_std_devs: [f64; 3],
        vision_measurement_std_devs: [f64; 3],
    ) -> Self {
        Self(PoseEstimator::new(
            DifferentialDriveOdometry::new(gyro_angle, left, right, initial).0,
            state_std_devs,
            vision_measurement_std_devs,
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

    pub fn update_with_time(
        &mut self,
        time: Time,
        gyro_angle: Rotation2D,
        left: Length,
        right: Length,
    ) -> Pose2D {
        self.0.update_with_time(
            time,
            gyro_angle,
            DifferentialDriveWheelPositions::new(left, right),
        )
    }
}

#[derive(Deref, DerefMut)]
pub struct SwerveDrivePoseEstimator<const N: usize>(
    PoseEstimator<[SwerveModuleState; N], [SwerveModulePosition; N], SwerveDriveKinematics<N>>,
);

impl<const N: usize> SwerveDrivePoseEstimator<N> {
    pub fn new(
        kinematics: SwerveDriveKinematics<N>,
        gyro_angle: Rotation2D,
        module_positions: [SwerveModulePosition; N],
        initial_pose: Pose2D,
    ) -> Self {
        Self(PoseEstimator::new(
            SwerveDriveOdometry::new(kinematics, gyro_angle, module_positions, initial_pose).0,
            [0.1, 0.1, 0.1],
            [0.9, 0.9, 0.9],
        ))
    }

    pub fn new_stds(
        kinematics: SwerveDriveKinematics<N>,
        gyro_angle: Rotation2D,
        module_positions: [SwerveModulePosition; N],
        initial_pose: Pose2D,
        state_std_devs: [f64; 3],
        vision_measurement_std_devs: [f64; 3],
    ) -> Self {
        Self(PoseEstimator::new(
            SwerveDriveOdometry::new(kinematics, gyro_angle, module_positions, initial_pose).0,
            state_std_devs,
            vision_measurement_std_devs,
        ))
    }
}
