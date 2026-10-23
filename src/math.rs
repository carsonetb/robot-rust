use std::ops::{Add, Div, Mul};

use std::sync::LazyLock;
use std::time::Instant;

use derive_more::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Neg, Sub, SubAssign};
use uom::typenum::P2;

use crate::prelude::*;

pub mod control;
pub mod estimator;
pub mod interpolation;
pub mod kinematics;
pub mod odometry;
pub mod plant;
pub mod prelude;
pub mod system;
pub mod trajectory;

pub static START_TIME: LazyLock<Instant> = LazyLock::new(Instant::now);

pub fn timestamp() -> Time {
    Instant::now()
        .duration_since(*START_TIME)
        .as_secs_f64()
        .seconds()
}

/// A rotation in a 2D coordinate frame represented by a point on the unit
/// circle (cosine and sine).
#[derive(
    Default,
    Debug,
    Clone,
    Copy,
    PartialEq,
    Add,
    AddAssign,
    Sub,
    SubAssign,
    Mul,
    MulAssign,
    Div,
    DivAssign,
    Neg,
)]
pub struct Rotation2D {
    pub value: Angle,
}

impl Rotation2D {
    pub fn new(value: Angle) -> Self {
        Self { value }
    }

    pub fn to(x: f64, y: f64) -> Self {
        if x.abs() <= 1e-6 && y.abs() <= 1e-6 {
            Self::new(0.0.radians())
        } else {
            Self::new(f64::atan2(y, x).radians())
        }
    }

    pub fn rotated(&self, other: &Self) -> Self {
        let (cos, sin) = (self.cos(), self.sin());
        let (ocos, osin) = (other.cos(), other.sin());
        Self::to(cos * ocos - sin * osin, sin * ocos + cos * osin)
    }

    /// Current rotation relative to the given rotation.
    pub fn relative(&self, other: &Self) -> Self {
        self.rotated(&-*other) // LOL
    }

    pub fn sin(&self) -> f64 {
        self.value.get::<radian>().sin()
    }

    pub fn cos(&self) -> f64 {
        self.value.get::<radian>().cos()
    }

    pub fn tan(&self) -> f64 {
        self.value.get::<radian>().tan()
    }
}

/// Represents a translation in 2D space.
#[derive(
    Default,
    Debug,
    Clone,
    Copy,
    PartialEq,
    Add,
    AddAssign,
    Sub,
    SubAssign,
    Mul,
    MulAssign,
    Div,
    DivAssign,
    Neg,
)]
pub struct Vec2 {
    pub x: Length,
    pub y: Length,
}

impl Vec2 {
    pub fn new(x: Length, y: Length) -> Self {
        Self { x, y }
    }

    pub fn polar(distance: Length, angle: Rotation2D) -> Self {
        Self::new(distance * angle.cos(), distance * angle.sin())
    }

    pub fn distance_to(&self, other: &Vec2) -> Length {
        (other.x - self.x).hypot(other.y - self.y)
    }

    pub fn distance_to_squared(&self, other: &Vec2) -> f64 {
        (other.x - self.x).get::<meter>().powi(2) + (other.y - self.y).get::<meter>().powi(2)
    }

    pub fn length(&self) -> Length {
        self.x.hypot(self.y)
    }

    pub fn length_squared(&self) -> f64 {
        self.x.get::<meter>().powi(2) + self.y.get::<meter>().powi(2)
    }

    pub fn rotated(&self, by: &Rotation2D) -> Self {
        let (cos, sin) = (by.cos(), by.sin());
        Self::new(self.x * cos - self.y * sin, self.x * sin + self.y * cos)
    }

    pub fn rotated_around(&self, other: &Vec2, by: &Rotation2D) -> Self {
        let (cos, sin) = (by.cos(), by.sin());
        Self::new(
            (self.x - other.x) * cos - (self.y - other.y) * sin + other.x,
            (self.x - other.x) * sin + (self.y - other.y) * cos + other.y,
        )
    }

    pub fn translated(&self, other: &Vec2) -> Self {
        Self::new(self.x + other.x, self.y + other.y)
    }

    pub fn dot(&self, other: &Vec2) -> Area {
        self.x * other.x + self.y * other.y
    }

    pub fn cross(&self, other: &Vec2) -> Area {
        self.x * other.y - self.y * other.x
    }

    pub fn angle(&self) -> Rotation2D {
        Rotation2D::to(self.x.value, self.y.value)
    }
}

#[derive(Debug, Default, Clone, Copy, PartialEq)]
pub struct Pose2D {
    pub pos: Vec2,
    pub rotation: Rotation2D,
}

impl Pose2D {
    pub fn new(pos: Vec2, rotation: Rotation2D) -> Self {
        Self { pos, rotation }
    }

    pub fn rotated(&self, other: &Rotation2D) -> Self {
        Self::new(self.pos.rotated(other), self.rotation.rotated(other))
    }

    pub fn transformed(&self, other: &Self) -> Self {
        Self::new(
            self.pos.translated(&other.pos.rotated(&self.rotation)),
            self.rotation.rotated(&other.rotation),
        )
    }

    pub fn to(&self, other: &Self) -> Self {
        Self::new(
            (other.pos - self.pos).rotated(&-self.rotation),
            other.rotation.relative(&self.rotation),
        )
    }

    pub fn rotate_around(&self, point: Vec2, rotation: Rotation2D) -> Self {
        Self::new(
            self.pos.rotated_around(&point, &rotation),
            self.rotation.rotated(&rotation),
        )
    }

    pub fn exp(&self, twist: &Twist2D) -> Self {
        let dx = twist.dx.get::<meter>();
        let dy = twist.dy.get::<meter>();
        let dtheta = twist.dtheta.get::<radian>();

        let sin_theta = dtheta.sin();
        let cos_theta = dtheta.cos();

        let (s, c) = if dtheta.abs() < 1e-9 {
            (1.0 - 1.0 / 6.0 * dtheta * dtheta, 0.5 * dtheta)
        } else {
            (sin_theta / dtheta, (1.0 - cos_theta) / dtheta)
        };

        let offset = Pose2D::new(
            Vec2::new((dx * s - dy * c).meters(), (dx * c + dy * s).meters()),
            Rotation2D::to(cos_theta, sin_theta),
        );
        self.transformed(&offset)
    }

    pub fn log(&self, end: &Pose2D) -> Twist2D {
        let transform = self.to(end);
        let dtheta = transform.rotation.value.get::<radian>();
        let half_dtheta = dtheta / 2.0;

        let cos_m1 = transform.rotation.cos() - 1.0;

        let htbtohdt = if cos_m1.abs() < 1e-9 {
            1.0 - 1.0 / 12.0 * dtheta * dtheta
        } else {
            -(half_dtheta * transform.rotation.sin()) / cos_m1
        };

        let translation = transform
            .pos
            .rotated(&Rotation2D::to(htbtohdt, -half_dtheta))
            * f64::hypot(htbtohdt, half_dtheta);

        Twist2D::new(translation.x, translation.y, dtheta.radians())
    }

    pub fn lerp(&self, other: Self, t: f64) -> Self {
        let t = t.clamp(0.0, 1.0);
        let twist = self.log(&other);
        self.exp(&(twist * t))
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Mul, MulAssign)]
pub struct Twist2D {
    pub dx: Length,
    pub dy: Length,
    pub dtheta: Angle,
}

impl Twist2D {
    pub fn new(dx: Length, dy: Length, dtheta: Angle) -> Self {
        Self { dx, dy, dtheta }
    }
}

pub type Quaternion = glam::DQuat;

#[derive(
    Debug,
    Clone,
    Copy,
    PartialEq,
    Add,
    AddAssign,
    Sub,
    SubAssign,
    Mul,
    MulAssign,
    Div,
    DivAssign,
    Neg,
)]
pub struct Rotation3D {
    pub quat: Quaternion,
}

impl Rotation3D {
    pub fn new(roll: Angle, pitch: Angle, yaw: Angle) -> Self {
        let cr = (roll * 0.5).value.cos();
        let sr = (roll * 0.5).value.sin();

        let cp = (pitch * 0.5).value.cos();
        let sp = (pitch * 0.5).value.sin();

        let cy = (yaw * 0.5).value.cos();
        let sy = (yaw * 0.5).value.sin();

        let quat = Quaternion::from_xyzw(
            cr * cp * cy + sr * sp * sy,
            sr * cp * cy - cr * sp * sy,
            cr * sp * cy + sr * cp * sy,
            cr * cp * sy - sr * sp * cy,
        );

        Self { quat }
    }

    pub fn from_quaternion(quat: Quaternion) -> Self {
        Self { quat }
    }

    pub fn from_rotation2d(rotation: Rotation2D) -> Self {
        Self::new(0.0.radians(), 0.0.radians(), rotation.value)
    }

    pub fn rotate_by(&self, other: Self) -> Self {
        Self::from_quaternion(other.quat * self.quat)
    }

    pub fn relative_to(&self, other: Self) -> Self {
        Self::from_quaternion(other.quat.inverse() * self.quat)
    }

    pub fn x(&self) -> Angle {
        self.quat.to_euler(glam::EulerRot::XYZ).0.radians()
    }

    pub fn y(&self) -> Angle {
        self.quat.to_euler(glam::EulerRot::XYZ).1.radians()
    }

    pub fn z(&self) -> Angle {
        self.quat.to_euler(glam::EulerRot::XYZ).2.radians()
    }

    pub fn to_rotation2d(&self) -> Rotation2D {
        Rotation2D::new(self.z())
    }

    pub(crate) fn to_glam_vector(&self) -> glam::DVec3 {
        let (axis, angle) = self.quat.to_axis_angle();
        axis * angle
    }
}

#[derive(
    Default,
    Debug,
    Clone,
    Copy,
    PartialEq,
    Add,
    AddAssign,
    Sub,
    SubAssign,
    MulAssign,
    DivAssign,
    Neg,
)]
pub struct Vec3 {
    pub x: Length,
    pub y: Length,
    pub z: Length,
}

impl Vec3 {
    pub fn new(x: Length, y: Length, z: Length) -> Self {
        Self { x, y, z }
    }

    pub fn from_angle_distance(angle: Rotation3D, distance: Length) -> Self {
        Self::new(distance, 0.0.meters(), 0.0.meters()).rotate_by(angle)
    }

    pub fn distance(&self, other: Self) -> Length {
        ((other.x - self.x).powi(P2::new())
            + (other.y - self.y).powi(P2::new())
            + (other.z - self.z).powi(P2::new()))
        .sqrt()
    }

    pub fn length(&self) -> Length {
        (self.x * self.x + self.y * self.y + self.z * self.z).sqrt()
    }

    pub fn length_squared(&self) -> LengthSquared {
        self.x * self.x + self.y * self.y + self.z * self.z
    }

    pub fn rotate_by(&self, other: Rotation3D) -> Self {
        let p = Quaternion::from_xyzw(0.0, self.x.value, self.y.value, self.z.value);
        let qprime = other.quat * p * other.quat.inverse();
        let vec = qprime.to_euler(glam::EulerRot::XYZ);
        Self::new(vec.0.meters(), vec.1.meters(), vec.2.meters())
    }

    pub fn rotate_around(&self, other: Self, rot: Rotation3D) -> Self {
        (*self - other).rotate_by(rot) + other
    }

    pub fn dot(&self, other: Self) -> LengthSquared {
        self.x * other.x + self.y * other.y + self.z * other.z
    }

    pub fn to_vec2(&self) -> Vec2 {
        Vec2::new(self.x, self.y)
    }
}

impl Mul<f64> for Vec3 {
    type Output = Self;

    fn mul(self, rhs: f64) -> Self::Output {
        Self::new(self.x * rhs, self.y * rhs, self.z * rhs)
    }
}

impl Div<f64> for Vec3 {
    type Output = Self;

    fn div(self, rhs: f64) -> Self::Output {
        Self::new(self.x / rhs, self.y / rhs, self.z / rhs)
    }
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Pose3D {
    pub pos: Vec3,
    pub rot: Rotation3D,
}

impl Pose3D {
    pub fn new(translation: Vec3, rotation: Rotation3D) -> Self {
        Self {
            pos: translation,
            rot: rotation,
        }
    }

    pub fn rotate_by(&self, other: Rotation3D) -> Self {
        Self::new(self.pos.rotate_by(other), self.rot.rotate_by(other))
    }

    pub fn transform_by(&self, other: Self) -> Self {
        Self::new(
            self.pos + other.pos.rotate_by(self.rot),
            other.rot.rotate_by(self.rot),
        )
    }

    pub fn relative_to(&self, other: Self) -> Self {
        Self::new(
            (other.pos - self.pos).rotate_by(-self.rot),
            other.rot.relative_to(self.rot),
        )
    }

    pub fn rotate_around(&self, point: Vec3, rot: Rotation3D) -> Self {
        Self::new(self.pos.rotate_around(point, rot), self.rot.rotate_by(rot))
    }

    pub fn exp(self, twist: Twist3D) -> Self {
        let u = glam::DVec3::new(twist.dx.value, twist.dy.value, twist.dz.value);
        let rvec = glam::DVec3::new(twist.rx.value, twist.ry.value, twist.rz.value);
        let omega = glam::DMat3::from_euler(glam::EulerRot::XYZ, rvec.x, rvec.y, rvec.z);
        let omega_sq = omega * omega;
        let theta = rvec.length();
        let theta_sq = theta * theta;

        let a;
        let b;
        let c;

        if theta.abs() < 1e-7 {
            a = 1.0 - theta_sq / 6.0 + theta_sq * theta_sq / 120.0;
            b = 1.0 / 2.0 - theta_sq / 24.0 + theta_sq * theta_sq / 720.0;
            c = 1.0 / 6.0 - theta_sq / 120.0 + theta_sq * theta_sq / 5040.0;
        } else {
            a = theta.sin() / theta;
            b = (1.0 - theta.cos()) / theta_sq;
            c = (1.0 - a) / theta_sq;
        }

        let r = glam::DMat3::IDENTITY + a * omega + b * omega_sq;
        let v = glam::DMat3::IDENTITY + b * omega + c * omega_sq;

        let translation_component = v * u;

        let euler = r.to_euler(glam::EulerRot::XYZ);
        let transform = Self::new(
            Vec3::new(
                translation_component.x.meters(),
                translation_component.y.meters(),
                translation_component.z.meters(),
            ),
            Rotation3D::new(euler.0.radians(), euler.1.radians(), euler.2.radians()),
        );

        self + transform
    }

    pub fn log(self, end: Pose3D) -> Twist3D {
        let transform = end.relative_to(self);

        let u = glam::DVec3::new(
            transform.pos.x.value,
            transform.pos.y.value,
            transform.pos.z.value,
        );
        let (raxis, rangle) = transform.rot.quat.to_axis_angle();
        let rvec = raxis * rangle;
        let omega = glam::DMat3::from_axis_angle(raxis, rangle);
        let omega_sq = omega * omega;
        let theta = rvec.length();
        let theta_sq = theta * theta;

        let c;
        if theta.abs() < 1e-7 {
            c = 1.0 / 12.0 + theta_sq / 720.0 + theta_sq * theta_sq / 30240.0;
        } else {
            let a = theta.sin() / theta;
            let b = (1.0 - theta.cos()) / theta_sq;
            c = (1.0 - a / (2.0 * b)) / theta_sq;
        }

        let v_inv = glam::DMat3::IDENTITY - 0.5 * omega + c * omega_sq;

        let translation_component = v_inv * u;

        Twist3D::new(
            translation_component.x.meters(),
            translation_component.y.meters(),
            translation_component.z.meters(),
            rvec.x.radians(),
            rvec.y.radians(),
            rvec.z.radians(),
        )
    }

    pub fn to_pose2d(&self) -> Pose2D {
        Pose2D::new(self.pos.to_vec2(), self.rot.to_rotation2d())
    }
}

impl Add for Pose3D {
    type Output = Self;

    fn add(self, rhs: Self) -> Self::Output {
        self.transform_by(rhs)
    }
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Twist3D {
    pub dx: Length,
    pub dy: Length,
    pub dz: Length,
    pub rx: Angle,
    pub ry: Angle,
    pub rz: Angle,
}

impl Twist3D {
    pub fn new(dx: Length, dy: Length, dz: Length, rx: Angle, ry: Angle, rz: Angle) -> Self {
        Self {
            dx,
            dy,
            dz,
            rx,
            ry,
            rz,
        }
    }
}

impl Mul<f64> for Twist3D {
    type Output = Self;

    fn mul(self, rhs: f64) -> Self::Output {
        Self::new(
            self.dx * rhs,
            self.dy * rhs,
            self.dz * rhs,
            self.rx * rhs,
            self.ry * rhs,
            self.rz * rhs,
        )
    }
}
