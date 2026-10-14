/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/controls/ControlRequest.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include "ctre/phoenix6/signals/RGBWColor.hpp"
#include <units/frequency.h>
#include <units/time.h>

namespace ctre {
namespace phoenix6 {
namespace controls {

/**
 * Animation that gradually lights the entire LED strip one LED at a time.
 * 
 * 
 */
class ColorFlowAnimation final : public ControlRequest {
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override;

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
     * \brief The color to use in the animation.
     */
    signals::RGBWColor Color = signals::RGBWColor{};
    /**
     * \brief The direction of the animation.
     */
    signals::AnimationDirectionValue Direction = signals::AnimationDirectionValue::Forward;
    /**
     * \brief The frame rate of the animation, from [2, 1000] Hz. This determines
     * the speed of the animation.
     * 
     * A frame is defined as a transition in the state of the LEDs, turning one on
     * or off.
     * 
     * - Units: Hz
     * 
     */
    units::frequency::hertz_t FrameRate = 25_Hz;

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
     * \brief Animation that gradually lights the entire LED strip one LED at a
     *        time.
     * 
     * \details 
     * 
     * \param LEDStartIndex The index of the first LED this animation controls
     *                      (inclusive). Indices 0-7 control the onboard LEDs, and
     *                      8-399 control an attached LED strip
     *                      
     *                      If the start index is greater than the end index, the
     *                      direction will be reversed. The direction can also be
     *                      changed using the Direction parameter.
     * \param LEDEndIndex The index of the last LED this animation controls
     *                    (inclusive). Indices 0-7 control the onboard LEDs, and
     *                    8-399 control an attached LED strip.
     *                    
     *                    If the end index is less than the start index, the
     *                    direction will be reversed. The direction can also be
     *                    changed using the Direction parameter.
     */
    constexpr ColorFlowAnimation(int LEDStartIndex, int LEDEndIndex) : ControlRequest{},
        LEDStartIndex{std::move(LEDStartIndex)},
        LEDEndIndex{std::move(LEDEndIndex)}
    {}

    constexpr ~ColorFlowAnimation() override {}

    /**
     * \brief Gets the name of this control request.
     *
     * \returns Name of the control request
     */
    constexpr std::string_view GetName() const override
    {
        return "ColorFlowAnimation";
    }
    
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
    constexpr ColorFlowAnimation &WithLEDStartIndex(int newLEDStartIndex)
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
    constexpr ColorFlowAnimation &WithLEDEndIndex(int newLEDEndIndex)
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
    constexpr ColorFlowAnimation &WithSlot(int newSlot)
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
    constexpr ColorFlowAnimation &WithColor(signals::RGBWColor newColor)
    {
        Color = std::move(newColor);
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
    constexpr ColorFlowAnimation &WithDirection(signals::AnimationDirectionValue newDirection)
    {
        Direction = std::move(newDirection);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's FrameRate parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The frame rate of the animation, from [2, 1000] Hz. This determines the speed
     * of the animation.
     * 
     * A frame is defined as a transition in the state of the LEDs, turning one on
     * or off.
     * 
     * - Units: Hz
     * 
     *
     * \param newFrameRate Parameter to modify
     * \returns Itself
     */
    constexpr ColorFlowAnimation &WithFrameRate(units::frequency::hertz_t newFrameRate)
    {
        FrameRate = std::move(newFrameRate);
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
    constexpr ColorFlowAnimation &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
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

