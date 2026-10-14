/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include <units/current.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs that affect Torque Current control types.
 * 
 * \details Includes the maximum and minimum applied torque output and
 *          the neutral deadband used during TorqueCurrentFOC
 *          requests.
 */
class TorqueCurrentConfigs : public ParentConfiguration {
public:
    constexpr TorqueCurrentConfigs() = default;

    /**
     * \brief Maximum (forward) output during torque current based control
     * modes.
     * 
     * - Minimum Value: -800
     * - Maximum Value: 800
     * - Default Value: 800
     * - Units: A
     */
    units::current::ampere_t PeakForwardTorqueCurrent = 800_A;
    /**
     * \brief Minimum (reverse) output during torque current based control
     * modes.
     * 
     * - Minimum Value: -800
     * - Maximum Value: 800
     * - Default Value: -800
     * - Units: A
     */
    units::current::ampere_t PeakReverseTorqueCurrent = -800_A;
    /**
     * \brief Configures the output deadband during torque current based
     * control modes.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 25
     * - Default Value: 0.0
     * - Units: A
     */
    units::current::ampere_t TorqueNeutralDeadband = 0.0_A;
    
    /**
     * \brief Modifies this configuration's PeakForwardTorqueCurrent parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum (forward) output during torque current based control modes.
     * 
     * - Minimum Value: -800
     * - Maximum Value: 800
     * - Default Value: 800
     * - Units: A
     *
     * \param newPeakForwardTorqueCurrent Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentConfigs &WithPeakForwardTorqueCurrent(units::current::ampere_t newPeakForwardTorqueCurrent)
    {
        PeakForwardTorqueCurrent = std::move(newPeakForwardTorqueCurrent);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakReverseTorqueCurrent parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Minimum (reverse) output during torque current based control modes.
     * 
     * - Minimum Value: -800
     * - Maximum Value: 800
     * - Default Value: -800
     * - Units: A
     *
     * \param newPeakReverseTorqueCurrent Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentConfigs &WithPeakReverseTorqueCurrent(units::current::ampere_t newPeakReverseTorqueCurrent)
    {
        PeakReverseTorqueCurrent = std::move(newPeakReverseTorqueCurrent);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's TorqueNeutralDeadband parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configures the output deadband during torque current based control
     * modes.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 25
     * - Default Value: 0.0
     * - Units: A
     *
     * \param newTorqueNeutralDeadband Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentConfigs &WithTorqueNeutralDeadband(units::current::ampere_t newTorqueNeutralDeadband)
    {
        TorqueNeutralDeadband = std::move(newTorqueNeutralDeadband);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
