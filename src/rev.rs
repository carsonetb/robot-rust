use autocxx::c_int;

use crate::ffi;

use enums::MotorType;

pub mod configs;
pub mod enums;

use configs::SparkBaseConfig;
use enums::*;

// pub struct SparkMax {
//     handle: *mut ffi::SparkMaxHandle,
//     pub inverted: bool,
// }
//
// impl SparkMax {
//     pub fn new(can_id: i32) -> Self {
//         Self {
//             handle: ffi::sparkmax_create(autocxx::c_int(can_id)),
//             inverted: false,
//         }
//     }
//
//     pub fn set(&mut self, speed: f64) {
//         let speed = if self.inverted { -speed } else { speed };
//         let speed = speed.clamp(-1.0, 1.0);
//
//         unsafe {
//             ffi::sparkmax_set(self.handle, speed);
//         }
//     }
//
//     pub fn set_voltage(&mut self, voltage: ElectricPotential) {
//         let voltage = if self.inverted { -voltage } else { voltage };
//
//         unsafe {
//             ffi::sparkmax_set_voltage(self.handle, voltage.get::<volt>());
//         }
//     }
// }
//
// impl Drop for SparkMax {
//     fn drop(&mut self) {
//         unsafe {
//             ffi::sparkmax_destroy(self.handle);
//         }
//     }
// }

pub struct SparkMax {
    spark: cxx::UniquePtr<ffi::rev::SparkMax>,
    pub inverted: bool,
}

impl SparkMax {
    pub fn new(id: i32, motor_type: MotorType) -> Self {
        Self {
            spark: ffi::rev::sparkmax_create(c_int(id), c_int(motor_type as i32)),
            inverted: false,
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
}
