/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs that determine motor selection and commutation.
 * 
 * \details Set these configs to match your motor setup before
 *          commanding motor output.
 */
class CommutationConfigs : public ParentConfiguration {
public:
    constexpr CommutationConfigs() = default;

    /**
     * \brief Requires Phoenix Pro; Improves commutation and velocity
     * measurement for motors with hall sensors.  Talon can use advanced
     * features to improve commutation and velocity measurement when using
     * a motor with hall sensors.  This can improve peak efficiency by as
     * high as 2% and reduce noise in the measured velocity.
     * 
     */
    signals::AdvancedHallSupportValue AdvancedHallSupport = signals::AdvancedHallSupportValue::Disabled;
    /**
     * \brief Selects the motor and motor connections used with Talon.
     * 
     * This setting determines what kind of motor and sensors are used
     * with the Talon.  This also determines what signals are used on the
     * JST and Gadgeteer port.
     * 
     * Motor drive will not function correctly if this setting does not
     * match the physical setup.
     * 
     */
    signals::MotorArrangementValue MotorArrangement = signals::MotorArrangementValue::Disabled;
    /**
     * \brief If a brushed motor is selected with Motor Arrangement, this
     * config determines which of three leads to use.
     * 
     */
    signals::BrushedMotorWiringValue BrushedMotorWiring = signals::BrushedMotorWiringValue::Leads_A_and_B;
    
    /**
     * \brief Modifies this configuration's AdvancedHallSupport parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Requires Phoenix Pro; Improves commutation and velocity measurement
     * for motors with hall sensors.  Talon can use advanced features to
     * improve commutation and velocity measurement when using a motor
     * with hall sensors.  This can improve peak efficiency by as high as
     * 2% and reduce noise in the measured velocity.
     * 
     *
     * \param newAdvancedHallSupport Parameter to modify
     * \returns Itself
     */
    constexpr CommutationConfigs &WithAdvancedHallSupport(signals::AdvancedHallSupportValue newAdvancedHallSupport)
    {
        AdvancedHallSupport = std::move(newAdvancedHallSupport);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MotorArrangement parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Selects the motor and motor connections used with Talon.
     * 
     * This setting determines what kind of motor and sensors are used
     * with the Talon.  This also determines what signals are used on the
     * JST and Gadgeteer port.
     * 
     * Motor drive will not function correctly if this setting does not
     * match the physical setup.
     * 
     *
     * \param newMotorArrangement Parameter to modify
     * \returns Itself
     */
    constexpr CommutationConfigs &WithMotorArrangement(signals::MotorArrangementValue newMotorArrangement)
    {
        MotorArrangement = std::move(newMotorArrangement);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's BrushedMotorWiring parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If a brushed motor is selected with Motor Arrangement, this config
     * determines which of three leads to use.
     * 
     *
     * \param newBrushedMotorWiring Parameter to modify
     * \returns Itself
     */
    constexpr CommutationConfigs &WithBrushedMotorWiring(signals::BrushedMotorWiringValue newBrushedMotorWiring)
    {
        BrushedMotorWiring = std::move(newBrushedMotorWiring);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
