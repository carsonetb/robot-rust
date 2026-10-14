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
 * \brief Configs related to the CANdi™ branded device's digital I/O
 *        settings
 * 
 * \details Contains float-state settings and when to assert the S1/S2
 *          inputs.
 */
class DigitalInputsConfigs : public ParentConfiguration {
public:
    constexpr DigitalInputsConfigs() = default;

    /**
     * \brief The floating state of the Signal 1 input (S1IN).
     * 
     */
    signals::S1FloatStateValue S1FloatState = signals::S1FloatStateValue::FloatDetect;
    /**
     * \brief The floating state of the Signal 2 input (S2IN).
     * 
     */
    signals::S2FloatStateValue S2FloatState = signals::S2FloatStateValue::FloatDetect;
    /**
     * \brief What value the Signal 1 input (S1IN) needs to be for the CTR
     * Electronics' CANdi™ to detect as Closed.
     * 
     * \details Devices using the S1 input as a remote limit switch will
     * treat the switch as closed when the S1 input is this state.
     * 
     */
    signals::S1CloseStateValue S1CloseState = signals::S1CloseStateValue::CloseWhenNotFloating;
    /**
     * \brief What value the Signal 2 input (S2IN) needs to be for the CTR
     * Electronics' CANdi™ to detect as Closed.
     * 
     * \details Devices using the S2 input as a remote limit switch will
     * treat the switch as closed when the S2 input is this state.
     * 
     */
    signals::S2CloseStateValue S2CloseState = signals::S2CloseStateValue::CloseWhenNotFloating;
    
    /**
     * \brief Modifies this configuration's S1FloatState parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The floating state of the Signal 1 input (S1IN).
     * 
     *
     * \param newS1FloatState Parameter to modify
     * \returns Itself
     */
    constexpr DigitalInputsConfigs &WithS1FloatState(signals::S1FloatStateValue newS1FloatState)
    {
        S1FloatState = std::move(newS1FloatState);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's S2FloatState parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The floating state of the Signal 2 input (S2IN).
     * 
     *
     * \param newS2FloatState Parameter to modify
     * \returns Itself
     */
    constexpr DigitalInputsConfigs &WithS2FloatState(signals::S2FloatStateValue newS2FloatState)
    {
        S2FloatState = std::move(newS2FloatState);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's S1CloseState parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * What value the Signal 1 input (S1IN) needs to be for the CTR
     * Electronics' CANdi™ to detect as Closed.
     * 
     * \details Devices using the S1 input as a remote limit switch will
     * treat the switch as closed when the S1 input is this state.
     * 
     *
     * \param newS1CloseState Parameter to modify
     * \returns Itself
     */
    constexpr DigitalInputsConfigs &WithS1CloseState(signals::S1CloseStateValue newS1CloseState)
    {
        S1CloseState = std::move(newS1CloseState);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's S2CloseState parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * What value the Signal 2 input (S2IN) needs to be for the CTR
     * Electronics' CANdi™ to detect as Closed.
     * 
     * \details Devices using the S2 input as a remote limit switch will
     * treat the switch as closed when the S2 input is this state.
     * 
     *
     * \param newS2CloseState Parameter to modify
     * \returns Itself
     */
    constexpr DigitalInputsConfigs &WithS2CloseState(signals::S2CloseStateValue newS2CloseState)
    {
        S2CloseState = std::move(newS2CloseState);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
