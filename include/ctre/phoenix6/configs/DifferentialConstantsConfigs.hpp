/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include <units/current.h>
#include <units/dimensionless.h>
#include <units/voltage.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs related to constants used for differential control
 *        of a mechanism.
 * 
 * \details Includes the differential peak outputs.
 */
class DifferentialConstantsConfigs : public ParentConfiguration {
public:
    constexpr DifferentialConstantsConfigs() = default;

    /**
     * \brief Maximum differential output during duty cycle based
     * differential control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 1.0
     * - Units: fractional
     */
    units::dimensionless::scalar_t PeakDifferentialDutyCycle = 1.0;
    /**
     * \brief Maximum differential output during voltage based
     * differential control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 32
     * - Default Value: 16
     * - Units: V
     */
    units::voltage::volt_t PeakDifferentialVoltage = 16_V;
    /**
     * \brief Maximum differential output during torque current based
     * differential control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 800
     * - Default Value: 800
     * - Units: A
     */
    units::current::ampere_t PeakDifferentialTorqueCurrent = 800_A;
    
    /**
     * \brief Modifies this configuration's PeakDifferentialDutyCycle parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum differential output during duty cycle based differential
     * control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 1.0
     * - Units: fractional
     *
     * \param newPeakDifferentialDutyCycle Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialConstantsConfigs &WithPeakDifferentialDutyCycle(units::dimensionless::scalar_t newPeakDifferentialDutyCycle)
    {
        PeakDifferentialDutyCycle = std::move(newPeakDifferentialDutyCycle);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakDifferentialVoltage parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum differential output during voltage based differential
     * control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 32
     * - Default Value: 16
     * - Units: V
     *
     * \param newPeakDifferentialVoltage Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialConstantsConfigs &WithPeakDifferentialVoltage(units::voltage::volt_t newPeakDifferentialVoltage)
    {
        PeakDifferentialVoltage = std::move(newPeakDifferentialVoltage);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakDifferentialTorqueCurrent parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum differential output during torque current based
     * differential control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 800
     * - Default Value: 800
     * - Units: A
     *
     * \param newPeakDifferentialTorqueCurrent Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialConstantsConfigs &WithPeakDifferentialTorqueCurrent(units::current::ampere_t newPeakDifferentialTorqueCurrent)
    {
        PeakDifferentialTorqueCurrent = std::move(newPeakDifferentialTorqueCurrent);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
