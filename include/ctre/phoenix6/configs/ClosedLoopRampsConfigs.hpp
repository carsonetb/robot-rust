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
 * \brief Configs that affect the closed-loop control of this motor
 *        controller.
 * 
 * \details Closed-loop ramp rates for the various control types.
 */
class ClosedLoopRampsConfigs : public ParentConfiguration {
public:
    constexpr ClosedLoopRampsConfigs() = default;

    /**
     * \brief If non-zero, this determines how much time to ramp from 0%
     * output to 100% during the closed-loop DutyCycle control modes.
     * 
     * If the goal is to limit acceleration, it is more useful to ramp the
     * closed-loop setpoint instead of the output. This can be achieved
     * using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t DutyCycleClosedLoopRampPeriod = 0_s;
    /**
     * \brief If non-zero, this determines how much time to ramp from 0V
     * output to 12V during the closed-loop Voltage control modes.
     * 
     * If the goal is to limit acceleration, it is more useful to ramp the
     * closed-loop setpoint instead of the output. This can be achieved
     * using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t VoltageClosedLoopRampPeriod = 0_s;
    /**
     * \brief If non-zero, this determines how much time to ramp from 0A
     * output to 300A during the closed-loop TorqueCurrent control modes.
     * 
     * Since TorqueCurrent is directly proportional to acceleration, this
     * ramp limits jerk instead of acceleration.
     * 
     * If the goal is to limit acceleration or jerk, it is more useful to
     * ramp the closed-loop setpoint instead of the output. This can be
     * achieved using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 10
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t TorqueClosedLoopRampPeriod = 0_s;
    
    /**
     * \brief Modifies this configuration's DutyCycleClosedLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0% output
     * to 100% during the closed-loop DutyCycle control modes.
     * 
     * If the goal is to limit acceleration, it is more useful to ramp the
     * closed-loop setpoint instead of the output. This can be achieved
     * using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newDutyCycleClosedLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr ClosedLoopRampsConfigs &WithDutyCycleClosedLoopRampPeriod(units::time::second_t newDutyCycleClosedLoopRampPeriod)
    {
        DutyCycleClosedLoopRampPeriod = std::move(newDutyCycleClosedLoopRampPeriod);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's VoltageClosedLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0V output
     * to 12V during the closed-loop Voltage control modes.
     * 
     * If the goal is to limit acceleration, it is more useful to ramp the
     * closed-loop setpoint instead of the output. This can be achieved
     * using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newVoltageClosedLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr ClosedLoopRampsConfigs &WithVoltageClosedLoopRampPeriod(units::time::second_t newVoltageClosedLoopRampPeriod)
    {
        VoltageClosedLoopRampPeriod = std::move(newVoltageClosedLoopRampPeriod);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's TorqueClosedLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0A output
     * to 300A during the closed-loop TorqueCurrent control modes.
     * 
     * Since TorqueCurrent is directly proportional to acceleration, this
     * ramp limits jerk instead of acceleration.
     * 
     * If the goal is to limit acceleration or jerk, it is more useful to
     * ramp the closed-loop setpoint instead of the output. This can be
     * achieved using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 10
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newTorqueClosedLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr ClosedLoopRampsConfigs &WithTorqueClosedLoopRampPeriod(units::time::second_t newTorqueClosedLoopRampPeriod)
    {
        TorqueClosedLoopRampPeriod = std::move(newTorqueClosedLoopRampPeriod);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
