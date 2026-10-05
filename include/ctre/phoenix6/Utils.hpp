/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/networking/Utils.hpp"
#include <units/time.h>

#include "frc/Timer.h"

namespace ctre {
namespace phoenix6 {
namespace utils {

    /**
     * \brief Get the current timestamp.
     *
     * This is the time source used for status signals.
     *
     * This time source is typically continuous and monotonic.
     * However, it may be overridden in simulation to use a
     * non-monotonic, non-continuous source.
     *
     * \returns Current time
     */
    inline units::second_t GetCurrentTime()
    {
        return units::second_t{GetCurrentTimeSeconds()};
    }
    /**
     * \brief Get the system timestamp.
     *
     * This is NOT the time source used for status signals.
     * Use GetCurrentTime instead when working with status
     * signal timing.
     *
     * This time source is guaranteed to be continuous and
     * monotonic, making it useful for measuring time deltas
     * in a robot program.
     *
     * \returns System time
     */
    inline units::second_t GetSystemTime()
    {
        return units::second_t{GetSystemTimeSeconds()};
    }

    /**
     * \brief Converts an FPGA timestamp to the timebase
     * reported by GetCurrentTime().
     *
     * \param fpgaTime The FPGA timestamp
     * \returns The equivalent GetCurrentTime() timestamp
     */
    inline units::second_t FPGAToCurrentTime(units::second_t fpgaTime)
    {
        return (GetCurrentTime() - frc::Timer::GetFPGATimestamp()) + fpgaTime;
    }

}
}
}
