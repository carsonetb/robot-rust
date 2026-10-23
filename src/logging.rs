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
pub fn now() -> i64 {
    unsafe { ffi::WPI_Now() as i64 }
}
