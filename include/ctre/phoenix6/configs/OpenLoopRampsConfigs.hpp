/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include <units/time.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs that affect the open-loop control of this motor
 *        controller.
 * 
 * \details Open-loop ramp rates for the various control types.
 */
class OpenLoopRampsConfigs : public ParentConfiguration {
public:
    constexpr OpenLoopRampsConfigs() = default;

    /**
     * \brief If non-zero, this determines how much time to ramp from 0%
     * output to 100% during the open-loop DutyCycleOut control mode.
     * 
     * This provides an easy way to limit the acceleration of the motor.
     * However, the acceleration and current draw of the motor can be
     * better restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t DutyCycleOpenLoopRampPeriod = 0_s;
    /**
     * \brief If non-zero, this determines how much time to ramp from 0V
     * output to 12V during the open-loop VoltageOut control mode.
     * 
     * This provides an easy way to limit the acceleration of the motor.
     * However, the acceleration and current draw of the motor can be
     * better restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t VoltageOpenLoopRampPeriod = 0_s;
    /**
     * \brief If non-zero, this determines how much time to ramp from 0A
     * output to 300A during the open-loop TorqueCurrent control mode.
     * 
     * Since TorqueCurrent is directly proportional to acceleration, this
     * ramp limits jerk instead of acceleration.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 10
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t TorqueOpenLoopRampPeriod = 0_s;
    
    /**
     * \brief Modifies this configuration's DutyCycleOpenLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0% output
     * to 100% during the open-loop DutyCycleOut control mode.
     * 
     * This provides an easy way to limit the acceleration of the motor.
     * However, the acceleration and current draw of the motor can be
     * better restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newDutyCycleOpenLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr OpenLoopRampsConfigs &WithDutyCycleOpenLoopRampPeriod(units::time::second_t newDutyCycleOpenLoopRampPeriod)
    {
        DutyCycleOpenLoopRampPeriod = std::move(newDutyCycleOpenLoopRampPeriod);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's VoltageOpenLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0V output
     * to 12V during the open-loop VoltageOut control mode.
     * 
     * This provides an easy way to limit the acceleration of the motor.
     * However, the acceleration and current draw of the motor can be
     * better restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newVoltageOpenLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr OpenLoopRampsConfigs &WithVoltageOpenLoopRampPeriod(units::time::second_t newVoltageOpenLoopRampPeriod)
    {
        VoltageOpenLoopRampPeriod = std::move(newVoltageOpenLoopRampPeriod);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's TorqueOpenLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0A output
     * to 300A during the open-loop TorqueCurrent control mode.
     * 
     * Since TorqueCurrent is directly proportional to acceleration, this
     * ramp limits jerk instead of acceleration.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 10
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newTorqueOpenLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr OpenLoopRampsConfigs &WithTorqueOpenLoopRampPeriod(units::time::second_t newTorqueOpenLoopRampPeriod)
    {
        TorqueOpenLoopRampPeriod = std::move(newTorqueOpenLoopRampPeriod);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
