///! Wrappers for Cross The Road Electronics (CTRE) devices.
use autocxx::WithinUniquePtr;
use uom::si::{electric_potential::volt, f64::ElectricPotential};

use crate::ffi;

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

    /// Disable the motor controller.
    pub fn disable(&mut self) {
        self.motor.pin_mut().Disable();
    }

    /// Stop motor movement until Set is called again.
    pub fn stop(&mut self) {
        self.motor.pin_mut().StopMotor();
    }
}
