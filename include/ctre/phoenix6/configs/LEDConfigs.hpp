/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include <units/dimensionless.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs related to CANdle LED control.
 * 
 * \details All the configs related to controlling LEDs with the
 *          CANdle, including LED strip type and brightness.
 */
class LEDConfigs : public ParentConfiguration {
public:
    constexpr LEDConfigs() = default;

    /**
     * \brief The type of LEDs that are being controlled.
     * 
     */
    signals::StripTypeValue StripType = signals::StripTypeValue::GRB;
    /**
     * \brief The brightness scalar for all LEDs controlled. All LED
     * values sent to the CANdle will be scaled by this config.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 1.0
     * - Units: scalar
     */
    units::dimensionless::scalar_t BrightnessScalar = 1.0;
    /**
     * \brief The behavior of the LEDs when the control signal is lost.
     * 
     */
    signals::LossOfSignalBehaviorValue LossOfSignalBehavior = signals::LossOfSignalBehaviorValue::KeepRunning;
    
    /**
     * \brief Modifies this configuration's StripType parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The type of LEDs that are being controlled.
     * 
     *
     * \param newStripType Parameter to modify
     * \returns Itself
     */
    constexpr LEDConfigs &WithStripType(signals::StripTypeValue newStripType)
    {
        StripType = std::move(newStripType);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's BrightnessScalar parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The brightness scalar for all LEDs controlled. All LED values sent
     * to the CANdle will be scaled by this config.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 1.0
     * - Units: scalar
     *
     * \param newBrightnessScalar Parameter to modify
     * \returns Itself
     */
    constexpr LEDConfigs &WithBrightnessScalar(units::dimensionless::scalar_t newBrightnessScalar)
    {
        BrightnessScalar = std::move(newBrightnessScalar);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's LossOfSignalBehavior parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The behavior of the LEDs when the control signal is lost.
     * 
     *
     * \param newLossOfSignalBehavior Parameter to modify
     * \returns Itself
     */
    constexpr LEDConfigs &WithLossOfSignalBehavior(signals::LossOfSignalBehaviorValue newLossOfSignalBehavior)
    {
        LossOfSignalBehavior = std::move(newLossOfSignalBehavior);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
