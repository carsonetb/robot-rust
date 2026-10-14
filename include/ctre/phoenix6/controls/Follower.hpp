/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/controls/ControlRequest.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include <units/frequency.h>
#include <units/time.h>

namespace ctre {
namespace phoenix6 {
namespace controls {

/**
 * Follow the motor output of another Talon.
 * 
 * The follower will atomically change its output type when it receives the leader's latest output status
 * signal (DutyCycle, MotorVoltage, TorqueCurrent). If Talon is in torque control, the torque is copied -
 * which will increase the total torque applied. If Talon is in duty cycle output control, the duty cycle is
 * matched. If Talon is in voltage output control, the motor voltage is matched. Motor direction either
 * matches the leader's configured direction or opposes it based on the MotorAlignment.
 * 
 * The leader must ensure the status signal corresponding to its control output type (DutyCycle, MotorVoltage,
 * TorqueCurrent) is enabled. The update rate of the status signal determines the update rate of the
 * follower's output and should be no slower than 20 Hz.
 */
class Follower final : public ControlRequest {
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override;

public:
    /**
     * \brief Device ID of the leader to follow.
     */
    int LeaderID;
    /**
     * \brief Set to Aligned for motor invert to match the leader's configured
     * Invert - which is typical when leader and follower are mechanically linked
     * and spin in the same direction.  Set to Opposed for motor invert to oppose
     * the leader's configured Invert - this is typical where the leader and
     * follower mechanically spin in opposite directions.
     */
    signals::MotorAlignmentValue MotorAlignment;

    /**
     * \brief The frequency at which this control will update.
     * This is designated in Hertz, with a minimum of 20 Hz
     * (every 50 ms) and a maximum of 1000 Hz (every 1 ms).
     * Some update frequencies are not supported and will be
     * promoted up to the next highest supported frequency.
     *
     * If this field is set to 0 Hz, the control request will
     * be sent immediately as a one-shot frame. This may be useful
     * for advanced applications that require outputs to be
     * synchronized with data acquisition. In this case, we
     * recommend not exceeding 50 ms between control calls.
     */
    units::frequency::hertz_t UpdateFreqHz{20_Hz};

    /**
     * \brief Follow the motor output of another Talon.
     * 
     * \details The follower will atomically change its output type when it receives
     *          the leader's latest output status signal (DutyCycle, MotorVoltage,
     *          TorqueCurrent). If Talon is in torque control, the torque is copied
     *          - which will increase the total torque applied. If Talon is in duty
     *          cycle output control, the duty cycle is matched. If Talon is in
     *          voltage output control, the motor voltage is matched. Motor
     *          direction either matches the leader's configured direction or
     *          opposes it based on the MotorAlignment.
     *          
     *          The leader must ensure the status signal corresponding to its
     *          control output type (DutyCycle, MotorVoltage, TorqueCurrent) is
     *          enabled. The update rate of the status signal determines the update
     *          rate of the follower's output and should be no slower than 20 Hz.
     * 
     * \param LeaderID Device ID of the leader to follow.
     * \param MotorAlignment Set to Aligned for motor invert to match the leader's
     *                       configured Invert - which is typical when leader and
     *                       follower are mechanically linked and spin in the same
     *                       direction.  Set to Opposed for motor invert to oppose
     *                       the leader's configured Invert - this is typical where
     *                       the leader and follower mechanically spin in opposite
     *                       directions.
     */
    constexpr Follower(int LeaderID, signals::MotorAlignmentValue MotorAlignment) : ControlRequest{},
        LeaderID{std::move(LeaderID)},
        MotorAlignment{std::move(MotorAlignment)}
    {}

    constexpr ~Follower() override {}

    /**
     * \brief Gets the name of this control request.
     *
     * \returns Name of the control request
     */
    constexpr std::string_view GetName() const override
    {
        return "Follower";
    }
    
    /**
     * \brief Modifies this Control Request's LeaderID parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Device ID of the leader to follow.
     *
     * \param newLeaderID Parameter to modify
     * \returns Itself
     */
    constexpr Follower &WithLeaderID(int newLeaderID)
    {
        LeaderID = std::move(newLeaderID);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's MotorAlignment parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Set to Aligned for motor invert to match the leader's configured Invert -
     * which is typical when leader and follower are mechanically linked and spin in
     * the same direction.  Set to Opposed for motor invert to oppose the leader's
     * configured Invert - this is typical where the leader and follower
     * mechanically spin in opposite directions.
     *
     * \param newMotorAlignment Parameter to modify
     * \returns Itself
     */
    constexpr Follower &WithMotorAlignment(signals::MotorAlignmentValue newMotorAlignment)
    {
        MotorAlignment = std::move(newMotorAlignment);
        return *this;
    }

    /**
     * \brief Sets the frequency at which this control will update.
     * This is designated in Hertz, with a minimum of 20 Hz
     * (every 50 ms) and a maximum of 1000 Hz (every 1 ms).
     * Some update frequencies are not supported and will be
     * promoted up to the next highest supported frequency.
     *
     * If this field is set to 0 Hz, the control request will
     * be sent immediately as a one-shot frame. This may be useful
     * for advanced applications that require outputs to be
     * synchronized with data acquisition. In this case, we
     * recommend not exceeding 50 ms between control calls.
     *
     * \param newUpdateFreqHz Parameter to modify
     * \returns Itself
     */
    constexpr Follower &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
    {
        UpdateFreqHz = newUpdateFreqHz;
        return *this;
    }

    /**
     * \brief Returns a string representation of the object.
     *
     * \returns a string representation of the object.
     */
    std::string ToString() const override;

    /**
     * \brief Gets information about this control request.
     *
     * \returns Map of control parameter names and corresponding applied values
     */
    std::map<std::string, std::string> GetControlInfo() const override;
};

}
}
}

