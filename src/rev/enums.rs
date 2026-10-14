use num_derive::FromPrimitive;
use num_traits::FromPrimitive;

use crate::ffi;

pub enum MotorType {
    Brushed = 0,
    Brushless = 1,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum ClosedLoopSlot {
    Slot0,
    Slot1,
    Slot2,
    Slot3,
}

impl ClosedLoopSlot {
    pub(crate) fn to_ffi(self) -> ffi::rev::ClosedLoopSlot {
        match self {
            ClosedLoopSlot::Slot0 => ffi::rev::ClosedLoopSlot::kSlot0,
            ClosedLoopSlot::Slot1 => ffi::rev::ClosedLoopSlot::kSlot1,
            ClosedLoopSlot::Slot2 => ffi::rev::ClosedLoopSlot::kSlot2,
            ClosedLoopSlot::Slot3 => ffi::rev::ClosedLoopSlot::kSlot3,
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum FeedbackSensor {
    NoSensor,
    PrimaryEncoder,
    AnalogSensor,
    AlternateOrExternalEncoder,
    AbsoluteEncoder,
    DetachedAbsoluteEncoder,
    DetachedRelativeEncoder,
}

impl FeedbackSensor {
    pub(crate) fn to_ffi(self) -> ffi::rev::FeedbackSensor {
        match self {
            Self::NoSensor => ffi::rev::FeedbackSensor::kNoSensor,
            Self::PrimaryEncoder => ffi::rev::FeedbackSensor::kPrimaryEncoder,
            Self::AnalogSensor => ffi::rev::FeedbackSensor::kAnalogSensor,
            Self::AlternateOrExternalEncoder => {
                ffi::rev::FeedbackSensor::kAlternateOrExternalEncoder
            }
            Self::AbsoluteEncoder => ffi::rev::FeedbackSensor::kAbsoluteEncoder,
            Self::DetachedAbsoluteEncoder => ffi::rev::FeedbackSensor::kDetachedAbsoluteEncoder,
            Self::DetachedRelativeEncoder => ffi::rev::FeedbackSensor::kDetachedRelativeEncoder,
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum ResetMode {
    NoResetSafeParameters,
    ResetSafeParameters,
}

impl ResetMode {
    pub(crate) fn to_ffi(self) -> ffi::rev::ResetMode {
        match self {
            Self::NoResetSafeParameters => ffi::rev::ResetMode::kNoResetSafeParameters,
            Self::ResetSafeParameters => ffi::rev::ResetMode::kResetSafeParameters,
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum PersistMode {
    NoPersistParameters,
    PersistParameters,
}

impl PersistMode {
    pub(crate) fn to_ffi(self) -> ffi::rev::PersistMode {
        match self {
            Self::NoPersistParameters => ffi::rev::PersistMode::kNoPersistParameters,
            Self::PersistParameters => ffi::rev::PersistMode::kPersistParameters,
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum IdleMode {
    Coast = 0,
    Brake = 1,
}

#[derive(FromPrimitive, Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum REVLibError {
    Ok = 0,
    Error = 1,
    Timeout = 2,
    NotImplemented = 3,
    HALError = 4,
    CantFindFirmware = 5,
    FirmwareTooOld = 6,
    FirmwareTooNew = 7,
    ParamInvalidID = 8,
    ParamMismatchType = 9,
    ParamAccessMode = 10,
    ParamInvalid = 11,
    ParamNotImplementedDeprecated = 12,
    FollowConfigMismatch = 13,
    Invalid = 14,
    SetpointOutOfRange = 15,
    Unknown = 16,
    CANDisconnected = 17,
    DuplicateCANId = 18,
    InvalidCANId = 19,
    SparkMaxDataPortAlreadyConfiguredDifferently = 20,
    SparkFlexBrushedWithoutDock = 21,
    InvalidBrushlessEncoderConfiguration = 22,
    FeedbackSensorIncompatibleWithDataPortConfig = 23,
    ParamInvalidChannel = 24,
    ParamInvalidValue = 25,
    CannotPersistParametersWhileEnabled = 26,
}

impl REVLibError {
    pub(crate) fn from_ffi(ffi: ffi::rev::REVLibError) -> Self {
        Self::from_i32(ffi as i32).unwrap()
    }
}
