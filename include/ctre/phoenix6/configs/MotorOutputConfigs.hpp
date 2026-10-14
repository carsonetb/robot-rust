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
#include <units/frequency.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs that directly affect motor output.
 * 
 * \details Includes motor invert, neutral mode, and other features
 *          related to motor output.
 */
class MotorOutputConfigs : public ParentConfiguration {
public:
    constexpr MotorOutputConfigs() = default;

    /**
     * \brief Invert state of the device as seen from the front of the
     * motor.
     * 
     */
    signals::InvertedValue Inverted = signals::InvertedValue::CounterClockwise_Positive;
    /**
     * \brief The state of the motor controller bridge when output is
     * neutral or disabled.
     * 
     */
    signals::NeutralModeValue NeutralMode = signals::NeutralModeValue::Coast;
    /**
     * \brief Configures the output deadband duty cycle during duty cycle
     * and voltage based control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 0.25
     * - Default Value: 0
     * - Units: fractional
     */
    units::dimensionless::scalar_t DutyCycleNeutralDeadband = 0;
    /**
     * \brief Maximum (forward) output during duty cycle based control
     * modes.
     * 
     * - Minimum Value: -1.0
     * - Maximum Value: 1.0
     * - Default Value: 1
     * - Units: fractional
     */
    units::dimensionless::scalar_t PeakForwardDutyCycle = 1;
    /**
     * \brief Minimum (reverse) output during duty cycle based control
     * modes.
     * 
     * - Minimum Value: -1.0
     * - Maximum Value: 1.0
     * - Default Value: -1
     * - Units: fractional
     */
    units::dimensionless::scalar_t PeakReverseDutyCycle = -1;
    /**
     * \brief When a control request UseTimesync is enabled, this
     * determines the time-sychronized frequency at which control requests
     * are applied.
     * 
     * \details The application of the control request will be delayed
     * until the next timesync boundary at the frequency defined by this
     * config. When set to 0 Hz, timesync will never be used for control
     * requests, regardless of the value of UseTimesync.
     * 
     * - Minimum Value: 50
     * - Maximum Value: 500
     * - Default Value: 0
     * - Units: Hz
     */
    units::frequency::hertz_t ControlTimesyncFreqHz = 0_Hz;
    
    /**
     * \brief Modifies this configuration's Inverted parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Invert state of the device as seen from the front of the motor.
     * 
     *
     * \param newInverted Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithInverted(signals::InvertedValue newInverted)
    {
        Inverted = std::move(newInverted);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's NeutralMode parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The state of the motor controller bridge when output is neutral or
     * disabled.
     * 
     *
     * \param newNeutralMode Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithNeutralMode(signals::NeutralModeValue newNeutralMode)
    {
        NeutralMode = std::move(newNeutralMode);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DutyCycleNeutralDeadband parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configures the output deadband duty cycle during duty cycle and
     * voltage based control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 0.25
     * - Default Value: 0
     * - Units: fractional
     *
     * \param newDutyCycleNeutralDeadband Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithDutyCycleNeutralDeadband(units::dimensionless::scalar_t newDutyCycleNeutralDeadband)
    {
        DutyCycleNeutralDeadband = std::move(newDutyCycleNeutralDeadband);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakForwardDutyCycle parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum (forward) output during duty cycle based control modes.
     * 
     * - Minimum Value: -1.0
     * - Maximum Value: 1.0
     * - Default Value: 1
     * - Units: fractional
     *
     * \param newPeakForwardDutyCycle Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithPeakForwardDutyCycle(units::dimensionless::scalar_t newPeakForwardDutyCycle)
    {
        PeakForwardDutyCycle = std::move(newPeakForwardDutyCycle);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakReverseDutyCycle parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Minimum (reverse) output during duty cycle based control modes.
     * 
     * - Minimum Value: -1.0
     * - Maximum Value: 1.0
     * - Default Value: -1
     * - Units: fractional
     *
     * \param newPeakReverseDutyCycle Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithPeakReverseDutyCycle(units::dimensionless::scalar_t newPeakReverseDutyCycle)
    {
        PeakReverseDutyCycle = std::move(newPeakReverseDutyCycle);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ControlTimesyncFreqHz parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * When a control request UseTimesync is enabled, this determines the
     * time-sychronized frequency at which control requests are applied.
     * 
     * \details The application of the control request will be delayed
     * until the next timesync boundary at the frequency defined by this
     * config. When set to 0 Hz, timesync will never be used for control
     * requests, regardless of the value of UseTimesync.
     * 
     * - Minimum Value: 50
     * - Maximum Value: 500
     * - Default Value: 0
     * - Units: Hz
     *
     * \param newControlTimesyncFreqHz Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithControlTimesyncFreqHz(units::frequency::hertz_t newControlTimesyncFreqHz)
    {
        ControlTimesyncFreqHz = std::move(newControlTimesyncFreqHz);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
