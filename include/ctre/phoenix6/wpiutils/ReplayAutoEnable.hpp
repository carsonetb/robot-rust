/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/HootReplay.hpp"
#include "frc/simulation/DriverStationSim.h"
#include "frc/Notifier.h"
#include <mutex>

namespace ctre {
namespace phoenix6 {
namespace wpiutils {

class ReplayAutoEnable {
public:
    static ReplayAutoEnable &GetInstance()
    {
        static ReplayAutoEnable *replayAutoEnable = new ReplayAutoEnable{};
        return *replayAutoEnable;
    }

private:
    std::mutex _lck;
    frc::Notifier _enableNotifier;
    uint32_t _startCount = 0;

    ReplayAutoEnable() :
        _enableNotifier{[] {
            if (HootReplay::IsPlaying()) {
                auto enableSig = HootReplay::GetBoolean("RobotEnable");
                if (enableSig.status.IsOK()) {
                    frc::sim::DriverStationSim::SetEnabled(enableSig.value);
                }

                auto robotModeSig = HootReplay::GetString("RobotMode");
                if (robotModeSig.status.IsOK()) {
                    if (robotModeSig.value == "Autonomous") {
                        frc::sim::DriverStationSim::SetAutonomous(true);
                        frc::sim::DriverStationSim::SetTest(false);
                    } else if (robotModeSig.value == "Test") {
                        frc::sim::DriverStationSim::SetAutonomous(false);
                        frc::sim::DriverStationSim::SetTest(true);
                    } else {
                        frc::sim::DriverStationSim::SetAutonomous(false);
                        frc::sim::DriverStationSim::SetTest(false);
                    }
                }

                frc::sim::DriverStationSim::NotifyNewData();
            }
        }}
    {}

public:
    /**
     * \brief Starts automatically enabling the robot in replay.
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
     * \brief Stops automatically enabling the robot in replay.
     * The replay enable will only be stopped when all actuators
     * have requested to stop the replay enable.
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