/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include <units/dimensionless.h>
#include <units/length.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs that affect the ToF Proximity detection
 * 
 * \details Includes proximity mode and the threshold for simple
 *          detection
 */
class ProximityParamsConfigs : public ParentConfiguration {
public:
    constexpr ProximityParamsConfigs() = default;

    /**
     * \brief Threshold for object detection.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 4
     * - Default Value: 0.4
     * - Units: m
     */
    units::length::meter_t ProximityThreshold = 0.4_m;
    /**
     * \brief How far above and below the threshold the distance needs to
     * be to trigger undetected and detected, respectively. This is used
     * to prevent bouncing between the detected and undetected states for
     * objects on the threshold.
     * 
     * If the threshold is set to 0.1 meters, and the hysteresis is 0.01
     * meters, then an object needs to be within 0.09 meters to be
     * detected. After the object is first detected, the distance then
     * needs to exceed 0.11 meters to become undetected again.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0.01
     * - Units: m
     */
    units::length::meter_t ProximityHysteresis = 0.01_m;
    /**
     * \brief The minimum allowable signal strength before determining the
     * measurement is valid.
     * 
     * If the signal strength is particularly low, this typically means
     * the object is far away and there's fewer total samples to derive
     * the distance from. Set this value to be below the lowest strength
     * you see when you're detecting an object with the CANrange; the
     * default of 2500 is typically acceptable in most cases.
     * 
     * - Minimum Value: 1
     * - Maximum Value: 15000
     * - Default Value: 2500
     * - Units: 
     */
    units::dimensionless::scalar_t MinSignalStrengthForValidMeasurement = 2500;
    
    /**
     * \brief Modifies this configuration's ProximityThreshold parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Threshold for object detection.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 4
     * - Default Value: 0.4
     * - Units: m
     *
     * \param newProximityThreshold Parameter to modify
     * \returns Itself
     */
    constexpr ProximityParamsConfigs &WithProximityThreshold(units::length::meter_t newProximityThreshold)
    {
        ProximityThreshold = std::move(newProximityThreshold);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ProximityHysteresis parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * How far above and below the threshold the distance needs to be to
     * trigger undetected and detected, respectively. This is used to
     * prevent bouncing between the detected and undetected states for
     * objects on the threshold.
     * 
     * If the threshold is set to 0.1 meters, and the hysteresis is 0.01
     * meters, then an object needs to be within 0.09 meters to be
     * detected. After the object is first detected, the distance then
     * needs to exceed 0.11 meters to become undetected again.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0.01
     * - Units: m
     *
     * \param newProximityHysteresis Parameter to modify
     * \returns Itself
     */
    constexpr ProximityParamsConfigs &WithProximityHysteresis(units::length::meter_t newProximityHysteresis)
    {
        ProximityHysteresis = std::move(newProximityHysteresis);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MinSignalStrengthForValidMeasurement parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The minimum allowable signal strength before determining the
     * measurement is valid.
     * 
     * If the signal strength is particularly low, this typically means
     * the object is far away and there's fewer total samples to derive
     * the distance from. Set this value to be below the lowest strength
     * you see when you're detecting an object with the CANrange; the
     * default of 2500 is typically acceptable in most cases.
     * 
     * - Minimum Value: 1
     * - Maximum Value: 15000
     * - Default Value: 2500
     * - Units: 
     *
     * \param newMinSignalStrengthForValidMeasurement Parameter to modify
     * \returns Itself
     */
    constexpr ProximityParamsConfigs &WithMinSignalStrengthForValidMeasurement(units::dimensionless::scalar_t newMinSignalStrengthForValidMeasurement)
    {
        MinSignalStrengthForValidMeasurement = std::move(newMinSignalStrengthForValidMeasurement);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
