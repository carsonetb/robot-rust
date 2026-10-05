/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include <units/angular_velocity.h>
#include <units/current.h>
#include <units/torque.h>
#include <units/voltage.h>

namespace ctre {
namespace unit {

    using newton_meters_per_ampere = units::compound_unit<units::newton_meters, units::inverse<units::amperes>>;
    using newton_meters_per_ampere_t = units::unit_t<newton_meters_per_ampere>;

    using rpm_per_volt = units::compound_unit<units::revolutions_per_minute, units::inverse<units::volts>>;
    using rpm_per_volt_t = units::unit_t<rpm_per_volt>;

}
}
