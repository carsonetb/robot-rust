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
 * \brief Custom Params.
 * 
 * \details Custom paramaters that have no real impact on controller.
 */
class CustomParamsConfigs : public ParentConfiguration {
public:
    constexpr CustomParamsConfigs() = default;

    /**
     * \brief Custom parameter 0.  This is provided to allow
     * end-applications to store persistent information in the device.
     * 
     * - Minimum Value: -32768
     * - Maximum Value: 32767
     * - Default Value: 0
     * - Units: 
     */
    int CustomParam0 = 0;
    /**
     * \brief Custom parameter 1.  This is provided to allow
     * end-applications to store persistent information in the device.
     * 
     * - Minimum Value: -32768
     * - Maximum Value: 32767
     * - Default Value: 0
     * - Units: 
     */
    int CustomParam1 = 0;
    
    /**
     * \brief Modifies this configuration's CustomParam0 parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Custom parameter 0.  This is provided to allow end-applications to
     * store persistent information in the device.
     * 
     * - Minimum Value: -32768
     * - Maximum Value: 32767
     * - Default Value: 0
     * - Units: 
     *
     * \param newCustomParam0 Parameter to modify
     * \returns Itself
     */
    constexpr CustomParamsConfigs &WithCustomParam0(int newCustomParam0)
    {
        CustomParam0 = std::move(newCustomParam0);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's CustomParam1 parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Custom parameter 1.  This is provided to allow end-applications to
     * store persistent information in the device.
     * 
     * - Minimum Value: -32768
     * - Maximum Value: 32767
     * - Default Value: 0
     * - Units: 
     *
     * \param newCustomParam1 Parameter to modify
     * \returns Itself
     */
    constexpr CustomParamsConfigs &WithCustomParam1(int newCustomParam1)
    {
        CustomParam1 = std::move(newCustomParam1);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
