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
 * An empty animation, clearing any animation in the specified slot.
 * 
 * 
 */
class EmptyAnimation : public ControlRequest
{
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override
    {
        if (req.get() != this)
        {
            auto const reqCast = dynamic_cast<EmptyAnimation *>(req.get());
            if (reqCast != nullptr)
            {
                *reqCast = *this;
            }
            else
            {
                req = std::make_shared<EmptyAnimation>(*this);
            }
        }

        return c_ctre_phoenix6_RequestControlEmptyAnimation(network, deviceHash, UpdateFreqHz.to<double>(), Slot);
    }

public:
    /**
     * \brief The slot of this animation, within [0, 7]. Each slot on the CANdle can
     * store and run one animation.
     */
    int Slot;

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
    units::frequency::hertz_t UpdateFreqHz{0_Hz};

    /**
     * \brief An empty animation, clearing any animation in the specified slot.
     * 
     * \details 
     * 
     * \param Slot    The slot of this animation, within [0, 7]. Each slot on the
     *                CANdle can store and run one animation.
     */
    EmptyAnimation(int Slot) : ControlRequest{"EmptyAnimation"},
        Slot{std::move(Slot)}
    {}
    
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
    EmptyAnimation &WithSlot(int newSlot)
    {
        Slot = std::move(newSlot);
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
    EmptyAnimation &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
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
        ss << "Control: EmptyAnimation" << std::endl;
        ss << "    Slot: " << Slot << std::endl;
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
        ss << Slot; controlInfo["Slot"] = ss.str(); ss.str(std::string{});
        return controlInfo;
    }
};

}
}
}

