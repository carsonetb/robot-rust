use std::ffi::CString;

use crate::ffi;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum AlertType {
    Warning,
    Error,
}

pub fn refresh() -> bool {
    unsafe { ffi::HAL_RefreshDSData() != 0 }
}

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
