/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"


namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs to enable/disable various features of the Pigeon2.
 * 
 * \details These configs allow the user to enable or disable various
 *          aspects of the Pigeon2.
 */
class Pigeon2FeaturesConfigs : public ParentConfiguration {
public:
    constexpr Pigeon2FeaturesConfigs() = default;

    /**
     * \brief Turns on or off the magnetometer fusing for 9-axis. FRC
     * users are not recommended to turn this on, as the magnetic
     * influence of the robot will likely negatively affect the
     * performance of the Pigeon2.
     * 
     * - Default Value: False
     */
    bool EnableCompass = false;
    /**
     * \brief Disables using the temperature compensation feature.
     * 
     * - Default Value: False
     */
    bool DisableTemperatureCompensation = false;
    /**
     * \brief Disables using the no-motion calibration feature.
     * 
     * - Default Value: False
     */
    bool DisableNoMotionCalibration = false;
    
    /**
     * \brief Modifies this configuration's EnableCompass parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Turns on or off the magnetometer fusing for 9-axis. FRC users are
     * not recommended to turn this on, as the magnetic influence of the
     * robot will likely negatively affect the performance of the Pigeon2.
     * 
     * - Default Value: False
     *
     * \param newEnableCompass Parameter to modify
     * \returns Itself
     */
    constexpr Pigeon2FeaturesConfigs &WithEnableCompass(bool newEnableCompass)
    {
        EnableCompass = std::move(newEnableCompass);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DisableTemperatureCompensation parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Disables using the temperature compensation feature.
     * 
     * - Default Value: False
     *
     * \param newDisableTemperatureCompensation Parameter to modify
     * \returns Itself
     */
    constexpr Pigeon2FeaturesConfigs &WithDisableTemperatureCompensation(bool newDisableTemperatureCompensation)
    {
        DisableTemperatureCompensation = std::move(newDisableTemperatureCompensation);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DisableNoMotionCalibration parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Disables using the no-motion calibration feature.
     * 
     * - Default Value: False
     *
     * \param newDisableNoMotionCalibration Parameter to modify
     * \returns Itself
     */
    constexpr Pigeon2FeaturesConfigs &WithDisableNoMotionCalibration(bool newDisableNoMotionCalibration)
    {
        DisableNoMotionCalibration = std::move(newDisableNoMotionCalibration);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
