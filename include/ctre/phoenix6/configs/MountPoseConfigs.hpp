/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include <units/angle.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs for Pigeon 2's Mount Pose configuration.
 * 
 * \details These configs allow the Pigeon2 to be mounted in whatever
 *          orientation that's desired and ensure the reported
 *          Yaw/Pitch/Roll is from the robot's reference.
 */
class MountPoseConfigs : public ParentConfiguration {
public:
    constexpr MountPoseConfigs() = default;

    /**
     * \brief The mounting calibration yaw-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     */
    units::angle::degree_t MountPoseYaw = 0_deg;
    /**
     * \brief The mounting calibration pitch-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     */
    units::angle::degree_t MountPosePitch = 0_deg;
    /**
     * \brief The mounting calibration roll-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     */
    units::angle::degree_t MountPoseRoll = 0_deg;
    
    /**
     * \brief Modifies this configuration's MountPoseYaw parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The mounting calibration yaw-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     *
     * \param newMountPoseYaw Parameter to modify
     * \returns Itself
     */
    constexpr MountPoseConfigs &WithMountPoseYaw(units::angle::degree_t newMountPoseYaw)
    {
        MountPoseYaw = std::move(newMountPoseYaw);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MountPosePitch parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The mounting calibration pitch-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     *
     * \param newMountPosePitch Parameter to modify
     * \returns Itself
     */
    constexpr MountPoseConfigs &WithMountPosePitch(units::angle::degree_t newMountPosePitch)
    {
        MountPosePitch = std::move(newMountPosePitch);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MountPoseRoll parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The mounting calibration roll-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     *
     * \param newMountPoseRoll Parameter to modify
     * \returns Itself
     */
    constexpr MountPoseConfigs &WithMountPoseRoll(units::angle::degree_t newMountPoseRoll)
    {
        MountPoseRoll = std::move(newMountPoseRoll);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
