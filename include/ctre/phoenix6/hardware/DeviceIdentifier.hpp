/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/CANBus.hpp"
#include <stdint.h>

namespace ctre {
namespace phoenix6 {
namespace hardware {

    /**
     * \brief The unique identifier for a device.
     */
    class DeviceIdentifier final {
    public:
        std::string network;
        std::string model;
        int deviceID{-1};
        uint32_t deviceHash;

        DeviceIdentifier() = default;
        DeviceIdentifier(int deviceID, std::string model, CANBus canbus);

        std::string ToString() const;
    };

}
}
}
