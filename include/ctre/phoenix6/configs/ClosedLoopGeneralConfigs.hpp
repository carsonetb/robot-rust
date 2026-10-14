/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include <units/angle.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs that affect general behavior during closed-looping.
 * 
 * \details Includes Continuous Wrap features.
 */
class ClosedLoopGeneralConfigs : public ParentConfiguration {
public:
    constexpr ClosedLoopGeneralConfigs() = default;

    /**
     * \brief Wrap position error within [-0.5, +0.5) mechanism rotations.
     *  Typically used for continuous position closed-loops like swerve
     * azimuth.
     * 
     * \details This uses the mechanism rotation value. If there is a gear
     * ratio between the sensor and the mechanism, make sure to apply a
     * SensorToMechanismRatio so the closed loop operates on the full
     * rotation.
     * 
     * - Default Value: False
     */
    bool ContinuousWrap = false;
    /**
     * \brief Wrap differential difference position error within [-0.5,
     * +0.5) mechanism rotations.  Typically used for continuous position
     * closed-loops like a differential wrist.
     * 
     * \details This uses the differential difference rotation value. If
     * there is a gear ratio on the difference axis, make sure to apply a
     * SensorToDifferentialRatio so the closed loop operates on the full
     * rotation.
     * 
     * - Default Value: False
     */
    bool DifferentialContinuousWrap = false;
    /**
     * \brief The position closed-loop error threshold for gain
     * scheduling. When the absolute value of the closed-loop error is
     * within the threshold (inclusive), the PID controller will
     * automatically switch gains according to the configured
     * GainSchedBehavior of the slot.
     * 
     * When this is zero (default), no gain scheduling will occur.
     * Additionally, this does not take effect for velocity closed-loop
     * controls.
     * 
     * \details This can be used to implement a closed-loop deadband or,
     * less commonly, to switch to weaker gains when close to the target.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 0.0
     * - Units: rotations
     */
    units::angle::turn_t GainSchedErrorThreshold = 0.0_tr;
    /**
     * \brief The behavior of kP output as the error crosses the
     * GainSchedErrorThreshold during gain scheduling. The output of kP
     * can be adjusted to maintain continuity in output, or it can be left
     * discontinuous.
     * 
     */
    signals::GainSchedKpBehaviorValue GainSchedKpBehavior = signals::GainSchedKpBehaviorValue::Continuous;
    
    /**
     * \brief Modifies this configuration's ContinuousWrap parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Wrap position error within [-0.5, +0.5) mechanism rotations. 
     * Typically used for continuous position closed-loops like swerve
     * azimuth.
     * 
     * \details This uses the mechanism rotation value. If there is a gear
     * ratio between the sensor and the mechanism, make sure to apply a
     * SensorToMechanismRatio so the closed loop operates on the full
     * rotation.
     * 
     * - Default Value: False
     *
     * \param newContinuousWrap Parameter to modify
     * \returns Itself
     */
    constexpr ClosedLoopGeneralConfigs &WithContinuousWrap(bool newContinuousWrap)
    {
        ContinuousWrap = std::move(newContinuousWrap);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DifferentialContinuousWrap parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Wrap differential difference position error within [-0.5, +0.5)
     * mechanism rotations.  Typically used for continuous position
     * closed-loops like a differential wrist.
     * 
     * \details This uses the differential difference rotation value. If
     * there is a gear ratio on the difference axis, make sure to apply a
     * SensorToDifferentialRatio so the closed loop operates on the full
     * rotation.
     * 
     * - Default Value: False
     *
     * \param newDifferentialContinuousWrap Parameter to modify
     * \returns Itself
     */
    constexpr ClosedLoopGeneralConfigs &WithDifferentialContinuousWrap(bool newDifferentialContinuousWrap)
    {
        DifferentialContinuousWrap = std::move(newDifferentialContinuousWrap);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GainSchedErrorThreshold parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The position closed-loop error threshold for gain scheduling. When
     * the absolute value of the closed-loop error is within the threshold
     * (inclusive), the PID controller will automatically switch gains
     * according to the configured GainSchedBehavior of the slot.
     * 
     * When this is zero (default), no gain scheduling will occur.
     * Additionally, this does not take effect for velocity closed-loop
     * controls.
     * 
     * \details This can be used to implement a closed-loop deadband or,
     * less commonly, to switch to weaker gains when close to the target.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 0.0
     * - Units: rotations
     *
     * \param newGainSchedErrorThreshold Parameter to modify
     * \returns Itself
     */
    constexpr ClosedLoopGeneralConfigs &WithGainSchedErrorThreshold(units::angle::turn_t newGainSchedErrorThreshold)
    {
        GainSchedErrorThreshold = std::move(newGainSchedErrorThreshold);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GainSchedKpBehavior parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The behavior of kP output as the error crosses the
     * GainSchedErrorThreshold during gain scheduling. The output of kP
     * can be adjusted to maintain continuity in output, or it can be left
     * discontinuous.
     * 
     *
     * \param newGainSchedKpBehavior Parameter to modify
     * \returns Itself
     */
    constexpr ClosedLoopGeneralConfigs &WithGainSchedKpBehavior(signals::GainSchedKpBehaviorValue newGainSchedKpBehavior)
    {
        GainSchedKpBehavior = std::move(newGainSchedKpBehavior);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
