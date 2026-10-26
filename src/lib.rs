//! Safe, all-in-one solution for writing robot code in Rust.
//!
//! ## Features
//!
//! Normally, different functionality is separated into different modules
//! created by different teams (Core functionality, CTRE motors, REV motors,
//! Logging, Autonomoous, etc). In Rust, we don't get this luxury because there
//! are no other teams to write modules! So, the goal of this library is to
//! support all those needs:
//!
//! - HAL bindings: A State type that sets everything up and runs your robot for
//!   you.
//! - CTRE bindings: TalonFX, CANCoder, Pigeon2, a subset of configs.
//! - REV bindings: SparkMax, Spark Relative & Absolute Encoders, a subset of
//!   configs.
//! - Logging system: Similar to the [AdvantageKit](https://docs.advantagekit.org/)
//!   system, supports logging basic Rust types, Units, and automatically making
//!   your own types loggable via the `AutoLog` derive-macro. NetworkTables is
//!   supported.
//! - Units: Everything, when possible, is unit-ed using [`uom`](https://docs.rs/uom/latest/uom/).
//!   Helper functions are provided to make using these easier.
//! - Math: Feedback and feedforward controllers, simple math types, kinematics,
//!   odometry, ported manually from WPILib. If a math type exists, it should
//!   work the same as it does in WPILib.
//! - Autonomous System: Support for tank drive autonomous point-to-point path
//!   following, and (planned) support for swerve drive path following.
//! - Simulation: Many of the WPILib simulation types are manually ported, and
//!   future support for integrating [MuJoCo](https://mujoco.org/) is planned.

#[macro_use]
extern crate uom;

pub mod auto;
pub mod chooser;
pub mod ctre;
pub mod ds;
pub mod ecs;
pub mod ffi;
pub mod hal;
pub mod hid;
pub mod logging;
pub mod math;
pub mod prelude;
pub mod rev;
pub mod sim;
pub mod units;
