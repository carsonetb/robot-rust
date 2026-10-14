/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include <units/time.h>
#include <units/voltage.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs that affect Voltage control types.
 * 
 * \details Includes peak output voltages and other configs affecting
 *          voltage measurements.
 */
class VoltageConfigs : public ParentConfiguration {
public:
    constexpr VoltageConfigs() = default;

    /**
     * \brief The time constant (in seconds) of the low-pass filter for
     * the supply voltage.
     * 
     * \details This impacts the filtering for the reported supply
     * voltage, and any control strategies that use the supply voltage
     * (such as voltage control on a motor controller).
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 0.1
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t SupplyVoltageTimeConstant = 0_s;
    /**
     * \brief Maximum (forward) output during voltage based control modes.
     * 
     * - Minimum Value: -32
     * - Maximum Value: 32
     * - Default Value: 16
     * - Units: V
     */
    units::voltage::volt_t PeakForwardVoltage = 16_V;
    /**
     * \brief Minimum (reverse) output during voltage based control modes.
     * 
     * - Minimum Value: -32
     * - Maximum Value: 32
     * - Default Value: -16
     * - Units: V
     */
    units::voltage::volt_t PeakReverseVoltage = -16_V;
    
    /**
     * \brief Modifies this configuration's SupplyVoltageTimeConstant parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The time constant (in seconds) of the low-pass filter for the
     * supply voltage.
     * 
     * \details This impacts the filtering for the reported supply
     * voltage, and any control strategies that use the supply voltage
     * (such as voltage control on a motor controller).
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 0.1
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newSupplyVoltageTimeConstant Parameter to modify
     * \returns Itself
     */
    constexpr VoltageConfigs &WithSupplyVoltageTimeConstant(units::time::second_t newSupplyVoltageTimeConstant)
    {
        SupplyVoltageTimeConstant = std::move(newSupplyVoltageTimeConstant);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakForwardVoltage parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum (forward) output during voltage based control modes.
     * 
     * - Minimum Value: -32
     * - Maximum Value: 32
     * - Default Value: 16
     * - Units: V
     *
     * \param newPeakForwardVoltage Parameter to modify
     * \returns Itself
     */
    constexpr VoltageConfigs &WithPeakForwardVoltage(units::voltage::volt_t newPeakForwardVoltage)
    {
        PeakForwardVoltage = std::move(newPeakForwardVoltage);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakReverseVoltage parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Minimum (reverse) output during voltage based control modes.
     * 
     * - Minimum Value: -32
     * - Maximum Value: 32
     * - Default Value: -16
     * - Units: V
     *
     * \param newPeakReverseVoltage Parameter to modify
     * \returns Itself
     */
    constexpr VoltageConfigs &WithPeakReverseVoltage(units::voltage::volt_t newPeakReverseVoltage)
    {
        PeakReverseVoltage = std::move(newPeakReverseVoltage);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
