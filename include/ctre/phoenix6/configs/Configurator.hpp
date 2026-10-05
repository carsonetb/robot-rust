/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix/platform/Platform.hpp"
#include "ctre/phoenix6/hardware/DeviceIdentifier.hpp"
#include "ctre/phoenix6/networking/interfaces/ReportError_Interface.h"
#include "ctre/phoenix6/Utils.hpp"
#include <units/time.h>
#include <mutex>

namespace ctre {
namespace phoenix6 {
namespace configs {

    class ParentConfigurator
    {
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
        {
        }

        ParentConfigurator(ParentConfigurator const &) = delete;
        ParentConfigurator &operator=(ParentConfigurator const &) = delete;

        void ReportIfFrequent() const
        {
            auto currentTime = utils::GetCurrentTime();
            auto lastConfigTime = _lastConfigTime;
            _lastConfigTime = currentTime;

            if (currentTime - _creationTime < 5_s) {
                /* this was constructed recently, do not warn */
                return;
            }

            if (currentTime - lastConfigTime < 1_s) {
                /* we should not see multiple configs within a second */
                if (_freqConfigStart == 0_s) {
                    /* this is the first frequent config, capture the time we started seeing them */
                    _freqConfigStart = lastConfigTime;
                }
            } else {
                /* this is not a frequent config, reset the start time */
                _freqConfigStart = 0_s;
            }

            if (_freqConfigStart > 0_s && currentTime - _freqConfigStart > 3_s) {
                /* we've been seeing frequent config calls continuously for a few seconds, warn user */
                ctre::phoenix::StatusCode const status = ctre::phoenix::StatusCode::FrequentConfigCalls;

                std::stringstream location;
                location << this->deviceIdentifier.ToString() << " Config";
                c_ctre_phoenix_report_error(status.IsError(), status, 0, status.GetDescription(), location.str().c_str(), ctre::phoenix::platform::GetStackTrace(1).c_str());
            }
        }

        ctre::phoenix::StatusCode SetConfigsPrivate(const std::string &serializedString, units::time::second_t timeoutSeconds, bool futureProofConfigs, bool overrideIfDuplicate)
        {
            ctre::phoenix::StatusCode status;
            {
                std::lock_guard<std::mutex> lock{_m};

                status = networking::Wrappers::Device_SetConfigValues(
                    deviceIdentifier.network.c_str(),
                    deviceIdentifier.deviceHash,
                    timeoutSeconds.to<double>(),
                    serializedString,
                    futureProofConfigs,
                    overrideIfDuplicate);

                ReportIfFrequent();
            }

            if (!status.IsOK() && status != ctre::phoenix::StatusCode::TimeoutCannotBeZero) {
                std::stringstream location;
                location << this->deviceIdentifier.ToString() << " Apply Config";
                c_ctre_phoenix_report_error(status.IsError(), status, 0, status.GetDescription(), location.str().c_str(), ctre::phoenix::platform::GetStackTrace(1).c_str());
            }
            return status;
        }
        ctre::phoenix::StatusCode GetConfigsPrivate(std::string &serializedString, units::time::second_t timeoutSeconds) const
        {
            ctre::phoenix::StatusCode status;
            {
                std::lock_guard<std::mutex> lock{_m};

                status = networking::Wrappers::Device_GetConfigValues(
                    deviceIdentifier.network.c_str(),
                    deviceIdentifier.deviceHash,
                    timeoutSeconds.to<double>(),
                    serializedString);

                ReportIfFrequent();
            }

            if (!status.IsOK()) {
                std::stringstream location;
                location << this->deviceIdentifier.ToString() << " Refresh Config";
                c_ctre_phoenix_report_error(status.IsError(), status, 0, status.GetDescription(), location.str().c_str(), ctre::phoenix::platform::GetStackTrace(1).c_str());
            }
            return status;
        }
    };

}
}
}
