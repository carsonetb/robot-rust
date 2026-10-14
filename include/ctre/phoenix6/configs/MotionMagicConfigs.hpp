/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/unit/pid_ff.h"
#include <units/angular_acceleration.h>
#include <units/angular_jerk.h>
#include <units/angular_velocity.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs for Motion Magic®.
 * 
 * \details Includes Velocity, Acceleration, Jerk, and Expo
 *          parameters.
 */
class MotionMagicConfigs : public ParentConfiguration {
public:
    constexpr MotionMagicConfigs() = default;

    /**
     * \brief This is the maximum velocity Motion Magic® based control
     * modes are allowed to use.  Motion Magic® Velocity control modes do
     * not use this config.
     * 
     * When using Motion Magic® Expo control modes, setting this to 0 will
     * allow the profile to run to the max possible velocity based on
     * Expo_kV.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec
     */
    units::angular_velocity::turns_per_second_t MotionMagicCruiseVelocity = 0_tps;
    /**
     * \brief This is the target acceleration Motion Magic® based control
     * modes are allowed to use.  Motion Magic® Expo control modes do not
     * use this config.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec²
     */
    units::angular_acceleration::turns_per_second_squared_t MotionMagicAcceleration = 0_tr_per_s_sq;
    /**
     * \brief This is the target jerk (acceleration derivative) Motion
     * Magic® based control modes are allowed to use.  Motion Magic® Expo
     * control modes do not use this config.  This allows Motion Magic® to
     * generate S-Curve profiles.
     * 
     * Jerk is optional; if this is set to zero, then Motion Magic® will
     * not apply a Jerk limit.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec³
     */
    units::angular_jerk::turns_per_second_cubed_t MotionMagicJerk = 0_tr_per_s_cu;
    /**
     * \brief This is the target kV used only by Motion Magic® Expo
     * control modes. Unlike the kV slot gain, this is always in units of
     * V/rps.
     * 
     * This represents the amount of voltage necessary to hold a velocity.
     * In terms of the Motion Magic® Expo profile, a higher kV results in
     * a slower maximum velocity.
     * 
     * - Minimum Value: 0.001
     * - Maximum Value: 100
     * - Default Value: 0.12
     * - Units: V/rps
     */
    ctre::unit::volts_per_turn_per_second_t MotionMagicExpo_kV = 0.12_V / 1_tps;
    /**
     * \brief This is the target kA used only by Motion Magic® Expo
     * control modes. Unlike the kA slot gain, this is always in units of
     * V/rps².
     * 
     * This represents the amount of voltage necessary to achieve an
     * acceleration. In terms of the Motion Magic® Expo profile, a higher
     * kA results in a slower acceleration.
     * 
     * - Minimum Value: 1e-05
     * - Maximum Value: 100
     * - Default Value: 0.1
     * - Units: V/rps²
     */
    ctre::unit::volts_per_turn_per_second_squared_t MotionMagicExpo_kA = 0.1_V / 1_tr_per_s_sq;
    
    /**
     * \brief Modifies this configuration's MotionMagicCruiseVelocity parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This is the maximum velocity Motion Magic® based control modes are
     * allowed to use.  Motion Magic® Velocity control modes do not use
     * this config.
     * 
     * When using Motion Magic® Expo control modes, setting this to 0 will
     * allow the profile to run to the max possible velocity based on
     * Expo_kV.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec
     *
     * \param newMotionMagicCruiseVelocity Parameter to modify
     * \returns Itself
     */
    constexpr MotionMagicConfigs &WithMotionMagicCruiseVelocity(units::angular_velocity::turns_per_second_t newMotionMagicCruiseVelocity)
    {
        MotionMagicCruiseVelocity = std::move(newMotionMagicCruiseVelocity);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MotionMagicAcceleration parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This is the target acceleration Motion Magic® based control modes
     * are allowed to use.  Motion Magic® Expo control modes do not use
     * this config.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec²
     *
     * \param newMotionMagicAcceleration Parameter to modify
     * \returns Itself
     */
    constexpr MotionMagicConfigs &WithMotionMagicAcceleration(units::angular_acceleration::turns_per_second_squared_t newMotionMagicAcceleration)
    {
        MotionMagicAcceleration = std::move(newMotionMagicAcceleration);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MotionMagicJerk parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This is the target jerk (acceleration derivative) Motion Magic®
     * based control modes are allowed to use.  Motion Magic® Expo control
     * modes do not use this config.  This allows Motion Magic® to
     * generate S-Curve profiles.
     * 
     * Jerk is optional; if this is set to zero, then Motion Magic® will
     * not apply a Jerk limit.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec³
     *
     * \param newMotionMagicJerk Parameter to modify
     * \returns Itself
     */
    constexpr MotionMagicConfigs &WithMotionMagicJerk(units::angular_jerk::turns_per_second_cubed_t newMotionMagicJerk)
    {
        MotionMagicJerk = std::move(newMotionMagicJerk);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MotionMagicExpo_kV parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This is the target kV used only by Motion Magic® Expo control
     * modes. Unlike the kV slot gain, this is always in units of V/rps.
     * 
     * This represents the amount of voltage necessary to hold a velocity.
     * In terms of the Motion Magic® Expo profile, a higher kV results in
     * a slower maximum velocity.
     * 
     * - Minimum Value: 0.001
     * - Maximum Value: 100
     * - Default Value: 0.12
     * - Units: V/rps
     *
     * \param newMotionMagicExpo_kV Parameter to modify
     * \returns Itself
     */
    constexpr MotionMagicConfigs &WithMotionMagicExpo_kV(ctre::unit::volts_per_turn_per_second_t newMotionMagicExpo_kV)
    {
        MotionMagicExpo_kV = std::move(newMotionMagicExpo_kV);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MotionMagicExpo_kA parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This is the target kA used only by Motion Magic® Expo control
     * modes. Unlike the kA slot gain, this is always in units of V/rps².
     * 
     * This represents the amount of voltage necessary to achieve an
     * acceleration. In terms of the Motion Magic® Expo profile, a higher
     * kA results in a slower acceleration.
     * 
     * - Minimum Value: 1e-05
     * - Maximum Value: 100
     * - Default Value: 0.1
     * - Units: V/rps²
     *
     * \param newMotionMagicExpo_kA Parameter to modify
     * \returns Itself
     */
    constexpr MotionMagicConfigs &WithMotionMagicExpo_kA(ctre::unit::volts_per_turn_per_second_squared_t newMotionMagicExpo_kA)
    {
        MotionMagicExpo_kA = std::move(newMotionMagicExpo_kA);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
