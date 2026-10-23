#pragma once

#include "ctre/phoenix6/TalonFX.hpp"
#include "units/angle.h"
#include "units/angular_velocity.h"
#include "units/voltage.h"
#include "ctre/phoenix6/unmanaged/Unmanaged.hpp"

namespace sim_helpers {

inline void ctre_feed_enable(int timeout_ms) {
    ctre::phoenix::unmanaged::FeedEnable(timeout_ms);
}

inline double talonfx_get_voltage(ctre::phoenix6::hardware::TalonFX& motor) {
    return motor.GetSimState().GetMotorVoltage().value();
}

inline void talonfx_set_physics(ctre::phoenix6::hardware::TalonFX& motor, double supply_volts, double mechanism_rotations, double mechanism_rps, double gear_ratio) {
    auto& sim = motor.GetSimState();
    sim.SetSupplyVoltage(units::voltage::volt_t{supply_volts});
    sim.SetRawRotorPosition(units::angle::turn_t{mechanism_rotations * gear_ratio});
    sim.SetRotorVelocity(units::angular_velocity::turns_per_second_t{mechanism_rps * gear_ratio});
}

}
