/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/swerve/impl/SwerveModuleImpl.hpp"
#include "ctre/phoenix6/CANcoder.hpp"
#include "ctre/phoenix6/CANdi.hpp"
#include "ctre/phoenix6/TalonFX.hpp"
#include "ctre/phoenix6/TalonFXS.hpp"

namespace ctre {
namespace phoenix6 {
namespace swerve {

using impl::SteerRequestType;
using impl::DriveRequestType;

/**
 * \brief Swerve Module class that encapsulates a swerve module powered by
 * CTR Electronics devices.
 *
 * This class handles the hardware devices and configures them for
 * swerve module operation using the Phoenix 6 API.
 *
 * This class constructs hardware devices internally, so the user
 * only specifies the constants (IDs, PID gains, gear ratios, etc).
 * Getters for these hardware devices are available.
 */
template <
    typename DriveMotorT,
    typename SteerMotorT,
    typename EncoderT,
    typename = std::enable_if_t<std::is_base_of_v<hardware::traits::CommonTalon, DriveMotorT>>,
    typename = std::enable_if_t<std::is_base_of_v<hardware::traits::CommonTalon, SteerMotorT>>,
    typename = std::enable_if_t<std::disjunction_v<
        std::is_same<hardware::CANcoder, EncoderT>,
        std::is_same<hardware::CANdi, EncoderT>,
        std::is_same<hardware::TalonFXS, EncoderT>
    >>
>
class SwerveModule {
public:
    /**
     * \brief Contains everything the swerve module needs to apply a request.
     */
    using ModuleRequest = impl::SwerveModuleImpl::ModuleRequest;

protected:
    /** \brief Number of times to attempt config applies. */
    static constexpr int kNumConfigAttempts = 2;

    /** \brief The underlying swerve module instance. */
    impl::SwerveModuleImpl *_module;

private:
    DriveMotorT _driveMotor;
    SteerMotorT _steerMotor;
    EncoderT _encoder;

public:
    /**
     * \brief Construct a SwerveModule with the specified constants.
     *
     * \param constants  Constants used to construct the module
     * \param canbusName The name of the CAN bus this module is on
     * \param module     The impl#SwerveModuleImpl to use
     */
    SwerveModule(
        SwerveModuleConstants<typename DriveMotorT::Configuration, typename SteerMotorT::Configuration, typename EncoderT::Configuration> const &constants,
        std::string_view canbusName,
        impl::SwerveModuleImpl &module
    ) :
        _module{&module},
        _driveMotor{constants.DriveMotorId, std::string{canbusName}},
        _steerMotor{constants.SteerMotorId, std::string{canbusName}},
        _encoder{constants.EncoderId, std::string{canbusName}}
    {
        ctre::phoenix::StatusCode response{};

        typename DriveMotorT::Configuration driveConfigs = constants.DriveMotorInitialConfigs;
        driveConfigs.MotorOutput.NeutralMode = signals::NeutralModeValue::Brake;

        driveConfigs.Slot0 = constants.DriveMotorGains;
        if constexpr (!std::is_same_v<configs::TalonFXSConfiguration, decltype(driveConfigs)>) {
            driveConfigs.TorqueCurrent.PeakForwardTorqueCurrent = constants.SlipCurrent;
            driveConfigs.TorqueCurrent.PeakReverseTorqueCurrent = -constants.SlipCurrent;
        }
        driveConfigs.CurrentLimits.StatorCurrentLimit = constants.SlipCurrent;
        driveConfigs.CurrentLimits.StatorCurrentLimitEnable = true;

        if constexpr (std::is_same_v<configs::TalonFXSConfiguration, decltype(driveConfigs)>) {
            switch (constants.DriveMotorType) {
                case DriveMotorArrangement::TalonFX_Integrated:
                    printf(
                        "Cannot use TalonFX_Integrated drive motor type on Talon FXS ID %d. TalonFX_Integrated is only supported on Talon FX.",
                        GetDriveMotor().GetDeviceID()
                    );
                    break;

                case DriveMotorArrangement::TalonFXS_NEO_JST:
                    driveConfigs.Commutation.MotorArrangement = signals::MotorArrangementValue::NEO_JST;
                    break;
                case DriveMotorArrangement::TalonFXS_VORTEX_JST:
                    driveConfigs.Commutation.MotorArrangement = signals::MotorArrangementValue::VORTEX_JST;
                    break;
            }
        } else {
            if (constants.DriveMotorType != DriveMotorArrangement::TalonFX_Integrated) {
                printf("Drive motor Talon FX ID %d only supports TalonFX_Integrated.", GetDriveMotor().GetDeviceID());
            }
        }

        driveConfigs.MotorOutput.Inverted = constants.DriveMotorInverted ? signals::InvertedValue::Clockwise_Positive
                : signals::InvertedValue::CounterClockwise_Positive;
        for (int i = 0; i < kNumConfigAttempts; ++i) {
            response = GetDriveMotor().GetConfigurator().Apply(driveConfigs);
            if (response.IsOK()) break;
        }
        if (!response.IsOK()) {
            printf("Talon ID %d failed config with error %s\n", GetDriveMotor().GetDeviceID(), response.GetName());
        }

        typename SteerMotorT::Configuration steerConfigs = constants.SteerMotorInitialConfigs;
        steerConfigs.MotorOutput.NeutralMode = signals::NeutralModeValue::Brake;

        steerConfigs.Slot0 = constants.SteerMotorGains;

        if constexpr (std::is_same_v<configs::TalonFXSConfiguration, decltype(steerConfigs)>) {
            switch (constants.SteerMotorType) {
                case SteerMotorArrangement::TalonFX_Integrated:
                    printf(
                        "Cannot use TalonFX_Integrated steer motor type on Talon FXS ID %d. TalonFX_Integrated is only supported on Talon FX.",
                        GetSteerMotor().GetDeviceID()
                    );
                    break;

                case SteerMotorArrangement::TalonFXS_Minion_JST:
                    steerConfigs.Commutation.MotorArrangement = signals::MotorArrangementValue::Minion_JST;
                    break;
                case SteerMotorArrangement::TalonFXS_NEO_JST:
                    steerConfigs.Commutation.MotorArrangement = signals::MotorArrangementValue::NEO_JST;
                    break;
                case SteerMotorArrangement::TalonFXS_VORTEX_JST:
                    steerConfigs.Commutation.MotorArrangement = signals::MotorArrangementValue::VORTEX_JST;
                    break;
                case SteerMotorArrangement::TalonFXS_NEO550_JST:
                    steerConfigs.Commutation.MotorArrangement = signals::MotorArrangementValue::NEO550_JST;
                    break;
                case SteerMotorArrangement::TalonFXS_Brushed_AB:
                    steerConfigs.Commutation.MotorArrangement = signals::MotorArrangementValue::Brushed_DC;
                    steerConfigs.Commutation.BrushedMotorWiring = signals::BrushedMotorWiringValue::Leads_A_and_B;
                    break;
                case SteerMotorArrangement::TalonFXS_Brushed_AC:
                    steerConfigs.Commutation.MotorArrangement = signals::MotorArrangementValue::Brushed_DC;
                    steerConfigs.Commutation.BrushedMotorWiring = signals::BrushedMotorWiringValue::Leads_A_and_C;
                    break;
                case SteerMotorArrangement::TalonFXS_Brushed_BC:
                    steerConfigs.Commutation.MotorArrangement = signals::MotorArrangementValue::Brushed_DC;
                    steerConfigs.Commutation.BrushedMotorWiring = signals::BrushedMotorWiringValue::Leads_B_and_C;
                    break;
            }

            /* Modify configuration to use remote encoder setting */
            steerConfigs.ExternalFeedback.FeedbackRemoteSensorID = constants.EncoderId;
            switch (constants.FeedbackSource) {
                case SteerFeedbackType::FusedCANcoder:
                    steerConfigs.ExternalFeedback.ExternalFeedbackSensorSource = signals::ExternalFeedbackSensorSourceValue::FusedCANcoder;
                    break;
                case SteerFeedbackType::SyncCANcoder:
                    steerConfigs.ExternalFeedback.ExternalFeedbackSensorSource = signals::ExternalFeedbackSensorSourceValue::SyncCANcoder;
                    break;
                case SteerFeedbackType::RemoteCANcoder:
                    steerConfigs.ExternalFeedback.ExternalFeedbackSensorSource = signals::ExternalFeedbackSensorSourceValue::RemoteCANcoder;
                    break;

                case SteerFeedbackType::FusedCANdiPWM1:
                    steerConfigs.ExternalFeedback.ExternalFeedbackSensorSource = signals::ExternalFeedbackSensorSourceValue::FusedCANdiPWM1;
                    break;
                case SteerFeedbackType::FusedCANdiPWM2:
                    steerConfigs.ExternalFeedback.ExternalFeedbackSensorSource = signals::ExternalFeedbackSensorSourceValue::FusedCANdiPWM2;
                    break;
                case SteerFeedbackType::SyncCANdiPWM1:
                    steerConfigs.ExternalFeedback.ExternalFeedbackSensorSource = signals::ExternalFeedbackSensorSourceValue::SyncCANdiPWM1;
                    break;
                case SteerFeedbackType::SyncCANdiPWM2:
                    steerConfigs.ExternalFeedback.ExternalFeedbackSensorSource = signals::ExternalFeedbackSensorSourceValue::SyncCANdiPWM2;
                    break;
                case SteerFeedbackType::RemoteCANdiPWM1:
                    steerConfigs.ExternalFeedback.ExternalFeedbackSensorSource = signals::ExternalFeedbackSensorSourceValue::RemoteCANdiPWM1;
                    break;
                case SteerFeedbackType::RemoteCANdiPWM2:
                    steerConfigs.ExternalFeedback.ExternalFeedbackSensorSource = signals::ExternalFeedbackSensorSourceValue::RemoteCANdiPWM2;
                    break;

                case SteerFeedbackType::TalonFXS_PulseWidth:
                    steerConfigs.ExternalFeedback.ExternalFeedbackSensorSource = signals::ExternalFeedbackSensorSourceValue::PulseWidth;
                    steerConfigs.ExternalFeedback.AbsoluteSensorOffset = constants.EncoderOffset;
                    steerConfigs.ExternalFeedback.SensorPhase = constants.EncoderInverted
                        ? signals::SensorPhaseValue::Opposed
                        : signals::SensorPhaseValue::Aligned;
                    break;
            }
            steerConfigs.ExternalFeedback.RotorToSensorRatio = constants.SteerMotorGearRatio;
        } else {
            if (constants.SteerMotorType != SteerMotorArrangement::TalonFX_Integrated) {
                printf("Steer motor Talon FX ID %d only supports TalonFX_Integrated.", GetSteerMotor().GetDeviceID());
            }

            /* Modify configuration to use remote encoder setting */
            steerConfigs.Feedback.FeedbackRemoteSensorID = constants.EncoderId;
            switch (constants.FeedbackSource) {
                case SteerFeedbackType::FusedCANcoder:
                    steerConfigs.Feedback.FeedbackSensorSource = signals::FeedbackSensorSourceValue::FusedCANcoder;
                    break;
                case SteerFeedbackType::SyncCANcoder:
                    steerConfigs.Feedback.FeedbackSensorSource = signals::FeedbackSensorSourceValue::SyncCANcoder;
                    break;
                case SteerFeedbackType::RemoteCANcoder:
                    steerConfigs.Feedback.FeedbackSensorSource = signals::FeedbackSensorSourceValue::RemoteCANcoder;
                    break;

                case SteerFeedbackType::FusedCANdiPWM1:
                    steerConfigs.Feedback.FeedbackSensorSource = signals::FeedbackSensorSourceValue::FusedCANdiPWM1;
                    break;
                case SteerFeedbackType::FusedCANdiPWM2:
                    steerConfigs.Feedback.FeedbackSensorSource = signals::FeedbackSensorSourceValue::FusedCANdiPWM2;
                    break;
                case SteerFeedbackType::SyncCANdiPWM1:
                    steerConfigs.Feedback.FeedbackSensorSource = signals::FeedbackSensorSourceValue::SyncCANdiPWM1;
                    break;
                case SteerFeedbackType::SyncCANdiPWM2:
                    steerConfigs.Feedback.FeedbackSensorSource = signals::FeedbackSensorSourceValue::SyncCANdiPWM2;
                    break;
                case SteerFeedbackType::RemoteCANdiPWM1:
                    steerConfigs.Feedback.FeedbackSensorSource = signals::FeedbackSensorSourceValue::RemoteCANdiPWM1;
                    break;
                case SteerFeedbackType::RemoteCANdiPWM2:
                    steerConfigs.Feedback.FeedbackSensorSource = signals::FeedbackSensorSourceValue::RemoteCANdiPWM2;
                    break;

                case SteerFeedbackType::TalonFXS_PulseWidth:
                    printf(
                        "Cannot use Pulse Width steer feedback type on Talon FX ID %d. Pulse Width is only supported on Talon FXS.\n",
                        GetSteerMotor().GetDeviceID()
                    );
                    break;
            }
            steerConfigs.Feedback.RotorToSensorRatio = constants.SteerMotorGearRatio;
        }

        steerConfigs.MotionMagic.MotionMagicExpo_kV = 0.12_V / 1_tps * constants.SteerMotorGearRatio;
        steerConfigs.MotionMagic.MotionMagicExpo_kA = 0.8_V / 1_tr_per_s_sq / constants.SteerMotorGearRatio;

        steerConfigs.ClosedLoopGeneral.ContinuousWrap = true; // Enable continuous wrap for swerve modules

        steerConfigs.MotorOutput.Inverted = constants.SteerMotorInverted
                ? signals::InvertedValue::Clockwise_Positive
                : signals::InvertedValue::CounterClockwise_Positive;
        for (int i = 0; i < kNumConfigAttempts; ++i) {
            response = GetSteerMotor().GetConfigurator().Apply(steerConfigs);
            if (response.IsOK()) break;
        }
        if (!response.IsOK()) {
            printf("Talon ID %d failed config with error %s\n", GetSteerMotor().GetDeviceID(), response.GetName());
        }

        typename EncoderT::Configuration encoderConfigs = constants.EncoderInitialConfigs;
        if constexpr (std::is_same_v<configs::CANcoderConfiguration, decltype(encoderConfigs)>) {
            encoderConfigs.MagnetSensor.MagnetOffset = constants.EncoderOffset;
            encoderConfigs.MagnetSensor.SensorDirection = constants.EncoderInverted
                    ? signals::SensorDirectionValue::Clockwise_Positive
                    : signals::SensorDirectionValue::CounterClockwise_Positive;

            for (int i = 0; i < kNumConfigAttempts; ++i) {
                response = GetEncoder().GetConfigurator().Apply(encoderConfigs);
                if (response.IsOK()) break;
            }
            if (!response.IsOK()) {
                printf("Encoder ID %d failed config with error %s\n", GetEncoder().GetDeviceID(), response.GetName());
            }
        } else if constexpr (std::is_same_v<configs::CANdiConfiguration, decltype(encoderConfigs)>) {
            for (int i = 0; i < kNumConfigAttempts; ++i) {
                response = GetEncoder().GetConfigurator().Apply(encoderConfigs.DigitalInputs);
                if (response.IsOK()) break;
            }
            if (!response.IsOK()) {
                printf("Encoder ID %d failed config with error %s\n", GetEncoder().GetDeviceID(), response.GetName());
            }

            for (int i = 0; i < kNumConfigAttempts; ++i) {
                response = GetEncoder().GetConfigurator().Apply(encoderConfigs.CustomParams);
                if (response.IsOK()) break;
            }
            if (!response.IsOK()) {
                printf("Encoder ID %d failed config with error %s\n", GetEncoder().GetDeviceID(), response.GetName());
            }

            switch (constants.FeedbackSource) {
                case SteerFeedbackType::FusedCANdiPWM1:
                case SteerFeedbackType::SyncCANdiPWM1:
                case SteerFeedbackType::RemoteCANdiPWM1:
                    encoderConfigs.PWM1.AbsoluteSensorOffset = constants.EncoderOffset;
                    encoderConfigs.PWM1.SensorDirection = constants.EncoderInverted;

                    for (int i = 0; i < kNumConfigAttempts; ++i) {
                        response = GetEncoder().GetConfigurator().Apply(encoderConfigs.PWM1);
                        if (response.IsOK()) break;
                    }
                    if (!response.IsOK()) {
                        printf("Encoder ID %d failed config with error %s\n", GetEncoder().GetDeviceID(), response.GetName());
                    }
                    break;

                case SteerFeedbackType::FusedCANdiPWM2:
                case SteerFeedbackType::SyncCANdiPWM2:
                case SteerFeedbackType::RemoteCANdiPWM2:
                    encoderConfigs.PWM2.AbsoluteSensorOffset = constants.EncoderOffset;
                    encoderConfigs.PWM2.SensorDirection = constants.EncoderInverted;

                    for (int i = 0; i < kNumConfigAttempts; ++i) {
                        response = GetEncoder().GetConfigurator().Apply(encoderConfigs.PWM2);
                        if (response.IsOK()) break;
                    }
                    if (!response.IsOK()) {
                        printf("Encoder ID %d failed config with error %s\n", GetEncoder().GetDeviceID(), response.GetName());
                    }
                    break;

                default:
                    break;
            }
        }
    }

    virtual ~SwerveModule() = default;

    /**
     * \brief Applies the desired ModuleRequest to this module.
     *
     * \param moduleRequest The request to apply to this module
     */
    virtual void Apply(ModuleRequest const &moduleRequest)
    {
        return _module->Apply(moduleRequest);
    }

    /**
     * \brief Controls this module using the specified drive and steer control requests.
     *
     * This is intended only to be used for characterization of the robot; do not use this for normal use.
     *
     * \param driveRequest The control request to apply to the drive motor
     * \param steerRequest The control request to apply to the steer motor
     */
    template <typename DriveReq, typename SteerReq>
    void Apply(DriveReq &&driveRequest, SteerReq &&steerRequest)
    {
        return _module->Apply(std::forward<DriveReq>(driveRequest), std::forward<SteerReq>(steerRequest));
    }

    /**
     * \brief Gets the state of this module and passes it back as a
     * SwerveModulePosition object with latency compensated values.
     *
     * This function is blocking when it performs a refresh.
     *
     * \param refresh True if the signals should be refreshed
     * \returns SwerveModulePosition containing this module's state.
     */
    SwerveModulePosition GetPosition(bool refresh)
    {
        return _module->GetPosition(refresh);
    }

    /**
     * \brief Gets the last cached swerve module position.
     * This differs from #GetPosition in that it will not
     * perform any latency compensation or refresh the signals.
     *
     * \returns Last cached SwerveModulePosition
     */
    SwerveModulePosition GetCachedPosition() const
    {
        return _module->GetCachedPosition();
    }

    /**
     * \brief Get the current state of the module.
     *
     * This is typically used for telemetry, as the SwerveModulePosition
     * is used for odometry.
     *
     * \returns Current state of the module
     */
    SwerveModuleState GetCurrentState() const
    {
        return _module->GetCurrentState();
    }

    /**
     * \brief Get the target state of the module.
     *
     * This is typically used for telemetry.
     *
     * \returns Target state of the module
     */
    SwerveModuleState GetTargetState() const
    {
        return _module->GetTargetState();
    }

    /**
     * \brief Resets this module's drive motor position to 0 rotations.
     */
    virtual void ResetPosition()
    {
        return _module->ResetPosition();
    }

    /**
     * \brief Gets the closed-loop output type to use for the drive motor.
     *
     * \returns Drive motor closed-loop output type
     */
    ClosedLoopOutputType GetDriveClosedLoopOutputType() const
    {
        return _module->GetDriveClosedLoopOutputType();
    }

    /**
     * \brief Gets the closed-loop output type to use for the steer motor.
     *
     * \returns Steer motor closed-loop output type
     */
    ClosedLoopOutputType GetSteerClosedLoopOutputType() const
    {
        return _module->GetSteerClosedLoopOutputType();
    }

    /**
     * \brief Gets this module's Drive Motor reference.
     *
     * This should be used only to access signals and change configurations that the
     * swerve drivetrain does not configure itself.
     *
     * \returns This module's Drive Motor reference
     */
    DriveMotorT &GetDriveMotor()
    {
        return _driveMotor;
    }

    /**
     * \brief Gets this module's Steer Motor reference.
     *
     * This should be used only to access signals and change configurations that the
     * swerve drivetrain does not configure itself.
     *
     * \returns This module's Steer Motor reference
     */
    SteerMotorT &GetSteerMotor()
    {
        return _steerMotor;
    }

    /**
     * \brief Gets this module's azimuth encoder reference.
     *
     * This should be used only to access signals and change configurations that the
     * swerve drivetrain does not configure itself.
     *
     * \returns This module's azimuth encoder reference
     */
    EncoderT &GetEncoder()
    {
        return _encoder;
    }
};

}
}
}
