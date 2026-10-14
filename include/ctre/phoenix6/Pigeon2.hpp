/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/core/CorePigeon2.hpp"

namespace ctre {
namespace phoenix6 {
namespace hardware {

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

/**
 * Class description for the Pigeon 2 IMU sensor that measures orientation.
 */
class Pigeon2 : public core::CorePigeon2 {
public:
    Pigeon2(Pigeon2 const &) = delete;
    Pigeon2(Pigeon2 &&) noexcept : Pigeon2(0) {}

    /**
     * Constructs a new Pigeon 2 sensor object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner
     * \param canbus      The CAN bus this device is on
     */
    Pigeon2(int deviceId, CANBus canbus = {}) : CorePigeon2{deviceId, std::move(canbus)}
    {}

    /**
     * Constructs a new Pigeon 2 sensor object.
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
    Pigeon2(int deviceId, std::string canbus) : CorePigeon2{deviceId, std::move(canbus)}
    {}

    /**
     * \brief Constructs a stubbed-out Pigeon2, where all status signals, controls,
     * configs, etc. perform no action and immediately return OK. This can be used to
     * silence error messages for devices that have been completely removed from the robot.
     *
     * \returns Stubbed-out Pigeon2
     */
    static Pigeon2 None()
    {
        return Pigeon2{-1, CANBus{}};
    }
};

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(pop)
#endif

}
}
}
