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
 * \brief Configs that affect the magnet sensor and how to interpret
 *        it.
 * 
 * \details Includes sensor direction, the sensor discontinuity point,
 *          and the magnet offset.
 */
class MagnetSensorConfigs : public ParentConfiguration {
public:
    constexpr MagnetSensorConfigs() = default;

    /**
     * \brief Direction of the sensor to determine positive rotation, as
     * seen facing the LED side of the CANcoder.
     * 
     */
    signals::SensorDirectionValue SensorDirection = signals::SensorDirectionValue::CounterClockwise_Positive;
    /**
     * \brief This offset is added to the reported position, allowing the
     * application to trim the zero position.  When set to the default
     * value of zero, position reports zero when magnet north pole aligns
     * with the LED.
     * 
     * - Minimum Value: -1
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: rotations
     */
    units::angle::turn_t MagnetOffset = 0_tr;
    /**
     * \brief The positive discontinuity point of the absolute sensor in
     * rotations. This determines the point at which the absolute sensor
     * wraps around, keeping the absolute position (after offset) in the
     * range [x-1, x).
     * 
     * - Setting this to 1 makes the absolute position unsigned [0, 1)
     * - Setting this to 0.5 makes the absolute position signed [-0.5,
     * 0.5)
     * - Setting this to 0 makes the absolute position always negative
     * [-1, 0)
     * 
     * Many rotational mechanisms such as arms have a region of motion
     * that is unreachable. This should be set to the center of that
     * region of motion, in non-negative rotations. This affects the
     * position of the device at bootup.
     * 
     * \details For example, consider an arm which can travel from -0.2 to
     * 0.6 rotations with a little leeway, where 0 is horizontally
     * forward. Since -0.2 rotations has the same absolute position as 0.8
     * rotations, we can say that the arm typically does not travel in the
     * range (0.6, 0.8) rotations. As a result, the discontinuity point
     * would be the center of that range, which is 0.7 rotations. This
     * results in an absolute sensor range of [-0.3, 0.7) rotations.
     * 
     * Given a total range of motion less than 1 rotation, users can
     * calculate the discontinuity point using mean(lowerLimit,
     * upperLimit) + 0.5. If that results in a value outside the range [0,
     * 1], either cap the value to [0, 1], or add/subtract 1.0 rotation
     * from your lower and upper limits of motion.
     * 
     * On a Talon motor controller, this is only supported when using the
     * PulseWidth sensor source.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 0.5
     * - Units: rotations
     */
    units::angle::turn_t AbsoluteSensorDiscontinuityPoint = 0.5_tr;
    
    /**
     * \brief Modifies this configuration's SensorDirection parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Direction of the sensor to determine positive rotation, as seen
     * facing the LED side of the CANcoder.
     * 
     *
     * \param newSensorDirection Parameter to modify
     * \returns Itself
     */
    constexpr MagnetSensorConfigs &WithSensorDirection(signals::SensorDirectionValue newSensorDirection)
    {
        SensorDirection = std::move(newSensorDirection);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MagnetOffset parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This offset is added to the reported position, allowing the
     * application to trim the zero position.  When set to the default
     * value of zero, position reports zero when magnet north pole aligns
     * with the LED.
     * 
     * - Minimum Value: -1
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: rotations
     *
     * \param newMagnetOffset Parameter to modify
     * \returns Itself
     */
    constexpr MagnetSensorConfigs &WithMagnetOffset(units::angle::turn_t newMagnetOffset)
    {
        MagnetOffset = std::move(newMagnetOffset);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's AbsoluteSensorDiscontinuityPoint parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The positive discontinuity point of the absolute sensor in
     * rotations. This determines the point at which the absolute sensor
     * wraps around, keeping the absolute position (after offset) in the
     * range [x-1, x).
     * 
     * - Setting this to 1 makes the absolute position unsigned [0, 1)
     * - Setting this to 0.5 makes the absolute position signed [-0.5,
     * 0.5)
     * - Setting this to 0 makes the absolute position always negative
     * [-1, 0)
     * 
     * Many rotational mechanisms such as arms have a region of motion
     * that is unreachable. This should be set to the center of that
     * region of motion, in non-negative rotations. This affects the
     * position of the device at bootup.
     * 
     * \details For example, consider an arm which can travel from -0.2 to
     * 0.6 rotations with a little leeway, where 0 is horizontally
     * forward. Since -0.2 rotations has the same absolute position as 0.8
     * rotations, we can say that the arm typically does not travel in the
     * range (0.6, 0.8) rotations. As a result, the discontinuity point
     * would be the center of that range, which is 0.7 rotations. This
     * results in an absolute sensor range of [-0.3, 0.7) rotations.
     * 
     * Given a total range of motion less than 1 rotation, users can
     * calculate the discontinuity point using mean(lowerLimit,
     * upperLimit) + 0.5. If that results in a value outside the range [0,
     * 1], either cap the value to [0, 1], or add/subtract 1.0 rotation
     * from your lower and upper limits of motion.
     * 
     * On a Talon motor controller, this is only supported when using the
     * PulseWidth sensor source.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 0.5
     * - Units: rotations
     *
     * \param newAbsoluteSensorDiscontinuityPoint Parameter to modify
     * \returns Itself
     */
    constexpr MagnetSensorConfigs &WithAbsoluteSensorDiscontinuityPoint(units::angle::turn_t newAbsoluteSensorDiscontinuityPoint)
    {
        AbsoluteSensorDiscontinuityPoint = std::move(newAbsoluteSensorDiscontinuityPoint);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
