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

#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include <units/frequency.h>
#include <units/time.h>
#include <units/dimensionless.h>

namespace ctre {
namespace phoenix6 {
namespace controls {

/**
 * Animation that looks similar to a flame flickering.
 * 
 * 
 */
class FireAnimation : public ControlRequest
{
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override
    {
        if (req.get() != this)
        {
            auto const reqCast = dynamic_cast<FireAnimation *>(req.get());
            if (reqCast != nullptr)
            {
                *reqCast = *this;
            }
            else
            {
                req = std::make_shared<FireAnimation>(*this);
            }
        }

        return c_ctre_phoenix6_RequestControlFireAnimation(network, deviceHash, UpdateFreqHz.to<double>(), LEDStartIndex, LEDEndIndex, Slot, Brightness.to<double>(), Direction.value, Sparking.to<double>(), Cooling.to<double>(), FrameRate.to<double>());
    }

public:
    /**
     * \brief The index of the first LED this animation controls (inclusive).
     * Indices 0-7 control the onboard LEDs, and 8-399 control an attached LED strip
     * 
     * If the start index is greater than the end index, the direction will be
     * reversed. The direction can also be changed using the Direction parameter.
     */
    int LEDStartIndex;
    /**
     * \brief The index of the last LED this animation controls (inclusive). Indices
     * 0-7 control the onboard LEDs, and 8-399 control an attached LED strip.
     * 
     * If the end index is less than the start index, the direction will be
     * reversed. The direction can also be changed using the Direction parameter.
     */
    int LEDEndIndex;
    /**
     * \brief The slot of this animation, within [0, 7]. Each slot on the CANdle can
     * store and run one animation.
     */
    int Slot = 0;
    /**
     * \brief The brightness of the animation, as a scalar from 0.0 to 1.0.
     */
    units::dimensionless::scalar_t Brightness = 1.0;
    /**
     * \brief The direction of the animation.
     */
    signals::AnimationDirectionValue Direction = signals::AnimationDirectionValue::Forward;
    /**
     * \brief The proportion of time in which sparks reignite the fire, as a scalar
     * from 0.0 to 1.0.
     */
    units::dimensionless::scalar_t Sparking = 0.6;
    /**
     * \brief The rate at which the fire cools along the travel, as a scalar from
     * 0.0 to 1.0.
     */
    units::dimensionless::scalar_t Cooling = 0.3;
    /**
     * \brief The frame rate of the animation, from [2, 1000] Hz. This determines
     * the speed of the animation.
     * 
     * A frame is defined as a transition in the state of the LEDs, advancing the
     * animation of the fire.
     * 
     * - Units: Hz
     * 
     */
    units::frequency::hertz_t FrameRate = 60_Hz;

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
     * \brief Animation that looks similar to a flame flickering.
     * 
     * \details 
     * 
     * \param LEDStartIndex    The index of the first LED this animation controls
     *                         (inclusive). Indices 0-7 control the onboard LEDs,
     *                         and 8-399 control an attached LED strip
     *                         
     *                         If the start index is greater than the end index, the
     *                         direction will be reversed. The direction can also be
     *                         changed using the Direction parameter.
     * \param LEDEndIndex    The index of the last LED this animation controls
     *                       (inclusive). Indices 0-7 control the onboard LEDs, and
     *                       8-399 control an attached LED strip.
     *                       
     *                       If the end index is less than the start index, the
     *                       direction will be reversed. The direction can also be
     *                       changed using the Direction parameter.
     */
    FireAnimation(int LEDStartIndex, int LEDEndIndex) : ControlRequest{"FireAnimation"},
        LEDStartIndex{std::move(LEDStartIndex)},
        LEDEndIndex{std::move(LEDEndIndex)}
    {}
    
    /**
     * \brief Modifies this Control Request's LEDStartIndex parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The index of the first LED this animation controls (inclusive). Indices 0-7
     * control the onboard LEDs, and 8-399 control an attached LED strip
     * 
     * If the start index is greater than the end index, the direction will be
     * reversed. The direction can also be changed using the Direction parameter.
     *
     * \param newLEDStartIndex Parameter to modify
     * \returns Itself
     */
    FireAnimation &WithLEDStartIndex(int newLEDStartIndex)
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
     * If the end index is less than the start index, the direction will be
     * reversed. The direction can also be changed using the Direction parameter.
     *
     * \param newLEDEndIndex Parameter to modify
     * \returns Itself
     */
    FireAnimation &WithLEDEndIndex(int newLEDEndIndex)
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
    FireAnimation &WithSlot(int newSlot)
    {
        Slot = std::move(newSlot);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's Brightness parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The brightness of the animation, as a scalar from 0.0 to 1.0.
     *
     * \param newBrightness Parameter to modify
     * \returns Itself
     */
    FireAnimation &WithBrightness(units::dimensionless::scalar_t newBrightness)
    {
        Brightness = std::move(newBrightness);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's Direction parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The direction of the animation.
     *
     * \param newDirection Parameter to modify
     * \returns Itself
     */
    FireAnimation &WithDirection(signals::AnimationDirectionValue newDirection)
    {
        Direction = std::move(newDirection);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's Sparking parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The proportion of time in which sparks reignite the fire, as a scalar from
     * 0.0 to 1.0.
     *
     * \param newSparking Parameter to modify
     * \returns Itself
     */
    FireAnimation &WithSparking(units::dimensionless::scalar_t newSparking)
    {
        Sparking = std::move(newSparking);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's Cooling parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The rate at which the fire cools along the travel, as a scalar from 0.0 to
     * 1.0.
     *
     * \param newCooling Parameter to modify
     * \returns Itself
     */
    FireAnimation &WithCooling(units::dimensionless::scalar_t newCooling)
    {
        Cooling = std::move(newCooling);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's FrameRate parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The frame rate of the animation, from [2, 1000] Hz. This determines the speed
     * of the animation.
     * 
     * A frame is defined as a transition in the state of the LEDs, advancing the
     * animation of the fire.
     * 
     * - Units: Hz
     * 
     *
     * \param newFrameRate Parameter to modify
     * \returns Itself
     */
    FireAnimation &WithFrameRate(units::frequency::hertz_t newFrameRate)
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
    FireAnimation &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
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
        ss << "Control: FireAnimation" << std::endl;
        ss << "    LEDStartIndex: " << LEDStartIndex << std::endl;
        ss << "    LEDEndIndex: " << LEDEndIndex << std::endl;
        ss << "    Slot: " << Slot << std::endl;
        ss << "    Brightness: " << Brightness.to<double>() << std::endl;
        ss << "    Direction: " << Direction << std::endl;
        ss << "    Sparking: " << Sparking.to<double>() << std::endl;
        ss << "    Cooling: " << Cooling.to<double>() << std::endl;
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
        ss << Brightness.to<double>(); controlInfo["Brightness"] = ss.str(); ss.str(std::string{});
        ss << Direction; controlInfo["Direction"] = ss.str(); ss.str(std::string{});
        ss << Sparking.to<double>(); controlInfo["Sparking"] = ss.str(); ss.str(std::string{});
        ss << Cooling.to<double>(); controlInfo["Cooling"] = ss.str(); ss.str(std::string{});
        ss << FrameRate.to<double>(); controlInfo["FrameRate"] = ss.str(); ss.str(std::string{});
        return controlInfo;
    }
};

}
}
}

