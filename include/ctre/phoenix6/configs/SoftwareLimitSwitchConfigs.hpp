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
 * \brief Configs that affect how software-limit switches behave.
 * 
 * \details Includes enabling software-limit switches and the
 *          threshold at which they are tripped.
 */
class SoftwareLimitSwitchConfigs : public ParentConfiguration {
public:
    constexpr SoftwareLimitSwitchConfigs() = default;

    /**
     * \brief If enabled, the motor output is set to neutral if position
     * exceeds ForwardSoftLimitThreshold and forward output is requested.
     * 
     * - Default Value: False
     */
    bool ForwardSoftLimitEnable = false;
    /**
     * \brief If enabled, the motor output is set to neutral if position
     * exceeds ReverseSoftLimitThreshold and reverse output is requested.
     * 
     * - Default Value: False
     */
    bool ReverseSoftLimitEnable = false;
    /**
     * \brief Position threshold for forward soft limit features.
     * ForwardSoftLimitEnable must be enabled for this to take effect.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     */
    units::angle::turn_t ForwardSoftLimitThreshold = 0_tr;
    /**
     * \brief Position threshold for reverse soft limit features.
     * ReverseSoftLimitEnable must be enabled for this to take effect.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     */
    units::angle::turn_t ReverseSoftLimitThreshold = 0_tr;
    
    /**
     * \brief Modifies this configuration's ForwardSoftLimitEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If enabled, the motor output is set to neutral if position exceeds
     * ForwardSoftLimitThreshold and forward output is requested.
     * 
     * - Default Value: False
     *
     * \param newForwardSoftLimitEnable Parameter to modify
     * \returns Itself
     */
    constexpr SoftwareLimitSwitchConfigs &WithForwardSoftLimitEnable(bool newForwardSoftLimitEnable)
    {
        ForwardSoftLimitEnable = std::move(newForwardSoftLimitEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ReverseSoftLimitEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If enabled, the motor output is set to neutral if position exceeds
     * ReverseSoftLimitThreshold and reverse output is requested.
     * 
     * - Default Value: False
     *
     * \param newReverseSoftLimitEnable Parameter to modify
     * \returns Itself
     */
    constexpr SoftwareLimitSwitchConfigs &WithReverseSoftLimitEnable(bool newReverseSoftLimitEnable)
    {
        ReverseSoftLimitEnable = std::move(newReverseSoftLimitEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ForwardSoftLimitThreshold parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Position threshold for forward soft limit features.
     * ForwardSoftLimitEnable must be enabled for this to take effect.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     *
     * \param newForwardSoftLimitThreshold Parameter to modify
     * \returns Itself
     */
    constexpr SoftwareLimitSwitchConfigs &WithForwardSoftLimitThreshold(units::angle::turn_t newForwardSoftLimitThreshold)
    {
        ForwardSoftLimitThreshold = std::move(newForwardSoftLimitThreshold);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ReverseSoftLimitThreshold parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Position threshold for reverse soft limit features.
     * ReverseSoftLimitEnable must be enabled for this to take effect.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     *
     * \param newReverseSoftLimitThreshold Parameter to modify
     * \returns Itself
     */
    constexpr SoftwareLimitSwitchConfigs &WithReverseSoftLimitThreshold(units::angle::turn_t newReverseSoftLimitThreshold)
    {
        ReverseSoftLimitThreshold = std::move(newReverseSoftLimitThreshold);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
