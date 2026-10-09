use uom::si::electric_potential::volt;
use uom::si::f64::ElectricPotential;

use crate::ffi;

pub struct SparkMax {
    handle: *mut ffi::SparkMaxHandle,
    pub inverted: bool,
}

impl SparkMax {
    pub fn new(can_id: i32) -> Self {
        Self {
            handle: ffi::sparkmax_create(autocxx::c_int(can_id)),
            inverted: false,
        }
    }

    pub fn set(&mut self, speed: f64) {
        let speed = if self.inverted { -speed } else { speed };
        let speed = speed.clamp(-1.0, 1.0);

        unsafe {
            ffi::sparkmax_set(self.handle, speed);
        }
    }

    pub fn set_voltage(&mut self, voltage: ElectricPotential) {
        let voltage = if self.inverted { -voltage } else { voltage };

        unsafe {
            ffi::sparkmax_set_voltage(self.handle, voltage.get::<volt>());
        }
    }
}

impl Drop for SparkMax {
    fn drop(&mut self) {
        unsafe {
            ffi::sparkmax_destroy(self.handle);
        }
    }
}
