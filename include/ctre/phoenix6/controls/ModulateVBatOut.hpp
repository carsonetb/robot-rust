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
class ModulateVBatOut final : public ControlRequest {
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override;

public:
    /**
     * \brief Proportion of VBat to output in fractional units between 0.0 and 1.0.
     * 
     * - Units: fractional
     * 
     */
    units::dimensionless::scalar_t Output;

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
     * \param Output Proportion of VBat to output in fractional units between 0.0
     *               and 1.0.
     */
    constexpr ModulateVBatOut(units::dimensionless::scalar_t Output) : ControlRequest{},
        Output{std::move(Output)}
    {}

    constexpr ~ModulateVBatOut() override {}

    /**
     * \brief Gets the name of this control request.
     *
     * \returns Name of the control request
     */
    constexpr std::string_view GetName() const override
    {
        return "ModulateVBatOut";
    }
    
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
    constexpr ModulateVBatOut &WithOutput(units::dimensionless::scalar_t newOutput)
    {
        Output = std::move(newOutput);
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
    constexpr ModulateVBatOut &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
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

