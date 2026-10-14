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
 * \brief Configs related to the CANdi™ branded device's quadrature
 *        interface using both the S1IN and S2IN inputs
 * 
 * \details All the configs related to the quadrature interface for
 *          the CANdi™ branded device , including encoder edges per
 *          revolution and sensor direction.
 */
class QuadratureConfigs : public ParentConfiguration {
public:
    constexpr QuadratureConfigs() = default;

    /**
     * \brief The number of quadrature edges in one rotation for the
     * quadrature sensor connected to the Talon data port.
     * 
     * This is the total number of transitions from high-to-low or
     * low-to-high across both channels per rotation of the sensor. This
     * is also equivalent to the Counts Per Revolution when using 4x
     * decoding.
     * 
     * For example, the SRX Mag Encoder has 4096 edges per rotation, and a
     * US Digital 1024 CPR (Cycles Per Revolution) quadrature encoder has
     * 4096 edges per rotation.
     * 
     * \details On the Talon FXS, this can be at most 2,000,000,000 / Peak
     * RPM.
     * 
     * - Minimum Value: 1
     * - Maximum Value: 1000000
     * - Default Value: 4096
     * - Units: 
     */
    int QuadratureEdgesPerRotation = 4096;
    /**
     * \brief Direction of the quadrature sensor to determine positive
     * rotation. Invert this so that forward motion on the mechanism
     * results in an increase in quadrature position.
     * 
     * - Default Value: False
     */
    bool SensorDirection = false;
    
    /**
     * \brief Modifies this configuration's QuadratureEdgesPerRotation parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The number of quadrature edges in one rotation for the quadrature
     * sensor connected to the Talon data port.
     * 
     * This is the total number of transitions from high-to-low or
     * low-to-high across both channels per rotation of the sensor. This
     * is also equivalent to the Counts Per Revolution when using 4x
     * decoding.
     * 
     * For example, the SRX Mag Encoder has 4096 edges per rotation, and a
     * US Digital 1024 CPR (Cycles Per Revolution) quadrature encoder has
     * 4096 edges per rotation.
     * 
     * \details On the Talon FXS, this can be at most 2,000,000,000 / Peak
     * RPM.
     * 
     * - Minimum Value: 1
     * - Maximum Value: 1000000
     * - Default Value: 4096
     * - Units: 
     *
     * \param newQuadratureEdgesPerRotation Parameter to modify
     * \returns Itself
     */
    constexpr QuadratureConfigs &WithQuadratureEdgesPerRotation(int newQuadratureEdgesPerRotation)
    {
        QuadratureEdgesPerRotation = std::move(newQuadratureEdgesPerRotation);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SensorDirection parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Direction of the quadrature sensor to determine positive rotation.
     * Invert this so that forward motion on the mechanism results in an
     * increase in quadrature position.
     * 
     * - Default Value: False
     *
     * \param newSensorDirection Parameter to modify
     * \returns Itself
     */
    constexpr QuadratureConfigs &WithSensorDirection(bool newSensorDirection)
    {
        SensorDirection = std::move(newSensorDirection);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
