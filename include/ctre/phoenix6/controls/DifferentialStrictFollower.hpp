/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/controls/ControlRequest.hpp"
#include <units/frequency.h>
#include <units/time.h>

namespace ctre {
namespace phoenix6 {
namespace controls {

/**
 * Follow the differential motor output of another Talon while ignoring the
 * leader's invert setting.
 * 
 * If Talon is in torque control, the differential torque is copied - which will increase the total torque
 * applied. If Talon is in duty cycle output control, the differential duty cycle is matched. If Talon is in
 * voltage output control, the differential motor voltage is matched. Motor direction is strictly determined
 * by the configured invert and not the leader. If you want motor direction to match or oppose the leader, use
 * DifferentialFollower instead.
 * 
 * The leader must enable its DifferentialOutput status signal. The update rate of the status signal
 * determines the update rate of the follower's output and should be no slower than 20 Hz.
 */
class DifferentialStrictFollower final : public ControlRequest {
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override;

public:
    /**
     * \brief Device ID of the differential leader to follow.
     */
    int LeaderID;

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
     * \brief Follow the differential motor output of another Talon while ignoring
     *        the leader's invert setting.
     * 
     * \details If Talon is in torque control, the differential torque is copied -
     *          which will increase the total torque applied. If Talon is in duty
     *          cycle output control, the differential duty cycle is matched. If
     *          Talon is in voltage output control, the differential motor voltage
     *          is matched. Motor direction is strictly determined by the configured
     *          invert and not the leader. If you want motor direction to match or
     *          oppose the leader, use DifferentialFollower instead.
     *          
     *          The leader must enable its DifferentialOutput status signal. The
     *          update rate of the status signal determines the update rate of the
     *          follower's output and should be no slower than 20 Hz.
     * 
     * \param LeaderID Device ID of the differential leader to follow.
     */
    constexpr DifferentialStrictFollower(int LeaderID) : ControlRequest{},
        LeaderID{std::move(LeaderID)}
    {}

    constexpr ~DifferentialStrictFollower() override {}

    /**
     * \brief Gets the name of this control request.
     *
     * \returns Name of the control request
     */
    constexpr std::string_view GetName() const override
    {
        return "DifferentialStrictFollower";
    }
    
    /**
     * \brief Modifies this Control Request's LeaderID parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Device ID of the differential leader to follow.
     *
     * \param newLeaderID Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialStrictFollower &WithLeaderID(int newLeaderID)
    {
        LeaderID = std::move(newLeaderID);
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
    constexpr DifferentialStrictFollower &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
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

