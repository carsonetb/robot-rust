/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/core/CoreCANdle.hpp"

namespace ctre {
namespace phoenix6 {
namespace hardware {

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

/**
 * Class for CTR Electronics' CANdle® branded device,
 * a device that controls LEDs over the CAN bus.
 */
class CANdle : public core::CoreCANdle {
public:
    /** The number of animation slots. */
    static constexpr int kAnimSlotCount = 8;

    /**
     * Constructs a new CANdle object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner
     * \param canbus      The CAN bus this device is on
     */
    CANdle(int deviceId, CANBus canbus = {}) : CoreCANdle{deviceId, std::move(canbus)}
    {}

    /**
     * Constructs a new CANdle object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner
     * \param canbus      Name of the CAN bus this device is on. Possible CAN bus strings are:
     *                    - "rio" for the native roboRIO CAN bus
     *                    - CANivore name or serial number
     *                    - SocketCAN interface (non-FRC Linux only)
     *                    - "*" for any CANivore seen by the program
     *                    - empty string (default) to select the default for the system:
     *                      - "rio" on roboRIO
     *                      - "can0" on Linux
     *                      - "*" on Windows
     *
     * \deprecated Constructing devices with a CAN bus string is deprecated for removal
     * in the 2027 season. Construct devices using a CANBus instance instead.
     */
    [[deprecated(
        "Constructing devices with a CAN bus string is deprecated for removal "
        "in the 2027 season. Construct devices using a CANBus instance instead."
    )]]
    CANdle(int deviceId, std::string canbus) : CoreCANdle{deviceId, std::move(canbus)}
    {}

    /**
     * \brief Constructs a stubbed-out CANdle, where all status signals, controls,
     * configs, etc. perform no action and immediately return OK. This can be used to
     * silence error messages for devices that have been completely removed from the robot.
     *
     * \returns Stubbed-out CANdle
     */
    static CANdle None()
    {
        return CANdle{-1, CANBus{}};
    }

    /**
     * \brief Clears all animations on the CANdle. This is equivalent to applying a
     * controls#EmptyAnimation to all the animation slots on the CANdle.
     *
     * \returns Status code of the first failed control call, or OK if all succeeded
     */
    ctre::phoenix::StatusCode ClearAllAnimations();
};

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(pop)
#endif

}
}
}