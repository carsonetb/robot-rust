/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include <units/angle.h>
#include <units/dimensionless.h>
#include <units/time.h>

namespace ctre {
namespace phoenix6 {
namespace hardware::core { class CoreCANcoder; }
namespace hardware::core { class CoreCANdi; }
namespace hardware::core { class CorePigeon2; }

namespace configs {

/**
 * \brief Configs that affect the feedback of this motor controller.
 * 
 * \details Includes feedback sensor source, any offsets for the
 *          feedback sensor, and various ratios to describe the
 *          relationship between the sensor and the mechanism for
 *          closed looping.
 */
class FeedbackConfigs : public ParentConfiguration {
public:
    constexpr FeedbackConfigs() = default;

    /**
     * \brief The offset added to the absolute integrated rotor sensor. 
     * This can be used to zero the rotor in applications that are within
     * one rotor rotation.
     * 
     * - Minimum Value: -1
     * - Maximum Value: 1
     * - Default Value: 0.0
     * - Units: rotations
     */
    units::angle::turn_t FeedbackRotorOffset = 0.0_tr;
    /**
     * \brief The ratio of sensor rotations to the mechanism's output,
     * where a ratio greater than 1 is a reduction.
     * 
     * This is equivalent to the mechanism's gear ratio if the sensor is
     * located on the input of a gearbox.  If sensor is on the output of a
     * gearbox, then this is typically set to 1.
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
    units::dimensionless::scalar_t SensorToMechanismRatio = 1.0;
    /**
     * \brief The ratio of motor rotor rotations to remote sensor
     * rotations, where a ratio greater than 1 is a reduction.
     * 
     * The Talon FX is capable of fusing a remote CANcoder with its rotor
     * sensor to produce a high-bandwidth sensor source.  This feature
     * requires specifying the ratio between the motor rotor and the
     * remote sensor.
     * 
     * If this is set to zero, the device will reset back to one.
     * 
     * - Minimum Value: -1000
     * - Maximum Value: 1000
     * - Default Value: 1.0
     * - Units: scalar
     */
    units::dimensionless::scalar_t RotorToSensorRatio = 1.0;
    /**
     * \brief Choose what sensor source is reported via API and used by
     * closed-loop and limit features.  The default is RotorSensor, which
     * uses the internal rotor sensor in the Talon.
     * 
     * Choose Remote* to use another sensor on the same CAN bus (this also
     * requires setting FeedbackRemoteSensorID).  Talon will update its
     * position and velocity whenever the remote sensor publishes its
     * information on CAN bus, and the Talon internal rotor will not be
     * used.
     * 
     * Choose Fused* (requires Phoenix Pro) and Talon will fuse another
     * sensor's information with the internal rotor, which provides the
     * best possible position and velocity for accuracy and bandwidth
     * (this also requires setting FeedbackRemoteSensorID).  This was
     * developed for applications such as swerve-azimuth.
     * 
     * Choose Sync* (requires Phoenix Pro) and Talon will synchronize its
     * internal rotor position against another sensor, then continue to
     * use the rotor sensor for closed loop control (this also requires
     * setting FeedbackRemoteSensorID).  The Talon will report if its
     * internal position differs significantly from the reported remote
     * sensor position.  This was developed for mechanisms where there is
     * a risk of the sensor failing in such a way that it reports a
     * position that does not match the mechanism, such as the sensor
     * mounting assembly breaking off.
     * 
     * Choose RemotePigeon2Yaw, RemotePigeon2Pitch, and RemotePigeon2Roll
     * to use another Pigeon2 on the same CAN bus (this also requires
     * setting FeedbackRemoteSensorID).  Talon will update its position to
     * match the selected value whenever Pigeon2 publishes its information
     * on CAN bus. Note that the Talon position will be in rotations and
     * not degrees.
     * 
     * \details Note: When the feedback source is changed to Fused* or
     * Sync*, the Talon needs a period of time to fuse before sensor-based
     * (soft-limit, closed loop, etc.) features are used. This period of
     * time is determined by the update frequency of the remote sensor's
     * Position signal.
     * 
     */
    signals::FeedbackSensorSourceValue FeedbackSensorSource = signals::FeedbackSensorSourceValue::RotorSensor;
    /**
     * \brief Device ID of which remote device to use.  This is not used
     * if the Sensor Source is the internal rotor sensor.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 62
     * - Default Value: 0
     * - Units: 
     */
    int FeedbackRemoteSensorID = 0;
    /**
     * \brief The configurable time constant of the Kalman velocity
     * filter. The velocity Kalman filter will adjust to act as a low-pass
     * with this value as its time constant.
     * 
     * \details If the user is aiming for an expected cutoff frequency,
     * the frequency is calculated as 1 / (2 * π * τ) with τ being the
     * time constant.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t VelocityFilterTimeConstant = 0_s;
    
    /**
     * \brief Modifies this configuration's FeedbackRotorOffset parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The offset added to the absolute integrated rotor sensor.  This can
     * be used to zero the rotor in applications that are within one rotor
     * rotation.
     * 
     * - Minimum Value: -1
     * - Maximum Value: 1
     * - Default Value: 0.0
     * - Units: rotations
     *
     * \param newFeedbackRotorOffset Parameter to modify
     * \returns Itself
     */
    constexpr FeedbackConfigs &WithFeedbackRotorOffset(units::angle::turn_t newFeedbackRotorOffset)
    {
        FeedbackRotorOffset = std::move(newFeedbackRotorOffset);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SensorToMechanismRatio parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The ratio of sensor rotations to the mechanism's output, where a
     * ratio greater than 1 is a reduction.
     * 
     * This is equivalent to the mechanism's gear ratio if the sensor is
     * located on the input of a gearbox.  If sensor is on the output of a
     * gearbox, then this is typically set to 1.
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
     * \param newSensorToMechanismRatio Parameter to modify
     * \returns Itself
     */
    constexpr FeedbackConfigs &WithSensorToMechanismRatio(units::dimensionless::scalar_t newSensorToMechanismRatio)
    {
        SensorToMechanismRatio = std::move(newSensorToMechanismRatio);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's RotorToSensorRatio parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The ratio of motor rotor rotations to remote sensor rotations,
     * where a ratio greater than 1 is a reduction.
     * 
     * The Talon FX is capable of fusing a remote CANcoder with its rotor
     * sensor to produce a high-bandwidth sensor source.  This feature
     * requires specifying the ratio between the motor rotor and the
     * remote sensor.
     * 
     * If this is set to zero, the device will reset back to one.
     * 
     * - Minimum Value: -1000
     * - Maximum Value: 1000
     * - Default Value: 1.0
     * - Units: scalar
     *
     * \param newRotorToSensorRatio Parameter to modify
     * \returns Itself
     */
    constexpr FeedbackConfigs &WithRotorToSensorRatio(units::dimensionless::scalar_t newRotorToSensorRatio)
    {
        RotorToSensorRatio = std::move(newRotorToSensorRatio);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's FeedbackSensorSource parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Choose what sensor source is reported via API and used by
     * closed-loop and limit features.  The default is RotorSensor, which
     * uses the internal rotor sensor in the Talon.
     * 
     * Choose Remote* to use another sensor on the same CAN bus (this also
     * requires setting FeedbackRemoteSensorID).  Talon will update its
     * position and velocity whenever the remote sensor publishes its
     * information on CAN bus, and the Talon internal rotor will not be
     * used.
     * 
     * Choose Fused* (requires Phoenix Pro) and Talon will fuse another
     * sensor's information with the internal rotor, which provides the
     * best possible position and velocity for accuracy and bandwidth
     * (this also requires setting FeedbackRemoteSensorID).  This was
     * developed for applications such as swerve-azimuth.
     * 
     * Choose Sync* (requires Phoenix Pro) and Talon will synchronize its
     * internal rotor position against another sensor, then continue to
     * use the rotor sensor for closed loop control (this also requires
     * setting FeedbackRemoteSensorID).  The Talon will report if its
     * internal position differs significantly from the reported remote
     * sensor position.  This was developed for mechanisms where there is
     * a risk of the sensor failing in such a way that it reports a
     * position that does not match the mechanism, such as the sensor
     * mounting assembly breaking off.
     * 
     * Choose RemotePigeon2Yaw, RemotePigeon2Pitch, and RemotePigeon2Roll
     * to use another Pigeon2 on the same CAN bus (this also requires
     * setting FeedbackRemoteSensorID).  Talon will update its position to
     * match the selected value whenever Pigeon2 publishes its information
     * on CAN bus. Note that the Talon position will be in rotations and
     * not degrees.
     * 
     * \details Note: When the feedback source is changed to Fused* or
     * Sync*, the Talon needs a period of time to fuse before sensor-based
     * (soft-limit, closed loop, etc.) features are used. This period of
     * time is determined by the update frequency of the remote sensor's
     * Position signal.
     * 
     *
     * \param newFeedbackSensorSource Parameter to modify
     * \returns Itself
     */
    constexpr FeedbackConfigs &WithFeedbackSensorSource(signals::FeedbackSensorSourceValue newFeedbackSensorSource)
    {
        FeedbackSensorSource = std::move(newFeedbackSensorSource);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's FeedbackRemoteSensorID parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Device ID of which remote device to use.  This is not used if the
     * Sensor Source is the internal rotor sensor.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 62
     * - Default Value: 0
     * - Units: 
     *
     * \param newFeedbackRemoteSensorID Parameter to modify
     * \returns Itself
     */
    constexpr FeedbackConfigs &WithFeedbackRemoteSensorID(int newFeedbackRemoteSensorID)
    {
        FeedbackRemoteSensorID = std::move(newFeedbackRemoteSensorID);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's VelocityFilterTimeConstant parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The configurable time constant of the Kalman velocity filter. The
     * velocity Kalman filter will adjust to act as a low-pass with this
     * value as its time constant.
     * 
     * \details If the user is aiming for an expected cutoff frequency,
     * the frequency is calculated as 1 / (2 * π * τ) with τ being the
     * time constant.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newVelocityFilterTimeConstant Parameter to modify
     * \returns Itself
     */
    constexpr FeedbackConfigs &WithVelocityFilterTimeConstant(units::time::second_t newVelocityFilterTimeConstant)
    {
        VelocityFilterTimeConstant = std::move(newVelocityFilterTimeConstant);
        return *this;
    }
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANcoder by passing in the CANcoder object.
     *        
     *        When using RemoteCANcoder, the Talon will use another
     *        CANcoder on the same CAN bus. The Talon will update its
     *        position and velocity whenever CANcoder publishes its
     *        information on CAN bus, and the Talon internal rotor will
     *        not be used.
     * 
     * \param device CANcoder reference to use for RemoteCANcoder
     * \returns Itself
     */
    FeedbackConfigs &WithRemoteCANcoder(const hardware::core::CoreCANcoder& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        FusedCANcoder by passing in the CANcoder object.
     *        
     *        When using FusedCANcoder (requires Phoenix Pro), the Talon
     *        will fuse another CANcoder's information with the internal
     *        rotor, which provides the best possible position and
     *        velocity for accuracy and bandwidth. FusedCANcoder was
     *        developed for applications such as swerve-azimuth.
     * 
     * \param device CANcoder reference to use for FusedCANcoder
     * \returns Itself
     */
    FeedbackConfigs &WithFusedCANcoder(const hardware::core::CoreCANcoder& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        SyncCANcoder by passing in the CANcoder object.
     *        
     *        When using SyncCANcoder (requires Phoenix Pro), the Talon
     *        will synchronize its internal rotor position against another
     *        CANcoder, then continue to use the rotor sensor for closed
     *        loop control. The Talon will report if its internal position
     *        differs significantly from the reported CANcoder position.
     *        SyncCANcoder was developed for mechanisms where there is a
     *        risk of the CANcoder failing in such a way that it reports a
     *        position that does not match the mechanism, such as the
     *        sensor mounting assembly breaking off.
     * 
     * \param device CANcoder reference to use for SyncCANcoder
     * \returns Itself
     */
    FeedbackConfigs &WithSyncCANcoder(const hardware::core::CoreCANcoder& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemotePigeon2Yaw by passing in the Pigeon2 object.
     *        
     *        When using RemotePigeon2Yaw, the Talon will use another
     *        Pigeon2 on the same CAN bus. The Talon will update its
     *        position to match the Pigeon2 yaw whenever Pigeon2 publishes
     *        its information on CAN bus. Note that the Talon position
     *        will be in rotations and not degrees.
     * 
     * \param device Pigeon2 reference to use for RemotePigeon2Yaw
     * \returns Itself
     */
    FeedbackConfigs &WithRemotePigeon2Yaw(const hardware::core::CorePigeon2& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemotePigeon2Pitch by passing in the Pigeon2 object.
     *        
     *        When using RemotePigeon2Pitch, the Talon will use another
     *        Pigeon2 on the same CAN bus. The Talon will update its
     *        position to match the Pigeon2 pitch whenever Pigeon2
     *        publishes its information on CAN bus. Note that the Talon
     *        position will be in rotations and not degrees.
     * 
     * \param device Pigeon2 reference to use for RemotePigeon2Pitch
     * \returns Itself
     */
    FeedbackConfigs &WithRemotePigeon2Pitch(const hardware::core::CorePigeon2& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemotePigeon2Roll by passing in the Pigeon2 object.
     *        
     *        When using RemotePigeon2Roll, the Talon will use another
     *        Pigeon2 on the same CAN bus. The Talon will update its
     *        position to match the Pigeon2 roll whenever Pigeon2
     *        publishes its information on CAN bus. Note that the Talon
     *        position will be in rotations and not degrees.
     * 
     * \param device Pigeon2 reference to use for RemotePigeon2Roll
     * \returns Itself
     */
    FeedbackConfigs &WithRemotePigeon2Roll(const hardware::core::CorePigeon2& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANdi PWM 1 by passing in the CANdi object.
     *        
     *        When using RemoteCANdi, the Talon will use another CTR
     *        Electronics' CANdi™ on the same CAN bus. The Talon will
     *        update its position and velocity whenever the CTR
     *        Electronics' CANdi™ publishes its information on CAN bus,
     *        and the Talon commutation sensor will not be used.
     * 
     * \param device CANdi reference to use for RemoteCANdi
     * \returns Itself
     */
    FeedbackConfigs &WithRemoteCANdiPWM1(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANdi PWM 2 by passing in the CANdi object.
     *        
     *        When using RemoteCANdi, the Talon will use another CTR
     *        Electronics' CANdi™ on the same CAN bus. The Talon will
     *        update its position and velocity whenever the CTR
     *        Electronics' CANdi™ publishes its information on CAN bus,
     *        and the Talon commutation sensor will not be used.
     * 
     * \param device CANdi reference to use for RemoteCANdi
     * \returns Itself
     */
    FeedbackConfigs &WithRemoteCANdiPWM2(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANdi Quadrature by passing in the CANdi object.
     *        
     *        When using RemoteCANdi, the Talon will use another CTR
     *        Electronics' CANdi™ on the same CAN bus. The Talon will
     *        update its position and velocity whenever the CTR
     *        Electronics' CANdi™ publishes its information on CAN bus,
     *        and the Talon commutation sensor will not be used.
     * 
     * \param device CANdi reference to use for RemoteCANdi
     * \returns Itself
     */
    FeedbackConfigs &WithRemoteCANdiQuadrature(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        FusedCANdi PWM 1 by passing in the CANdi object.
     *        
     *        When using FusedCANdi (requires Phoenix Pro), the Talon will
     *        fuse another CANdi™ branded device's information with the
     *        internal rotor, which provides the best possible position
     *        and velocity for accuracy and bandwidth.
     * 
     * \param device CANdi reference to use for FusedCANdi
     * \returns Itself
     */
    FeedbackConfigs &WithFusedCANdiPWM1(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        FusedCANdi PWM 2 by passing in the CANdi object.
     *        
     *        When using FusedCANdi (requires Phoenix Pro), the Talon will
     *        fuse another CANdi™ branded device's information with the
     *        internal rotor, which provides the best possible position
     *        and velocity for accuracy and bandwidth.
     * 
     * \param device CANdi reference to use for FusedCANdi
     * \returns Itself
     */
    FeedbackConfigs &WithFusedCANdiPWM2(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        FusedCANdi Quadrature by passing in the CANdi object.
     *        
     *        When using FusedCANdi (requires Phoenix Pro), the Talon will
     *        fuse another CANdi™ branded device's information with the
     *        internal rotor, which provides the best possible position
     *        and velocity for accuracy and bandwidth.
     * 
     * \param device CANdi reference to use for FusedCANdi
     * \returns Itself
     */
    FeedbackConfigs &WithFusedCANdiQuadrature(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        SyncCANdi PWM 1 by passing in the CANdi object.
     *        
     *        When using SyncCANdi (requires Phoenix Pro), the Talon will
     *        synchronize its internal rotor position against another
     *        CANdi™ branded device, then continue to use the rotor sensor
     *        for closed loop control. The Talon will report if its
     *        internal position differs significantly from the reported
     *        CANdi™ branded device's position. SyncCANdi was developed
     *        for mechanisms where there is a risk of the CANdi™ branded
     *        device failing in such a way that it reports a position that
     *        does not match the mechanism, such as the sensor mounting
     *        assembly breaking off.
     * 
     * \param device CANdi reference to use for SyncCANdi
     * \returns Itself
     */
    FeedbackConfigs &WithSyncCANdiPWM1(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        SyncCANdi PWM 2 by passing in the CANdi object.
     *        
     *        When using SyncCANdi (requires Phoenix Pro), the Talon will
     *        synchronize its internal rotor position against another
     *        CANdi™ branded device, then continue to use the rotor sensor
     *        for closed loop control. The Talon will report if its
     *        internal position differs significantly from the reported
     *        CANdi™ branded device's position. SyncCANdi was developed
     *        for mechanisms where there is a risk of the CANdi™ branded
     *        device failing in such a way that it reports a position that
     *        does not match the mechanism, such as the sensor mounting
     *        assembly breaking off.
     * 
     * \param device CANdi reference to use for SyncCANdi
     * \returns Itself
     */
    FeedbackConfigs &WithSyncCANdiPWM2(const hardware::core::CoreCANdi& device);
    
    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
