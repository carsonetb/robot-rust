/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include <units/angle.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/current.h>
#include <units/dimensionless.h>
#include <units/voltage.h>

namespace ctre {
namespace unit {

#define CTRE_PID_FF_UNIT_ADD(unit_name, output)                                                                                             \
    using unit_name##_per_turn = units::compound_unit<output, units::inverse<units::turns>>;                                                \
    using unit_name##_per_turn_t = units::unit_t<unit_name##_per_turn>;                                                                     \
    using unit_name##_per_turn_second = units::compound_unit<output, units::inverse<units::compound_unit<units::turns, units::seconds>>>;   \
    using unit_name##_per_turn_second_t = units::unit_t<unit_name##_per_turn_second>;                                                       \
    using unit_name##_per_turn_per_second = units::compound_unit<output, units::inverse<units::turns_per_second>>;                          \
    using unit_name##_per_turn_per_second_t = units::unit_t<unit_name##_per_turn_per_second>;                                               \
    using unit_name##_per_turn_per_second_squared = units::compound_unit<output, units::inverse<units::turns_per_second_squared>>;          \
    using unit_name##_per_turn_per_second_squared_t = units::unit_t<unit_name##_per_turn_per_second_squared>;

    CTRE_PID_FF_UNIT_ADD(scalar, units::scalar)
    CTRE_PID_FF_UNIT_ADD(volts, units::volts)
    CTRE_PID_FF_UNIT_ADD(amperes, units::amperes)

}
}
