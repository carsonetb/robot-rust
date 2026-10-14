use autocxx::c_int;
use std::pin::Pin;

use crate::ffi;
use crate::prelude::*;

use configs::SparkBaseConfig;
use enums::*;

pub mod configs;
pub mod enums;
pub mod prelude;

pub struct SparkMax {
    spark: cxx::UniquePtr<ffi::rev::SparkMax>,
}

impl SparkMax {
    pub fn new(id: i32, motor_type: MotorType) -> Self {
        Self {
            spark: ffi::rev::sparkmax_create(c_int(id), c_int(motor_type as i32)),
        }
    }

    pub fn configure(&mut self, config: SparkBaseConfig, reset: ResetMode, persist: PersistMode) {
        unsafe {
            ffi::rev::configure(
                self.spark.pin_mut(),
                config.conf,
                reset.to_ffi(),
                persist.to_ffi(),
            );
        }
    }

    pub fn get_encoder(&'_ mut self) -> SparkRelativeEncoder<'_> {
        SparkRelativeEncoder::new(ffi::rev::get_encoder(self.spark.pin_mut()))
    }

    pub fn get_absolute_encoder(&'_ mut self) -> SparkAbsoluteEncoder<'_> {
        SparkAbsoluteEncoder::new(ffi::rev::get_absolute_encoder(self.spark.pin_mut()))
    }

    pub fn set(&mut self, speed: f64) {
        ffi::rev::set(self.spark.pin_mut(), speed);
    }

    pub fn set_voltage(&mut self, voltage: Voltage) {
        ffi::rev::set_voltage(self.spark.pin_mut(), voltage.get::<volt>());
    }

    pub fn disable(&mut self) {
        ffi::rev::disable(self.spark.pin_mut());
    }

    pub fn stop(&mut self) {
        ffi::rev::stop(self.spark.pin_mut());
    }

    pub fn get(&mut self) -> f64 {
        ffi::rev::get(self.spark.pin_mut())
    }

    pub fn get_applied_output(&mut self) -> f64 {
        ffi::rev::get_applied_output(self.spark.pin_mut())
    }

    pub fn get_bus_voltage(&mut self) -> Voltage {
        ffi::rev::get_applied_output(self.spark.pin_mut()).volts()
    }

    pub fn get_output_voltage(&mut self) -> Voltage {
        self.get_bus_voltage() * self.get_applied_output()
    }

    pub fn get_output_current(&mut self) -> Current {
        ffi::rev::get_applied_output(self.spark.pin_mut()).amps()
    }

    pub fn get_motor_temperature(&mut self) -> Temperature {
        ffi::rev::get_applied_output(self.spark.pin_mut()).celsius()
    }
}

pub struct SparkRelativeEncoder<'spark> {
    enc: Pin<&'spark mut ffi::rev::SparkRelativeEncoder>,
}

impl<'spark> SparkRelativeEncoder<'spark> {
    pub(crate) fn new(enc: Pin<&'spark mut ffi::rev::SparkRelativeEncoder>) -> Self {
        Self { enc }
    }

    pub fn get_position(&mut self) -> Angle {
        ffi::rev::get_position(self.enc.as_mut()).rotations()
    }

    pub fn get_velocity(&mut self) -> AngularVelocity {
        ffi::rev::get_position(self.enc.as_mut()).rotations_per_second()
    }

    pub fn set_position(&mut self, position: Angle) -> Result<(), REVLibError> {
        let err = REVLibError::from_ffi(ffi::rev::set_position(
            self.enc.as_mut(),
            position.get::<revolution>(),
        ));
        match err {
            REVLibError::Ok => Ok(()),
            _ => Err(err),
        }
    }
}

pub struct SparkAbsoluteEncoder<'spark> {
    enc: Pin<&'spark mut ffi::rev::SparkAbsoluteEncoder>,
}

impl<'spark> SparkAbsoluteEncoder<'spark> {
    pub(crate) fn new(enc: Pin<&'spark mut ffi::rev::SparkAbsoluteEncoder>) -> Self {
        Self { enc }
    }

    pub fn get_position(&mut self) -> Angle {
        ffi::rev::absolute_get_position(self.enc.as_mut()).rotations()
    }

    pub fn get_velocity(&mut self) -> AngularVelocity {
        ffi::rev::absolute_get_position(self.enc.as_mut()).rotations_per_second()
    }
}
