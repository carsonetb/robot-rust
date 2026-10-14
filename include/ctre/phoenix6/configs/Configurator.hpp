/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix6/hardware/DeviceIdentifier.hpp"
#include "ctre/phoenix6/Utils.hpp"
#include <mutex>

namespace ctre {
namespace phoenix6 {
namespace configs {

    /**
     * \brief The base class for all device configurators.
     */
    class ParentConfigurator {
    public:
        /**
         * \brief The default maximum amount of time to wait for a config.
         */
        units::time::second_t DefaultTimeoutSeconds{0.100_s};

    private:
        hardware::DeviceIdentifier deviceIdentifier;
        mutable std::mutex _m;

        mutable units::second_t _creationTime = utils::GetCurrentTime();
        mutable units::second_t _lastConfigTime = _creationTime;
        mutable units::second_t _freqConfigStart = 0_s;

    protected:
        ParentConfigurator(hardware::DeviceIdentifier deviceIdentifier) : deviceIdentifier{std::move(deviceIdentifier)}
        {}

        ParentConfigurator(ParentConfigurator const &) = delete;
        ParentConfigurator &operator=(ParentConfigurator const &) = delete;

        void ReportIfFrequent() const;

        ctre::phoenix::StatusCode SetConfigsPrivate(std::string_view serializedString, units::time::second_t timeoutSeconds, bool futureProofConfigs, bool overrideIfDuplicate);
        ctre::phoenix::StatusCode GetConfigsPrivate(std::string &serializedString, units::time::second_t timeoutSeconds) const;
    };

}
}
}
