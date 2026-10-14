/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/controls/ControlRequest.hpp"
#include "ctre/phoenix6/signals/RGBWColor.hpp"
#include <units/frequency.h>
#include <units/time.h>

namespace ctre {
namespace phoenix6 {
namespace controls {

/**
 * Sets LEDs to a solid color.
 * 
 * 
 */
class SolidColor final : public ControlRequest {
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override;

public:
    /**
     * \brief The index of the first LED this animation controls (inclusive).
     * Indices 0-7 control the onboard LEDs, and 8-399 control an attached LED
     * strip.
     */
    int LEDStartIndex;
    /**
     * \brief The index of the last LED this animation controls (inclusive). Indices
     * 0-7 control the onboard LEDs, and 8-399 control an attached LED strip.
     */
    int LEDEndIndex;
    /**
     * \brief The color to apply to the LEDs.
     */
    signals::RGBWColor Color = signals::RGBWColor{};

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
    // This request is always 0 Hz. units::frequency::hertz_t UpdateFreqHz{0_Hz};

    /**
     * \brief Sets LEDs to a solid color.
     * 
     * \details 
     * 
     * \param LEDStartIndex The index of the first LED this animation controls
     *                      (inclusive). Indices 0-7 control the onboard LEDs, and
     *                      8-399 control an attached LED strip.
     * \param LEDEndIndex The index of the last LED this animation controls
     *                    (inclusive). Indices 0-7 control the onboard LEDs, and
     *                    8-399 control an attached LED strip.
     */
    constexpr SolidColor(int LEDStartIndex, int LEDEndIndex) : ControlRequest{},
        LEDStartIndex{std::move(LEDStartIndex)},
        LEDEndIndex{std::move(LEDEndIndex)}
    {}

    constexpr ~SolidColor() override {}

    /**
     * \brief Gets the name of this control request.
     *
     * \returns Name of the control request
     */
    constexpr std::string_view GetName() const override
    {
        return "SolidColor";
    }
    
    /**
     * \brief Modifies this Control Request's LEDStartIndex parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The index of the first LED this animation controls (inclusive). Indices 0-7
     * control the onboard LEDs, and 8-399 control an attached LED strip.
     *
     * \param newLEDStartIndex Parameter to modify
     * \returns Itself
     */
    constexpr SolidColor &WithLEDStartIndex(int newLEDStartIndex)
    {
        LEDStartIndex = std::move(newLEDStartIndex);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's LEDEndIndex parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The index of the last LED this animation controls (inclusive). Indices 0-7
     * control the onboard LEDs, and 8-399 control an attached LED strip.
     *
     * \param newLEDEndIndex Parameter to modify
     * \returns Itself
     */
    constexpr SolidColor &WithLEDEndIndex(int newLEDEndIndex)
    {
        LEDEndIndex = std::move(newLEDEndIndex);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's Color parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The color to apply to the LEDs.
     *
     * \param newColor Parameter to modify
     * \returns Itself
     */
    constexpr SolidColor &WithColor(signals::RGBWColor newColor)
    {
        Color = std::move(newColor);
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
    constexpr SolidColor &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
    {
        // This request is always 0 Hz. UpdateFreqHz = newUpdateFreqHz;
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

