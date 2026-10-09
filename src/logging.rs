pub use autolog::AutoLog;
pub use loggable::Loggable;
pub use logger::Logger;

use crate::ffi;

pub mod autolog;
pub mod loggable;
pub mod logger;

pub fn now() -> i64 {
    unsafe { ffi::WPI_Now() as i64 }
}
