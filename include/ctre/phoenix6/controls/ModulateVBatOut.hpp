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

#include <units/frequency.h>
#include <units/time.h>
#include <units/dimensionless.h>

namespace ctre {
namespace phoenix6 {
namespace controls {

/**
 * Modulates the CANdle VBat output to the specified duty cycle. This can be
 * used to control a single-color LED strip.
 * 
 * Note that configs::CANdleFeaturesConfigs::VBatOutputMode must be set to
 * signals::VBatOutputModeValue::Modulated.
 * 
 * 
 */
class ModulateVBatOut : public ControlRequest
{
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override
    {
        if (req.get() != this)
        {
            auto const reqCast = dynamic_cast<ModulateVBatOut *>(req.get());
            if (reqCast != nullptr)
            {
                *reqCast = *this;
            }
            else
            {
                req = std::make_shared<ModulateVBatOut>(*this);
            }
        }

        return c_ctre_phoenix6_RequestControlModulateVBatOut(network, deviceHash, UpdateFreqHz.to<double>(), Output.to<double>());
    }

public:
    /**
     * \brief Proportion of VBat to output in fractional units between 0.0 and 1.0.
     * 
     * - Units: fractional
     * 
     */
    units::dimensionless::scalar_t Output;

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
    units::frequency::hertz_t UpdateFreqHz{50_Hz};

    /**
     * \brief Modulates the CANdle VBat output to the specified duty cycle. This can
     *        be used to control a single-color LED strip.
     *        
     *        Note that configs::CANdleFeaturesConfigs::VBatOutputMode must be set
     *        to signals::VBatOutputModeValue::Modulated.
     * 
     * \details 
     * 
     * \param Output    Proportion of VBat to output in fractional units between 0.0
     *                  and 1.0.
     */
    ModulateVBatOut(units::dimensionless::scalar_t Output) : ControlRequest{"ModulateVBatOut"},
        Output{std::move(Output)}
    {}
    
    /**
     * \brief Modifies this Control Request's Output parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Proportion of VBat to output in fractional units between 0.0 and 1.0.
     * 
     * - Units: fractional
     * 
     *
     * \param newOutput Parameter to modify
     * \returns Itself
     */
    ModulateVBatOut &WithOutput(units::dimensionless::scalar_t newOutput)
    {
        Output = std::move(newOutput);
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
    ModulateVBatOut &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
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
        ss << "Control: ModulateVBatOut" << std::endl;
        ss << "    Output: " << Output.to<double>() << " fractional" << std::endl;
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
        ss << Output.to<double>(); controlInfo["Output"] = ss.str(); ss.str(std::string{});
        return controlInfo;
    }
};

}
}
}

