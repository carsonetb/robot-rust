/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include <units/frequency.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs that affect the ToF sensor
 * 
 * \details Includes Update mode and frequency
 */
class ToFParamsConfigs : public ParentConfiguration {
public:
    constexpr ToFParamsConfigs() = default;

    /**
     * \brief Update mode of the CANrange. The CANrange supports
     * short-range and long-range detection at various update frequencies.
     * 
     */
    signals::UpdateModeValue UpdateMode = signals::UpdateModeValue::ShortRange100Hz;
    /**
     * \brief Rate at which the CANrange will take measurements. A lower
     * frequency may provide more stable readings but will reduce the data
     * rate of the sensor.
     * 
     * - Minimum Value: 5
     * - Maximum Value: 50
     * - Default Value: 50
     * - Units: Hz
     */
    units::frequency::hertz_t UpdateFrequency = 50_Hz;
    
    /**
     * \brief Modifies this configuration's UpdateMode parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Update mode of the CANrange. The CANrange supports short-range and
     * long-range detection at various update frequencies.
     * 
     *
     * \param newUpdateMode Parameter to modify
     * \returns Itself
     */
    constexpr ToFParamsConfigs &WithUpdateMode(signals::UpdateModeValue newUpdateMode)
    {
        UpdateMode = std::move(newUpdateMode);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's UpdateFrequency parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Rate at which the CANrange will take measurements. A lower
     * frequency may provide more stable readings but will reduce the data
     * rate of the sensor.
     * 
     * - Minimum Value: 5
     * - Maximum Value: 50
     * - Default Value: 50
     * - Units: Hz
     *
     * \param newUpdateFrequency Parameter to modify
     * \returns Itself
     */
    constexpr ToFParamsConfigs &WithUpdateFrequency(units::frequency::hertz_t newUpdateFrequency)
    {
        UpdateFrequency = std::move(newUpdateFrequency);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
