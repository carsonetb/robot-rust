//! Includes everything you'll need to write a basic robot program.
//!
//! Specialized modules like [`crate::ctre`], [`crate::rev`], [`crate::math`],
//! and [`crate::sim`] all have their own preludes.
//!
//! # Examples
//!
//! ```
//! use robot_rust::prelude::*;
//! ```

pub use crate::auto::{PoseProvider, TankAuto, tank_auto};
pub use crate::chooser::SendableChooser;
pub use crate::chooser_enum;
pub use crate::ctre::{CANCoder, KrakenX44, KrakenX60, Pigeon2, TalonFX};
pub use crate::ds::{AlertType, alert};
pub use crate::ecs::{
    AutonomousExit, AutonomousInit, AutonomousPeriodic, Command, CommandInternal, DisabledExit,
    DisabledInit, DisabledPeriodic, Init, Mode, Periodic, Resource, ResourceMut, State, StateRes,
    TeleopExit, TeleopInit, TeleopPeriodic, TestExit, TestInit, TestPeriodic, Timer,
};
pub use crate::hid::XboxController;
pub use crate::logging::{AutoLog, Loggable, Logger, now};
pub use crate::math::control::*;
pub use crate::math::{Pose2D, Rotation2D, Vec2, timestamp};
pub use crate::rev::SparkMax;
pub use crate::units::revolution_per_second_cubed::revolution_per_second_cubed;
pub use crate::units::revolution_per_second_squared::revolution_per_second_squared;
pub use crate::units::rpm::rpm;
pub use crate::units::*;
pub use bevy_ecs::prelude::{Component, Query};
pub use derive_more::{Deref, DerefMut};
pub use frc_autolog_macro::AutoLog;
#[allow(unused)]
pub(crate) use tracing::{Level, debug_span, error_span, info_span, trace_span, warn_span};
pub use tracing::{debug, error, event, info, span, trace, warn};
