/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include <units/dimensionless.h>

namespace ctre {
namespace phoenix6 {


namespace configs {

/**
 * \brief Configs related to sensors used for differential control of
 *        a mechanism.
 * 
 * \details Includes the differential sensor sources and IDs.
 */
class DifferentialSensorsConfigs : public ParentConfiguration {
public:
    constexpr DifferentialSensorsConfigs() = default;

    /**
     * \brief Choose what sensor source is used for differential control
     * of a mechanism.  The default is Disabled.  All other options
     * require setting the DifferentialTalonFXSensorID, as the average of
     * this Talon FX's sensor and the remote TalonFX's sensor is used for
     * the differential controller's primary targets.
     * 
     * Choose RemoteTalonFX_HalfDiff to use another TalonFX on the same
     * CAN bus.  Talon FX will update its differential position and
     * velocity whenever the remote TalonFX publishes its information on
     * CAN bus.  The differential controller will use half of the
     * difference between this TalonFX's sensor and the remote Talon FX's
     * sensor for the differential component of the output.
     * 
     * Choose RemotePigeon2Yaw, RemotePigeon2Pitch, and RemotePigeon2Roll
     * to use another Pigeon2 on the same CAN bus (this also requires
     * setting DifferentialRemoteSensorID).  Talon FX will update its
     * differential position to match the selected value whenever Pigeon2
     * publishes its information on CAN bus. Note that the Talon FX
     * differential position will be in rotations and not degrees.
     * 
     * Choose RemoteCANcoder to use another CANcoder on the same CAN bus
     * (this also requires setting DifferentialRemoteSensorID).  Talon FX
     * will update its differential position and velocity to match the
     * CANcoder whenever CANcoder publishes its information on CAN bus.
     * 
     */
    signals::DifferentialSensorSourceValue DifferentialSensorSource = signals::DifferentialSensorSourceValue::Disabled;
    /**
     * \brief Device ID of which remote Talon FX to use.  This is used
     * whenever the Differential Sensor Source is not disabled.
     * 
     * The differential Talon FX must enable its Position and Velocity
     * status signals. The update rate of the status signals determines
     * the update rate of differential control.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 62
     * - Default Value: 0
     * - Units: 
     */
    int DifferentialTalonFXSensorID = 0;
    /**
     * \brief Device ID of which remote sensor to use on the differential
     * axis.  This is used when the Differential Sensor Source is not
     * Disabled or RemoteTalonFX_HalfDiff.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 62
     * - Default Value: 0
     * - Units: 
     */
    int DifferentialRemoteSensorID = 0;
    /**
     * \brief The ratio of sensor rotations to the differential
     * mechanism's difference output, where a ratio greater than 1 is a
     * reduction.
     * 
     * When using RemoteTalonFX_HalfDiff, the sensor is considered half of
     * the difference between the two devices' mechanism
     * positions/velocities. As a result, this should be set to the gear
     * ratio on the difference axis when using RemoteTalonFX_HalfDiff, or
     * any gear ratio between the sensor and the mechanism differential
     * when using another sensor source.
     * 
     * We recommend against using this config to perform onboard unit
     * conversions.  Instead, unit conversions should be performed in
     * robot code using the units library.
     * 
     * If this is set to zero, the device will reset back to one.
     * 
     * - Minimum Value: -1000
     * - Maximum Value: 1000
     * - Default Value: 1.0
     * - Units: scalar
     */
    units::dimensionless::scalar_t SensorToDifferentialRatio = 1.0;
    
    /**
     * \brief Modifies this configuration's DifferentialSensorSource parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Choose what sensor source is used for differential control of a
     * mechanism.  The default is Disabled.  All other options require
     * setting the DifferentialTalonFXSensorID, as the average of this
     * Talon FX's sensor and the remote TalonFX's sensor is used for the
     * differential controller's primary targets.
     * 
     * Choose RemoteTalonFX_HalfDiff to use another TalonFX on the same
     * CAN bus.  Talon FX will update its differential position and
     * velocity whenever the remote TalonFX publishes its information on
     * CAN bus.  The differential controller will use half of the
     * difference between this TalonFX's sensor and the remote Talon FX's
     * sensor for the differential component of the output.
     * 
     * Choose RemotePigeon2Yaw, RemotePigeon2Pitch, and RemotePigeon2Roll
     * to use another Pigeon2 on the same CAN bus (this also requires
     * setting DifferentialRemoteSensorID).  Talon FX will update its
     * differential position to match the selected value whenever Pigeon2
     * publishes its information on CAN bus. Note that the Talon FX
     * differential position will be in rotations and not degrees.
     * 
     * Choose RemoteCANcoder to use another CANcoder on the same CAN bus
     * (this also requires setting DifferentialRemoteSensorID).  Talon FX
     * will update its differential position and velocity to match the
     * CANcoder whenever CANcoder publishes its information on CAN bus.
     * 
     *
     * \param newDifferentialSensorSource Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialSensorsConfigs &WithDifferentialSensorSource(signals::DifferentialSensorSourceValue newDifferentialSensorSource)
    {
        DifferentialSensorSource = std::move(newDifferentialSensorSource);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DifferentialTalonFXSensorID parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Device ID of which remote Talon FX to use.  This is used whenever
     * the Differential Sensor Source is not disabled.
     * 
     * The differential Talon FX must enable its Position and Velocity
     * status signals. The update rate of the status signals determines
     * the update rate of differential control.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 62
     * - Default Value: 0
     * - Units: 
     *
     * \param newDifferentialTalonFXSensorID Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialSensorsConfigs &WithDifferentialTalonFXSensorID(int newDifferentialTalonFXSensorID)
    {
        DifferentialTalonFXSensorID = std::move(newDifferentialTalonFXSensorID);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DifferentialRemoteSensorID parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Device ID of which remote sensor to use on the differential axis. 
     * This is used when the Differential Sensor Source is not Disabled or
     * RemoteTalonFX_HalfDiff.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 62
     * - Default Value: 0
     * - Units: 
     *
     * \param newDifferentialRemoteSensorID Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialSensorsConfigs &WithDifferentialRemoteSensorID(int newDifferentialRemoteSensorID)
    {
        DifferentialRemoteSensorID = std::move(newDifferentialRemoteSensorID);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SensorToDifferentialRatio parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The ratio of sensor rotations to the differential mechanism's
     * difference output, where a ratio greater than 1 is a reduction.
     * 
     * When using RemoteTalonFX_HalfDiff, the sensor is considered half of
     * the difference between the two devices' mechanism
     * positions/velocities. As a result, this should be set to the gear
     * ratio on the difference axis when using RemoteTalonFX_HalfDiff, or
     * any gear ratio between the sensor and the mechanism differential
     * when using another sensor source.
     * 
     * We recommend against using this config to perform onboard unit
     * conversions.  Instead, unit conversions should be performed in
     * robot code using the units library.
     * 
     * If this is set to zero, the device will reset back to one.
     * 
     * - Minimum Value: -1000
     * - Maximum Value: 1000
     * - Default Value: 1.0
     * - Units: scalar
     *
     * \param newSensorToDifferentialRatio Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialSensorsConfigs &WithSensorToDifferentialRatio(units::dimensionless::scalar_t newSensorToDifferentialRatio)
    {
        SensorToDifferentialRatio = std::move(newSensorToDifferentialRatio);
        return *this;
    }

    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
