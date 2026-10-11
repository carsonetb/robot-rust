#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

#[allow(dead_code)]
#[allow(unused_variables)]
#[allow(non_snake_case)]
#[allow(non_camel_case_types)]
#[allow(non_upper_case_globals)]
#[allow(improper_ctypes)]
pub mod bindings {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

pub use bindings::*;

autocxx::include_cpp! {
    #include "ctre/phoenix6/TalonFX.hpp"
    #include "ctre_helpers.hpp"

    #include "rev_helpers.hpp"

    safety!(unsafe)

    generate!("ctre::phoenix6::hardware::TalonFX")
    generate!("ctre::phoenix6::configs::TalonFXConfigurator")
    generate!("ctre::phoenix6::configs::TalonFXConfiguration")
    generate!("ctre::phoenix6::configs::Slot0Configs")
    generate!("ctre::phoenix6::configs::MotionMagicConfigs")
    generate!("ctre::phoenix6::configs::FeedbackConfigs")
    generate!("ctre::phoenix6::configs::MotorOutputConfigs")

    generate!("ctre::phoenix6::signals::FeedbackSensorSourceValue")
    generate!("ctre::phoenix6::signals::NeutralModeValue")
    generate!("ctre::phoenix6::signals::InvertedValue")

    generate!("ctre_helpers::set_voltage")
    generate!("ctre_helpers::set_position")
    generate!("ctre_helpers::get_output_voltage")
    generate!("ctre_helpers::get_supply_voltage")
    generate!("ctre_helpers::get_torque_current")
    generate!("ctre_helpers::get_stator_current")
    generate!("ctre_helpers::get_supply_current")
    generate!("ctre_helpers::get_device_temp")
    generate!("ctre_helpers::get_velocity")
    generate!("ctre_helpers::get_position")
    generate!("ctre_helpers::get_acceleration")
    generate!("ctre_helpers::get_kt")
    generate!("ctre_helpers::get_kv")
    generate!("ctre_helpers::get_stall_current")
    generate!("ctre_helpers::get_configurator")

    generate!("ctre_helpers::slot0::set_kP")
    generate!("ctre_helpers::slot0::set_kI")
    generate!("ctre_helpers::slot0::set_kD")
    generate!("ctre_helpers::slot0::set_kS")
    generate!("ctre_helpers::slot0::set_kV")
    generate!("ctre_helpers::slot0::set_kA")
    generate!("ctre_helpers::slot0::set_kG")

    generate!("ctre_helpers::motionmagic::set_cruise_velocity")
    generate!("ctre_helpers::motionmagic::set_acceleration")
    generate!("ctre_helpers::motionmagic::set_jerk")
    generate!("ctre_helpers::motionmagic::set_expo_kv")
    generate!("ctre_helpers::motionmagic::set_expo_ka")

    generate!("ctre_helpers::feedback::set_rotor_offset")
    generate!("ctre_helpers::feedback::set_sensor_to_mechanism_ratio")
    generate!("ctre_helpers::feedback::set_rotor_to_sensor_ratio")
    generate!("ctre_helpers::feedback::set_remote_sensor_id")
    generate!("ctre_helpers::feedback::set_velocity_filter_time_constant")

    generate!("rev_helpers::sparkmax_create")
    generate!("rev_helpers::sparkmax_set")
    generate!("rev_helpers::sparkmax_set_voltage")
    generate!("rev_helpers::sparkmax_destroy")

    block!("wpi::SendableBuilder")
    block!("wpi::Sendable")
    block!("wpi::SendableRegistry")
}

pub use ffi::ctre::phoenix6::configs::{
    FeedbackConfigs, MotionMagicConfigs, MotorOutputConfigs, Slot0Configs, TalonFXConfiguration,
    TalonFXConfigurator,
};
pub use ffi::ctre::phoenix6::hardware::TalonFX;
pub use ffi::ctre::phoenix6::signals::{
    FeedbackSensorSourceValue, InvertedValue, NeutralModeValue,
};
pub use ffi::ctre_helpers::feedback::{
    set_remote_sensor_id, set_rotor_offset, set_rotor_to_sensor_ratio,
    set_sensor_to_mechanism_ratio, set_velocity_filter_time_constant,
};
pub use ffi::ctre_helpers::motionmagic::{
    set_acceleration, set_cruise_velocity, set_expo_ka, set_expo_kv, set_jerk,
};
pub use ffi::ctre_helpers::slot0::{set_kA, set_kD, set_kG, set_kI, set_kP, set_kS, set_kV};
pub use ffi::ctre_helpers::{
    get_acceleration, get_configurator, get_device_temp, get_kt, get_kv, get_output_voltage,
    get_position, get_stall_current, get_stator_current, get_supply_current, get_supply_voltage,
    get_torque_current, get_velocity, set_position, set_voltage,
};
pub use ffi::rev_helpers::{
    SparkMaxHandle, sparkmax_create, sparkmax_destroy, sparkmax_set, sparkmax_set_voltage,
};
