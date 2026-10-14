/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include <units/current.h>
#include <units/time.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs that directly affect current limiting features.
 * 
 * \details Contains the supply/stator current limit thresholds and
 *          whether to enable them.
 */
class CurrentLimitsConfigs : public ParentConfiguration {
public:
    constexpr CurrentLimitsConfigs() = default;

    /**
     * \brief The amount of current allowed in the motor (motoring and
     * regen current).  Note this requires StatorCurrentLimitEnable to be
     * true.
     * 
     * For torque current control, this is applied in addition to the
     * PeakForwardTorqueCurrent and PeakReverseTorqueCurrent in
     * TorqueCurrentConfigs.
     * 
     * Stator current is directly proportional to torque, so this limit
     * can be used to restrict the torque output of the motor, such as
     * preventing wheel slip for a drivetrain.  Additionally, stator
     * current limits can prevent brownouts during acceleration; supply
     * current will never exceed the stator current limit and is often
     * significantly lower than stator current.
     * 
     * A reasonable starting point for a stator current limit is 120 A,
     * with values commonly ranging from 80-160 A. Mechanisms with a hard
     * stop may need a smaller limit to reduce the torque applied when
     * running into the hard stop.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 800.0
     * - Default Value: 120
     * - Units: A
     */
    units::current::ampere_t StatorCurrentLimit = 120_A;
    /**
     * \brief Enable motor stator current limiting.
     * 
     * - Default Value: True
     */
    bool StatorCurrentLimitEnable = true;
    /**
     * \brief The absolute maximum amount of supply current allowed.  Note
     * this requires SupplyCurrentLimitEnable to be true.  Use
     * SupplyCurrentLowerLimit and SupplyCurrentLowerTime to reduce the
     * supply current limit after the time threshold is exceeded.
     * 
     * Supply current is the current drawn from the battery, so this limit
     * can be used to prevent breaker trips and improve battery longevity.
     *  Additionally, in scenarios where the robot experiences brownouts
     * despite configuring stator current limits, a supply current limit
     * can further help avoid brownouts. However, it is important to note
     * that such brownouts may be caused by a bad battery or poor power
     * wiring.
     * 
     * A reasonable starting point for a supply current limit is 70 A with
     * a lower limit of 40 A after 1.0 second. Supply current limits
     * commonly range from 20-80 A depending on the breaker used.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 800.0
     * - Default Value: 70
     * - Units: A
     */
    units::current::ampere_t SupplyCurrentLimit = 70_A;
    /**
     * \brief Enable motor supply current limiting.
     * 
     * - Default Value: True
     */
    bool SupplyCurrentLimitEnable = true;
    /**
     * \brief The amount of supply current allowed after the regular
     * SupplyCurrentLimit is active for longer than
     * SupplyCurrentLowerTime.  This allows higher current draws for a
     * fixed period of time before reducing the current limit to protect
     * breakers.  This has no effect if SupplyCurrentLimit is lower than
     * this value or SupplyCurrentLowerTime is 0.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 500
     * - Default Value: 40
     * - Units: A
     */
    units::current::ampere_t SupplyCurrentLowerLimit = 40_A;
    /**
     * \brief Reduces supply current to the SupplyCurrentLowerLimit after
     * limiting to SupplyCurrentLimit for this period of time.  If this is
     * set to 0, SupplyCurrentLowerLimit will be ignored.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 5.0
     * - Default Value: 1.0
     * - Units: seconds
     */
    units::time::second_t SupplyCurrentLowerTime = 1.0_s;
    
    /**
     * \brief Modifies this configuration's StatorCurrentLimit parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The amount of current allowed in the motor (motoring and regen
     * current).  Note this requires StatorCurrentLimitEnable to be true.
     * 
     * For torque current control, this is applied in addition to the
     * PeakForwardTorqueCurrent and PeakReverseTorqueCurrent in
     * TorqueCurrentConfigs.
     * 
     * Stator current is directly proportional to torque, so this limit
     * can be used to restrict the torque output of the motor, such as
     * preventing wheel slip for a drivetrain.  Additionally, stator
     * current limits can prevent brownouts during acceleration; supply
     * current will never exceed the stator current limit and is often
     * significantly lower than stator current.
     * 
     * A reasonable starting point for a stator current limit is 120 A,
     * with values commonly ranging from 80-160 A. Mechanisms with a hard
     * stop may need a smaller limit to reduce the torque applied when
     * running into the hard stop.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 800.0
     * - Default Value: 120
     * - Units: A
     *
     * \param newStatorCurrentLimit Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithStatorCurrentLimit(units::current::ampere_t newStatorCurrentLimit)
    {
        StatorCurrentLimit = std::move(newStatorCurrentLimit);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's StatorCurrentLimitEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Enable motor stator current limiting.
     * 
     * - Default Value: True
     *
     * \param newStatorCurrentLimitEnable Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithStatorCurrentLimitEnable(bool newStatorCurrentLimitEnable)
    {
        StatorCurrentLimitEnable = std::move(newStatorCurrentLimitEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SupplyCurrentLimit parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The absolute maximum amount of supply current allowed.  Note this
     * requires SupplyCurrentLimitEnable to be true.  Use
     * SupplyCurrentLowerLimit and SupplyCurrentLowerTime to reduce the
     * supply current limit after the time threshold is exceeded.
     * 
     * Supply current is the current drawn from the battery, so this limit
     * can be used to prevent breaker trips and improve battery longevity.
     *  Additionally, in scenarios where the robot experiences brownouts
     * despite configuring stator current limits, a supply current limit
     * can further help avoid brownouts. However, it is important to note
     * that such brownouts may be caused by a bad battery or poor power
     * wiring.
     * 
     * A reasonable starting point for a supply current limit is 70 A with
     * a lower limit of 40 A after 1.0 second. Supply current limits
     * commonly range from 20-80 A depending on the breaker used.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 800.0
     * - Default Value: 70
     * - Units: A
     *
     * \param newSupplyCurrentLimit Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithSupplyCurrentLimit(units::current::ampere_t newSupplyCurrentLimit)
    {
        SupplyCurrentLimit = std::move(newSupplyCurrentLimit);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SupplyCurrentLimitEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Enable motor supply current limiting.
     * 
     * - Default Value: True
     *
     * \param newSupplyCurrentLimitEnable Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithSupplyCurrentLimitEnable(bool newSupplyCurrentLimitEnable)
    {
        SupplyCurrentLimitEnable = std::move(newSupplyCurrentLimitEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SupplyCurrentLowerLimit parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The amount of supply current allowed after the regular
     * SupplyCurrentLimit is active for longer than
     * SupplyCurrentLowerTime.  This allows higher current draws for a
     * fixed period of time before reducing the current limit to protect
     * breakers.  This has no effect if SupplyCurrentLimit is lower than
     * this value or SupplyCurrentLowerTime is 0.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 500
     * - Default Value: 40
     * - Units: A
     *
     * \param newSupplyCurrentLowerLimit Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithSupplyCurrentLowerLimit(units::current::ampere_t newSupplyCurrentLowerLimit)
    {
        SupplyCurrentLowerLimit = std::move(newSupplyCurrentLowerLimit);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SupplyCurrentLowerTime parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Reduces supply current to the SupplyCurrentLowerLimit after
     * limiting to SupplyCurrentLimit for this period of time.  If this is
     * set to 0, SupplyCurrentLowerLimit will be ignored.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 5.0
     * - Default Value: 1.0
     * - Units: seconds
     *
     * \param newSupplyCurrentLowerTime Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithSupplyCurrentLowerTime(units::time::second_t newSupplyCurrentLowerTime)
    {
        SupplyCurrentLowerTime = std::move(newSupplyCurrentLowerTime);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
