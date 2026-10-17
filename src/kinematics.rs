use std::ops::{Div, Mul};

use derive_more::{Add, AddAssign, Neg, Sub, SubAssign};

use crate::prelude::*;

#[derive(Debug, Default, Clone, Copy, PartialEq, Add, AddAssign, Sub, SubAssign, Neg)]
pub struct ChassisSpeeds {
    pub vx: Velocity,
    pub vy: Velocity,
    pub omega: AngularVelocity,
}

impl ChassisSpeeds {
    pub fn new(vx: Velocity, vy: Velocity, omega: AngularVelocity) -> Self {
        Self { vx, vy, omega }
    }

    pub fn to_twist2d(&self, dt: Time) -> Twist2D {
        Twist2D::new(
            self.vx * dt,
            self.vy * dt,
            (self.omega * dt).value.radians(),
        )
    }

    pub fn discretize(vx: Velocity, vy: Velocity, omega: AngularVelocity, dt: Time) -> Self {
        let desired_offset = Pose2D::new(
            Vec2::new(vx * dt, vy * dt),
            Rotation2D::new((omega * dt).value.radians()),
        );
        let twist = Pose2D::default().log(&desired_offset);
        Self::new(
            twist.dx / dt,
            twist.dy / dt,
            (twist.dtheta / dt).value.radians_per_second(),
        )
    }

    pub fn discretize_speeds(speeds: Self, dt: Time) -> Self {
        Self::discretize(speeds.vx, speeds.vy, speeds.omega, dt)
    }

    pub fn from_field_relative(
        vx: Velocity,
        vy: Velocity,
        omega: AngularVelocity,
        robot_angle: Rotation2D,
    ) -> Self {
        let rotated = Vec2::new(vx.value.meters(), vy.value.meters()).rotated(&-robot_angle);
        Self::new(
            rotated.x.value.meters_per_second(),
            rotated.y.value.meters_per_second(),
            omega,
        )
    }

    pub fn from_field_relative_speeds(speeds: Self, robot_angle: Rotation2D) -> Self {
        Self::from_field_relative(speeds.vx, speeds.vy, speeds.omega, robot_angle)
    }

    pub fn from_robot_relative(
        vx: Velocity,
        vy: Velocity,
        omega: AngularVelocity,
        robot_angle: Rotation2D,
    ) -> Self {
        let rotated = Vec2::new(vx.value.meters(), vy.value.meters()).rotated(&robot_angle);
        Self::new(
            rotated.x.value.meters_per_second(),
            rotated.y.value.meters_per_second(),
            omega,
        )
    }

    pub fn from_robot_relative_speeds(speeds: Self, robot_angle: Rotation2D) -> Self {
        Self::from_robot_relative(speeds.vx, speeds.vy, speeds.omega, robot_angle)
    }
}

impl Mul<f64> for ChassisSpeeds {
    type Output = Self;

    fn mul(self, rhs: f64) -> Self::Output {
        Self::new(self.vx * rhs, self.vy * rhs, self.omega * rhs)
    }
}

impl Div<f64> for ChassisSpeeds {
    type Output = Self;

    fn div(self, rhs: f64) -> Self::Output {
        Self::new(self.vx / rhs, self.vy / rhs, self.omega / rhs)
    }
}

#[derive(Debug, Default, Clone, Copy, PartialEq, Add, AddAssign, Sub, SubAssign, Neg)]
pub struct DifferentialDriveWheelSpeeds {
    pub left: Velocity,
    pub right: Velocity,
}

impl DifferentialDriveWheelSpeeds {
    pub fn new(left: Velocity, right: Velocity) -> Self {
        Self { left, right }
    }

    pub fn desaturate(&mut self, attainable_max_speed: Velocity) {
        let real_max_speed =
            f64::max(self.left.abs().value, self.right.abs().value).meters_per_second();
        if real_max_speed > attainable_max_speed {
            self.left = self.left / real_max_speed * attainable_max_speed;
            self.right = self.right / real_max_speed * attainable_max_speed;
        }
    }
}

pub struct DifferentialDriveKinematics {
    width: Length,
}

impl DifferentialDriveKinematics {
    pub fn new(track_width: Length) -> Self {
        Self { width: track_width }
    }

    pub fn to_chassis_speeds(&self, speeds: DifferentialDriveWheelSpeeds) -> ChassisSpeeds {
        ChassisSpeeds::new(
            (speeds.left + speeds.right) / 2.0,
            0.0.meters_per_second(),
            ((speeds.right - speeds.left) / self.width)
                .value
                .radians_per_second(),
        )
    }

    pub fn to_wheel_speeds(&self, speeds: ChassisSpeeds) -> DifferentialDriveWheelSpeeds {
        DifferentialDriveWheelSpeeds::new(
            speeds.vx - self.width / 2.0 * speeds.omega / 1.0.radians(),
            speeds.vx + self.width / 2.0 * speeds.omega / 1.0.radians(),
        )
    }
}
