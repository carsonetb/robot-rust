/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"


namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs that affect audible components of the device.
 * 
 * \details Includes configuration for the beep on boot.
 */
class AudioConfigs : public ParentConfiguration {
public:
    constexpr AudioConfigs() = default;

    /**
     * \brief If true, the TalonFX will beep during boot-up.  This is
     * useful for general debugging, and defaults to true.  If rotor is
     * moving during boot-up, the beep will not occur regardless of this
     * setting.
     * 
     * - Default Value: True
     */
    bool BeepOnBoot = true;
    /**
     * \brief If true, the TalonFX will beep during configuration API
     * calls if device is disabled.  This is useful for general debugging,
     * and defaults to true.  Note that if the rotor is moving, the beep
     * will not occur regardless of this setting.
     * 
     * - Default Value: True
     */
    bool BeepOnConfig = true;
    /**
     * \brief If true, the TalonFX will allow Orchestra and MusicTone
     * requests during disabled state.  This can be used to address corner
     * cases when music features are needed when disabled.  This setting
     * defaults to false.  Note that if the rotor is moving, music
     * features are always disabled regardless of this setting.
     * 
     * - Default Value: False
     */
    bool AllowMusicDurDisable = false;
    
    /**
     * \brief Modifies this configuration's BeepOnBoot parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If true, the TalonFX will beep during boot-up.  This is useful for
     * general debugging, and defaults to true.  If rotor is moving during
     * boot-up, the beep will not occur regardless of this setting.
     * 
     * - Default Value: True
     *
     * \param newBeepOnBoot Parameter to modify
     * \returns Itself
     */
    constexpr AudioConfigs &WithBeepOnBoot(bool newBeepOnBoot)
    {
        BeepOnBoot = std::move(newBeepOnBoot);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's BeepOnConfig parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If true, the TalonFX will beep during configuration API calls if
     * device is disabled.  This is useful for general debugging, and
     * defaults to true.  Note that if the rotor is moving, the beep will
     * not occur regardless of this setting.
     * 
     * - Default Value: True
     *
     * \param newBeepOnConfig Parameter to modify
     * \returns Itself
     */
    constexpr AudioConfigs &WithBeepOnConfig(bool newBeepOnConfig)
    {
        BeepOnConfig = std::move(newBeepOnConfig);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's AllowMusicDurDisable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If true, the TalonFX will allow Orchestra and MusicTone requests
     * during disabled state.  This can be used to address corner cases
     * when music features are needed when disabled.  This setting
     * defaults to false.  Note that if the rotor is moving, music
     * features are always disabled regardless of this setting.
     * 
     * - Default Value: False
     *
     * \param newAllowMusicDurDisable Parameter to modify
     * \returns Itself
     */
    constexpr AudioConfigs &WithAllowMusicDurDisable(bool newAllowMusicDurDisable)
    {
        AllowMusicDurDisable = std::move(newAllowMusicDurDisable);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
