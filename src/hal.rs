///! Wrappers for Hardware Abstraction Layer (HAL) functionality.
use std::{ffi::CStr, mem, ptr::null_mut};

use num_enum::TryFromPrimitive;

use crate::ffi::*;

/// Wrapper for errors reported by the HAL.
#[derive(Debug, Clone)]
pub struct HALError {
    /// Raw error code.
    pub code: i32,
    /// Error code converted to human-readable string.
    pub message: String,
}

impl HALError {
    pub(crate) fn new(code: i32) -> Result<(), Self> {
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

    pub(crate) fn new_with<T>(code: i32, with: T) -> Result<T, Self> {
        Self::new(code).map(|_| with)
    }
}

/// State of the robot program reported by the driver station. This is handled
/// sufficiently by the `robot::run` function.
#[derive(Debug, Clone, Copy)]
pub struct ControlWord(HAL_ControlWord);

impl ControlWord {
    /// Gets the current control word of the driver station.
    /// The control word contains the robot state.
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

    pub fn disabled(&self) -> bool {
        self.0.enabled() == 0
    }

    pub fn autonomous(&self) -> bool {
        self.0.autonomous() != 0
    }

    pub fn teleop(&self) -> bool {
        self.0.autonomous() == 0
    }

    pub fn test(&self) -> bool {
        self.0.test() != 0
    }
}

impl PartialEq for ControlWord {
    fn eq(&self, other: &Self) -> bool {
        self.0._bindgen_align == other.0._bindgen_align && self.0._bitfield_1 == other.0._bitfield_1
    }
}

impl Eq for ControlWord {}

/// Basic PWM port wrapper.
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

///  Call this to start up HAL. This is required for robot programs.
///
///  This must be called before any other HAL functions. Failure to do so will
///  result in undefined behavior, and likely segmentation faults. This means
/// that  any statically initialized variables in a program MUST call this
/// function in  their constructors if they want to use other HAL calls.
///
///  This function is safe to call from any thread, and as many times as you
/// wish.  It internally guards from any reentrancy.
pub fn init() -> bool {
    unsafe { HAL_Initialize(500, 0) != 0 }
}

/// Ran at the beginning of the program.
pub fn start() {
    unsafe {
        HAL_ObserveUserProgramStarting();
    }
}

#[derive(TryFromPrimitive, Debug, Clone, Copy)]
#[repr(i32)]
pub enum AllianceStation {
    Unknown = 0,
    Red1 = 1,
    Red2 = 2,
    Red3 = 3,
    Blue1 = 4,
    Blue2 = 5,
    Blue3 = 6,
}

impl AllianceStation {
    pub fn to_alliance(&self) -> Alliance {
        match *self {
            AllianceStation::Unknown => Alliance::Unknown,
            AllianceStation::Red1 => Alliance::Red,
            AllianceStation::Red2 => Alliance::Red,
            AllianceStation::Red3 => Alliance::Red,
            AllianceStation::Blue1 => Alliance::Blue,
            AllianceStation::Blue2 => Alliance::Blue,
            AllianceStation::Blue3 => Alliance::Blue,
        }
    }
}

#[derive(Debug, Clone, Copy)]
pub enum Alliance {
    Unknown,
    Red,
    Blue,
}

pub fn get_alliance() -> Result<AllianceStation, HALError> {
    let mut status = 0;
    let out = unsafe { HAL_GetAllianceStation(&mut status) };
    HALError::new_with(status, AllianceStation::try_from_primitive(out).unwrap())
}

pub fn observe_disabled() {
    unsafe {
        HAL_ObserveUserProgramDisabled();
    }
}

pub fn observe_autonomous() {
    unsafe {
        HAL_ObserveUserProgramAutonomous();
    }
}

pub fn observe_teleop() {
    unsafe {
        HAL_ObserveUserProgramTeleop();
    }
}

pub fn observe_test() {
    unsafe {
        HAL_ObserveUserProgramTest();
    }
}

pub fn sim_pause_timing() {
    sim::HALSIM_PauseTiming();
}

pub fn sim_step_20ms() {
    sim::HALSIM_StepTiming(20_000);
}
