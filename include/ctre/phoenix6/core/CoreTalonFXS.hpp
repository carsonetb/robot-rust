/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/hardware/ParentDevice.hpp"
#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/phoenix6/configs/Configurator.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include "ctre/phoenix6/hardware/traits/CommonTalonWithExternalMotor.hpp"
#include "ctre/phoenix6/configs/MotorOutputConfigs.hpp"
#include "ctre/phoenix6/configs/CurrentLimitsConfigs.hpp"
#include "ctre/phoenix6/configs/VoltageConfigs.hpp"
#include "ctre/phoenix6/configs/ExternalFeedbackConfigs.hpp"
#include "ctre/phoenix6/configs/DifferentialSensorsConfigs.hpp"
#include "ctre/phoenix6/configs/DifferentialConstantsConfigs.hpp"
#include "ctre/phoenix6/configs/OpenLoopRampsConfigs.hpp"
#include "ctre/phoenix6/configs/ClosedLoopRampsConfigs.hpp"
#include "ctre/phoenix6/configs/HardwareLimitSwitchConfigs.hpp"
#include "ctre/phoenix6/configs/AudioConfigs.hpp"
#include "ctre/phoenix6/configs/SoftwareLimitSwitchConfigs.hpp"
#include "ctre/phoenix6/configs/MotionMagicConfigs.hpp"
#include "ctre/phoenix6/configs/CustomParamsConfigs.hpp"
#include "ctre/phoenix6/configs/ClosedLoopGeneralConfigs.hpp"
#include "ctre/phoenix6/configs/CommutationConfigs.hpp"
#include "ctre/phoenix6/configs/CustomBrushlessMotorConfigs.hpp"
#include "ctre/phoenix6/configs/ExternalTempConfigs.hpp"
#include "ctre/phoenix6/configs/Slot0Configs.hpp"
#include "ctre/phoenix6/configs/Slot1Configs.hpp"
#include "ctre/phoenix6/configs/Slot2Configs.hpp"
#include "ctre/phoenix6/configs/SlotConfigs.hpp"
#include "ctre/phoenix6/controls/DutyCycleOut.hpp"
#include "ctre/phoenix6/controls/VoltageOut.hpp"
#include "ctre/phoenix6/controls/PositionDutyCycle.hpp"
#include "ctre/phoenix6/controls/PositionVoltage.hpp"
#include "ctre/phoenix6/controls/VelocityDutyCycle.hpp"
#include "ctre/phoenix6/controls/VelocityVoltage.hpp"
#include "ctre/phoenix6/controls/MotionMagicDutyCycle.hpp"
#include "ctre/phoenix6/controls/MotionMagicVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialPositionDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialPositionVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialVelocityDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialVelocityVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicExpoDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicExpoVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicVelocityDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicVelocityVoltage.hpp"
#include "ctre/phoenix6/controls/Follower.hpp"
#include "ctre/phoenix6/controls/StrictFollower.hpp"
#include "ctre/phoenix6/controls/DifferentialFollower.hpp"
#include "ctre/phoenix6/controls/DifferentialStrictFollower.hpp"
#include "ctre/phoenix6/controls/NeutralOut.hpp"
#include "ctre/phoenix6/controls/CoastOut.hpp"
#include "ctre/phoenix6/controls/StaticBrake.hpp"
#include "ctre/phoenix6/controls/MotionMagicVelocityDutyCycle.hpp"
#include "ctre/phoenix6/controls/MotionMagicVelocityVoltage.hpp"
#include "ctre/phoenix6/controls/MotionMagicExpoDutyCycle.hpp"
#include "ctre/phoenix6/controls/MotionMagicExpoVoltage.hpp"
#include "ctre/phoenix6/controls/DynamicMotionMagicDutyCycle.hpp"
#include "ctre/phoenix6/controls/DynamicMotionMagicVoltage.hpp"
#include "ctre/phoenix6/controls/DynamicMotionMagicExpoDutyCycle.hpp"
#include "ctre/phoenix6/controls/DynamicMotionMagicExpoVoltage.hpp"
#include "ctre/phoenix6/controls/compound/Diff_DutyCycleOut_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionDutyCycle_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityDutyCycle_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicDutyCycle_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoDutyCycle_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityDutyCycle_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_DutyCycleOut_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_DutyCycleOut_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionDutyCycle_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityDutyCycle_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicDutyCycle_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoDutyCycle_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityDutyCycle_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VoltageOut_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VoltageOut_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VoltageOut_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionVoltage_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityVoltage_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVoltage_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoVoltage_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityVoltage_Open.hpp"
#include "ctre/phoenix6/sim/TalonFXSSimState.hpp"
#include "ctre/unit/motor_constants.h"
#include <units/angle.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/current.h>
#include <units/dimensionless.h>
#include <units/temperature.h>
#include <units/voltage.h>

namespace ctre {
namespace phoenix6 {

namespace hardware {
namespace core {
    class CoreTalonFXS;
}
}

namespace configs {

/**
 * Class description for the Talon FXS motor controller.
 *
 * This defines all configurations for the hardware#TalonFXS.
 */
class TalonFXSConfiguration : public ParentConfiguration
{
public:
    constexpr TalonFXSConfiguration() = default;

    /**
     * \brief True if we should factory default newer unsupported configs,
     *        false to leave newer unsupported configs alone.
     *
     * \details This flag addresses a corner case where the device may have
     *          firmware with newer configs that didn't exist when this
     *          version of the API was built. If this occurs and this
     *          flag is true, unsupported new configs will be factory
     *          defaulted to avoid unexpected behavior.
     *
     *          This is also the behavior in Phoenix 5, so this flag
     *          is defaulted to true to match.
     */
    bool FutureProofConfigs{true};

    
    /**
     * \brief Configs that directly affect motor output.
     * 
     * \details Includes motor invert, neutral mode, and other features
     *          related to motor output.
     * 
     * Parameter list:
     * 
     * - MotorOutputConfigs#Inverted
     * - MotorOutputConfigs#NeutralMode
     * - MotorOutputConfigs#DutyCycleNeutralDeadband
     * - MotorOutputConfigs#PeakForwardDutyCycle
     * - MotorOutputConfigs#PeakReverseDutyCycle
     * - MotorOutputConfigs#ControlTimesyncFreqHz
     * 
     */
    MotorOutputConfigs MotorOutput;
    
    /**
     * \brief Configs that directly affect current limiting features.
     * 
     * \details Contains the supply/stator current limit thresholds and
     *          whether to enable them.
     * 
     * Parameter list:
     * 
     * - CurrentLimitsConfigs#StatorCurrentLimit
     * - CurrentLimitsConfigs#StatorCurrentLimitEnable
     * - CurrentLimitsConfigs#SupplyCurrentLimit
     * - CurrentLimitsConfigs#SupplyCurrentLimitEnable
     * - CurrentLimitsConfigs#SupplyCurrentLowerLimit
     * - CurrentLimitsConfigs#SupplyCurrentLowerTime
     * 
     */
    CurrentLimitsConfigs CurrentLimits;
    
    /**
     * \brief Configs that affect Voltage control types.
     * 
     * \details Includes peak output voltages and other configs affecting
     *          voltage measurements.
     * 
     * Parameter list:
     * 
     * - VoltageConfigs#SupplyVoltageTimeConstant
     * - VoltageConfigs#PeakForwardVoltage
     * - VoltageConfigs#PeakReverseVoltage
     * 
     */
    VoltageConfigs Voltage;
    
    /**
     * \brief Configs that affect the external feedback sensor of this
     *        motor controller.
     * 
     * \details Includes feedback sensor source, offsets and sensor phase
     *          for the feedback sensor, and various ratios to describe
     *          the relationship between the sensor and the mechanism for
     *          closed looping.
     * 
     * Parameter list:
     * 
     * - ExternalFeedbackConfigs#SensorToMechanismRatio
     * - ExternalFeedbackConfigs#RotorToSensorRatio
     * - ExternalFeedbackConfigs#FeedbackRemoteSensorID
     * - ExternalFeedbackConfigs#VelocityFilterTimeConstant
     * - ExternalFeedbackConfigs#AbsoluteSensorOffset
     * - ExternalFeedbackConfigs#ExternalFeedbackSensorSource
     * - ExternalFeedbackConfigs#SensorPhase
     * - ExternalFeedbackConfigs#QuadratureEdgesPerRotation
     * - ExternalFeedbackConfigs#AbsoluteSensorDiscontinuityPoint
     * 
     */
    ExternalFeedbackConfigs ExternalFeedback;
    
    /**
     * \brief Configs related to sensors used for differential control of
     *        a mechanism.
     * 
     * \details Includes the differential sensor sources and IDs.
     * 
     * Parameter list:
     * 
     * - DifferentialSensorsConfigs#DifferentialSensorSource
     * - DifferentialSensorsConfigs#DifferentialTalonFXSensorID
     * - DifferentialSensorsConfigs#DifferentialRemoteSensorID
     * - DifferentialSensorsConfigs#SensorToDifferentialRatio
     * 
     */
    DifferentialSensorsConfigs DifferentialSensors;
    
    /**
     * \brief Configs related to constants used for differential control
     *        of a mechanism.
     * 
     * \details Includes the differential peak outputs.
     * 
     * Parameter list:
     * 
     * - DifferentialConstantsConfigs#PeakDifferentialDutyCycle
     * - DifferentialConstantsConfigs#PeakDifferentialVoltage
     * - DifferentialConstantsConfigs#PeakDifferentialTorqueCurrent
     * 
     */
    DifferentialConstantsConfigs DifferentialConstants;
    
    /**
     * \brief Configs that affect the open-loop control of this motor
     *        controller.
     * 
     * \details Open-loop ramp rates for the various control types.
     * 
     * Parameter list:
     * 
     * - OpenLoopRampsConfigs#DutyCycleOpenLoopRampPeriod
     * - OpenLoopRampsConfigs#VoltageOpenLoopRampPeriod
     * - OpenLoopRampsConfigs#TorqueOpenLoopRampPeriod
     * 
     */
    OpenLoopRampsConfigs OpenLoopRamps;
    
    /**
     * \brief Configs that affect the closed-loop control of this motor
     *        controller.
     * 
     * \details Closed-loop ramp rates for the various control types.
     * 
     * Parameter list:
     * 
     * - ClosedLoopRampsConfigs#DutyCycleClosedLoopRampPeriod
     * - ClosedLoopRampsConfigs#VoltageClosedLoopRampPeriod
     * - ClosedLoopRampsConfigs#TorqueClosedLoopRampPeriod
     * 
     */
    ClosedLoopRampsConfigs ClosedLoopRamps;
    
    /**
     * \brief Configs that change how the motor controller behaves under
     *        different limit switch states.
     * 
     * \details Includes configs such as enabling limit switches,
     *          configuring the remote sensor ID, the source, and the
     *          position to set on limit.
     * 
     * Parameter list:
     * 
     * - HardwareLimitSwitchConfigs#ForwardLimitType
     * - HardwareLimitSwitchConfigs#ForwardLimitAutosetPositionEnable
     * - HardwareLimitSwitchConfigs#ForwardLimitAutosetPositionValue
     * - HardwareLimitSwitchConfigs#ForwardLimitEnable
     * - HardwareLimitSwitchConfigs#ForwardLimitSource
     * - HardwareLimitSwitchConfigs#ForwardLimitRemoteSensorID
     * - HardwareLimitSwitchConfigs#ReverseLimitType
     * - HardwareLimitSwitchConfigs#ReverseLimitAutosetPositionEnable
     * - HardwareLimitSwitchConfigs#ReverseLimitAutosetPositionValue
     * - HardwareLimitSwitchConfigs#ReverseLimitEnable
     * - HardwareLimitSwitchConfigs#ReverseLimitSource
     * - HardwareLimitSwitchConfigs#ReverseLimitRemoteSensorID
     * 
     */
    HardwareLimitSwitchConfigs HardwareLimitSwitch;
    
    /**
     * \brief Configs that affect audible components of the device.
     * 
     * \details Includes configuration for the beep on boot.
     * 
     * Parameter list:
     * 
     * - AudioConfigs#BeepOnBoot
     * - AudioConfigs#BeepOnConfig
     * - AudioConfigs#AllowMusicDurDisable
     * 
     */
    AudioConfigs Audio;
    
    /**
     * \brief Configs that affect how software-limit switches behave.
     * 
     * \details Includes enabling software-limit switches and the
     *          threshold at which they are tripped.
     * 
     * Parameter list:
     * 
     * - SoftwareLimitSwitchConfigs#ForwardSoftLimitEnable
     * - SoftwareLimitSwitchConfigs#ReverseSoftLimitEnable
     * - SoftwareLimitSwitchConfigs#ForwardSoftLimitThreshold
     * - SoftwareLimitSwitchConfigs#ReverseSoftLimitThreshold
     * 
     */
    SoftwareLimitSwitchConfigs SoftwareLimitSwitch;
    
    /**
     * \brief Configs for Motion Magic®.
     * 
     * \details Includes Velocity, Acceleration, Jerk, and Expo
     *          parameters.
     * 
     * Parameter list:
     * 
     * - MotionMagicConfigs#MotionMagicCruiseVelocity
     * - MotionMagicConfigs#MotionMagicAcceleration
     * - MotionMagicConfigs#MotionMagicJerk
     * - MotionMagicConfigs#MotionMagicExpo_kV
     * - MotionMagicConfigs#MotionMagicExpo_kA
     * 
     */
    MotionMagicConfigs MotionMagic;
    
    /**
     * \brief Custom Params.
     * 
     * \details Custom paramaters that have no real impact on controller.
     * 
     * Parameter list:
     * 
     * - CustomParamsConfigs#CustomParam0
     * - CustomParamsConfigs#CustomParam1
     * 
     */
    CustomParamsConfigs CustomParams;
    
    /**
     * \brief Configs that affect general behavior during closed-looping.
     * 
     * \details Includes Continuous Wrap features.
     * 
     * Parameter list:
     * 
     * - ClosedLoopGeneralConfigs#ContinuousWrap
     * - ClosedLoopGeneralConfigs#DifferentialContinuousWrap
     * - ClosedLoopGeneralConfigs#GainSchedErrorThreshold
     * - ClosedLoopGeneralConfigs#GainSchedKpBehavior
     * 
     */
    ClosedLoopGeneralConfigs ClosedLoopGeneral;
    
    /**
     * \brief Configs that determine motor selection and commutation.
     * 
     * \details Set these configs to match your motor setup before
     *          commanding motor output.
     * 
     * Parameter list:
     * 
     * - CommutationConfigs#AdvancedHallSupport
     * - CommutationConfigs#MotorArrangement
     * - CommutationConfigs#BrushedMotorWiring
     * 
     */
    CommutationConfigs Commutation;
    
    /**
     * \brief Configs related to using a custom brushless motor that is
     *        not formally supported by Talon FXS.
     * 
     * \details Configs are only used when Motor Arrangement is set to
     *          Custom Brushless Motor.  Note this feature will only work
     *          device is not FRC-Locked.
     *          
     *          Users are responsible for ensuring that these configs are
     *          accurate to the motor. CTR Electronics is not responsible
     *          for damage caused by an incorrect custom motor
     *          configuration.
     * 
     * Parameter list:
     * 
     * - CustomBrushlessMotorConfigs#MotorKv
     * - CustomBrushlessMotorConfigs#PolePairCount
     * - CustomBrushlessMotorConfigs#HallDuringAB
     * - CustomBrushlessMotorConfigs#HallDuringAC
     * - CustomBrushlessMotorConfigs#HallCCWSelect
     * - CustomBrushlessMotorConfigs#HallDirection
     * 
     */
    CustomBrushlessMotorConfigs CustomBrushlessMotor;
    
    /**
     * \brief Configs related to using an independent thermister for
     *        automatically disabling a motor when a threshold has been
     *        reached.
     * 
     * \details Configs are only used when Motor Arrangement is set to
     *          Custom Brushless Motor or Brushed.  Note this feature will
     *          only work device is not FRC-Locked.
     *          
     *          Users are responsible for ensuring that these configs are
     *          accurate to the motor. CTR Electronics is not responsible
     *          for damage caused by an incorrect custom motor
     *          configuration.
     * 
     * Parameter list:
     * 
     * - ExternalTempConfigs#ThermistorMaxTemperature
     * - ExternalTempConfigs#ThermistorBeta
     * - ExternalTempConfigs#ThermistorR0
     * - ExternalTempConfigs#TempSensorRequired
     * 
     */
    ExternalTempConfigs ExternalTemp;
    
    /**
     * \brief Gains for the specified slot.
     * 
     * \details If this slot is selected, these gains are used in closed
     *          loop control requests.
     * 
     * Parameter list:
     * 
     * - Slot0Configs#kP
     * - Slot0Configs#kI
     * - Slot0Configs#kD
     * - Slot0Configs#kS
     * - Slot0Configs#kV
     * - Slot0Configs#kA
     * - Slot0Configs#kG
     * - Slot0Configs#GravityType
     * - Slot0Configs#StaticFeedforwardSign
     * - Slot0Configs#GravityArmPositionOffset
     * - Slot0Configs#GainSchedBehavior
     * 
     */
    Slot0Configs Slot0;
    
    /**
     * \brief Gains for the specified slot.
     * 
     * \details If this slot is selected, these gains are used in closed
     *          loop control requests.
     * 
     * Parameter list:
     * 
     * - Slot1Configs#kP
     * - Slot1Configs#kI
     * - Slot1Configs#kD
     * - Slot1Configs#kS
     * - Slot1Configs#kV
     * - Slot1Configs#kA
     * - Slot1Configs#kG
     * - Slot1Configs#GravityType
     * - Slot1Configs#StaticFeedforwardSign
     * - Slot1Configs#GravityArmPositionOffset
     * - Slot1Configs#GainSchedBehavior
     * 
     */
    Slot1Configs Slot1;
    
    /**
     * \brief Gains for the specified slot.
     * 
     * \details If this slot is selected, these gains are used in closed
     *          loop control requests.
     * 
     * Parameter list:
     * 
     * - Slot2Configs#kP
     * - Slot2Configs#kI
     * - Slot2Configs#kD
     * - Slot2Configs#kS
     * - Slot2Configs#kV
     * - Slot2Configs#kA
     * - Slot2Configs#kG
     * - Slot2Configs#GravityType
     * - Slot2Configs#StaticFeedforwardSign
     * - Slot2Configs#GravityArmPositionOffset
     * - Slot2Configs#GainSchedBehavior
     * 
     */
    Slot2Configs Slot2;
    
    /**
     * \brief Modifies this configuration's MotorOutput parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that directly affect motor output.
     * 
     * \details Includes motor invert, neutral mode, and other features
     *          related to motor output.
     * 
     * Parameter list:
     * 
     * - MotorOutputConfigs#Inverted
     * - MotorOutputConfigs#NeutralMode
     * - MotorOutputConfigs#DutyCycleNeutralDeadband
     * - MotorOutputConfigs#PeakForwardDutyCycle
     * - MotorOutputConfigs#PeakReverseDutyCycle
     * - MotorOutputConfigs#ControlTimesyncFreqHz
     * 
     *
     * \param newMotorOutput Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithMotorOutput(MotorOutputConfigs newMotorOutput)
    {
        MotorOutput = std::move(newMotorOutput);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's CurrentLimits parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that directly affect current limiting features.
     * 
     * \details Contains the supply/stator current limit thresholds and
     *          whether to enable them.
     * 
     * Parameter list:
     * 
     * - CurrentLimitsConfigs#StatorCurrentLimit
     * - CurrentLimitsConfigs#StatorCurrentLimitEnable
     * - CurrentLimitsConfigs#SupplyCurrentLimit
     * - CurrentLimitsConfigs#SupplyCurrentLimitEnable
     * - CurrentLimitsConfigs#SupplyCurrentLowerLimit
     * - CurrentLimitsConfigs#SupplyCurrentLowerTime
     * 
     *
     * \param newCurrentLimits Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithCurrentLimits(CurrentLimitsConfigs newCurrentLimits)
    {
        CurrentLimits = std::move(newCurrentLimits);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's Voltage parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that affect Voltage control types.
     * 
     * \details Includes peak output voltages and other configs affecting
     *          voltage measurements.
     * 
     * Parameter list:
     * 
     * - VoltageConfigs#SupplyVoltageTimeConstant
     * - VoltageConfigs#PeakForwardVoltage
     * - VoltageConfigs#PeakReverseVoltage
     * 
     *
     * \param newVoltage Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithVoltage(VoltageConfigs newVoltage)
    {
        Voltage = std::move(newVoltage);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ExternalFeedback parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that affect the external feedback sensor of this motor
     * controller.
     * 
     * \details Includes feedback sensor source, offsets and sensor phase
     *          for the feedback sensor, and various ratios to describe
     *          the relationship between the sensor and the mechanism for
     *          closed looping.
     * 
     * Parameter list:
     * 
     * - ExternalFeedbackConfigs#SensorToMechanismRatio
     * - ExternalFeedbackConfigs#RotorToSensorRatio
     * - ExternalFeedbackConfigs#FeedbackRemoteSensorID
     * - ExternalFeedbackConfigs#VelocityFilterTimeConstant
     * - ExternalFeedbackConfigs#AbsoluteSensorOffset
     * - ExternalFeedbackConfigs#ExternalFeedbackSensorSource
     * - ExternalFeedbackConfigs#SensorPhase
     * - ExternalFeedbackConfigs#QuadratureEdgesPerRotation
     * - ExternalFeedbackConfigs#AbsoluteSensorDiscontinuityPoint
     * 
     *
     * \param newExternalFeedback Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithExternalFeedback(ExternalFeedbackConfigs newExternalFeedback)
    {
        ExternalFeedback = std::move(newExternalFeedback);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DifferentialSensors parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs related to sensors used for differential control of a
     * mechanism.
     * 
     * \details Includes the differential sensor sources and IDs.
     * 
     * Parameter list:
     * 
     * - DifferentialSensorsConfigs#DifferentialSensorSource
     * - DifferentialSensorsConfigs#DifferentialTalonFXSensorID
     * - DifferentialSensorsConfigs#DifferentialRemoteSensorID
     * - DifferentialSensorsConfigs#SensorToDifferentialRatio
     * 
     *
     * \param newDifferentialSensors Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithDifferentialSensors(DifferentialSensorsConfigs newDifferentialSensors)
    {
        DifferentialSensors = std::move(newDifferentialSensors);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DifferentialConstants parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs related to constants used for differential control of a
     * mechanism.
     * 
     * \details Includes the differential peak outputs.
     * 
     * Parameter list:
     * 
     * - DifferentialConstantsConfigs#PeakDifferentialDutyCycle
     * - DifferentialConstantsConfigs#PeakDifferentialVoltage
     * - DifferentialConstantsConfigs#PeakDifferentialTorqueCurrent
     * 
     *
     * \param newDifferentialConstants Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithDifferentialConstants(DifferentialConstantsConfigs newDifferentialConstants)
    {
        DifferentialConstants = std::move(newDifferentialConstants);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's OpenLoopRamps parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that affect the open-loop control of this motor controller.
     * 
     * \details Open-loop ramp rates for the various control types.
     * 
     * Parameter list:
     * 
     * - OpenLoopRampsConfigs#DutyCycleOpenLoopRampPeriod
     * - OpenLoopRampsConfigs#VoltageOpenLoopRampPeriod
     * - OpenLoopRampsConfigs#TorqueOpenLoopRampPeriod
     * 
     *
     * \param newOpenLoopRamps Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithOpenLoopRamps(OpenLoopRampsConfigs newOpenLoopRamps)
    {
        OpenLoopRamps = std::move(newOpenLoopRamps);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ClosedLoopRamps parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that affect the closed-loop control of this motor
     * controller.
     * 
     * \details Closed-loop ramp rates for the various control types.
     * 
     * Parameter list:
     * 
     * - ClosedLoopRampsConfigs#DutyCycleClosedLoopRampPeriod
     * - ClosedLoopRampsConfigs#VoltageClosedLoopRampPeriod
     * - ClosedLoopRampsConfigs#TorqueClosedLoopRampPeriod
     * 
     *
     * \param newClosedLoopRamps Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithClosedLoopRamps(ClosedLoopRampsConfigs newClosedLoopRamps)
    {
        ClosedLoopRamps = std::move(newClosedLoopRamps);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's HardwareLimitSwitch parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that change how the motor controller behaves under
     * different limit switch states.
     * 
     * \details Includes configs such as enabling limit switches,
     *          configuring the remote sensor ID, the source, and the
     *          position to set on limit.
     * 
     * Parameter list:
     * 
     * - HardwareLimitSwitchConfigs#ForwardLimitType
     * - HardwareLimitSwitchConfigs#ForwardLimitAutosetPositionEnable
     * - HardwareLimitSwitchConfigs#ForwardLimitAutosetPositionValue
     * - HardwareLimitSwitchConfigs#ForwardLimitEnable
     * - HardwareLimitSwitchConfigs#ForwardLimitSource
     * - HardwareLimitSwitchConfigs#ForwardLimitRemoteSensorID
     * - HardwareLimitSwitchConfigs#ReverseLimitType
     * - HardwareLimitSwitchConfigs#ReverseLimitAutosetPositionEnable
     * - HardwareLimitSwitchConfigs#ReverseLimitAutosetPositionValue
     * - HardwareLimitSwitchConfigs#ReverseLimitEnable
     * - HardwareLimitSwitchConfigs#ReverseLimitSource
     * - HardwareLimitSwitchConfigs#ReverseLimitRemoteSensorID
     * 
     *
     * \param newHardwareLimitSwitch Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithHardwareLimitSwitch(HardwareLimitSwitchConfigs newHardwareLimitSwitch)
    {
        HardwareLimitSwitch = std::move(newHardwareLimitSwitch);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's Audio parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that affect audible components of the device.
     * 
     * \details Includes configuration for the beep on boot.
     * 
     * Parameter list:
     * 
     * - AudioConfigs#BeepOnBoot
     * - AudioConfigs#BeepOnConfig
     * - AudioConfigs#AllowMusicDurDisable
     * 
     *
     * \param newAudio Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithAudio(AudioConfigs newAudio)
    {
        Audio = std::move(newAudio);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SoftwareLimitSwitch parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that affect how software-limit switches behave.
     * 
     * \details Includes enabling software-limit switches and the
     *          threshold at which they are tripped.
     * 
     * Parameter list:
     * 
     * - SoftwareLimitSwitchConfigs#ForwardSoftLimitEnable
     * - SoftwareLimitSwitchConfigs#ReverseSoftLimitEnable
     * - SoftwareLimitSwitchConfigs#ForwardSoftLimitThreshold
     * - SoftwareLimitSwitchConfigs#ReverseSoftLimitThreshold
     * 
     *
     * \param newSoftwareLimitSwitch Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithSoftwareLimitSwitch(SoftwareLimitSwitchConfigs newSoftwareLimitSwitch)
    {
        SoftwareLimitSwitch = std::move(newSoftwareLimitSwitch);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MotionMagic parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs for Motion Magic®.
     * 
     * \details Includes Velocity, Acceleration, Jerk, and Expo
     *          parameters.
     * 
     * Parameter list:
     * 
     * - MotionMagicConfigs#MotionMagicCruiseVelocity
     * - MotionMagicConfigs#MotionMagicAcceleration
     * - MotionMagicConfigs#MotionMagicJerk
     * - MotionMagicConfigs#MotionMagicExpo_kV
     * - MotionMagicConfigs#MotionMagicExpo_kA
     * 
     *
     * \param newMotionMagic Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithMotionMagic(MotionMagicConfigs newMotionMagic)
    {
        MotionMagic = std::move(newMotionMagic);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's CustomParams parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Custom Params.
     * 
     * \details Custom paramaters that have no real impact on controller.
     * 
     * Parameter list:
     * 
     * - CustomParamsConfigs#CustomParam0
     * - CustomParamsConfigs#CustomParam1
     * 
     *
     * \param newCustomParams Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithCustomParams(CustomParamsConfigs newCustomParams)
    {
        CustomParams = std::move(newCustomParams);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ClosedLoopGeneral parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that affect general behavior during closed-looping.
     * 
     * \details Includes Continuous Wrap features.
     * 
     * Parameter list:
     * 
     * - ClosedLoopGeneralConfigs#ContinuousWrap
     * - ClosedLoopGeneralConfigs#DifferentialContinuousWrap
     * - ClosedLoopGeneralConfigs#GainSchedErrorThreshold
     * - ClosedLoopGeneralConfigs#GainSchedKpBehavior
     * 
     *
     * \param newClosedLoopGeneral Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithClosedLoopGeneral(ClosedLoopGeneralConfigs newClosedLoopGeneral)
    {
        ClosedLoopGeneral = std::move(newClosedLoopGeneral);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's Commutation parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that determine motor selection and commutation.
     * 
     * \details Set these configs to match your motor setup before
     *          commanding motor output.
     * 
     * Parameter list:
     * 
     * - CommutationConfigs#AdvancedHallSupport
     * - CommutationConfigs#MotorArrangement
     * - CommutationConfigs#BrushedMotorWiring
     * 
     *
     * \param newCommutation Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithCommutation(CommutationConfigs newCommutation)
    {
        Commutation = std::move(newCommutation);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's CustomBrushlessMotor parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs related to using a custom brushless motor that is not
     * formally supported by Talon FXS.
     * 
     * \details Configs are only used when Motor Arrangement is set to
     *          Custom Brushless Motor.  Note this feature will only work
     *          device is not FRC-Locked.
     *          
     *          Users are responsible for ensuring that these configs are
     *          accurate to the motor. CTR Electronics is not responsible
     *          for damage caused by an incorrect custom motor
     *          configuration.
     * 
     * Parameter list:
     * 
     * - CustomBrushlessMotorConfigs#MotorKv
     * - CustomBrushlessMotorConfigs#PolePairCount
     * - CustomBrushlessMotorConfigs#HallDuringAB
     * - CustomBrushlessMotorConfigs#HallDuringAC
     * - CustomBrushlessMotorConfigs#HallCCWSelect
     * - CustomBrushlessMotorConfigs#HallDirection
     * 
     *
     * \param newCustomBrushlessMotor Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithCustomBrushlessMotor(CustomBrushlessMotorConfigs newCustomBrushlessMotor)
    {
        CustomBrushlessMotor = std::move(newCustomBrushlessMotor);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ExternalTemp parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs related to using an independent thermister for
     * automatically disabling a motor when a threshold has been reached.
     * 
     * \details Configs are only used when Motor Arrangement is set to
     *          Custom Brushless Motor or Brushed.  Note this feature will
     *          only work device is not FRC-Locked.
     *          
     *          Users are responsible for ensuring that these configs are
     *          accurate to the motor. CTR Electronics is not responsible
     *          for damage caused by an incorrect custom motor
     *          configuration.
     * 
     * Parameter list:
     * 
     * - ExternalTempConfigs#ThermistorMaxTemperature
     * - ExternalTempConfigs#ThermistorBeta
     * - ExternalTempConfigs#ThermistorR0
     * - ExternalTempConfigs#TempSensorRequired
     * 
     *
     * \param newExternalTemp Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithExternalTemp(ExternalTempConfigs newExternalTemp)
    {
        ExternalTemp = std::move(newExternalTemp);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's Slot0 parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gains for the specified slot.
     * 
     * \details If this slot is selected, these gains are used in closed
     *          loop control requests.
     * 
     * Parameter list:
     * 
     * - Slot0Configs#kP
     * - Slot0Configs#kI
     * - Slot0Configs#kD
     * - Slot0Configs#kS
     * - Slot0Configs#kV
     * - Slot0Configs#kA
     * - Slot0Configs#kG
     * - Slot0Configs#GravityType
     * - Slot0Configs#StaticFeedforwardSign
     * - Slot0Configs#GravityArmPositionOffset
     * - Slot0Configs#GainSchedBehavior
     * 
     *
     * \param newSlot0 Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithSlot0(Slot0Configs newSlot0)
    {
        Slot0 = std::move(newSlot0);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's Slot1 parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gains for the specified slot.
     * 
     * \details If this slot is selected, these gains are used in closed
     *          loop control requests.
     * 
     * Parameter list:
     * 
     * - Slot1Configs#kP
     * - Slot1Configs#kI
     * - Slot1Configs#kD
     * - Slot1Configs#kS
     * - Slot1Configs#kV
     * - Slot1Configs#kA
     * - Slot1Configs#kG
     * - Slot1Configs#GravityType
     * - Slot1Configs#StaticFeedforwardSign
     * - Slot1Configs#GravityArmPositionOffset
     * - Slot1Configs#GainSchedBehavior
     * 
     *
     * \param newSlot1 Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithSlot1(Slot1Configs newSlot1)
    {
        Slot1 = std::move(newSlot1);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's Slot2 parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gains for the specified slot.
     * 
     * \details If this slot is selected, these gains are used in closed
     *          loop control requests.
     * 
     * Parameter list:
     * 
     * - Slot2Configs#kP
     * - Slot2Configs#kI
     * - Slot2Configs#kD
     * - Slot2Configs#kS
     * - Slot2Configs#kV
     * - Slot2Configs#kA
     * - Slot2Configs#kG
     * - Slot2Configs#GravityType
     * - Slot2Configs#StaticFeedforwardSign
     * - Slot2Configs#GravityArmPositionOffset
     * - Slot2Configs#GainSchedBehavior
     * 
     *
     * \param newSlot2 Parameter to modify
     * \returns Itself
     */
    constexpr TalonFXSConfiguration &WithSlot2(Slot2Configs newSlot2)
    {
        Slot2 = std::move(newSlot2);
        return *this;
    }

    /**
     * \brief Get the string representation of this configuration
     */
    std::string ToString() const override;

    /**
     * \brief Get the serialized form of this configuration
     */
    std::string Serialize() const final;
    /**
     * \brief Take a string and deserialize it to this configuration
     */
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

/**
 * Class description for the Talon FXS motor controller.
 *
 * This handles applying and refreshing configurations for the hardware#TalonFXS.
 */
class TalonFXSConfigurator : public ParentConfigurator
{
private:
    TalonFXSConfigurator(hardware::DeviceIdentifier id) :
        ParentConfigurator{std::move(id)}
    {}

    friend hardware::core::CoreTalonFXS;

public:
    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const TalonFXSConfiguration &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const TalonFXSConfiguration &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, configs.FutureProofConfigs, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const MotorOutputConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const MotorOutputConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const CurrentLimitsConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const CurrentLimitsConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const VoltageConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const VoltageConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const ExternalFeedbackConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const ExternalFeedbackConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const DifferentialSensorsConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const DifferentialSensorsConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const DifferentialConstantsConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const DifferentialConstantsConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const OpenLoopRampsConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const OpenLoopRampsConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const ClosedLoopRampsConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const ClosedLoopRampsConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const HardwareLimitSwitchConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const HardwareLimitSwitchConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const AudioConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const AudioConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const SoftwareLimitSwitchConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const SoftwareLimitSwitchConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const MotionMagicConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const MotionMagicConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const CustomParamsConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const CustomParamsConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const ClosedLoopGeneralConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const ClosedLoopGeneralConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const CommutationConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const CommutationConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const CustomBrushlessMotorConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const CustomBrushlessMotorConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const ExternalTempConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const ExternalTempConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const Slot0Configs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const Slot0Configs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const Slot1Configs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const Slot1Configs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const Slot2Configs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const Slot2Configs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const SlotConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of applying the configs
     */
    ctre::phoenix::StatusCode Apply(const SlotConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(TalonFXSConfiguration &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(TalonFXSConfiguration &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(MotorOutputConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(MotorOutputConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(CurrentLimitsConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(CurrentLimitsConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(VoltageConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(VoltageConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(ExternalFeedbackConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(ExternalFeedbackConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(DifferentialSensorsConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(DifferentialSensorsConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(DifferentialConstantsConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(DifferentialConstantsConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(OpenLoopRampsConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(OpenLoopRampsConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(ClosedLoopRampsConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(ClosedLoopRampsConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(HardwareLimitSwitchConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(HardwareLimitSwitchConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(AudioConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(AudioConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(SoftwareLimitSwitchConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(SoftwareLimitSwitchConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(MotionMagicConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(MotionMagicConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(CustomParamsConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(CustomParamsConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(ClosedLoopGeneralConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(ClosedLoopGeneralConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(CommutationConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(CommutationConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(CustomBrushlessMotorConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(CustomBrushlessMotorConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(ExternalTempConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(ExternalTempConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(Slot0Configs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(Slot0Configs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(Slot1Configs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(Slot1Configs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(Slot2Configs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(Slot2Configs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(SlotConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(SlotConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    
    /**
     * \brief Sets the mechanism position of the device in mechanism
     * rotations.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param newValue Value to set to. Units are in rotations.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetPosition(units::angle::turn_t newValue)
    {
        return SetPosition(newValue, DefaultTimeoutSeconds);
    }
    /**
     * \brief Sets the mechanism position of the device in mechanism
     * rotations.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param newValue Value to set to. Units are in rotations.
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetPosition(units::angle::turn_t newValue, units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear the sticky faults in the device.
     * 
     * \details This typically has no impact on the device functionality. 
     * Instead, it just clears telemetry faults that are accessible via
     * API and Tuner Self-Test.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFaults()
    {
        return ClearStickyFaults(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear the sticky faults in the device.
     * 
     * \details This typically has no impact on the device functionality. 
     * Instead, it just clears telemetry faults that are accessible via
     * API and Tuner Self-Test.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFaults(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Hardware fault occurred
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Hardware()
    {
        return ClearStickyFault_Hardware(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Hardware fault occurred
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Hardware(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Processor temperature exceeded limit
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ProcTemp()
    {
        return ClearStickyFault_ProcTemp(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Processor temperature exceeded limit
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ProcTemp(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Device temperature exceeded limit
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DeviceTemp()
    {
        return ClearStickyFault_DeviceTemp(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device temperature exceeded limit
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DeviceTemp(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Device supply voltage dropped to near
     * brownout levels
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Undervoltage()
    {
        return ClearStickyFault_Undervoltage(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device supply voltage dropped to near
     * brownout levels
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Undervoltage(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Device boot while detecting the enable
     * signal
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootDuringEnable()
    {
        return ClearStickyFault_BootDuringEnable(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device boot while detecting the enable
     * signal
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootDuringEnable(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: An unlicensed feature is in use, device
     * may not behave as expected.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnlicensedFeatureInUse()
    {
        return ClearStickyFault_UnlicensedFeatureInUse(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: An unlicensed feature is in use, device
     * may not behave as expected.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnlicensedFeatureInUse(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to
     * supply voltage dropping too low.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BridgeBrownout()
    {
        return ClearStickyFault_BridgeBrownout(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to
     * supply voltage dropping too low.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BridgeBrownout(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: The remote sensor has reset.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorReset()
    {
        return ClearStickyFault_RemoteSensorReset(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote sensor has reset.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorReset(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: The remote Talon used for differential
     * control is not present on CAN Bus.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingDifferentialFX()
    {
        return ClearStickyFault_MissingDifferentialFX(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote Talon used for differential
     * control is not present on CAN Bus.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingDifferentialFX(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: The remote sensor position has
     * overflowed. Because of the nature of remote sensors, it is possible
     * for the remote sensor position to overflow beyond what is supported
     * by the status signal frame. However, this is rare and cannot occur
     * over the course of an FRC match under normal use.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorPosOverflow()
    {
        return ClearStickyFault_RemoteSensorPosOverflow(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote sensor position has
     * overflowed. Because of the nature of remote sensors, it is possible
     * for the remote sensor position to overflow beyond what is supported
     * by the status signal frame. However, this is rare and cannot occur
     * over the course of an FRC match under normal use.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorPosOverflow(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Supply Voltage has exceeded the maximum
     * voltage rating of device.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_OverSupplyV()
    {
        return ClearStickyFault_OverSupplyV(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Supply Voltage has exceeded the maximum
     * voltage rating of device.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_OverSupplyV(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Supply Voltage is unstable.  Ensure you
     * are using a battery and current limited power supply.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnstableSupplyV()
    {
        return ClearStickyFault_UnstableSupplyV(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Supply Voltage is unstable.  Ensure you
     * are using a battery and current limited power supply.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnstableSupplyV(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Reverse limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ReverseHardLimit()
    {
        return ClearStickyFault_ReverseHardLimit(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Reverse limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ReverseHardLimit(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Forward limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ForwardHardLimit()
    {
        return ClearStickyFault_ForwardHardLimit(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Forward limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ForwardHardLimit(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Reverse soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ReverseSoftLimit()
    {
        return ClearStickyFault_ReverseSoftLimit(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Reverse soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ReverseSoftLimit(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Forward soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ForwardSoftLimit()
    {
        return ClearStickyFault_ForwardSoftLimit(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Forward soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ForwardSoftLimit(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: The remote soft limit device is not
     * present on CAN Bus.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingSoftLimitRemote()
    {
        return ClearStickyFault_MissingSoftLimitRemote(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote soft limit device is not
     * present on CAN Bus.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingSoftLimitRemote(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: The remote limit switch device is not
     * present on CAN Bus.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingHardLimitRemote()
    {
        return ClearStickyFault_MissingHardLimitRemote(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote limit switch device is not
     * present on CAN Bus.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingHardLimitRemote(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: The remote sensor's data is no longer
     * trusted. This can happen if the remote sensor disappears from the
     * CAN bus or if the remote sensor indicates its data is no longer
     * valid, such as when a CANcoder's magnet strength falls into the
     * "red" range.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorDataInvalid()
    {
        return ClearStickyFault_RemoteSensorDataInvalid(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote sensor's data is no longer
     * trusted. This can happen if the remote sensor disappears from the
     * CAN bus or if the remote sensor indicates its data is no longer
     * valid, such as when a CANcoder's magnet strength falls into the
     * "red" range.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorDataInvalid(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: The remote sensor used for fusion has
     * fallen out of sync to the local sensor. A re-synchronization has
     * occurred, which may cause a discontinuity. This typically happens
     * if there is significant slop in the mechanism, or if the
     * RotorToSensorRatio configuration parameter is incorrect.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_FusedSensorOutOfSync()
    {
        return ClearStickyFault_FusedSensorOutOfSync(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote sensor used for fusion has
     * fallen out of sync to the local sensor. A re-synchronization has
     * occurred, which may cause a discontinuity. This typically happens
     * if there is significant slop in the mechanism, or if the
     * RotorToSensorRatio configuration parameter is incorrect.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_FusedSensorOutOfSync(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Stator current limit occured.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_StatorCurrLimit()
    {
        return ClearStickyFault_StatorCurrLimit(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Stator current limit occured.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_StatorCurrLimit(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Supply current limit occured.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SupplyCurrLimit()
    {
        return ClearStickyFault_SupplyCurrLimit(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Supply current limit occured.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SupplyCurrLimit(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Using Fused CANcoder feature while
     * unlicensed. Device has fallen back to remote CANcoder.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UsingFusedCANcoderWhileUnlicensed()
    {
        return ClearStickyFault_UsingFusedCANcoderWhileUnlicensed(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Using Fused CANcoder feature while
     * unlicensed. Device has fallen back to remote CANcoder.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UsingFusedCANcoderWhileUnlicensed(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Static brake was momentarily disabled
     * due to excessive braking current while disabled.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_StaticBrakeDisabled()
    {
        return ClearStickyFault_StaticBrakeDisabled(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Static brake was momentarily disabled
     * due to excessive braking current while disabled.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_StaticBrakeDisabled(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to a
     * short in the motor leads.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BridgeShort()
    {
        return ClearStickyFault_BridgeShort(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to a
     * short in the motor leads.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BridgeShort(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid.  Check
     * hall sensor and cabling.  This fault can be used to detect when
     * hall cable is unplugged.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_HallSensorMissing()
    {
        return ClearStickyFault_HallSensorMissing(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid.  Check
     * hall sensor and cabling.  This fault can be used to detect when
     * hall cable is unplugged.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_HallSensorMissing(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid during
     * motor drive, so motor was disabled.  Check hall sensor and cabling.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DriveDisabledHallSensor()
    {
        return ClearStickyFault_DriveDisabledHallSensor(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid during
     * motor drive, so motor was disabled.  Check hall sensor and cabling.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DriveDisabledHallSensor(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Motor temperature signal appears to not
     * be connected.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorMissing()
    {
        return ClearStickyFault_MotorTempSensorMissing(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motor temperature signal appears to not
     * be connected.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorMissing(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Motor temperature signal indicates motor
     * is too hot.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorTooHot()
    {
        return ClearStickyFault_MotorTempSensorTooHot(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motor temperature signal indicates motor
     * is too hot.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorTooHot(units::time::second_t timeoutSeconds);
    
    /**
     * \brief Clear sticky fault: Motor arrangement has not been set in
     * configuration.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorArrangementNotSelected()
    {
        return ClearStickyFault_MotorArrangementNotSelected(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motor arrangement has not been set in
     * configuration.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorArrangementNotSelected(units::time::second_t timeoutSeconds);
};

}

namespace hardware {
namespace core {

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

/**
 * Class description for the Talon FXS motor controller.
 */
class CoreTalonFXS : public ParentDevice, public traits::CommonTalonWithExternalMotor
{
private:
    configs::TalonFXSConfigurator _configs;

public:
    /**
     * \brief The configuration class for this device.
     */
    using Configuration = configs::TalonFXSConfiguration;

    /**
     * Constructs a new Talon FXS motor controller object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner
     * \param canbus      The CAN bus this device is on
     */
    CoreTalonFXS(int deviceId, CANBus canbus = {});

    /**
     * Constructs a new Talon FXS motor controller object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner
     * \param canbus      Name of the CAN bus this device is on. Possible CAN bus strings are:
     *                    - "rio" for the native roboRIO CAN bus
     *                    - CANivore name or serial number
     *                    - SocketCAN interface (non-FRC Linux only)
     *                    - "*" for any CANivore seen by the program
     *                    - empty string (default) to select the default for the system:
     *                      - "rio" on roboRIO
     *                      - "can0" on Linux
     *                      - "*" on Windows
     *
     * \deprecated Constructing devices with a CAN bus string is deprecated for removal
     * in the 2027 season. Construct devices using a CANBus instance instead.
     */
    CoreTalonFXS(int deviceId, std::string canbus);

    /**
     * \brief Constructs a stubbed-out CoreTalonFXS, where all status signals, controls,
     * configs, etc. perform no action and immediately return OK. This can be used to
     * silence error messages for devices that have been completely removed from the robot.
     *
     * \returns Stubbed-out CoreTalonFXS
     */
    static CoreTalonFXS None()
    {
        return CoreTalonFXS{-1, CANBus{}};
    }

    /**
     * \brief Gets the configurator for this TalonFXS
     *
     * \details Gets the configurator for this TalonFXS
     *
     * \returns Configurator for this TalonFXS
     */
    configs::TalonFXSConfigurator &GetConfigurator()
    {
        return _configs;
    }

    /**
     * \brief Gets the configurator for this TalonFXS
     *
     * \details Gets the configurator for this TalonFXS
     *
     * \returns Configurator for this TalonFXS
     */
    configs::TalonFXSConfigurator const &GetConfigurator() const
    {
        return _configs;
    }


private:
    std::unique_ptr<sim::TalonFXSSimState> _simState{};
public:
    /**
     * \brief Get the simulation state for this device.
     *
     * \details This function reuses an allocated simulation
     * state object, so it is safe to call this function multiple
     * times in a robot loop.
     *
     * \returns Simulation state
     */
    sim::TalonFXSSimState &GetSimState()
    {
        if (_simState == nullptr)
            _simState = std::make_unique<sim::TalonFXSSimState>(*this);
        return *_simState;
    }


        
    /**
     * \brief App Major Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns VersionMajor Status Signal Object
     */
    StatusSignal<int> &GetVersionMajor(bool refresh = true) final;
        
    /**
     * \brief App Minor Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns VersionMinor Status Signal Object
     */
    StatusSignal<int> &GetVersionMinor(bool refresh = true) final;
        
    /**
     * \brief App Bugfix Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns VersionBugfix Status Signal Object
     */
    StatusSignal<int> &GetVersionBugfix(bool refresh = true) final;
        
    /**
     * \brief App Build Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns VersionBuild Status Signal Object
     */
    StatusSignal<int> &GetVersionBuild(bool refresh = true) final;
        
    /**
     * \brief Full Version of firmware in device.  The format is a four
     * byte value.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 4294967295
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Version Status Signal Object
     */
    StatusSignal<int> &GetVersion(bool refresh = true) final;
        
    /**
     * \brief Integer representing all fault flags reported by the device.
     * 
     * \details These are device specific and are not used directly in
     * typical applications. Use the signal specific GetFault_*() methods
     * instead.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 4294967295
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns FaultField Status Signal Object
     */
    StatusSignal<int> &GetFaultField(bool refresh = true) final;
        
    /**
     * \brief Integer representing all (persistent) sticky fault flags
     * reported by the device.
     * 
     * \details These are device specific and are not used directly in
     * typical applications. Use the signal specific GetStickyFault_*()
     * methods instead.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 4294967295
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFaultField Status Signal Object
     */
    StatusSignal<int> &GetStickyFaultField(bool refresh = true) final;
        
    /**
     * \brief The applied (output) motor voltage.
     * 
     * - Minimum Value: -40.96
     * - Maximum Value: 40.95
     * - Default Value: 0
     * - Units: V
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns MotorVoltage Status Signal Object
     */
    StatusSignal<units::voltage::volt_t> &GetMotorVoltage(bool refresh = true) final;
        
    /**
     * \brief Forward Limit Pin.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ForwardLimit Status Signal Object
     */
    StatusSignal<signals::ForwardLimitValue> &GetForwardLimit(bool refresh = true) final;
        
    /**
     * \brief Reverse Limit Pin.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ReverseLimit Status Signal Object
     */
    StatusSignal<signals::ReverseLimitValue> &GetReverseLimit(bool refresh = true) final;
        
    /**
     * \brief The applied rotor polarity as seen from the front of the
     * motor.  This typically is determined by the Inverted config, but
     * can be overridden if using Follower features.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns AppliedRotorPolarity Status Signal Object
     */
    StatusSignal<signals::AppliedRotorPolarityValue> &GetAppliedRotorPolarity(bool refresh = true) final;
        
    /**
     * \brief The applied motor duty cycle.
     * 
     * - Minimum Value: -2.0
     * - Maximum Value: 1.9990234375
     * - Default Value: 0
     * - Units: fractional
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DutyCycle Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetDutyCycle(bool refresh = true) final;
        
    /**
     * \brief Current corresponding to the torque output by the motor.
     * Similar to StatorCurrent. Users will likely prefer this current to
     * calculate the applied torque to the rotor.
     * 
     * \details Stator current where positive current means torque is
     * applied in the forward direction as determined by the Inverted
     * setting.
     * 
     * - Minimum Value: -327.68
     * - Maximum Value: 327.67
     * - Default Value: 0
     * - Units: A
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns TorqueCurrent Status Signal Object
     */
    StatusSignal<units::current::ampere_t> &GetTorqueCurrent(bool refresh = true) final;
        
    /**
     * \brief Current corresponding to the stator windings. Similar to
     * TorqueCurrent. Users will likely prefer TorqueCurrent over
     * StatorCurrent.
     * 
     * \details Stator current where Positive current indicates motoring
     * regardless of direction. Negative current indicates regenerative
     * braking regardless of direction.
     * 
     * - Minimum Value: -327.68
     * - Maximum Value: 327.66
     * - Default Value: 0
     * - Units: A
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StatorCurrent Status Signal Object
     */
    StatusSignal<units::current::ampere_t> &GetStatorCurrent(bool refresh = true) final;
        
    /**
     * \brief Measured supply side current.
     * 
     * - Minimum Value: -327.68
     * - Maximum Value: 327.66
     * - Default Value: 0
     * - Units: A
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns SupplyCurrent Status Signal Object
     */
    StatusSignal<units::current::ampere_t> &GetSupplyCurrent(bool refresh = true) final;
        
    /**
     * \brief Measured supply voltage to the device.
     * 
     * - Minimum Value: 4
     * - Maximum Value: 29.575
     * - Default Value: 4
     * - Units: V
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns SupplyVoltage Status Signal Object
     */
    StatusSignal<units::voltage::volt_t> &GetSupplyVoltage(bool refresh = true) final;
        
    /**
     * \brief Temperature of device.
     * 
     * \details This is the temperature that the device measures itself to
     * be at. Similar to Processor Temperature.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 255.0
     * - Default Value: 0
     * - Units: ℃
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DeviceTemp Status Signal Object
     */
    StatusSignal<units::temperature::celsius_t> &GetDeviceTemp(bool refresh = true) final;
        
    /**
     * \brief Temperature of the processor.
     * 
     * \details This is the temperature that the processor measures itself
     * to be at. Similar to Device Temperature.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 255.0
     * - Default Value: 0
     * - Units: ℃
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ProcessorTemp Status Signal Object
     */
    StatusSignal<units::temperature::celsius_t> &GetProcessorTemp(bool refresh = true) final;
        
    /**
     * \brief Velocity of the motor rotor. This velocity is not affected
     * by any feedback configs.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns RotorVelocity Status Signal Object
     */
    StatusSignal<units::angular_velocity::turns_per_second_t> &GetRotorVelocity(bool refresh = true) final;
        
    /**
     * \brief Position of the motor rotor. This position is only affected
     * by the RotorOffset config and calls to setPosition.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns RotorPosition Status Signal Object
     */
    StatusSignal<units::angle::turn_t> &GetRotorPosition(bool refresh = true) final;
        
    /**
     * \brief Velocity of the device in mechanism rotations per second.
     * This can be the velocity of a remote sensor and is affected by the
     * RotorToSensorRatio and SensorToMechanismRatio configs.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * Default Rates:
     * - CAN 2.0: 50.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Velocity Status Signal Object
     */
    StatusSignal<units::angular_velocity::turns_per_second_t> &GetVelocity(bool refresh = true) final;
        
    /**
     * \brief Position of the device in mechanism rotations. This can be
     * the position of a remote sensor and is affected by the
     * RotorToSensorRatio and SensorToMechanismRatio configs, as well as
     * calls to setPosition.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * Default Rates:
     * - CAN 2.0: 50.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Position Status Signal Object
     */
    StatusSignal<units::angle::turn_t> &GetPosition(bool refresh = true) final;
        
    /**
     * \brief Acceleration of the device in mechanism rotations per
     * second². This can be the acceleration of a remote sensor and is
     * affected by the RotorToSensorRatio and SensorToMechanismRatio
     * configs.
     * 
     * - Minimum Value: -2048.0
     * - Maximum Value: 2047.75
     * - Default Value: 0
     * - Units: rotations per second²
     * 
     * Default Rates:
     * - CAN 2.0: 50.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Acceleration Status Signal Object
     */
    StatusSignal<units::angular_acceleration::turns_per_second_squared_t> &GetAcceleration(bool refresh = true) final;
        
    /**
     * \brief The active control mode of the motor controller.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ControlMode Status Signal Object
     */
    StatusSignal<signals::ControlModeValue> &GetControlMode(bool refresh = true) final;
        
    /**
     * \brief Status of the temperature sensor of the external motor.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ExternalMotorTempStatus Status Signal Object
     */
    StatusSignal<signals::ExternalMotorTempStatusValue> &GetExternalMotorTempStatus(bool refresh = true) final;
        
    /**
     * \brief Temperature of the external motor.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 255.0
     * - Default Value: 0
     * - Units: ℃
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ExternalMotorTemp Status Signal Object
     */
    StatusSignal<units::temperature::celsius_t> &GetExternalMotorTemp(bool refresh = true) final;
        
    /**
     * \brief Check if the Motion Magic® profile has reached the target.
     * This is equivalent to checking that MotionMagicIsRunning, the
     * ClosedLoopReference is the target, and the ClosedLoopReferenceSlope
     * is 0.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns MotionMagicAtTarget Status Signal Object
     */
    StatusSignal<bool> &GetMotionMagicAtTarget(bool refresh = true) final;
        
    /**
     * \brief Check if Motion Magic® is running.  This is equivalent to
     * checking that the reported control mode is a Motion Magic® based
     * mode.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns MotionMagicIsRunning Status Signal Object
     */
    StatusSignal<bool> &GetMotionMagicIsRunning(bool refresh = true) final;
        
    /**
     * \brief Indicates if the robot is enabled.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns RobotEnable Status Signal Object
     */
    StatusSignal<signals::RobotEnableValue> &GetRobotEnable(bool refresh = true) final;
        
    /**
     * \brief Indicates if device is actuator enabled.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DeviceEnable Status Signal Object
     */
    StatusSignal<signals::DeviceEnableValue> &GetDeviceEnable(bool refresh = true) final;
        
    /**
     * \brief The slot that the closed-loop PID is using.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 2
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ClosedLoopSlot Status Signal Object
     */
    StatusSignal<int> &GetClosedLoopSlot(bool refresh = true) final;
        
    /**
     * \brief Assess the status of the motor output with respect to load
     * and supply.
     * 
     * \details This routine can be used to determine the general status
     * of motor commutation.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns MotorOutputStatus Status Signal Object
     */
    StatusSignal<signals::MotorOutputStatusValue> &GetMotorOutputStatus(bool refresh = true) final;
        
    /**
     * \brief The active control mode of the differential controller.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialControlMode Status Signal Object
     */
    StatusSignal<signals::DifferentialControlModeValue> &GetDifferentialControlMode(bool refresh = true) final;
        
    /**
     * \brief Average component of the differential velocity of device.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialAverageVelocity Status Signal Object
     */
    StatusSignal<units::angular_velocity::turns_per_second_t> &GetDifferentialAverageVelocity(bool refresh = true) final;
        
    /**
     * \brief Average component of the differential position of device.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialAveragePosition Status Signal Object
     */
    StatusSignal<units::angle::turn_t> &GetDifferentialAveragePosition(bool refresh = true) final;
        
    /**
     * \brief Difference component of the differential velocity of device.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialDifferenceVelocity Status Signal Object
     */
    StatusSignal<units::angular_velocity::turns_per_second_t> &GetDifferentialDifferenceVelocity(bool refresh = true) final;
        
    /**
     * \brief Difference component of the differential position of device.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialDifferencePosition Status Signal Object
     */
    StatusSignal<units::angle::turn_t> &GetDifferentialDifferencePosition(bool refresh = true) final;
        
    /**
     * \brief The slot that the closed-loop differential PID is using.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 2
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialClosedLoopSlot Status Signal Object
     */
    StatusSignal<int> &GetDifferentialClosedLoopSlot(bool refresh = true) final;
        
    /**
     * \brief The torque constant (K_T) of the motor.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 0.025500000000000002
     * - Default Value: 0
     * - Units: Nm/A
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns MotorKT Status Signal Object
     */
    StatusSignal<ctre::unit::newton_meters_per_ampere_t> &GetMotorKT(bool refresh = true) final;
        
    /**
     * \brief The velocity constant (K_V) of the motor.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 2047.0
     * - Default Value: 0
     * - Units: RPM/V
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns MotorKV Status Signal Object
     */
    StatusSignal<ctre::unit::rpm_per_volt_t> &GetMotorKV(bool refresh = true) final;
        
    /**
     * \brief The stall current of the motor at 12 V output.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1023.0
     * - Default Value: 0
     * - Units: A
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns MotorStallCurrent Status Signal Object
     */
    StatusSignal<units::current::ampere_t> &GetMotorStallCurrent(bool refresh = true) final;
        
    /**
     * \brief The applied output of the bridge.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns BridgeOutput Status Signal Object
     */
    StatusSignal<signals::BridgeOutputValue> &GetBridgeOutput(bool refresh = true) final;
        
    /**
     * \brief Whether the device is Phoenix Pro licensed.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns IsProLicensed Status Signal Object
     */
    StatusSignal<bool> &GetIsProLicensed(bool refresh = true) final;
        
    /**
     * \brief Temperature of device from second sensor.
     * 
     * \details Newer versions of Talon have multiple temperature
     * measurement methods.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 255.0
     * - Default Value: 0
     * - Units: ℃
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns AncillaryDeviceTemp Status Signal Object
     */
    StatusSignal<units::temperature::celsius_t> &GetAncillaryDeviceTemp(bool refresh = true) final;
        
    /**
     * \brief The type of motor attached to the Talon.
     * 
     * \details This can be used to determine what motor is attached to
     * the Talon FX.  Return will be "Unknown" if firmware is too old or
     * device is not present.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ConnectedMotor Status Signal Object
     */
    StatusSignal<signals::ConnectedMotorValue> &GetConnectedMotor(bool refresh = true) final;
        
    /**
     * \brief The measured voltage of the 5V rail available on the JST and
     * dataport connectors.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 40.95
     * - Default Value: 0
     * - Units: Volts
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns FiveVRailVoltage Status Signal Object
     */
    StatusSignal<units::voltage::volt_t> &GetFiveVRailVoltage(bool refresh = true) final;
        
    /**
     * \brief The voltage of the analog pin (pin 3) of the Talon FXS data
     * port. The analog pin reads a nominal voltage of 0-5V.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 6
     * - Default Value: 0
     * - Units: Volts
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns AnalogVoltage Status Signal Object
     */
    StatusSignal<units::voltage::volt_t> &GetAnalogVoltage(bool refresh = true) final;
        
    /**
     * \brief The raw position retrieved from the connected quadrature
     * encoder. This is only affected by the QuadratureEdgesPerRotation
     * config. In most situations, the user should instead configure the
     * ExternalFeedbackSensorSource and use the regular position getter.
     * 
     * This signal must have its update frequency configured before it
     * will have data.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * Default Rates:
     * - CAN: 0.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns RawQuadraturePosition Status Signal Object
     */
    StatusSignal<units::angle::turn_t> &GetRawQuadraturePosition(bool refresh = true) final;
        
    /**
     * \brief The raw velocity retrieved from the connected quadrature
     * encoder. This is only affected by the QuadratureEdgesPerRotation
     * config. In most situations, the user should instead configure the
     * ExternalFeedbackSensorSource and use the regular velocity getter.
     * 
     * This signal must have its update frequency configured before it
     * will have data.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * Default Rates:
     * - CAN: 0.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns RawQuadratureVelocity Status Signal Object
     */
    StatusSignal<units::angular_velocity::turns_per_second_t> &GetRawQuadratureVelocity(bool refresh = true) final;
        
    /**
     * \brief The raw position retrieved from the connected pulse-width
     * encoder. This is not affected by any config. In most situations,
     * the user should instead configure the ExternalFeedbackSensorSource
     * and use the regular position getter.
     * 
     * This signal must have its update frequency configured before it
     * will have data.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * Default Rates:
     * - CAN: 0.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns RawPulseWidthPosition Status Signal Object
     */
    StatusSignal<units::angle::turn_t> &GetRawPulseWidthPosition(bool refresh = true) final;
        
    /**
     * \brief The raw velocity retrieved from the connected pulse-width
     * encoder. This is not affected by any config. In most situations,
     * the user should instead configure the ExternalFeedbackSensorSource
     * and use the regular velocity getter.
     * 
     * This signal must have its update frequency configured before it
     * will have data.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * Default Rates:
     * - CAN: 0.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns RawPulseWidthVelocity Status Signal Object
     */
    StatusSignal<units::angular_velocity::turns_per_second_t> &GetRawPulseWidthVelocity(bool refresh = true) final;
        
    /**
     * \brief Hardware fault occurred
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_Hardware Status Signal Object
     */
    StatusSignal<bool> &GetFault_Hardware(bool refresh = true) final;
        
    /**
     * \brief Hardware fault occurred
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_Hardware Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_Hardware(bool refresh = true) final;
        
    /**
     * \brief Processor temperature exceeded limit
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_ProcTemp Status Signal Object
     */
    StatusSignal<bool> &GetFault_ProcTemp(bool refresh = true) final;
        
    /**
     * \brief Processor temperature exceeded limit
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_ProcTemp Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_ProcTemp(bool refresh = true) final;
        
    /**
     * \brief Device temperature exceeded limit
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_DeviceTemp Status Signal Object
     */
    StatusSignal<bool> &GetFault_DeviceTemp(bool refresh = true) final;
        
    /**
     * \brief Device temperature exceeded limit
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_DeviceTemp Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_DeviceTemp(bool refresh = true) final;
        
    /**
     * \brief Device supply voltage dropped to near brownout levels
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_Undervoltage Status Signal Object
     */
    StatusSignal<bool> &GetFault_Undervoltage(bool refresh = true) final;
        
    /**
     * \brief Device supply voltage dropped to near brownout levels
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_Undervoltage Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_Undervoltage(bool refresh = true) final;
        
    /**
     * \brief Device boot while detecting the enable signal
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_BootDuringEnable Status Signal Object
     */
    StatusSignal<bool> &GetFault_BootDuringEnable(bool refresh = true) final;
        
    /**
     * \brief Device boot while detecting the enable signal
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_BootDuringEnable Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_BootDuringEnable(bool refresh = true) final;
        
    /**
     * \brief An unlicensed feature is in use, device may not behave as
     * expected.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_UnlicensedFeatureInUse Status Signal Object
     */
    StatusSignal<bool> &GetFault_UnlicensedFeatureInUse(bool refresh = true) final;
        
    /**
     * \brief An unlicensed feature is in use, device may not behave as
     * expected.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_UnlicensedFeatureInUse Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_UnlicensedFeatureInUse(bool refresh = true) final;
        
    /**
     * \brief Bridge was disabled most likely due to supply voltage
     * dropping too low.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_BridgeBrownout Status Signal Object
     */
    StatusSignal<bool> &GetFault_BridgeBrownout(bool refresh = true) final;
        
    /**
     * \brief Bridge was disabled most likely due to supply voltage
     * dropping too low.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_BridgeBrownout Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_BridgeBrownout(bool refresh = true) final;
        
    /**
     * \brief The remote sensor has reset.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_RemoteSensorReset Status Signal Object
     */
    StatusSignal<bool> &GetFault_RemoteSensorReset(bool refresh = true) final;
        
    /**
     * \brief The remote sensor has reset.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_RemoteSensorReset Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_RemoteSensorReset(bool refresh = true) final;
        
    /**
     * \brief The remote Talon used for differential control is not
     * present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_MissingDifferentialFX Status Signal Object
     */
    StatusSignal<bool> &GetFault_MissingDifferentialFX(bool refresh = true) final;
        
    /**
     * \brief The remote Talon used for differential control is not
     * present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_MissingDifferentialFX Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_MissingDifferentialFX(bool refresh = true) final;
        
    /**
     * \brief The remote sensor position has overflowed. Because of the
     * nature of remote sensors, it is possible for the remote sensor
     * position to overflow beyond what is supported by the status signal
     * frame. However, this is rare and cannot occur over the course of an
     * FRC match under normal use.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_RemoteSensorPosOverflow Status Signal Object
     */
    StatusSignal<bool> &GetFault_RemoteSensorPosOverflow(bool refresh = true) final;
        
    /**
     * \brief The remote sensor position has overflowed. Because of the
     * nature of remote sensors, it is possible for the remote sensor
     * position to overflow beyond what is supported by the status signal
     * frame. However, this is rare and cannot occur over the course of an
     * FRC match under normal use.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_RemoteSensorPosOverflow Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_RemoteSensorPosOverflow(bool refresh = true) final;
        
    /**
     * \brief Supply Voltage has exceeded the maximum voltage rating of
     * device.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_OverSupplyV Status Signal Object
     */
    StatusSignal<bool> &GetFault_OverSupplyV(bool refresh = true) final;
        
    /**
     * \brief Supply Voltage has exceeded the maximum voltage rating of
     * device.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_OverSupplyV Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_OverSupplyV(bool refresh = true) final;
        
    /**
     * \brief Supply Voltage is unstable.  Ensure you are using a battery
     * and current limited power supply.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_UnstableSupplyV Status Signal Object
     */
    StatusSignal<bool> &GetFault_UnstableSupplyV(bool refresh = true) final;
        
    /**
     * \brief Supply Voltage is unstable.  Ensure you are using a battery
     * and current limited power supply.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_UnstableSupplyV Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_UnstableSupplyV(bool refresh = true) final;
        
    /**
     * \brief Reverse limit switch has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_ReverseHardLimit Status Signal Object
     */
    StatusSignal<bool> &GetFault_ReverseHardLimit(bool refresh = true) final;
        
    /**
     * \brief Reverse limit switch has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_ReverseHardLimit Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_ReverseHardLimit(bool refresh = true) final;
        
    /**
     * \brief Forward limit switch has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_ForwardHardLimit Status Signal Object
     */
    StatusSignal<bool> &GetFault_ForwardHardLimit(bool refresh = true) final;
        
    /**
     * \brief Forward limit switch has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_ForwardHardLimit Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_ForwardHardLimit(bool refresh = true) final;
        
    /**
     * \brief Reverse soft limit has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_ReverseSoftLimit Status Signal Object
     */
    StatusSignal<bool> &GetFault_ReverseSoftLimit(bool refresh = true) final;
        
    /**
     * \brief Reverse soft limit has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_ReverseSoftLimit Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_ReverseSoftLimit(bool refresh = true) final;
        
    /**
     * \brief Forward soft limit has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_ForwardSoftLimit Status Signal Object
     */
    StatusSignal<bool> &GetFault_ForwardSoftLimit(bool refresh = true) final;
        
    /**
     * \brief Forward soft limit has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_ForwardSoftLimit Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_ForwardSoftLimit(bool refresh = true) final;
        
    /**
     * \brief The remote soft limit device is not present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_MissingSoftLimitRemote Status Signal Object
     */
    StatusSignal<bool> &GetFault_MissingSoftLimitRemote(bool refresh = true) final;
        
    /**
     * \brief The remote soft limit device is not present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_MissingSoftLimitRemote Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_MissingSoftLimitRemote(bool refresh = true) final;
        
    /**
     * \brief The remote limit switch device is not present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_MissingHardLimitRemote Status Signal Object
     */
    StatusSignal<bool> &GetFault_MissingHardLimitRemote(bool refresh = true) final;
        
    /**
     * \brief The remote limit switch device is not present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_MissingHardLimitRemote Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_MissingHardLimitRemote(bool refresh = true) final;
        
    /**
     * \brief The remote sensor's data is no longer trusted. This can
     * happen if the remote sensor disappears from the CAN bus or if the
     * remote sensor indicates its data is no longer valid, such as when a
     * CANcoder's magnet strength falls into the "red" range.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_RemoteSensorDataInvalid Status Signal Object
     */
    StatusSignal<bool> &GetFault_RemoteSensorDataInvalid(bool refresh = true) final;
        
    /**
     * \brief The remote sensor's data is no longer trusted. This can
     * happen if the remote sensor disappears from the CAN bus or if the
     * remote sensor indicates its data is no longer valid, such as when a
     * CANcoder's magnet strength falls into the "red" range.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_RemoteSensorDataInvalid Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_RemoteSensorDataInvalid(bool refresh = true) final;
        
    /**
     * \brief The remote sensor used for fusion has fallen out of sync to
     * the local sensor. A re-synchronization has occurred, which may
     * cause a discontinuity. This typically happens if there is
     * significant slop in the mechanism, or if the RotorToSensorRatio
     * configuration parameter is incorrect.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_FusedSensorOutOfSync Status Signal Object
     */
    StatusSignal<bool> &GetFault_FusedSensorOutOfSync(bool refresh = true) final;
        
    /**
     * \brief The remote sensor used for fusion has fallen out of sync to
     * the local sensor. A re-synchronization has occurred, which may
     * cause a discontinuity. This typically happens if there is
     * significant slop in the mechanism, or if the RotorToSensorRatio
     * configuration parameter is incorrect.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_FusedSensorOutOfSync Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_FusedSensorOutOfSync(bool refresh = true) final;
        
    /**
     * \brief Stator current limit occured.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_StatorCurrLimit Status Signal Object
     */
    StatusSignal<bool> &GetFault_StatorCurrLimit(bool refresh = true) final;
        
    /**
     * \brief Stator current limit occured.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_StatorCurrLimit Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_StatorCurrLimit(bool refresh = true) final;
        
    /**
     * \brief Supply current limit occured.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_SupplyCurrLimit Status Signal Object
     */
    StatusSignal<bool> &GetFault_SupplyCurrLimit(bool refresh = true) final;
        
    /**
     * \brief Supply current limit occured.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_SupplyCurrLimit Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_SupplyCurrLimit(bool refresh = true) final;
        
    /**
     * \brief Using Fused CANcoder feature while unlicensed. Device has
     * fallen back to remote CANcoder.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_UsingFusedCANcoderWhileUnlicensed Status Signal Object
     */
    StatusSignal<bool> &GetFault_UsingFusedCANcoderWhileUnlicensed(bool refresh = true) final;
        
    /**
     * \brief Using Fused CANcoder feature while unlicensed. Device has
     * fallen back to remote CANcoder.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_UsingFusedCANcoderWhileUnlicensed Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_UsingFusedCANcoderWhileUnlicensed(bool refresh = true) final;
        
    /**
     * \brief Static brake was momentarily disabled due to excessive
     * braking current while disabled.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_StaticBrakeDisabled Status Signal Object
     */
    StatusSignal<bool> &GetFault_StaticBrakeDisabled(bool refresh = true) final;
        
    /**
     * \brief Static brake was momentarily disabled due to excessive
     * braking current while disabled.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_StaticBrakeDisabled Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_StaticBrakeDisabled(bool refresh = true) final;
        
    /**
     * \brief Bridge was disabled most likely due to a short in the motor
     * leads.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_BridgeShort Status Signal Object
     */
    StatusSignal<bool> &GetFault_BridgeShort(bool refresh = true) final;
        
    /**
     * \brief Bridge was disabled most likely due to a short in the motor
     * leads.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_BridgeShort Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_BridgeShort(bool refresh = true) final;
        
    /**
     * \brief Hall sensor signals are invalid.  Check hall sensor and
     * cabling.  This fault can be used to detect when hall cable is
     * unplugged.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_HallSensorMissing Status Signal Object
     */
    StatusSignal<bool> &GetFault_HallSensorMissing(bool refresh = true) final;
        
    /**
     * \brief Hall sensor signals are invalid.  Check hall sensor and
     * cabling.  This fault can be used to detect when hall cable is
     * unplugged.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_HallSensorMissing Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_HallSensorMissing(bool refresh = true) final;
        
    /**
     * \brief Hall sensor signals are invalid during motor drive, so motor
     * was disabled.  Check hall sensor and cabling.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_DriveDisabledHallSensor Status Signal Object
     */
    StatusSignal<bool> &GetFault_DriveDisabledHallSensor(bool refresh = true) final;
        
    /**
     * \brief Hall sensor signals are invalid during motor drive, so motor
     * was disabled.  Check hall sensor and cabling.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_DriveDisabledHallSensor Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_DriveDisabledHallSensor(bool refresh = true) final;
        
    /**
     * \brief Motor temperature signal appears to not be connected.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_MotorTempSensorMissing Status Signal Object
     */
    StatusSignal<bool> &GetFault_MotorTempSensorMissing(bool refresh = true) final;
        
    /**
     * \brief Motor temperature signal appears to not be connected.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_MotorTempSensorMissing Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_MotorTempSensorMissing(bool refresh = true) final;
        
    /**
     * \brief Motor temperature signal indicates motor is too hot.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_MotorTempSensorTooHot Status Signal Object
     */
    StatusSignal<bool> &GetFault_MotorTempSensorTooHot(bool refresh = true) final;
        
    /**
     * \brief Motor temperature signal indicates motor is too hot.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_MotorTempSensorTooHot Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_MotorTempSensorTooHot(bool refresh = true) final;
        
    /**
     * \brief Motor arrangement has not been set in configuration.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_MotorArrangementNotSelected Status Signal Object
     */
    StatusSignal<bool> &GetFault_MotorArrangementNotSelected(bool refresh = true) final;
        
    /**
     * \brief Motor arrangement has not been set in configuration.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_MotorArrangementNotSelected Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_MotorArrangementNotSelected(bool refresh = true) final;
        
    /**
     * \brief The CTR Electronics' TalonFX device has detected a 5V fault.
     * This may be due to overcurrent or a short-circuit.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns Fault_5V Status Signal Object
     */
    StatusSignal<bool> &GetFault_5V(bool refresh = true) final;
        
    /**
     * \brief The CTR Electronics' TalonFX device has detected a 5V fault.
     * This may be due to overcurrent or a short-circuit.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns StickyFault_5V Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_5V(bool refresh = true) final;
    
    /**
     * \brief Closed loop proportional component.
     * 
     * \details The portion of the closed loop output that is proportional
     * to the error. Alternatively, the kP contribution of the closed loop
     * output.
     * 
     * When using differential control, this applies to the average axis.
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ClosedLoopProportionalOutput Status Signal object
     */
    StatusSignal<double> &GetClosedLoopProportionalOutput(bool refresh = true) final;
    
    /**
     * \brief Closed loop integrated component.
     * 
     * \details The portion of the closed loop output that is proportional
     * to the integrated error. Alternatively, the kI contribution of the
     * closed loop output.
     * 
     * When using differential control, this applies to the average axis.
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ClosedLoopIntegratedOutput Status Signal object
     */
    StatusSignal<double> &GetClosedLoopIntegratedOutput(bool refresh = true) final;
    
    /**
     * \brief Feedforward passed by the user.
     * 
     * \details This is the general feedforward that the user provides for
     * the closed loop.
     * 
     * When using differential control, this applies to the average axis.
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ClosedLoopFeedForward Status Signal object
     */
    StatusSignal<double> &GetClosedLoopFeedForward(bool refresh = true) final;
    
    /**
     * \brief Closed loop derivative component.
     * 
     * \details The portion of the closed loop output that is proportional
     * to the deriviative of error. Alternatively, the kD contribution of
     * the closed loop output.
     * 
     * When using differential control, this applies to the average axis.
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ClosedLoopDerivativeOutput Status Signal object
     */
    StatusSignal<double> &GetClosedLoopDerivativeOutput(bool refresh = true) final;
    
    /**
     * \brief Closed loop total output.
     * 
     * \details The total output of the closed loop output.
     * 
     * When using differential control, this applies to the average axis.
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ClosedLoopOutput Status Signal object
     */
    StatusSignal<double> &GetClosedLoopOutput(bool refresh = true) final;
    
    /**
     * \brief Value that the closed loop is targeting.
     * 
     * \details This is the value that the closed loop PID controller
     * targets.
     * 
     * When using differential control, this applies to the average axis.
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ClosedLoopReference Status Signal object
     */
    StatusSignal<double> &GetClosedLoopReference(bool refresh = true) final;
    
    /**
     * \brief Derivative of the target that the closed loop is targeting.
     * 
     * \details This is the change in the closed loop reference. This may
     * be used in the feed-forward calculation, the derivative-error, or
     * in application of the signage for kS. Typically, this represents
     * the target velocity during Motion Magic®.
     * 
     * When using differential control, this applies to the average axis.
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ClosedLoopReferenceSlope Status Signal object
     */
    StatusSignal<double> &GetClosedLoopReferenceSlope(bool refresh = true) final;
    
    /**
     * \brief The difference between target reference and current
     * measurement.
     * 
     * \details This is the value that is treated as the error in the PID
     * loop.
     * 
     * When using differential control, this applies to the average axis.
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns ClosedLoopError Status Signal object
     */
    StatusSignal<double> &GetClosedLoopError(bool refresh = true) final;
    
    /**
     * \brief The calculated motor output for differential followers.
     * 
     * \details This is a torque request when using the TorqueCurrentFOC
     * control output type, a voltage request when using the Voltage
     * control output type, and a duty cycle when using the DutyCycle
     * control output type.
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialOutput Status Signal object
     */
    StatusSignal<double> &GetDifferentialOutput(bool refresh = true) final;
    
    /**
     * \brief Differential closed loop proportional component.
     * 
     * \details The portion of the differential closed loop output (on the
     * difference axis) that is proportional to the error. Alternatively,
     * the kP contribution of the closed loop output.
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialClosedLoopProportionalOutput Status Signal object
     */
    StatusSignal<double> &GetDifferentialClosedLoopProportionalOutput(bool refresh = true) final;
    
    /**
     * \brief Differential closed loop integrated component.
     * 
     * \details The portion of the differential closed loop output (on the
     * difference axis) that is proportional to the integrated error.
     * Alternatively, the kI contribution of the closed loop output.
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialClosedLoopIntegratedOutput Status Signal object
     */
    StatusSignal<double> &GetDifferentialClosedLoopIntegratedOutput(bool refresh = true) final;
    
    /**
     * \brief Differential Feedforward passed by the user.
     * 
     * \details This is the general feedforward that the user provides for
     * the differential closed loop (on the difference axis).
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialClosedLoopFeedForward Status Signal object
     */
    StatusSignal<double> &GetDifferentialClosedLoopFeedForward(bool refresh = true) final;
    
    /**
     * \brief Differential closed loop derivative component.
     * 
     * \details The portion of the differential closed loop output (on the
     * difference axis) that is proportional to the deriviative of error.
     * Alternatively, the kD contribution of the closed loop output.
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialClosedLoopDerivativeOutput Status Signal object
     */
    StatusSignal<double> &GetDifferentialClosedLoopDerivativeOutput(bool refresh = true) final;
    
    /**
     * \brief Differential closed loop total output.
     * 
     * \details The total output of the differential closed loop output
     * (on the difference axis).
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialClosedLoopOutput Status Signal object
     */
    StatusSignal<double> &GetDifferentialClosedLoopOutput(bool refresh = true) final;
    
    /**
     * \brief Value that the differential closed loop is targeting.
     * 
     * \details This is the value that the differential closed loop PID
     * controller targets (on the difference axis).
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialClosedLoopReference Status Signal object
     */
    StatusSignal<double> &GetDifferentialClosedLoopReference(bool refresh = true) final;
    
    /**
     * \brief Derivative of the target that the differential closed loop
     * is targeting.
     * 
     * \details This is the change in the closed loop reference (on the
     * difference axis). This may be used in the feed-forward calculation,
     * the derivative-error, or in application of the signage for kS.
     * Typically, this represents the target velocity during Motion
     * Magic®.
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialClosedLoopReferenceSlope Status Signal object
     */
    StatusSignal<double> &GetDifferentialClosedLoopReferenceSlope(bool refresh = true) final;
    
    /**
     * \brief The difference between target differential reference and
     * current measurement.
     * 
     * \details This is the value that is treated as the error in the
     * differential PID loop (on the difference axis).
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it;
     *                defaults to true
     * \returns DifferentialClosedLoopError Status Signal object
     */
    StatusSignal<double> &GetDifferentialClosedLoopError(bool refresh = true) final;

    
    /**
     * \brief Request a specified motor duty cycle.
     * 
     * \details This control mode will output a proportion of the supplied
     * voltage which is supplied by the user.
     * 
     * - DutyCycleOut Parameters: 
     *   - Output: Proportion of supply voltage to apply in fractional units between
     *             -1 and +1
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DutyCycleOut const &request) final;
    
    /**
     * \brief Request a specified voltage.
     * 
     * \details This control mode will attempt to apply the specified
     * voltage to the motor. If the supply voltage is below the requested
     * voltage, the motor controller will output the supply voltage.
     * 
     * - VoltageOut Parameters: 
     *   - Output: Voltage to attempt to drive at
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::VoltageOut const &request) final;
    
    /**
     * \brief Request PID to target position with duty cycle feedforward.
     * 
     * \details This control mode will set the motor's position setpoint
     * to the position specified by the user. In addition, it will apply
     * an additional duty cycle as an arbitrary feedforward value.
     * 
     * - PositionDutyCycle Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - Velocity: Velocity to drive toward in rotations per second. This is
     *               typically used for motion profiles generated by the robot
     *               program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::PositionDutyCycle const &request) final;
    
    /**
     * \brief Request PID to target position with voltage feedforward
     * 
     * \details This control mode will set the motor's position setpoint
     * to the position specified by the user. In addition, it will apply
     * an additional voltage as an arbitrary feedforward value.
     * 
     * - PositionVoltage Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - Velocity: Velocity to drive toward in rotations per second. This is
     *               typically used for motion profiles generated by the robot
     *               program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::PositionVoltage const &request) final;
    
    /**
     * \brief Request PID to target velocity with duty cycle feedforward.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. In addition, it will apply
     * an additional voltage as an arbitrary feedforward value.
     * 
     * - VelocityDutyCycle Parameters: 
     *   - Velocity: Velocity to drive toward in rotations per second.
     *   - Acceleration: Acceleration to drive toward in rotations per second
     *                   squared. This is typically used for motion profiles
     *                   generated by the robot program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::VelocityDutyCycle const &request) final;
    
    /**
     * \brief Request PID to target velocity with voltage feedforward.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. In addition, it will apply
     * an additional voltage as an arbitrary feedforward value.
     * 
     * - VelocityVoltage Parameters: 
     *   - Velocity: Velocity to drive toward in rotations per second.
     *   - Acceleration: Acceleration to drive toward in rotations per second
     *                   squared. This is typically used for motion profiles
     *                   generated by the robot program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts This is added to the output of
     *                  the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::VelocityVoltage const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  Users can optionally provide a duty cycle
     * feedforward.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the Cruise Velocity, Acceleration, and
     * (optional) Jerk specified via the Motion Magic® configuration
     * values.  This control mode does not use the Expo_kV or Expo_kA
     * configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - MotionMagicDutyCycle Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::MotionMagicDutyCycle const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  Users can optionally provide a voltage
     * feedforward.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the Cruise Velocity, Acceleration, and
     * (optional) Jerk specified via the Motion Magic® configuration
     * values.  This control mode does not use the Expo_kV or Expo_kA
     * configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - MotionMagicVoltage Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::MotionMagicVoltage const &request) final;
    
    /**
     * \brief Request a specified motor duty cycle with a differential
     * position closed-loop.
     * 
     * \details This control mode will output a proportion of the supplied
     * voltage which is supplied by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialDutyCycle Parameters: 
     *   - AverageOutput: Proportion of supply voltage to apply on the Average axis
     *                    in fractional units between -1 and +1.
     *   - DifferentialPosition: Differential position to drive towards in
     *                           rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialDutyCycle const &request) final;
    
    /**
     * \brief Request a specified voltage with a differential position
     * closed-loop.
     * 
     * \details This control mode will attempt to apply the specified
     * voltage to the motor. If the supply voltage is below the requested
     * voltage, the motor controller will output the supply voltage. It
     * will also set the motor's differential position setpoint to the
     * specified position.
     * 
     * - DifferentialVoltage Parameters: 
     *   - AverageOutput: Voltage to attempt to drive at on the Average axis.
     *   - DifferentialPosition: Differential position to drive towards in
     *                           rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialVoltage const &request) final;
    
    /**
     * \brief Request PID to target position with a differential position
     * setpoint.
     * 
     * \details This control mode will set the motor's position setpoint
     * to the position specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialPositionDutyCycle Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialPositionDutyCycle const &request) final;
    
    /**
     * \brief Request PID to target position with a differential position
     * setpoint
     * 
     * \details This control mode will set the motor's position setpoint
     * to the position specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialPositionVoltage Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialPositionVoltage const &request) final;
    
    /**
     * \brief Request PID to target velocity with a differential position
     * setpoint.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialVelocityDutyCycle Parameters: 
     *   - AverageVelocity: Average velocity to drive toward in rotations per
     *                      second.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialVelocityDutyCycle const &request) final;
    
    /**
     * \brief Request PID to target velocity with a differential position
     * setpoint.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialVelocityVoltage Parameters: 
     *   - AverageVelocity: Average velocity to drive toward in rotations per
     *                      second.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialVelocityVoltage const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile, and PID to a differential position setpoint.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the Cruise Velocity, Acceleration, and
     * (optional) Jerk specified via the Motion Magic® configuration
     * values.  This control mode does not use the Expo_kV or Expo_kA
     * configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - DifferentialMotionMagicDutyCycle Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicDutyCycle const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile, and PID to a differential position setpoint.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the Cruise Velocity, Acceleration, and
     * (optional) Jerk specified via the Motion Magic® configuration
     * values.  This control mode does not use the Expo_kV or Expo_kA
     * configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - DifferentialMotionMagicVoltage Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicVoltage const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final position using an
     * exponential motion profile, and PID to a differential position
     * setpoint.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the Cruise Velocity (optional) and the
     * mechanism kV and kA, specified via the Motion Magic® configuration
     * values.  Note that unlike the slot gains, the Expo_kV and Expo_kA
     * configs are always in output units of Volts.
     * 
     * Setting Cruise Velocity to 0 will allow the profile to run to the
     * max possible velocity based on Expo_kV.  This control mode does not
     * use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - DifferentialMotionMagicExpoDutyCycle Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicExpoDutyCycle const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final position using an
     * exponential motion profile, and PID to a differential position
     * setpoint.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the Cruise Velocity (optional) and the
     * mechanism kV and kA, specified via the Motion Magic® configuration
     * values.  Note that unlike the slot gains, the Expo_kV and Expo_kA
     * configs are always in output units of Volts.
     * 
     * Setting Cruise Velocity to 0 will allow the profile to run to the
     * max possible velocity based on Expo_kV.  This control mode does not
     * use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - DifferentialMotionMagicExpoVoltage Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicExpoVoltage const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final velocity using a
     * motion profile, and PID to a differential position setpoint.  This
     * allows smooth transitions between velocity set points.
     * 
     * \details Motion Magic® Velocity produces a motion profile in
     * real-time while attempting to honor the specified Acceleration and
     * (optional) Jerk.  This control mode does not use the
     * CruiseVelocity, Expo_kV, or Expo_kA configs.
     * 
     * Acceleration and jerk are specified in the Motion Magic® persistent
     * configuration values.  If Jerk is set to zero, Motion Magic® will
     * produce a trapezoidal acceleration profile.
     * 
     * Target velocity can also be changed on-the-fly and Motion Magic®
     * will do its best to adjust the profile.  This control mode is duty
     * cycle based, so relevant closed-loop gains will use fractional duty
     * cycle for the numerator:  +1.0 represents full forward output.
     * 
     * - DifferentialMotionMagicVelocityDutyCycle Parameters: 
     *   - AverageVelocity: Average velocity to drive toward in rotations per
     *                      second.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicVelocityDutyCycle const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final velocity using a
     * motion profile, and PID to a differential position setpoint.  This
     * allows smooth transitions between velocity set points.
     * 
     * \details Motion Magic® Velocity produces a motion profile in
     * real-time while attempting to honor the specified Acceleration and
     * (optional) Jerk.  This control mode does not use the
     * CruiseVelocity, Expo_kV, or Expo_kA configs.
     * 
     * Acceleration and jerk are specified in the Motion Magic® persistent
     * configuration values.  If Jerk is set to zero, Motion Magic® will
     * produce a trapezoidal acceleration profile.
     * 
     * Target velocity can also be changed on-the-fly and Motion Magic®
     * will do its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - DifferentialMotionMagicVelocityVoltage Parameters: 
     *   - AverageVelocity: Average velocity to drive toward in rotations per
     *                      second.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicVelocityVoltage const &request) final;
    
    /**
     * \brief Follow the motor output of another Talon.
     * 
     * \details The follower will atomically change its output type when
     * it receives the leader's latest output status signal (DutyCycle,
     * MotorVoltage, TorqueCurrent). If Talon is in torque control, the
     * torque is copied - which will increase the total torque applied. If
     * Talon is in duty cycle output control, the duty cycle is matched.
     * If Talon is in voltage output control, the motor voltage is
     * matched. Motor direction either matches the leader's configured
     * direction or opposes it based on the MotorAlignment.
     * 
     * The leader must ensure the status signal corresponding to its
     * control output type (DutyCycle, MotorVoltage, TorqueCurrent) is
     * enabled. The update rate of the status signal determines the update
     * rate of the follower's output and should be no slower than 20 Hz.
     * 
     * - Follower Parameters: 
     *   - LeaderID: Device ID of the leader to follow.
     *   - MotorAlignment: Set to Aligned for motor invert to match the leader's
     *                     configured Invert - which is typical when leader and
     *                     follower are mechanically linked and spin in the same
     *                     direction.  Set to Opposed for motor invert to oppose the
     *                     leader's configured Invert - this is typical where the
     *                     leader and follower mechanically spin in opposite
     *                     directions.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::Follower const &request) final;
    
    /**
     * \brief Follow the motor output of another Talon while ignoring the
     * leader's invert setting.
     * 
     * \details The follower will atomically change its output type when
     * it receives the leader's latest output status signal (DutyCycle,
     * MotorVoltage, TorqueCurrent). If Talon is in torque control, the
     * torque is copied - which will increase the total torque applied. If
     * Talon is in duty cycle output control, the duty cycle is matched.
     * If Talon is in voltage output control, the motor voltage is
     * matched. Motor direction is strictly determined by the configured
     * invert and not the leader. If you want motor direction to match or
     * oppose the leader, use Follower instead.
     * 
     * The leader must ensure the status signal corresponding to its
     * control output type (DutyCycle, MotorVoltage, TorqueCurrent) is
     * enabled. The update rate of the status signal determines the update
     * rate of the follower's output and should be no slower than 20 Hz.
     * 
     * - StrictFollower Parameters: 
     *   - LeaderID: Device ID of the leader to follow.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::StrictFollower const &request) final;
    
    /**
     * \brief Follow the differential motor output of another Talon.
     * 
     * \details If Talon is in torque control, the differential torque is
     * copied - which will increase the total torque applied. If Talon is
     * in duty cycle output control, the differential duty cycle is
     * matched. If Talon is in voltage output control, the differential
     * motor voltage is matched. Motor direction either matches leader's
     * configured direction or opposes it based on the MotorAlignment.
     * 
     * The leader must enable its DifferentialOutput status signal. The
     * update rate of the status signal determines the update rate of the
     * follower's output and should be no slower than 20 Hz.
     * 
     * - DifferentialFollower Parameters: 
     *   - LeaderID: Device ID of the differential leader to follow.
     *   - MotorAlignment: Set to Aligned for motor invert to match the leader's
     *                     configured Invert - which is typical when leader and
     *                     follower are mechanically linked and spin in the same
     *                     direction.  Set to Opposed for motor invert to oppose the
     *                     leader's configured Invert - this is typical where the
     *                     leader and follower mechanically spin in opposite
     *                     directions.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialFollower const &request) final;
    
    /**
     * \brief Follow the differential motor output of another Talon while
     * ignoring the leader's invert setting.
     * 
     * \details If Talon is in torque control, the differential torque is
     * copied - which will increase the total torque applied. If Talon is
     * in duty cycle output control, the differential duty cycle is
     * matched. If Talon is in voltage output control, the differential
     * motor voltage is matched. Motor direction is strictly determined by
     * the configured invert and not the leader. If you want motor
     * direction to match or oppose the leader, use DifferentialFollower
     * instead.
     * 
     * The leader must enable its DifferentialOutput status signal. The
     * update rate of the status signal determines the update rate of the
     * follower's output and should be no slower than 20 Hz.
     * 
     * - DifferentialStrictFollower Parameters: 
     *   - LeaderID: Device ID of the differential leader to follow.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialStrictFollower const &request) final;
    
    /**
     * \brief Request neutral output of actuator. The applied brake type
     * is determined by the NeutralMode configuration.
     * 
     * - NeutralOut Parameters: 
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::NeutralOut const &request) final;
    
    /**
     * \brief Request coast neutral output of actuator.  The bridge is
     * disabled and the rotor is allowed to coast.
     * 
     * - CoastOut Parameters: 
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::CoastOut const &request) final;
    
    /**
     * \brief Applies full neutral-brake by shorting motor leads together.
     * 
     * - StaticBrake Parameters: 
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::StaticBrake const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final velocity using a
     * motion profile.  This allows smooth transitions between velocity
     * set points.  Users can optionally provide a duty cycle feedforward.
     * 
     * \details Motion Magic® Velocity produces a motion profile in
     * real-time while attempting to honor the specified Acceleration and
     * (optional) Jerk.  This control mode does not use the
     * CruiseVelocity, Expo_kV, or Expo_kA configs.
     * 
     * If the specified acceleration is zero, the Acceleration under
     * Motion Magic® configuration parameter is used instead.  This allows
     * for runtime adjustment of acceleration for advanced users.  Jerk is
     * also specified in the Motion Magic® persistent configuration
     * values.  If Jerk is set to zero, Motion Magic® will produce a
     * trapezoidal acceleration profile.
     * 
     * Target velocity can also be changed on-the-fly and Motion Magic®
     * will do its best to adjust the profile.  This control mode is duty
     * cycle based, so relevant closed-loop gains will use fractional duty
     * cycle for the numerator:  +1.0 represents full forward output.
     * 
     * - MotionMagicVelocityDutyCycle Parameters: 
     *   - Velocity: Target velocity to drive toward in rotations per second.  This
     *               can be changed on-the fly.
     *   - Acceleration: This is the absolute Acceleration to use generating the
     *                   profile.  If this parameter is zero, the Acceleration
     *                   persistent configuration parameter is used instead.
     *                   Acceleration is in rotations per second squared.  If
     *                   nonzero, the signage does not matter as the absolute value
     *                   is used.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::MotionMagicVelocityDutyCycle const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final velocity using a
     * motion profile.  This allows smooth transitions between velocity
     * set points.  Users can optionally provide a voltage feedforward.
     * 
     * \details Motion Magic® Velocity produces a motion profile in
     * real-time while attempting to honor the specified Acceleration and
     * (optional) Jerk.  This control mode does not use the
     * CruiseVelocity, Expo_kV, or Expo_kA configs.
     * 
     * If the specified acceleration is zero, the Acceleration under
     * Motion Magic® configuration parameter is used instead.  This allows
     * for runtime adjustment of acceleration for advanced users.  Jerk is
     * also specified in the Motion Magic® persistent configuration
     * values.  If Jerk is set to zero, Motion Magic® will produce a
     * trapezoidal acceleration profile.
     * 
     * Target velocity can also be changed on-the-fly and Motion Magic®
     * will do its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - MotionMagicVelocityVoltage Parameters: 
     *   - Velocity: Target velocity to drive toward in rotations per second.  This
     *               can be changed on-the fly.
     *   - Acceleration: This is the absolute Acceleration to use generating the
     *                   profile.  If this parameter is zero, the Acceleration
     *                   persistent configuration parameter is used instead.
     *                   Acceleration is in rotations per second squared.  If
     *                   nonzero, the signage does not matter as the absolute value
     *                   is used.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::MotionMagicVelocityVoltage const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final position using an
     * exponential motion profile.  Users can optionally provide a duty
     * cycle feedforward.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the Cruise Velocity (optional) and the
     * mechanism kV and kA, specified via the Motion Magic® configuration
     * values.  Note that unlike the slot gains, the Expo_kV and Expo_kA
     * configs are always in output units of Volts.
     * 
     * Setting Cruise Velocity to 0 will allow the profile to run to the
     * max possible velocity based on Expo_kV.  This control mode does not
     * use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - MotionMagicExpoDutyCycle Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::MotionMagicExpoDutyCycle const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final position using an
     * exponential motion profile.  Users can optionally provide a voltage
     * feedforward.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the Cruise Velocity (optional) and the
     * mechanism kV and kA, specified via the Motion Magic® configuration
     * values.  Note that unlike the slot gains, the Expo_kV and Expo_kA
     * configs are always in output units of Volts.
     * 
     * Setting Cruise Velocity to 0 will allow the profile to run to the
     * max possible velocity based on Expo_kV.  This control mode does not
     * use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - MotionMagicExpoVoltage Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::MotionMagicExpoVoltage const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  This dynamic request allows runtime changes to
     * Cruise Velocity, Acceleration, and (optional) Jerk.  Users can
     * optionally provide a duty cycle feedforward.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the specified Cruise Velocity, Acceleration,
     * and (optional) Jerk.  This control mode does not use the Expo_kV or
     * Expo_kA configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile. This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - DynamicMotionMagicDutyCycle Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - Velocity: Cruise velocity for profiling.  The signage does not matter as
     *               the device will use the absolute value for profile generation.
     *   - Acceleration: Acceleration for profiling.  The signage does not matter as
     *                   the device will use the absolute value for profile
     *                   generation
     *   - Jerk: Jerk for profiling.  The signage does not matter as the device will
     *           use the absolute value for profile generation.
     *           
     *           Jerk is optional; if this is set to zero, then Motion Magic® will
     *           not apply a Jerk limit.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DynamicMotionMagicDutyCycle const &request) final;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  This dynamic request allows runtime changes to
     * Cruise Velocity, Acceleration, and (optional) Jerk.  Users can
     * optionally provide a voltage feedforward.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the specified Cruise Velocity, Acceleration,
     * and (optional) Jerk.  This control mode does not use the Expo_kV or
     * Expo_kA configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - DynamicMotionMagicVoltage Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - Velocity: Cruise velocity for profiling.  The signage does not matter as
     *               the device will use the absolute value for profile generation.
     *   - Acceleration: Acceleration for profiling.  The signage does not matter as
     *                   the device will use the absolute value for profile
     *                   generation.
     *   - Jerk: Jerk for profiling.  The signage does not matter as the device will
     *           use the absolute value for profile generation.
     *           
     *           Jerk is optional; if this is set to zero, then Motion Magic® will
     *           not apply a Jerk limit.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DynamicMotionMagicVoltage const &request) final;
    
    /**
     * \brief Requests Motion Magic® Expo to target a final position using
     * an exponential motion profile.  This dynamic request allows runtime
     * changes to the profile kV, kA, and (optional) Cruise Velocity. 
     * Users can optionally provide a duty cycle feedforward.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the specified Cruise Velocity (optional)
     * and the mechanism kV and kA.  Note that unlike the slot gains, the
     * Expo_kV and Expo_kA parameters are always in output units of Volts.
     * 
     * Setting the Cruise Velocity to 0 will allow the profile to run to
     * the max possible velocity based on Expo_kV.  This control mode does
     * not use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile. This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - DynamicMotionMagicExpoDutyCycle Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - kV: Mechanism kV for profiling.  Unlike the kV slot gain, this is always
     *         in units of V/rps.
     *         
     *         This represents the amount of voltage necessary to hold a velocity. 
     *         In terms of the Motion Magic® Expo profile, a higher kV results in a
     *         slower maximum velocity.
     *   - kA: Mechanism kA for profiling.  Unlike the kA slot gain, this is always
     *         in units of V/rps².
     *         
     *         This represents the amount of voltage necessary to achieve an
     *         acceleration.  In terms of the Motion Magic® Expo profile, a higher
     *         kA results in a slower acceleration.
     *   - Velocity: Cruise velocity for profiling.  The signage does not matter as
     *               the device will use the absolute value for profile generation. 
     *               Setting this to 0 will allow the profile to run to the max
     *               possible velocity based on Expo_kV.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DynamicMotionMagicExpoDutyCycle const &request) final;
    
    /**
     * \brief Requests Motion Magic® Expo to target a final position using
     * an exponential motion profile.  This dynamic request allows runtime
     * changes to the profile kV, kA, and (optional) Cruise Velocity. 
     * Users can optionally provide a voltage feedforward.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the specified Cruise Velocity (optional)
     * and the mechanism kV and kA.  Note that unlike the slot gains, the
     * Expo_kV and Expo_kA parameters are always in output units of Volts.
     * 
     * Setting the Cruise Velocity to 0 will allow the profile to run to
     * the max possible velocity based on Expo_kV.  This control mode does
     * not use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - DynamicMotionMagicExpoVoltage Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - kV: Mechanism kV for profiling.  Unlike the kV slot gain, this is always
     *         in units of V/rps.
     *         
     *         This represents the amount of voltage necessary to hold a velocity. 
     *         In terms of the Motion Magic® Expo profile, a higher kV results in a
     *         slower maximum velocity.
     *   - kA: Mechanism kA for profiling.  Unlike the kA slot gain, this is always
     *         in units of V/rps².
     *         
     *         This represents the amount of voltage necessary to achieve an
     *         acceleration.  In terms of the Motion Magic® Expo profile, a higher
     *         kA results in a slower acceleration.
     *   - Velocity: Cruise velocity for profiling.  The signage does not matter as
     *               the device will use the absolute value for profile generation. 
     *               Setting this to 0 will allow the profile to run to the max
     *               possible velocity based on Expo_kV.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DynamicMotionMagicExpoVoltage const &request) final;
    
    /**
     * \brief Differential control with duty cycle average target and
     * position difference target.
     * 
     * - Diff_DutyCycleOut_Position Parameters: 
     *   - AverageRequest: Average DutyCycleOut request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_DutyCycleOut_Position const &request) final;
    
    /**
     * \brief Differential control with position average target and
     * position difference target using duty cycle control.
     * 
     * - Diff_PositionDutyCycle_Position Parameters: 
     *   - AverageRequest: Average PositionDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionDutyCycle_Position const &request) final;
    
    /**
     * \brief Differential control with velocity average target and
     * position difference target using duty cycle control.
     * 
     * - Diff_VelocityDutyCycle_Position Parameters: 
     *   - AverageRequest: Average VelocityDutyCYcle request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityDutyCycle_Position const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * position difference target using duty cycle control.
     * 
     * - Diff_MotionMagicDutyCycle_Position Parameters: 
     *   - AverageRequest: Average MotionMagicDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicDutyCycle_Position const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and position difference target using duty cycle control.
     * 
     * - Diff_MotionMagicExpoDutyCycle_Position Parameters: 
     *   - AverageRequest: Average MotionMagicExpoDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoDutyCycle_Position const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and position difference target using duty cycle control.
     * 
     * - Diff_MotionMagicVelocityDutyCycle_Position Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityDutyCycle_Position const &request) final;
    
    /**
     * \brief Differential control with duty cycle average target and
     * velocity difference target.
     * 
     * - Diff_DutyCycleOut_Velocity Parameters: 
     *   - AverageRequest: Average DutyCycleOut request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_DutyCycleOut_Velocity const &request) final;
    
    /**
     * \brief Differential control with position average target and
     * velocity difference target using duty cycle control.
     * 
     * - Diff_PositionDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average PositionDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionDutyCycle_Velocity const &request) final;
    
    /**
     * \brief Differential control with velocity average target and
     * velocity difference target using duty cycle control.
     * 
     * - Diff_VelocityDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average VelocityDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityDutyCycle_Velocity const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * velocity difference target using duty cycle control.
     * 
     * - Diff_MotionMagicDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicDutyCycle_Velocity const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and velocity difference target using duty cycle control.
     * 
     * - Diff_MotionMagicExpoDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicExpoDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoDutyCycle_Velocity const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and velocity difference target using duty cycle control.
     * 
     * - Diff_MotionMagicVelocityDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityDutyCycle_Velocity const &request) final;
    
    /**
     * \brief Differential control with duty cycle average target and duty
     * cycle difference target.
     * 
     * - Diff_DutyCycleOut_Open Parameters: 
     *   - AverageRequest: Average DutyCycleOut request of the mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_DutyCycleOut_Open const &request) final;
    
    /**
     * \brief Differential control with position average target and duty
     * cycle difference target.
     * 
     * - Diff_PositionDutyCycle_Open Parameters: 
     *   - AverageRequest: Average PositionDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionDutyCycle_Open const &request) final;
    
    /**
     * \brief Differential control with velocity average target and duty
     * cycle difference target.
     * 
     * - Diff_VelocityDutyCycle_Open Parameters: 
     *   - AverageRequest: Average VelocityDutyCYcle request of the mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityDutyCycle_Open const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * duty cycle difference target.
     * 
     * - Diff_MotionMagicDutyCycle_Open Parameters: 
     *   - AverageRequest: Average MotionMagicDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicDutyCycle_Open const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and duty cycle difference target.
     * 
     * - Diff_MotionMagicExpoDutyCycle_Open Parameters: 
     *   - AverageRequest: Average MotionMagicExpoDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoDutyCycle_Open const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and duty cycle difference target.
     * 
     * - Diff_MotionMagicVelocityDutyCycle_Open Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityDutyCycle_Open const &request) final;
    
    /**
     * \brief Differential control with voltage average target and
     * position difference target.
     * 
     * - Diff_VoltageOut_Position Parameters: 
     *   - AverageRequest: Average VoltageOut request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VoltageOut_Position const &request) final;
    
    /**
     * \brief Differential control with position average target and
     * position difference target using voltage control.
     * 
     * - Diff_PositionVoltage_Position Parameters: 
     *   - AverageRequest: Average PositionVoltage request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionVoltage_Position const &request) final;
    
    /**
     * \brief Differential control with velocity average target and
     * position difference target using voltage control.
     * 
     * - Diff_VelocityVoltage_Position Parameters: 
     *   - AverageRequest: Average VelocityVoltage request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityVoltage_Position const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * position difference target using voltage control.
     * 
     * - Diff_MotionMagicVoltage_Position Parameters: 
     *   - AverageRequest: Average MotionMagicVoltage request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVoltage_Position const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and position difference target using voltage control.
     * 
     * - Diff_MotionMagicExpoVoltage_Position Parameters: 
     *   - AverageRequest: Average MotionMagicExpoVoltage request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoVoltage_Position const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and position difference target using voltage control.
     * 
     * - Diff_MotionMagicVelocityVoltage_Position Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityVoltage request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityVoltage_Position const &request) final;
    
    /**
     * \brief Differential control with voltage average target and
     * velocity difference target.
     * 
     * - Diff_VoltageOut_Velocity Parameters: 
     *   - AverageRequest: Average VoltageOut request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VoltageOut_Velocity const &request) final;
    
    /**
     * \brief Differential control with position average target and
     * velocity difference target using voltage control.
     * 
     * - Diff_PositionVoltage_Velocity Parameters: 
     *   - AverageRequest: Average PositionVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionVoltage_Velocity const &request) final;
    
    /**
     * \brief Differential control with velocity average target and
     * velocity difference target using voltage control.
     * 
     * - Diff_VelocityVoltage_Velocity Parameters: 
     *   - AverageRequest: Average VelocityVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityVoltage_Velocity const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * velocity difference target using voltage control.
     * 
     * - Diff_MotionMagicVoltage_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVoltage_Velocity const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and velocity difference target using voltage control.
     * 
     * - Diff_MotionMagicExpoVoltage_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicExpoVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoVoltage_Velocity const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and velocity difference target using voltage control.
     * 
     * - Diff_MotionMagicVelocityVoltage_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityVoltage request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityVoltage_Velocity const &request) final;
    
    /**
     * \brief Differential control with voltage average target and voltage
     * difference target.
     * 
     * - Diff_VoltageOut_Open Parameters: 
     *   - AverageRequest: Average VoltageOut request of the mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VoltageOut_Open const &request) final;
    
    /**
     * \brief Differential control with position average target and
     * voltage difference target.
     * 
     * - Diff_PositionVoltage_Open Parameters: 
     *   - AverageRequest: Average PositionVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionVoltage_Open const &request) final;
    
    /**
     * \brief Differential control with velocity average target and
     * voltage difference target.
     * 
     * - Diff_VelocityVoltage_Open Parameters: 
     *   - AverageRequest: Average VelocityVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityVoltage_Open const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * voltage difference target.
     * 
     * - Diff_MotionMagicVoltage_Open Parameters: 
     *   - AverageRequest: Average MotionMagicVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVoltage_Open const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and voltage difference target.
     * 
     * - Diff_MotionMagicExpoVoltage_Open Parameters: 
     *   - AverageRequest: Average MotionMagicExpoVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoVoltage_Open const &request) final;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and voltage difference target.
     * 
     * - Diff_MotionMagicVelocityVoltage_Open Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityVoltage request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityVoltage_Open const &request) final;

    /**
     * \brief Apply a generic empty control used to do nothing.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::EmptyControl const &request) final;

    /**
     * \brief Control device with generic control request object. User must make
     *        sure the specified object is castable to a valid control request,
     *        otherwise this function will fail at run-time and return the NotSupported
     *        StatusCode
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::ControlRequest const &request) final;

    
    /**
     * \brief Sets the mechanism position of the device in mechanism
     * rotations.
     * 
     * \param newValue Value to set to. Units are in rotations.
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetPosition(units::angle::turn_t newValue, units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().SetPosition(newValue, timeoutSeconds);
    }
    /**
     * \brief Sets the mechanism position of the device in mechanism
     * rotations.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \param newValue Value to set to. Units are in rotations.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetPosition(units::angle::turn_t newValue) final
    {
        return SetPosition(newValue, 0.100_s);
    }
    
    /**
     * \brief Clear the sticky faults in the device.
     * 
     * \details This typically has no impact on the device functionality. 
     * Instead, it just clears telemetry faults that are accessible via
     * API and Tuner Self-Test.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFaults(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFaults(timeoutSeconds);
    }
    /**
     * \brief Clear the sticky faults in the device.
     * 
     * \details This typically has no impact on the device functionality. 
     * Instead, it just clears telemetry faults that are accessible via
     * API and Tuner Self-Test.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFaults() final
    {
        return ClearStickyFaults(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Hardware fault occurred
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Hardware(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_Hardware(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Hardware fault occurred
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Hardware() final
    {
        return ClearStickyFault_Hardware(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Processor temperature exceeded limit
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ProcTemp(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_ProcTemp(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Processor temperature exceeded limit
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ProcTemp() final
    {
        return ClearStickyFault_ProcTemp(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Device temperature exceeded limit
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DeviceTemp(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_DeviceTemp(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device temperature exceeded limit
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DeviceTemp() final
    {
        return ClearStickyFault_DeviceTemp(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Device supply voltage dropped to near
     * brownout levels
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Undervoltage(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_Undervoltage(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device supply voltage dropped to near
     * brownout levels
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Undervoltage() final
    {
        return ClearStickyFault_Undervoltage(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Device boot while detecting the enable
     * signal
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootDuringEnable(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_BootDuringEnable(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device boot while detecting the enable
     * signal
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootDuringEnable() final
    {
        return ClearStickyFault_BootDuringEnable(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: An unlicensed feature is in use, device
     * may not behave as expected.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnlicensedFeatureInUse(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_UnlicensedFeatureInUse(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: An unlicensed feature is in use, device
     * may not behave as expected.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnlicensedFeatureInUse() final
    {
        return ClearStickyFault_UnlicensedFeatureInUse(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to
     * supply voltage dropping too low.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BridgeBrownout(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_BridgeBrownout(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to
     * supply voltage dropping too low.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BridgeBrownout() final
    {
        return ClearStickyFault_BridgeBrownout(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: The remote sensor has reset.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorReset(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_RemoteSensorReset(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote sensor has reset.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorReset() final
    {
        return ClearStickyFault_RemoteSensorReset(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: The remote Talon used for differential
     * control is not present on CAN Bus.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingDifferentialFX(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_MissingDifferentialFX(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote Talon used for differential
     * control is not present on CAN Bus.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingDifferentialFX() final
    {
        return ClearStickyFault_MissingDifferentialFX(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: The remote sensor position has
     * overflowed. Because of the nature of remote sensors, it is possible
     * for the remote sensor position to overflow beyond what is supported
     * by the status signal frame. However, this is rare and cannot occur
     * over the course of an FRC match under normal use.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorPosOverflow(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_RemoteSensorPosOverflow(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote sensor position has
     * overflowed. Because of the nature of remote sensors, it is possible
     * for the remote sensor position to overflow beyond what is supported
     * by the status signal frame. However, this is rare and cannot occur
     * over the course of an FRC match under normal use.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorPosOverflow() final
    {
        return ClearStickyFault_RemoteSensorPosOverflow(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Supply Voltage has exceeded the maximum
     * voltage rating of device.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_OverSupplyV(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_OverSupplyV(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Supply Voltage has exceeded the maximum
     * voltage rating of device.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_OverSupplyV() final
    {
        return ClearStickyFault_OverSupplyV(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Supply Voltage is unstable.  Ensure you
     * are using a battery and current limited power supply.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnstableSupplyV(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_UnstableSupplyV(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Supply Voltage is unstable.  Ensure you
     * are using a battery and current limited power supply.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnstableSupplyV() final
    {
        return ClearStickyFault_UnstableSupplyV(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Reverse limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ReverseHardLimit(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_ReverseHardLimit(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Reverse limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ReverseHardLimit() final
    {
        return ClearStickyFault_ReverseHardLimit(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Forward limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ForwardHardLimit(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_ForwardHardLimit(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Forward limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ForwardHardLimit() final
    {
        return ClearStickyFault_ForwardHardLimit(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Reverse soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ReverseSoftLimit(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_ReverseSoftLimit(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Reverse soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ReverseSoftLimit() final
    {
        return ClearStickyFault_ReverseSoftLimit(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Forward soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ForwardSoftLimit(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_ForwardSoftLimit(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Forward soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ForwardSoftLimit() final
    {
        return ClearStickyFault_ForwardSoftLimit(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: The remote soft limit device is not
     * present on CAN Bus.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingSoftLimitRemote(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_MissingSoftLimitRemote(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote soft limit device is not
     * present on CAN Bus.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingSoftLimitRemote() final
    {
        return ClearStickyFault_MissingSoftLimitRemote(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: The remote limit switch device is not
     * present on CAN Bus.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingHardLimitRemote(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_MissingHardLimitRemote(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote limit switch device is not
     * present on CAN Bus.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MissingHardLimitRemote() final
    {
        return ClearStickyFault_MissingHardLimitRemote(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: The remote sensor's data is no longer
     * trusted. This can happen if the remote sensor disappears from the
     * CAN bus or if the remote sensor indicates its data is no longer
     * valid, such as when a CANcoder's magnet strength falls into the
     * "red" range.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorDataInvalid(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_RemoteSensorDataInvalid(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote sensor's data is no longer
     * trusted. This can happen if the remote sensor disappears from the
     * CAN bus or if the remote sensor indicates its data is no longer
     * valid, such as when a CANcoder's magnet strength falls into the
     * "red" range.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorDataInvalid() final
    {
        return ClearStickyFault_RemoteSensorDataInvalid(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: The remote sensor used for fusion has
     * fallen out of sync to the local sensor. A re-synchronization has
     * occurred, which may cause a discontinuity. This typically happens
     * if there is significant slop in the mechanism, or if the
     * RotorToSensorRatio configuration parameter is incorrect.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_FusedSensorOutOfSync(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_FusedSensorOutOfSync(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The remote sensor used for fusion has
     * fallen out of sync to the local sensor. A re-synchronization has
     * occurred, which may cause a discontinuity. This typically happens
     * if there is significant slop in the mechanism, or if the
     * RotorToSensorRatio configuration parameter is incorrect.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_FusedSensorOutOfSync() final
    {
        return ClearStickyFault_FusedSensorOutOfSync(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Stator current limit occured.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_StatorCurrLimit(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_StatorCurrLimit(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Stator current limit occured.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_StatorCurrLimit() final
    {
        return ClearStickyFault_StatorCurrLimit(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Supply current limit occured.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SupplyCurrLimit(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_SupplyCurrLimit(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Supply current limit occured.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SupplyCurrLimit() final
    {
        return ClearStickyFault_SupplyCurrLimit(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Using Fused CANcoder feature while
     * unlicensed. Device has fallen back to remote CANcoder.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UsingFusedCANcoderWhileUnlicensed(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_UsingFusedCANcoderWhileUnlicensed(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Using Fused CANcoder feature while
     * unlicensed. Device has fallen back to remote CANcoder.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UsingFusedCANcoderWhileUnlicensed() final
    {
        return ClearStickyFault_UsingFusedCANcoderWhileUnlicensed(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Static brake was momentarily disabled
     * due to excessive braking current while disabled.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_StaticBrakeDisabled(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_StaticBrakeDisabled(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Static brake was momentarily disabled
     * due to excessive braking current while disabled.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_StaticBrakeDisabled() final
    {
        return ClearStickyFault_StaticBrakeDisabled(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to a
     * short in the motor leads.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BridgeShort(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_BridgeShort(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to a
     * short in the motor leads.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BridgeShort() final
    {
        return ClearStickyFault_BridgeShort(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid.  Check
     * hall sensor and cabling.  This fault can be used to detect when
     * hall cable is unplugged.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_HallSensorMissing(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_HallSensorMissing(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid.  Check
     * hall sensor and cabling.  This fault can be used to detect when
     * hall cable is unplugged.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_HallSensorMissing() final
    {
        return ClearStickyFault_HallSensorMissing(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid during
     * motor drive, so motor was disabled.  Check hall sensor and cabling.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DriveDisabledHallSensor(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_DriveDisabledHallSensor(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid during
     * motor drive, so motor was disabled.  Check hall sensor and cabling.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DriveDisabledHallSensor() final
    {
        return ClearStickyFault_DriveDisabledHallSensor(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Motor temperature signal appears to not
     * be connected.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorMissing(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_MotorTempSensorMissing(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motor temperature signal appears to not
     * be connected.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorMissing() final
    {
        return ClearStickyFault_MotorTempSensorMissing(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Motor temperature signal indicates motor
     * is too hot.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorTooHot(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_MotorTempSensorTooHot(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motor temperature signal indicates motor
     * is too hot.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorTooHot() final
    {
        return ClearStickyFault_MotorTempSensorTooHot(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Motor arrangement has not been set in
     * configuration.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorArrangementNotSelected(units::time::second_t timeoutSeconds) final
    {
        return GetConfigurator().ClearStickyFault_MotorArrangementNotSelected(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motor arrangement has not been set in
     * configuration.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_MotorArrangementNotSelected() final
    {
        return ClearStickyFault_MotorArrangementNotSelected(0.100_s);
    }
};

#if defined(_WIN32) || defined(_WIN64)
#pragma warning(pop)
#endif

}
}

}
}

