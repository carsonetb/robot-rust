/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/core/CoreCANcoder.hpp"

namespace ctre {
namespace phoenix6 {
namespace hardware {

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

/**
 * Class for CANcoder, a CAN based magnetic encoder that provides absolute and
 * relative position along with filtered velocity.
 */
class CANcoder : public core::CoreCANcoder {
public:
    CANcoder(CANcoder const &) = delete;
    CANcoder(CANcoder &&) noexcept : CANcoder(0) {}

    /**
     * Constructs a new CANcoder object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner
     * \param canbus      The CAN bus this device is on
     */
    CANcoder(int deviceId, CANBus canbus = {}) : CoreCANcoder{deviceId, std::move(canbus)}
    {}

    /**
     * Constructs a new CANcoder object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner.
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
    CANcoder(int deviceId, std::string canbus) : CoreCANcoder{deviceId, std::move(canbus)}
    {}

    /**
     * \brief Constructs a stubbed-out CANcoder, where all status signals, controls,
     * configs, etc. perform no action and immediately return OK. This can be used to
     * silence error messages for devices that have been completely removed from the robot.
     *
     * \returns Stubbed-out CANcoder
     */
    static CANcoder None()
    {
        return CANcoder{-1, CANBus{}};
    }
};

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(pop)
#endif

}
}
}
