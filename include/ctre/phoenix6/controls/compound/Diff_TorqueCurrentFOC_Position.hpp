/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/controls/ControlRequest.hpp"
#include "ctre/phoenix6/networking/interfaces/Control_Interface.h"
#include <sstream>

#include "ctre/phoenix6/controls/TorqueCurrentFOC.hpp"
#include "ctre/phoenix6/controls/PositionTorqueCurrentFOC.hpp"

namespace ctre {
namespace phoenix6 {
namespace controls {
namespace compound {

/**
 * \private
 * Requires Phoenix Pro and CANivore;
 * Differential control with torque current average target and position
 * difference target.
 */
class Diff_TorqueCurrentFOC_Position : public ControlRequest
{
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override
    {
        if (req.get() != this)
        {
            auto const reqCast = dynamic_cast<Diff_TorqueCurrentFOC_Position *>(req.get());
            if (reqCast != nullptr)
            {
                *reqCast = *this;
            }
            else
            {
                req = std::make_shared<Diff_TorqueCurrentFOC_Position>(*this);
            }
        }

        return c_ctre_phoenix6_RequestControlDiff_TorqueCurrentFOC_Position(network, deviceHash, UpdateFreqHz.to<double>(), AverageRequest.Output.to<double>(), AverageRequest.MaxAbsDutyCycle.to<double>(), AverageRequest.Deadband.to<double>(), AverageRequest.OverrideCoastDurNeutral, AverageRequest.LimitForwardMotion, AverageRequest.LimitReverseMotion, AverageRequest.IgnoreHardwareLimits, AverageRequest.UseTimesync, DifferentialRequest.Position.to<double>(), DifferentialRequest.Velocity.to<double>(), DifferentialRequest.FeedForward.to<double>(), DifferentialRequest.Slot, DifferentialRequest.OverrideCoastDurNeutral, DifferentialRequest.LimitForwardMotion, DifferentialRequest.LimitReverseMotion, DifferentialRequest.IgnoreHardwareLimits, DifferentialRequest.UseTimesync);
    }

public:
    /**
     * \brief Average TorqueCurrentFOC request of the mechanism.
     */
    TorqueCurrentFOC AverageRequest;
    /**
     * \brief Differential PositionTorqueCurrentFOC request of the mechanism.
     */
    PositionTorqueCurrentFOC DifferentialRequest;

    /**
     * \brief The period at which this control will update at.
     * This is designated in Hertz, with a minimum of 20 Hz
     * (every 50 ms) and a maximum of 1000 Hz (every 1 ms).
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
     *        Differential control with torque current average target and position
     *        difference target.
     * 
     * \param AverageRequest    Average TorqueCurrentFOC request of the mechanism.
     * \param DifferentialRequest    Differential PositionTorqueCurrentFOC request
     *                               of the mechanism.
     */
    Diff_TorqueCurrentFOC_Position(TorqueCurrentFOC AverageRequest, PositionTorqueCurrentFOC DifferentialRequest) : ControlRequest{"Diff_TorqueCurrentFOC_Position"},
        AverageRequest{std::move(AverageRequest)},
        DifferentialRequest{std::move(DifferentialRequest)}
    {}
    
    /**
     * \brief Modifies this Control Request's AverageRequest parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Average TorqueCurrentFOC request of the mechanism.
     *
     * \param newAverageRequest Parameter to modify
     * \returns Itself
     */
    Diff_TorqueCurrentFOC_Position &WithAverageRequest(TorqueCurrentFOC newAverageRequest)
    {
        AverageRequest = std::move(newAverageRequest);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's DifferentialRequest parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Differential PositionTorqueCurrentFOC request of the mechanism.
     *
     * \param newDifferentialRequest Parameter to modify
     * \returns Itself
     */
    Diff_TorqueCurrentFOC_Position &WithDifferentialRequest(PositionTorqueCurrentFOC newDifferentialRequest)
    {
        DifferentialRequest = std::move(newDifferentialRequest);
        return *this;
    }
    /**
     * \brief Sets the period at which this control will update at.
     * This is designated in Hertz, with a minimum of 20 Hz
     * (every 50 ms) and a maximum of 1000 Hz (every 1 ms).
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
    Diff_TorqueCurrentFOC_Position &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
    {
        UpdateFreqHz = newUpdateFreqHz;
        return *this;
    }
    /**
     * \brief Returns a string representation of the object.
     *
     * \returns a string representation of the object.
     */
    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Control: Diff_TorqueCurrentFOC_Position" << std::endl;
        ss << "    AverageRequest:" << std::endl;
        ss << "        Output: " << AverageRequest.Output.to<double>() << " A" << std::endl;
        ss << "        MaxAbsDutyCycle: " << AverageRequest.MaxAbsDutyCycle.to<double>() << " fractional" << std::endl;
        ss << "        Deadband: " << AverageRequest.Deadband.to<double>() << " A" << std::endl;
        ss << "        OverrideCoastDurNeutral: " << AverageRequest.OverrideCoastDurNeutral << std::endl;
        ss << "        LimitForwardMotion: " << AverageRequest.LimitForwardMotion << std::endl;
        ss << "        LimitReverseMotion: " << AverageRequest.LimitReverseMotion << std::endl;
        ss << "        IgnoreHardwareLimits: " << AverageRequest.IgnoreHardwareLimits << std::endl;
        ss << "        UseTimesync: " << AverageRequest.UseTimesync << std::endl;
        ss << "    DifferentialRequest:" << std::endl;
        ss << "        Position: " << DifferentialRequest.Position.to<double>() << " rotations" << std::endl;
        ss << "        Velocity: " << DifferentialRequest.Velocity.to<double>() << " rotations per second" << std::endl;
        ss << "        FeedForward: " << DifferentialRequest.FeedForward.to<double>() << " A" << std::endl;
        ss << "        Slot: " << DifferentialRequest.Slot << std::endl;
        ss << "        OverrideCoastDurNeutral: " << DifferentialRequest.OverrideCoastDurNeutral << std::endl;
        ss << "        LimitForwardMotion: " << DifferentialRequest.LimitForwardMotion << std::endl;
        ss << "        LimitReverseMotion: " << DifferentialRequest.LimitReverseMotion << std::endl;
        ss << "        IgnoreHardwareLimits: " << DifferentialRequest.IgnoreHardwareLimits << std::endl;
        ss << "        UseTimesync: " << DifferentialRequest.UseTimesync << std::endl;
        return ss.str();
    }

    /**
     * \brief Gets information about this control request.
     *
     * \returns Map of control parameter names and corresponding applied values
     */
    std::map<std::string, std::string> GetControlInfo() const override
    {
        std::map<std::string, std::string> controlInfo;
        std::stringstream ss;
        controlInfo["Name"] = GetName();
        ss << AverageRequest.ToString(); controlInfo["AverageRequest"] = ss.str(); ss.str(std::string{});
        ss << DifferentialRequest.ToString(); controlInfo["DifferentialRequest"] = ss.str(); ss.str(std::string{});
        return controlInfo;
    }
};

}
}
}
}

