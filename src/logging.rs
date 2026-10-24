//! Provides tools for logging to both the roboRIO `.wpilog` file as well as to
//! NetworkTables. The logger can be paired with tools like [AdvantageScope](https://docs.advantagescope.org/).
//!
//! See documentation for [`Logger`]. All basic types and units
//! are loggable, and all types that are made up of only those types can be made
//! loggable with [`AutoLog`].

pub use autolog::AutoLog;
pub use loggable::Loggable;
pub use logger::Logger;

use crate::ffi;

pub mod autolog;
pub mod loggable;
pub mod logger;
pub mod nt;

pub(super) fn str_to_wpi(s: &str) -> ffi::WPI_String {
    ffi::WPI_String {
        str_: s.as_ptr() as *const std::ffi::c_char,
        len: s.len(),
    }
}

#[allow(unused)]
pub(super) fn wpi_to_str(s: &ffi::WPI_String) -> &str {
    unsafe {
        let bytes = std::slice::from_raw_parts(s.str_ as *const u8, s.len);
        str::from_utf8_unchecked(bytes)
    }
}

/// Return a value representing the current time in microseconds.
/// The epoch is not defined.
///
/// ## Example
///
/// ```
/// use robot_rust::prelude::*;
///
/// let time = (now() as f64).microseconds();
/// ```
///
/// ## Bound code
///
/// Code is bound to `WPI_Now` in `wpi/timestamp.h`.
pub fn now() -> i64 {
    unsafe { ffi::WPI_Now() as i64 }
}
