pub use autolog::AutoLog;
pub use loggable::Loggable;
pub use logger::Logger;

use crate::ffi;

pub mod autolog;
pub mod loggable;
pub mod logger;

pub(super) fn str_to_wpi(s: &str) -> ffi::WPI_String {
    ffi::WPI_String {
        str_: s.as_ptr(),
        len: s.len(),
    }
}

pub fn now() -> i64 {
    unsafe { ffi::WPI_Now() as i64 }
}
