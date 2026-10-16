use derive_more::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Neg, Sub, SubAssign};
use num_traits::Pow;

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
    cos: f64,
    sin: f64,
}

impl Rotation2D {
    pub fn new(value: Angle) -> Self {
        Self {
            value,
            cos: value.get::<radian>().cos(),
            sin: value.get::<radian>().sin(),
        }
    }

    pub fn to(x: f64, y: f64) -> Self {
        let magnitude = f64::hypot(x, y);
        let (cos, sin) = if magnitude > 1e-6 {
            (x / magnitude, y / magnitude)
        } else {
            panic!("X,Y components of Rotation2D are zero.");
        };
        Self::new(f64::atan2(cos, sin).radians())
    }

    pub fn rotated(&self, other: &Self) -> Self {
        Self::to(
            self.cos * other.cos - self.sin * other.sin,
            self.cos * other.sin + self.sin * other.cos,
        )
    }

    /// Current rotation relative to the given rotation.
    pub fn relative(&self, other: &Self) -> Self {
        self.rotated(&-*other) // LOL
    }

    pub fn sin(&self) -> f64 {
        self.sin
    }

    pub fn cos(&self) -> f64 {
        self.cos
    }

    pub fn tan(&self) -> f64 {
        self.sin / self.cos
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
        Self::new(distance * angle.cos, distance * angle.sin)
    }

    pub fn distance_to(&self, other: &Vec2) -> Length {
        (other.x - self.x).hypot(other.y - self.y)
    }

    pub fn distance_to_squared(&self, other: &Vec2) -> f64 {
        (other.x - self.x).get::<meter>().pow(2.0) + (other.y - self.y).get::<meter>().pow(2.0)
    }

    pub fn norm(&self) -> Length {
        self.x.hypot(self.y)
    }

    pub fn squared_norm(&self) -> f64 {
        self.x.get::<meter>().pow(2.0) + self.y.get::<meter>().pow(2.0)
    }

    pub fn rotated(&self, by: &Rotation2D) -> Self {
        Self::new(
            self.x * by.cos - self.y * by.sin,
            self.x * by.sin + self.y * by.cos,
        )
    }

    pub fn rotated_around(&self, other: &Vec2, by: &Rotation2D) -> Self {
        Self::new(
            (self.x - other.x) * by.cos - (self.y - other.y) * by.sin + other.x,
            (self.x - other.x) * by.sin + (self.y - other.y) * by.cos + other.y,
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

    pub fn transformed(&self, other: &Vec2) -> Self {
        Self::new(self.pos.transformed(other), self.rotation)
    }

    pub fn to(&self, other: &Self) -> Self {
        Self::new(
            other.pos - self.pos,
            other.rotation.relative(&self.rotation),
        )
    }

    pub fn rotate_around(&self, point: Vec2, rotation: Rotation2D) -> Self {
        Self::new(
            self.pos.rotated_around(&point, &rotation),
            self.rotation.rotated(&rotation),
        )
    }

    // TODO: Exp and Log for Twist2D
}

#[derive(Debug, Clone, Copy, PartialEq, Mul, MulAssign)]
pub struct Twist2D {
    pub dx: Length,
    pub dy: Length,
    pub theta: Angle,
}

impl Twist2D {
    pub fn new(dx: Length, dy: Length, theta: Angle) -> Self {
        Self { dx, dy, theta }
    }
}
