use autocxx::WithinUniquePtr;
use uom::si::{electric_potential::volt, f64::ElectricPotential};

use crate::ffi;

pub struct KrakenX60 {
    motor: cxx::UniquePtr<ffi::TalonFX>,
    pub inverted: bool,
}

impl KrakenX60 {
    pub fn new(can: i32, bus: &str) -> Self {
        let motor = ffi::TalonFX::new(autocxx::c_int(can), bus).within_unique_ptr();

        Self {
            motor,
            inverted: false,
        }
    }

    pub fn set(&mut self, speed: f64) {
        let speed = if self.inverted { -speed } else { speed };
        let speed = speed.clamp(-1.0, 1.0);

        let motor = self.motor.pin_mut();
        motor.Set(speed);
    }

    pub fn set_voltage(&mut self, voltage: ElectricPotential) {
        let voltage = if self.inverted { -voltage } else { voltage };
        ffi::set_voltage(self.motor.pin_mut(), voltage.get::<volt>());
    }

    pub fn disable(&mut self) {
        self.motor.pin_mut().Disable();
    }

    pub fn stop(&mut self) {
        self.motor.pin_mut().StopMotor();
    }
}
