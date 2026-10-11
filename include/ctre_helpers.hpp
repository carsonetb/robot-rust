#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix6/CANcoder.hpp"
#include "ctre/phoenix6/TalonFX.hpp"
#include "ctre/phoenix6/configs/Configs.hpp"
#include "ctre/phoenix6/core/CoreCANcoder.hpp"
#include "ctre/phoenix6/core/CoreTalonFX.hpp"
#include "ctre/unit/pid_ff.h"
#include "units/angle.h"
#include "units/angular_acceleration.h"
#include "units/angular_jerk.h"
#include "units/angular_velocity.h"
#include "units/time.h"
#include "units/voltage.h"

// This file was fried to make ):

namespace ctre_helpers {

namespace talonfx {

inline void set_voltage(ctre::phoenix6::hardware::TalonFX& motor, double volts) {
    motor.SetVoltage(units::volt_t{volts});
}

inline ctre::phoenix::StatusCode set_position(ctre::phoenix6::hardware::TalonFX& motor, double value_rotations) {
    return motor.SetPosition(units::angle::turn_t{value_rotations});
}

inline double get_output_voltage(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetMotorVoltage().GetValueAsDouble(); }

inline double get_supply_voltage(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetSupplyVoltage().GetValueAsDouble(); }

inline double get_torque_current(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetTorqueCurrent().GetValueAsDouble(); }

inline double get_stator_current(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetStatorCurrent().GetValueAsDouble(); }

inline double get_supply_current(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetSupplyCurrent().GetValueAsDouble(); }

/** Device temperature in celsius */
inline double get_device_temp(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetDeviceTemp().GetValueAsDouble(); }

/** Velocity in turns/rotations per second */
inline double get_velocity(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetVelocity().GetValueAsDouble(); }

/** Position in turns/rotations */
inline double get_position(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetPosition().GetValueAsDouble(); }

/** Acceleration in turns/rotations per second squared. */
inline double get_acceleration(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetAcceleration().GetValueAsDouble(); }

/** Motor kT in newton meters per ampere. */
inline double get_kt(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetMotorKT().GetValueAsDouble(); }

/** Motor kV in rpm per volt. */
inline double get_kv(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetMotorKV().GetValueAsDouble(); }

inline double get_stall_current(ctre::phoenix6::hardware::TalonFX& motor) { return motor.GetMotorStallCurrent().GetValueAsDouble(); }

inline ctre::phoenix6::configs::TalonFXConfigurator& get_configurator(ctre::phoenix6::hardware::TalonFX& motor) {
    return motor.GetConfigurator();
}

namespace slot0 {

inline void set_kP(ctre::phoenix6::configs::Slot0Configs& conf, double value) {
    conf.kP = value;
}

inline void set_kI(ctre::phoenix6::configs::Slot0Configs& conf, double value) {
    conf.kI = value;
}

inline void set_kD(ctre::phoenix6::configs::Slot0Configs& conf, double value) {
    conf.kD = value;
}

inline void set_kS(ctre::phoenix6::configs::Slot0Configs& conf, double value) {
    conf.kS = value;
}

inline void set_kV(ctre::phoenix6::configs::Slot0Configs& conf, double value) {
    conf.kV = value;
}

inline void set_kA(ctre::phoenix6::configs::Slot0Configs& conf, double value) {
    conf.kA = value;
}

inline void set_kG(ctre::phoenix6::configs::Slot0Configs& conf, double value) {
    conf.kG = value;
}

} // namespace slot0

namespace motionmagic {

inline void set_cruise_velocity(ctre::phoenix6::configs::MotionMagicConfigs& conf, double rps) {
    conf.MotionMagicCruiseVelocity = units::angular_velocity::turns_per_second_t{rps};
}

inline void set_acceleration(ctre::phoenix6::configs::MotionMagicConfigs& conf, double rps_squared) {
    conf.MotionMagicAcceleration = units::angular_acceleration::turns_per_second_squared_t{rps_squared};
}

inline void set_jerk(ctre::phoenix6::configs::MotionMagicConfigs& conf, double rps_cubed) {
    conf.MotionMagicJerk = units::angular_jerk::turns_per_second_cubed_t{rps_cubed};
}

inline void set_expo_kv(ctre::phoenix6::configs::MotionMagicConfigs& conf, double volts_per_rps) {
    conf.MotionMagicExpo_kV = ctre::unit::volts_per_turn_per_second_t{volts_per_rps};
}

inline void set_expo_ka(ctre::phoenix6::configs::MotionMagicConfigs& conf, double volts_per_rps_squared) {
    conf.MotionMagicExpo_kA = ctre::unit::volts_per_turn_per_second_squared_t{volts_per_rps_squared};
}

} // namespace motionmagic

namespace feedback {

inline void set_rotor_offset(ctre::phoenix6::configs::FeedbackConfigs& conf, double rotations) {
    conf.FeedbackRotorOffset = units::angle::turn_t{rotations};
}

inline void set_sensor_to_mechanism_ratio(ctre::phoenix6::configs::FeedbackConfigs& conf, double value) {
    conf.SensorToMechanismRatio = value;
}

inline void set_rotor_to_sensor_ratio(ctre::phoenix6::configs::FeedbackConfigs& conf, double value) {
    conf.RotorToSensorRatio = value;
}

inline void set_remote_sensor_id(ctre::phoenix6::configs::FeedbackConfigs& conf, int value) {
    conf.FeedbackRemoteSensorID = value;
}

inline void set_velocity_filter_time_constant(ctre::phoenix6::configs::FeedbackConfigs& conf, double seconds) {
    conf.VelocityFilterTimeConstant = units::time::second_t{seconds};
}

}  // namespace feedback

}  // namespace talonfx

namespace cancoder {

inline ctre::phoenix6::configs::CANcoderConfigurator& get_configurator(ctre::phoenix6::hardware::CANcoder& coder) {
    return coder.GetConfigurator();
}

/** rps */
inline double get_velocity(ctre::phoenix6::hardware::CANcoder& coder, bool refresh) {
    return coder.GetVelocity(refresh).GetValueAsDouble();
}

/** rps */
inline double get_unfiltered_velocity(ctre::phoenix6::hardware::CANcoder& coder, bool refresh) {
    return coder.GetUnfilteredVelocity(refresh).GetValueAsDouble();
}

/** rotations */
inline double get_position(ctre::phoenix6::hardware::CANcoder& coder, bool refresh) {
    return coder.GetPosition(refresh).GetValueAsDouble();
}

/** rotations */
inline double get_absolute_position(ctre::phoenix6::hardware::CANcoder& coder, bool refresh) {
    return coder.GetAbsolutePosition(refresh).GetValueAsDouble();
}

/** rotations */
inline double get_position_since_boot(ctre::phoenix6::hardware::CANcoder& coder, bool refresh) {
    return coder.GetPositionSinceBoot(refresh).GetValueAsDouble();
}

/** volts */
inline double get_supply_voltage(ctre::phoenix6::hardware::CANcoder& coder, bool refresh) {
    return coder.GetSupplyVoltage(refresh).GetValueAsDouble();
}

inline ctre::phoenix::StatusCode set_position(ctre::phoenix6::hardware::CANcoder& coder, double rotations) {
    return coder.SetPosition(units::angle::turn_t{rotations});
}

}

}  // namespace ctre_helpers
