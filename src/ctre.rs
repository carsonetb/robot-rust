///! Wrappers for Cross The Road Electronics (CTRE) devices.
use autocxx::WithinUniquePtr;
use uom::si::angle::revolution;
use uom::si::electric_potential::volt;
use uom::si::f64::{Angle, ElectricPotential};

use crate::ffi;
use prelude::*;

pub mod configuration;
pub mod enums;
pub mod prelude;

pub type KrakenX60 = TalonFX;
pub type KrakenX44 = TalonFX;

/// Wrapper for any motor powered by the TalonFX system.
pub struct TalonFX {
    motor: cxx::UniquePtr<ffi::TalonFX>,
    /// If true, a positive speed/voltage will become negative..
    pub inverted: bool,
}

impl TalonFX {
    /// Create a new motor object. Specify the CAN ID and the CAN bus of the
    /// motor.
    pub fn new(can: i32, bus: &str) -> Self {
        let motor = ffi::TalonFX::new(autocxx::c_int(can), bus).within_unique_ptr();

        Self {
            motor,
            inverted: false,
        }
    }

    pub fn configurator(&'_ mut self) -> TalonFXConfigurator<'_> {
        TalonFXConfigurator {
            conf: ffi::get_configurator(self.motor.pin_mut()),
        }
    }

    /// Set the speed of the motor. The range is -1.0 to 1.0. Alternatively,
    /// you can use the `set_voltage` function to specify the exact voltage.
    ///
    /// If the motor is inverted, the speed will be negated.
    pub fn set(&mut self, speed: f64) {
        let speed = if self.inverted { -speed } else { speed };
        let speed = speed.clamp(-1.0, 1.0);

        let motor = self.motor.pin_mut();
        motor.Set(speed);
    }

    /// Supply a voltage to the motor. This should generally be somewhere from
    /// -12.0 volts to 12.0 volts.
    ///
    /// If the motor is inverted, the voltage will be negated.
    pub fn set_voltage(&mut self, voltage: ElectricPotential) {
        let voltage = if self.inverted { -voltage } else { voltage };
        ffi::set_voltage(self.motor.pin_mut(), voltage.get::<volt>());
    }

    pub fn set_position(&mut self, position: Angle) {
        // TODO: Handle status code.
        let _ = ffi::set_position(self.motor.pin_mut(), position.get::<revolution>());
    }

    /// Get the current set speed of the motor controller. The value returned
    /// will be between -1.0 and 1.0.
    pub fn get(&self) -> f64 {
        self.motor.Get()
    }

    pub fn get_position(&mut self) -> f64 {
        ffi::get_position(self.motor.pin_mut())
    }

    pub fn get_velocity(&mut self) -> f64 {
        ffi::get_velocity(self.motor.pin_mut())
    }

    pub fn get_acceleration(&mut self) -> f64 {
        ffi::get_acceleration(self.motor.pin_mut())
    }

    /// Disable the motor controller.
    pub fn disable(&mut self) {
        self.motor.pin_mut().Disable();
    }

    /// Stop motor movement until Set is called again.
    pub fn stop(&mut self) {
        self.motor.pin_mut().StopMotor();
    }
}
