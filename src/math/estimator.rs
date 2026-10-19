use std::collections::HashMap;

use super::prelude::*;
use crate::prelude::*;

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
    vision_updates: HashMap<Time, VisionUpdate>,
    pose_estimate: Pose2D,
}

impl<S, P, K: Kinematics<S, P>> PoseEstimator<S, P, K> {
    pub fn new(
        odometry: Odometry<S, P, K>,
        state_std_devs: [f64; 3],
        vision_measurement_std_devs: [f64; 3],
    ) -> Self {
        let q = nalgebra::Matrix3::zeros();
        for i in 0..3 {
            q[i] = state_std_devs[i].powi(2);
        }

        let mut out = Self {
            odometry,
            q: [0.0; 3],
            vision_k: nalgebra::Matrix3::zeros(),
            odometry_pose_buffer: TimeInterpolatableBuffer::new(),
            vision_updates: HashMap::new(),
            pose_estimate: Pose2D::default(),
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
                    self.q[row] / (self.q[row] + (self.q[row] + r[row]).sqrt());
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

        let last_vision_update = if self.vision_updates.is_empty() {
            None
        } else {
            Some(self.vision_updates.iter().last())
        };
    }
}
