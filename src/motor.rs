use autocxx::WithinUniquePtr;

use crate::ffi;

pub trait MotorController {
    fn set(&mut self, speed: f64);
}

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
}

impl MotorController for KrakenX60 {
    fn set(&mut self, speed: f64) {
        let speed = if self.inverted { -speed } else { speed };
        let speed = speed.clamp(-1.0, 1.0);

        let motor = self.motor.pin_mut();
        motor.Set(speed);
    }
}
