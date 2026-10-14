/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/hardware/traits/CommonTalon.hpp"
#include "ctre/phoenix6/mechanisms/DifferentialConstants.hpp"
#include "ctre/phoenix6/mechanisms/MechanismState.hpp"
#include <atomic>
#include <optional>

namespace ctre {
namespace phoenix6 {

namespace hardware {
    class CANcoder;
    class CANdi;
    class Pigeon2;
}

namespace mechanisms {

/**
 * \brief Manages control of a simple two-axis differential mechanism.
 *
 * This mechanism provides limited differential functionality. Pro users
 * on a CAN FD bus can use the \c DifferentialMechanism instead
 * for full functionality.
 *
 * \details A differential mechanism has two axes of motion, where
 * the position along each axis is determined by two motors in
 * separate gearboxes:
 *
 * - Driving both motors in a common direction causes the mechanism
 *   to move forward/reverse, up/down, etc.
 *
 *   - This is the Average axis: position is determined by the
 *     average of the two motors' positions.
 *
 * - Driving the motors in opposing directions causes the mechanism
 *   to twist or rotate left/right.
 *
 *   - This is the Difference axis: rotation is determined by half
 *     the difference of the two motors' positions.
 */
template <std::derived_from<hardware::traits::CommonTalon> MotorT>
class SimpleDifferentialMechanism {
public:
    /**
     * \brief Possible reasons for the mechanism to disable.
     */
    enum class DisabledReasonValue {
        /**
         * \brief No reason given.
         */
        None,
        /**
         * \brief A remote sensor is not present on CAN Bus.
         */
        MissingRemoteSensor,
        /**
         * \brief The remote Talon FX used for differential
         * control is not present on CAN Bus.
         */
        MissingDifferentialFX,
        /**
         * \brief A remote sensor position has overflowed. Because of the
         * nature of remote sensors, it is possible for a remote sensor
         * position to overflow beyond what is supported by the status signal
         * frame. However, this is rare and cannot occur over the course of an
         * FRC match under normal use.
         */
        RemoteSensorPosOverflow,
        /**
         * \brief A device or remote sensor has reset.
         */
        DeviceHasReset,
    };

    /**
     * \brief Possible reasons for the mechanism to require
     * user action to resume control.
     */
    enum class RequiresUserReasonValue {
        /**
         * \brief No reason given.
         */
        None,
        /**
         * \brief A remote sensor position has overflowed. Because of the
         * nature of remote sensors, it is possible for a remote sensor
         * position to overflow beyond what is supported by the status signal
         * frame. However, this is rare and cannot occur over the course of an
         * FRC match under normal use.
         */
        RemoteSensorPosOverflow,
        /**
         * \brief A device or remote sensor has reset.
         */
        DeviceHasReset,
    };

private:
    /** \brief Number of times to attempt config applies. */
    static constexpr int kNumConfigAttempts = 2;

    std::unique_ptr<MotorT> _diffLeaderFX;
    std::unique_ptr<MotorT> _diffFollowerFX;

    units::scalar_t _sensorToDiffRatio;

    std::function<bool()> _diffLeaderFXResetChecker;
    std::function<bool()> _diffFollowerFXResetChecker;
    std::optional<std::function<bool()>> _diffSensorResetChecker{};

    controls::DifferentialFollower _diffFollow;

    controls::NeutralOut _neutral{};
    controls::CoastOut _coast{};
    controls::StaticBrake _brake{};

    std::atomic<bool> _mechanismDisabled{false};
    std::atomic<bool> _requiresUserAction{false};

    DisabledReasonValue _disabledReason{DisabledReasonValue::None};
    RequiresUserReasonValue _requiresUserReason{RequiresUserReasonValue::None};

    void ApplyConfigs(
        DifferentialMotorConstants<typename MotorT::Configuration> const &constants,
        signals::DifferentialSensorSourceValue diffSensorSource,
        std::optional<int> diffSensorID
    );
    ctre::phoenix::StatusCode BeforeControl();

public:
    /**
     * \brief Creates a new simple differential mechanism using two hardware#traits#CommonTalon devices.
     * The mechanism will use the average of the two Talon FX sensors on the primary axis,
     * and half of the difference between the two Talon FX sensors on the differential axis.
     *
     * This mechanism provides limited differential functionality. Pro users on a CAN FD
     * bus can use the \c DifferentialMechanism class instead for full functionality.
     *
     * \param constants Constants used to construct the mechanism
     */
    SimpleDifferentialMechanism(DifferentialMotorConstants<typename MotorT::Configuration> const &constants);

    /**
     * \brief Creates a new simple differential mechanism using two hardware#traits#CommonTalon devices and
     * a hardware#Pigeon2. The mechanism will use the average of the two Talon FX sensors on the primary
     * axis, and the selected Pigeon 2 sensor source on the differential axis.
     *
     * This mechanism provides limited differential functionality. Pro users on a CAN FD
     * bus can use the \c DifferentialMechanism class instead for full functionality.
     *
     * \param constants Constants used to construct the mechanism
     * \param pigeon2 The Pigeon 2 to use for the differential axis
     * \param pigeonSource The sensor source to use for the Pigeon 2 (Yaw, Pitch, or Roll)
     */
    SimpleDifferentialMechanism(DifferentialMotorConstants<typename MotorT::Configuration> const &constants, hardware::Pigeon2 &pigeon2, DifferentialPigeon2Source pigeonSource);

    /**
     * \brief Creates a new simple differential mechanism using two hardware#traits#CommonTalon devices and
     * a hardware#CANcoder. The mechanism will use the average of the two Talon FX sensors on the primary
     * axis, and the CANcoder position/velocity on the differential axis.
     *
     * This mechanism provides limited differential functionality. Pro users on a CAN FD
     * bus can use the \c DifferentialMechanism class instead for full functionality.
     *
     * \param constants Constants used to construct the mechanism
     * \param cancoder The CANcoder to use for the differential axis
     */
    SimpleDifferentialMechanism(DifferentialMotorConstants<typename MotorT::Configuration> const &constants, hardware::CANcoder &cancoder);

    /**
     * \brief Creates a new simple differential mechanism using two hardware#traits#CommonTalon devices and
     * a hardware#CANdi. The mechanism will use the average of the two Talon FX sensors on the primary
     * axis, and the selected CTR Electronics' CANdi™ branded sensor source on the differential axis.
     *
     * This mechanism provides limited differential functionality. Pro users on a CAN FD
     * bus can use the \c DifferentialMechanism class instead for full functionality.
     *
     * \param constants Constants used to construct the mechanism
     * \param candi The CTR Electronics' CANdi™ branded device to use for the differential axis
     * \param candiSource The sensor source to use for the CTR Electronics' CANdi™ branded device
     */
    SimpleDifferentialMechanism(DifferentialMotorConstants<typename MotorT::Configuration> const &constants, hardware::CANdi &candi, DifferentialCANdiSource candiSource);

    /**
     * \brief Configures the neutral mode to use for both motors in the mechanism.
     *
     * \param neutralMode The state of the motor controller bridge when output is neutral or disabled
     * \param timeoutSeconds Maximum amount of time to wait when performing each configuration
     * \returns Status code of the first failed config call, or OK if all succeeded
     */
    ctre::phoenix::StatusCode ConfigNeutralMode(signals::NeutralModeValue neutralMode, units::second_t timeoutSeconds = 100_ms);

    /**
     * \brief Call this method periodically to automatically protect against
     * dangerous fault conditions and keep #GetMechanismState() updated.
     */
    void Periodic();

    /**
     * \brief Get whether the mechanism is currently disabled due to an issue.
     *
     * \returns true if the mechanism is temporarily disabled
     */
    bool IsDisabled() const
    {
        return _mechanismDisabled.load(std::memory_order_acquire);
    }

    /**
     * \brief Get whether the mechanism is currently disabled and requires
     * user action to re-enable mechanism control.
     *
     * \returns true if the mechanism is disabled and the user must manually
     *          perform an action
     */
    bool RequiresUserAction() const
    {
        return _requiresUserAction.load(std::memory_order_acquire);
    }

    /**
     * \brief Gets the state of the mechanism.
     *
     * \returns MechanismState representing the state of the mechanism
     */
    MechanismState GetMechanismState() const
    {
        if (RequiresUserAction()) {
            return MechanismState::RequiresUserAction;
        } else if (IsDisabled()) {
            return MechanismState::Disabled;
        } else {
            return MechanismState::OK;
        }
    }

    /**
     * \brief Indicate to the mechanism that the user has performed the required
     * action to resume mechanism control.
     */
    void ClearUserRequirement();

    /**
     * \returns The reason for the mechanism being disabled
     */
    DisabledReasonValue GetDisabledReason() const
    {
        return _disabledReason;
    }
    /**
     * \returns The reason for the mechanism requiring user
     *          action to resume control
     */
    RequiresUserReasonValue GetRequiresUserReason() const
    {
        return _requiresUserReason;
    }

    /**
     * \brief Average component of the mechanism position.
     *
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     *
     * This refreshes and returns a cached StatusSignal object.
     *
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialAveragePosition Status Signal Object
     */
    StatusSignal<units::turn_t> &GetAveragePosition(bool refresh = true)
    {
        return _diffLeaderFX->GetDifferentialAveragePosition(refresh);
    }

    /**
     * \brief Average component of the mechanism velocity.
     *
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     *
     * This refreshes and returns a cached StatusSignal object.
     *
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialAverageVelocity Status Signal Object
     */
    StatusSignal<units::turns_per_second_t> &GetAverageVelocity(bool refresh = true)
    {
        return _diffLeaderFX->GetDifferentialAverageVelocity(refresh);
    }

    /**
     * \brief Differential component of the mechanism position.
     *
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     *
     * This refreshes and returns a cached StatusSignal object.
     *
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialDifferencePosition Status Signal Object
     */
    StatusSignal<units::turn_t> &GetDifferentialPosition(bool refresh = true)
    {
        return _diffLeaderFX->GetDifferentialDifferencePosition(refresh);
    }

    /**
     * \brief Differential component of the mechanism velocity.
     *
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     *
     * This refreshes and returns a cached StatusSignal object.
     *
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialDifferenceVelocity Status Signal Object
     */
    StatusSignal<units::turns_per_second_t> &GetDifferentialVelocity(bool refresh = true)
    {
        return _diffLeaderFX->GetDifferentialDifferenceVelocity(refresh);
    }
    
    /**
     * \brief Value that the average closed loop is targeting.
     * 
     * \details This is the value that the closed loop PID controller
     * targets.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopReference Status Signal object
     */
    StatusSignal<double> &GetAverageClosedLoopReference(bool refresh = true)
    {
        return _diffLeaderFX->GetClosedLoopReference(refresh);
    }
    
    /**
     * \brief Derivative of the target that the average closed loop is targeting.
     * 
     * \details This is the change in the closed loop reference. This may
     * be used in the feed-forward calculation, the derivative-error, or
     * in application of the signage for kS. Typically, this represents
     * the target velocity during Motion Magic®.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopReferenceSlope Status Signal object
     */
    StatusSignal<double> &GetAverageClosedLoopReferenceSlope(bool refresh = true)
    {
        return _diffLeaderFX->GetClosedLoopReferenceSlope(refresh);
    }
    
    /**
     * \brief The difference between target average reference and current
     * measurement.
     * 
     * \details This is the value that is treated as the error in the PID
     * loop.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopError Status Signal object
     */
    StatusSignal<double> &GetAverageClosedLoopError(bool refresh = true)
    {
        return _diffLeaderFX->GetClosedLoopError(refresh);
    }

    /**
     * \brief Value that the differential closed loop is targeting.
     *
     * \details This is the value that the differential closed loop PID
     * controller targets (on the difference axis).
     *
     * This refreshes and returns a cached StatusSignal object.
     *
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopReference Status Signal object
     */
    StatusSignal<double> &GetDifferentialClosedLoopReference(bool refresh = true)
    {
        return _diffLeaderFX->GetDifferentialClosedLoopReference(refresh);
    }

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
     * This refreshes and returns a cached StatusSignal object.
     *
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopReferenceSlope Status Signal object
     */
    StatusSignal<double> &GetDifferentialClosedLoopReferenceSlope(bool refresh = true)
    {
        return _diffLeaderFX->GetDifferentialClosedLoopReferenceSlope(refresh);
    }

    /**
     * \brief The difference between target differential reference and
     * current measurement.
     *
     * \details This is the value that is treated as the error in the
     * differential PID loop (on the difference axis).
     *
     * This refreshes and returns a cached StatusSignal object.
     *
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopError Status Signal object
     */
    StatusSignal<double> &GetDifferentialClosedLoopError(bool refresh = true)
    {
        return _diffLeaderFX->GetDifferentialClosedLoopError(refresh);
    }

    /**
     * \brief Sets the position of the mechanism in rotations.
     *
     * \param avgPosition The average position of the mechanism, in rotations
     * \param diffPosition The differential position of the mechanism, in rotations
     * \param timeoutSeconds Maximum time to wait up to in seconds
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetPosition(units::turn_t avgPosition, units::turn_t diffPosition = 0_tr, units::time::second_t timeoutSeconds = 0.100_s)
    {
        ctre::phoenix::StatusCode retval = ctre::phoenix::StatusCode::OK;

        auto response = _diffLeaderFX->SetPosition(avgPosition + diffPosition * _sensorToDiffRatio, timeoutSeconds);
        if (retval.IsOK()) retval = response;
        response = _diffFollowerFX->SetPosition(avgPosition - diffPosition * _sensorToDiffRatio, timeoutSeconds);
        if (retval.IsOK()) retval = response;

        return retval;
    }

    /**
     * \brief Get the Talon FX that is differential leader. The differential
     * leader calculates the output for the differential follower. The differential
     * leader is also used for fault detection, and it reports status signals for
     * the differential controller.
     *
     * \returns Differential leader Talon FX
     */
    MotorT &GetLeader()
    {
        return *_diffLeaderFX;
    }
    /**
     * \brief Get the Talon FX that is differential leader. The differential
     * leader calculates the output for the differential follower. The differential
     * leader is also useful for fault detection, and it reports status signals for
     * the differential controller.
     *
     * \returns Differential leader Talon FX
     */
    MotorT const &GetLeader() const
    {
        return *_diffLeaderFX;
    }

    /**
     * \brief Get the Talon FX that is differential follower. The differential
     * follower's position and velocity are used by the differential leader
     * for the differential controller.
     *
     * \returns Differential follower Talon FX
     */
    MotorT &GetFollower()
    {
        return *_diffFollowerFX;
    }
    /**
     * \brief Get the Talon FX that is differential follower. The differential
     * follower's position and velocity are used by the differential leader
     * for the differential controller.
     *
     * \returns Differential follower Talon FX
     */
    MotorT const &GetFollower() const
    {
        return *_diffFollowerFX;
    }

    /**
     * \brief Request neutral output of mechanism. The applied brake type
     * is determined by the NeutralMode configuration of each device.
     *
     * \details Since the NeutralMode configuration of devices may not align, users
     * may prefer to use the \c SetCoastOut() or \c SetStaticBrake() method.
     *
     * \returns Status Code of the request.
     */
    ctre::phoenix::StatusCode SetNeutralOut();

    /**
     * \brief Request coast neutral output of mechanism. The bridge is
     * disabled and the rotor is allowed to coast.
     *
     * \returns Status Code of the request.
     */
    ctre::phoenix::StatusCode SetCoastOut();

    /**
     * \brief Applies full neutral-brake on the mechanism by shorting
     * motor leads together.
     *
     * \returns Status Code of the request.
     */
    ctre::phoenix::StatusCode SetStaticBrake();

    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Request a specified motor duty cycle with a
     *                            differential position closed-loop.
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialDutyCycle const &diffLeaderFXRequest);
    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Request a specified voltage with a differential
     *                            position closed-loop.
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialVoltage const &diffLeaderFXRequest);
    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Request PID to target position with a differential
     *                            position setpoint.
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialPositionDutyCycle const &diffLeaderFXRequest);
    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Request PID to target position with a differential
     *                            position setpoint
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialPositionVoltage const &diffLeaderFXRequest);
    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Request PID to target velocity with a differential
     *                            position setpoint.
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialVelocityDutyCycle const &diffLeaderFXRequest);
    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Request PID to target velocity with a differential
     *                            position setpoint.
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialVelocityVoltage const &diffLeaderFXRequest);
    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Requests Motion Magic® to target a final position
     *                            using a motion profile, and PID to a differential
     *                            position setpoint.
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicDutyCycle const &diffLeaderFXRequest);
    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Requests Motion Magic® to target a final position
     *                            using a motion profile, and PID to a differential
     *                            position setpoint.
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicVoltage const &diffLeaderFXRequest);
    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Requests Motion Magic® to target a final position
     *                            using an exponential motion profile, and PID to a
     *                            differential position setpoint.
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicExpoDutyCycle const &diffLeaderFXRequest);
    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Requests Motion Magic® to target a final position
     *                            using an exponential motion profile, and PID to a
     *                            differential position setpoint.
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicExpoVoltage const &diffLeaderFXRequest);
    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Requests Motion Magic® to target a final velocity
     *                            using a motion profile, and PID to a differential
     *                            position setpoint.  This allows smooth transitions
     *                            between velocity set points.
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicVelocityDutyCycle const &diffLeaderFXRequest);
    /**
     * \brief Sets the control request for this mechanism.
     *
     * \param diffLeaderFXRequest Requests Motion Magic® to target a final velocity
     *                            using a motion profile, and PID to a differential
     *                            position setpoint.  This allows smooth transitions
     *                            between velocity set points.
     * \returns Status code of the request
     */
    ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicVelocityVoltage const &diffLeaderFXRequest);
};

}
}
}
