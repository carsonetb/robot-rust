/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/controls/ControlRequest.hpp"
#include "ctre/phoenix6/controls/MotionMagicVoltage.hpp"
#include "ctre/phoenix6/controls/VelocityVoltage.hpp"

namespace ctre {
namespace phoenix6 {
namespace controls {
namespace compound {

/**
 * \private
 * Requires Phoenix Pro and CANivore;
 * Differential control with Motion Magic® average target and velocity
 * difference target using voltage control.
 */
class Diff_MotionMagicVoltage_Velocity final : public ControlRequest {
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override;

public:
    /**
     * \brief Average MotionMagicVoltage request of the mechanism.
     */
    MotionMagicVoltage AverageRequest;
    /**
     * \brief Differential VelocityVoltage request of the mechanism.
     */
    VelocityVoltage DifferentialRequest;

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
    units::frequency::hertz_t UpdateFreqHz{100_Hz};

    /**
     * \brief Requires Phoenix Pro and CANivore;
     *        Differential control with Motion Magic® average target and velocity
     *        difference target using voltage control.
     * 
     * \param AverageRequest Average MotionMagicVoltage request of the mechanism.
     * \param DifferentialRequest Differential VelocityVoltage request of the
     *                            mechanism.
     */
    constexpr Diff_MotionMagicVoltage_Velocity(MotionMagicVoltage AverageRequest, VelocityVoltage DifferentialRequest) : ControlRequest{},
        AverageRequest{std::move(AverageRequest)},
        DifferentialRequest{std::move(DifferentialRequest)}
    {}

    constexpr ~Diff_MotionMagicVoltage_Velocity() override {}

    /**
     * \brief Gets the name of this control request.
     *
     * \returns Name of the control request
     */
    constexpr std::string_view GetName() const override
    {
        return "Diff_MotionMagicVoltage_Velocity";
    }
    
    /**
     * \brief Modifies this Control Request's AverageRequest parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Average MotionMagicVoltage request of the mechanism.
     *
     * \param newAverageRequest Parameter to modify
     * \returns Itself
     */
    constexpr Diff_MotionMagicVoltage_Velocity &WithAverageRequest(MotionMagicVoltage newAverageRequest)
    {
        AverageRequest = std::move(newAverageRequest);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's DifferentialRequest parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Differential VelocityVoltage request of the mechanism.
     *
     * \param newDifferentialRequest Parameter to modify
     * \returns Itself
     */
    constexpr Diff_MotionMagicVoltage_Velocity &WithDifferentialRequest(VelocityVoltage newDifferentialRequest)
    {
        DifferentialRequest = std::move(newDifferentialRequest);
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
    constexpr Diff_MotionMagicVoltage_Velocity &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
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
}

