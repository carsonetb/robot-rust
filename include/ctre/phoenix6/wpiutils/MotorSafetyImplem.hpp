/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "frc/MotorSafety.h"
#include <functional>

namespace ctre {
namespace phoenix6 {
namespace wpiutils {

/**
 * \brief Implem of MotorSafety interface from WPILib. This also allows
 * late/lazy construction of WPILib's motor safety object.
 */
class MotorSafetyImplem : public frc::MotorSafety {
private:
    std::function<void()> m_stopMotor;
    std::string const &m_description;

public:
    /**
     * \brief Constructor for MotorSafetyImplem
     * \param stopMotor Function to stop the motor
     * \param description Description of motor controller
     */
    MotorSafetyImplem(std::function<void()> stopMotor, std::string const &description) :
        m_stopMotor{std::move(stopMotor)},
        m_description{description}
    {}

    /**
     * \brief Stops the controller
     */
    void StopMotor() override
    {
        m_stopMotor();
    }
    /**
     * \returns Description of motor controller
     */
    std::string GetDescription() const override
    {
        return m_description;
    }
};

}
}
}
