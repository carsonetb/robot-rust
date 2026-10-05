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

#include "ctre/phoenix6/signals/RGBWColor.hpp"
#include <units/frequency.h>
#include <units/time.h>
#include <units/dimensionless.h>

namespace ctre {
namespace phoenix6 {
namespace controls {

/**
 * Animation that randomly turns on LEDs until it reaches the maximum count, and
 * then turns them all off.
 * 
 * 
 */
class TwinkleOffAnimation : public ControlRequest
{
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override
    {
        if (req.get() != this)
        {
            auto const reqCast = dynamic_cast<TwinkleOffAnimation *>(req.get());
            if (reqCast != nullptr)
            {
                *reqCast = *this;
            }
            else
            {
                req = std::make_shared<TwinkleOffAnimation>(*this);
            }
        }

        return c_ctre_phoenix6_RequestControlTwinkleOffAnimation(network, deviceHash, UpdateFreqHz.to<double>(), LEDStartIndex, LEDEndIndex, Slot, Color.Red, Color.Green, Color.Blue, Color.White, MaxLEDsOnProportion.to<double>(), FrameRate.to<double>());
    }

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
     * \brief The slot of this animation, within [0, 7]. Each slot on the CANdle can
     * store and run one animation.
     */
    int Slot = 0;
    /**
     * \brief The color to use in the animation.
     */
    signals::RGBWColor Color = signals::RGBWColor{};
    /**
     * \brief The max proportion of LEDs that can be on, in the range [0.1, 1.0].
     */
    units::dimensionless::scalar_t MaxLEDsOnProportion = 1.0;
    /**
     * \brief The frame rate of the animation, from [2, 1000] Hz. This determines
     * the speed of the animation.
     * 
     * A frame is defined as a transition in the state of the LEDs, turning one LED
     * on or all LEDs off.
     * 
     * - Units: Hz
     * 
     */
    units::frequency::hertz_t FrameRate = 25_Hz;

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
    units::frequency::hertz_t UpdateFreqHz{20_Hz};

    /**
     * \brief Animation that randomly turns on LEDs until it reaches the maximum
     *        count, and then turns them all off.
     * 
     * \details 
     * 
     * \param LEDStartIndex    The index of the first LED this animation controls
     *                         (inclusive). Indices 0-7 control the onboard LEDs,
     *                         and 8-399 control an attached LED strip.
     * \param LEDEndIndex    The index of the last LED this animation controls
     *                       (inclusive). Indices 0-7 control the onboard LEDs, and
     *                       8-399 control an attached LED strip.
     */
    TwinkleOffAnimation(int LEDStartIndex, int LEDEndIndex) : ControlRequest{"TwinkleOffAnimation"},
        LEDStartIndex{std::move(LEDStartIndex)},
        LEDEndIndex{std::move(LEDEndIndex)}
    {}
    
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
    TwinkleOffAnimation &WithLEDStartIndex(int newLEDStartIndex)
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
    TwinkleOffAnimation &WithLEDEndIndex(int newLEDEndIndex)
    {
        LEDEndIndex = std::move(newLEDEndIndex);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's Slot parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The slot of this animation, within [0, 7]. Each slot on the CANdle can store
     * and run one animation.
     *
     * \param newSlot Parameter to modify
     * \returns Itself
     */
    TwinkleOffAnimation &WithSlot(int newSlot)
    {
        Slot = std::move(newSlot);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's Color parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The color to use in the animation.
     *
     * \param newColor Parameter to modify
     * \returns Itself
     */
    TwinkleOffAnimation &WithColor(signals::RGBWColor newColor)
    {
        Color = std::move(newColor);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's MaxLEDsOnProportion parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The max proportion of LEDs that can be on, in the range [0.1, 1.0].
     *
     * \param newMaxLEDsOnProportion Parameter to modify
     * \returns Itself
     */
    TwinkleOffAnimation &WithMaxLEDsOnProportion(units::dimensionless::scalar_t newMaxLEDsOnProportion)
    {
        MaxLEDsOnProportion = std::move(newMaxLEDsOnProportion);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's FrameRate parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The frame rate of the animation, from [2, 1000] Hz. This determines the speed
     * of the animation.
     * 
     * A frame is defined as a transition in the state of the LEDs, turning one LED
     * on or all LEDs off.
     * 
     * - Units: Hz
     * 
     *
     * \param newFrameRate Parameter to modify
     * \returns Itself
     */
    TwinkleOffAnimation &WithFrameRate(units::frequency::hertz_t newFrameRate)
    {
        FrameRate = std::move(newFrameRate);
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
    TwinkleOffAnimation &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
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
        ss << "Control: TwinkleOffAnimation" << std::endl;
        ss << "    LEDStartIndex: " << LEDStartIndex << std::endl;
        ss << "    LEDEndIndex: " << LEDEndIndex << std::endl;
        ss << "    Slot: " << Slot << std::endl;
        ss << "    Color: " << Color << std::endl;
        ss << "    MaxLEDsOnProportion: " << MaxLEDsOnProportion.to<double>() << std::endl;
        ss << "    FrameRate: " << FrameRate.to<double>() << " Hz" << std::endl;
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
        ss << LEDStartIndex; controlInfo["LEDStartIndex"] = ss.str(); ss.str(std::string{});
        ss << LEDEndIndex; controlInfo["LEDEndIndex"] = ss.str(); ss.str(std::string{});
        ss << Slot; controlInfo["Slot"] = ss.str(); ss.str(std::string{});
        ss << Color; controlInfo["Color"] = ss.str(); ss.str(std::string{});
        ss << MaxLEDsOnProportion.to<double>(); controlInfo["MaxLEDsOnProportion"] = ss.str(); ss.str(std::string{});
        ss << FrameRate.to<double>(); controlInfo["FrameRate"] = ss.str(); ss.str(std::string{});
        return controlInfo;
    }
};

}
}
}

