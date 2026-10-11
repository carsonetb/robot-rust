use std::f64::consts::TAU;
use std::pin::Pin;

use autocxx::{WithinUniquePtr, c_int};
use uom::si::{
    angle::revolution,
    angular_acceleration::radian_per_second_squared,
    angular_jerk::radian_per_second_cubed,
    angular_velocity::revolution_per_second,
    f64::{Angle, AngularAcceleration, AngularJerk, AngularVelocity, Time},
    time::second,
};

use super::prelude::*;
use crate::ffi;

pub struct TalonFXConfigurator<'a> {
    conf: Pin<&'a mut ffi::TalonFXConfigurator>,
}

impl<'a> TalonFXConfigurator<'a> {
    pub(crate) fn new(conf: Pin<&'a mut ffi::TalonFXConfigurator>) -> Self {
        Self { conf }
    }

    pub fn apply(&mut self, configuration: TalonFXConfiguration) -> StatusCode {
        StatusCode::new(
            self.conf
                .as_mut()
                .Apply(&configuration.conf)
                .within_unique_ptr(),
        )
    }
}

pub struct TalonFXConfiguration {
    conf: cxx::UniquePtr<ffi::TalonFXConfiguration>,
}

impl TalonFXConfiguration {
    pub fn new() -> Self {
        Self {
            conf: ffi::TalonFXConfiguration::new().within_unique_ptr(),
        }
    }

    pub fn with_slot0(mut self, configs: Slot0Configs) -> Self {
        self.conf.pin_mut().WithSlot0(configs.conf);
        self
    }

    pub fn with_motion_magic(mut self, configs: MotionMagicConfigs) -> Self {
        self.conf.pin_mut().WithMotionMagic(configs.conf);
        self
    }

    pub fn with_feedback(mut self, configs: FeedbackConfigs) -> Self {
        self.conf.pin_mut().WithFeedback(configs.conf);
        self
    }

    pub fn with_motor_output(mut self, configs: MotorOutputConfigs) -> Self {
        self.conf.pin_mut().WithMotorOutput(configs.conf);
        self
    }
}

pub struct Slot0Configs {
    pub(super) conf: cxx::UniquePtr<ffi::Slot0Configs>,
}

impl Slot0Configs {
    pub fn new() -> Self {
        Self {
            conf: ffi::Slot0Configs::new().within_unique_ptr(),
        }
    }

    pub fn with_ka(mut self, value: f64) -> Self {
        ffi::talon::set_kA(self.conf.pin_mut(), value);
        self
    }

    pub fn with_kg(mut self, value: f64) -> Self {
        ffi::talon::set_kG(self.conf.pin_mut(), value);
        self
    }

    pub fn with_ki(mut self, value: f64) -> Self {
        ffi::talon::set_kI(self.conf.pin_mut(), value);
        self
    }

    pub fn with_kp(mut self, value: f64) -> Self {
        ffi::talon::set_kP(self.conf.pin_mut(), value);
        self
    }

    pub fn with_kd(mut self, value: f64) -> Self {
        ffi::talon::set_kD(self.conf.pin_mut(), value);
        self
    }

    pub fn with_ks(mut self, value: f64) -> Self {
        ffi::talon::set_kS(self.conf.pin_mut(), value);
        self
    }

    pub fn with_kv(mut self, value: f64) -> Self {
        ffi::talon::set_kV(self.conf.pin_mut(), value);
        self
    }
}

pub struct MotionMagicConfigs {
    conf: cxx::UniquePtr<ffi::MotionMagicConfigs>,
}

impl MotionMagicConfigs {
    pub fn new() -> Self {
        Self {
            conf: ffi::MotionMagicConfigs::new().within_unique_ptr(),
        }
    }

    pub fn with_cruise_velocity(mut self, value: AngularVelocity) -> Self {
        ffi::talon::set_cruise_velocity(self.conf.pin_mut(), value.get::<revolution_per_second>());
        self
    }

    pub fn with_acceleration(mut self, value: AngularAcceleration) -> Self {
        ffi::talon::set_cruise_velocity(
            self.conf.pin_mut(),
            value.get::<radian_per_second_squared>() / TAU,
        );
        self
    }

    pub fn with_jerk(mut self, value: AngularJerk) -> Self {
        ffi::talon::set_jerk(
            self.conf.pin_mut(),
            value.get::<radian_per_second_cubed>() / TAU,
        );
        self
    }

    // TODO: Expo whatever that is.
}

pub struct FeedbackConfigs {
    conf: cxx::UniquePtr<ffi::FeedbackConfigs>,
}

impl FeedbackConfigs {
    pub fn new() -> Self {
        Self {
            conf: ffi::FeedbackConfigs::new().within_unique_ptr(),
        }
    }

    pub fn with_rotor_offset(mut self, value: Angle) -> Self {
        ffi::talon::set_rotor_offset(self.conf.pin_mut(), value.get::<revolution>());
        self
    }

    pub fn with_sensor_to_mechanism_ratio(mut self, value: f64) -> Self {
        ffi::talon::set_sensor_to_mechanism_ratio(self.conf.pin_mut(), value);
        self
    }

    pub fn with_rotor_to_sensor_ratio(mut self, value: f64) -> Self {
        ffi::talon::set_rotor_to_sensor_ratio(self.conf.pin_mut(), value);
        self
    }

    pub fn with_remote_sensor_id(mut self, value: i32) -> Self {
        ffi::talon::set_remote_sensor_id(self.conf.pin_mut(), c_int(value));
        self
    }

    pub fn with_velocity_filter_time_constant(mut self, value: Time) -> Self {
        ffi::talon::set_velocity_filter_time_constant(self.conf.pin_mut(), value.get::<second>());
        self
    }

    pub fn with_sensor_source(mut self, source: FeedbackSensorSourceValue) -> Self {
        self.conf.pin_mut().WithFeedbackSensorSource(
            ffi::FeedbackSensorSourceValue::new(c_int(source as i32)).within_unique_ptr(),
        );
        self
    }
}

pub struct MotorOutputConfigs {
    conf: cxx::UniquePtr<ffi::MotorOutputConfigs>,
}

impl MotorOutputConfigs {
    pub fn new() -> Self {
        Self {
            conf: ffi::MotorOutputConfigs::new().within_unique_ptr(),
        }
    }

    pub fn with_inverted(mut self, inverted: InvertedValue) -> Self {
        self.conf
            .pin_mut()
            .WithInverted(ffi::InvertedValue::new(c_int(inverted as i32)).within_unique_ptr());
        self
    }

    pub fn with_neutral_mode(mut self, mode: NeutralModeValue) -> Self {
        self.conf
            .pin_mut()
            .WithNeutralMode(ffi::NeutralModeValue::new(c_int(mode as i32)).within_unique_ptr());
        self
    }
}

pub struct CANCoderConfigurator<'a> {
    conf: Pin<&'a mut ffi::CANcoderConfigurator>,
}

impl<'a> CANCoderConfigurator<'a> {
    pub(crate) fn new(conf: Pin<&'a mut ffi::CANcoderConfigurator>) -> Self {
        Self { conf }
    }

    pub fn apply(&mut self, config: CANCoderConfiguration) -> StatusCode {
        StatusCode::new(self.conf.as_mut().Apply(&config.conf).within_unique_ptr())
    }
}

pub struct CANCoderConfiguration {
    conf: cxx::UniquePtr<ffi::CANcoderConfiguration>,
}

impl CANCoderConfiguration {
    pub fn new() -> Self {
        Self {
            conf: ffi::CANcoderConfiguration::new().within_unique_ptr(),
        }
    }

    pub fn with_magnet_sensor(mut self, configs: MagnetSensorConfigs) -> Self {
        self.conf.pin_mut().WithMagnetSensor(configs.conf);
        self
    }
}

pub struct MagnetSensorConfigs {
    conf: cxx::UniquePtr<ffi::MagnetSensorConfigs>,
}

impl MagnetSensorConfigs {
    pub fn new() -> Self {
        Self {
            conf: ffi::MagnetSensorConfigs::new().within_unique_ptr(),
        }
    }

    pub fn with_magnet_offset(mut self, value: Angle) -> Self {
        ffi::cancoder::set_magnet_offset(self.conf.pin_mut(), value.get::<revolution>());
        self
    }

    pub fn with_discontinuity_point(mut self, value: Angle) -> Self {
        ffi::cancoder::set_discontinuity_point(self.conf.pin_mut(), value.get::<revolution>());
        self
    }
}
