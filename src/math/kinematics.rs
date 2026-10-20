use std::f64::consts::PI;
use std::ops::{Div, Mul};

use derive_more::{Add, AddAssign, Neg, Sub, SubAssign};

use super::prelude::*;

pub trait Kinematics<S, P> {
    fn to_chassis_speeds(&mut self, wheel_speeds: &S) -> ChassisSpeeds;
    fn to_wheel_speeds(&mut self, chassis_speeds: &ChassisSpeeds) -> S;
    fn to_twist2d(&mut self, start: &P, end: &P) -> Twist2D;
    fn interpolate(&mut self, start: &P, end: &P, t: f64) -> P;
}

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

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct DifferentialDriveWheelPositions {
    left: Length,
    right: Length,
}

impl DifferentialDriveWheelPositions {
    pub fn new(left: Length, right: Length) -> Self {
        Self { left, right }
    }

    pub fn interpolate(&self, end: Self, t: f64) -> Self {
        Self::new(
            self.left + t * (end.left - self.left),
            self.right + t * (end.right - self.right),
        )
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

#[derive(Debug, Clone, Copy)]
pub struct DifferentialDriveKinematics {
    width: Length,
}

impl DifferentialDriveKinematics {
    pub fn new(track_width: Length) -> Self {
        Self { width: track_width }
    }

    pub fn distances_to_twist2d(&self, left: Length, right: Length) -> Twist2D {
        Twist2D::new(
            (left + right) / 2.0,
            0.0.meters(),
            ((right - left) / self.width).value.radians(),
        )
    }
}

impl Kinematics<DifferentialDriveWheelSpeeds, DifferentialDriveWheelPositions>
    for DifferentialDriveKinematics
{
    fn to_chassis_speeds(&mut self, speeds: &DifferentialDriveWheelSpeeds) -> ChassisSpeeds {
        ChassisSpeeds::new(
            (speeds.left + speeds.right) / 2.0,
            0.0.meters_per_second(),
            ((speeds.right - speeds.left) / self.width)
                .value
                .radians_per_second(),
        )
    }

    fn to_wheel_speeds(&mut self, speeds: &ChassisSpeeds) -> DifferentialDriveWheelSpeeds {
        DifferentialDriveWheelSpeeds::new(
            speeds.vx - self.width / 2.0 * speeds.omega / 1.0.radians(),
            speeds.vx + self.width / 2.0 * speeds.omega / 1.0.radians(),
        )
    }

    fn to_twist2d(
        &mut self,
        start: &DifferentialDriveWheelPositions,
        end: &DifferentialDriveWheelPositions,
    ) -> Twist2D {
        self.distances_to_twist2d(end.left - start.left, end.right - start.right)
    }

    fn interpolate(
        &mut self,
        start: &DifferentialDriveWheelPositions,
        end: &DifferentialDriveWheelPositions,
        t: f64,
    ) -> DifferentialDriveWheelPositions {
        start.interpolate(*end, t)
    }
}

#[derive(Debug, Default, Clone, Copy, PartialEq)]
pub struct SwerveModulePosition {
    pub distance: Length,
    pub angle: Rotation2D,
}

impl SwerveModulePosition {
    pub fn new(distance: Length, angle: Rotation2D) -> Self {
        Self { distance, angle }
    }

    pub fn interpolate(&self, end: SwerveModulePosition, t: f64) -> Self {
        Self::new(
            self.distance + t * (end.distance - self.distance),
            self.angle + Rotation2D::new(t * (end.angle - self.angle).value),
        )
    }
}

#[derive(Debug, Default, Clone, Copy, PartialEq)]
pub struct SwerveModuleState {
    pub speed: Velocity,
    pub angle: Rotation2D,
}

impl SwerveModuleState {
    pub fn optimize(desired_state: Self, current_angle: Rotation2D) -> Self {
        let desired = desired_state.angle.value.get::<radian>();
        let delta = (desired - current_angle.value.get::<radian>() + PI).rem_euclid(2.0 * PI) - PI;

        if delta.abs() > PI / 2.0 {
            Self {
                speed: -desired_state.speed,
                angle: Rotation2D::new((desired + PI).radians()),
            }
        } else {
            desired_state
        }
    }
}

#[derive(Debug, Clone)]
pub struct SwerveDriveKinematics<const N: usize> {
    modules: [Vec2; N],
    prev_headings: [Rotation2D; N],
}

impl<const N: usize> SwerveDriveKinematics<N> {
    pub fn new(modules: [Vec2; N]) -> Self {
        Self {
            modules,
            prev_headings: [Rotation2D::default(); N],
        }
    }

    pub fn to_swerve_module_states(
        &mut self,
        speeds: ChassisSpeeds,
        rotation_center: Vec2,
    ) -> [SwerveModuleState; N] {
        let mut states = [SwerveModuleState::default(); N];

        if speeds.vx.abs() < 1e-9.meters_per_second()
            && speeds.vy.abs() < 1e-9.meters_per_second()
            && speeds.omega.abs() < 1e-9.radians_per_second()
        {
            for i in 0..N {
                states[i] = SwerveModuleState {
                    speed: 0.0.meters_per_second(),
                    angle: self.prev_headings[i],
                };
            }
            return states;
        }

        for i in 0..N {
            let rx = self.modules[i].x - rotation_center.x;
            let ry = self.modules[i].y - rotation_center.y;

            // v_module = v_chassis + omega x r
            let vx = speeds.vx - speeds.omega * ry;
            let vy = speeds.vy + speeds.omega * rx;

            let speed = vx.hypot(vy);
            let angle = if speed > 1e-6.meters_per_second() {
                Rotation2D::new(vy.atan2(vx))
            } else {
                self.prev_headings[i]
            };

            self.prev_headings[i] = angle;
            states[i] = SwerveModuleState { speed, angle };
        }

        states
    }

    pub fn deltas_to_twist2d(&self, deltas: [SwerveModulePosition; N]) -> Twist2D {
        let n = N as f64;
        let mut sum_rx = 0.0;
        let mut sum_ry = 0.0;
        let mut sum_r2 = 0.0;

        let mut sum_dx = 0.0;
        let mut sum_dy = 0.0;
        let mut sum_dtheta_moment = 0.0;

        for i in 0..N {
            let rx = self.modules[i].x.value;
            let ry = self.modules[i].y.value;
            let dx = deltas[i].distance.value * deltas[i].angle.cos();
            let dy = deltas[i].distance.value * deltas[i].angle.sin();

            sum_rx += rx;
            sum_ry += ry;
            sum_r2 += rx * rx + ry * ry;

            sum_dx += dx;
            sum_dy += dy;
            sum_dtheta_moment += rx * dy - ry * dx;
        }

        let denom = n * sum_r2 - (sum_rx * sum_rx + sum_ry * sum_ry);
        let dtheta = if denom.abs() > 1e-9 {
            (n * sum_dtheta_moment + sum_ry * sum_dx - sum_rx * sum_dy) / denom
        } else {
            0.0
        }
        .radians();

        let dx = ((sum_dx + dtheta.value * sum_ry) / n).meters();
        let dy = ((sum_dy - dtheta.value * sum_rx) / n).meters();

        Twist2D { dx, dy, dtheta }
    }

    pub fn desaturate_wheel_speeds(states: &mut [SwerveModuleState; N], max_speed: Velocity) {
        let real_max = states
            .iter()
            .map(|s| s.speed.abs().value)
            .fold(0.0_f64, f64::max);

        if real_max > max_speed.value {
            let scale = max_speed.value / real_max;
            for state in states.iter_mut() {
                state.speed *= scale;
            }
        }
    }
}

impl<const N: usize> Kinematics<[SwerveModuleState; N], [SwerveModulePosition; N]>
    for SwerveDriveKinematics<N>
{
    fn to_chassis_speeds(&mut self, module_states: &[SwerveModuleState; N]) -> ChassisSpeeds {
        let n = N as f64;
        let mut sum_rx = 0.0;
        let mut sum_ry = 0.0;
        let mut sum_r2 = 0.0;

        let mut sum_vx = 0.0;
        let mut sum_vy = 0.0;
        let mut sum_tau = 0.0;

        for i in 0..N {
            let rx = self.modules[i].x.value;
            let ry = self.modules[i].y.value;
            let vx = (module_states[i].speed * module_states[i].angle.cos()).value;
            let vy = (module_states[i].speed * module_states[i].angle.sin()).value;

            sum_rx += rx;
            sum_ry += ry;
            sum_r2 += rx * rx + ry * ry;

            sum_vx += vx;
            sum_vy += vy;
            sum_tau += rx * vy - ry * vx;
        }

        let denom = n * sum_r2 - (sum_rx * sum_rx + sum_ry * sum_ry);
        let omega = if denom.abs() > 1e-9 {
            (n * sum_tau + sum_ry * sum_vx - sum_rx * sum_vy) / denom
        } else {
            0.0
        }
        .radians_per_second();

        let vx = ((sum_vx + omega.value * sum_ry) / n).meters_per_second();
        let vy = ((sum_vy - omega.value * sum_rx) / n).meters_per_second();

        ChassisSpeeds { vx, vy, omega }
    }

    fn to_wheel_speeds(&mut self, chassis_speeds: &ChassisSpeeds) -> [SwerveModuleState; N] {
        self.to_swerve_module_states(*chassis_speeds, Vec2::default())
    }

    fn to_twist2d(
        &mut self,
        start: &[SwerveModulePosition; N],
        end: &[SwerveModulePosition; N],
    ) -> Twist2D {
        let mut result = [SwerveModulePosition::default(); N];
        for i in 0..N {
            result[i] =
                SwerveModulePosition::new(end[i].distance - start[i].distance, end[i].angle);
        }
        self.deltas_to_twist2d(result)
    }

    fn interpolate(
        &mut self,
        start: &[SwerveModulePosition; N],
        end: &[SwerveModulePosition; N],
        t: f64,
    ) -> [SwerveModulePosition; N] {
        let mut result = [SwerveModulePosition::default(); N];
        for i in 0..N {
            result[i] = start[i].interpolate(end[i], t)
        }
        result
    }
}
