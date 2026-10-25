#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

#[allow(warnings)]
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
    #include "chooser_helpers.hpp"

    #include "ctre/phoenix6/sim/TalonFXSimState.hpp"
    #include "sim_helpers.hpp"

    #include "frc/XboxController.h"
    #include "frc/event/BooleanEvent.h"
    #include "frc/kinematics/ChassisSpeeds.h"

    #include "ctre/phoenix6/TalonFX.hpp"
    #include "ctre/phoenix6/CANcoder.hpp"
    #include "ctre/phoenix6/Pigeon2.hpp"
    #include "ctre_helpers.hpp"

    #include "rev/SparkMax.h"
    #include "rev/SparkRelativeEncoder.h"
    #include "rev/SparkAbsoluteEncoder.h"
    #include "rev/ClosedLoopTypes.h"
    #include "rev/ConfigureTypes.h"
    #include "rev/REVLibError.h"
    #include "rev/config/AbsoluteEncoderConfig.h"
    #include "rev/config/AnalogSensorConfig.h"
    #include "rev/config/EncoderConfig.h"
    #include "rev/config/LimitSwitchConfig.h"
    #include "rev/config/SoftLimitConfig.h"
    #include "rev/config/ClosedLoopConfig.h"
    #include "rev/config/SignalsConfig.h"
    #include "rev_helpers.hpp"

    safety!(unsafe)

    generate!("frc::XboxController")
    block!("frc::EventLoop")

    generate!("frc::ChassisSpeeds")

    generate!("chooser::ChooserHandle")
    generate!("chooser::chooser_create")
    generate!("chooser::chooser_destroy")
    generate!("chooser::chooser_set_default")
    generate!("chooser::chooser_add_option")
    generate!("chooser::chooser_publish")
    generate!("chooser::chooser_get_selected")

    generate!("ctre::phoenix::StatusCode")

    generate!("ctre::phoenix6::hardware::TalonFX")
    generate!("ctre::phoenix6::hardware::CANcoder")
    generate!("ctre::phoenix6::hardware::Pigeon2")

    generate!("ctre::phoenix6::signals::FeedbackSensorSourceValue")
    generate!("ctre::phoenix6::signals::NeutralModeValue")
    generate!("ctre::phoenix6::signals::InvertedValue")
    generate!("ctre::phoenix6::signals::SensorDirectionValue")

    generate!("ctre::phoenix6::configs::TalonFXConfigurator")
    generate!("ctre::phoenix6::configs::TalonFXConfiguration")
    generate!("ctre::phoenix6::configs::Slot0Configs")
    generate!("ctre::phoenix6::configs::MotionMagicConfigs")
    generate!("ctre::phoenix6::configs::FeedbackConfigs")
    generate!("ctre::phoenix6::configs::MotorOutputConfigs")

    generate!("ctre::phoenix6::configs::CANcoderConfigurator")
    generate!("ctre::phoenix6::configs::CANcoderConfiguration")
    generate!("ctre::phoenix6::configs::MagnetSensorConfigs")

    generate!("ctre::phoenix6::configs::Pigeon2Configurator")
    generate!("ctre::phoenix6::configs::Pigeon2Configuration")
    generate!("ctre::phoenix6::configs::MountPoseConfigs")
    generate!("ctre::phoenix6::configs::GyroTrimConfigs")
    generate!("ctre::phoenix6::configs::Pigeon2FeaturesConfigs")

    generate!("ctre_helpers::talonfx::set")
    generate!("ctre_helpers::talonfx::set_voltage")
    generate!("ctre_helpers::talonfx::set_position")
    generate!("ctre_helpers::talonfx::neutral")
    generate!("ctre_helpers::talonfx::coast")
    generate!("ctre_helpers::talonfx::set_motionmagic_voltage")
    generate!("ctre_helpers::talonfx::get_duty_cycle")
    generate!("ctre_helpers::talonfx::get_output_voltage")
    generate!("ctre_helpers::talonfx::get_supply_voltage")
    generate!("ctre_helpers::talonfx::get_torque_current")
    generate!("ctre_helpers::talonfx::get_stator_current")
    generate!("ctre_helpers::talonfx::get_supply_current")
    generate!("ctre_helpers::talonfx::get_device_temp")
    generate!("ctre_helpers::talonfx::get_velocity")
    generate!("ctre_helpers::talonfx::get_position")
    generate!("ctre_helpers::talonfx::get_acceleration")
    generate!("ctre_helpers::talonfx::get_kt")
    generate!("ctre_helpers::talonfx::get_kv")
    generate!("ctre_helpers::talonfx::get_stall_current")
    generate!("ctre_helpers::talonfx::get_configurator")

    generate!("ctre_helpers::talonfx::slot0::set_kP")
    generate!("ctre_helpers::talonfx::slot0::set_kI")
    generate!("ctre_helpers::talonfx::slot0::set_kD")
    generate!("ctre_helpers::talonfx::slot0::set_kS")
    generate!("ctre_helpers::talonfx::slot0::set_kV")
    generate!("ctre_helpers::talonfx::slot0::set_kA")
    generate!("ctre_helpers::talonfx::slot0::set_kG")

    generate!("ctre_helpers::talonfx::motionmagic::create_control")
    generate!("ctre_helpers::talonfx::motionmagic::set_cruise_velocity")
    generate!("ctre_helpers::talonfx::motionmagic::set_acceleration")
    generate!("ctre_helpers::talonfx::motionmagic::set_jerk")
    generate!("ctre_helpers::talonfx::motionmagic::set_expo_kv")
    generate!("ctre_helpers::talonfx::motionmagic::set_expo_ka")

    generate!("ctre_helpers::talonfx::feedback::set_rotor_offset")
    generate!("ctre_helpers::talonfx::feedback::set_sensor_to_mechanism_ratio")
    generate!("ctre_helpers::talonfx::feedback::set_rotor_to_sensor_ratio")
    generate!("ctre_helpers::talonfx::feedback::set_remote_sensor_id")
    generate!("ctre_helpers::talonfx::feedback::set_velocity_filter_time_constant")

    generate!("ctre_helpers::cancoder::get_configurator")
    generate!("ctre_helpers::cancoder::get_velocity")
    generate!("ctre_helpers::cancoder::get_unfiltered_velocity")
    generate!("ctre_helpers::cancoder::get_position")
    generate!("ctre_helpers::cancoder::get_absolute_position")
    generate!("ctre_helpers::cancoder::get_position_since_boot")
    generate!("ctre_helpers::cancoder::get_supply_voltage")
    generate!("ctre_helpers::cancoder::set_position")

    generate!("ctre_helpers::magnetsensor::set_magnet_offset")
    generate!("ctre_helpers::magnetsensor::set_discontinuity_point")

    generate!("ctre_helpers::pigeon2::get_configurator")
    generate!("ctre_helpers::pigeon2::get_yaw")
    generate!("ctre_helpers::pigeon2::get_pitch")
    generate!("ctre_helpers::pigeon2::get_roll")
    generate!("ctre_helpers::pigeon2::get_temperature")
    generate!("ctre_helpers::pigeon2::get_acceleration_x")
    generate!("ctre_helpers::pigeon2::get_acceleration_y")
    generate!("ctre_helpers::pigeon2::get_acceleration_z")
    generate!("ctre_helpers::pigeon2::get_supply_voltage")
    generate!("ctre_helpers::pigeon2::set_yaw")

    generate!("ctre_helpers::mountpose::set_yaw")
    generate!("ctre_helpers::mountpose::set_pitch")
    generate!("ctre_helpers::mountpose::set_roll")

    generate!("ctre_helpers::gyrotrim::set_scalar_x")
    generate!("ctre_helpers::gyrotrim::set_scalar_y")
    generate!("ctre_helpers::gyrotrim::set_scalar_z")

    generate!("rev::spark::SparkMax")
    block_constructors!("rev::spark::SparkMax")
    generate!("rev::spark::SparkRelativeEncoder")
    block_constructors!("rev::spark::SparkRelativeEncoder")
    generate!("rev::spark::SparkAbsoluteEncoder")
    block_constructors!("rev::spark::SparkAbsoluteEncoder")

    generate!("rev::spark::AbsoluteEncoderConfig")
    generate!("rev::spark::AnalogSensorConfig")
    generate!("rev::spark::EncoderConfig")
    generate!("rev::spark::LimitSwitchConfig")
    generate!("rev::spark::SoftLimitConfig")
    generate!("rev::spark::ClosedLoopConfig")
    generate!("rev::spark::SignalsConfig")

    generate!("rev::spark::ClosedLoopSlot")
    generate!("rev::spark::FeedbackSensor")
    generate!("rev::ResetMode")
    generate!("rev::PersistMode")

    generate!("rev::REVLibError")

    generate!("rev_helpers::spark::create")
    generate!("rev_helpers::spark::set")
    generate!("rev_helpers::spark::set_voltage")
    generate!("rev_helpers::spark::disable")
    generate!("rev_helpers::spark::stop")
    generate!("rev_helpers::spark::get")
    generate!("rev_helpers::spark::get_encoder")
    generate!("rev_helpers::spark::get_absolute_encoder")
    generate!("rev_helpers::spark::get_applied_output")
    generate!("rev_helpers::spark::get_bus_voltage")
    generate!("rev_helpers::spark::get_output_current")
    generate!("rev_helpers::spark::get_motor_temperature")
    generate!("rev_helpers::spark::configure")

    generate!("rev_helpers::spark::config_create")
    generate!("rev_helpers::spark::config_delete")
    generate!("rev_helpers::spark::config_neo")
    generate!("rev_helpers::spark::config_neo_2")
    generate!("rev_helpers::spark::config_neo_550")
    generate!("rev_helpers::spark::config_vortex")
    generate!("rev_helpers::spark::config_ctre_minion")
    generate!("rev_helpers::spark::apply_absolute_encoder")
    generate!("rev_helpers::spark::apply_analog_sensor")
    generate!("rev_helpers::spark::apply_encoder")
    generate!("rev_helpers::spark::apply_closed_loop")
    generate!("rev_helpers::spark::apply_inverted")
    generate!("rev_helpers::spark::apply_idle_mode")

    generate!("rev_helpers::spark::get_position")
    generate!("rev_helpers::spark::get_velocity")
    generate!("rev_helpers::spark::set_position")

    generate!("rev_helpers::spark::absolute_get_position")
    generate!("rev_helpers::spark::absolute_get_velocity")

    generate!("sim_helpers::ctre_feed_enable")
    generate!("sim_helpers::talonfx_sim_state")
    generate!("sim_helpers::talonfx_get_voltage")
    generate!("sim_helpers::talonfx_get_torque_current")
    generate!("sim_helpers::talonfx_set_physics")

    block!("ctre::phoenix6::hardware::core::CoreTalonFX")
    generate!("ctre::phoenix6::sim::TalonFXSimState")
    block_constructors!("ctre::phoenix6::sim::TalonFXSimState")

    block!("wpi::SendableBuilder")
    block!("wpi::Sendable")
    block!("wpi::SendableRegistry")
}

pub mod talon {
    use super::ffi;

    pub use ffi::ctre::phoenix6::controls::MotionMagicVoltage;
    pub use ffi::ctre::phoenix6::hardware::TalonFX;
    pub use ffi::ctre_helpers::talonfx::feedback::{
        set_remote_sensor_id, set_rotor_offset, set_rotor_to_sensor_ratio,
        set_sensor_to_mechanism_ratio, set_velocity_filter_time_constant,
    };
    pub use ffi::ctre_helpers::talonfx::motionmagic::{
        create_control as create_motionmagic_control, set_acceleration, set_cruise_velocity,
        set_expo_ka, set_expo_kv, set_jerk,
    };
    pub use ffi::ctre_helpers::talonfx::slot0::{
        set_kA, set_kD, set_kG, set_kI, set_kP, set_kS, set_kV,
    };
    pub use ffi::ctre_helpers::talonfx::{
        coast, get_acceleration, get_configurator, get_device_temp, get_duty_cycle, get_kt, get_kv,
        get_output_voltage, get_position, get_stall_current, get_stator_current,
        get_supply_current, get_supply_voltage, get_torque_current, get_velocity, neutral, set,
        set_motionmagic_voltage, set_position, set_voltage,
    };
}

pub mod cancoder {
    use super::ffi;

    pub use ffi::ctre::phoenix6::hardware::CANcoder;
    pub use ffi::ctre_helpers::cancoder::{
        get_absolute_position, get_configurator, get_position, get_position_since_boot,
        get_supply_voltage, get_unfiltered_velocity, get_velocity, set_position,
    };
    pub use ffi::ctre_helpers::magnetsensor::{set_discontinuity_point, set_magnet_offset};
}

pub mod pigeon2 {
    use super::ffi;

    pub use ffi::ctre::phoenix6::hardware::Pigeon2;
    pub use ffi::ctre_helpers::gyrotrim::{set_scalar_x, set_scalar_y, set_scalar_z};
    pub use ffi::ctre_helpers::pigeon2::{
        get_acceleration_x, get_acceleration_y, get_acceleration_z, get_configurator, get_pitch,
        get_roll, get_supply_voltage, get_temperature, get_yaw, set_yaw,
    };

    pub mod mountpose {
        use super::ffi;

        pub use ffi::ctre_helpers::mountpose::{set_pitch, set_roll, set_yaw};
    }
}

pub mod rev {
    use super::ffi;

    pub use ffi::rev::spark::{
        AbsoluteEncoderConfig, AnalogSensorConfig, ClosedLoopConfig, ClosedLoopSlot, EncoderConfig,
        FeedbackSensor, LimitSwitchConfig, SignalsConfig, SoftLimitConfig, SparkAbsoluteEncoder,
        SparkMax, SparkRelativeEncoder,
    };
    pub use ffi::rev::{PersistMode, REVLibError, ResetMode};
    pub use ffi::rev_helpers::spark::{
        SparkConfigWrapper, absolute_get_position, absolute_get_velocity, apply_absolute_encoder,
        apply_analog_sensor, apply_closed_loop, apply_encoder, apply_idle_mode, apply_inverted,
        config_create, config_ctre_minion, config_delete, config_neo, config_neo_2, config_neo_550,
        config_vortex, configure, create as sparkmax_create, disable, get, get_absolute_encoder,
        get_applied_output, get_bus_voltage, get_encoder, get_motor_temperature,
        get_output_current, get_position, get_velocity, set, set_position, set_voltage, stop,
    };
}

pub mod sim {
    use super::ffi;

    pub use ffi::sim_helpers::*;

    pub use ffi::ctre::phoenix6::sim::{TalonFXSimState, TalonFXSimState_MotorType};
}

pub use ffi::chooser::{
    ChooserHandle, chooser_add_option, chooser_create, chooser_destroy, chooser_get_selected,
    chooser_publish, chooser_set_default,
};
pub use ffi::ctre::phoenix::StatusCode;
pub use ffi::ctre::phoenix6::configs::{
    CANcoderConfiguration, CANcoderConfigurator, FeedbackConfigs, GyroTrimConfigs,
    MagnetSensorConfigs, MotionMagicConfigs, MotorOutputConfigs, MountPoseConfigs,
    Pigeon2Configuration, Pigeon2Configurator, Pigeon2FeaturesConfigs, Slot0Configs,
    TalonFXConfiguration, TalonFXConfigurator,
};
pub use ffi::ctre::phoenix6::signals::{
    FeedbackSensorSourceValue, InvertedValue, NeutralModeValue, SensorDirectionValue,
};
pub use ffi::frc::XboxController;
