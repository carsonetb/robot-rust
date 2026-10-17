use autocxx::WithinUniquePtr;
use autocxx::c_int;

use crate::ffi;
use crate::prelude::*;

#[derive(Debug, Clone)]
pub struct MotionMagicVoltage {
    pub position: Angle,
    pub enable_foc: bool,
    pub feedforward: Voltage,
    pub slot: i32,
    pub override_brake_dur_neutral: bool,
    pub limit_forward_motion: bool,
    pub limit_reverse_motion: bool,
    pub ignore_hardware_limits: bool,
    pub ignore_software_limits: bool,
    pub use_timesync: bool,
    pub update_frequency: Frequency,
}

impl Default for MotionMagicVoltage {
    fn default() -> Self {
        Self::new(0.0.degrees())
    }
}

impl MotionMagicVoltage {
    pub fn new(position: Angle) -> Self {
        Self {
            position,
            enable_foc: true,
            feedforward: 0.0.volts(),
            slot: 0,
            override_brake_dur_neutral: false,
            limit_forward_motion: false,
            limit_reverse_motion: false,
            ignore_hardware_limits: false,
            ignore_software_limits: false,
            use_timesync: false,
            update_frequency: 100.0.hertz(),
        }
    }

    pub fn with_position(&mut self, position: Angle) -> &mut Self {
        self.position = position;
        self
    }

    pub fn with_enable_foc(&mut self, enable_foc: bool) -> &mut Self {
        self.enable_foc = enable_foc;
        self
    }

    pub fn with_feedforward(&mut self, feedforward: Voltage) -> &mut Self {
        self.feedforward = feedforward;
        self
    }

    pub fn with_slot(&mut self, slot: i32) -> &mut Self {
        self.slot = slot;
        self
    }

    pub fn with_override_brake_dur_neutral(
        &mut self,
        override_brake_dur_neutral: bool,
    ) -> &mut Self {
        self.override_brake_dur_neutral = override_brake_dur_neutral;
        self
    }

    pub fn with_limit_forward_motion(&mut self, limit_forward_motion: bool) -> &mut Self {
        self.limit_forward_motion = limit_forward_motion;
        self
    }

    pub fn with_limit_reverse_motion(&mut self, limit_reverse_motion: bool) -> &mut Self {
        self.limit_reverse_motion = limit_reverse_motion;
        self
    }

    pub fn with_ignore_hardware_limits(&mut self, ignore_hardware_limits: bool) -> &mut Self {
        self.ignore_hardware_limits = ignore_hardware_limits;
        self
    }

    pub fn with_ignore_software_limits(&mut self, ignore_software_limits: bool) -> &mut Self {
        self.ignore_software_limits = ignore_software_limits;
        self
    }

    pub fn with_use_timesync(&mut self, use_timesync: bool) -> &mut Self {
        self.use_timesync = use_timesync;
        self
    }

    pub fn with_update_frequency(&mut self, frequency: Frequency) -> &mut Self {
        self.update_frequency = frequency;
        self
    }

    pub(crate) fn to_ffi(&self) -> cxx::UniquePtr<ffi::talon::MotionMagicVoltage> {
        ffi::talon::create_motionmagic_control(
            self.position.get::<revolution>(),
            self.enable_foc,
            self.feedforward.get::<volt>(),
            c_int(self.slot),
            self.override_brake_dur_neutral,
            self.limit_forward_motion,
            self.limit_reverse_motion,
            self.ignore_hardware_limits,
            self.ignore_software_limits,
            self.use_timesync,
            self.update_frequency.get::<hertz>(),
        )
        .within_unique_ptr()
    }
}
