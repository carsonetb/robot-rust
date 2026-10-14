/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs related to general CANdle features.
 * 
 * \details This includes configs such as disabling the 5V rail and
 *          the behavior of VBat output.
 */
class CANdleFeaturesConfigs : public ParentConfiguration {
public:
    constexpr CANdleFeaturesConfigs() = default;

    /**
     * \brief Whether the 5V rail is enabled. Disabling the 5V rail will
     * also turn off the onboard LEDs.
     * 
     */
    signals::Enable5VRailValue Enable5VRail = signals::Enable5VRailValue::Enabled;
    /**
     * \brief The behavior of the VBat output. CANdle supports modulating
     * VBat output for single-color LED strips.
     * 
     */
    signals::VBatOutputModeValue VBatOutputMode = signals::VBatOutputModeValue::On;
    /**
     * \brief Whether the Status LED is enabled when the CANdle is
     * actively being controlled.
     * 
     */
    signals::StatusLedWhenActiveValue StatusLedWhenActive = signals::StatusLedWhenActiveValue::Enabled;
    
    /**
     * \brief Modifies this configuration's Enable5VRail parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Whether the 5V rail is enabled. Disabling the 5V rail will also
     * turn off the onboard LEDs.
     * 
     *
     * \param newEnable5VRail Parameter to modify
     * \returns Itself
     */
    constexpr CANdleFeaturesConfigs &WithEnable5VRail(signals::Enable5VRailValue newEnable5VRail)
    {
        Enable5VRail = std::move(newEnable5VRail);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's VBatOutputMode parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The behavior of the VBat output. CANdle supports modulating VBat
     * output for single-color LED strips.
     * 
     *
     * \param newVBatOutputMode Parameter to modify
     * \returns Itself
     */
    constexpr CANdleFeaturesConfigs &WithVBatOutputMode(signals::VBatOutputModeValue newVBatOutputMode)
    {
        VBatOutputMode = std::move(newVBatOutputMode);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's StatusLedWhenActive parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Whether the Status LED is enabled when the CANdle is actively being
     * controlled.
     * 
     *
     * \param newStatusLedWhenActive Parameter to modify
     * \returns Itself
     */
    constexpr CANdleFeaturesConfigs &WithStatusLedWhenActive(signals::StatusLedWhenActiveValue newStatusLedWhenActive)
    {
        StatusLedWhenActive = std::move(newStatusLedWhenActive);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
