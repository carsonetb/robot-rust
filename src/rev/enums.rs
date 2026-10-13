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
