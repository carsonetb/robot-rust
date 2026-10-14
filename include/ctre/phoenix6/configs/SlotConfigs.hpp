/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/phoenix6/configs/Slot0Configs.hpp"
#include "ctre/phoenix6/configs/Slot1Configs.hpp"
#include "ctre/phoenix6/configs/Slot2Configs.hpp"
#include <unordered_map>

namespace ctre {
namespace phoenix6 {


namespace configs {
/**
 * \brief Gains for the specified slot.
 * 
 * \details If this slot is selected, these gains are used in closed
 *          loop control requests.
 */
class SlotConfigs : public ParentConfiguration {
    struct SlotSpns {
        int kPSpn;
        int kISpn;
        int kDSpn;
        int kSSpn;
        int kVSpn;
        int kASpn;
        int kGSpn;
        int GravityTypeSpn;
        int StaticFeedforwardSignSpn;
        int GravityArmPositionOffsetSpn;
        int GainSchedBehaviorSpn;
    };

    static std::unordered_map<int, SlotSpns> const genericMap;

public:
    constexpr SlotConfigs() = default;

    /**
     * \brief Proportional gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input, the units
     * should be defined as units of output per unit of input error. For
     * example, when controlling velocity using a duty cycle closed loop,
     * the units for the proportional gain will be duty cycle per rps of
     * error, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kP = 0;
    /**
     * \brief Integral gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input integrated over
     * time (in units of seconds), the units should be defined as units of
     * output per unit of integrated input error. For example, when
     * controlling velocity using a duty cycle closed loop, integrating
     * velocity over time results in rps * s = rotations. Therefore, the
     * units for the integral gain will be duty cycle per rotation of
     * accumulated error, or 1/rot.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kI = 0;
    /**
     * \brief Derivative gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the derivative of error in the
     * input with respect to time (in units of seconds), the units should
     * be defined as units of output per unit of the differentiated input
     * error. For example, when controlling velocity using a duty cycle
     * closed loop, the derivative of velocity with respect to time is rot
     * per sec², which is acceleration. Therefore, the units for the
     * derivative gain will be duty cycle per unit of acceleration error,
     * or 1/(rot per sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kD = 0;
    /**
     * \brief Static feedforward gain.
     * 
     * \details This is added to the closed loop output. The unit for this
     * constant is dependent on the control mode, typically fractional
     * duty cycle, voltage, or torque current.
     * 
     * The sign is typically determined by reference velocity when using
     * position, velocity, and Motion Magic® closed loop modes. However,
     * when using position closed loop with zero velocity reference (no
     * motion profiling), the application can instead use the position
     * closed loop error by setting the Static Feedforward Sign
     * configuration parameter.  When doing so, we recommend the minimal
     * amount of kS, otherwise the motor output may dither when closed
     * loop error is near zero.
     * 
     * - Minimum Value: -128
     * - Maximum Value: 127
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kS = 0;
    /**
     * \brief Velocity feedforward gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested velocity, the units
     * should be defined as units of output per unit of requested input
     * velocity. For example, when controlling velocity using a duty cycle
     * closed loop, the units for the velocity feedfoward gain will be
     * duty cycle per requested rps, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kV = 0;
    /**
     * \brief Acceleration feedforward gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested acceleration, the
     * units should be defined as units of output per unit of requested
     * input acceleration. For example, when controlling velocity using a
     * duty cycle closed loop, the units for the acceleration feedfoward
     * gain will be duty cycle per requested rot per sec², or 1/(rot per
     * sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kA = 0;
    /**
     * \brief Gravity feedforward/feedback gain. The type of gravity
     * compensation is selected by #GravityType.
     * 
     * \details This is added to the closed loop output. The sign is
     * determined by the gravity type. The unit for this constant is
     * dependent on the control mode, typically fractional duty cycle,
     * voltage, or torque current.
     * 
     * Note that kG may be negative for some counterbalanced mechanisms.
     * 
     * - Minimum Value: -128
     * - Maximum Value: 127
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kG = 0;
    /**
     * \brief Gravity feedforward/feedback type.
     * 
     * This determines the type of the gravity feedforward/feedback.
     * 
     * Choose Elevator_Static for systems where the gravity feedforward is
     * constant, such as an elevator. The gravity feedforward output will
     * always have the same sign.
     * 
     * Choose Arm_Cosine for systems where the gravity feedback is
     * dependent on the angular position of the mechanism, such as an arm.
     * The gravity feedback output will vary depending on the mechanism
     * angular position. Note that the sensor offset and ratios must be
     * configured so that the sensor reports a position of 0 when the
     * mechanism is horizonal (parallel to the ground), and the reported
     * sensor position is 1:1 with the mechanism.
     * 
     */
    signals::GravityTypeValue GravityType = signals::GravityTypeValue::Elevator_Static;
    /**
     * \brief Static feedforward sign during position closed loop.
     * 
     * This determines the sign of the applied kS during position
     * closed-loop modes. The default behavior uses the velocity reference
     * sign. This works well with velocity closed loop, Motion Magic®
     * controls, and position closed loop when velocity reference is
     * specified (motion profiling).
     * 
     * However, when using position closed loop with zero velocity
     * reference (no motion profiling), the application may want to apply
     * static feedforward based on the sign of closed loop error instead.
     * When doing so, we recommend using the minimal amount of kS,
     * otherwise the motor output may dither when closed loop error is
     * near zero.
     * 
     */
    signals::StaticFeedforwardSignValue StaticFeedforwardSign = signals::StaticFeedforwardSignValue::UseVelocitySign;
    /**
     * \brief Gravity feedback position offset when using the Arm/Cosine
     * gravity type.
     * 
     * This is an offset applied to the position of the arm, within
     * (-0.25, 0.25) rot, before calculating the output of kG. This is
     * useful when the center of gravity of the arm is offset from the
     * actual zero point of the arm, such as when the arm and intake form
     * an L shape.
     * 
     * - Minimum Value: -0.25
     * - Maximum Value: 0.25
     * - Default Value: 0
     * - Units: rotations
     */
    units::angle::turn_t GravityArmPositionOffset = 0_tr;
    /**
     * \brief The behavior of the gain scheduler on this slot. This
     * specifies which gains to use while within the configured
     * GainSchedErrorThreshold. The default is to continue using the
     * specified slot.
     * 
     * \details Gain scheduling will not take effect when running velocity
     * closed-loop controls.
     * 
     */
    signals::GainSchedBehaviorValue GainSchedBehavior = signals::GainSchedBehaviorValue::Inactive;
    
    /**
     * \brief Modifies this configuration's kP parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Proportional gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input, the units
     * should be defined as units of output per unit of input error. For
     * example, when controlling velocity using a duty cycle closed loop,
     * the units for the proportional gain will be duty cycle per rps of
     * error, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKP Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKP(units::dimensionless::scalar_t newKP)
    {
        kP = std::move(newKP);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kI parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Integral gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input integrated over
     * time (in units of seconds), the units should be defined as units of
     * output per unit of integrated input error. For example, when
     * controlling velocity using a duty cycle closed loop, integrating
     * velocity over time results in rps * s = rotations. Therefore, the
     * units for the integral gain will be duty cycle per rotation of
     * accumulated error, or 1/rot.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKI Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKI(units::dimensionless::scalar_t newKI)
    {
        kI = std::move(newKI);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kD parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Derivative gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the derivative of error in the
     * input with respect to time (in units of seconds), the units should
     * be defined as units of output per unit of the differentiated input
     * error. For example, when controlling velocity using a duty cycle
     * closed loop, the derivative of velocity with respect to time is rot
     * per sec², which is acceleration. Therefore, the units for the
     * derivative gain will be duty cycle per unit of acceleration error,
     * or 1/(rot per sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKD Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKD(units::dimensionless::scalar_t newKD)
    {
        kD = std::move(newKD);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kS parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Static feedforward gain.
     * 
     * \details This is added to the closed loop output. The unit for this
     * constant is dependent on the control mode, typically fractional
     * duty cycle, voltage, or torque current.
     * 
     * The sign is typically determined by reference velocity when using
     * position, velocity, and Motion Magic® closed loop modes. However,
     * when using position closed loop with zero velocity reference (no
     * motion profiling), the application can instead use the position
     * closed loop error by setting the Static Feedforward Sign
     * configuration parameter.  When doing so, we recommend the minimal
     * amount of kS, otherwise the motor output may dither when closed
     * loop error is near zero.
     * 
     * - Minimum Value: -128
     * - Maximum Value: 127
     * - Default Value: 0
     * - Units: 
     *
     * \param newKS Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKS(units::dimensionless::scalar_t newKS)
    {
        kS = std::move(newKS);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kV parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Velocity feedforward gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested velocity, the units
     * should be defined as units of output per unit of requested input
     * velocity. For example, when controlling velocity using a duty cycle
     * closed loop, the units for the velocity feedfoward gain will be
     * duty cycle per requested rps, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKV Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKV(units::dimensionless::scalar_t newKV)
    {
        kV = std::move(newKV);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kA parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Acceleration feedforward gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested acceleration, the
     * units should be defined as units of output per unit of requested
     * input acceleration. For example, when controlling velocity using a
     * duty cycle closed loop, the units for the acceleration feedfoward
     * gain will be duty cycle per requested rot per sec², or 1/(rot per
     * sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKA Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKA(units::dimensionless::scalar_t newKA)
    {
        kA = std::move(newKA);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kG parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gravity feedforward/feedback gain. The type of gravity compensation
     * is selected by #GravityType.
     * 
     * \details This is added to the closed loop output. The sign is
     * determined by the gravity type. The unit for this constant is
     * dependent on the control mode, typically fractional duty cycle,
     * voltage, or torque current.
     * 
     * Note that kG may be negative for some counterbalanced mechanisms.
     * 
     * - Minimum Value: -128
     * - Maximum Value: 127
     * - Default Value: 0
     * - Units: 
     *
     * \param newKG Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKG(units::dimensionless::scalar_t newKG)
    {
        kG = std::move(newKG);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GravityType parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gravity feedforward/feedback type.
     * 
     * This determines the type of the gravity feedforward/feedback.
     * 
     * Choose Elevator_Static for systems where the gravity feedforward is
     * constant, such as an elevator. The gravity feedforward output will
     * always have the same sign.
     * 
     * Choose Arm_Cosine for systems where the gravity feedback is
     * dependent on the angular position of the mechanism, such as an arm.
     * The gravity feedback output will vary depending on the mechanism
     * angular position. Note that the sensor offset and ratios must be
     * configured so that the sensor reports a position of 0 when the
     * mechanism is horizonal (parallel to the ground), and the reported
     * sensor position is 1:1 with the mechanism.
     * 
     *
     * \param newGravityType Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithGravityType(signals::GravityTypeValue newGravityType)
    {
        GravityType = std::move(newGravityType);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's StaticFeedforwardSign parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Static feedforward sign during position closed loop.
     * 
     * This determines the sign of the applied kS during position
     * closed-loop modes. The default behavior uses the velocity reference
     * sign. This works well with velocity closed loop, Motion Magic®
     * controls, and position closed loop when velocity reference is
     * specified (motion profiling).
     * 
     * However, when using position closed loop with zero velocity
     * reference (no motion profiling), the application may want to apply
     * static feedforward based on the sign of closed loop error instead.
     * When doing so, we recommend using the minimal amount of kS,
     * otherwise the motor output may dither when closed loop error is
     * near zero.
     * 
     *
     * \param newStaticFeedforwardSign Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithStaticFeedforwardSign(signals::StaticFeedforwardSignValue newStaticFeedforwardSign)
    {
        StaticFeedforwardSign = std::move(newStaticFeedforwardSign);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GravityArmPositionOffset parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gravity feedback position offset when using the Arm/Cosine gravity
     * type.
     * 
     * This is an offset applied to the position of the arm, within
     * (-0.25, 0.25) rot, before calculating the output of kG. This is
     * useful when the center of gravity of the arm is offset from the
     * actual zero point of the arm, such as when the arm and intake form
     * an L shape.
     * 
     * - Minimum Value: -0.25
     * - Maximum Value: 0.25
     * - Default Value: 0
     * - Units: rotations
     *
     * \param newGravityArmPositionOffset Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithGravityArmPositionOffset(units::angle::turn_t newGravityArmPositionOffset)
    {
        GravityArmPositionOffset = std::move(newGravityArmPositionOffset);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GainSchedBehavior parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The behavior of the gain scheduler on this slot. This specifies
     * which gains to use while within the configured
     * GainSchedErrorThreshold. The default is to continue using the
     * specified slot.
     * 
     * \details Gain scheduling will not take effect when running velocity
     * closed-loop controls.
     * 
     *
     * \param newGainSchedBehavior Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithGainSchedBehavior(signals::GainSchedBehaviorValue newGainSchedBehavior)
    {
        GainSchedBehavior = std::move(newGainSchedBehavior);
        return *this;
    }


    /**
     * \brief Chooses which slot these configs are for.
     */
    int SlotNumber = 0;

    /**
     * Converts the provided value to an instance of this type.
     *
     * \param value The value to convert
     * \returns Converted value
     */
    static SlotConfigs From(Slot0Configs const &value);
    /**
     * Converts the provided value to an instance of this type.
     *
     * \param value The value to convert
     * \returns Converted value
     */
    static SlotConfigs From(Slot1Configs const &value);
    /**
     * Converts the provided value to an instance of this type.
     *
     * \param value The value to convert
     * \returns Converted value
     */
    static SlotConfigs From(Slot2Configs const &value);

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
