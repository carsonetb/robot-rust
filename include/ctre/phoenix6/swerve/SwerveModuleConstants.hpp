/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/core/CoreCANcoder.hpp"
#include "ctre/phoenix6/core/CoreCANdi.hpp"
#include "ctre/phoenix6/core/CoreTalonFX.hpp"
#include "ctre/phoenix6/core/CoreTalonFXS.hpp"

#include <units/length.h>
#include <units/moment_of_inertia.h>
#include <units/velocity.h>

namespace ctre {
namespace phoenix6 {
namespace swerve {

/**
 * \brief Supported closed-loop output types.
 */
enum class ClosedLoopOutputType {
    Voltage = 0,
    /** \brief Requires Pro */
    TorqueCurrentFOC = 1,
};

/**
 * \brief Supported motor arrangements for the drive motors.
 */
enum class DriveMotorArrangement {
    /**
     * \brief Talon FX integrated brushless motor.
     */
    TalonFX_Integrated = 0,
    /**
     * \brief Third party NEO brushless motor connected to a Talon FXS over JST.
     */
    TalonFXS_NEO_JST = 1,
    /**
     * \brief Third party VORTEX brushless motor connected to a Talon FXS over JST.
     */
    TalonFXS_VORTEX_JST = 2,
};

/**
 * \brief Supported motor arrangements for the steer motors.
 */
enum class SteerMotorArrangement {
    /**
     * \brief Talon FX integrated brushless motor.
     */
    TalonFX_Integrated = 0,
    /**
     * \brief CTR Electronics Minion® brushless motor connected to a Talon FXS over JST.
     */
    TalonFXS_Minion_JST = 1,
    /**
     * \brief Third party NEO brushless motor connected to a Talon FXS over JST.
     */
    TalonFXS_NEO_JST = 2,
    /**
     * \brief Third party VORTEX brushless motor connected to a Talon FXS over JST.
     */
    TalonFXS_VORTEX_JST = 3,
    /**
     * \brief Third party NEO550 brushless motor connected to a Talon FXS over JST.
     */
    TalonFXS_NEO550_JST = 4,
    /**
     * \brief Brushed motor connected to a Talon FXS on terminals A and B.
     */
    TalonFXS_Brushed_AB = 5,
    /**
     * \brief Brushed motor connected to a Talon FXS on terminals A and C.
     */
    TalonFXS_Brushed_AC = 6,
    /**
     * \brief Brushed motor connected to a Talon FXS on terminals B and C.
     */
    TalonFXS_Brushed_BC = 7,
};

/**
 * \brief Supported feedback sensors for the steer motors.
 */
enum class SteerFeedbackType {
    /**
     * \brief Requires Pro; Use signals#FeedbackSensorSourceValue#FusedCANcoder
     * for the steer motor.
     */
    FusedCANcoder = 0,
    /**
     * \brief Requires Pro; Use signals#FeedbackSensorSourceValue#SyncCANcoder
     * for the steer motor.
     */
    SyncCANcoder = 1,
    /**
     * \brief Use signals#FeedbackSensorSourceValue#RemoteCANcoder
     * for the steer motor.
     */
    RemoteCANcoder = 2,
    /**
     * \brief Requires Pro; Use signals#FeedbackSensorSourceValue#FusedCANdiPWM1
     * for the steer motor.
     */
    FusedCANdiPWM1 = 3,
    /**
     * \brief Requires Pro; Use signals#FeedbackSensorSourceValue#FusedCANdiPWM2
     * for the steer motor.
     */
    FusedCANdiPWM2 = 4,
    /**
     * \brief Requires Pro; Use signals#FeedbackSensorSourceValue#SyncCANdiPWM1
     * for the steer motor.
     */
    SyncCANdiPWM1 = 5,
    /**
     * \brief Requires Pro; Use signals#FeedbackSensorSourceValue#SyncCANdiPWM2
     * for the steer motor.
     */
    SyncCANdiPWM2 = 6,
    /**
     * \brief Use signals#FeedbackSensorSourceValue#RemoteCANdiPWM1
     * for the steer motor.
     */
    RemoteCANdiPWM1 = 7,
    /**
     * \brief Use signals#FeedbackSensorSourceValue#RemoteCANdiPWM2
     * for the steer motor.
     */
    RemoteCANdiPWM2 = 8,
    /**
     * \brief Use signals#ExternalFeedbackSensorSourceValue#PulseWidth
     * for the steer motor. This requires Talon FXS.
     */
    TalonFXS_PulseWidth = 9,
};

/**
 * \brief All constants for a swerve module.
 */
template <
    typename DriveMotorConfigsT,
    typename SteerMotorConfigsT,
    typename EncoderConfigsT,
    typename = std::enable_if_t<std::is_base_of_v<configs::ParentConfiguration, DriveMotorConfigsT>>,
    typename = std::enable_if_t<std::is_base_of_v<configs::ParentConfiguration, SteerMotorConfigsT>>,
    typename = std::enable_if_t<std::is_base_of_v<configs::ParentConfiguration, EncoderConfigsT>>
>
struct SwerveModuleConstants {
    constexpr SwerveModuleConstants() = default;

    /**
     * \brief CAN ID of the steer motor.
     */
    int SteerMotorId = 0;
    /**
     * \brief CAN ID of the drive motor.
     */
    int DriveMotorId = 0;
    /**
     * \brief CAN ID of the absolute encoder used for azimuth.
     */
    int EncoderId = 0;
    /**
     * \brief Offset of the azimuth encoder.
     */
    units::angle::turn_t EncoderOffset = 0_tr;
    /**
     * \brief The location of this module's wheels relative to the physical center
     * of the robot in meters along the X axis of the robot.
     */
    units::length::meter_t LocationX = 0_m;
    /**
     * \brief The location of this module's wheels relative to the physical center
     * of the robot in meters along the Y axis of the robot.
     */
    units::length::meter_t LocationY = 0_m;
    /**
     * \brief True if the drive motor is inverted.
     */
    bool DriveMotorInverted = false;
    /**
     * \brief True if the steer motor is inverted from the azimuth. The azimuth
     * should rotate counter-clockwise (as seen from the top of the robot) for a
     * positive motor output.
     */
    bool SteerMotorInverted = false;
    /**
     * \brief True if the azimuth encoder is inverted from the azimuth. The encoder
     * should report a positive velocity when the azimuth rotates counter-clockwise
     * (as seen from the top of the robot).
     */
    bool EncoderInverted = false;
    /**
     * \brief Gear ratio between the drive motor and the wheel.
     */
    units::dimensionless::scalar_t DriveMotorGearRatio = 0;
    /**
     * \brief Gear ratio between the steer motor and the azimuth encoder. For
     * example, the SDS Mk4 has a steering ratio of 12.8.
     */
    units::dimensionless::scalar_t SteerMotorGearRatio = 0;
    /**
     * \brief Coupled gear ratio between the azimuth encoder and the drive motor.
     * 
     * For a typical swerve module, the azimuth turn motor also drives the wheel a
     * nontrivial amount, which affects the accuracy of odometry and control. This
     * ratio represents the number of rotations of the drive motor caused by a
     * rotation of the azimuth.
     */
    units::dimensionless::scalar_t CouplingGearRatio = 0;
    /**
     * \brief Radius of the driving wheel in meters.
     */
    units::length::meter_t WheelRadius = 0_m;
    /**
     * \brief The steer motor closed-loop gains.
     * 
     * The steer motor uses the control ouput type specified by
     * SteerMotorClosedLoopOutput and any SwerveModule#SteerRequestType. These gains
     * operate on azimuth rotations (after the gear ratio).
     */
    configs::Slot0Configs SteerMotorGains = configs::Slot0Configs{};
    /**
     * \brief The drive motor closed-loop gains.
     * 
     * When using closed-loop control, the drive motor uses the control output type
     * specified by DriveMotorClosedLoopOutput and any closed-loop
     * SwerveModule#DriveRequestType. These gains operate on motor rotor rotations
     * (before the gear ratio).
     */
    configs::Slot0Configs DriveMotorGains = configs::Slot0Configs{};
    /**
     * \brief The closed-loop output type to use for the steer motors.
     */
    ClosedLoopOutputType SteerMotorClosedLoopOutput = ClosedLoopOutputType::Voltage;
    /**
     * \brief The closed-loop output type to use for the drive motors.
     */
    ClosedLoopOutputType DriveMotorClosedLoopOutput = ClosedLoopOutputType::Voltage;
    /**
     * \brief The maximum amount of stator current the drive motors can apply
     * without slippage.
     */
    units::current::ampere_t SlipCurrent = 120_A;
    /**
     * \brief When using open-loop drive control, this specifies the speed at which
     * the robot travels when driven with 12 volts. This is used to approximate the
     * output for a desired velocity. If using closed loop control, this value is
     * ignored.
     */
    units::velocity::meters_per_second_t SpeedAt12Volts = 0_mps;
    /**
     * \brief Choose the motor used for the drive motor.
     * 
     * If using a Talon FX, this should be set to TalonFX_Integrated. If using a
     * Talon FXS, this should be set to the motor attached to the Talon FXS.
     */
    DriveMotorArrangement DriveMotorType = DriveMotorArrangement::TalonFX_Integrated;
    /**
     * \brief Choose the motor used for the steer motor.
     * 
     * If using a Talon FX, this should be set to TalonFX_Integrated. If using a
     * Talon FXS, this should be set to the motor attached to the Talon FXS.
     */
    SteerMotorArrangement SteerMotorType = SteerMotorArrangement::TalonFX_Integrated;
    /**
     * \brief Choose how the feedback sensors should be configured.
     * 
     * If the robot does not support Pro, then this should be set to RemoteCANcoder.
     * Otherwise, users have the option to use either FusedCANcoder or SyncCANcoder
     * depending on if there is a risk that the CANcoder can fail in a way to
     * provide "good" data.
     * 
     * If this is set to FusedCANcoder or SyncCANcoder when the steer motor is not
     * Pro-licensed, the device will automatically fall back to RemoteCANcoder and
     * report a UsingProFeatureOnUnlicensedDevice status code.
     */
    SteerFeedbackType FeedbackSource = SteerFeedbackType::FusedCANcoder;
    /**
     * \brief The initial configs used to configure the drive motor of the swerve
     * module. The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#MotorOutputConfigs#NeutralMode (Brake mode, overwritten with
     *   SwerveDrivetrain#ConfigNeutralMode)
     * - configs#MotorOutputConfigs#Inverted
     *   (SwerveModuleConstants#DriveMotorInverted)
     * - configs#Slot0Configs (SwerveModuleConstants#DriveMotorGains)
     * - configs#CurrentLimitsConfigs#StatorCurrentLimit /
     *   configs#TorqueCurrentConfigs#PeakForwardTorqueCurrent /
     *   configs#TorqueCurrentConfigs#PeakReverseTorqueCurrent
     *   (SwerveModuleConstants#SlipCurrent)
     * - configs#CurrentLimitsConfigs#StatorCurrentLimitEnable (Enabled)
     * 
     */
    DriveMotorConfigsT DriveMotorInitialConfigs = {};
    /**
     * \brief The initial configs used to configure the steer motor of the swerve
     * module. The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#MotorOutputConfigs#NeutralMode (Brake mode)
     * - configs#MotorOutputConfigs#Inverted
     *   (SwerveModuleConstants#SteerMotorInverted)
     * - configs#Slot0Configs (SwerveModuleConstants#SteerMotorGains)
     * - configs#FeedbackConfigs#FeedbackRemoteSensorID
     *   (SwerveModuleConstants#EncoderId)
     * - configs#FeedbackConfigs#FeedbackSensorSource
     *   (SwerveModuleConstants#FeedbackSource)
     * - configs#FeedbackConfigs#RotorToSensorRatio
     *   (SwerveModuleConstants#SteerMotorGearRatio)
     * - configs#MotionMagicConfigs#MotionMagicExpo_kV /
     *   configs#MotionMagicConfigs#MotionMagicExpo_kA (Calculated from gear ratios)
     * - configs#ClosedLoopGeneralConfigs#ContinuousWrap (true)
     * 
     */
    SteerMotorConfigsT SteerMotorInitialConfigs = {};
    /**
     * \brief The initial configs used to configure the azimuth encoder of the
     * swerve module. The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * For CANcoder, the list of configs that will be overwritten is as follows:
     * 
     * - configs#MagnetSensorConfigs#MagnetOffset
     *   (SwerveModuleConstants#EncoderOffset)
     * - configs#MagnetSensorConfigs#SensorDirection
     *   (SwerveModuleConstants#EncoderInverted)
     * 
     */
    EncoderConfigsT EncoderInitialConfigs = {};
    /**
     * \brief Simulated azimuthal inertia.
     */
    units::moment_of_inertia::kilogram_square_meter_t SteerInertia = 0.00001_kg_sq_m;
    /**
     * \brief Simulated drive inertia.
     */
    units::moment_of_inertia::kilogram_square_meter_t DriveInertia = 0.001_kg_sq_m;
    /**
     * \brief Simulated steer voltage required to overcome friction.
     */
    units::voltage::volt_t SteerFrictionVoltage = 0.25_V;
    /**
     * \brief Simulated drive voltage required to overcome friction.
     */
    units::voltage::volt_t DriveFrictionVoltage = 0.25_V;
    
    /**
     * \brief Modifies the SteerMotorId parameter and returns itself.
     *
     * CAN ID of the steer motor.
     *
     * \param newSteerMotorId Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorId(int newSteerMotorId)
    {
        this->SteerMotorId = newSteerMotorId;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveMotorId parameter and returns itself.
     *
     * CAN ID of the drive motor.
     *
     * \param newDriveMotorId Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorId(int newDriveMotorId)
    {
        this->DriveMotorId = newDriveMotorId;
        return *this;
    }
    
    /**
     * \brief Modifies the EncoderId parameter and returns itself.
     *
     * CAN ID of the absolute encoder used for azimuth.
     *
     * \param newEncoderId Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithEncoderId(int newEncoderId)
    {
        this->EncoderId = newEncoderId;
        return *this;
    }
    
    /**
     * \brief Modifies the EncoderOffset parameter and returns itself.
     *
     * Offset of the azimuth encoder.
     *
     * \param newEncoderOffset Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithEncoderOffset(units::angle::turn_t newEncoderOffset)
    {
        this->EncoderOffset = newEncoderOffset;
        return *this;
    }
    
    /**
     * \brief Modifies the LocationX parameter and returns itself.
     *
     * The location of this module's wheels relative to the physical center of the
     * robot in meters along the X axis of the robot.
     *
     * \param newLocationX Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithLocationX(units::length::meter_t newLocationX)
    {
        this->LocationX = newLocationX;
        return *this;
    }
    
    /**
     * \brief Modifies the LocationY parameter and returns itself.
     *
     * The location of this module's wheels relative to the physical center of the
     * robot in meters along the Y axis of the robot.
     *
     * \param newLocationY Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithLocationY(units::length::meter_t newLocationY)
    {
        this->LocationY = newLocationY;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveMotorInverted parameter and returns itself.
     *
     * True if the drive motor is inverted.
     *
     * \param newDriveMotorInverted Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorInverted(bool newDriveMotorInverted)
    {
        this->DriveMotorInverted = newDriveMotorInverted;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerMotorInverted parameter and returns itself.
     *
     * True if the steer motor is inverted from the azimuth. The azimuth should
     * rotate counter-clockwise (as seen from the top of the robot) for a positive
     * motor output.
     *
     * \param newSteerMotorInverted Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorInverted(bool newSteerMotorInverted)
    {
        this->SteerMotorInverted = newSteerMotorInverted;
        return *this;
    }
    
    /**
     * \brief Modifies the EncoderInverted parameter and returns itself.
     *
     * True if the azimuth encoder is inverted from the azimuth. The encoder should
     * report a positive velocity when the azimuth rotates counter-clockwise (as
     * seen from the top of the robot).
     *
     * \param newEncoderInverted Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithEncoderInverted(bool newEncoderInverted)
    {
        this->EncoderInverted = newEncoderInverted;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveMotorGearRatio parameter and returns itself.
     *
     * Gear ratio between the drive motor and the wheel.
     *
     * \param newDriveMotorGearRatio Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorGearRatio(units::dimensionless::scalar_t newDriveMotorGearRatio)
    {
        this->DriveMotorGearRatio = newDriveMotorGearRatio;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerMotorGearRatio parameter and returns itself.
     *
     * Gear ratio between the steer motor and the azimuth encoder. For example, the
     * SDS Mk4 has a steering ratio of 12.8.
     *
     * \param newSteerMotorGearRatio Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorGearRatio(units::dimensionless::scalar_t newSteerMotorGearRatio)
    {
        this->SteerMotorGearRatio = newSteerMotorGearRatio;
        return *this;
    }
    
    /**
     * \brief Modifies the CouplingGearRatio parameter and returns itself.
     *
     * Coupled gear ratio between the azimuth encoder and the drive motor.
     * 
     * For a typical swerve module, the azimuth turn motor also drives the wheel a
     * nontrivial amount, which affects the accuracy of odometry and control. This
     * ratio represents the number of rotations of the drive motor caused by a
     * rotation of the azimuth.
     *
     * \param newCouplingGearRatio Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithCouplingGearRatio(units::dimensionless::scalar_t newCouplingGearRatio)
    {
        this->CouplingGearRatio = newCouplingGearRatio;
        return *this;
    }
    
    /**
     * \brief Modifies the WheelRadius parameter and returns itself.
     *
     * Radius of the driving wheel in meters.
     *
     * \param newWheelRadius Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithWheelRadius(units::length::meter_t newWheelRadius)
    {
        this->WheelRadius = newWheelRadius;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerMotorGains parameter and returns itself.
     *
     * The steer motor closed-loop gains.
     * 
     * The steer motor uses the control ouput type specified by
     * SteerMotorClosedLoopOutput and any SwerveModule#SteerRequestType. These gains
     * operate on azimuth rotations (after the gear ratio).
     *
     * \param newSteerMotorGains Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorGains(const configs::Slot0Configs& newSteerMotorGains)
    {
        this->SteerMotorGains = newSteerMotorGains;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveMotorGains parameter and returns itself.
     *
     * The drive motor closed-loop gains.
     * 
     * When using closed-loop control, the drive motor uses the control output type
     * specified by DriveMotorClosedLoopOutput and any closed-loop
     * SwerveModule#DriveRequestType. These gains operate on motor rotor rotations
     * (before the gear ratio).
     *
     * \param newDriveMotorGains Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorGains(const configs::Slot0Configs& newDriveMotorGains)
    {
        this->DriveMotorGains = newDriveMotorGains;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerMotorClosedLoopOutput parameter and returns itself.
     *
     * The closed-loop output type to use for the steer motors.
     *
     * \param newSteerMotorClosedLoopOutput Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorClosedLoopOutput(ClosedLoopOutputType newSteerMotorClosedLoopOutput)
    {
        this->SteerMotorClosedLoopOutput = newSteerMotorClosedLoopOutput;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveMotorClosedLoopOutput parameter and returns itself.
     *
     * The closed-loop output type to use for the drive motors.
     *
     * \param newDriveMotorClosedLoopOutput Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorClosedLoopOutput(ClosedLoopOutputType newDriveMotorClosedLoopOutput)
    {
        this->DriveMotorClosedLoopOutput = newDriveMotorClosedLoopOutput;
        return *this;
    }
    
    /**
     * \brief Modifies the SlipCurrent parameter and returns itself.
     *
     * The maximum amount of stator current the drive motors can apply without
     * slippage.
     *
     * \param newSlipCurrent Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSlipCurrent(units::current::ampere_t newSlipCurrent)
    {
        this->SlipCurrent = newSlipCurrent;
        return *this;
    }
    
    /**
     * \brief Modifies the SpeedAt12Volts parameter and returns itself.
     *
     * When using open-loop drive control, this specifies the speed at which the
     * robot travels when driven with 12 volts. This is used to approximate the
     * output for a desired velocity. If using closed loop control, this value is
     * ignored.
     *
     * \param newSpeedAt12Volts Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSpeedAt12Volts(units::velocity::meters_per_second_t newSpeedAt12Volts)
    {
        this->SpeedAt12Volts = newSpeedAt12Volts;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveMotorType parameter and returns itself.
     *
     * Choose the motor used for the drive motor.
     * 
     * If using a Talon FX, this should be set to TalonFX_Integrated. If using a
     * Talon FXS, this should be set to the motor attached to the Talon FXS.
     *
     * \param newDriveMotorType Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorType(DriveMotorArrangement newDriveMotorType)
    {
        this->DriveMotorType = newDriveMotorType;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerMotorType parameter and returns itself.
     *
     * Choose the motor used for the steer motor.
     * 
     * If using a Talon FX, this should be set to TalonFX_Integrated. If using a
     * Talon FXS, this should be set to the motor attached to the Talon FXS.
     *
     * \param newSteerMotorType Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorType(SteerMotorArrangement newSteerMotorType)
    {
        this->SteerMotorType = newSteerMotorType;
        return *this;
    }
    
    /**
     * \brief Modifies the FeedbackSource parameter and returns itself.
     *
     * Choose how the feedback sensors should be configured.
     * 
     * If the robot does not support Pro, then this should be set to RemoteCANcoder.
     * Otherwise, users have the option to use either FusedCANcoder or SyncCANcoder
     * depending on if there is a risk that the CANcoder can fail in a way to
     * provide "good" data.
     * 
     * If this is set to FusedCANcoder or SyncCANcoder when the steer motor is not
     * Pro-licensed, the device will automatically fall back to RemoteCANcoder and
     * report a UsingProFeatureOnUnlicensedDevice status code.
     *
     * \param newFeedbackSource Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithFeedbackSource(SteerFeedbackType newFeedbackSource)
    {
        this->FeedbackSource = newFeedbackSource;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveMotorInitialConfigs parameter and returns itself.
     *
     * The initial configs used to configure the drive motor of the swerve module.
     * The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#MotorOutputConfigs#NeutralMode (Brake mode, overwritten with
     *   SwerveDrivetrain#ConfigNeutralMode)
     * - configs#MotorOutputConfigs#Inverted
     *   (SwerveModuleConstants#DriveMotorInverted)
     * - configs#Slot0Configs (SwerveModuleConstants#DriveMotorGains)
     * - configs#CurrentLimitsConfigs#StatorCurrentLimit /
     *   configs#TorqueCurrentConfigs#PeakForwardTorqueCurrent /
     *   configs#TorqueCurrentConfigs#PeakReverseTorqueCurrent
     *   (SwerveModuleConstants#SlipCurrent)
     * - configs#CurrentLimitsConfigs#StatorCurrentLimitEnable (Enabled)
     * 
     *
     * \param newDriveMotorInitialConfigs Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorInitialConfigs(const DriveMotorConfigsT& newDriveMotorInitialConfigs)
    {
        this->DriveMotorInitialConfigs = newDriveMotorInitialConfigs;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerMotorInitialConfigs parameter and returns itself.
     *
     * The initial configs used to configure the steer motor of the swerve module.
     * The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#MotorOutputConfigs#NeutralMode (Brake mode)
     * - configs#MotorOutputConfigs#Inverted
     *   (SwerveModuleConstants#SteerMotorInverted)
     * - configs#Slot0Configs (SwerveModuleConstants#SteerMotorGains)
     * - configs#FeedbackConfigs#FeedbackRemoteSensorID
     *   (SwerveModuleConstants#EncoderId)
     * - configs#FeedbackConfigs#FeedbackSensorSource
     *   (SwerveModuleConstants#FeedbackSource)
     * - configs#FeedbackConfigs#RotorToSensorRatio
     *   (SwerveModuleConstants#SteerMotorGearRatio)
     * - configs#MotionMagicConfigs#MotionMagicExpo_kV /
     *   configs#MotionMagicConfigs#MotionMagicExpo_kA (Calculated from gear ratios)
     * - configs#ClosedLoopGeneralConfigs#ContinuousWrap (true)
     * 
     *
     * \param newSteerMotorInitialConfigs Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorInitialConfigs(const SteerMotorConfigsT& newSteerMotorInitialConfigs)
    {
        this->SteerMotorInitialConfigs = newSteerMotorInitialConfigs;
        return *this;
    }
    
    /**
     * \brief Modifies the EncoderInitialConfigs parameter and returns itself.
     *
     * The initial configs used to configure the azimuth encoder of the swerve
     * module. The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * For CANcoder, the list of configs that will be overwritten is as follows:
     * 
     * - configs#MagnetSensorConfigs#MagnetOffset
     *   (SwerveModuleConstants#EncoderOffset)
     * - configs#MagnetSensorConfigs#SensorDirection
     *   (SwerveModuleConstants#EncoderInverted)
     * 
     *
     * \param newEncoderInitialConfigs Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithEncoderInitialConfigs(const EncoderConfigsT& newEncoderInitialConfigs)
    {
        this->EncoderInitialConfigs = newEncoderInitialConfigs;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerInertia parameter and returns itself.
     *
     * Simulated azimuthal inertia.
     *
     * \param newSteerInertia Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerInertia(units::moment_of_inertia::kilogram_square_meter_t newSteerInertia)
    {
        this->SteerInertia = newSteerInertia;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveInertia parameter and returns itself.
     *
     * Simulated drive inertia.
     *
     * \param newDriveInertia Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveInertia(units::moment_of_inertia::kilogram_square_meter_t newDriveInertia)
    {
        this->DriveInertia = newDriveInertia;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerFrictionVoltage parameter and returns itself.
     *
     * Simulated steer voltage required to overcome friction.
     *
     * \param newSteerFrictionVoltage Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerFrictionVoltage(units::voltage::volt_t newSteerFrictionVoltage)
    {
        this->SteerFrictionVoltage = newSteerFrictionVoltage;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveFrictionVoltage parameter and returns itself.
     *
     * Simulated drive voltage required to overcome friction.
     *
     * \param newDriveFrictionVoltage Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveFrictionVoltage(units::voltage::volt_t newDriveFrictionVoltage)
    {
        this->DriveFrictionVoltage = newDriveFrictionVoltage;
        return *this;
    }
    
};

/**
 * \brief Constants that are common across the swerve modules, used
 * for creating instances of module-specific SwerveModuleConstants.
 */
template <
    typename DriveMotorConfigsT,
    typename SteerMotorConfigsT,
    typename EncoderConfigsT,
    typename = std::enable_if_t<std::is_base_of_v<configs::ParentConfiguration, DriveMotorConfigsT>>,
    typename = std::enable_if_t<std::is_base_of_v<configs::ParentConfiguration, SteerMotorConfigsT>>,
    typename = std::enable_if_t<std::is_base_of_v<configs::ParentConfiguration, EncoderConfigsT>>
>
struct SwerveModuleConstantsFactory {
    constexpr SwerveModuleConstantsFactory() = default;

    /**
     * \brief Gear ratio between the drive motor and the wheel.
     */
    units::dimensionless::scalar_t DriveMotorGearRatio = 0;
    /**
     * \brief Gear ratio between the steer motor and the azimuth encoder. For
     * example, the SDS Mk4 has a steering ratio of 12.8.
     */
    units::dimensionless::scalar_t SteerMotorGearRatio = 0;
    /**
     * \brief Coupled gear ratio between the azimuth encoder and the drive motor.
     * 
     * For a typical swerve module, the azimuth turn motor also drives the wheel a
     * nontrivial amount, which affects the accuracy of odometry and control. This
     * ratio represents the number of rotations of the drive motor caused by a
     * rotation of the azimuth.
     */
    units::dimensionless::scalar_t CouplingGearRatio = 0;
    /**
     * \brief Radius of the driving wheel in meters.
     */
    units::length::meter_t WheelRadius = 0_m;
    /**
     * \brief The steer motor closed-loop gains.
     * 
     * The steer motor uses the control ouput type specified by
     * SteerMotorClosedLoopOutput and any SwerveModule#SteerRequestType. These gains
     * operate on azimuth rotations (after the gear ratio).
     */
    configs::Slot0Configs SteerMotorGains = configs::Slot0Configs{};
    /**
     * \brief The drive motor closed-loop gains.
     * 
     * When using closed-loop control, the drive motor uses the control output type
     * specified by DriveMotorClosedLoopOutput and any closed-loop
     * SwerveModule#DriveRequestType. These gains operate on motor rotor rotations
     * (before the gear ratio).
     */
    configs::Slot0Configs DriveMotorGains = configs::Slot0Configs{};
    /**
     * \brief The closed-loop output type to use for the steer motors.
     */
    ClosedLoopOutputType SteerMotorClosedLoopOutput = ClosedLoopOutputType::Voltage;
    /**
     * \brief The closed-loop output type to use for the drive motors.
     */
    ClosedLoopOutputType DriveMotorClosedLoopOutput = ClosedLoopOutputType::Voltage;
    /**
     * \brief The maximum amount of stator current the drive motors can apply
     * without slippage.
     */
    units::current::ampere_t SlipCurrent = 120_A;
    /**
     * \brief When using open-loop drive control, this specifies the speed at which
     * the robot travels when driven with 12 volts. This is used to approximate the
     * output for a desired velocity. If using closed loop control, this value is
     * ignored.
     */
    units::velocity::meters_per_second_t SpeedAt12Volts = 0_mps;
    /**
     * \brief Choose the motor used for the drive motor.
     * 
     * If using a Talon FX, this should be set to TalonFX_Integrated. If using a
     * Talon FXS, this should be set to the motor attached to the Talon FXS.
     */
    DriveMotorArrangement DriveMotorType = DriveMotorArrangement::TalonFX_Integrated;
    /**
     * \brief Choose the motor used for the steer motor.
     * 
     * If using a Talon FX, this should be set to TalonFX_Integrated. If using a
     * Talon FXS, this should be set to the motor attached to the Talon FXS.
     */
    SteerMotorArrangement SteerMotorType = SteerMotorArrangement::TalonFX_Integrated;
    /**
     * \brief Choose how the feedback sensors should be configured.
     * 
     * If the robot does not support Pro, then this should be set to RemoteCANcoder.
     * Otherwise, users have the option to use either FusedCANcoder or SyncCANcoder
     * depending on if there is a risk that the CANcoder can fail in a way to
     * provide "good" data.
     * 
     * If this is set to FusedCANcoder or SyncCANcoder when the steer motor is not
     * Pro-licensed, the device will automatically fall back to RemoteCANcoder and
     * report a UsingProFeatureOnUnlicensedDevice status code.
     */
    SteerFeedbackType FeedbackSource = SteerFeedbackType::FusedCANcoder;
    /**
     * \brief The initial configs used to configure the drive motor of the swerve
     * module. The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#MotorOutputConfigs#NeutralMode (Brake mode, overwritten with
     *   SwerveDrivetrain#ConfigNeutralMode)
     * - configs#MotorOutputConfigs#Inverted
     *   (SwerveModuleConstants#DriveMotorInverted)
     * - configs#Slot0Configs (SwerveModuleConstants#DriveMotorGains)
     * - configs#CurrentLimitsConfigs#StatorCurrentLimit /
     *   configs#TorqueCurrentConfigs#PeakForwardTorqueCurrent /
     *   configs#TorqueCurrentConfigs#PeakReverseTorqueCurrent
     *   (SwerveModuleConstants#SlipCurrent)
     * - configs#CurrentLimitsConfigs#StatorCurrentLimitEnable (Enabled)
     * 
     */
    DriveMotorConfigsT DriveMotorInitialConfigs = {};
    /**
     * \brief The initial configs used to configure the steer motor of the swerve
     * module. The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#MotorOutputConfigs#NeutralMode (Brake mode)
     * - configs#MotorOutputConfigs#Inverted
     *   (SwerveModuleConstants#SteerMotorInverted)
     * - configs#Slot0Configs (SwerveModuleConstants#SteerMotorGains)
     * - configs#FeedbackConfigs#FeedbackRemoteSensorID
     *   (SwerveModuleConstants#EncoderId)
     * - configs#FeedbackConfigs#FeedbackSensorSource
     *   (SwerveModuleConstants#FeedbackSource)
     * - configs#FeedbackConfigs#RotorToSensorRatio
     *   (SwerveModuleConstants#SteerMotorGearRatio)
     * - configs#MotionMagicConfigs#MotionMagicExpo_kV /
     *   configs#MotionMagicConfigs#MotionMagicExpo_kA (Calculated from gear ratios)
     * - configs#ClosedLoopGeneralConfigs#ContinuousWrap (true)
     * 
     */
    SteerMotorConfigsT SteerMotorInitialConfigs = {};
    /**
     * \brief The initial configs used to configure the azimuth encoder of the
     * swerve module. The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * For CANcoder, the list of configs that will be overwritten is as follows:
     * 
     * - configs#MagnetSensorConfigs#MagnetOffset
     *   (SwerveModuleConstants#EncoderOffset)
     * - configs#MagnetSensorConfigs#SensorDirection
     *   (SwerveModuleConstants#EncoderInverted)
     * 
     */
    EncoderConfigsT EncoderInitialConfigs = {};
    /**
     * \brief Simulated azimuthal inertia.
     */
    units::moment_of_inertia::kilogram_square_meter_t SteerInertia = 0.00001_kg_sq_m;
    /**
     * \brief Simulated drive inertia.
     */
    units::moment_of_inertia::kilogram_square_meter_t DriveInertia = 0.001_kg_sq_m;
    /**
     * \brief Simulated steer voltage required to overcome friction.
     */
    units::voltage::volt_t SteerFrictionVoltage = 0.25_V;
    /**
     * \brief Simulated drive voltage required to overcome friction.
     */
    units::voltage::volt_t DriveFrictionVoltage = 0.25_V;
    
    /**
     * \brief Modifies the DriveMotorGearRatio parameter and returns itself.
     *
     * Gear ratio between the drive motor and the wheel.
     *
     * \param newDriveMotorGearRatio Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorGearRatio(units::dimensionless::scalar_t newDriveMotorGearRatio)
    {
        this->DriveMotorGearRatio = newDriveMotorGearRatio;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerMotorGearRatio parameter and returns itself.
     *
     * Gear ratio between the steer motor and the azimuth encoder. For example, the
     * SDS Mk4 has a steering ratio of 12.8.
     *
     * \param newSteerMotorGearRatio Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorGearRatio(units::dimensionless::scalar_t newSteerMotorGearRatio)
    {
        this->SteerMotorGearRatio = newSteerMotorGearRatio;
        return *this;
    }
    
    /**
     * \brief Modifies the CouplingGearRatio parameter and returns itself.
     *
     * Coupled gear ratio between the azimuth encoder and the drive motor.
     * 
     * For a typical swerve module, the azimuth turn motor also drives the wheel a
     * nontrivial amount, which affects the accuracy of odometry and control. This
     * ratio represents the number of rotations of the drive motor caused by a
     * rotation of the azimuth.
     *
     * \param newCouplingGearRatio Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithCouplingGearRatio(units::dimensionless::scalar_t newCouplingGearRatio)
    {
        this->CouplingGearRatio = newCouplingGearRatio;
        return *this;
    }
    
    /**
     * \brief Modifies the WheelRadius parameter and returns itself.
     *
     * Radius of the driving wheel in meters.
     *
     * \param newWheelRadius Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithWheelRadius(units::length::meter_t newWheelRadius)
    {
        this->WheelRadius = newWheelRadius;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerMotorGains parameter and returns itself.
     *
     * The steer motor closed-loop gains.
     * 
     * The steer motor uses the control ouput type specified by
     * SteerMotorClosedLoopOutput and any SwerveModule#SteerRequestType. These gains
     * operate on azimuth rotations (after the gear ratio).
     *
     * \param newSteerMotorGains Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorGains(configs::Slot0Configs newSteerMotorGains)
    {
        this->SteerMotorGains = newSteerMotorGains;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveMotorGains parameter and returns itself.
     *
     * The drive motor closed-loop gains.
     * 
     * When using closed-loop control, the drive motor uses the control output type
     * specified by DriveMotorClosedLoopOutput and any closed-loop
     * SwerveModule#DriveRequestType. These gains operate on motor rotor rotations
     * (before the gear ratio).
     *
     * \param newDriveMotorGains Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorGains(configs::Slot0Configs newDriveMotorGains)
    {
        this->DriveMotorGains = newDriveMotorGains;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerMotorClosedLoopOutput parameter and returns itself.
     *
     * The closed-loop output type to use for the steer motors.
     *
     * \param newSteerMotorClosedLoopOutput Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorClosedLoopOutput(ClosedLoopOutputType newSteerMotorClosedLoopOutput)
    {
        this->SteerMotorClosedLoopOutput = newSteerMotorClosedLoopOutput;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveMotorClosedLoopOutput parameter and returns itself.
     *
     * The closed-loop output type to use for the drive motors.
     *
     * \param newDriveMotorClosedLoopOutput Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorClosedLoopOutput(ClosedLoopOutputType newDriveMotorClosedLoopOutput)
    {
        this->DriveMotorClosedLoopOutput = newDriveMotorClosedLoopOutput;
        return *this;
    }
    
    /**
     * \brief Modifies the SlipCurrent parameter and returns itself.
     *
     * The maximum amount of stator current the drive motors can apply without
     * slippage.
     *
     * \param newSlipCurrent Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSlipCurrent(units::current::ampere_t newSlipCurrent)
    {
        this->SlipCurrent = newSlipCurrent;
        return *this;
    }
    
    /**
     * \brief Modifies the SpeedAt12Volts parameter and returns itself.
     *
     * When using open-loop drive control, this specifies the speed at which the
     * robot travels when driven with 12 volts. This is used to approximate the
     * output for a desired velocity. If using closed loop control, this value is
     * ignored.
     *
     * \param newSpeedAt12Volts Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSpeedAt12Volts(units::velocity::meters_per_second_t newSpeedAt12Volts)
    {
        this->SpeedAt12Volts = newSpeedAt12Volts;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveMotorType parameter and returns itself.
     *
     * Choose the motor used for the drive motor.
     * 
     * If using a Talon FX, this should be set to TalonFX_Integrated. If using a
     * Talon FXS, this should be set to the motor attached to the Talon FXS.
     *
     * \param newDriveMotorType Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorType(DriveMotorArrangement newDriveMotorType)
    {
        this->DriveMotorType = newDriveMotorType;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerMotorType parameter and returns itself.
     *
     * Choose the motor used for the steer motor.
     * 
     * If using a Talon FX, this should be set to TalonFX_Integrated. If using a
     * Talon FXS, this should be set to the motor attached to the Talon FXS.
     *
     * \param newSteerMotorType Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorType(SteerMotorArrangement newSteerMotorType)
    {
        this->SteerMotorType = newSteerMotorType;
        return *this;
    }
    
    /**
     * \brief Modifies the FeedbackSource parameter and returns itself.
     *
     * Choose how the feedback sensors should be configured.
     * 
     * If the robot does not support Pro, then this should be set to RemoteCANcoder.
     * Otherwise, users have the option to use either FusedCANcoder or SyncCANcoder
     * depending on if there is a risk that the CANcoder can fail in a way to
     * provide "good" data.
     * 
     * If this is set to FusedCANcoder or SyncCANcoder when the steer motor is not
     * Pro-licensed, the device will automatically fall back to RemoteCANcoder and
     * report a UsingProFeatureOnUnlicensedDevice status code.
     *
     * \param newFeedbackSource Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithFeedbackSource(SteerFeedbackType newFeedbackSource)
    {
        this->FeedbackSource = newFeedbackSource;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveMotorInitialConfigs parameter and returns itself.
     *
     * The initial configs used to configure the drive motor of the swerve module.
     * The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#MotorOutputConfigs#NeutralMode (Brake mode, overwritten with
     *   SwerveDrivetrain#ConfigNeutralMode)
     * - configs#MotorOutputConfigs#Inverted
     *   (SwerveModuleConstants#DriveMotorInverted)
     * - configs#Slot0Configs (SwerveModuleConstants#DriveMotorGains)
     * - configs#CurrentLimitsConfigs#StatorCurrentLimit /
     *   configs#TorqueCurrentConfigs#PeakForwardTorqueCurrent /
     *   configs#TorqueCurrentConfigs#PeakReverseTorqueCurrent
     *   (SwerveModuleConstants#SlipCurrent)
     * - configs#CurrentLimitsConfigs#StatorCurrentLimitEnable (Enabled)
     * 
     *
     * \param newDriveMotorInitialConfigs Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveMotorInitialConfigs(DriveMotorConfigsT newDriveMotorInitialConfigs)
    {
        this->DriveMotorInitialConfigs = newDriveMotorInitialConfigs;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerMotorInitialConfigs parameter and returns itself.
     *
     * The initial configs used to configure the steer motor of the swerve module.
     * The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#MotorOutputConfigs#NeutralMode (Brake mode)
     * - configs#MotorOutputConfigs#Inverted
     *   (SwerveModuleConstants#SteerMotorInverted)
     * - configs#Slot0Configs (SwerveModuleConstants#SteerMotorGains)
     * - configs#FeedbackConfigs#FeedbackRemoteSensorID
     *   (SwerveModuleConstants#EncoderId)
     * - configs#FeedbackConfigs#FeedbackSensorSource
     *   (SwerveModuleConstants#FeedbackSource)
     * - configs#FeedbackConfigs#RotorToSensorRatio
     *   (SwerveModuleConstants#SteerMotorGearRatio)
     * - configs#MotionMagicConfigs#MotionMagicExpo_kV /
     *   configs#MotionMagicConfigs#MotionMagicExpo_kA (Calculated from gear ratios)
     * - configs#ClosedLoopGeneralConfigs#ContinuousWrap (true)
     * 
     *
     * \param newSteerMotorInitialConfigs Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerMotorInitialConfigs(SteerMotorConfigsT newSteerMotorInitialConfigs)
    {
        this->SteerMotorInitialConfigs = newSteerMotorInitialConfigs;
        return *this;
    }
    
    /**
     * \brief Modifies the EncoderInitialConfigs parameter and returns itself.
     *
     * The initial configs used to configure the azimuth encoder of the swerve
     * module. The default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the SwerveModuleConstants class is available to be changed.
     * 
     * For CANcoder, the list of configs that will be overwritten is as follows:
     * 
     * - configs#MagnetSensorConfigs#MagnetOffset
     *   (SwerveModuleConstants#EncoderOffset)
     * - configs#MagnetSensorConfigs#SensorDirection
     *   (SwerveModuleConstants#EncoderInverted)
     * 
     *
     * \param newEncoderInitialConfigs Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithEncoderInitialConfigs(EncoderConfigsT newEncoderInitialConfigs)
    {
        this->EncoderInitialConfigs = newEncoderInitialConfigs;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerInertia parameter and returns itself.
     *
     * Simulated azimuthal inertia.
     *
     * \param newSteerInertia Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerInertia(units::moment_of_inertia::kilogram_square_meter_t newSteerInertia)
    {
        this->SteerInertia = newSteerInertia;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveInertia parameter and returns itself.
     *
     * Simulated drive inertia.
     *
     * \param newDriveInertia Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveInertia(units::moment_of_inertia::kilogram_square_meter_t newDriveInertia)
    {
        this->DriveInertia = newDriveInertia;
        return *this;
    }
    
    /**
     * \brief Modifies the SteerFrictionVoltage parameter and returns itself.
     *
     * Simulated steer voltage required to overcome friction.
     *
     * \param newSteerFrictionVoltage Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithSteerFrictionVoltage(units::voltage::volt_t newSteerFrictionVoltage)
    {
        this->SteerFrictionVoltage = newSteerFrictionVoltage;
        return *this;
    }
    
    /**
     * \brief Modifies the DriveFrictionVoltage parameter and returns itself.
     *
     * Simulated drive voltage required to overcome friction.
     *
     * \param newDriveFrictionVoltage Parameter to modify
     * \returns this object
     */
    constexpr SwerveModuleConstantsFactory<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> &WithDriveFrictionVoltage(units::voltage::volt_t newDriveFrictionVoltage)
    {
        this->DriveFrictionVoltage = newDriveFrictionVoltage;
        return *this;
    }
    
    /**
     * \brief Creates the constants for a swerve module with the given properties.
     *
     * \param steerMotorId CAN ID of the steer motor.
     * \param driveMotorId CAN ID of the drive motor.
     * \param encoderId CAN ID of the absolute encoder used for azimuth.
     * \param encoderOffset Offset of the azimuth encoder.
     * \param locationX The location of this module's wheels relative to the physical center of the robot in meters along the X axis of the robot.
     * \param locationY The location of this module's wheels relative to the physical center of the robot in meters along the Y axis of the robot.
     * \param driveMotorInverted True if the drive motor is inverted.
     * \param steerMotorInverted True if the steer motor is inverted from the azimuth. The azimuth should rotate counter-clockwise (as seen from the top of the robot) for a positive motor output.
     * \param encoderInverted True if the azimuth encoder is inverted from the azimuth. The encoder should report a positive velocity when the azimuth rotates counter-clockwise (as seen from the top of the robot).
     * \returns Constants for the swerve module
     */
    constexpr SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> CreateModuleConstants(
            int steerMotorId,
            int driveMotorId,
            int encoderId,
            units::angle::turn_t encoderOffset,
            units::length::meter_t locationX,
            units::length::meter_t locationY,
            bool driveMotorInverted,
            bool steerMotorInverted,
            bool encoderInverted) const
    {
        return SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT>{}
            .WithSteerMotorId(steerMotorId)
            .WithDriveMotorId(driveMotorId)
            .WithEncoderId(encoderId)
            .WithEncoderOffset(encoderOffset)
            .WithLocationX(locationX)
            .WithLocationY(locationY)
            .WithDriveMotorInverted(driveMotorInverted)
            .WithSteerMotorInverted(steerMotorInverted)
            .WithEncoderInverted(encoderInverted)
            .WithDriveMotorGearRatio(DriveMotorGearRatio)
            .WithSteerMotorGearRatio(SteerMotorGearRatio)
            .WithCouplingGearRatio(CouplingGearRatio)
            .WithWheelRadius(WheelRadius)
            .WithSteerMotorGains(SteerMotorGains)
            .WithDriveMotorGains(DriveMotorGains)
            .WithSteerMotorClosedLoopOutput(SteerMotorClosedLoopOutput)
            .WithDriveMotorClosedLoopOutput(DriveMotorClosedLoopOutput)
            .WithSlipCurrent(SlipCurrent)
            .WithSpeedAt12Volts(SpeedAt12Volts)
            .WithDriveMotorType(DriveMotorType)
            .WithSteerMotorType(SteerMotorType)
            .WithFeedbackSource(FeedbackSource)
            .WithDriveMotorInitialConfigs(DriveMotorInitialConfigs)
            .WithSteerMotorInitialConfigs(SteerMotorInitialConfigs)
            .WithEncoderInitialConfigs(EncoderInitialConfigs)
            .WithSteerInertia(SteerInertia)
            .WithDriveInertia(DriveInertia)
            .WithSteerFrictionVoltage(SteerFrictionVoltage)
            .WithDriveFrictionVoltage(DriveFrictionVoltage);
    }
};

}
}
}
