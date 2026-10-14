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
 * \brief Configs that affect the external feedback sensor of this
 *        motor controller.
 * 
 * \details Includes feedback sensor source, offsets and sensor phase
 *          for the feedback sensor, and various ratios to describe
 *          the relationship between the sensor and the mechanism for
 *          closed looping.
 */
class ExternalFeedbackConfigs : public ParentConfiguration {
public:
    constexpr ExternalFeedbackConfigs() = default;

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
     * \brief The offset added to any absolute sensor connected to the
     * Talon data port. This is only supported when using the PulseWidth
     * sensor source.
     * 
     * This can be used to zero the sensor position in applications where
     * the sensor is 1:1 with the mechanism.
     * 
     * - Minimum Value: -1
     * - Maximum Value: 1
     * - Default Value: 0.0
     * - Units: rotations
     */
    units::angle::turn_t AbsoluteSensorOffset = 0.0_tr;
    /**
     * \brief Choose what sensor source is reported via API and used by
     * closed-loop and limit features.  The default is Commutation, which
     * uses the external sensor used for motor commutation.
     * 
     * Choose Remote* to use another sensor on the same CAN bus (this also
     * requires setting FeedbackRemoteSensorID).  Talon will update its
     * position and velocity whenever the remote sensor publishes its
     * information on CAN bus, and the Talon commutation sensor will not
     * be used.
     * 
     * Choose Fused* (requires Phoenix Pro) and Talon will fuse another
     * sensor's information with the commutation sensor, which provides
     * the best possible position and velocity for accuracy and bandwidth
     * (this also requires setting FeedbackRemoteSensorID).  This was
     * developed for applications such as swerve-azimuth.
     * 
     * Choose Sync* (requires Phoenix Pro) and Talon will synchronize its
     * commutation sensor position against another sensor, then continue
     * to use the rotor sensor for closed loop control (this also requires
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
     * Choose Quadrature to use a quadrature encoder directly attached to
     * the Talon data port. This provides velocity and relative position
     * measurements.
     * 
     * Choose PulseWidth to use a pulse-width encoder directly attached to
     * the Talon data port. This provides velocity and absolute position
     * measurements.
     * 
     * \details Note: When the feedback source is changed to Fused* or
     * Sync*, the Talon needs a period of time to fuse before sensor-based
     * (soft-limit, closed loop, etc.) features are used. This period of
     * time is determined by the update frequency of the remote sensor's
     * Position signal.
     * 
     */
    signals::ExternalFeedbackSensorSourceValue ExternalFeedbackSensorSource = signals::ExternalFeedbackSensorSourceValue::Commutation;
    /**
     * \brief The relationship between the motor controlled by a Talon and
     * the external sensor connected to the data port. This does not
     * affect the commutation sensor or remote sensors.
     * 
     * To determine the sensor phase, set this config to Aligned and drive
     * the motor with positive output. If the reported sensor velocity is
     * positive, then the phase is Aligned. If the reported sensor
     * velocity is negative, then the phase is Opposed.
     * 
     * The sensor direction is automatically inverted along with motor
     * invert, so the sensor phase does not need to be changed when motor
     * invert changes.
     * 
     */
    signals::SensorPhaseValue SensorPhase = signals::SensorPhaseValue::Aligned;
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
     * \brief The positive discontinuity point of the absolute sensor in
     * rotations. This determines the point at which the absolute sensor
     * wraps around, keeping the absolute position (after offset) in the
     * range [x-1, x).
     * 
     * - Setting this to 1 makes the absolute position unsigned [0, 1)
     * - Setting this to 0.5 makes the absolute position signed [-0.5,
     * 0.5)
     * - Setting this to 0 makes the absolute position always negative
     * [-1, 0)
     * 
     * Many rotational mechanisms such as arms have a region of motion
     * that is unreachable. This should be set to the center of that
     * region of motion, in non-negative rotations. This affects the
     * position of the device at bootup.
     * 
     * \details For example, consider an arm which can travel from -0.2 to
     * 0.6 rotations with a little leeway, where 0 is horizontally
     * forward. Since -0.2 rotations has the same absolute position as 0.8
     * rotations, we can say that the arm typically does not travel in the
     * range (0.6, 0.8) rotations. As a result, the discontinuity point
     * would be the center of that range, which is 0.7 rotations. This
     * results in an absolute sensor range of [-0.3, 0.7) rotations.
     * 
     * Given a total range of motion less than 1 rotation, users can
     * calculate the discontinuity point using mean(lowerLimit,
     * upperLimit) + 0.5. If that results in a value outside the range [0,
     * 1], either cap the value to [0, 1], or add/subtract 1.0 rotation
     * from your lower and upper limits of motion.
     * 
     * On a Talon motor controller, this is only supported when using the
     * PulseWidth sensor source.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 0.5
     * - Units: rotations
     */
    units::angle::turn_t AbsoluteSensorDiscontinuityPoint = 0.5_tr;
    
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
    constexpr ExternalFeedbackConfigs &WithSensorToMechanismRatio(units::dimensionless::scalar_t newSensorToMechanismRatio)
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
    constexpr ExternalFeedbackConfigs &WithRotorToSensorRatio(units::dimensionless::scalar_t newRotorToSensorRatio)
    {
        RotorToSensorRatio = std::move(newRotorToSensorRatio);
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
    constexpr ExternalFeedbackConfigs &WithFeedbackRemoteSensorID(int newFeedbackRemoteSensorID)
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
    constexpr ExternalFeedbackConfigs &WithVelocityFilterTimeConstant(units::time::second_t newVelocityFilterTimeConstant)
    {
        VelocityFilterTimeConstant = std::move(newVelocityFilterTimeConstant);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's AbsoluteSensorOffset parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The offset added to any absolute sensor connected to the Talon data
     * port. This is only supported when using the PulseWidth sensor
     * source.
     * 
     * This can be used to zero the sensor position in applications where
     * the sensor is 1:1 with the mechanism.
     * 
     * - Minimum Value: -1
     * - Maximum Value: 1
     * - Default Value: 0.0
     * - Units: rotations
     *
     * \param newAbsoluteSensorOffset Parameter to modify
     * \returns Itself
     */
    constexpr ExternalFeedbackConfigs &WithAbsoluteSensorOffset(units::angle::turn_t newAbsoluteSensorOffset)
    {
        AbsoluteSensorOffset = std::move(newAbsoluteSensorOffset);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ExternalFeedbackSensorSource parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Choose what sensor source is reported via API and used by
     * closed-loop and limit features.  The default is Commutation, which
     * uses the external sensor used for motor commutation.
     * 
     * Choose Remote* to use another sensor on the same CAN bus (this also
     * requires setting FeedbackRemoteSensorID).  Talon will update its
     * position and velocity whenever the remote sensor publishes its
     * information on CAN bus, and the Talon commutation sensor will not
     * be used.
     * 
     * Choose Fused* (requires Phoenix Pro) and Talon will fuse another
     * sensor's information with the commutation sensor, which provides
     * the best possible position and velocity for accuracy and bandwidth
     * (this also requires setting FeedbackRemoteSensorID).  This was
     * developed for applications such as swerve-azimuth.
     * 
     * Choose Sync* (requires Phoenix Pro) and Talon will synchronize its
     * commutation sensor position against another sensor, then continue
     * to use the rotor sensor for closed loop control (this also requires
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
     * Choose Quadrature to use a quadrature encoder directly attached to
     * the Talon data port. This provides velocity and relative position
     * measurements.
     * 
     * Choose PulseWidth to use a pulse-width encoder directly attached to
     * the Talon data port. This provides velocity and absolute position
     * measurements.
     * 
     * \details Note: When the feedback source is changed to Fused* or
     * Sync*, the Talon needs a period of time to fuse before sensor-based
     * (soft-limit, closed loop, etc.) features are used. This period of
     * time is determined by the update frequency of the remote sensor's
     * Position signal.
     * 
     *
     * \param newExternalFeedbackSensorSource Parameter to modify
     * \returns Itself
     */
    constexpr ExternalFeedbackConfigs &WithExternalFeedbackSensorSource(signals::ExternalFeedbackSensorSourceValue newExternalFeedbackSensorSource)
    {
        ExternalFeedbackSensorSource = std::move(newExternalFeedbackSensorSource);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SensorPhase parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The relationship between the motor controlled by a Talon and the
     * external sensor connected to the data port. This does not affect
     * the commutation sensor or remote sensors.
     * 
     * To determine the sensor phase, set this config to Aligned and drive
     * the motor with positive output. If the reported sensor velocity is
     * positive, then the phase is Aligned. If the reported sensor
     * velocity is negative, then the phase is Opposed.
     * 
     * The sensor direction is automatically inverted along with motor
     * invert, so the sensor phase does not need to be changed when motor
     * invert changes.
     * 
     *
     * \param newSensorPhase Parameter to modify
     * \returns Itself
     */
    constexpr ExternalFeedbackConfigs &WithSensorPhase(signals::SensorPhaseValue newSensorPhase)
    {
        SensorPhase = std::move(newSensorPhase);
        return *this;
    }
    
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
    constexpr ExternalFeedbackConfigs &WithQuadratureEdgesPerRotation(int newQuadratureEdgesPerRotation)
    {
        QuadratureEdgesPerRotation = std::move(newQuadratureEdgesPerRotation);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's AbsoluteSensorDiscontinuityPoint parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The positive discontinuity point of the absolute sensor in
     * rotations. This determines the point at which the absolute sensor
     * wraps around, keeping the absolute position (after offset) in the
     * range [x-1, x).
     * 
     * - Setting this to 1 makes the absolute position unsigned [0, 1)
     * - Setting this to 0.5 makes the absolute position signed [-0.5,
     * 0.5)
     * - Setting this to 0 makes the absolute position always negative
     * [-1, 0)
     * 
     * Many rotational mechanisms such as arms have a region of motion
     * that is unreachable. This should be set to the center of that
     * region of motion, in non-negative rotations. This affects the
     * position of the device at bootup.
     * 
     * \details For example, consider an arm which can travel from -0.2 to
     * 0.6 rotations with a little leeway, where 0 is horizontally
     * forward. Since -0.2 rotations has the same absolute position as 0.8
     * rotations, we can say that the arm typically does not travel in the
     * range (0.6, 0.8) rotations. As a result, the discontinuity point
     * would be the center of that range, which is 0.7 rotations. This
     * results in an absolute sensor range of [-0.3, 0.7) rotations.
     * 
     * Given a total range of motion less than 1 rotation, users can
     * calculate the discontinuity point using mean(lowerLimit,
     * upperLimit) + 0.5. If that results in a value outside the range [0,
     * 1], either cap the value to [0, 1], or add/subtract 1.0 rotation
     * from your lower and upper limits of motion.
     * 
     * On a Talon motor controller, this is only supported when using the
     * PulseWidth sensor source.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 0.5
     * - Units: rotations
     *
     * \param newAbsoluteSensorDiscontinuityPoint Parameter to modify
     * \returns Itself
     */
    constexpr ExternalFeedbackConfigs &WithAbsoluteSensorDiscontinuityPoint(units::angle::turn_t newAbsoluteSensorDiscontinuityPoint)
    {
        AbsoluteSensorDiscontinuityPoint = std::move(newAbsoluteSensorDiscontinuityPoint);
        return *this;
    }
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANcoder by passing in the CANcoder object.
     *        
     *        When using RemoteCANcoder, the Talon will use another
     *        CANcoder on the same CAN bus. The Talon will update its
     *        position and velocity whenever CANcoder publishes its
     *        information on CAN bus, and the Talon commutation sensor
     *        will not be used.
     * 
     * \param device CANcoder reference to use for RemoteCANcoder
     * \returns Itself
     */
    ExternalFeedbackConfigs &WithRemoteCANcoder(const hardware::core::CoreCANcoder& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        FusedCANcoder by passing in the CANcoder object.
     *        
     *        When using FusedCANcoder (requires Phoenix Pro), the Talon
     *        will fuse another CANcoder's information with the
     *        commutation sensor, which provides the best possible
     *        position and velocity for accuracy and bandwidth.
     *        FusedCANcoder was developed for applications such as
     *        swerve-azimuth.
     * 
     * \param device CANcoder reference to use for FusedCANcoder
     * \returns Itself
     */
    ExternalFeedbackConfigs &WithFusedCANcoder(const hardware::core::CoreCANcoder& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        SyncCANcoder by passing in the CANcoder object.
     *        
     *        When using SyncCANcoder (requires Phoenix Pro), the Talon
     *        will synchronize its commutation sensor position against
     *        another CANcoder, then continue to use the rotor sensor for
     *        closed loop control. The Talon will report if its internal
     *        position differs significantly from the reported CANcoder
     *        position. SyncCANcoder was developed for mechanisms where
     *        there is a risk of the CANcoder failing in such a way that
     *        it reports a position that does not match the mechanism,
     *        such as the sensor mounting assembly breaking off.
     * 
     * \param device CANcoder reference to use for SyncCANcoder
     * \returns Itself
     */
    ExternalFeedbackConfigs &WithSyncCANcoder(const hardware::core::CoreCANcoder& device);
    
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
    ExternalFeedbackConfigs &WithRemotePigeon2Yaw(const hardware::core::CorePigeon2& device);
    
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
    ExternalFeedbackConfigs &WithRemotePigeon2Pitch(const hardware::core::CorePigeon2& device);
    
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
    ExternalFeedbackConfigs &WithRemotePigeon2Roll(const hardware::core::CorePigeon2& device);
    
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
    ExternalFeedbackConfigs &WithRemoteCANdiPWM1(const hardware::core::CoreCANdi& device);
    
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
    ExternalFeedbackConfigs &WithRemoteCANdiPWM2(const hardware::core::CoreCANdi& device);
    
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
    ExternalFeedbackConfigs &WithRemoteCANdiQuadrature(const hardware::core::CoreCANdi& device);
    
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
    ExternalFeedbackConfigs &WithFusedCANdiPWM1(const hardware::core::CoreCANdi& device);
    
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
    ExternalFeedbackConfigs &WithFusedCANdiPWM2(const hardware::core::CoreCANdi& device);
    
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
    ExternalFeedbackConfigs &WithFusedCANdiQuadrature(const hardware::core::CoreCANdi& device);
    
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
    ExternalFeedbackConfigs &WithSyncCANdiPWM1(const hardware::core::CoreCANdi& device);
    
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
    ExternalFeedbackConfigs &WithSyncCANdiPWM2(const hardware::core::CoreCANdi& device);
    
    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
