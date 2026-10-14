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
 * Request neutral output of actuator. The applied brake type is determined by
 * the NeutralMode configuration.
 */
class NeutralOut final : public ControlRequest {
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override;

public:
    /**
     * \brief Set to true to delay applying this control request until a timesync
     * boundary (requires Phoenix Pro and CANivore). This eliminates the impact of
     * nondeterministic network delays in exchange for a larger but deterministic
     * control latency.
     * 
     * This requires setting the ControlTimesyncFreqHz config in MotorOutputConfigs.
     * Additionally, when this is enabled, the UpdateFreqHz of this request should
     * be set to 0 Hz.
     */
    bool UseTimesync = false;

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
     * \brief Request neutral output of actuator. The applied brake type is
     *        determined by the NeutralMode configuration.
     * 
     */
    constexpr NeutralOut() : ControlRequest{}
    {}

    constexpr ~NeutralOut() override {}

    /**
     * \brief Gets the name of this control request.
     *
     * \returns Name of the control request
     */
    constexpr std::string_view GetName() const override
    {
        return "NeutralOut";
    }
    
    /**
     * \brief Modifies this Control Request's UseTimesync parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Set to true to delay applying this control request until a timesync boundary
     * (requires Phoenix Pro and CANivore). This eliminates the impact of
     * nondeterministic network delays in exchange for a larger but deterministic
     * control latency.
     * 
     * This requires setting the ControlTimesyncFreqHz config in MotorOutputConfigs.
     * Additionally, when this is enabled, the UpdateFreqHz of this request should
     * be set to 0 Hz.
     *
     * \param newUseTimesync Parameter to modify
     * \returns Itself
     */
    constexpr NeutralOut &WithUseTimesync(bool newUseTimesync)
    {
        UseTimesync = std::move(newUseTimesync);
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
    constexpr NeutralOut &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
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

