use std::f64::consts::PI;
use std::ops::{Div, Mul};

use derive_more::{Add, AddAssign, Neg, Sub, SubAssign};

use super::prelude::*;

/// Types that implement Kinematics can convert the [`ChassisSpeeds`] type into
/// their own wheel speeds, and convert their own wheel speeds back to chassis
/// speeds.
///
/// Kinematics is already implemented for swerve drives in
/// [`SwerveDriveKinematics`] and for differential (tank) drives in
/// [`DifferentialDriveKinematics`].
///
/// ## Type parameters
///
/// * S: Wheel speeds
/// * P: Wheel positions.
pub trait Kinematics<S, P> {
    fn to_chassis_speeds(&mut self, wheel_speeds: &S) -> ChassisSpeeds;
    fn to_wheel_speeds(&mut self, chassis_speeds: &ChassisSpeeds) -> S;
    fn to_twist2d(&mut self, start: &P, end: &P) -> Twist2D;
    fn interpolate(&mut self, start: &P, end: &P, t: f64) -> P;
}

/// Represents the speed of any robot, in either robot-relative or
/// field-relative coordiantes.
#[derive(Debug, Default, Clone, Copy, PartialEq, Add, AddAssign, Sub, SubAssign, Neg)]
pub struct ChassisSpeeds {
    /// Forward-backward movement relative to the robot.
    pub vx: Velocity,
    /// Left-right movement relative to the robot.
    pub vy: Velocity,
    /// Angular movement relative to forward on the robot.
    pub omega: AngularVelocity,
}

impl AutoLog for ChassisSpeeds {
    fn append_to(self, logger: &mut Logger, path: &str) {
        self.vx.append_to(logger, &format!("{path}/vx"));
        self.vy.append_to(logger, &format!("{path}/vy"));
        self.omega.append_to(logger, &format!("{path}/omega"));
    }
}

impl ChassisSpeeds {
    /// Create a new [`ChassisSpeeds`].
    pub fn new(vx: Velocity, vy: Velocity, omega: AngularVelocity) -> Self {
        Self { vx, vy, omega }
    }

    /// Convert these speeds to a [`Twist2D`], which represents movement over
    /// time.
    pub fn to_twist2d(&self, dt: Time) -> Twist2D {
        Twist2D::new(
            self.vx * dt,
            self.vy * dt,
            (self.omega * dt).value.radians(),
        )
    }

    /// Discretizes a continuous-time chassis speed.
    ///
    /// This function converts a continuous-time chassis speed into a
    /// discrete-time one such that when the discrete-time chassis speed is
    /// applied for one timestep, the robot moves as if the velocity
    /// components are independent (i.e., the robot moves v_x * dt along the
    /// x-axis, v_y * dt along the y-axis, and omega * dt around the
    /// z-axis).
    ///
    /// This is useful for compensating for translational skew when translating
    /// and rotating a holonomic (swerve or mecanum) drivetrain. However,
    /// scaling down the ChassisSpeeds after discretizing (e.g., when
    /// desaturating swerve module speeds) rotates the direction of net
    /// motion in the opposite direction of rotational velocity, introducing
    /// a different translational skew which is not accounted for by
    /// discretization.
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

    /// See [`Self::discretize`].
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

/// Represents the wheel positions of a differential (tank) drivetrain. Often,
/// this is used for the change in wheel positions instead of the actual wheel
/// positions.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct DifferentialDriveWheelPositions {
    left: Length,
    right: Length,
}

impl DifferentialDriveWheelPositions {
    pub fn new(left: Length, right: Length) -> Self {
        Self { left, right }
    }

    /// Interpolate between self (start) and end, by parameter t, whose bounds
    /// should be 0.0-1.0.
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

    /// Renormalizes the wheel speeds if either side is above the specified
    /// maximum.
    ///
    /// Sometimes, after inverse kinematics, the requested speed from one or
    /// more wheels may be above the max attainable speed for the driving
    /// motor on that wheel. To fix this issue, one can reduce all the wheel
    /// speeds to make sure that all requested module speeds are at-or-below
    /// the absolute threshold, while maintaining the ratio of speeds
    /// between wheels.
    pub fn desaturate(&mut self, attainable_max_speed: Velocity) {
        let real_max_speed =
            f64::max(self.left.abs().value, self.right.abs().value).meters_per_second();
        if real_max_speed > attainable_max_speed {
            self.left = self.left / real_max_speed * attainable_max_speed;
            self.right = self.right / real_max_speed * attainable_max_speed;
        }
    }
}

/// Kinematics implementation for the differential (tank) drive. See
/// documentation for [`Kinematics`] for more information.
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

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct MecanumDriveWheelPositions {
    pub front_left: Length,
    pub front_right: Length,
    pub rear_left: Length,
    pub rear_right: Length,
}

impl MecanumDriveWheelPositions {
    pub fn new(
        front_left: Length,
        front_right: Length,
        rear_left: Length,
        rear_right: Length,
    ) -> Self {
        Self {
            front_left,
            front_right,
            rear_left,
            rear_right,
        }
    }

    pub fn interpolate(self, end: Self, t: f64) -> Self {
        Self::new(
            self.front_left + t * (end.front_left - self.front_left),
            self.front_right + t * (end.front_right - self.front_right),
            self.rear_left + t * (end.rear_left - self.rear_left),
            self.rear_right + t * (end.rear_right - self.rear_right),
        )
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Add, AddAssign, Sub, SubAssign)]
pub struct MecanumDriveWheelSpeeds {
    pub front_left: Velocity,
    pub front_right: Velocity,
    pub rear_left: Velocity,
    pub rear_right: Velocity,
}

impl MecanumDriveWheelSpeeds {
    pub fn new(
        front_left: Velocity,
        front_right: Velocity,
        rear_left: Velocity,
        rear_right: Velocity,
    ) -> Self {
        Self {
            front_left,
            front_right,
            rear_left,
            rear_right,
        }
    }

    pub fn desaturate(&mut self, max_speed: Velocity) {
        let mut wheel_speeds = [
            self.front_left,
            self.front_right,
            self.rear_left,
            self.rear_right,
        ];
        let real_max_speed = wheel_speeds
            .iter()
            .max_by(|a, b| a.abs().partial_cmp(&b.abs()).unwrap())
            .unwrap()
            .abs();

        if real_max_speed > max_speed {
            for speed in &mut wheel_speeds {
                *speed = *speed / real_max_speed * max_speed;
            }
            self.front_left = wheel_speeds[0];
            self.front_right = wheel_speeds[1];
            self.rear_left = wheel_speeds[2];
            self.rear_right = wheel_speeds[3];
        }
    }
}

#[derive(Debug, Clone, Copy)]
pub struct MecanumDriveKinematics {
    ik: nalgebra::SMatrix<f64, 4, 3>,
    fk: nalgebra::SVD<f64, nalgebra::Const<4>, nalgebra::Const<3>>,
}

impl MecanumDriveKinematics {
    pub fn new(front_left: Vec2, front_right: Vec2, rear_left: Vec2, rear_right: Vec2) -> Self {
        let mut out = Self {
            ik: nalgebra::SMatrix::default(),
            fk: nalgebra::SVD::new(nalgebra::SMatrix::default(), true, true),
        };
        out.set_inverse_kinematics(front_left, front_right, rear_left, rear_right);
        out.fk = out.ik.svd(true, true);
        out
    }

    pub fn to_twist2d_deltas(&self, deltas: MecanumDriveWheelPositions) -> Twist2D {
        let wheel_deltas = nalgebra::vector![
            deltas.front_left.value,
            deltas.front_right.value,
            deltas.rear_left.value,
            deltas.rear_right.value,
        ];
        let twist = self.fk.solve(&wheel_deltas, 1e-12).unwrap();
        Twist2D::new(twist[0].meters(), twist[1].meters(), twist[2].radians())
    }

    fn set_inverse_kinematics(&mut self, fl: Vec2, fr: Vec2, rl: Vec2, rr: Vec2) {
        self.ik = nalgebra::matrix![
            1.0, -1.0, (-(fl.x + fl.y)).value;
            1.0, 1.0, (fr.x - fr.y).value;
            1.0, 1.0, (rl.x - rl.y).value;
            1.0, -1.0, (-(rr.x + rr.y)).value;
        ];
    }
}

impl Kinematics<MecanumDriveWheelSpeeds, MecanumDriveWheelPositions> for MecanumDriveKinematics {
    fn to_chassis_speeds(&mut self, speeds: &MecanumDriveWheelSpeeds) -> ChassisSpeeds {
        let wheel_speeds_vector = nalgebra::vector![
            speeds.front_left.value,
            speeds.front_right.value,
            speeds.rear_left.value,
            speeds.rear_right.value
        ];
        let speeds = self.fk.solve(&wheel_speeds_vector, 1e-12).unwrap();
        ChassisSpeeds::new(
            speeds[0].meters_per_second(),
            speeds[1].meters_per_second(),
            speeds[2].radians_per_second(),
        )
    }

    fn to_wheel_speeds(&mut self, speeds: &ChassisSpeeds) -> MecanumDriveWheelSpeeds {
        let chassis_speeds_vector =
            nalgebra::vector![speeds.vx.value, speeds.vy.value, speeds.omega.value];
        let wheels = self.ik * chassis_speeds_vector;
        MecanumDriveWheelSpeeds::new(
            wheels[0].meters_per_second(),
            wheels[1].meters_per_second(),
            wheels[2].meters_per_second(),
            wheels[3].meters_per_second(),
        )
    }

    fn to_twist2d(
        &mut self,
        start: &MecanumDriveWheelPositions,
        end: &MecanumDriveWheelPositions,
    ) -> Twist2D {
        let wheel_deltas = nalgebra::vector![
            end.front_left.value - start.front_left.value,
            end.front_right.value - start.front_right.value,
            end.rear_left.value - start.rear_left.value,
            end.rear_right.value - start.rear_right.value,
        ];
        let twist = self.fk.solve(&wheel_deltas, 1e-12).unwrap();
        Twist2D::new(twist[0].meters(), twist[1].meters(), twist[2].radians())
    }

    fn interpolate(
        &mut self,
        start: &MecanumDriveWheelPositions,
        end: &MecanumDriveWheelPositions,
        t: f64,
    ) -> MecanumDriveWheelPositions {
        start.interpolate(*end, t)
    }
}

/// Represents the position of a swerve module. Often these are used to
/// represent change in position instead of position itself.
#[derive(Debug, Default, Clone, Copy, PartialEq)]
pub struct SwerveModulePosition {
    pub distance: Length,
    pub angle: Rotation2D,
}

impl SwerveModulePosition {
    pub fn new(distance: Length, angle: Rotation2D) -> Self {
        Self { distance, angle }
    }

    /// Interpolate between self (start) and end, by parameter t, whose bounds
    /// should be 0.0-1.0.
    pub fn interpolate(&self, end: SwerveModulePosition, t: f64) -> Self {
        Self::new(
            self.distance + t * (end.distance - self.distance),
            self.angle + Rotation2D::new(t * (end.angle - self.angle).value),
        )
    }
}

/// Represents the velocity and rotation of the wheel, this is used in place of
/// a speeds type because knowing the angular velocity of the swerve module
/// rotation would be pretty useless.
#[derive(Debug, Default, Clone, Copy, PartialEq)]
pub struct SwerveModuleState {
    pub speed: Velocity,
    pub angle: Rotation2D,
}

impl AutoLog for SwerveModuleState {
    fn append_to(self, logger: &mut Logger, path: &str) {
        self.speed.append_to(logger, &format!("{path}/speed"));
        self.angle.value.append_to(logger, &format!("{path}/angle"));
    }
}

impl SwerveModuleState {
    pub fn new(speed: Velocity, angle: Rotation2D) -> Self {
        Self { speed, angle }
    }

    /// Minimize the change in the heading this swerve module state would
    /// require by potentially reversing the direction the wheel spins. If this
    /// is used with the PIDController class's continuous input
    /// functionality, the furthest a wheel will ever rotate is 90 degrees.
    pub fn optimize(&mut self, current_angle: Rotation2D) {
        let desired = self.angle.value.get::<radian>();
        let delta = (desired - current_angle.value.get::<radian>() + PI).rem_euclid(2.0 * PI) - PI;

        if delta.abs() > PI / 2.0 {
            self.speed = -self.speed;
            self.angle = Rotation2D::new((desired + PI).radians());
        }
    }

    pub fn cosine_scale(&mut self, current_angle: Rotation2D) {
        self.speed *= (self.angle - current_angle).cos()
    }
}

/// Kinematics for swerve drivetrains. This supports any number of
/// modules, specified in the type parameter `N`, although this value is
/// typically 4.
///
/// See documentation for [`Kinematics`] for more information.
///
/// TODO: This class needs to be rewritten to conform better with the WPILib
/// implementation.
#[derive(Debug, Clone)]
pub struct SwerveDriveKinematics<const N: usize> {
    modules: [Vec2; N],
}

impl<const N: usize> SwerveDriveKinematics<N> {
    /// Create a new kinematics object with the positions of each module
    /// relative to the center of the drivetrain.
    pub fn new(modules: [Vec2; N]) -> Self {
        Self { modules }
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
                    angle: Rotation2D::new(0.0.radians()),
                };
            }
            return states;
        }

        for i in 0..N {
            let rx = self.modules[i].x - rotation_center.x;
            let ry = self.modules[i].y - rotation_center.y;

            let vx = speeds.vx - speeds.omega * ry;
            let vy = speeds.vy + speeds.omega * rx;

            let speed = vx.hypot(vy);
            let angle = if speed > 1e-6.meters_per_second() {
                Rotation2D::new(vy.atan2(vx))
            } else {
                Rotation2D::new(0.0.radians())
            };

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
