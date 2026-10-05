use std::{ffi::CStr, mem, ptr::null_mut};

use crate::ffi::*;

#[derive(Debug, Clone)]
pub struct HALError {
    pub code: i32,
    pub message: String,
}

impl HALError {
    pub fn new(code: i32) -> Result<(), Self> {
        if code == 0 {
            return Result::Ok(());
        }

        let message = unsafe {
            CStr::from_ptr(HAL_GetErrorMessage(code))
                .to_str()
                .unwrap()
                .to_string()
        };

        Result::Err(Self { code, message })
    }
}

pub struct ControlWord(HAL_ControlWord);

impl ControlWord {
    pub fn new() -> Result<Self, HALError> {
        let mut control = unsafe { mem::zeroed() };
        unsafe {
            let status = HAL_GetControlWord(&mut control);
            HALError::new(status)?;
        }

        Ok(Self(control))
    }

    pub fn enabled(&self) -> bool {
        self.0.enabled() != 0
    }

    pub fn autonomous(&self) -> bool {
        self.0.autonomous() != 0
    }

    pub fn teleop(&self) -> bool {
        self.0.autonomous() == 0
    }
}

pub struct PWMPort(HAL_DigitalPWMHandle);

impl PWMPort {
    pub fn new(port: i32) -> Result<Self, HALError> {
        let mut status: i32 = 0;

        unsafe {
            let handle = HAL_InitializePWMPort(port, null_mut(), &mut status);
            HALError::new(status)?;

            Ok(PWMPort(handle))
        }
    }
}

impl Drop for PWMPort {
    fn drop(&mut self) {
        unsafe {
            HAL_FreePWMPort(self.0);
        }
    }
}
