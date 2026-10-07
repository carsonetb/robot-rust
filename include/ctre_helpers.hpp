#pragma once

#include "ctre/phoenix6/TalonFX.hpp"
#include "units/voltage.h"

namespace ctre_helpers {

inline void set_voltage(ctre::phoenix6::hardware::TalonFX& motor, double volts) {
  motor.SetVoltage(units::volt_t{volts});
}

}  // namespace ctre_helpers
