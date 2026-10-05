/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/swerve/SwerveModuleConstants.hpp"
#include "ctre/phoenix6/swerve/impl/SwerveDriveKinematics.hpp"
#include "ctre/phoenix6/CANBus.hpp"
#include "units/force.h"
#include "units/torque.h"
#include <array>

namespace ctre {
namespace phoenix6 {
namespace swerve {
namespace impl {

/**
 * \brief All possible control requests for the module steer motor.
 */
enum class SteerRequestType {
    /**
     * \brief Control the drive motor using a Motion Magic® Expo request.
     * The control output type is determined by SwerveModuleConstants#SteerMotorClosedLoopOutput.
     */
    MotionMagicExpo = 0,
    /**
     * \brief Control the drive motor using an unprofiled position request.
     * The control output type is determined by SwerveModuleConstants#SteerMotorClosedLoopOutput.
     */
    Position = 1,
};

/**
 * \brief All possible control requests for the module drive motor.
 */
enum class DriveRequestType {
    /**
     * \brief Control the drive motor using an open-loop voltage request.
     */
    OpenLoopVoltage = 0,
    /**
     * \brief Control the drive motor using a velocity closed-loop request.
     * The control output type is determined by SwerveModuleConstants#DriveMotorClosedLoopOutput.
     */
    Velocity = 1,
};

/**
 * \brief Swerve Module class that encapsulates a swerve module powered by
 * CTR Electronics devices.
 *
 * This class handles the hardware devices but does not configure them for
 * swerve module operation using the Phoenix 6 API. Users should create a
 * high-level SwerveModule instead of using this directly.
 */
class SwerveModuleImpl {
public:
    /**
     * \brief Contains everything the swerve module needs to apply a request.
     */
    struct ModuleRequest {
        /**
         * \brief Unoptimized speed and direction the module should target.
         */
        SwerveModuleState State{};

        /**
         * \brief Robot-centric wheel force feedforward to apply in the
         * X direction. X is defined as forward according to WPILib
         * convention, so this determines the forward force to apply.
         *
         * This force should include friction applied to the ground.
         */
        units::newton_t WheelForceFeedforwardX = 0_N;
        /**
         * \brief Robot-centric wheel force feedforward to apply in the
         * Y direction. Y is defined as to the left according to WPILib
         * convention, so this determines the force to apply to the left.
         *
         * This force should include friction applied to the ground.
         */
        units::newton_t WheelForceFeedforwardY = 0_N;

        /**
         * \brief The type of control request to use for the drive motor.
         */
        DriveRequestType DriveRequest = DriveRequestType::OpenLoopVoltage;
        /**
         * \brief The type of control request to use for the steer motor.
         */
        SteerRequestType SteerRequest = SteerRequestType::Position;

        /**
         * \brief The update period of the module request. Setting this to
         * a non-zero value adds a velocity feedforward to the steer motor.
         */
        units::second_t UpdatePeriod = 0_s;

        /**
         * \brief When using Voltage-based control, set to true (default) to use FOC
         * commutation (requires Phoenix Pro), which increases peak power by ~15%. Set to
         * false to use trapezoidal commutation. This is ignored when using Torque-based
         * control, which always uses FOC.
         *
         * FOC improves motor performance by leveraging torque (current) control. 
         * However, this may be inconvenient for applications that require specifying
         * duty cycle or voltage.  CTR-Electronics has developed a hybrid method that
         * combines the performances gains of FOC while still allowing applications to
         * provide duty cycle or voltage demand.  This not to be confused with simple
         * sinusoidal control or phase voltage control which lacks the performance
         * gains.
         */
        bool EnableFOC = true;

        /**
         * \brief Modifies the State parameter and returns itself.
         *
         * Unoptimized speed and direction the module should target.
         *
         * \param newState Parameter to modify
         * \returns Itself
         */
        ModuleRequest &WithState(SwerveModuleState newState)
        {
            this->State = std::move(newState);
            return *this;
        }

        /**
         * \brief Modifies the WheelForceFeedforwardX parameter and returns itself.
         *
         * Robot-centric wheel force feedforward to apply in the
         * X direction. X is defined as forward according to WPILib
         * convention, so this determines the forward force to apply.
         *
         * This force should include friction.
         *
         * \param newWheelForceFeedforwardX Parameter to modify
         * \returns Itself
         */
        ModuleRequest &WithWheelForceFeedforwardX(units::newton_t newWheelForceFeedforwardX)
        {
            this->WheelForceFeedforwardX = newWheelForceFeedforwardX;
            return *this;
        }
        /**
         * \brief Modifies the WheelForceFeedforwardY parameter and returns itself.
         *
         * Robot-centric wheel force feedforward to apply in the
         * Y direction. Y is defined as to the left according to WPILib
         * convention, so this determines the force to apply to the left.
         *
         * This force should include friction.
         *
         * \param newWheelForceFeedforwardY Parameter to modify
         * \returns Itself
         */
        ModuleRequest &WithWheelForceFeedforwardY(units::newton_t newWheelForceFeedforwardY)
        {
            this->WheelForceFeedforwardY = newWheelForceFeedforwardY;
            return *this;
        }

        /**
         * \brief Modifies the DriveRequest parameter and returns itself.
         *
         * The type of control request to use for the drive motor.
         *
         * \param newDriveRequest Parameter to modify
         * \returns Itself
         */
        ModuleRequest &WithDriveRequest(DriveRequestType newDriveRequest)
        {
            this->DriveRequest = newDriveRequest;
            return *this;
        }
        /**
         * \brief Modifies the SteerRequest parameter and returns itself.
         *
         * The type of control request to use for the steer motor.
         *
         * \param newSteerRequest Parameter to modify
         * \returns Itself
         */
        ModuleRequest &WithSteerRequest(SteerRequestType newSteerRequest)
        {
            this->SteerRequest = newSteerRequest;
            return *this;
        }

        /**
         * \brief Modifies the UpdatePeriod parameter and returns itself.
         *
         * The update period of the module request. Setting this to a
         * non-zero value adds a velocity feedforward to the steer motor.
         *
         * \param newUpdatePeriod Parameter to modify
         * \returns Itself
         */
        ModuleRequest &WithUpdatePeriod(units::second_t newUpdatePeriod)
        {
            this->UpdatePeriod = newUpdatePeriod;
            return *this;
        }

        /**
         * \brief Modifies the EnableFOC parameter and returns itself.
         *
         * When using Voltage-based control, set to true (default) to use FOC commutation
         * (requires Phoenix Pro), which increases peak power by ~15%. Set to false to
         * use trapezoidal commutation. This is ignored when using Torque-based control,
         * which always uses FOC.
         *
         * FOC improves motor performance by leveraging torque (current) control. 
         * However, this may be inconvenient for applications that require specifying
         * duty cycle or voltage.  CTR-Electronics has developed a hybrid method that
         * combines the performances gains of FOC while still allowing applications to
         * provide duty cycle or voltage demand.  This not to be confused with simple
         * sinusoidal control or phase voltage control which lacks the performance
         * gains.
         *
         * \param newEnableFOC Parameter to modify
         * \returns Itself
         */
        ModuleRequest &WithEnableFOC(bool newEnableFOC)
        {
            this->EnableFOC = newEnableFOC;
            return *this;
        }
    };

private:
    std::unique_ptr<hardware::traits::CommonTalon> _driveMotor;
    std::unique_ptr<hardware::traits::CommonTalon> _steerMotor;
    hardware::traits::CommonTalonWithFOC *_driveMotorFOC{};
    hardware::traits::CommonTalonWithFOC *_steerMotorFOC{};

    StatusSignal<units::turn_t> _drivePosition;
    StatusSignal<units::turns_per_second_t> _driveVelocity;
    StatusSignal<units::turn_t> _steerPosition;
    StatusSignal<units::turns_per_second_t> _steerVelocity;

    mutable StatusSignal<ctre::unit::newton_meters_per_ampere_t> _driveMotorKT;
    mutable StatusSignal<units::ampere_t> _driveMotorStallCurrent;

    struct ModuleSupplem;
    mutable std::unique_ptr<ModuleSupplem> _moduleSupplem;

    ClosedLoopOutputType kDriveClosedLoopOutput;
    ClosedLoopOutputType kSteerClosedLoopOutput;

    using turns_per_meter = units::compound_unit<units::turns, units::inverse<units::meters>>;
    using turns_per_meter_t = units::unit_t<turns_per_meter>;

    turns_per_meter_t kDriveRotationsPerMeter;
    units::meter_t kDriveNmPerWheelN;
    units::scalar_t kCouplingRatioDriveRotorToEncoder;
    units::meters_per_second_t kSpeedAt12Volts;

    bool kIsOnCANFD;

    SwerveModulePosition _currentPosition;
    SwerveModuleState _targetState;

public:
    /**
     * \brief Construct a SwerveModuleImpl with the specified constants.
     *
     * \param constants Constants used to construct the module
     * \param canbus    The CAN bus this module is on
     */
    template <typename DriveMotorConfigsT, typename SteerMotorConfigsT, typename EncoderConfigsT>
    SwerveModuleImpl(
        SwerveModuleConstants<DriveMotorConfigsT, SteerMotorConfigsT, EncoderConfigsT> const &constants,
        CANBus canbus
    );

    ~SwerveModuleImpl();

    /**
     * \brief Applies the desired ModuleRequest to this module.
     *
     * \param moduleRequest The request to apply to this module
     */
    void Apply(ModuleRequest const &moduleRequest);

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
        if (_driveMotorFOC) {
            _driveMotorFOC->SetControl(driveRequest.WithUpdateFreqHz(0_Hz));
        } else {
            _driveMotor->SetControl(driveRequest.WithUpdateFreqHz(0_Hz));
        }

        if (_steerMotorFOC) {
            _steerMotorFOC->SetControl(steerRequest.WithUpdateFreqHz(0_Hz));
        } else {
            _steerMotor->SetControl(steerRequest.WithUpdateFreqHz(0_Hz));
        }
    }

    /**
     * \brief Configures the neutral mode to use for the module's drive motor.
     *
     * \param neutralMode The drive motor neutral mode
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status code response of the request
     */
    ctre::phoenix::StatusCode ConfigNeutralMode(signals::NeutralModeValue neutralMode, units::second_t timeoutSeconds = 0.100_s);

    /**
     * \brief Gets the state of this module and passes it back as a
     * SwerveModulePosition object with latency compensated values.
     *
     * This function is blocking when it performs a refresh.
     *
     * \param refresh True if the signals should be refreshed
     * \returns SwerveModulePosition containing this module's state.
     */
    SwerveModulePosition GetPosition(bool refresh);

    /**
     * \brief Gets the last cached swerve module position.
     * This differs from #GetPosition in that it will not
     * perform any latency compensation or refresh the signals.
     *
     * \returns Last cached SwerveModulePosition
     */
    SwerveModulePosition GetCachedPosition() const { return _currentPosition; }

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
        return SwerveModuleState{_driveVelocity.GetValue() / kDriveRotationsPerMeter, {_steerPosition.GetValue()}};
    }

    /**
     * \brief Get the target state of the module.
     *
     * This is typically used for telemetry.
     *
     * \returns Target state of the module
     */
    SwerveModuleState GetTargetState() const { return _targetState; }

    /**
     * \brief Resets this module's drive motor position to 0 rotations.
     */
    void ResetPosition()
    {
        /* Only touch drive pos, not steer */
        _driveMotor->SetPosition(0_tr);
    }

    /**
     * \brief Gets the closed-loop output type to use for the drive motor.
     *
     * \returns Drive motor closed-loop output type
     */
    ClosedLoopOutputType GetDriveClosedLoopOutputType() const
    {
        return kDriveClosedLoopOutput;
    }

    /**
     * \brief Gets the closed-loop output type to use for the steer motor.
     *
     * \returns Steer motor closed-loop output type
     */
    ClosedLoopOutputType GetSteerClosedLoopOutputType() const
    {
        return kSteerClosedLoopOutput;
    }

private:
    /**
     * \brief Collection of all possible torque feedforward outputs that
     * can be applied to the motor for a given wheel force feedforward.
     */
    struct MotorTorqueFeedforwards {
        units::newton_meter_t torque;
        units::ampere_t torqueCurrent;
        units::volt_t voltage;
    };

    units::turns_per_second_t ApplyVelocityCorrections(units::turns_per_second_t velocity, units::turn_t targetAngle) const;
    MotorTorqueFeedforwards CalculateMotorTorqueFeedforwards(
        units::newton_t wheelForceFeedforwardX,
        units::newton_t wheelForceFeedforwardY
    ) const;

    friend class SwerveDrivetrainImpl;

    std::array<BaseStatusSignal *, 4> GetSignals()
    {
        return std::array<BaseStatusSignal *, 4>{&_drivePosition, &_driveVelocity, &_steerPosition, &_steerVelocity};
    }
};

}
}
}
}
