///! Wrappers for Cross The Road Electronics (CTRE) devices.
use autocxx::WithinUniquePtr;
use uom::si::acceleration::meter_per_second_squared;
use uom::si::angle::{degree, revolution};
use uom::si::angular_velocity::revolution_per_second;
use uom::si::electric_potential::volt;
use uom::si::f64::{
    Acceleration, Angle, AngularVelocity, ElectricPotential, ThermodynamicTemperature,
};
use uom::si::thermodynamic_temperature::degree_celsius;

use crate::ffi;
use prelude::*;

pub mod configuration;
pub mod enums;
pub mod prelude;

pub type KrakenX60 = TalonFX;
pub type KrakenX44 = TalonFX;
pub type Falcon500 = TalonFX;

use std::ffi::CStr;

pub struct StatusCode {
    status: cxx::UniquePtr<ffi::StatusCode>,
}

impl StatusCode {
    pub(crate) fn new(status: cxx::UniquePtr<ffi::StatusCode>) -> Self {
        Self { status }
    }

    pub fn is_error(&mut self) -> bool {
        self.status.pin_mut().IsError()
    }

    pub fn is_warning(&mut self) -> bool {
        self.status.pin_mut().IsWarning()
    }

    pub fn is_ok(&mut self) -> bool {
        self.status.pin_mut().IsOK()
    }

    pub fn get_name(&mut self) -> &'static str {
        let name = self.status.pin_mut().GetName();
        let name = unsafe { CStr::from_ptr(name) };
        name.to_str().unwrap()
    }

    pub fn get_description(&mut self) -> &'static str {
        let name = self.status.pin_mut().GetDescription();
        let name = unsafe { CStr::from_ptr(name) };
        name.to_str().unwrap()
    }

    /// Returns Ok if the status is a warning or ok, and an Err if the status
    /// is an error.
    pub fn result(mut self) -> Result<(), StatusCode> {
        if self.is_error() { Err(self) } else { Ok(()) }
    }

    pub fn result_with<T>(mut self, with: T) -> Result<T, StatusCode> {
        if self.is_error() { Err(self) } else { Ok(with) }
    }
}

/// Wrapper for any motor powered by the TalonFX system.
pub struct TalonFX {
    motor: cxx::UniquePtr<ffi::talon::TalonFX>,
    /// If true, a positive speed/voltage will become negative..
    pub inverted: bool,
}

impl TalonFX {
    /// Create a new motor object. Specify the CAN ID and the CAN bus of the
    /// motor.
    pub fn new(can: i32, bus: &str) -> Self {
        let motor = ffi::talon::TalonFX::new(autocxx::c_int(can), bus).within_unique_ptr();

        Self {
            motor,
            inverted: false,
        }
    }

    pub fn configurator(&'_ mut self) -> TalonFXConfigurator<'_> {
        TalonFXConfigurator::new(ffi::talon::get_configurator(self.motor.pin_mut()))
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
        ffi::talon::set_voltage(self.motor.pin_mut(), voltage.get::<volt>());
    }

    pub fn set_position(&mut self, position: Angle) -> StatusCode {
        StatusCode::new(
            ffi::talon::set_position(self.motor.pin_mut(), position.get::<revolution>())
                .within_unique_ptr(),
        )
    }

    /// Get the current set speed of the motor controller. The value returned
    /// will be between -1.0 and 1.0.
    pub fn get(&self) -> f64 {
        self.motor.Get()
    }

    pub fn get_position(&mut self) -> f64 {
        ffi::talon::get_position(self.motor.pin_mut())
    }

    pub fn get_velocity(&mut self) -> f64 {
        ffi::talon::get_velocity(self.motor.pin_mut())
    }

    pub fn get_acceleration(&mut self) -> f64 {
        ffi::talon::get_acceleration(self.motor.pin_mut())
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

pub struct CANCoder {
    coder: cxx::UniquePtr<ffi::cancoder::CANcoder>,
}

impl CANCoder {
    pub fn new(id: i32, bus: &str) -> Self {
        Self {
            coder: ffi::cancoder::CANcoder::new(autocxx::c_int(id), bus).within_unique_ptr(),
        }
    }

    pub fn configurator(&'_ mut self) -> CANCoderConfigurator<'_> {
        CANCoderConfigurator::new(ffi::cancoder::get_configurator(self.coder.pin_mut()))
    }

    pub fn get_position(&mut self, refresh: bool) -> Angle {
        Angle::new::<revolution>(ffi::cancoder::get_position(self.coder.pin_mut(), refresh))
    }

    pub fn get_absolute_position(&mut self, refresh: bool) -> Angle {
        Angle::new::<revolution>(ffi::cancoder::get_absolute_position(
            self.coder.pin_mut(),
            refresh,
        ))
    }

    pub fn get_position_since_boot(&mut self, refresh: bool) -> Angle {
        Angle::new::<revolution>(ffi::cancoder::get_position_since_boot(
            self.coder.pin_mut(),
            refresh,
        ))
    }

    pub fn get_velocity(&mut self, refresh: bool) -> AngularVelocity {
        AngularVelocity::new::<revolution_per_second>(ffi::cancoder::get_velocity(
            self.coder.pin_mut(),
            refresh,
        ))
    }

    pub fn get_unfiltered_velocity(&mut self, refresh: bool) -> AngularVelocity {
        AngularVelocity::new::<revolution_per_second>(ffi::cancoder::get_unfiltered_velocity(
            self.coder.pin_mut(),
            refresh,
        ))
    }

    pub fn get_supply_voltage(&mut self, refresh: bool) -> ElectricPotential {
        ElectricPotential::new::<volt>(ffi::cancoder::get_velocity(self.coder.pin_mut(), refresh))
    }

    pub fn set_position(&mut self, angle: Angle) -> StatusCode {
        StatusCode::new(
            ffi::cancoder::set_position(self.coder.pin_mut(), angle.get::<revolution>())
                .within_unique_ptr(),
        )
    }
}

pub struct Pigeon2 {
    gyro: cxx::UniquePtr<ffi::pigeon2::Pigeon2>,
}

impl Pigeon2 {
    pub fn new(id: i32, bus: &str) -> Self {
        Self {
            gyro: ffi::pigeon2::Pigeon2::new(autocxx::c_int(id), bus).within_unique_ptr(),
        }
    }

    pub fn configurator(&'_ mut self) -> Pigeon2Configurator<'_> {
        Pigeon2Configurator::new(ffi::pigeon2::get_configurator(self.gyro.pin_mut()))
    }

    pub fn get_yaw(&mut self) -> Angle {
        Angle::new::<degree>(ffi::pigeon2::get_yaw(self.gyro.pin_mut()))
    }

    pub fn get_pitch(&mut self) -> Angle {
        Angle::new::<degree>(ffi::pigeon2::get_pitch(self.gyro.pin_mut()))
    }

    pub fn get_roll(&mut self) -> Angle {
        Angle::new::<degree>(ffi::pigeon2::get_roll(self.gyro.pin_mut()))
    }

    pub fn get_temperature(&mut self) -> ThermodynamicTemperature {
        ThermodynamicTemperature::new::<degree_celsius>(ffi::pigeon2::get_temperature(
            self.gyro.pin_mut(),
        ))
    }

    pub fn get_acceleration_x(&mut self) -> Acceleration {
        Acceleration::new::<meter_per_second_squared>(ffi::pigeon2::get_acceleration_x(
            self.gyro.pin_mut(),
        ))
    }

    pub fn get_acceleration_y(&mut self) -> Acceleration {
        Acceleration::new::<meter_per_second_squared>(ffi::pigeon2::get_acceleration_y(
            self.gyro.pin_mut(),
        ))
    }

    pub fn get_acceleration_z(&mut self) -> Acceleration {
        Acceleration::new::<meter_per_second_squared>(ffi::pigeon2::get_acceleration_z(
            self.gyro.pin_mut(),
        ))
    }

    pub fn get_supply_voltage(&mut self) -> ElectricPotential {
        ElectricPotential::new::<volt>(ffi::pigeon2::get_supply_voltage(self.gyro.pin_mut()))
    }

    pub fn set_yaw(&mut self, yaw: Angle) -> StatusCode {
        StatusCode::new(
            ffi::pigeon2::set_yaw(self.gyro.pin_mut(), yaw.get::<degree>()).within_unique_ptr(),
        )
    }

    pub fn reset(&mut self) {
        self.gyro.pin_mut().Reset();
    }
}
