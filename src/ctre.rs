//! Wrappers for Cross The Road Electronics (CTRE) devices.
//!
//! This module has a seperate prelude that you can import with:
//!
//! ```
//! use robot_rust::ctre::prelude::*;
//! ```
//!
//! ## Currently supported devices
//!
//! * [KrakenX60], [KrakenX44], and [Falcon500] via the [TalonFX] motor
//!   controller (configs incomplete).
//! * [CANCoder] motor encoder.
//! * [Pigeon2] gyro.

use autocxx::WithinUniquePtr;
use std::ffi::CStr;
use std::pin::Pin;

use crate::ffi;
use crate::prelude::*;
use crate::sim::prelude::*;

use prelude::*;

pub mod configuration;
pub mod control;
pub mod enums;
pub mod prelude;

/// A KrakenX60 motor controller, equivilant to [TalonFX].
pub type KrakenX60 = TalonFX;
/// A KrakenX44 motor controller, equivilant to [TalonFX].
pub type KrakenX44 = TalonFX;
/// A Falcon500 motor controller, equivilant to [TalonFX].
pub type Falcon500 = TalonFX;

/// The status returned by some functions.
///
/// ## Bound code
///
/// This type contains bound code, safety of some functions is not guaranteed.
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

    /// Returns Ok(T) if the status is a warning or ok, and an Err if the status
    /// is an error.
    pub fn result_with<T>(mut self, with: T) -> Result<T, StatusCode> {
        if self.is_error() { Err(self) } else { Ok(with) }
    }
}

#[derive(Debug, Default, Clone, Copy)]
pub enum TalonFXMotorType {
    #[default]
    KrakenX60,
    KrakenX60FOC,
    KrakenX44,
    KrakenX44FOC,
}

/// Wrapper for any motor powered by the TalonFX system.
#[allow(unused)]
pub struct TalonFX {
    bus: &'static str,
    id: i32,
    motor_type: MotorType,
    gearing: f64,
    moi: MomentOfInertia,
    motor: cxx::UniquePtr<ffi::talon::TalonFX>,
}

impl TalonFX {
    /// Create a new motor object. Specify the CAN ID and the CAN bus of the
    /// motor.
    pub fn new(id: i32, bus: &'static str) -> Self {
        // TODO: Deprecated CANBus string intialization.
        let motor = ffi::talon::TalonFX::new3(autocxx::c_int(id), bus).within_unique_ptr();

        Self {
            id,
            bus,
            motor,
            motor_type: MotorType::KrakenX60,
            gearing: 1.0,
            moi: 1.0.moment_of_inertia(),
        }
    }

    /// Provide simulation parameters. This is necessary to call for simulation.
    /// Does nothing when running on the roboRIO.
    pub fn with_simulation_params(
        #[allow(unused)] mut self,
        #[allow(unused)] motor_type: TalonFXMotorType,
        #[allow(unused)] gearing: f64,
        #[allow(unused)] moi: MomentOfInertia,
    ) -> Self {
        #[cfg(not(target_arch = "arm"))]
        {
            let _ = self.simulator().SetMotorType(match motor_type {
                TalonFXMotorType::KrakenX44 => ffi::sim::TalonFXSimState_MotorType::KrakenX44,
                TalonFXMotorType::KrakenX44FOC => ffi::sim::TalonFXSimState_MotorType::KrakenX44,
                TalonFXMotorType::KrakenX60 => ffi::sim::TalonFXSimState_MotorType::KrakenX60,
                TalonFXMotorType::KrakenX60FOC => ffi::sim::TalonFXSimState_MotorType::KrakenX60,
            });
            self.motor_type = match motor_type {
                TalonFXMotorType::KrakenX44 => MotorType::KrakenX44,
                TalonFXMotorType::KrakenX44FOC => MotorType::KrakenX44,
                TalonFXMotorType::KrakenX60 => MotorType::KrakenX60,
                TalonFXMotorType::KrakenX60FOC => MotorType::KrakenX60,
            };
            self.gearing = gearing;
            self.moi = moi;
        }
        self
    }

    /// Allows the motor to simulate when running in simulation mode. This
    /// function does nothing when running on the roboRIO and can be called at
    /// no performance cost.
    pub fn simulate(&mut self) {
        #[cfg(not(target_arch = "arm"))]
        {
            let mut inputs = SimulatorInputs::get();
            let mut outputs = SimulatorOutputs::get();

            let outputs = outputs.motor(self.bus, self.id);
            ffi::sim::talonfx_set_physics(
                self.motor.pin_mut(),
                outputs.supply_voltage.value,
                outputs.position.get::<revolution>(),
                outputs.velocity.get::<revolution_per_second>(),
            );

            let inputs = inputs.motor(self.bus, self.id);
            inputs.motor_type = self.motor_type;
            inputs.gearing = self.gearing;
            inputs.moi = self.moi;
            inputs.applied_voltage = ffi::sim::talonfx_get_voltage(self.motor.pin_mut()).volts();
            inputs.torque_current =
                ffi::sim::talonfx_get_torque_current(self.motor.pin_mut()).amps();
        }
    }

    pub fn configurator(&'_ mut self) -> TalonFXConfigurator<'_> {
        TalonFXConfigurator::new(ffi::talon::get_configurator(self.motor.pin_mut()))
    }

    /// Set the speed of the motor. The range is -1.0 to 1.0. Alternatively,
    /// you can use the `set_voltage` function to specify the exact voltage.
    pub fn set(&mut self, speed: f64) {
        ffi::talon::set(self.motor.pin_mut(), speed);
    }

    /// Supply a voltage to the motor. This should generally be somewhere from
    /// -12.0 volts to 12.0 volts.
    pub fn set_voltage(&mut self, voltage: ElectricPotential) {
        ffi::talon::set_voltage(self.motor.pin_mut(), voltage.get::<volt>());
    }

    /// Set this motor to use a MotionMagic controller.
    pub fn set_motionmagic_voltage(&mut self, control: &MotionMagicVoltage) {
        ffi::talon::set_motionmagic_voltage(self.motor.pin_mut(), control.to_ffi().pin_mut());
    }

    /// Resets the position of the encoder on this motor.
    pub fn set_position(&mut self, position: Angle) -> StatusCode {
        StatusCode::new(
            ffi::talon::set_position(self.motor.pin_mut(), position.get::<revolution>())
                .within_unique_ptr(),
        )
    }

    /// Get the current set speed of the motor controller. The value returned
    /// will be between -1.0 and 1.0.
    pub fn get_duty_cycle(&mut self) -> f64 {
        ffi::talon::get_duty_cycle(self.motor.pin_mut())
    }

    pub fn get_position(&mut self) -> Angle {
        ffi::talon::get_position(self.motor.pin_mut()).rotations()
    }

    pub fn get_velocity(&mut self) -> AngularVelocity {
        ffi::talon::get_velocity(self.motor.pin_mut()).rotations_per_second()
    }

    pub fn get_acceleration(&mut self) -> AngularAcceleration {
        ffi::talon::get_acceleration(self.motor.pin_mut()).rotations_per_second_squared()
    }

    /// Stops applying voltage to the motor, but leaves it free-spinning.
    pub fn coast(&mut self) {
        ffi::talon::coast(self.motor.pin_mut())
    }

    /// Brake mode.
    pub fn neutral(&mut self) {
        ffi::talon::neutral(self.motor.pin_mut())
    }

    #[allow(unused)]
    fn simulator(&mut self) -> Pin<&mut ffi::sim::TalonFXSimState> {
        ffi::sim::talonfx_sim_state(self.motor.pin_mut())
    }
}

/// A CAN based magnetic encoder that provides absolute and relative position
/// along with filtered velocity.
///
/// ## Bound code
///
/// This type contains bound code, safety of some functions is not guaranteed.
pub struct CANCoder {
    coder: cxx::UniquePtr<ffi::cancoder::CANcoder>,
}

impl CANCoder {
    pub fn new(id: i32, bus: &str) -> Self {
        Self {
            // TODO: Deprecated CANBus string intialization.
            coder: ffi::cancoder::CANcoder::new3(autocxx::c_int(id), bus).within_unique_ptr(),
        }
    }

    pub fn configurator(&'_ mut self) -> CANCoderConfigurator<'_> {
        CANCoderConfigurator::new(ffi::cancoder::get_configurator(self.coder.pin_mut()))
    }

    pub fn get_position(&mut self, refresh: bool) -> Angle {
        ffi::cancoder::get_position(self.coder.pin_mut(), refresh).rotations()
    }

    pub fn get_absolute_position(&mut self, refresh: bool) -> Angle {
        ffi::cancoder::get_absolute_position(self.coder.pin_mut(), refresh).rotations()
    }

    pub fn get_position_since_boot(&mut self, refresh: bool) -> Angle {
        ffi::cancoder::get_position_since_boot(self.coder.pin_mut(), refresh).rotations()
    }

    pub fn get_velocity(&mut self, refresh: bool) -> AngularVelocity {
        ffi::cancoder::get_velocity(self.coder.pin_mut(), refresh).rotations_per_second()
    }

    pub fn get_unfiltered_velocity(&mut self, refresh: bool) -> AngularVelocity {
        ffi::cancoder::get_unfiltered_velocity(self.coder.pin_mut(), refresh).rotations_per_second()
    }

    pub fn get_supply_voltage(&mut self, refresh: bool) -> ElectricPotential {
        ffi::cancoder::get_velocity(self.coder.pin_mut(), refresh).volts()
    }

    pub fn set_position(&mut self, angle: Angle) -> StatusCode {
        StatusCode::new(
            ffi::cancoder::set_position(self.coder.pin_mut(), angle.get::<revolution>())
                .within_unique_ptr(),
        )
    }
}

pub struct Pigeon2 {
    #[allow(unused)]
    bus: &'static str,
    #[allow(unused)]
    id: i32,
    gyro: cxx::UniquePtr<ffi::pigeon2::Pigeon2>,
}

impl Pigeon2 {
    pub fn new(bus: &'static str, id: i32) -> Self {
        Self {
            bus,
            id,
            // TODO: Deprecated CANBus string intialization.
            gyro: ffi::pigeon2::Pigeon2::new3(autocxx::c_int(id), bus).within_unique_ptr(),
        }
    }

    /// Allows the gyro to simulate when running in simulation mode. This
    /// function does nothing when running on the roboRIO and can be called at
    /// no performance cost.
    pub fn simulate(&mut self) {
        #[cfg(not(target_arch = "arm"))]
        {
            let mut inputs = SimulatorInputs::get();
            let mut outputs = SimulatorOutputs::get();

            let outputs = outputs.gyro(self.bus, self.id);
            ffi::sim::pigeon2_set_physics(
                self.gyro.pin_mut(),
                outputs.supply_voltage.value,
                outputs.xvel.get::<degree_per_second>(),
                outputs.yvel.get::<degree_per_second>(),
                outputs.zvel.get::<degree_per_second>(),
            );

            let inputs = inputs.gyro(self.bus, self.id);
            inputs.gyro_type = GyroType::Pigeon2;
        }
    }

    pub fn configurator(&'_ mut self) -> Pigeon2Configurator<'_> {
        Pigeon2Configurator::new(ffi::pigeon2::get_configurator(self.gyro.pin_mut()))
    }

    pub fn get_yaw(&mut self) -> Angle {
        ffi::pigeon2::get_yaw(self.gyro.pin_mut()).degrees()
    }

    pub fn get_pitch(&mut self) -> Angle {
        ffi::pigeon2::get_pitch(self.gyro.pin_mut()).degrees()
    }

    pub fn get_roll(&mut self) -> Angle {
        ffi::pigeon2::get_roll(self.gyro.pin_mut()).degrees()
    }

    pub fn get_temperature(&mut self) -> ThermodynamicTemperature {
        ffi::pigeon2::get_temperature(self.gyro.pin_mut()).celsius()
    }

    pub fn get_acceleration_x(&mut self) -> Acceleration {
        ffi::pigeon2::get_acceleration_x(self.gyro.pin_mut()).meters_per_second_squared()
    }

    pub fn get_acceleration_y(&mut self) -> Acceleration {
        ffi::pigeon2::get_acceleration_y(self.gyro.pin_mut()).meters_per_second_squared()
    }

    pub fn get_acceleration_z(&mut self) -> Acceleration {
        ffi::pigeon2::get_acceleration_z(self.gyro.pin_mut()).meters_per_second_squared()
    }

    pub fn get_supply_voltage(&mut self) -> ElectricPotential {
        ffi::pigeon2::get_supply_voltage(self.gyro.pin_mut()).volts()
    }

    pub fn set_yaw(&mut self, yaw: Angle) -> StatusCode {
        StatusCode::new(
            ffi::pigeon2::set_yaw(self.gyro.pin_mut(), yaw.get::<degree>()).within_unique_ptr(),
        )
    }
}
