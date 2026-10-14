/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include <units/dimensionless.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs to trim the Pigeon2's gyroscope.
 * 
 * \details Pigeon2 allows the user to trim the gyroscope's
 *          sensitivity. While this isn't necessary for the Pigeon2,
 *          as it comes calibrated out-of-the-box, users can make use
 *          of this to make the Pigeon2 even more accurate for their
 *          application.
 */
class GyroTrimConfigs : public ParentConfiguration {
public:
    constexpr GyroTrimConfigs() = default;

    /**
     * \brief The gyro scalar component for the X axis.
     * 
     * - Minimum Value: -180
     * - Maximum Value: 180
     * - Default Value: 0
     * - Units: deg per rotation
     */
    units::dimensionless::scalar_t GyroScalarX = 0;
    /**
     * \brief The gyro scalar component for the Y axis.
     * 
     * - Minimum Value: -180
     * - Maximum Value: 180
     * - Default Value: 0
     * - Units: deg per rotation
     */
    units::dimensionless::scalar_t GyroScalarY = 0;
    /**
     * \brief The gyro scalar component for the Z axis.
     * 
     * - Minimum Value: -180
     * - Maximum Value: 180
     * - Default Value: 0
     * - Units: deg per rotation
     */
    units::dimensionless::scalar_t GyroScalarZ = 0;
    
    /**
     * \brief Modifies this configuration's GyroScalarX parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The gyro scalar component for the X axis.
     * 
     * - Minimum Value: -180
     * - Maximum Value: 180
     * - Default Value: 0
     * - Units: deg per rotation
     *
     * \param newGyroScalarX Parameter to modify
     * \returns Itself
     */
    constexpr GyroTrimConfigs &WithGyroScalarX(units::dimensionless::scalar_t newGyroScalarX)
    {
        GyroScalarX = std::move(newGyroScalarX);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GyroScalarY parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The gyro scalar component for the Y axis.
     * 
     * - Minimum Value: -180
     * - Maximum Value: 180
     * - Default Value: 0
     * - Units: deg per rotation
     *
     * \param newGyroScalarY Parameter to modify
     * \returns Itself
     */
    constexpr GyroTrimConfigs &WithGyroScalarY(units::dimensionless::scalar_t newGyroScalarY)
    {
        GyroScalarY = std::move(newGyroScalarY);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GyroScalarZ parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The gyro scalar component for the Z axis.
     * 
     * - Minimum Value: -180
     * - Maximum Value: 180
     * - Default Value: 0
     * - Units: deg per rotation
     *
     * \param newGyroScalarZ Parameter to modify
     * \returns Itself
     */
    constexpr GyroTrimConfigs &WithGyroScalarZ(units::dimensionless::scalar_t newGyroScalarZ)
    {
        GyroScalarZ = std::move(newGyroScalarZ);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
