/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix6/HootReplay.hpp"
#include <string>

namespace ctre {
namespace phoenix6 {

/**
 * \brief Class for getting information about an available CAN bus.
 */
class CANBus {
public:
    /**
     * \brief Contains status information about a CAN bus.
     */
    struct CANBusStatus {
        /**
         * \brief Status code response of getting the data
         */
        ctre::phoenix::StatusCode Status;

        /**
         * \brief CAN bus utilization, from 0.0 to 1.0
         */
        float BusUtilization;
        /**
         * \brief Bus off count
         */
        uint32_t BusOffCount;
        /**
         * \brief Transmit buffer full count
         */
        uint32_t TxFullCount;
        /**
         * \brief Receive Error Counter (REC)
         */
        uint32_t REC;
        /**
         * \brief Transmit Error Counter (TEC)
         */
        uint32_t TEC;
    };

private:
    std::string_view _name;

public:
    /**
     * \brief Creates a new CAN bus with the given name.
     *
     * \param canbus    Name of the CAN bus. Possible CAN bus strings are:
     *                  - "rio" for the native roboRIO CAN bus
     *                  - CANivore name or serial number
     *                  - SocketCAN interface (non-FRC Linux only)
     *                  - "*" for any CANivore seen by the program
     *                  - empty string (default) to select the default for the system:
     *                    - "rio" on roboRIO
     *                    - "can0" on Linux
     *                    - "*" on Windows
     */
    constexpr CANBus(std::string_view canbus = "") :
        _name{canbus}
    {}

    /**
     * \brief Creates a new CAN bus with the given name, and loads an associated
     * hoot file for replay (equivalent to HootReplay#LoadFile).
     *
     * Only one hoot log may be replayed at a time. As a result, only one
     * CAN bus should be constructed with a hoot file.
     *
     * When using relative paths, the file path is typically relative
     * to the top-level folder of the robot project.
     *
     * \param canbus    Name of the CAN bus. Possible CAN bus strings are:
     *                  - "rio" for the native roboRIO CAN bus
     *                  - CANivore name or serial number
     *                  - SocketCAN interface (non-FRC Linux only)
     *                  - "*" for any CANivore seen by the program
     *                  - empty string (default) to select the default for the system:
     *                    - "rio" on roboRIO
     *                    - "can0" on Linux
     *                    - "*" on Windows
     * \param hootFilepath Path and name of the hoot file to load
     */
    CANBus(std::string_view canbus, char const *hootFilepath) :
        CANBus{canbus}
    {
        HootReplay::LoadFile(hootFilepath);
    }

    /**
     * \brief Get the name used to construct this CAN bus.
     *
     * \returns Name of the CAN bus
     */
    constexpr std::string_view GetName() const
    {
        return _name;
    }

    /**
     * \brief Gets whether the CAN bus is a CAN FD network.
     *
     * \returns True if the CAN bus is CAN FD
     */
    bool IsNetworkFD() const;
    /**
     * \brief Gets the status of the CAN bus, including the
     * bus utilization and the error counters.
     *
     * This can block for up to 0.001 seconds (1 ms).
     *
     * \returns Status of the CAN bus
     */
    CANBusStatus GetStatus() const;

    /**
     * \brief Gets whether the CAN bus is a CAN FD network.
     *
     * \deprecated The CANBus static methods are deprecated
     * for removal in 2026. Construct a new CANBus instance
     * and call #IsNetworkFD() instead.
     *
     * \param canbus Name of the CAN bus
     * \returns True if the CAN bus is CAN FD
     */
    [[deprecated("The CANBus static methods are deprecated for removal in 2026."
                "Construct a new CANBus instance and call IsNetworkFD() instead.")]]
    static bool IsNetworkFD(std::string const &canbus)
    {
        return CANBus{canbus}.IsNetworkFD();
    }
    /**
     * \brief Gets the status of the CAN bus, including the
     * bus utilization and the error counters.
     *
     * \deprecated The CANBus static methods are deprecated
     * for removal in 2026. Construct a new CANBus instance
     * and call #GetStatus() instead.
     *
     * \param canbus Name of the CAN bus
     * \returns Status of the CAN bus
     */
    [[deprecated("The CANBus static methods are deprecated for removal in 2026."
                "Construct a new CANBus instance and call GetStatus() instead.")]]
    static CANBusStatus GetStatus(std::string const &canbus)
    {
        return CANBus{canbus}.GetStatus();
    }
};

}
}
