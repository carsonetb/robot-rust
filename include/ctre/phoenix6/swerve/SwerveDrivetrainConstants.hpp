/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/core/CorePigeon2.hpp"
#include <optional>

namespace ctre {
namespace phoenix6 {
namespace swerve {

/**
 * \brief Common constants for a swerve drivetrain.
 */
struct SwerveDrivetrainConstants {
    constexpr SwerveDrivetrainConstants() = default;

    /**
     * \brief Name of the CAN bus the swerve drive is on. Possible CAN bus strings
     * are:
     * 
     * - empty string or "rio" for the native roboRIO CAN bus
     * - CANivore name or serial number
     * - "*" for any CANivore seen by the program
     * 
     * Note that all devices must be on the same CAN bus.
     */
    std::string_view CANBusName = "rio";
    /**
     * \brief CAN ID of the Pigeon2 on the drivetrain.
     */
    int Pigeon2Id = 0;
    /**
     * \brief The configuration object to apply to the Pigeon2. This defaults to
     * null. If this remains null, then the Pigeon2 will not be configured (and
     * whatever configs are on it remain on it). If this is not null, the Pigeon2
     * will be overwritten with these configs.
     */
    std::optional<configs::Pigeon2Configuration> Pigeon2Configs = std::nullopt;
    
    /**
     * \brief Modifies the CANBusName parameter and returns itself.
     *
     * Name of the CAN bus the swerve drive is on. Possible CAN bus strings are:
     * 
     * - empty string or "rio" for the native roboRIO CAN bus
     * - CANivore name or serial number
     * - "*" for any CANivore seen by the program
     * 
     * Note that all devices must be on the same CAN bus.
     *
     * \param newCANBusName Parameter to modify
     * \returns this object
     */
    constexpr SwerveDrivetrainConstants &WithCANBusName(std::string_view newCANBusName)
    {
        this->CANBusName = newCANBusName;
        return *this;
    }
    
    /**
     * \brief Modifies the Pigeon2Id parameter and returns itself.
     *
     * CAN ID of the Pigeon2 on the drivetrain.
     *
     * \param newPigeon2Id Parameter to modify
     * \returns this object
     */
    constexpr SwerveDrivetrainConstants &WithPigeon2Id(int newPigeon2Id)
    {
        this->Pigeon2Id = newPigeon2Id;
        return *this;
    }
    
    /**
     * \brief Modifies the Pigeon2Configs parameter and returns itself.
     *
     * The configuration object to apply to the Pigeon2. This defaults to null. If
     * this remains null, then the Pigeon2 will not be configured (and whatever
     * configs are on it remain on it). If this is not null, the Pigeon2 will be
     * overwritten with these configs.
     *
     * \param newPigeon2Configs Parameter to modify
     * \returns this object
     */
    #if __cpp_lib_optional >= 202106L || (defined(__APPLE__) && __cplusplus >= 202002L)
    constexpr
    #endif
    SwerveDrivetrainConstants &WithPigeon2Configs(const std::optional<configs::Pigeon2Configuration>& newPigeon2Configs)
    {
        this->Pigeon2Configs = newPigeon2Configs;
        return *this;
    }
    
};

}
}
}
