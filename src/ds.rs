///! Driver station utility functions.
use std::ffi::CString;

use crate::ffi;

/// Type of alert to be sent to the driver station in the `alert` function.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum AlertType {
    Warning,
    Error,
}

/// Refresh the DS control word.
pub fn refresh() -> bool {
    unsafe { ffi::HAL_RefreshDSData() != 0 }
}

/// Send an error or warning to the driver station. If you want to print a
/// non-error message, you can just use `println`.
pub fn alert(typ: AlertType, message: &str) {
    let details = CString::new(message).unwrap();
    let empty = CString::new("").unwrap();

    let is_error = match typ {
        AlertType::Warning => 0,
        AlertType::Error => 1,
    };

    unsafe {
        ffi::HAL_SendError(
            is_error,
            1,
            0,
            details.as_ptr(),
            empty.as_ptr(),
            empty.as_ptr(),
            1,
        );
    }
}
