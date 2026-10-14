/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include <units/angle.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs that affect the ToF Field of View
 * 
 * \details Includes range and center configs
 */
class FovParamsConfigs : public ParentConfiguration {
public:
    constexpr FovParamsConfigs() = default;

    /**
     * \brief Specifies the target center of the Field of View in the X
     * direction.
     * 
     * \details The exact value may be different for different CANrange
     * devices due to imperfections in the sensing silicon.
     * 
     * - Minimum Value: -11.8
     * - Maximum Value: 11.8
     * - Default Value: 0
     * - Units: deg
     */
    units::angle::degree_t FOVCenterX = 0_deg;
    /**
     * \brief Specifies the target center of the Field of View in the Y
     * direction.
     * 
     * \details The exact value may be different for different CANrange
     * devices due to imperfections in the sensing silicon.
     * 
     * - Minimum Value: -11.8
     * - Maximum Value: 11.8
     * - Default Value: 0
     * - Units: deg
     */
    units::angle::degree_t FOVCenterY = 0_deg;
    /**
     * \brief Specifies the target range of the Field of View in the X
     * direction. This is the full range of the FOV.
     * 
     * The magnitude of this is capped to abs(27 - 2*FOVCenterX).
     * 
     * \details The exact value may be different for different CANrange
     * devices due to imperfections in the sensing silicon.
     * 
     * - Minimum Value: 6.75
     * - Maximum Value: 27
     * - Default Value: 27
     * - Units: deg
     */
    units::angle::degree_t FOVRangeX = 27_deg;
    /**
     * \brief Specifies the target range of the Field of View in the Y
     * direction. This is the full range of the FOV.
     * 
     * The magnitude of this is capped to abs(27 - 2*FOVCenterY).
     * 
     * \details The exact value may be different for different CANrange
     * devices due to imperfections in the sensing silicon.
     * 
     * - Minimum Value: 6.75
     * - Maximum Value: 27
     * - Default Value: 27
     * - Units: deg
     */
    units::angle::degree_t FOVRangeY = 27_deg;
    
    /**
     * \brief Modifies this configuration's FOVCenterX parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Specifies the target center of the Field of View in the X
     * direction.
     * 
     * \details The exact value may be different for different CANrange
     * devices due to imperfections in the sensing silicon.
     * 
     * - Minimum Value: -11.8
     * - Maximum Value: 11.8
     * - Default Value: 0
     * - Units: deg
     *
     * \param newFOVCenterX Parameter to modify
     * \returns Itself
     */
    constexpr FovParamsConfigs &WithFOVCenterX(units::angle::degree_t newFOVCenterX)
    {
        FOVCenterX = std::move(newFOVCenterX);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's FOVCenterY parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Specifies the target center of the Field of View in the Y
     * direction.
     * 
     * \details The exact value may be different for different CANrange
     * devices due to imperfections in the sensing silicon.
     * 
     * - Minimum Value: -11.8
     * - Maximum Value: 11.8
     * - Default Value: 0
     * - Units: deg
     *
     * \param newFOVCenterY Parameter to modify
     * \returns Itself
     */
    constexpr FovParamsConfigs &WithFOVCenterY(units::angle::degree_t newFOVCenterY)
    {
        FOVCenterY = std::move(newFOVCenterY);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's FOVRangeX parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Specifies the target range of the Field of View in the X direction.
     * This is the full range of the FOV.
     * 
     * The magnitude of this is capped to abs(27 - 2*FOVCenterX).
     * 
     * \details The exact value may be different for different CANrange
     * devices due to imperfections in the sensing silicon.
     * 
     * - Minimum Value: 6.75
     * - Maximum Value: 27
     * - Default Value: 27
     * - Units: deg
     *
     * \param newFOVRangeX Parameter to modify
     * \returns Itself
     */
    constexpr FovParamsConfigs &WithFOVRangeX(units::angle::degree_t newFOVRangeX)
    {
        FOVRangeX = std::move(newFOVRangeX);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's FOVRangeY parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Specifies the target range of the Field of View in the Y direction.
     * This is the full range of the FOV.
     * 
     * The magnitude of this is capped to abs(27 - 2*FOVCenterY).
     * 
     * \details The exact value may be different for different CANrange
     * devices due to imperfections in the sensing silicon.
     * 
     * - Minimum Value: 6.75
     * - Maximum Value: 27
     * - Default Value: 27
     * - Units: deg
     *
     * \param newFOVRangeY Parameter to modify
     * \returns Itself
     */
    constexpr FovParamsConfigs &WithFOVRangeY(units::angle::degree_t newFOVRangeY)
    {
        FOVRangeY = std::move(newFOVRangeY);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
