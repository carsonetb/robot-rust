use derive_more::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Neg, Sub, SubAssign};

use crate::prelude::*;

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
        let magnitude = f64::hypot(x, y);
        let (cos, sin) = if magnitude > 1e-6 {
            (x / magnitude, y / magnitude)
        } else {
            panic!("X,Y components of Rotation2D are zero.");
        };
        Self::new(f64::atan2(sin, cos).radians())
    }

    pub fn rotated(&self, other: &Self) -> Self {
        let (cos, sin) = (self.cos(), self.sin());
        let (ocos, osin) = (other.cos(), other.sin());
        Self::to(cos * ocos - sin * osin, cos * ocos + sin * osin)
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

    pub fn transformed(&self, other: &Vec2) -> Self {
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
            self.pos.transformed(&other.pos.rotated(&self.rotation)),
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
