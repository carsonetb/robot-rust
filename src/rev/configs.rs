use autocxx::WithinUniquePtr;
use autocxx::c_int;

use crate::ffi;
use crate::prelude::*;

use super::enums::*;

pub struct SparkBaseConfig {
    pub(crate) conf: *mut ffi::rev::SparkConfigWrapper,
}

impl SparkBaseConfig {
    pub fn new() -> Self {
        Self {
            conf: ffi::rev::config_create(),
        }
    }

    pub fn neo() -> Self {
        Self {
            conf: ffi::rev::config_neo(),
        }
    }

    pub fn neo_2() -> Self {
        Self {
            conf: ffi::rev::config_neo_2(),
        }
    }

    pub fn neo_550() -> Self {
        Self {
            conf: ffi::rev::config_neo_550(),
        }
    }

    pub fn vortex() -> Self {
        Self {
            conf: ffi::rev::config_vortex(),
        }
    }

    pub fn ctre_minion() -> Self {
        Self {
            conf: ffi::rev::config_ctre_minion(),
        }
    }

    pub fn with_absolute_encoder(self, mut config: AbsoluteEncoderConfig) -> Self {
        unsafe {
            ffi::rev::apply_absolute_encoder(self.conf, config.conf.pin_mut());
        }
        self
    }

    pub fn with_analog_sensor(self, mut config: AnalogSensorConfig) -> Self {
        unsafe {
            ffi::rev::apply_analog_sensor(self.conf, config.conf.pin_mut());
        }
        self
    }

    pub fn with_encoder(self, mut config: EncoderConfig) -> Self {
        unsafe {
            ffi::rev::apply_encoder(self.conf, config.conf.pin_mut());
        }
        self
    }

    pub fn with_closed_loop(self, mut config: ClosedLoopConfig) -> Self {
        unsafe {
            ffi::rev::apply_closed_loop(self.conf, config.conf.pin_mut());
        }
        self
    }

    pub fn with_inverted(self, inverted: bool) -> Self {
        unsafe {
            ffi::rev::apply_inverted(self.conf, inverted);
        }
        self
    }

    pub fn with_idle_mode(self, mode: IdleMode) -> Self {
        unsafe {
            ffi::rev::apply_idle_mode(self.conf, mode as u32);
        }
        self
    }
}

impl Drop for SparkBaseConfig {
    fn drop(&mut self) {
        unsafe {
            ffi::rev::config_delete(self.conf);
        }
    }
}

pub struct AbsoluteEncoderConfig {
    conf: cxx::UniquePtr<ffi::rev::AbsoluteEncoderConfig>,
}

impl AbsoluteEncoderConfig {
    pub fn new() -> Self {
        Self {
            conf: ffi::rev::AbsoluteEncoderConfig::new().within_unique_ptr(),
        }
    }

    pub fn throughbore() -> Self {
        Self::new()
            .with_start_pulse(1.0.microseconds())
            .with_end_pulse(1.0.microseconds())
    }

    pub fn throughbore_v2() -> Self {
        Self::new()
            .with_start_pulse(3.88443797.microseconds())
            .with_end_pulse(1.94221899.microseconds())
    }

    pub fn spline() -> Self {
        Self::new()
            .with_start_pulse(1.0.microseconds())
            .with_end_pulse(1.0.microseconds())
    }

    pub fn with_inverted(mut self, inverted: bool) -> Self {
        self.conf.pin_mut().Inverted(inverted);
        self
    }

    pub fn with_position_conversion_factor(mut self, factor: f64) -> Self {
        self.conf.pin_mut().PositionConversionFactor(factor);
        self
    }

    pub fn with_velocity_conversion_factor(mut self, factor: f64) -> Self {
        self.conf.pin_mut().VelocityConversionFactor(factor);
        self
    }

    pub fn with_zero_offset(mut self, offset: f64) -> Self {
        self.conf.pin_mut().ZeroOffset(offset);
        self
    }

    pub fn with_average_depth(mut self, depth: i32) -> Self {
        self.conf.pin_mut().AverageDepth(c_int(depth));
        self
    }

    pub fn with_start_pulse(mut self, pulse: Time) -> Self {
        self.conf.pin_mut().StartPulseUs(pulse.get::<microsecond>());
        self
    }

    pub fn with_end_pulse(mut self, pulse: Time) -> Self {
        self.conf.pin_mut().EndPulseUs(pulse.get::<microsecond>());
        self
    }

    pub fn with_zero_centered(mut self, value: bool) -> Self {
        self.conf.pin_mut().ZeroCentered(value);
        self
    }
}

pub struct AnalogSensorConfig {
    conf: cxx::UniquePtr<ffi::rev::AnalogSensorConfig>,
}

impl AnalogSensorConfig {
    pub fn new() -> Self {
        Self {
            conf: ffi::rev::AnalogSensorConfig::new().within_unique_ptr(),
        }
    }

    pub fn with_inverted(mut self, inverted: bool) -> Self {
        self.conf.pin_mut().Inverted(inverted);
        self
    }

    pub fn with_position_conversion_factor(mut self, factor: f64) -> Self {
        self.conf.pin_mut().PositionConversionFactor(factor);
        self
    }

    pub fn with_velocity_conversion_factor(mut self, factor: f64) -> Self {
        self.conf.pin_mut().VelocityConversionFactor(factor);
        self
    }
}

pub struct EncoderConfig {
    conf: cxx::UniquePtr<ffi::rev::EncoderConfig>,
}

impl EncoderConfig {
    pub fn new() -> Self {
        Self {
            conf: ffi::rev::EncoderConfig::new().within_unique_ptr(),
        }
    }

    pub fn throughbore_or_spline() -> Self {
        Self::new().with_counts_per_rev(8192)
    }

    pub fn with_counts_per_rev(mut self, cpr: i32) -> Self {
        self.conf.pin_mut().CountsPerRevolution(c_int(cpr));
        self
    }

    pub fn with_inverted(mut self, inverted: bool) -> Self {
        self.conf.pin_mut().Inverted(inverted);
        self
    }

    pub fn with_position_conversion_factor(mut self, factor: f64) -> Self {
        self.conf.pin_mut().PositionConversionFactor(factor);
        self
    }

    pub fn with_velocity_conversion_factor(mut self, factor: f64) -> Self {
        self.conf.pin_mut().VelocityConversionFactor(factor);
        self
    }

    pub fn with_quadrature_average_depth(mut self, depth: i32) -> Self {
        self.conf.pin_mut().QuadratureAverageDepth(c_int(depth));
        self
    }

    pub fn with_quadrature_measurement_period(mut self, period_ms: i32) -> Self {
        self.conf
            .pin_mut()
            .QuadratureMeasurementPeriod(c_int(period_ms));
        self
    }

    pub fn with_uvw_average_depth(mut self, depth: i32) -> Self {
        self.conf.pin_mut().UvwAverageDepth(c_int(depth));
        self
    }

    pub fn with_uvw_measurement_period(mut self, period_ms: i32) -> Self {
        self.conf.pin_mut().UvwMeasurementPeriod(c_int(period_ms));
        self
    }
}

pub struct ClosedLoopConfig {
    conf: cxx::UniquePtr<ffi::rev::ClosedLoopConfig>,
}

impl ClosedLoopConfig {
    pub fn new() -> Self {
        Self {
            conf: ffi::rev::ClosedLoopConfig::new().within_unique_ptr(),
        }
    }

    pub fn with_pid(mut self, pid: PIDGains, slot: ClosedLoopSlot) -> Self {
        self.conf.pin_mut().Pid(pid.p, pid.i, pid.d, slot.to_ffi());
        self
    }

    pub fn with_p(mut self, p: f64, slot: ClosedLoopSlot) -> Self {
        self.conf.pin_mut().P(p, slot.to_ffi());
        self
    }

    pub fn with_i(mut self, i: f64, slot: ClosedLoopSlot) -> Self {
        self.conf.pin_mut().I(i, slot.to_ffi());
        self
    }

    pub fn with_d(mut self, d: f64, slot: ClosedLoopSlot) -> Self {
        self.conf.pin_mut().D(d, slot.to_ffi());
        self
    }

    pub fn with_dfilter(mut self, filter: f64, slot: ClosedLoopSlot) -> Self {
        self.conf.pin_mut().DFilter(filter, slot.to_ffi());
        self
    }

    pub fn with_izone(mut self, zone: f64, slot: ClosedLoopSlot) -> Self {
        self.conf.pin_mut().IZone(zone, slot.to_ffi());
        self
    }

    pub fn with_i_max_accum(mut self, value: f64, slot: ClosedLoopSlot) -> Self {
        self.conf.pin_mut().IMaxAccum(value, slot.to_ffi());
        self
    }

    pub fn with_min_output(mut self, value: f64, slot: ClosedLoopSlot) -> Self {
        self.conf.pin_mut().MinOutput(value, slot.to_ffi());
        self
    }

    pub fn with_max_output(mut self, value: f64, slot: ClosedLoopSlot) -> Self {
        self.conf.pin_mut().MaxOutput(value, slot.to_ffi());
        self
    }

    pub fn with_allowed_error(mut self, value: f64, slot: ClosedLoopSlot) -> Self {
        self.conf
            .pin_mut()
            .AllowedClosedLoopError(value, slot.to_ffi());
        self
    }

    pub fn with_position_wrapping(mut self, enabled: bool) -> Self {
        self.conf.pin_mut().PositionWrappingEnabled(enabled);
        self
    }

    pub fn with_position_wrapping_min(mut self, value: f64) -> Self {
        self.conf.pin_mut().PositionWrappingMinInput(value);
        self
    }

    pub fn with_position_wrapping_max(mut self, value: f64) -> Self {
        self.conf.pin_mut().PositionWrappingMaxInput(value);
        self
    }

    pub fn with_feedback_sensor(mut self, sensor: FeedbackSensor) -> Self {
        self.conf.pin_mut().SetFeedbackSensor(sensor.to_ffi());
        self
    }

    pub fn with_detached_feedback_sensor(mut self, sensor: FeedbackSensor, id: i32) -> Self {
        self.conf
            .pin_mut()
            .SetFeedbackSensor1(sensor.to_ffi(), c_int(id));
        self
    }
}
