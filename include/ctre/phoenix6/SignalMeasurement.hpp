/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include <string>
#include <units/time.h>

namespace ctre {
namespace phoenix6 {

    /**
     * \brief Information from a single measurement of a status signal.
     */
    template <typename T>
    struct SignalMeasurement {
        /**
         * \brief The name of the signal
         */
        std::string_view name;
        /**
         * \brief The value of the signal
         */
        T value;
        /**
         * \brief Timestamp of when the data point was taken
         */
        units::time::second_t timestamp;
        /**
         * \brief The units of the signal measurement
         */
        std::string units;
        /**
         * \brief Status code response of getting the data
         */
        ctre::phoenix::StatusCode status;
    };

}
}
