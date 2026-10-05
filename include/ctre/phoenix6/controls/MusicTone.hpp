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

namespace ctre {
namespace phoenix6 {
namespace controls {

/**
 * Plays a single tone at the user specified frequency.
 */
class MusicTone : public ControlRequest
{
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override
    {
        if (req.get() != this)
        {
            auto const reqCast = dynamic_cast<MusicTone *>(req.get());
            if (reqCast != nullptr)
            {
                *reqCast = *this;
            }
            else
            {
                req = std::make_shared<MusicTone>(*this);
            }
        }

        return c_ctre_phoenix6_RequestControlMusicTone(network, deviceHash, UpdateFreqHz.to<double>(), AudioFrequency.to<double>());
    }

public:
    /**
     * \brief Sound frequency to play.  A value of zero will silence the device. The
     * effective frequency range is 10-20000 Hz.  Any nonzero frequency less than 10
     * Hz will be capped to 10 Hz.  Any frequency above 20 kHz will be capped to 20
     * kHz.
     * 
     * - Units: Hz
     * 
     */
    units::frequency::hertz_t AudioFrequency;

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
     * \brief Plays a single tone at the user specified frequency.
     * 
     * \param AudioFrequency    Sound frequency to play.  A value of zero will
     *                          silence the device. The effective frequency range is
     *                          10-20000 Hz.  Any nonzero frequency less than 10 Hz
     *                          will be capped to 10 Hz.  Any frequency above 20 kHz
     *                          will be capped to 20 kHz.
     */
    MusicTone(units::frequency::hertz_t AudioFrequency) : ControlRequest{"MusicTone"},
        AudioFrequency{std::move(AudioFrequency)}
    {}
    
    /**
     * \brief Modifies this Control Request's AudioFrequency parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Sound frequency to play.  A value of zero will silence the device. The
     * effective frequency range is 10-20000 Hz.  Any nonzero frequency less than 10
     * Hz will be capped to 10 Hz.  Any frequency above 20 kHz will be capped to 20
     * kHz.
     * 
     * - Units: Hz
     * 
     *
     * \param newAudioFrequency Parameter to modify
     * \returns Itself
     */
    MusicTone &WithAudioFrequency(units::frequency::hertz_t newAudioFrequency)
    {
        AudioFrequency = std::move(newAudioFrequency);
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
    MusicTone &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
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
        ss << "Control: MusicTone" << std::endl;
        ss << "    AudioFrequency: " << AudioFrequency.to<double>() << " Hz" << std::endl;
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
        ss << AudioFrequency.to<double>(); controlInfo["AudioFrequency"] = ss.str(); ss.str(std::string{});
        return controlInfo;
    }
};

}
}
}

