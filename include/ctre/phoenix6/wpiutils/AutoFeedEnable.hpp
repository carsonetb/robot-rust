/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/SignalLogger.hpp"
#include "ctre/phoenix6/unmanaged/Unmanaged.hpp"
#include "frc/DriverStation.h"
#include "frc/Notifier.h"
#include <mutex>

namespace ctre {
namespace phoenix6 {
namespace wpiutils {

class AutoFeedEnable {
public:
    static AutoFeedEnable &GetInstance()
    {
        static AutoFeedEnable *autoFeedEnable = new AutoFeedEnable{};
        return *autoFeedEnable;
    }

private:
    std::mutex _lck;
    frc::Notifier _enableNotifier;
    uint32_t _startCount = 0;

    AutoFeedEnable() :
        _enableNotifier{[] {
            std::string_view robotMode;
            if (frc::DriverStation::IsEnabled()) {
                ctre::phoenix::unmanaged::FeedEnable(100);

                if (frc::DriverStation::IsAutonomous()) {
                    robotMode = "Autonomous";
                } else if (frc::DriverStation::IsTest()) {
                    robotMode = "Test";
                } else {
                    robotMode = "Teleop";
                }
            } else {
                robotMode = "Disabled";
            }
            SignalLogger::WriteString("RobotMode", robotMode);
        }}
    {}

public:
    /**
     * \brief Starts feeding the enable signal to CTRE actuators.
     */
    void Start()
    {
        std::lock_guard<std::mutex> lock{_lck};
        if (_startCount < UINT32_MAX) {
            if (_startCount++ == 0) {
                /* start if we were previously at 0 */
                _enableNotifier.StartPeriodic(20_ms);
            }
        }
    }

    /**
     * \brief Stops feeding the enable signal to CTRE actuators.
     * The enable signal will only be stopped when all actuators
     * have requested to stop the enable signal.
     */
    void Stop()
    {
        std::lock_guard<std::mutex> lock{_lck};
        if (_startCount > 0) {
            if (--_startCount == 0) {
                /* stop if we are now at 0 */
                _enableNotifier.Stop();
            }
        }
    }
};

}
}
}