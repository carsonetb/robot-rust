#pragma once

#include "ctre/phoenix6/TalonFX.hpp"
#include "ctre/phoenix6/Pigeon2.hpp"
#include "ctre/phoenix6/sim/TalonFXSimState.hpp"
#include "units/angle.h"
#include "units/angular_velocity.h"
#include "units/voltage.h"
#include "ctre/phoenix6/unmanaged/Unmanaged.hpp"

namespace sim_helpers {

inline void ctre_feed_enable(int timeout_ms) {
    ctre::phoenix::unmanaged::FeedEnable(timeout_ms);
}

inline ctre::phoenix6::sim::TalonFXSimState& talonfx_sim_state(ctre::phoenix6::hardware::TalonFX& motor) {
    return motor.GetSimState();
}

inline double talonfx_get_voltage(ctre::phoenix6::hardware::TalonFX& motor) {
    return motor.GetSimState().GetMotorVoltage().value();
}

inline double talonfx_get_torque_current(ctre::phoenix6::hardware::TalonFX& motor) {
    return motor.GetSimState().GetTorqueCurrent().value();
}

inline void talonfx_set_physics(ctre::phoenix6::hardware::TalonFX& motor, double supply_volts, double mechanism_rotations, double mechanism_rps) {
    auto& sim = motor.GetSimState();
    sim.SetSupplyVoltage(units::voltage::volt_t{supply_volts});
    sim.SetRawRotorPosition(units::angle::turn_t{mechanism_rotations});
    sim.SetRotorVelocity(units::angular_velocity::turns_per_second_t{mechanism_rps});
}

inline void pigeon2_set_physics(ctre::phoenix6::hardware::Pigeon2& gyro, double supply_volts, double xdps, double ydps, double zdps) {
    auto& sim = gyro.GetSimState();
    sim.SetSupplyVoltage(units::voltage::volt_t{supply_volts});
    sim.SetAngularVelocityX(units::angular_velocity::degrees_per_second_t{xdps});
    sim.SetAngularVelocityY(units::angular_velocity::degrees_per_second_t{ydps});
    sim.SetAngularVelocityZ(units::angular_velocity::degrees_per_second_t{zdps});
}

}
