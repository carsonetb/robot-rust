/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix6/Serializable.hpp"
#include "ctre/phoenix6/networking/interfaces/ConfigSerializer.h"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include "ctre/phoenix6/spns/SpnValue.hpp"
#include "ctre/unit/pid_ff.h"
#include <units/angle.h>
#include <units/angular_acceleration.h>
#include <units/angular_jerk.h>
#include <units/angular_velocity.h>
#include <units/current.h>
#include <units/dimensionless.h>
#include <units/frequency.h>
#include <units/length.h>
#include <units/voltage.h>
#include <sstream>
#include <map>
#include <string>

namespace ctre {
namespace phoenix6 {

namespace hardware { namespace core { class CoreCANcoder; } }
namespace hardware { namespace core { class CoreCANdi; } }
namespace hardware { namespace core { class CoreTalonFX; } }
namespace hardware { namespace core { class CoreCANrange; } }
namespace configs { class SlotConfigs; }

namespace configs {

class ParentConfiguration : public ISerializable
{
public:
    virtual std::string ToString() const = 0;
    friend std::ostream &operator<<(std::ostream &str, const ParentConfiguration &v)
    {
        str << v.ToString();
        return str;
    }
    virtual ctre::phoenix::StatusCode Deserialize(const std::string &string) = 0;
};


/**
 * \brief Configs that affect the magnet sensor and how to interpret
 *        it.
 * 
 * \details Includes sensor direction, the sensor discontinuity point,
 *          and the magnet offset.
 */
class MagnetSensorConfigs : public ParentConfiguration
{
public:
    constexpr MagnetSensorConfigs() = default;

    /**
     * \brief Direction of the sensor to determine positive rotation, as
     * seen facing the LED side of the CANcoder.
     * 
     */
    signals::SensorDirectionValue SensorDirection = signals::SensorDirectionValue::CounterClockwise_Positive;
    /**
     * \brief This offset is added to the reported position, allowing the
     * application to trim the zero position.  When set to the default
     * value of zero, position reports zero when magnet north pole aligns
     * with the LED.
     * 
     * - Minimum Value: -1
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: rotations
     */
    units::angle::turn_t MagnetOffset = 0_tr;
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
     * \brief Modifies this configuration's SensorDirection parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Direction of the sensor to determine positive rotation, as seen
     * facing the LED side of the CANcoder.
     * 
     *
     * \param newSensorDirection Parameter to modify
     * \returns Itself
     */
    constexpr MagnetSensorConfigs &WithSensorDirection(signals::SensorDirectionValue newSensorDirection)
    {
        SensorDirection = std::move(newSensorDirection);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MagnetOffset parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This offset is added to the reported position, allowing the
     * application to trim the zero position.  When set to the default
     * value of zero, position reports zero when magnet north pole aligns
     * with the LED.
     * 
     * - Minimum Value: -1
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: rotations
     *
     * \param newMagnetOffset Parameter to modify
     * \returns Itself
     */
    constexpr MagnetSensorConfigs &WithMagnetOffset(units::angle::turn_t newMagnetOffset)
    {
        MagnetOffset = std::move(newMagnetOffset);
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
    constexpr MagnetSensorConfigs &WithAbsoluteSensorDiscontinuityPoint(units::angle::turn_t newAbsoluteSensorDiscontinuityPoint)
    {
        AbsoluteSensorDiscontinuityPoint = std::move(newAbsoluteSensorDiscontinuityPoint);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: MagnetSensor" << std::endl;
        ss << "    SensorDirection: " << SensorDirection << std::endl;
        ss << "    MagnetOffset: " << MagnetOffset.to<double>() << " rotations" << std::endl;
        ss << "    AbsoluteSensorDiscontinuityPoint: " << AbsoluteSensorDiscontinuityPoint.to<double>() << " rotations" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::CANcoder_SensorDirection, SensorDirection.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::CANCoder_MagnetOffset, MagnetOffset.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_AbsoluteSensorDiscontinuityPoint, AbsoluteSensorDiscontinuityPoint.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::CANcoder_SensorDirection, string_c_str, string_length, &SensorDirection.value);
        double MagnetOffsetVal = MagnetOffset.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::CANCoder_MagnetOffset, string_c_str, string_length, &MagnetOffsetVal);
        MagnetOffset = units::angle::turn_t{MagnetOffsetVal};
        double AbsoluteSensorDiscontinuityPointVal = AbsoluteSensorDiscontinuityPoint.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_AbsoluteSensorDiscontinuityPoint, string_c_str, string_length, &AbsoluteSensorDiscontinuityPointVal);
        AbsoluteSensorDiscontinuityPoint = units::angle::turn_t{AbsoluteSensorDiscontinuityPointVal};
        return 0;
    }
};


/**
 * \brief Configs for Pigeon 2's Mount Pose configuration.
 * 
 * \details These configs allow the Pigeon2 to be mounted in whatever
 *          orientation that's desired and ensure the reported
 *          Yaw/Pitch/Roll is from the robot's reference.
 */
class MountPoseConfigs : public ParentConfiguration
{
public:
    constexpr MountPoseConfigs() = default;

    /**
     * \brief The mounting calibration yaw-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     */
    units::angle::degree_t MountPoseYaw = 0_deg;
    /**
     * \brief The mounting calibration pitch-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     */
    units::angle::degree_t MountPosePitch = 0_deg;
    /**
     * \brief The mounting calibration roll-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     */
    units::angle::degree_t MountPoseRoll = 0_deg;
    
    /**
     * \brief Modifies this configuration's MountPoseYaw parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The mounting calibration yaw-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     *
     * \param newMountPoseYaw Parameter to modify
     * \returns Itself
     */
    constexpr MountPoseConfigs &WithMountPoseYaw(units::angle::degree_t newMountPoseYaw)
    {
        MountPoseYaw = std::move(newMountPoseYaw);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MountPosePitch parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The mounting calibration pitch-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     *
     * \param newMountPosePitch Parameter to modify
     * \returns Itself
     */
    constexpr MountPoseConfigs &WithMountPosePitch(units::angle::degree_t newMountPosePitch)
    {
        MountPosePitch = std::move(newMountPosePitch);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MountPoseRoll parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The mounting calibration roll-component.
     * 
     * - Minimum Value: -360
     * - Maximum Value: 360
     * - Default Value: 0
     * - Units: deg
     *
     * \param newMountPoseRoll Parameter to modify
     * \returns Itself
     */
    constexpr MountPoseConfigs &WithMountPoseRoll(units::angle::degree_t newMountPoseRoll)
    {
        MountPoseRoll = std::move(newMountPoseRoll);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: MountPose" << std::endl;
        ss << "    MountPoseYaw: " << MountPoseYaw.to<double>() << " deg" << std::endl;
        ss << "    MountPosePitch: " << MountPosePitch.to<double>() << " deg" << std::endl;
        ss << "    MountPoseRoll: " << MountPoseRoll.to<double>() << " deg" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2MountPoseYaw, MountPoseYaw.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2MountPosePitch, MountPosePitch.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2MountPoseRoll, MountPoseRoll.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double MountPoseYawVal = MountPoseYaw.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2MountPoseYaw, string_c_str, string_length, &MountPoseYawVal);
        MountPoseYaw = units::angle::degree_t{MountPoseYawVal};
        double MountPosePitchVal = MountPosePitch.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2MountPosePitch, string_c_str, string_length, &MountPosePitchVal);
        MountPosePitch = units::angle::degree_t{MountPosePitchVal};
        double MountPoseRollVal = MountPoseRoll.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2MountPoseRoll, string_c_str, string_length, &MountPoseRollVal);
        MountPoseRoll = units::angle::degree_t{MountPoseRollVal};
        return 0;
    }
};


/**
 * \brief Configs to trim the Pigeon2's gyroscope.
 * 
 * \details Pigeon2 allows the user to trim the gyroscope's
 *          sensitivity. While this isn't necessary for the Pigeon2,
 *          as it comes calibrated out-of-the-box, users can make use
 *          of this to make the Pigeon2 even more accurate for their
 *          application.
 */
class GyroTrimConfigs : public ParentConfiguration
{
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

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: GyroTrim" << std::endl;
        ss << "    GyroScalarX: " << GyroScalarX.to<double>() << " deg per rotation" << std::endl;
        ss << "    GyroScalarY: " << GyroScalarY.to<double>() << " deg per rotation" << std::endl;
        ss << "    GyroScalarZ: " << GyroScalarZ.to<double>() << " deg per rotation" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2GyroScalarX, GyroScalarX.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2GyroScalarY, GyroScalarY.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2GyroScalarZ, GyroScalarZ.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double GyroScalarXVal = GyroScalarX.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2GyroScalarX, string_c_str, string_length, &GyroScalarXVal);
        GyroScalarX = units::dimensionless::scalar_t{GyroScalarXVal};
        double GyroScalarYVal = GyroScalarY.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2GyroScalarY, string_c_str, string_length, &GyroScalarYVal);
        GyroScalarY = units::dimensionless::scalar_t{GyroScalarYVal};
        double GyroScalarZVal = GyroScalarZ.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2GyroScalarZ, string_c_str, string_length, &GyroScalarZVal);
        GyroScalarZ = units::dimensionless::scalar_t{GyroScalarZVal};
        return 0;
    }
};


/**
 * \brief Configs to enable/disable various features of the Pigeon2.
 * 
 * \details These configs allow the user to enable or disable various
 *          aspects of the Pigeon2.
 */
class Pigeon2FeaturesConfigs : public ParentConfiguration
{
public:
    constexpr Pigeon2FeaturesConfigs() = default;

    /**
     * \brief Turns on or off the magnetometer fusing for 9-axis. FRC
     * users are not recommended to turn this on, as the magnetic
     * influence of the robot will likely negatively affect the
     * performance of the Pigeon2.
     * 
     * - Default Value: False
     */
    bool EnableCompass = false;
    /**
     * \brief Disables using the temperature compensation feature.
     * 
     * - Default Value: False
     */
    bool DisableTemperatureCompensation = false;
    /**
     * \brief Disables using the no-motion calibration feature.
     * 
     * - Default Value: False
     */
    bool DisableNoMotionCalibration = false;
    
    /**
     * \brief Modifies this configuration's EnableCompass parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Turns on or off the magnetometer fusing for 9-axis. FRC users are
     * not recommended to turn this on, as the magnetic influence of the
     * robot will likely negatively affect the performance of the Pigeon2.
     * 
     * - Default Value: False
     *
     * \param newEnableCompass Parameter to modify
     * \returns Itself
     */
    constexpr Pigeon2FeaturesConfigs &WithEnableCompass(bool newEnableCompass)
    {
        EnableCompass = std::move(newEnableCompass);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DisableTemperatureCompensation parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Disables using the temperature compensation feature.
     * 
     * - Default Value: False
     *
     * \param newDisableTemperatureCompensation Parameter to modify
     * \returns Itself
     */
    constexpr Pigeon2FeaturesConfigs &WithDisableTemperatureCompensation(bool newDisableTemperatureCompensation)
    {
        DisableTemperatureCompensation = std::move(newDisableTemperatureCompensation);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DisableNoMotionCalibration parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Disables using the no-motion calibration feature.
     * 
     * - Default Value: False
     *
     * \param newDisableNoMotionCalibration Parameter to modify
     * \returns Itself
     */
    constexpr Pigeon2FeaturesConfigs &WithDisableNoMotionCalibration(bool newDisableNoMotionCalibration)
    {
        DisableNoMotionCalibration = std::move(newDisableNoMotionCalibration);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: Pigeon2Features" << std::endl;
        ss << "    EnableCompass: " << EnableCompass << std::endl;
        ss << "    DisableTemperatureCompensation: " << DisableTemperatureCompensation << std::endl;
        ss << "    DisableNoMotionCalibration: " << DisableNoMotionCalibration << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Pigeon2UseCompass, EnableCompass, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Pigeon2DisableTemperatureCompensation, DisableTemperatureCompensation, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Pigeon2DisableNoMotionCalibration, DisableNoMotionCalibration, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Pigeon2UseCompass, string_c_str, string_length, &EnableCompass);
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Pigeon2DisableTemperatureCompensation, string_c_str, string_length, &DisableTemperatureCompensation);
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Pigeon2DisableNoMotionCalibration, string_c_str, string_length, &DisableNoMotionCalibration);
        return 0;
    }
};


/**
 * \brief Configs that directly affect motor output.
 * 
 * \details Includes motor invert, neutral mode, and other features
 *          related to motor output.
 */
class MotorOutputConfigs : public ParentConfiguration
{
public:
    constexpr MotorOutputConfigs() = default;

    /**
     * \brief Invert state of the device as seen from the front of the
     * motor.
     * 
     */
    signals::InvertedValue Inverted = signals::InvertedValue::CounterClockwise_Positive;
    /**
     * \brief The state of the motor controller bridge when output is
     * neutral or disabled.
     * 
     */
    signals::NeutralModeValue NeutralMode = signals::NeutralModeValue::Coast;
    /**
     * \brief Configures the output deadband duty cycle during duty cycle
     * and voltage based control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 0.25
     * - Default Value: 0
     * - Units: fractional
     */
    units::dimensionless::scalar_t DutyCycleNeutralDeadband = 0;
    /**
     * \brief Maximum (forward) output during duty cycle based control
     * modes.
     * 
     * - Minimum Value: -1.0
     * - Maximum Value: 1.0
     * - Default Value: 1
     * - Units: fractional
     */
    units::dimensionless::scalar_t PeakForwardDutyCycle = 1;
    /**
     * \brief Minimum (reverse) output during duty cycle based control
     * modes.
     * 
     * - Minimum Value: -1.0
     * - Maximum Value: 1.0
     * - Default Value: -1
     * - Units: fractional
     */
    units::dimensionless::scalar_t PeakReverseDutyCycle = -1;
    /**
     * \brief When a control request UseTimesync is enabled, this
     * determines the time-sychronized frequency at which control requests
     * are applied.
     * 
     * \details The application of the control request will be delayed
     * until the next timesync boundary at the frequency defined by this
     * config. When set to 0 Hz, timesync will never be used for control
     * requests, regardless of the value of UseTimesync.
     * 
     * - Minimum Value: 50
     * - Maximum Value: 500
     * - Default Value: 0
     * - Units: Hz
     */
    units::frequency::hertz_t ControlTimesyncFreqHz = 0_Hz;
    
    /**
     * \brief Modifies this configuration's Inverted parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Invert state of the device as seen from the front of the motor.
     * 
     *
     * \param newInverted Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithInverted(signals::InvertedValue newInverted)
    {
        Inverted = std::move(newInverted);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's NeutralMode parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The state of the motor controller bridge when output is neutral or
     * disabled.
     * 
     *
     * \param newNeutralMode Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithNeutralMode(signals::NeutralModeValue newNeutralMode)
    {
        NeutralMode = std::move(newNeutralMode);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DutyCycleNeutralDeadband parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configures the output deadband duty cycle during duty cycle and
     * voltage based control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 0.25
     * - Default Value: 0
     * - Units: fractional
     *
     * \param newDutyCycleNeutralDeadband Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithDutyCycleNeutralDeadband(units::dimensionless::scalar_t newDutyCycleNeutralDeadband)
    {
        DutyCycleNeutralDeadband = std::move(newDutyCycleNeutralDeadband);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakForwardDutyCycle parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum (forward) output during duty cycle based control modes.
     * 
     * - Minimum Value: -1.0
     * - Maximum Value: 1.0
     * - Default Value: 1
     * - Units: fractional
     *
     * \param newPeakForwardDutyCycle Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithPeakForwardDutyCycle(units::dimensionless::scalar_t newPeakForwardDutyCycle)
    {
        PeakForwardDutyCycle = std::move(newPeakForwardDutyCycle);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakReverseDutyCycle parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Minimum (reverse) output during duty cycle based control modes.
     * 
     * - Minimum Value: -1.0
     * - Maximum Value: 1.0
     * - Default Value: -1
     * - Units: fractional
     *
     * \param newPeakReverseDutyCycle Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithPeakReverseDutyCycle(units::dimensionless::scalar_t newPeakReverseDutyCycle)
    {
        PeakReverseDutyCycle = std::move(newPeakReverseDutyCycle);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ControlTimesyncFreqHz parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * When a control request UseTimesync is enabled, this determines the
     * time-sychronized frequency at which control requests are applied.
     * 
     * \details The application of the control request will be delayed
     * until the next timesync boundary at the frequency defined by this
     * config. When set to 0 Hz, timesync will never be used for control
     * requests, regardless of the value of UseTimesync.
     * 
     * - Minimum Value: 50
     * - Maximum Value: 500
     * - Default Value: 0
     * - Units: Hz
     *
     * \param newControlTimesyncFreqHz Parameter to modify
     * \returns Itself
     */
    constexpr MotorOutputConfigs &WithControlTimesyncFreqHz(units::frequency::hertz_t newControlTimesyncFreqHz)
    {
        ControlTimesyncFreqHz = std::move(newControlTimesyncFreqHz);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: MotorOutput" << std::endl;
        ss << "    Inverted: " << Inverted << std::endl;
        ss << "    NeutralMode: " << NeutralMode << std::endl;
        ss << "    DutyCycleNeutralDeadband: " << DutyCycleNeutralDeadband.to<double>() << " fractional" << std::endl;
        ss << "    PeakForwardDutyCycle: " << PeakForwardDutyCycle.to<double>() << " fractional" << std::endl;
        ss << "    PeakReverseDutyCycle: " << PeakReverseDutyCycle.to<double>() << " fractional" << std::endl;
        ss << "    ControlTimesyncFreqHz: " << ControlTimesyncFreqHz.to<double>() << " Hz" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_Inverted, Inverted.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_NeutralMode, NeutralMode.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_DutyCycleNeutralDB, DutyCycleNeutralDeadband.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakForwardDC, PeakForwardDutyCycle.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakReverseDC, PeakReverseDutyCycle.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_ControlTimesyncFreq, ControlTimesyncFreqHz.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_Inverted, string_c_str, string_length, &Inverted.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_NeutralMode, string_c_str, string_length, &NeutralMode.value);
        double DutyCycleNeutralDeadbandVal = DutyCycleNeutralDeadband.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_DutyCycleNeutralDB, string_c_str, string_length, &DutyCycleNeutralDeadbandVal);
        DutyCycleNeutralDeadband = units::dimensionless::scalar_t{DutyCycleNeutralDeadbandVal};
        double PeakForwardDutyCycleVal = PeakForwardDutyCycle.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakForwardDC, string_c_str, string_length, &PeakForwardDutyCycleVal);
        PeakForwardDutyCycle = units::dimensionless::scalar_t{PeakForwardDutyCycleVal};
        double PeakReverseDutyCycleVal = PeakReverseDutyCycle.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakReverseDC, string_c_str, string_length, &PeakReverseDutyCycleVal);
        PeakReverseDutyCycle = units::dimensionless::scalar_t{PeakReverseDutyCycleVal};
        double ControlTimesyncFreqHzVal = ControlTimesyncFreqHz.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_ControlTimesyncFreq, string_c_str, string_length, &ControlTimesyncFreqHzVal);
        ControlTimesyncFreqHz = units::frequency::hertz_t{ControlTimesyncFreqHzVal};
        return 0;
    }
};


/**
 * \brief Configs that directly affect current limiting features.
 * 
 * \details Contains the supply/stator current limit thresholds and
 *          whether to enable them.
 */
class CurrentLimitsConfigs : public ParentConfiguration
{
public:
    constexpr CurrentLimitsConfigs() = default;

    /**
     * \brief The amount of current allowed in the motor (motoring and
     * regen current).  Note this requires StatorCurrentLimitEnable to be
     * true.
     * 
     * For torque current control, this is applied in addition to the
     * PeakForwardTorqueCurrent and PeakReverseTorqueCurrent in
     * TorqueCurrentConfigs.
     * 
     * Stator current is directly proportional to torque, so this limit
     * can be used to restrict the torque output of the motor, such as
     * preventing wheel slip for a drivetrain.  Additionally, stator
     * current limits can prevent brownouts during acceleration; supply
     * current will never exceed the stator current limit and is often
     * significantly lower than stator current.
     * 
     * A reasonable starting point for a stator current limit is 120 A,
     * with values commonly ranging from 80-160 A. Mechanisms with a hard
     * stop may need a smaller limit to reduce the torque applied when
     * running into the hard stop.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 800.0
     * - Default Value: 120
     * - Units: A
     */
    units::current::ampere_t StatorCurrentLimit = 120_A;
    /**
     * \brief Enable motor stator current limiting.
     * 
     * - Default Value: True
     */
    bool StatorCurrentLimitEnable = true;
    /**
     * \brief The absolute maximum amount of supply current allowed.  Note
     * this requires SupplyCurrentLimitEnable to be true.  Use
     * SupplyCurrentLowerLimit and SupplyCurrentLowerTime to reduce the
     * supply current limit after the time threshold is exceeded.
     * 
     * Supply current is the current drawn from the battery, so this limit
     * can be used to prevent breaker trips and improve battery longevity.
     *  Additionally, in scenarios where the robot experiences brownouts
     * despite configuring stator current limits, a supply current limit
     * can further help avoid brownouts. However, it is important to note
     * that such brownouts may be caused by a bad battery or poor power
     * wiring.
     * 
     * A reasonable starting point for a supply current limit is 70 A with
     * a lower limit of 40 A after 1.0 second. Supply current limits
     * commonly range from 20-80 A depending on the breaker used.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 800.0
     * - Default Value: 70
     * - Units: A
     */
    units::current::ampere_t SupplyCurrentLimit = 70_A;
    /**
     * \brief Enable motor supply current limiting.
     * 
     * - Default Value: True
     */
    bool SupplyCurrentLimitEnable = true;
    /**
     * \brief The amount of supply current allowed after the regular
     * SupplyCurrentLimit is active for longer than
     * SupplyCurrentLowerTime.  This allows higher current draws for a
     * fixed period of time before reducing the current limit to protect
     * breakers.  This has no effect if SupplyCurrentLimit is lower than
     * this value or SupplyCurrentLowerTime is 0.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 500
     * - Default Value: 40
     * - Units: A
     */
    units::current::ampere_t SupplyCurrentLowerLimit = 40_A;
    /**
     * \brief Reduces supply current to the SupplyCurrentLowerLimit after
     * limiting to SupplyCurrentLimit for this period of time.  If this is
     * set to 0, SupplyCurrentLowerLimit will be ignored.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 2.5
     * - Default Value: 1.0
     * - Units: seconds
     */
    units::time::second_t SupplyCurrentLowerTime = 1.0_s;
    
    /**
     * \brief Modifies this configuration's StatorCurrentLimit parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The amount of current allowed in the motor (motoring and regen
     * current).  Note this requires StatorCurrentLimitEnable to be true.
     * 
     * For torque current control, this is applied in addition to the
     * PeakForwardTorqueCurrent and PeakReverseTorqueCurrent in
     * TorqueCurrentConfigs.
     * 
     * Stator current is directly proportional to torque, so this limit
     * can be used to restrict the torque output of the motor, such as
     * preventing wheel slip for a drivetrain.  Additionally, stator
     * current limits can prevent brownouts during acceleration; supply
     * current will never exceed the stator current limit and is often
     * significantly lower than stator current.
     * 
     * A reasonable starting point for a stator current limit is 120 A,
     * with values commonly ranging from 80-160 A. Mechanisms with a hard
     * stop may need a smaller limit to reduce the torque applied when
     * running into the hard stop.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 800.0
     * - Default Value: 120
     * - Units: A
     *
     * \param newStatorCurrentLimit Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithStatorCurrentLimit(units::current::ampere_t newStatorCurrentLimit)
    {
        StatorCurrentLimit = std::move(newStatorCurrentLimit);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's StatorCurrentLimitEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Enable motor stator current limiting.
     * 
     * - Default Value: True
     *
     * \param newStatorCurrentLimitEnable Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithStatorCurrentLimitEnable(bool newStatorCurrentLimitEnable)
    {
        StatorCurrentLimitEnable = std::move(newStatorCurrentLimitEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SupplyCurrentLimit parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The absolute maximum amount of supply current allowed.  Note this
     * requires SupplyCurrentLimitEnable to be true.  Use
     * SupplyCurrentLowerLimit and SupplyCurrentLowerTime to reduce the
     * supply current limit after the time threshold is exceeded.
     * 
     * Supply current is the current drawn from the battery, so this limit
     * can be used to prevent breaker trips and improve battery longevity.
     *  Additionally, in scenarios where the robot experiences brownouts
     * despite configuring stator current limits, a supply current limit
     * can further help avoid brownouts. However, it is important to note
     * that such brownouts may be caused by a bad battery or poor power
     * wiring.
     * 
     * A reasonable starting point for a supply current limit is 70 A with
     * a lower limit of 40 A after 1.0 second. Supply current limits
     * commonly range from 20-80 A depending on the breaker used.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 800.0
     * - Default Value: 70
     * - Units: A
     *
     * \param newSupplyCurrentLimit Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithSupplyCurrentLimit(units::current::ampere_t newSupplyCurrentLimit)
    {
        SupplyCurrentLimit = std::move(newSupplyCurrentLimit);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SupplyCurrentLimitEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Enable motor supply current limiting.
     * 
     * - Default Value: True
     *
     * \param newSupplyCurrentLimitEnable Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithSupplyCurrentLimitEnable(bool newSupplyCurrentLimitEnable)
    {
        SupplyCurrentLimitEnable = std::move(newSupplyCurrentLimitEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SupplyCurrentLowerLimit parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The amount of supply current allowed after the regular
     * SupplyCurrentLimit is active for longer than
     * SupplyCurrentLowerTime.  This allows higher current draws for a
     * fixed period of time before reducing the current limit to protect
     * breakers.  This has no effect if SupplyCurrentLimit is lower than
     * this value or SupplyCurrentLowerTime is 0.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 500
     * - Default Value: 40
     * - Units: A
     *
     * \param newSupplyCurrentLowerLimit Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithSupplyCurrentLowerLimit(units::current::ampere_t newSupplyCurrentLowerLimit)
    {
        SupplyCurrentLowerLimit = std::move(newSupplyCurrentLowerLimit);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SupplyCurrentLowerTime parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Reduces supply current to the SupplyCurrentLowerLimit after
     * limiting to SupplyCurrentLimit for this period of time.  If this is
     * set to 0, SupplyCurrentLowerLimit will be ignored.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 2.5
     * - Default Value: 1.0
     * - Units: seconds
     *
     * \param newSupplyCurrentLowerTime Parameter to modify
     * \returns Itself
     */
    constexpr CurrentLimitsConfigs &WithSupplyCurrentLowerTime(units::time::second_t newSupplyCurrentLowerTime)
    {
        SupplyCurrentLowerTime = std::move(newSupplyCurrentLowerTime);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: CurrentLimits" << std::endl;
        ss << "    StatorCurrentLimit: " << StatorCurrentLimit.to<double>() << " A" << std::endl;
        ss << "    StatorCurrentLimitEnable: " << StatorCurrentLimitEnable << std::endl;
        ss << "    SupplyCurrentLimit: " << SupplyCurrentLimit.to<double>() << " A" << std::endl;
        ss << "    SupplyCurrentLimitEnable: " << SupplyCurrentLimitEnable << std::endl;
        ss << "    SupplyCurrentLowerLimit: " << SupplyCurrentLowerLimit.to<double>() << " A" << std::endl;
        ss << "    SupplyCurrentLowerTime: " << SupplyCurrentLowerTime.to<double>() << " seconds" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_StatorCurrentLimit, StatorCurrentLimit.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_StatorCurrLimitEn, StatorCurrentLimitEnable, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_SupplyCurrentLimit, SupplyCurrentLimit.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_SupplyCurrLimitEn, SupplyCurrentLimitEnable, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_SupplyCurrentLowerLimit, SupplyCurrentLowerLimit.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_SupplyCurrentLowerTime, SupplyCurrentLowerTime.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double StatorCurrentLimitVal = StatorCurrentLimit.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_StatorCurrentLimit, string_c_str, string_length, &StatorCurrentLimitVal);
        StatorCurrentLimit = units::current::ampere_t{StatorCurrentLimitVal};
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_StatorCurrLimitEn, string_c_str, string_length, &StatorCurrentLimitEnable);
        double SupplyCurrentLimitVal = SupplyCurrentLimit.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_SupplyCurrentLimit, string_c_str, string_length, &SupplyCurrentLimitVal);
        SupplyCurrentLimit = units::current::ampere_t{SupplyCurrentLimitVal};
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_SupplyCurrLimitEn, string_c_str, string_length, &SupplyCurrentLimitEnable);
        double SupplyCurrentLowerLimitVal = SupplyCurrentLowerLimit.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_SupplyCurrentLowerLimit, string_c_str, string_length, &SupplyCurrentLowerLimitVal);
        SupplyCurrentLowerLimit = units::current::ampere_t{SupplyCurrentLowerLimitVal};
        double SupplyCurrentLowerTimeVal = SupplyCurrentLowerTime.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_SupplyCurrentLowerTime, string_c_str, string_length, &SupplyCurrentLowerTimeVal);
        SupplyCurrentLowerTime = units::time::second_t{SupplyCurrentLowerTimeVal};
        return 0;
    }
};


/**
 * \brief Configs that affect Voltage control types.
 * 
 * \details Includes peak output voltages and other configs affecting
 *          voltage measurements.
 */
class VoltageConfigs : public ParentConfiguration
{
public:
    constexpr VoltageConfigs() = default;

    /**
     * \brief The time constant (in seconds) of the low-pass filter for
     * the supply voltage.
     * 
     * \details This impacts the filtering for the reported supply
     * voltage, and any control strategies that use the supply voltage
     * (such as voltage control on a motor controller).
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 0.1
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t SupplyVoltageTimeConstant = 0_s;
    /**
     * \brief Maximum (forward) output during voltage based control modes.
     * 
     * - Minimum Value: -16
     * - Maximum Value: 16
     * - Default Value: 16
     * - Units: V
     */
    units::voltage::volt_t PeakForwardVoltage = 16_V;
    /**
     * \brief Minimum (reverse) output during voltage based control modes.
     * 
     * - Minimum Value: -16
     * - Maximum Value: 16
     * - Default Value: -16
     * - Units: V
     */
    units::voltage::volt_t PeakReverseVoltage = -16_V;
    
    /**
     * \brief Modifies this configuration's SupplyVoltageTimeConstant parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The time constant (in seconds) of the low-pass filter for the
     * supply voltage.
     * 
     * \details This impacts the filtering for the reported supply
     * voltage, and any control strategies that use the supply voltage
     * (such as voltage control on a motor controller).
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 0.1
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newSupplyVoltageTimeConstant Parameter to modify
     * \returns Itself
     */
    constexpr VoltageConfigs &WithSupplyVoltageTimeConstant(units::time::second_t newSupplyVoltageTimeConstant)
    {
        SupplyVoltageTimeConstant = std::move(newSupplyVoltageTimeConstant);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakForwardVoltage parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum (forward) output during voltage based control modes.
     * 
     * - Minimum Value: -16
     * - Maximum Value: 16
     * - Default Value: 16
     * - Units: V
     *
     * \param newPeakForwardVoltage Parameter to modify
     * \returns Itself
     */
    constexpr VoltageConfigs &WithPeakForwardVoltage(units::voltage::volt_t newPeakForwardVoltage)
    {
        PeakForwardVoltage = std::move(newPeakForwardVoltage);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakReverseVoltage parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Minimum (reverse) output during voltage based control modes.
     * 
     * - Minimum Value: -16
     * - Maximum Value: 16
     * - Default Value: -16
     * - Units: V
     *
     * \param newPeakReverseVoltage Parameter to modify
     * \returns Itself
     */
    constexpr VoltageConfigs &WithPeakReverseVoltage(units::voltage::volt_t newPeakReverseVoltage)
    {
        PeakReverseVoltage = std::move(newPeakReverseVoltage);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: Voltage" << std::endl;
        ss << "    SupplyVoltageTimeConstant: " << SupplyVoltageTimeConstant.to<double>() << " seconds" << std::endl;
        ss << "    PeakForwardVoltage: " << PeakForwardVoltage.to<double>() << " V" << std::endl;
        ss << "    PeakReverseVoltage: " << PeakReverseVoltage.to<double>() << " V" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_SupplyVLowpassTau, SupplyVoltageTimeConstant.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakForwardV, PeakForwardVoltage.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakReverseV, PeakReverseVoltage.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double SupplyVoltageTimeConstantVal = SupplyVoltageTimeConstant.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_SupplyVLowpassTau, string_c_str, string_length, &SupplyVoltageTimeConstantVal);
        SupplyVoltageTimeConstant = units::time::second_t{SupplyVoltageTimeConstantVal};
        double PeakForwardVoltageVal = PeakForwardVoltage.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakForwardV, string_c_str, string_length, &PeakForwardVoltageVal);
        PeakForwardVoltage = units::voltage::volt_t{PeakForwardVoltageVal};
        double PeakReverseVoltageVal = PeakReverseVoltage.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakReverseV, string_c_str, string_length, &PeakReverseVoltageVal);
        PeakReverseVoltage = units::voltage::volt_t{PeakReverseVoltageVal};
        return 0;
    }
};


/**
 * \brief Configs that affect Torque Current control types.
 * 
 * \details Includes the maximum and minimum applied torque output and
 *          the neutral deadband used during TorqueCurrentFOC
 *          requests.
 */
class TorqueCurrentConfigs : public ParentConfiguration
{
public:
    constexpr TorqueCurrentConfigs() = default;

    /**
     * \brief Maximum (forward) output during torque current based control
     * modes.
     * 
     * - Minimum Value: -800
     * - Maximum Value: 800
     * - Default Value: 800
     * - Units: A
     */
    units::current::ampere_t PeakForwardTorqueCurrent = 800_A;
    /**
     * \brief Minimum (reverse) output during torque current based control
     * modes.
     * 
     * - Minimum Value: -800
     * - Maximum Value: 800
     * - Default Value: -800
     * - Units: A
     */
    units::current::ampere_t PeakReverseTorqueCurrent = -800_A;
    /**
     * \brief Configures the output deadband during torque current based
     * control modes.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 25
     * - Default Value: 0.0
     * - Units: A
     */
    units::current::ampere_t TorqueNeutralDeadband = 0.0_A;
    
    /**
     * \brief Modifies this configuration's PeakForwardTorqueCurrent parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum (forward) output during torque current based control modes.
     * 
     * - Minimum Value: -800
     * - Maximum Value: 800
     * - Default Value: 800
     * - Units: A
     *
     * \param newPeakForwardTorqueCurrent Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentConfigs &WithPeakForwardTorqueCurrent(units::current::ampere_t newPeakForwardTorqueCurrent)
    {
        PeakForwardTorqueCurrent = std::move(newPeakForwardTorqueCurrent);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakReverseTorqueCurrent parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Minimum (reverse) output during torque current based control modes.
     * 
     * - Minimum Value: -800
     * - Maximum Value: 800
     * - Default Value: -800
     * - Units: A
     *
     * \param newPeakReverseTorqueCurrent Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentConfigs &WithPeakReverseTorqueCurrent(units::current::ampere_t newPeakReverseTorqueCurrent)
    {
        PeakReverseTorqueCurrent = std::move(newPeakReverseTorqueCurrent);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's TorqueNeutralDeadband parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configures the output deadband during torque current based control
     * modes.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 25
     * - Default Value: 0.0
     * - Units: A
     *
     * \param newTorqueNeutralDeadband Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentConfigs &WithTorqueNeutralDeadband(units::current::ampere_t newTorqueNeutralDeadband)
    {
        TorqueNeutralDeadband = std::move(newTorqueNeutralDeadband);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: TorqueCurrent" << std::endl;
        ss << "    PeakForwardTorqueCurrent: " << PeakForwardTorqueCurrent.to<double>() << " A" << std::endl;
        ss << "    PeakReverseTorqueCurrent: " << PeakReverseTorqueCurrent.to<double>() << " A" << std::endl;
        ss << "    TorqueNeutralDeadband: " << TorqueNeutralDeadband.to<double>() << " A" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakForTorqCurr, PeakForwardTorqueCurrent.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakRevTorqCurr, PeakReverseTorqueCurrent.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_TorqueNeutralDB, TorqueNeutralDeadband.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double PeakForwardTorqueCurrentVal = PeakForwardTorqueCurrent.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakForTorqCurr, string_c_str, string_length, &PeakForwardTorqueCurrentVal);
        PeakForwardTorqueCurrent = units::current::ampere_t{PeakForwardTorqueCurrentVal};
        double PeakReverseTorqueCurrentVal = PeakReverseTorqueCurrent.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakRevTorqCurr, string_c_str, string_length, &PeakReverseTorqueCurrentVal);
        PeakReverseTorqueCurrent = units::current::ampere_t{PeakReverseTorqueCurrentVal};
        double TorqueNeutralDeadbandVal = TorqueNeutralDeadband.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_TorqueNeutralDB, string_c_str, string_length, &TorqueNeutralDeadbandVal);
        TorqueNeutralDeadband = units::current::ampere_t{TorqueNeutralDeadbandVal};
        return 0;
    }
};


/**
 * \brief Configs that affect the feedback of this motor controller.
 * 
 * \details Includes feedback sensor source, any offsets for the
 *          feedback sensor, and various ratios to describe the
 *          relationship between the sensor and the mechanism for
 *          closed looping.
 */
class FeedbackConfigs : public ParentConfiguration
{
public:
    constexpr FeedbackConfigs() = default;

    /**
     * \brief The offset applied to the absolute integrated rotor sensor. 
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
     * Choose RemotePigeon2_Yaw, RemotePigeon2_Pitch, and
     * RemotePigeon2_Roll to use another Pigeon2 on the same CAN bus (this
     * also requires setting FeedbackRemoteSensorID).  Talon will update
     * its position to match the selected value whenever Pigeon2 publishes
     * its information on CAN bus. Note that the Talon position will be in
     * rotations and not degrees.
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
     * The offset applied to the absolute integrated rotor sensor.  This
     * can be used to zero the rotor in applications that are within one
     * rotor rotation.
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
     * Choose RemotePigeon2_Yaw, RemotePigeon2_Pitch, and
     * RemotePigeon2_Roll to use another Pigeon2 on the same CAN bus (this
     * also requires setting FeedbackRemoteSensorID).  Talon will update
     * its position to match the selected value whenever Pigeon2 publishes
     * its information on CAN bus. Note that the Talon position will be in
     * rotations and not degrees.
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
     *        RemoteCANdi PWM 1 by passing in the CANdi object.
     * 
     * \param device CANdi reference to use for RemoteCANdi
     * \returns Itself
     */
    FeedbackConfigs &WithRemoteCANdiPwm1(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANdi PWM 2 by passing in the CANdi object.
     * 
     * \param device CANdi reference to use for RemoteCANdi
     * \returns Itself
     */
    FeedbackConfigs &WithRemoteCANdiPwm2(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANdi Quadrature by passing in the CANdi object.
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
    FeedbackConfigs &WithFusedCANdiPwm1(const hardware::core::CoreCANdi& device);
    
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
    FeedbackConfigs &WithFusedCANdiPwm2(const hardware::core::CoreCANdi& device);
    
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
    FeedbackConfigs &WithSyncCANdiPwm1(const hardware::core::CoreCANdi& device);
    
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
    FeedbackConfigs &WithSyncCANdiPwm2(const hardware::core::CoreCANdi& device);
    
    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: Feedback" << std::endl;
        ss << "    FeedbackRotorOffset: " << FeedbackRotorOffset.to<double>() << " rotations" << std::endl;
        ss << "    SensorToMechanismRatio: " << SensorToMechanismRatio.to<double>() << " scalar" << std::endl;
        ss << "    RotorToSensorRatio: " << RotorToSensorRatio.to<double>() << " scalar" << std::endl;
        ss << "    FeedbackSensorSource: " << FeedbackSensorSource << std::endl;
        ss << "    FeedbackRemoteSensorID: " << FeedbackRemoteSensorID << std::endl;
        ss << "    VelocityFilterTimeConstant: " << VelocityFilterTimeConstant.to<double>() << " seconds" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_FeedbackRotorOffset, FeedbackRotorOffset.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_SensorToMechanismRatio, SensorToMechanismRatio.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_RotorToSensorRatio, RotorToSensorRatio.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_FeedbackSensorSource, FeedbackSensorSource.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_FeedbackRemoteSensorID, FeedbackRemoteSensorID, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_VelocityFilterTimeConstant, VelocityFilterTimeConstant.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double FeedbackRotorOffsetVal = FeedbackRotorOffset.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_FeedbackRotorOffset, string_c_str, string_length, &FeedbackRotorOffsetVal);
        FeedbackRotorOffset = units::angle::turn_t{FeedbackRotorOffsetVal};
        double SensorToMechanismRatioVal = SensorToMechanismRatio.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_SensorToMechanismRatio, string_c_str, string_length, &SensorToMechanismRatioVal);
        SensorToMechanismRatio = units::dimensionless::scalar_t{SensorToMechanismRatioVal};
        double RotorToSensorRatioVal = RotorToSensorRatio.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_RotorToSensorRatio, string_c_str, string_length, &RotorToSensorRatioVal);
        RotorToSensorRatio = units::dimensionless::scalar_t{RotorToSensorRatioVal};
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_FeedbackSensorSource, string_c_str, string_length, &FeedbackSensorSource.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_FeedbackRemoteSensorID, string_c_str, string_length, &FeedbackRemoteSensorID);
        double VelocityFilterTimeConstantVal = VelocityFilterTimeConstant.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_VelocityFilterTimeConstant, string_c_str, string_length, &VelocityFilterTimeConstantVal);
        VelocityFilterTimeConstant = units::time::second_t{VelocityFilterTimeConstantVal};
        return 0;
    }
};


/**
 * \brief Configs that affect the external feedback sensor of this
 *        motor controller.
 * 
 * \details Includes feedback sensor source, offsets and sensor phase
 *          for the feedback sensor, and various ratios to describe
 *          the relationship between the sensor and the mechanism for
 *          closed looping.
 */
class ExternalFeedbackConfigs : public ParentConfiguration
{
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
     * \brief The offset applied to any absolute sensor connected to the
     * Talon data port.  This is only supported when using the PulseWidth
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
     * Choose RemotePigeon2_Yaw, RemotePigeon2_Pitch, and
     * RemotePigeon2_Roll to use another Pigeon2 on the same CAN bus (this
     * also requires setting FeedbackRemoteSensorID).  Talon will update
     * its position to match the selected value whenever Pigeon2 publishes
     * its information on CAN bus. Note that the Talon position will be in
     * rotations and not degrees.
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
     * The offset applied to any absolute sensor connected to the Talon
     * data port.  This is only supported when using the PulseWidth sensor
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
     * Choose RemotePigeon2_Yaw, RemotePigeon2_Pitch, and
     * RemotePigeon2_Roll to use another Pigeon2 on the same CAN bus (this
     * also requires setting FeedbackRemoteSensorID).  Talon will update
     * its position to match the selected value whenever Pigeon2 publishes
     * its information on CAN bus. Note that the Talon position will be in
     * rotations and not degrees.
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
     *        RemoteCANdi PWM 1 by passing in the CANdi object.
     * 
     * \param device CANdi reference to use for RemoteCANdi
     * \returns Itself
     */
    ExternalFeedbackConfigs &WithRemoteCANdiPwm1(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANdi PWM 2 by passing in the CANdi object.
     * 
     * \param device CANdi reference to use for RemoteCANdi
     * \returns Itself
     */
    ExternalFeedbackConfigs &WithRemoteCANdiPwm2(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANdi Quadrature by passing in the CANdi object.
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
    ExternalFeedbackConfigs &WithFusedCANdiPwm1(const hardware::core::CoreCANdi& device);
    
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
    ExternalFeedbackConfigs &WithFusedCANdiPwm2(const hardware::core::CoreCANdi& device);
    
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
    ExternalFeedbackConfigs &WithSyncCANdiPwm1(const hardware::core::CoreCANdi& device);
    
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
    ExternalFeedbackConfigs &WithSyncCANdiPwm2(const hardware::core::CoreCANdi& device);
    
    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: ExternalFeedback" << std::endl;
        ss << "    SensorToMechanismRatio: " << SensorToMechanismRatio.to<double>() << " scalar" << std::endl;
        ss << "    RotorToSensorRatio: " << RotorToSensorRatio.to<double>() << " scalar" << std::endl;
        ss << "    FeedbackRemoteSensorID: " << FeedbackRemoteSensorID << std::endl;
        ss << "    VelocityFilterTimeConstant: " << VelocityFilterTimeConstant.to<double>() << " seconds" << std::endl;
        ss << "    AbsoluteSensorOffset: " << AbsoluteSensorOffset.to<double>() << " rotations" << std::endl;
        ss << "    ExternalFeedbackSensorSource: " << ExternalFeedbackSensorSource << std::endl;
        ss << "    SensorPhase: " << SensorPhase << std::endl;
        ss << "    QuadratureEdgesPerRotation: " << QuadratureEdgesPerRotation << std::endl;
        ss << "    AbsoluteSensorDiscontinuityPoint: " << AbsoluteSensorDiscontinuityPoint.to<double>() << " rotations" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_SensorToMechanismRatio, SensorToMechanismRatio.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_RotorToSensorRatio, RotorToSensorRatio.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_FeedbackRemoteSensorID, FeedbackRemoteSensorID, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_VelocityFilterTimeConstant, VelocityFilterTimeConstant.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_AbsoluteSensorOffset, AbsoluteSensorOffset.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_ExternalFeedbackSensorSource, ExternalFeedbackSensorSource.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_SensorPhase, SensorPhase.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_QuadratureEdgesPerRotation, QuadratureEdgesPerRotation, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_AbsoluteSensorDiscontinuityPoint, AbsoluteSensorDiscontinuityPoint.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double SensorToMechanismRatioVal = SensorToMechanismRatio.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_SensorToMechanismRatio, string_c_str, string_length, &SensorToMechanismRatioVal);
        SensorToMechanismRatio = units::dimensionless::scalar_t{SensorToMechanismRatioVal};
        double RotorToSensorRatioVal = RotorToSensorRatio.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_RotorToSensorRatio, string_c_str, string_length, &RotorToSensorRatioVal);
        RotorToSensorRatio = units::dimensionless::scalar_t{RotorToSensorRatioVal};
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_FeedbackRemoteSensorID, string_c_str, string_length, &FeedbackRemoteSensorID);
        double VelocityFilterTimeConstantVal = VelocityFilterTimeConstant.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_VelocityFilterTimeConstant, string_c_str, string_length, &VelocityFilterTimeConstantVal);
        VelocityFilterTimeConstant = units::time::second_t{VelocityFilterTimeConstantVal};
        double AbsoluteSensorOffsetVal = AbsoluteSensorOffset.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_AbsoluteSensorOffset, string_c_str, string_length, &AbsoluteSensorOffsetVal);
        AbsoluteSensorOffset = units::angle::turn_t{AbsoluteSensorOffsetVal};
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_ExternalFeedbackSensorSource, string_c_str, string_length, &ExternalFeedbackSensorSource.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_SensorPhase, string_c_str, string_length, &SensorPhase.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_QuadratureEdgesPerRotation, string_c_str, string_length, &QuadratureEdgesPerRotation);
        double AbsoluteSensorDiscontinuityPointVal = AbsoluteSensorDiscontinuityPoint.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_AbsoluteSensorDiscontinuityPoint, string_c_str, string_length, &AbsoluteSensorDiscontinuityPointVal);
        AbsoluteSensorDiscontinuityPoint = units::angle::turn_t{AbsoluteSensorDiscontinuityPointVal};
        return 0;
    }
};


/**
 * \brief Configs related to sensors used for differential control of
 *        a mechanism.
 * 
 * \details Includes the differential sensor sources and IDs.
 */
class DifferentialSensorsConfigs : public ParentConfiguration
{
public:
    constexpr DifferentialSensorsConfigs() = default;

    /**
     * \brief Choose what sensor source is used for differential control
     * of a mechanism.  The default is Disabled.  All other options
     * require setting the DifferentialTalonFXSensorID, as the average of
     * this Talon FX's sensor and the remote TalonFX's sensor is used for
     * the differential controller's primary targets.
     * 
     * Choose RemoteTalonFX_Diff to use another TalonFX on the same CAN
     * bus.  Talon FX will update its differential position and velocity
     * whenever the remote TalonFX publishes its information on CAN bus. 
     * The differential controller will use the difference between this
     * TalonFX's sensor and the remote Talon FX's sensor for the
     * differential component of the output.
     * 
     * Choose RemotePigeon2_Yaw, RemotePigeon2_Pitch, and
     * RemotePigeon2_Roll to use another Pigeon2 on the same CAN bus (this
     * also requires setting DifferentialRemoteSensorID).  Talon FX will
     * update its differential position to match the selected value
     * whenever Pigeon2 publishes its information on CAN bus. Note that
     * the Talon FX differential position will be in rotations and not
     * degrees.
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
     * when the Differential Sensor Source is not disabled.
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
     * RemoteTalonFX_Diff.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 62
     * - Default Value: 0
     * - Units: 
     */
    int DifferentialRemoteSensorID = 0;
    
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
     * Choose RemoteTalonFX_Diff to use another TalonFX on the same CAN
     * bus.  Talon FX will update its differential position and velocity
     * whenever the remote TalonFX publishes its information on CAN bus. 
     * The differential controller will use the difference between this
     * TalonFX's sensor and the remote Talon FX's sensor for the
     * differential component of the output.
     * 
     * Choose RemotePigeon2_Yaw, RemotePigeon2_Pitch, and
     * RemotePigeon2_Roll to use another Pigeon2 on the same CAN bus (this
     * also requires setting DifferentialRemoteSensorID).  Talon FX will
     * update its differential position to match the selected value
     * whenever Pigeon2 publishes its information on CAN bus. Note that
     * the Talon FX differential position will be in rotations and not
     * degrees.
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
     * Device ID of which remote Talon FX to use.  This is used when the
     * Differential Sensor Source is not disabled.
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
     * This is used when the Differential Sensor Source is not
     * RemoteTalonFX_Diff.
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

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: DifferentialSensors" << std::endl;
        ss << "    DifferentialSensorSource: " << DifferentialSensorSource << std::endl;
        ss << "    DifferentialTalonFXSensorID: " << DifferentialTalonFXSensorID << std::endl;
        ss << "    DifferentialRemoteSensorID: " << DifferentialRemoteSensorID << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_DifferentialSensorSource, DifferentialSensorSource.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_DifferentialTalonFXSensorID, DifferentialTalonFXSensorID, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_DifferentialRemoteSensorID, DifferentialRemoteSensorID, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_DifferentialSensorSource, string_c_str, string_length, &DifferentialSensorSource.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_DifferentialTalonFXSensorID, string_c_str, string_length, &DifferentialTalonFXSensorID);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_DifferentialRemoteSensorID, string_c_str, string_length, &DifferentialRemoteSensorID);
        return 0;
    }
};


/**
 * \brief Configs related to constants used for differential control
 *        of a mechanism.
 * 
 * \details Includes the differential peak outputs.
 */
class DifferentialConstantsConfigs : public ParentConfiguration
{
public:
    constexpr DifferentialConstantsConfigs() = default;

    /**
     * \brief Maximum differential output during duty cycle based
     * differential control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 2.0
     * - Default Value: 2
     * - Units: fractional
     */
    units::dimensionless::scalar_t PeakDifferentialDutyCycle = 2;
    /**
     * \brief Maximum differential output during voltage based
     * differential control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 32
     * - Default Value: 32
     * - Units: V
     */
    units::voltage::volt_t PeakDifferentialVoltage = 32_V;
    /**
     * \brief Maximum differential output during torque current based
     * differential control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1600
     * - Default Value: 1600
     * - Units: A
     */
    units::current::ampere_t PeakDifferentialTorqueCurrent = 1600_A;
    
    /**
     * \brief Modifies this configuration's PeakDifferentialDutyCycle parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum differential output during duty cycle based differential
     * control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 2.0
     * - Default Value: 2
     * - Units: fractional
     *
     * \param newPeakDifferentialDutyCycle Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialConstantsConfigs &WithPeakDifferentialDutyCycle(units::dimensionless::scalar_t newPeakDifferentialDutyCycle)
    {
        PeakDifferentialDutyCycle = std::move(newPeakDifferentialDutyCycle);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakDifferentialVoltage parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum differential output during voltage based differential
     * control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 32
     * - Default Value: 32
     * - Units: V
     *
     * \param newPeakDifferentialVoltage Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialConstantsConfigs &WithPeakDifferentialVoltage(units::voltage::volt_t newPeakDifferentialVoltage)
    {
        PeakDifferentialVoltage = std::move(newPeakDifferentialVoltage);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PeakDifferentialTorqueCurrent parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Maximum differential output during torque current based
     * differential control modes.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1600
     * - Default Value: 1600
     * - Units: A
     *
     * \param newPeakDifferentialTorqueCurrent Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialConstantsConfigs &WithPeakDifferentialTorqueCurrent(units::current::ampere_t newPeakDifferentialTorqueCurrent)
    {
        PeakDifferentialTorqueCurrent = std::move(newPeakDifferentialTorqueCurrent);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: DifferentialConstants" << std::endl;
        ss << "    PeakDifferentialDutyCycle: " << PeakDifferentialDutyCycle.to<double>() << " fractional" << std::endl;
        ss << "    PeakDifferentialVoltage: " << PeakDifferentialVoltage.to<double>() << " V" << std::endl;
        ss << "    PeakDifferentialTorqueCurrent: " << PeakDifferentialTorqueCurrent.to<double>() << " A" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakDiffDC, PeakDifferentialDutyCycle.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakDiffV, PeakDifferentialVoltage.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakDiffTorqCurr, PeakDifferentialTorqueCurrent.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double PeakDifferentialDutyCycleVal = PeakDifferentialDutyCycle.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakDiffDC, string_c_str, string_length, &PeakDifferentialDutyCycleVal);
        PeakDifferentialDutyCycle = units::dimensionless::scalar_t{PeakDifferentialDutyCycleVal};
        double PeakDifferentialVoltageVal = PeakDifferentialVoltage.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakDiffV, string_c_str, string_length, &PeakDifferentialVoltageVal);
        PeakDifferentialVoltage = units::voltage::volt_t{PeakDifferentialVoltageVal};
        double PeakDifferentialTorqueCurrentVal = PeakDifferentialTorqueCurrent.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PeakDiffTorqCurr, string_c_str, string_length, &PeakDifferentialTorqueCurrentVal);
        PeakDifferentialTorqueCurrent = units::current::ampere_t{PeakDifferentialTorqueCurrentVal};
        return 0;
    }
};


/**
 * \brief Configs that affect the open-loop control of this motor
 *        controller.
 * 
 * \details Open-loop ramp rates for the various control types.
 */
class OpenLoopRampsConfigs : public ParentConfiguration
{
public:
    constexpr OpenLoopRampsConfigs() = default;

    /**
     * \brief If non-zero, this determines how much time to ramp from 0%
     * output to 100% during the open-loop DutyCycleOut control mode.
     * 
     * This provides an easy way to limit the acceleration of the motor.
     * However, the acceleration and current draw of the motor can be
     * better restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t DutyCycleOpenLoopRampPeriod = 0_s;
    /**
     * \brief If non-zero, this determines how much time to ramp from 0V
     * output to 12V during the open-loop VoltageOut control mode.
     * 
     * This provides an easy way to limit the acceleration of the motor.
     * However, the acceleration and current draw of the motor can be
     * better restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t VoltageOpenLoopRampPeriod = 0_s;
    /**
     * \brief If non-zero, this determines how much time to ramp from 0A
     * output to 300A during the open-loop TorqueCurrent control mode.
     * 
     * Since TorqueCurrent is directly proportional to acceleration, this
     * ramp limits jerk instead of acceleration.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 10
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t TorqueOpenLoopRampPeriod = 0_s;
    
    /**
     * \brief Modifies this configuration's DutyCycleOpenLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0% output
     * to 100% during the open-loop DutyCycleOut control mode.
     * 
     * This provides an easy way to limit the acceleration of the motor.
     * However, the acceleration and current draw of the motor can be
     * better restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newDutyCycleOpenLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr OpenLoopRampsConfigs &WithDutyCycleOpenLoopRampPeriod(units::time::second_t newDutyCycleOpenLoopRampPeriod)
    {
        DutyCycleOpenLoopRampPeriod = std::move(newDutyCycleOpenLoopRampPeriod);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's VoltageOpenLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0V output
     * to 12V during the open-loop VoltageOut control mode.
     * 
     * This provides an easy way to limit the acceleration of the motor.
     * However, the acceleration and current draw of the motor can be
     * better restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newVoltageOpenLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr OpenLoopRampsConfigs &WithVoltageOpenLoopRampPeriod(units::time::second_t newVoltageOpenLoopRampPeriod)
    {
        VoltageOpenLoopRampPeriod = std::move(newVoltageOpenLoopRampPeriod);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's TorqueOpenLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0A output
     * to 300A during the open-loop TorqueCurrent control mode.
     * 
     * Since TorqueCurrent is directly proportional to acceleration, this
     * ramp limits jerk instead of acceleration.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 10
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newTorqueOpenLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr OpenLoopRampsConfigs &WithTorqueOpenLoopRampPeriod(units::time::second_t newTorqueOpenLoopRampPeriod)
    {
        TorqueOpenLoopRampPeriod = std::move(newTorqueOpenLoopRampPeriod);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: OpenLoopRamps" << std::endl;
        ss << "    DutyCycleOpenLoopRampPeriod: " << DutyCycleOpenLoopRampPeriod.to<double>() << " seconds" << std::endl;
        ss << "    VoltageOpenLoopRampPeriod: " << VoltageOpenLoopRampPeriod.to<double>() << " seconds" << std::endl;
        ss << "    TorqueOpenLoopRampPeriod: " << TorqueOpenLoopRampPeriod.to<double>() << " seconds" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_DutyCycleOpenLoopRampPeriod, DutyCycleOpenLoopRampPeriod.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_VoltageOpenLoopRampPeriod, VoltageOpenLoopRampPeriod.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_TorqueOpenLoopRampPeriod, TorqueOpenLoopRampPeriod.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double DutyCycleOpenLoopRampPeriodVal = DutyCycleOpenLoopRampPeriod.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_DutyCycleOpenLoopRampPeriod, string_c_str, string_length, &DutyCycleOpenLoopRampPeriodVal);
        DutyCycleOpenLoopRampPeriod = units::time::second_t{DutyCycleOpenLoopRampPeriodVal};
        double VoltageOpenLoopRampPeriodVal = VoltageOpenLoopRampPeriod.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_VoltageOpenLoopRampPeriod, string_c_str, string_length, &VoltageOpenLoopRampPeriodVal);
        VoltageOpenLoopRampPeriod = units::time::second_t{VoltageOpenLoopRampPeriodVal};
        double TorqueOpenLoopRampPeriodVal = TorqueOpenLoopRampPeriod.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_TorqueOpenLoopRampPeriod, string_c_str, string_length, &TorqueOpenLoopRampPeriodVal);
        TorqueOpenLoopRampPeriod = units::time::second_t{TorqueOpenLoopRampPeriodVal};
        return 0;
    }
};


/**
 * \brief Configs that affect the closed-loop control of this motor
 *        controller.
 * 
 * \details Closed-loop ramp rates for the various control types.
 */
class ClosedLoopRampsConfigs : public ParentConfiguration
{
public:
    constexpr ClosedLoopRampsConfigs() = default;

    /**
     * \brief If non-zero, this determines how much time to ramp from 0%
     * output to 100% during the closed-loop DutyCycle control modes.
     * 
     * If the goal is to limit acceleration, it is more useful to ramp the
     * closed-loop setpoint instead of the output. This can be achieved
     * using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t DutyCycleClosedLoopRampPeriod = 0_s;
    /**
     * \brief If non-zero, this determines how much time to ramp from 0V
     * output to 12V during the closed-loop Voltage control modes.
     * 
     * If the goal is to limit acceleration, it is more useful to ramp the
     * closed-loop setpoint instead of the output. This can be achieved
     * using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t VoltageClosedLoopRampPeriod = 0_s;
    /**
     * \brief If non-zero, this determines how much time to ramp from 0A
     * output to 300A during the closed-loop TorqueCurrent control modes.
     * 
     * Since TorqueCurrent is directly proportional to acceleration, this
     * ramp limits jerk instead of acceleration.
     * 
     * If the goal is to limit acceleration or jerk, it is more useful to
     * ramp the closed-loop setpoint instead of the output. This can be
     * achieved using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 10
     * - Default Value: 0
     * - Units: seconds
     */
    units::time::second_t TorqueClosedLoopRampPeriod = 0_s;
    
    /**
     * \brief Modifies this configuration's DutyCycleClosedLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0% output
     * to 100% during the closed-loop DutyCycle control modes.
     * 
     * If the goal is to limit acceleration, it is more useful to ramp the
     * closed-loop setpoint instead of the output. This can be achieved
     * using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newDutyCycleClosedLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr ClosedLoopRampsConfigs &WithDutyCycleClosedLoopRampPeriod(units::time::second_t newDutyCycleClosedLoopRampPeriod)
    {
        DutyCycleClosedLoopRampPeriod = std::move(newDutyCycleClosedLoopRampPeriod);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's VoltageClosedLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0V output
     * to 12V during the closed-loop Voltage control modes.
     * 
     * If the goal is to limit acceleration, it is more useful to ramp the
     * closed-loop setpoint instead of the output. This can be achieved
     * using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newVoltageClosedLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr ClosedLoopRampsConfigs &WithVoltageClosedLoopRampPeriod(units::time::second_t newVoltageClosedLoopRampPeriod)
    {
        VoltageClosedLoopRampPeriod = std::move(newVoltageClosedLoopRampPeriod);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's TorqueClosedLoopRampPeriod parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If non-zero, this determines how much time to ramp from 0A output
     * to 300A during the closed-loop TorqueCurrent control modes.
     * 
     * Since TorqueCurrent is directly proportional to acceleration, this
     * ramp limits jerk instead of acceleration.
     * 
     * If the goal is to limit acceleration or jerk, it is more useful to
     * ramp the closed-loop setpoint instead of the output. This can be
     * achieved using Motion Magic® controls.
     * 
     * The acceleration and current draw of the motor can also be better
     * restricted using current limits instead of a ramp rate.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 10
     * - Default Value: 0
     * - Units: seconds
     *
     * \param newTorqueClosedLoopRampPeriod Parameter to modify
     * \returns Itself
     */
    constexpr ClosedLoopRampsConfigs &WithTorqueClosedLoopRampPeriod(units::time::second_t newTorqueClosedLoopRampPeriod)
    {
        TorqueClosedLoopRampPeriod = std::move(newTorqueClosedLoopRampPeriod);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: ClosedLoopRamps" << std::endl;
        ss << "    DutyCycleClosedLoopRampPeriod: " << DutyCycleClosedLoopRampPeriod.to<double>() << " seconds" << std::endl;
        ss << "    VoltageClosedLoopRampPeriod: " << VoltageClosedLoopRampPeriod.to<double>() << " seconds" << std::endl;
        ss << "    TorqueClosedLoopRampPeriod: " << TorqueClosedLoopRampPeriod.to<double>() << " seconds" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_DutyCycleClosedLoopRampPeriod, DutyCycleClosedLoopRampPeriod.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_VoltageClosedLoopRampPeriod, VoltageClosedLoopRampPeriod.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_TorqueClosedLoopRampPeriod, TorqueClosedLoopRampPeriod.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double DutyCycleClosedLoopRampPeriodVal = DutyCycleClosedLoopRampPeriod.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_DutyCycleClosedLoopRampPeriod, string_c_str, string_length, &DutyCycleClosedLoopRampPeriodVal);
        DutyCycleClosedLoopRampPeriod = units::time::second_t{DutyCycleClosedLoopRampPeriodVal};
        double VoltageClosedLoopRampPeriodVal = VoltageClosedLoopRampPeriod.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_VoltageClosedLoopRampPeriod, string_c_str, string_length, &VoltageClosedLoopRampPeriodVal);
        VoltageClosedLoopRampPeriod = units::time::second_t{VoltageClosedLoopRampPeriodVal};
        double TorqueClosedLoopRampPeriodVal = TorqueClosedLoopRampPeriod.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_TorqueClosedLoopRampPeriod, string_c_str, string_length, &TorqueClosedLoopRampPeriodVal);
        TorqueClosedLoopRampPeriod = units::time::second_t{TorqueClosedLoopRampPeriodVal};
        return 0;
    }
};


/**
 * \brief Configs that change how the motor controller behaves under
 *        different limit switch states.
 * 
 * \details Includes configs such as enabling limit switches,
 *          configuring the remote sensor ID, the source, and the
 *          position to set on limit.
 */
class HardwareLimitSwitchConfigs : public ParentConfiguration
{
public:
    constexpr HardwareLimitSwitchConfigs() = default;

    /**
     * \brief Determines if the forward limit switch is normally-open
     * (default) or normally-closed.
     * 
     */
    signals::ForwardLimitTypeValue ForwardLimitType = signals::ForwardLimitTypeValue::NormallyOpen;
    /**
     * \brief If enabled, the position is automatically set to a specific
     * value, specified by ForwardLimitAutosetPositionValue, when the
     * forward limit switch is asserted.
     * 
     * - Default Value: False
     */
    bool ForwardLimitAutosetPositionEnable = false;
    /**
     * \brief The value to automatically set the position to when the
     * forward limit switch is asserted.  This has no effect if
     * ForwardLimitAutosetPositionEnable is false.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     */
    units::angle::turn_t ForwardLimitAutosetPositionValue = 0_tr;
    /**
     * \brief If enabled, motor output is set to neutral when the forward
     * limit switch is asserted and positive output is requested.
     * 
     * - Default Value: True
     */
    bool ForwardLimitEnable = true;
    /**
     * \brief Determines where to poll the forward limit switch.  This
     * defaults to the forward limit switch pin on the limit switch
     * connector.
     * 
     * Choose RemoteTalonFX to use the forward limit switch attached to
     * another Talon FX on the same CAN bus (this also requires setting
     * ForwardLimitRemoteSensorID).
     * 
     * Choose RemoteCANifier to use the forward limit switch attached to
     * another CANifier on the same CAN bus (this also requires setting
     * ForwardLimitRemoteSensorID).
     * 
     * Choose RemoteCANcoder to use another CANcoder on the same CAN bus
     * (this also requires setting ForwardLimitRemoteSensorID).  The
     * forward limit will assert when the CANcoder magnet strength changes
     * from BAD (red) to ADEQUATE (orange) or GOOD (green).
     * 
     */
    signals::ForwardLimitSourceValue ForwardLimitSource = signals::ForwardLimitSourceValue::LimitSwitchPin;
    /**
     * \brief Device ID of the remote device if using remote limit switch
     * features for the forward limit switch.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 62
     * - Default Value: 0
     * - Units: 
     */
    int ForwardLimitRemoteSensorID = 0;
    /**
     * \brief Determines if the reverse limit switch is normally-open
     * (default) or normally-closed.
     * 
     */
    signals::ReverseLimitTypeValue ReverseLimitType = signals::ReverseLimitTypeValue::NormallyOpen;
    /**
     * \brief If enabled, the position is automatically set to a specific
     * value, specified by ReverseLimitAutosetPositionValue, when the
     * reverse limit switch is asserted.
     * 
     * - Default Value: False
     */
    bool ReverseLimitAutosetPositionEnable = false;
    /**
     * \brief The value to automatically set the position to when the
     * reverse limit switch is asserted.  This has no effect if
     * ReverseLimitAutosetPositionEnable is false.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     */
    units::angle::turn_t ReverseLimitAutosetPositionValue = 0_tr;
    /**
     * \brief If enabled, motor output is set to neutral when reverse
     * limit switch is asseted and negative output is requested.
     * 
     * - Default Value: True
     */
    bool ReverseLimitEnable = true;
    /**
     * \brief Determines where to poll the reverse limit switch.  This
     * defaults to the reverse limit switch pin on the limit switch
     * connector.
     * 
     * Choose RemoteTalonFX to use the reverse limit switch attached to
     * another Talon FX on the same CAN bus (this also requires setting
     * ReverseLimitRemoteSensorID).
     * 
     * Choose RemoteCANifier to use the reverse limit switch attached to
     * another CANifier on the same CAN bus (this also requires setting
     * ReverseLimitRemoteSensorID).
     * 
     * Choose RemoteCANcoder to use another CANcoder on the same CAN bus
     * (this also requires setting ReverseLimitRemoteSensorID).  The
     * reverse limit will assert when the CANcoder magnet strength changes
     * from BAD (red) to ADEQUATE (orange) or GOOD (green).
     * 
     */
    signals::ReverseLimitSourceValue ReverseLimitSource = signals::ReverseLimitSourceValue::LimitSwitchPin;
    /**
     * \brief Device ID of the remote device if using remote limit switch
     * features for the reverse limit switch.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 62
     * - Default Value: 0
     * - Units: 
     */
    int ReverseLimitRemoteSensorID = 0;
    
    /**
     * \brief Modifies this configuration's ForwardLimitType parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Determines if the forward limit switch is normally-open (default)
     * or normally-closed.
     * 
     *
     * \param newForwardLimitType Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithForwardLimitType(signals::ForwardLimitTypeValue newForwardLimitType)
    {
        ForwardLimitType = std::move(newForwardLimitType);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ForwardLimitAutosetPositionEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If enabled, the position is automatically set to a specific value,
     * specified by ForwardLimitAutosetPositionValue, when the forward
     * limit switch is asserted.
     * 
     * - Default Value: False
     *
     * \param newForwardLimitAutosetPositionEnable Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithForwardLimitAutosetPositionEnable(bool newForwardLimitAutosetPositionEnable)
    {
        ForwardLimitAutosetPositionEnable = std::move(newForwardLimitAutosetPositionEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ForwardLimitAutosetPositionValue parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The value to automatically set the position to when the forward
     * limit switch is asserted.  This has no effect if
     * ForwardLimitAutosetPositionEnable is false.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     *
     * \param newForwardLimitAutosetPositionValue Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithForwardLimitAutosetPositionValue(units::angle::turn_t newForwardLimitAutosetPositionValue)
    {
        ForwardLimitAutosetPositionValue = std::move(newForwardLimitAutosetPositionValue);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ForwardLimitEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If enabled, motor output is set to neutral when the forward limit
     * switch is asserted and positive output is requested.
     * 
     * - Default Value: True
     *
     * \param newForwardLimitEnable Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithForwardLimitEnable(bool newForwardLimitEnable)
    {
        ForwardLimitEnable = std::move(newForwardLimitEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ForwardLimitSource parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Determines where to poll the forward limit switch.  This defaults
     * to the forward limit switch pin on the limit switch connector.
     * 
     * Choose RemoteTalonFX to use the forward limit switch attached to
     * another Talon FX on the same CAN bus (this also requires setting
     * ForwardLimitRemoteSensorID).
     * 
     * Choose RemoteCANifier to use the forward limit switch attached to
     * another CANifier on the same CAN bus (this also requires setting
     * ForwardLimitRemoteSensorID).
     * 
     * Choose RemoteCANcoder to use another CANcoder on the same CAN bus
     * (this also requires setting ForwardLimitRemoteSensorID).  The
     * forward limit will assert when the CANcoder magnet strength changes
     * from BAD (red) to ADEQUATE (orange) or GOOD (green).
     * 
     *
     * \param newForwardLimitSource Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithForwardLimitSource(signals::ForwardLimitSourceValue newForwardLimitSource)
    {
        ForwardLimitSource = std::move(newForwardLimitSource);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ForwardLimitRemoteSensorID parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Device ID of the remote device if using remote limit switch
     * features for the forward limit switch.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 62
     * - Default Value: 0
     * - Units: 
     *
     * \param newForwardLimitRemoteSensorID Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithForwardLimitRemoteSensorID(int newForwardLimitRemoteSensorID)
    {
        ForwardLimitRemoteSensorID = std::move(newForwardLimitRemoteSensorID);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ReverseLimitType parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Determines if the reverse limit switch is normally-open (default)
     * or normally-closed.
     * 
     *
     * \param newReverseLimitType Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithReverseLimitType(signals::ReverseLimitTypeValue newReverseLimitType)
    {
        ReverseLimitType = std::move(newReverseLimitType);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ReverseLimitAutosetPositionEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If enabled, the position is automatically set to a specific value,
     * specified by ReverseLimitAutosetPositionValue, when the reverse
     * limit switch is asserted.
     * 
     * - Default Value: False
     *
     * \param newReverseLimitAutosetPositionEnable Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithReverseLimitAutosetPositionEnable(bool newReverseLimitAutosetPositionEnable)
    {
        ReverseLimitAutosetPositionEnable = std::move(newReverseLimitAutosetPositionEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ReverseLimitAutosetPositionValue parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The value to automatically set the position to when the reverse
     * limit switch is asserted.  This has no effect if
     * ReverseLimitAutosetPositionEnable is false.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     *
     * \param newReverseLimitAutosetPositionValue Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithReverseLimitAutosetPositionValue(units::angle::turn_t newReverseLimitAutosetPositionValue)
    {
        ReverseLimitAutosetPositionValue = std::move(newReverseLimitAutosetPositionValue);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ReverseLimitEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If enabled, motor output is set to neutral when reverse limit
     * switch is asseted and negative output is requested.
     * 
     * - Default Value: True
     *
     * \param newReverseLimitEnable Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithReverseLimitEnable(bool newReverseLimitEnable)
    {
        ReverseLimitEnable = std::move(newReverseLimitEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ReverseLimitSource parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Determines where to poll the reverse limit switch.  This defaults
     * to the reverse limit switch pin on the limit switch connector.
     * 
     * Choose RemoteTalonFX to use the reverse limit switch attached to
     * another Talon FX on the same CAN bus (this also requires setting
     * ReverseLimitRemoteSensorID).
     * 
     * Choose RemoteCANifier to use the reverse limit switch attached to
     * another CANifier on the same CAN bus (this also requires setting
     * ReverseLimitRemoteSensorID).
     * 
     * Choose RemoteCANcoder to use another CANcoder on the same CAN bus
     * (this also requires setting ReverseLimitRemoteSensorID).  The
     * reverse limit will assert when the CANcoder magnet strength changes
     * from BAD (red) to ADEQUATE (orange) or GOOD (green).
     * 
     *
     * \param newReverseLimitSource Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithReverseLimitSource(signals::ReverseLimitSourceValue newReverseLimitSource)
    {
        ReverseLimitSource = std::move(newReverseLimitSource);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ReverseLimitRemoteSensorID parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Device ID of the remote device if using remote limit switch
     * features for the reverse limit switch.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 62
     * - Default Value: 0
     * - Units: 
     *
     * \param newReverseLimitRemoteSensorID Parameter to modify
     * \returns Itself
     */
    constexpr HardwareLimitSwitchConfigs &WithReverseLimitRemoteSensorID(int newReverseLimitRemoteSensorID)
    {
        ReverseLimitRemoteSensorID = std::move(newReverseLimitRemoteSensorID);
        return *this;
    }
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteTalonFX forward limit switch by passing in the TalonFX
     *        object. When using RemoteTalonFX, the Talon FX will use the
     *        forward limit switch attached to another Talon FX on the
     *        same CAN bus.
     * 
     * \param device TalonFX reference to use for RemoteTalonFX forward limit switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithForwardLimitRemoteTalonFX(const hardware::core::CoreTalonFX& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANcoder forward limit switch by passing in the
     *        CANcoder object. When using RemoteCANcoder, the Talon FX
     *        will use another CANcoder on the same CAN bus. The forward
     *        limit will assert when the CANcoder magnet strength changes
     *        from BAD (red) to ADEQUATE (orange) or GOOD (green).
     * 
     * \param device CANcoder reference to use for RemoteCANcoder forward limit switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithForwardLimitRemoteCANcoder(const hardware::core::CoreCANcoder& device);
    
    /**
     * \brief Helper method to configure this feedback group to use the
     *        RemoteCANrange by passing in the CANrange object. The
     *        forward limit will assert when the CANrange proximity detect
     *        is tripped.
     * 
     * \param device CANrange reference to use for RemoteCANrange forward limit switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithForwardLimitRemoteCANrange(const hardware::core::CoreCANrange& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANdi forward limit switch on Signal 1 Input (S1IN) by
     *        passing in the CANdi object. The forward limit will assert
     *        when the CANdi™ branded device's Signal 1 Input (S1IN) pin
     *        matches the configured closed state.
     * 
     * \param device CANdi reference to use for RemoteCANdi forward limit switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithForwardLimitRemoteCANdiS1(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANdi forward limit switch on Signal 2 Input (S2IN) by
     *        passing in the CANdi object. The forward limit will assert
     *        when the CANdi™ branded device's Signal 2 Input (S2IN) pin
     *        matches the configured closed state.
     * 
     * \param device CANdi reference to use for RemoteCANdi forward limit switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithForwardLimitRemoteCANdiS2(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteTalonFX reverse limit switch by passing in the TalonFX
     *        object. When using RemoteTalonFX, the Talon FX will use the
     *        reverse limit switch attached to another Talon FX on the
     *        same CAN bus.
     * 
     * \param device TalonFX reference to use for RemoteTalonFX reverse limit switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithReverseLimitRemoteTalonFX(const hardware::core::CoreTalonFX& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANcoder reverse limit switch by passing in the
     *        CANcoder object. When using RemoteCANcoder, the Talon FX
     *        will use another CANcoder on the same CAN bus. The reverse
     *        limit will assert when the CANcoder magnet strength changes
     *        from BAD (red) to ADEQUATE (orange) or GOOD (green).
     * 
     * \param device CANcoder reference to use for RemoteCANcoder reverse limit switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithReverseLimitRemoteCANcoder(const hardware::core::CoreCANcoder& device);
    
    /**
     * \brief Helper method to configure this feedback group to use the
     *        RemoteCANrange by passing in the CANrange object. The
     *        reverse limit will assert when the CANrange proximity detect
     *        is tripped.
     * 
     * \param device CANrange reference to use for RemoteCANrange reverse limit switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithReverseLimitRemoteCANrange(const hardware::core::CoreCANrange& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANdi reverse limit switch on Signal 1 Input (S1IN) by
     *        passing in the CANdi object. The reverse limit will assert
     *        when the CANdi™ branded device's Signal 1 Input (S1IN) pin
     *        matches the configured closed state.
     * 
     * \param device CANdi reference to use for RemoteCANdi reverse limit switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithReverseLimitRemoteCANdiS1(const hardware::core::CoreCANdi& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANdi reverse limit switch on Signal 2 Input (S2IN) by
     *        passing in the CANdi object. The reverse limit will assert
     *        when the CANdi™ branded device's Signal 2 Input (S2IN) pin
     *        matches the configured closed state.
     * 
     * \param device CANdi reference to use for RemoteCANdi reverse limit switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithReverseLimitRemoteCANdiS2(const hardware::core::CoreCANdi& device);
    
    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: HardwareLimitSwitch" << std::endl;
        ss << "    ForwardLimitType: " << ForwardLimitType << std::endl;
        ss << "    ForwardLimitAutosetPositionEnable: " << ForwardLimitAutosetPositionEnable << std::endl;
        ss << "    ForwardLimitAutosetPositionValue: " << ForwardLimitAutosetPositionValue.to<double>() << " rotations" << std::endl;
        ss << "    ForwardLimitEnable: " << ForwardLimitEnable << std::endl;
        ss << "    ForwardLimitSource: " << ForwardLimitSource << std::endl;
        ss << "    ForwardLimitRemoteSensorID: " << ForwardLimitRemoteSensorID << std::endl;
        ss << "    ReverseLimitType: " << ReverseLimitType << std::endl;
        ss << "    ReverseLimitAutosetPositionEnable: " << ReverseLimitAutosetPositionEnable << std::endl;
        ss << "    ReverseLimitAutosetPositionValue: " << ReverseLimitAutosetPositionValue.to<double>() << " rotations" << std::endl;
        ss << "    ReverseLimitEnable: " << ReverseLimitEnable << std::endl;
        ss << "    ReverseLimitSource: " << ReverseLimitSource << std::endl;
        ss << "    ReverseLimitRemoteSensorID: " << ReverseLimitRemoteSensorID << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitType, ForwardLimitType.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitAutosetPosEnable, ForwardLimitAutosetPositionEnable, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitAutosetPosValue, ForwardLimitAutosetPositionValue.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitEnable, ForwardLimitEnable, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitSource, ForwardLimitSource.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitRemoteSensorID, ForwardLimitRemoteSensorID, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitType, ReverseLimitType.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitAutosetPosEnable, ReverseLimitAutosetPositionEnable, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitAutosetPosValue, ReverseLimitAutosetPositionValue.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitEnable, ReverseLimitEnable, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitSource, ReverseLimitSource.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitRemoteSensorID, ReverseLimitRemoteSensorID, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitType, string_c_str, string_length, &ForwardLimitType.value);
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitAutosetPosEnable, string_c_str, string_length, &ForwardLimitAutosetPositionEnable);
        double ForwardLimitAutosetPositionValueVal = ForwardLimitAutosetPositionValue.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitAutosetPosValue, string_c_str, string_length, &ForwardLimitAutosetPositionValueVal);
        ForwardLimitAutosetPositionValue = units::angle::turn_t{ForwardLimitAutosetPositionValueVal};
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitEnable, string_c_str, string_length, &ForwardLimitEnable);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitSource, string_c_str, string_length, &ForwardLimitSource.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_ForwardLimitRemoteSensorID, string_c_str, string_length, &ForwardLimitRemoteSensorID);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitType, string_c_str, string_length, &ReverseLimitType.value);
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitAutosetPosEnable, string_c_str, string_length, &ReverseLimitAutosetPositionEnable);
        double ReverseLimitAutosetPositionValueVal = ReverseLimitAutosetPositionValue.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitAutosetPosValue, string_c_str, string_length, &ReverseLimitAutosetPositionValueVal);
        ReverseLimitAutosetPositionValue = units::angle::turn_t{ReverseLimitAutosetPositionValueVal};
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitEnable, string_c_str, string_length, &ReverseLimitEnable);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitSource, string_c_str, string_length, &ReverseLimitSource.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_ReverseLimitRemoteSensorID, string_c_str, string_length, &ReverseLimitRemoteSensorID);
        return 0;
    }
};


/**
 * \brief Configs that affect audible components of the device.
 * 
 * \details Includes configuration for the beep on boot.
 */
class AudioConfigs : public ParentConfiguration
{
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

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: Audio" << std::endl;
        ss << "    BeepOnBoot: " << BeepOnBoot << std::endl;
        ss << "    BeepOnConfig: " << BeepOnConfig << std::endl;
        ss << "    AllowMusicDurDisable: " << AllowMusicDurDisable << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_BeepOnBoot, BeepOnBoot, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_BeepOnConfig, BeepOnConfig, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_AllowMusicDurDisable, AllowMusicDurDisable, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_BeepOnBoot, string_c_str, string_length, &BeepOnBoot);
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_BeepOnConfig, string_c_str, string_length, &BeepOnConfig);
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_AllowMusicDurDisable, string_c_str, string_length, &AllowMusicDurDisable);
        return 0;
    }
};


/**
 * \brief Configs that affect how software-limit switches behave.
 * 
 * \details Includes enabling software-limit switches and the
 *          threshold at which they are tripped.
 */
class SoftwareLimitSwitchConfigs : public ParentConfiguration
{
public:
    constexpr SoftwareLimitSwitchConfigs() = default;

    /**
     * \brief If enabled, the motor output is set to neutral if position
     * exceeds ForwardSoftLimitThreshold and forward output is requested.
     * 
     * - Default Value: False
     */
    bool ForwardSoftLimitEnable = false;
    /**
     * \brief If enabled, the motor output is set to neutral if position
     * exceeds ReverseSoftLimitThreshold and reverse output is requested.
     * 
     * - Default Value: False
     */
    bool ReverseSoftLimitEnable = false;
    /**
     * \brief Position threshold for forward soft limit features.
     * ForwardSoftLimitEnable must be enabled for this to take effect.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     */
    units::angle::turn_t ForwardSoftLimitThreshold = 0_tr;
    /**
     * \brief Position threshold for reverse soft limit features.
     * ReverseSoftLimitEnable must be enabled for this to take effect.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     */
    units::angle::turn_t ReverseSoftLimitThreshold = 0_tr;
    
    /**
     * \brief Modifies this configuration's ForwardSoftLimitEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If enabled, the motor output is set to neutral if position exceeds
     * ForwardSoftLimitThreshold and forward output is requested.
     * 
     * - Default Value: False
     *
     * \param newForwardSoftLimitEnable Parameter to modify
     * \returns Itself
     */
    constexpr SoftwareLimitSwitchConfigs &WithForwardSoftLimitEnable(bool newForwardSoftLimitEnable)
    {
        ForwardSoftLimitEnable = std::move(newForwardSoftLimitEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ReverseSoftLimitEnable parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * If enabled, the motor output is set to neutral if position exceeds
     * ReverseSoftLimitThreshold and reverse output is requested.
     * 
     * - Default Value: False
     *
     * \param newReverseSoftLimitEnable Parameter to modify
     * \returns Itself
     */
    constexpr SoftwareLimitSwitchConfigs &WithReverseSoftLimitEnable(bool newReverseSoftLimitEnable)
    {
        ReverseSoftLimitEnable = std::move(newReverseSoftLimitEnable);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ForwardSoftLimitThreshold parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Position threshold for forward soft limit features.
     * ForwardSoftLimitEnable must be enabled for this to take effect.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     *
     * \param newForwardSoftLimitThreshold Parameter to modify
     * \returns Itself
     */
    constexpr SoftwareLimitSwitchConfigs &WithForwardSoftLimitThreshold(units::angle::turn_t newForwardSoftLimitThreshold)
    {
        ForwardSoftLimitThreshold = std::move(newForwardSoftLimitThreshold);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ReverseSoftLimitThreshold parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Position threshold for reverse soft limit features.
     * ReverseSoftLimitEnable must be enabled for this to take effect.
     * 
     * - Minimum Value: -3.4e+38
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: rotations
     *
     * \param newReverseSoftLimitThreshold Parameter to modify
     * \returns Itself
     */
    constexpr SoftwareLimitSwitchConfigs &WithReverseSoftLimitThreshold(units::angle::turn_t newReverseSoftLimitThreshold)
    {
        ReverseSoftLimitThreshold = std::move(newReverseSoftLimitThreshold);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: SoftwareLimitSwitch" << std::endl;
        ss << "    ForwardSoftLimitEnable: " << ForwardSoftLimitEnable << std::endl;
        ss << "    ReverseSoftLimitEnable: " << ReverseSoftLimitEnable << std::endl;
        ss << "    ForwardSoftLimitThreshold: " << ForwardSoftLimitThreshold.to<double>() << " rotations" << std::endl;
        ss << "    ReverseSoftLimitThreshold: " << ReverseSoftLimitThreshold.to<double>() << " rotations" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_ForwardSoftLimitEnable, ForwardSoftLimitEnable, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_ReverseSoftLimitEnable, ReverseSoftLimitEnable, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_ForwardSoftLimitThreshold, ForwardSoftLimitThreshold.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_ReverseSoftLimitThreshold, ReverseSoftLimitThreshold.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_ForwardSoftLimitEnable, string_c_str, string_length, &ForwardSoftLimitEnable);
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_ReverseSoftLimitEnable, string_c_str, string_length, &ReverseSoftLimitEnable);
        double ForwardSoftLimitThresholdVal = ForwardSoftLimitThreshold.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_ForwardSoftLimitThreshold, string_c_str, string_length, &ForwardSoftLimitThresholdVal);
        ForwardSoftLimitThreshold = units::angle::turn_t{ForwardSoftLimitThresholdVal};
        double ReverseSoftLimitThresholdVal = ReverseSoftLimitThreshold.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_ReverseSoftLimitThreshold, string_c_str, string_length, &ReverseSoftLimitThresholdVal);
        ReverseSoftLimitThreshold = units::angle::turn_t{ReverseSoftLimitThresholdVal};
        return 0;
    }
};


/**
 * \brief Configs for Motion Magic®.
 * 
 * \details Includes Velocity, Acceleration, Jerk, and Expo
 *          parameters.
 */
class MotionMagicConfigs : public ParentConfiguration
{
public:
    constexpr MotionMagicConfigs() = default;

    /**
     * \brief This is the maximum velocity Motion Magic® based control
     * modes are allowed to use.  Motion Magic® Velocity control modes do
     * not use this config.
     * 
     * When using Motion Magic® Expo control modes, setting this to 0 will
     * allow the profile to run to the max possible velocity based on
     * Expo_kV.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec
     */
    units::angular_velocity::turns_per_second_t MotionMagicCruiseVelocity = 0_tps;
    /**
     * \brief This is the target acceleration Motion Magic® based control
     * modes are allowed to use.  Motion Magic® Expo control modes do not
     * use this config.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec²
     */
    units::angular_acceleration::turns_per_second_squared_t MotionMagicAcceleration = 0_tr_per_s_sq;
    /**
     * \brief This is the target jerk (acceleration derivative) Motion
     * Magic® based control modes are allowed to use.  Motion Magic® Expo
     * control modes do not use this config.  This allows Motion Magic® to
     * generate S-Curve profiles.
     * 
     * Jerk is optional; if this is set to zero, then Motion Magic® will
     * not apply a Jerk limit.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec³
     */
    units::angular_jerk::turns_per_second_cubed_t MotionMagicJerk = 0_tr_per_s_cu;
    /**
     * \brief This is the target kV used only by Motion Magic® Expo
     * control modes. Unlike the kV slot gain, this is always in units of
     * V/rps.
     * 
     * This represents the amount of voltage necessary to hold a velocity.
     * In terms of the Motion Magic® Expo profile, a higher kV results in
     * a slower maximum velocity.
     * 
     * - Minimum Value: 0.001
     * - Maximum Value: 100
     * - Default Value: 0.12
     * - Units: V/rps
     */
    ctre::unit::volts_per_turn_per_second_t MotionMagicExpo_kV = 0.12_V / 1_tps;
    /**
     * \brief This is the target kA used only by Motion Magic® Expo
     * control modes. Unlike the kA slot gain, this is always in units of
     * V/rps².
     * 
     * This represents the amount of voltage necessary to achieve an
     * acceleration. In terms of the Motion Magic® Expo profile, a higher
     * kA results in a slower acceleration.
     * 
     * - Minimum Value: 1e-05
     * - Maximum Value: 100
     * - Default Value: 0.1
     * - Units: V/rps²
     */
    ctre::unit::volts_per_turn_per_second_squared_t MotionMagicExpo_kA = 0.1_V / 1_tr_per_s_sq;
    
    /**
     * \brief Modifies this configuration's MotionMagicCruiseVelocity parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This is the maximum velocity Motion Magic® based control modes are
     * allowed to use.  Motion Magic® Velocity control modes do not use
     * this config.
     * 
     * When using Motion Magic® Expo control modes, setting this to 0 will
     * allow the profile to run to the max possible velocity based on
     * Expo_kV.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec
     *
     * \param newMotionMagicCruiseVelocity Parameter to modify
     * \returns Itself
     */
    constexpr MotionMagicConfigs &WithMotionMagicCruiseVelocity(units::angular_velocity::turns_per_second_t newMotionMagicCruiseVelocity)
    {
        MotionMagicCruiseVelocity = std::move(newMotionMagicCruiseVelocity);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MotionMagicAcceleration parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This is the target acceleration Motion Magic® based control modes
     * are allowed to use.  Motion Magic® Expo control modes do not use
     * this config.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec²
     *
     * \param newMotionMagicAcceleration Parameter to modify
     * \returns Itself
     */
    constexpr MotionMagicConfigs &WithMotionMagicAcceleration(units::angular_acceleration::turns_per_second_squared_t newMotionMagicAcceleration)
    {
        MotionMagicAcceleration = std::move(newMotionMagicAcceleration);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MotionMagicJerk parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This is the target jerk (acceleration derivative) Motion Magic®
     * based control modes are allowed to use.  Motion Magic® Expo control
     * modes do not use this config.  This allows Motion Magic® to
     * generate S-Curve profiles.
     * 
     * Jerk is optional; if this is set to zero, then Motion Magic® will
     * not apply a Jerk limit.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 9999
     * - Default Value: 0
     * - Units: rot per sec³
     *
     * \param newMotionMagicJerk Parameter to modify
     * \returns Itself
     */
    constexpr MotionMagicConfigs &WithMotionMagicJerk(units::angular_jerk::turns_per_second_cubed_t newMotionMagicJerk)
    {
        MotionMagicJerk = std::move(newMotionMagicJerk);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MotionMagicExpo_kV parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This is the target kV used only by Motion Magic® Expo control
     * modes. Unlike the kV slot gain, this is always in units of V/rps.
     * 
     * This represents the amount of voltage necessary to hold a velocity.
     * In terms of the Motion Magic® Expo profile, a higher kV results in
     * a slower maximum velocity.
     * 
     * - Minimum Value: 0.001
     * - Maximum Value: 100
     * - Default Value: 0.12
     * - Units: V/rps
     *
     * \param newMotionMagicExpo_kV Parameter to modify
     * \returns Itself
     */
    constexpr MotionMagicConfigs &WithMotionMagicExpo_kV(ctre::unit::volts_per_turn_per_second_t newMotionMagicExpo_kV)
    {
        MotionMagicExpo_kV = std::move(newMotionMagicExpo_kV);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MotionMagicExpo_kA parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * This is the target kA used only by Motion Magic® Expo control
     * modes. Unlike the kA slot gain, this is always in units of V/rps².
     * 
     * This represents the amount of voltage necessary to achieve an
     * acceleration. In terms of the Motion Magic® Expo profile, a higher
     * kA results in a slower acceleration.
     * 
     * - Minimum Value: 1e-05
     * - Maximum Value: 100
     * - Default Value: 0.1
     * - Units: V/rps²
     *
     * \param newMotionMagicExpo_kA Parameter to modify
     * \returns Itself
     */
    constexpr MotionMagicConfigs &WithMotionMagicExpo_kA(ctre::unit::volts_per_turn_per_second_squared_t newMotionMagicExpo_kA)
    {
        MotionMagicExpo_kA = std::move(newMotionMagicExpo_kA);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: MotionMagic" << std::endl;
        ss << "    MotionMagicCruiseVelocity: " << MotionMagicCruiseVelocity.to<double>() << " rot per sec" << std::endl;
        ss << "    MotionMagicAcceleration: " << MotionMagicAcceleration.to<double>() << " rot per sec²" << std::endl;
        ss << "    MotionMagicJerk: " << MotionMagicJerk.to<double>() << " rot per sec³" << std::endl;
        ss << "    MotionMagicExpo_kV: " << MotionMagicExpo_kV.to<double>() << " V/rps" << std::endl;
        ss << "    MotionMagicExpo_kA: " << MotionMagicExpo_kA.to<double>() << " V/rps²" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_MotionMagicCruiseVelocity, MotionMagicCruiseVelocity.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_MotionMagicAcceleration, MotionMagicAcceleration.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_MotionMagicJerk, MotionMagicJerk.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_MotionMagicExpo_kV, MotionMagicExpo_kV.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_MotionMagicExpo_kA, MotionMagicExpo_kA.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double MotionMagicCruiseVelocityVal = MotionMagicCruiseVelocity.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_MotionMagicCruiseVelocity, string_c_str, string_length, &MotionMagicCruiseVelocityVal);
        MotionMagicCruiseVelocity = units::angular_velocity::turns_per_second_t{MotionMagicCruiseVelocityVal};
        double MotionMagicAccelerationVal = MotionMagicAcceleration.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_MotionMagicAcceleration, string_c_str, string_length, &MotionMagicAccelerationVal);
        MotionMagicAcceleration = units::angular_acceleration::turns_per_second_squared_t{MotionMagicAccelerationVal};
        double MotionMagicJerkVal = MotionMagicJerk.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_MotionMagicJerk, string_c_str, string_length, &MotionMagicJerkVal);
        MotionMagicJerk = units::angular_jerk::turns_per_second_cubed_t{MotionMagicJerkVal};
        double MotionMagicExpo_kVVal = MotionMagicExpo_kV.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_MotionMagicExpo_kV, string_c_str, string_length, &MotionMagicExpo_kVVal);
        MotionMagicExpo_kV = ctre::unit::volts_per_turn_per_second_t{MotionMagicExpo_kVVal};
        double MotionMagicExpo_kAVal = MotionMagicExpo_kA.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_MotionMagicExpo_kA, string_c_str, string_length, &MotionMagicExpo_kAVal);
        MotionMagicExpo_kA = ctre::unit::volts_per_turn_per_second_squared_t{MotionMagicExpo_kAVal};
        return 0;
    }
};


/**
 * \brief Custom Params.
 * 
 * \details Custom paramaters that have no real impact on controller.
 */
class CustomParamsConfigs : public ParentConfiguration
{
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

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: CustomParams" << std::endl;
        ss << "    CustomParam0: " << CustomParam0 << std::endl;
        ss << "    CustomParam1: " << CustomParam1 << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::CustomParam0, CustomParam0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::CustomParam1, CustomParam1, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::CustomParam0, string_c_str, string_length, &CustomParam0);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::CustomParam1, string_c_str, string_length, &CustomParam1);
        return 0;
    }
};


/**
 * \brief Configs that affect general behavior during closed-looping.
 * 
 * \details Includes Continuous Wrap features.
 */
class ClosedLoopGeneralConfigs : public ParentConfiguration
{
public:
    constexpr ClosedLoopGeneralConfigs() = default;

    /**
     * \brief Wrap position error within [-0.5,+0.5) mechanism rotations. 
     * Typically used for continuous position closed-loops like swerve
     * azimuth.
     * 
     * \details This uses the mechanism rotation value. If there is a gear
     * ratio between the sensor and the mechanism, make sure to apply a
     * SensorToMechanismRatio so the closed loop operates on the full
     * rotation.
     * 
     * - Default Value: False
     */
    bool ContinuousWrap = false;
    
    /**
     * \brief Modifies this configuration's ContinuousWrap parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Wrap position error within [-0.5,+0.5) mechanism rotations. 
     * Typically used for continuous position closed-loops like swerve
     * azimuth.
     * 
     * \details This uses the mechanism rotation value. If there is a gear
     * ratio between the sensor and the mechanism, make sure to apply a
     * SensorToMechanismRatio so the closed loop operates on the full
     * rotation.
     * 
     * - Default Value: False
     *
     * \param newContinuousWrap Parameter to modify
     * \returns Itself
     */
    constexpr ClosedLoopGeneralConfigs &WithContinuousWrap(bool newContinuousWrap)
    {
        ContinuousWrap = std::move(newContinuousWrap);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: ClosedLoopGeneral" << std::endl;
        ss << "    ContinuousWrap: " << ContinuousWrap << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_ContinuousWrap, ContinuousWrap, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_ContinuousWrap, string_c_str, string_length, &ContinuousWrap);
        return 0;
    }
};


/**
 * \brief Configs that affect the ToF sensor
 * 
 * \details Includes Update mode and frequency
 */
class ToFParamsConfigs : public ParentConfiguration
{
public:
    constexpr ToFParamsConfigs() = default;

    /**
     * \brief Update mode of the CANrange. The CANrange supports
     * short-range and long-range detection at various update frequencies.
     * 
     */
    signals::UpdateModeValue UpdateMode = signals::UpdateModeValue::ShortRange100Hz;
    /**
     * \brief Rate at which the CANrange will take measurements. A lower
     * frequency may provide more stable readings but will reduce the data
     * rate of the sensor.
     * 
     * - Minimum Value: 5
     * - Maximum Value: 50
     * - Default Value: 50
     * - Units: Hz
     */
    units::frequency::hertz_t UpdateFrequency = 50_Hz;
    
    /**
     * \brief Modifies this configuration's UpdateMode parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Update mode of the CANrange. The CANrange supports short-range and
     * long-range detection at various update frequencies.
     * 
     *
     * \param newUpdateMode Parameter to modify
     * \returns Itself
     */
    constexpr ToFParamsConfigs &WithUpdateMode(signals::UpdateModeValue newUpdateMode)
    {
        UpdateMode = std::move(newUpdateMode);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's UpdateFrequency parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Rate at which the CANrange will take measurements. A lower
     * frequency may provide more stable readings but will reduce the data
     * rate of the sensor.
     * 
     * - Minimum Value: 5
     * - Maximum Value: 50
     * - Default Value: 50
     * - Units: Hz
     *
     * \param newUpdateFrequency Parameter to modify
     * \returns Itself
     */
    constexpr ToFParamsConfigs &WithUpdateFrequency(units::frequency::hertz_t newUpdateFrequency)
    {
        UpdateFrequency = std::move(newUpdateFrequency);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: ToFParams" << std::endl;
        ss << "    UpdateMode: " << UpdateMode << std::endl;
        ss << "    UpdateFrequency: " << UpdateFrequency.to<double>() << " Hz" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::CANrange_UpdateMode, UpdateMode.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::CANrange_UpdateFreq, UpdateFrequency.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::CANrange_UpdateMode, string_c_str, string_length, &UpdateMode.value);
        double UpdateFrequencyVal = UpdateFrequency.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::CANrange_UpdateFreq, string_c_str, string_length, &UpdateFrequencyVal);
        UpdateFrequency = units::frequency::hertz_t{UpdateFrequencyVal};
        return 0;
    }
};


/**
 * \brief Configs that affect the ToF Proximity detection
 * 
 * \details Includes proximity mode and the threshold for simple
 *          detection
 */
class ProximityParamsConfigs : public ParentConfiguration
{
public:
    constexpr ProximityParamsConfigs() = default;

    /**
     * \brief Threshold for object detection.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 4
     * - Default Value: 0.4
     * - Units: m
     */
    units::length::meter_t ProximityThreshold = 0.4_m;
    /**
     * \brief How far above and below the threshold the distance needs to
     * be to trigger undetected and detected, respectively. This is used
     * to prevent bouncing between the detected and undetected states for
     * objects on the threshold.
     * 
     * If the threshold is set to 0.1 meters, and the hysteresis is 0.01
     * meters, then an object needs to be within 0.09 meters to be
     * detected. After the object is first detected, the distance then
     * needs to exceed 0.11 meters to become undetected again.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0.01
     * - Units: m
     */
    units::length::meter_t ProximityHysteresis = 0.01_m;
    /**
     * \brief The minimum allowable signal strength before determining the
     * measurement is valid.
     * 
     * If the signal strength is particularly low, this typically means
     * the object is far away and there's fewer total samples to derive
     * the distance from. Set this value to be below the lowest strength
     * you see when you're detecting an object with the CANrange; the
     * default of 2500 is typically acceptable in most cases.
     * 
     * - Minimum Value: 1
     * - Maximum Value: 15000
     * - Default Value: 2500
     * - Units: 
     */
    units::dimensionless::scalar_t MinSignalStrengthForValidMeasurement = 2500;
    
    /**
     * \brief Modifies this configuration's ProximityThreshold parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Threshold for object detection.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 4
     * - Default Value: 0.4
     * - Units: m
     *
     * \param newProximityThreshold Parameter to modify
     * \returns Itself
     */
    constexpr ProximityParamsConfigs &WithProximityThreshold(units::length::meter_t newProximityThreshold)
    {
        ProximityThreshold = std::move(newProximityThreshold);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ProximityHysteresis parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * How far above and below the threshold the distance needs to be to
     * trigger undetected and detected, respectively. This is used to
     * prevent bouncing between the detected and undetected states for
     * objects on the threshold.
     * 
     * If the threshold is set to 0.1 meters, and the hysteresis is 0.01
     * meters, then an object needs to be within 0.09 meters to be
     * detected. After the object is first detected, the distance then
     * needs to exceed 0.11 meters to become undetected again.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 1
     * - Default Value: 0.01
     * - Units: m
     *
     * \param newProximityHysteresis Parameter to modify
     * \returns Itself
     */
    constexpr ProximityParamsConfigs &WithProximityHysteresis(units::length::meter_t newProximityHysteresis)
    {
        ProximityHysteresis = std::move(newProximityHysteresis);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's MinSignalStrengthForValidMeasurement parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The minimum allowable signal strength before determining the
     * measurement is valid.
     * 
     * If the signal strength is particularly low, this typically means
     * the object is far away and there's fewer total samples to derive
     * the distance from. Set this value to be below the lowest strength
     * you see when you're detecting an object with the CANrange; the
     * default of 2500 is typically acceptable in most cases.
     * 
     * - Minimum Value: 1
     * - Maximum Value: 15000
     * - Default Value: 2500
     * - Units: 
     *
     * \param newMinSignalStrengthForValidMeasurement Parameter to modify
     * \returns Itself
     */
    constexpr ProximityParamsConfigs &WithMinSignalStrengthForValidMeasurement(units::dimensionless::scalar_t newMinSignalStrengthForValidMeasurement)
    {
        MinSignalStrengthForValidMeasurement = std::move(newMinSignalStrengthForValidMeasurement);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: ProximityParams" << std::endl;
        ss << "    ProximityThreshold: " << ProximityThreshold.to<double>() << " m" << std::endl;
        ss << "    ProximityHysteresis: " << ProximityHysteresis.to<double>() << " m" << std::endl;
        ss << "    MinSignalStrengthForValidMeasurement: " << MinSignalStrengthForValidMeasurement.to<double>() << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::CANrange_ProximityThreshold, ProximityThreshold.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::CANrange_ProximityHysteresis, ProximityHysteresis.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::CANrange_MinSigStrengthForValidMeas, MinSignalStrengthForValidMeasurement.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double ProximityThresholdVal = ProximityThreshold.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::CANrange_ProximityThreshold, string_c_str, string_length, &ProximityThresholdVal);
        ProximityThreshold = units::length::meter_t{ProximityThresholdVal};
        double ProximityHysteresisVal = ProximityHysteresis.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::CANrange_ProximityHysteresis, string_c_str, string_length, &ProximityHysteresisVal);
        ProximityHysteresis = units::length::meter_t{ProximityHysteresisVal};
        double MinSignalStrengthForValidMeasurementVal = MinSignalStrengthForValidMeasurement.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::CANrange_MinSigStrengthForValidMeas, string_c_str, string_length, &MinSignalStrengthForValidMeasurementVal);
        MinSignalStrengthForValidMeasurement = units::dimensionless::scalar_t{MinSignalStrengthForValidMeasurementVal};
        return 0;
    }
};


/**
 * \brief Configs that affect the ToF Field of View
 * 
 * \details Includes range and center configs
 */
class FovParamsConfigs : public ParentConfiguration
{
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

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: FovParams" << std::endl;
        ss << "    FOVCenterX: " << FOVCenterX.to<double>() << " deg" << std::endl;
        ss << "    FOVCenterY: " << FOVCenterY.to<double>() << " deg" << std::endl;
        ss << "    FOVRangeX: " << FOVRangeX.to<double>() << " deg" << std::endl;
        ss << "    FOVRangeY: " << FOVRangeY.to<double>() << " deg" << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::CANrange_FOVCenterX, FOVCenterX.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::CANrange_FOVCenterY, FOVCenterY.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::CANrange_FOVRangeX, FOVRangeX.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::CANrange_FOVRangeY, FOVRangeY.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double FOVCenterXVal = FOVCenterX.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::CANrange_FOVCenterX, string_c_str, string_length, &FOVCenterXVal);
        FOVCenterX = units::angle::degree_t{FOVCenterXVal};
        double FOVCenterYVal = FOVCenterY.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::CANrange_FOVCenterY, string_c_str, string_length, &FOVCenterYVal);
        FOVCenterY = units::angle::degree_t{FOVCenterYVal};
        double FOVRangeXVal = FOVRangeX.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::CANrange_FOVRangeX, string_c_str, string_length, &FOVRangeXVal);
        FOVRangeX = units::angle::degree_t{FOVRangeXVal};
        double FOVRangeYVal = FOVRangeY.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::CANrange_FOVRangeY, string_c_str, string_length, &FOVRangeYVal);
        FOVRangeY = units::angle::degree_t{FOVRangeYVal};
        return 0;
    }
};


/**
 * \brief Configs that determine motor selection and commutation.
 * 
 * \details Set these configs to match your motor setup before
 *          commanding motor output.
 */
class CommutationConfigs : public ParentConfiguration
{
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

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: Commutation" << std::endl;
        ss << "    AdvancedHallSupport: " << AdvancedHallSupport << std::endl;
        ss << "    MotorArrangement: " << MotorArrangement << std::endl;
        ss << "    BrushedMotorWiring: " << BrushedMotorWiring << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_AdvancedHallSupport, AdvancedHallSupport.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_MotorType, MotorArrangement.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_BrushedMotorWiring, BrushedMotorWiring.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_AdvancedHallSupport, string_c_str, string_length, &AdvancedHallSupport.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_MotorType, string_c_str, string_length, &MotorArrangement.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_BrushedMotorWiring, string_c_str, string_length, &BrushedMotorWiring.value);
        return 0;
    }
};


/**
 * \brief Configs related to the CANdi™ branded device's digital I/O
 *        settings
 * 
 * \details Contains float-state settings and when to assert the S1/S2
 *          inputs.
 */
class DigitalInputsConfigs : public ParentConfiguration
{
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

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: DigitalInputs" << std::endl;
        ss << "    S1FloatState: " << S1FloatState << std::endl;
        ss << "    S2FloatState: " << S2FloatState << std::endl;
        ss << "    S1CloseState: " << S1CloseState << std::endl;
        ss << "    S2CloseState: " << S2CloseState << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::CANdi_S1FloatState, S1FloatState.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::CANdi_S2FloatState, S2FloatState.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_S1_CloseState, S1CloseState.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_S2_CloseState, S2CloseState.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::CANdi_S1FloatState, string_c_str, string_length, &S1FloatState.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::CANdi_S2FloatState, string_c_str, string_length, &S2FloatState.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_S1_CloseState, string_c_str, string_length, &S1CloseState.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_S2_CloseState, string_c_str, string_length, &S2CloseState.value);
        return 0;
    }
};


/**
 * \brief Configs related to the CANdi™ branded device's quadrature
 *        interface using both the S1IN and S2IN inputs
 * 
 * \details All the configs related to the quadrature interface for
 *          the CANdi™ branded device , including encoder edges per
 *          revolution and sensor direction.
 */
class QuadratureConfigs : public ParentConfiguration
{
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

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: Quadrature" << std::endl;
        ss << "    QuadratureEdgesPerRotation: " << QuadratureEdgesPerRotation << std::endl;
        ss << "    SensorDirection: " << SensorDirection << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_QuadratureEdgesPerRotation, QuadratureEdgesPerRotation, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_Quad_SensorDirection, SensorDirection, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_QuadratureEdgesPerRotation, string_c_str, string_length, &QuadratureEdgesPerRotation);
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_Quad_SensorDirection, string_c_str, string_length, &SensorDirection);
        return 0;
    }
};


/**
 * \brief Configs related to the CANdi™ branded device's PWM interface
 *        on the Signal 1 input (S1IN)
 * 
 * \details All the configs related to the PWM interface for the
 *          CANdi™ branded device on S1, including absolute sensor
 *          offset, absolute sensor discontinuity point and sensor
 *          direction.
 */
class PWM1Configs : public ParentConfiguration
{
public:
    constexpr PWM1Configs() = default;

    /**
     * \brief The offset applied to the PWM sensor.
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
     * \brief Direction of the PWM sensor to determine positive rotation.
     * Invert this so that forward motion on the mechanism results in an
     * increase in PWM position.
     * 
     * - Default Value: False
     */
    bool SensorDirection = false;
    
    /**
     * \brief Modifies this configuration's AbsoluteSensorOffset parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The offset applied to the PWM sensor.
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
    constexpr PWM1Configs &WithAbsoluteSensorOffset(units::angle::turn_t newAbsoluteSensorOffset)
    {
        AbsoluteSensorOffset = std::move(newAbsoluteSensorOffset);
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
    constexpr PWM1Configs &WithAbsoluteSensorDiscontinuityPoint(units::angle::turn_t newAbsoluteSensorDiscontinuityPoint)
    {
        AbsoluteSensorDiscontinuityPoint = std::move(newAbsoluteSensorDiscontinuityPoint);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SensorDirection parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Direction of the PWM sensor to determine positive rotation. Invert
     * this so that forward motion on the mechanism results in an increase
     * in PWM position.
     * 
     * - Default Value: False
     *
     * \param newSensorDirection Parameter to modify
     * \returns Itself
     */
    constexpr PWM1Configs &WithSensorDirection(bool newSensorDirection)
    {
        SensorDirection = std::move(newSensorDirection);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: PWM1" << std::endl;
        ss << "    AbsoluteSensorOffset: " << AbsoluteSensorOffset.to<double>() << " rotations" << std::endl;
        ss << "    AbsoluteSensorDiscontinuityPoint: " << AbsoluteSensorDiscontinuityPoint.to<double>() << " rotations" << std::endl;
        ss << "    SensorDirection: " << SensorDirection << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PWM1_AbsoluteSensorOffset, AbsoluteSensorOffset.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PWM1_AbsoluteSensorDiscontinuityPoint, AbsoluteSensorDiscontinuityPoint.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_PWM1_SensorDirection, SensorDirection, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double AbsoluteSensorOffsetVal = AbsoluteSensorOffset.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PWM1_AbsoluteSensorOffset, string_c_str, string_length, &AbsoluteSensorOffsetVal);
        AbsoluteSensorOffset = units::angle::turn_t{AbsoluteSensorOffsetVal};
        double AbsoluteSensorDiscontinuityPointVal = AbsoluteSensorDiscontinuityPoint.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PWM1_AbsoluteSensorDiscontinuityPoint, string_c_str, string_length, &AbsoluteSensorDiscontinuityPointVal);
        AbsoluteSensorDiscontinuityPoint = units::angle::turn_t{AbsoluteSensorDiscontinuityPointVal};
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_PWM1_SensorDirection, string_c_str, string_length, &SensorDirection);
        return 0;
    }
};


/**
 * \brief Configs related to the CANdi™ branded device's PWM interface
 *        on the Signal 2 input (S2IN)
 * 
 * \details All the configs related to the PWM interface for the
 *          CANdi™ branded device on S1, including absolute sensor
 *          offset, absolute sensor discontinuity point and sensor
 *          direction.
 */
class PWM2Configs : public ParentConfiguration
{
public:
    constexpr PWM2Configs() = default;

    /**
     * \brief The offset applied to the PWM sensor.
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
     * \brief Direction of the PWM sensor to determine positive rotation.
     * Invert this so that forward motion on the mechanism results in an
     * increase in PWM position.
     * 
     * - Default Value: False
     */
    bool SensorDirection = false;
    
    /**
     * \brief Modifies this configuration's AbsoluteSensorOffset parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The offset applied to the PWM sensor.
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
    constexpr PWM2Configs &WithAbsoluteSensorOffset(units::angle::turn_t newAbsoluteSensorOffset)
    {
        AbsoluteSensorOffset = std::move(newAbsoluteSensorOffset);
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
    constexpr PWM2Configs &WithAbsoluteSensorDiscontinuityPoint(units::angle::turn_t newAbsoluteSensorDiscontinuityPoint)
    {
        AbsoluteSensorDiscontinuityPoint = std::move(newAbsoluteSensorDiscontinuityPoint);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's SensorDirection parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Direction of the PWM sensor to determine positive rotation. Invert
     * this so that forward motion on the mechanism results in an increase
     * in PWM position.
     * 
     * - Default Value: False
     *
     * \param newSensorDirection Parameter to modify
     * \returns Itself
     */
    constexpr PWM2Configs &WithSensorDirection(bool newSensorDirection)
    {
        SensorDirection = std::move(newSensorDirection);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: PWM2" << std::endl;
        ss << "    AbsoluteSensorOffset: " << AbsoluteSensorOffset.to<double>() << " rotations" << std::endl;
        ss << "    AbsoluteSensorDiscontinuityPoint: " << AbsoluteSensorDiscontinuityPoint.to<double>() << " rotations" << std::endl;
        ss << "    SensorDirection: " << SensorDirection << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PWM2_AbsoluteSensorOffset, AbsoluteSensorOffset.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_PWM2_AbsoluteSensorDiscontinuityPoint, AbsoluteSensorDiscontinuityPoint.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_bool(ctre::phoenix6::spns::SpnValue::Config_PWM2_SensorDirection, SensorDirection, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double AbsoluteSensorOffsetVal = AbsoluteSensorOffset.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PWM2_AbsoluteSensorOffset, string_c_str, string_length, &AbsoluteSensorOffsetVal);
        AbsoluteSensorOffset = units::angle::turn_t{AbsoluteSensorOffsetVal};
        double AbsoluteSensorDiscontinuityPointVal = AbsoluteSensorDiscontinuityPoint.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_PWM2_AbsoluteSensorDiscontinuityPoint, string_c_str, string_length, &AbsoluteSensorDiscontinuityPointVal);
        AbsoluteSensorDiscontinuityPoint = units::angle::turn_t{AbsoluteSensorDiscontinuityPointVal};
        c_ctre_phoenix6_deserialize_bool(ctre::phoenix6::spns::SpnValue::Config_PWM2_SensorDirection, string_c_str, string_length, &SensorDirection);
        return 0;
    }
};


/**
 * \brief Configs related to CANdle LED control.
 * 
 * \details All the configs related to controlling LEDs with the
 *          CANdle, including LED strip type and brightness.
 */
class LEDConfigs : public ParentConfiguration
{
public:
    constexpr LEDConfigs() = default;

    /**
     * \brief The type of LEDs that are being controlled.
     * 
     */
    signals::StripTypeValue StripType = signals::StripTypeValue::GRB;
    /**
     * \brief The brightness scalar for all LEDs controlled. All LED
     * values sent to the CANdle will be scaled by this config.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 1.0
     * - Units: scalar
     */
    units::dimensionless::scalar_t BrightnessScalar = 1.0;
    /**
     * \brief The behavior of the LEDs when the control signal is lost.
     * 
     */
    signals::LossOfSignalBehaviorValue LossOfSignalBehavior = signals::LossOfSignalBehaviorValue::KeepRunning;
    
    /**
     * \brief Modifies this configuration's StripType parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The type of LEDs that are being controlled.
     * 
     *
     * \param newStripType Parameter to modify
     * \returns Itself
     */
    constexpr LEDConfigs &WithStripType(signals::StripTypeValue newStripType)
    {
        StripType = std::move(newStripType);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's BrightnessScalar parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The brightness scalar for all LEDs controlled. All LED values sent
     * to the CANdle will be scaled by this config.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 1.0
     * - Units: scalar
     *
     * \param newBrightnessScalar Parameter to modify
     * \returns Itself
     */
    constexpr LEDConfigs &WithBrightnessScalar(units::dimensionless::scalar_t newBrightnessScalar)
    {
        BrightnessScalar = std::move(newBrightnessScalar);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's LossOfSignalBehavior parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The behavior of the LEDs when the control signal is lost.
     * 
     *
     * \param newLossOfSignalBehavior Parameter to modify
     * \returns Itself
     */
    constexpr LEDConfigs &WithLossOfSignalBehavior(signals::LossOfSignalBehaviorValue newLossOfSignalBehavior)
    {
        LossOfSignalBehavior = std::move(newLossOfSignalBehavior);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: LED" << std::endl;
        ss << "    StripType: " << StripType << std::endl;
        ss << "    BrightnessScalar: " << BrightnessScalar.to<double>() << " scalar" << std::endl;
        ss << "    LossOfSignalBehavior: " << LossOfSignalBehavior << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_LED_StripType, StripType.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Config_LED_BrightnessScalar, BrightnessScalar.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_LED_LossOfSignalBehavior, LossOfSignalBehavior.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_LED_StripType, string_c_str, string_length, &StripType.value);
        double BrightnessScalarVal = BrightnessScalar.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Config_LED_BrightnessScalar, string_c_str, string_length, &BrightnessScalarVal);
        BrightnessScalar = units::dimensionless::scalar_t{BrightnessScalarVal};
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_LED_LossOfSignalBehavior, string_c_str, string_length, &LossOfSignalBehavior.value);
        return 0;
    }
};


/**
 * \brief Configs related to general CANdle features.
 * 
 * \details This includes configs such as disabling the 5V rail and
 *          the behavior of VBat output.
 */
class CANdleFeaturesConfigs : public ParentConfiguration
{
public:
    constexpr CANdleFeaturesConfigs() = default;

    /**
     * \brief Whether the 5V rail is enabled. Disabling the 5V rail will
     * also turn off the onboard LEDs.
     * 
     */
    signals::Enable5VRailValue Enable5VRail = signals::Enable5VRailValue::Enabled;
    /**
     * \brief The behavior of the VBat output. CANdle supports modulating
     * VBat output for single-color LED strips.
     * 
     */
    signals::VBatOutputModeValue VBatOutputMode = signals::VBatOutputModeValue::On;
    /**
     * \brief Whether the Status LED is enabled when the CANdle is
     * actively being controlled.
     * 
     */
    signals::StatusLedWhenActiveValue StatusLedWhenActive = signals::StatusLedWhenActiveValue::Enabled;
    
    /**
     * \brief Modifies this configuration's Enable5VRail parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Whether the 5V rail is enabled. Disabling the 5V rail will also
     * turn off the onboard LEDs.
     * 
     *
     * \param newEnable5VRail Parameter to modify
     * \returns Itself
     */
    constexpr CANdleFeaturesConfigs &WithEnable5VRail(signals::Enable5VRailValue newEnable5VRail)
    {
        Enable5VRail = std::move(newEnable5VRail);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's VBatOutputMode parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * The behavior of the VBat output. CANdle supports modulating VBat
     * output for single-color LED strips.
     * 
     *
     * \param newVBatOutputMode Parameter to modify
     * \returns Itself
     */
    constexpr CANdleFeaturesConfigs &WithVBatOutputMode(signals::VBatOutputModeValue newVBatOutputMode)
    {
        VBatOutputMode = std::move(newVBatOutputMode);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's StatusLedWhenActive parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Whether the Status LED is enabled when the CANdle is actively being
     * controlled.
     * 
     *
     * \param newStatusLedWhenActive Parameter to modify
     * \returns Itself
     */
    constexpr CANdleFeaturesConfigs &WithStatusLedWhenActive(signals::StatusLedWhenActiveValue newStatusLedWhenActive)
    {
        StatusLedWhenActive = std::move(newStatusLedWhenActive);
        return *this;
    }

    

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: CANdleFeatures" << std::endl;
        ss << "    Enable5VRail: " << Enable5VRail << std::endl;
        ss << "    VBatOutputMode: " << VBatOutputMode << std::endl;
        ss << "    StatusLedWhenActive: " << StatusLedWhenActive << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_CANdle_5VRail, Enable5VRail.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_CANdle_VBatOutputMode, VBatOutputMode.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Config_CANdle_StatusLedWhenActive, StatusLedWhenActive.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_CANdle_5VRail, string_c_str, string_length, &Enable5VRail.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_CANdle_VBatOutputMode, string_c_str, string_length, &VBatOutputMode.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Config_CANdle_StatusLedWhenActive, string_c_str, string_length, &StatusLedWhenActive.value);
        return 0;
    }
};


/**
 * \brief Gains for the specified slot.
 * 
 * \details If this slot is selected, these gains are used in closed
 *          loop control requests.
 */
class Slot0Configs : public ParentConfiguration
{
public:
    constexpr Slot0Configs() = default;

    /**
     * \brief Proportional Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input, the units
     * should be defined as units of output per unit of input error. For
     * example, when controlling velocity using a duty cycle closed loop,
     * the units for the proportional gain will be duty cycle per rps of
     * error, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kP = 0;
    /**
     * \brief Integral Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input integrated over
     * time (in units of seconds), the units should be defined as units of
     * output per unit of integrated input error. For example, when
     * controlling velocity using a duty cycle closed loop, integrating
     * velocity over time results in rps * s = rotations. Therefore, the
     * units for the integral gain will be duty cycle per rotation of
     * accumulated error, or 1/rot.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kI = 0;
    /**
     * \brief Derivative Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the derivative of error in the
     * input with respect to time (in units of seconds), the units should
     * be defined as units of output per unit of the differentiated input
     * error. For example, when controlling velocity using a duty cycle
     * closed loop, the derivative of velocity with respect to time is rot
     * per sec², which is acceleration. Therefore, the units for the
     * derivative gain will be duty cycle per unit of acceleration error,
     * or 1/(rot per sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kD = 0;
    /**
     * \brief Static Feedforward Gain.
     * 
     * \details This is added to the closed loop output. The unit for this
     * constant is dependent on the control mode, typically fractional
     * duty cycle, voltage, or torque current.
     * 
     * The sign is typically determined by reference velocity when using
     * position, velocity, and Motion Magic® closed loop modes. However,
     * when using position closed loop with zero velocity reference (no
     * motion profiling), the application can instead use the position
     * closed loop error by setting the Static Feedforward Sign
     * configuration parameter.  When doing so, we recommend the minimal
     * amount of kS, otherwise the motor output may dither when closed
     * loop error is near zero.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kS = 0;
    /**
     * \brief Velocity Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested velocity, the units
     * should be defined as units of output per unit of requested input
     * velocity. For example, when controlling velocity using a duty cycle
     * closed loop, the units for the velocity feedfoward gain will be
     * duty cycle per requested rps, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kV = 0;
    /**
     * \brief Acceleration Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested acceleration, the
     * units should be defined as units of output per unit of requested
     * input acceleration. For example, when controlling velocity using a
     * duty cycle closed loop, the units for the acceleration feedfoward
     * gain will be duty cycle per requested rot per sec², or 1/(rot per
     * sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kA = 0;
    /**
     * \brief Gravity Feedforward/Feedback Gain.
     * 
     * \details This is added to the closed loop output. The sign is
     * determined by GravityType. The unit for this constant is dependent
     * on the control mode, typically fractional duty cycle, voltage, or
     * torque current.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kG = 0;
    /**
     * \brief Gravity Feedforward/Feedback Type.
     * 
     * This determines the type of the gravity feedforward/feedback.
     * 
     * Choose Elevator_Static for systems where the gravity feedforward is
     * constant, such as an elevator. The gravity feedforward output will
     * always have the same sign.
     * 
     * Choose Arm_Cosine for systems where the gravity feedback is
     * dependent on the angular position of the mechanism, such as an arm.
     * The gravity feedback output will vary depending on the mechanism
     * angular position. Note that the sensor offset and ratios must be
     * configured so that the sensor reports a position of 0 when the
     * mechanism is horizonal (parallel to the ground), and the reported
     * sensor position is 1:1 with the mechanism.
     * 
     */
    signals::GravityTypeValue GravityType = signals::GravityTypeValue::Elevator_Static;
    /**
     * \brief Static Feedforward Sign during position closed loop.
     * 
     * This determines the sign of the applied kS during position
     * closed-loop modes. The default behavior uses the velocity reference
     * sign. This works well with velocity closed loop, Motion Magic®
     * controls, and position closed loop when velocity reference is
     * specified (motion profiling).
     * 
     * However, when using position closed loop with zero velocity
     * reference (no motion profiling), the application may want to apply
     * static feedforward based on the sign of closed loop error instead.
     * When doing so, we recommend using the minimal amount of kS,
     * otherwise the motor output may dither when closed loop error is
     * near zero.
     * 
     */
    signals::StaticFeedforwardSignValue StaticFeedforwardSign = signals::StaticFeedforwardSignValue::UseVelocitySign;
    
    /**
     * \brief Modifies this configuration's kP parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Proportional Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input, the units
     * should be defined as units of output per unit of input error. For
     * example, when controlling velocity using a duty cycle closed loop,
     * the units for the proportional gain will be duty cycle per rps of
     * error, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKP Parameter to modify
     * \returns Itself
     */
    constexpr Slot0Configs &WithKP(units::dimensionless::scalar_t newKP)
    {
        kP = std::move(newKP);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kI parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Integral Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input integrated over
     * time (in units of seconds), the units should be defined as units of
     * output per unit of integrated input error. For example, when
     * controlling velocity using a duty cycle closed loop, integrating
     * velocity over time results in rps * s = rotations. Therefore, the
     * units for the integral gain will be duty cycle per rotation of
     * accumulated error, or 1/rot.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKI Parameter to modify
     * \returns Itself
     */
    constexpr Slot0Configs &WithKI(units::dimensionless::scalar_t newKI)
    {
        kI = std::move(newKI);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kD parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Derivative Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the derivative of error in the
     * input with respect to time (in units of seconds), the units should
     * be defined as units of output per unit of the differentiated input
     * error. For example, when controlling velocity using a duty cycle
     * closed loop, the derivative of velocity with respect to time is rot
     * per sec², which is acceleration. Therefore, the units for the
     * derivative gain will be duty cycle per unit of acceleration error,
     * or 1/(rot per sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKD Parameter to modify
     * \returns Itself
     */
    constexpr Slot0Configs &WithKD(units::dimensionless::scalar_t newKD)
    {
        kD = std::move(newKD);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kS parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Static Feedforward Gain.
     * 
     * \details This is added to the closed loop output. The unit for this
     * constant is dependent on the control mode, typically fractional
     * duty cycle, voltage, or torque current.
     * 
     * The sign is typically determined by reference velocity when using
     * position, velocity, and Motion Magic® closed loop modes. However,
     * when using position closed loop with zero velocity reference (no
     * motion profiling), the application can instead use the position
     * closed loop error by setting the Static Feedforward Sign
     * configuration parameter.  When doing so, we recommend the minimal
     * amount of kS, otherwise the motor output may dither when closed
     * loop error is near zero.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     *
     * \param newKS Parameter to modify
     * \returns Itself
     */
    constexpr Slot0Configs &WithKS(units::dimensionless::scalar_t newKS)
    {
        kS = std::move(newKS);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kV parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Velocity Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested velocity, the units
     * should be defined as units of output per unit of requested input
     * velocity. For example, when controlling velocity using a duty cycle
     * closed loop, the units for the velocity feedfoward gain will be
     * duty cycle per requested rps, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKV Parameter to modify
     * \returns Itself
     */
    constexpr Slot0Configs &WithKV(units::dimensionless::scalar_t newKV)
    {
        kV = std::move(newKV);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kA parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Acceleration Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested acceleration, the
     * units should be defined as units of output per unit of requested
     * input acceleration. For example, when controlling velocity using a
     * duty cycle closed loop, the units for the acceleration feedfoward
     * gain will be duty cycle per requested rot per sec², or 1/(rot per
     * sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKA Parameter to modify
     * \returns Itself
     */
    constexpr Slot0Configs &WithKA(units::dimensionless::scalar_t newKA)
    {
        kA = std::move(newKA);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kG parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gravity Feedforward/Feedback Gain.
     * 
     * \details This is added to the closed loop output. The sign is
     * determined by GravityType. The unit for this constant is dependent
     * on the control mode, typically fractional duty cycle, voltage, or
     * torque current.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     *
     * \param newKG Parameter to modify
     * \returns Itself
     */
    constexpr Slot0Configs &WithKG(units::dimensionless::scalar_t newKG)
    {
        kG = std::move(newKG);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GravityType parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gravity Feedforward/Feedback Type.
     * 
     * This determines the type of the gravity feedforward/feedback.
     * 
     * Choose Elevator_Static for systems where the gravity feedforward is
     * constant, such as an elevator. The gravity feedforward output will
     * always have the same sign.
     * 
     * Choose Arm_Cosine for systems where the gravity feedback is
     * dependent on the angular position of the mechanism, such as an arm.
     * The gravity feedback output will vary depending on the mechanism
     * angular position. Note that the sensor offset and ratios must be
     * configured so that the sensor reports a position of 0 when the
     * mechanism is horizonal (parallel to the ground), and the reported
     * sensor position is 1:1 with the mechanism.
     * 
     *
     * \param newGravityType Parameter to modify
     * \returns Itself
     */
    constexpr Slot0Configs &WithGravityType(signals::GravityTypeValue newGravityType)
    {
        GravityType = std::move(newGravityType);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's StaticFeedforwardSign parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Static Feedforward Sign during position closed loop.
     * 
     * This determines the sign of the applied kS during position
     * closed-loop modes. The default behavior uses the velocity reference
     * sign. This works well with velocity closed loop, Motion Magic®
     * controls, and position closed loop when velocity reference is
     * specified (motion profiling).
     * 
     * However, when using position closed loop with zero velocity
     * reference (no motion profiling), the application may want to apply
     * static feedforward based on the sign of closed loop error instead.
     * When doing so, we recommend using the minimal amount of kS,
     * otherwise the motor output may dither when closed loop error is
     * near zero.
     * 
     *
     * \param newStaticFeedforwardSign Parameter to modify
     * \returns Itself
     */
    constexpr Slot0Configs &WithStaticFeedforwardSign(signals::StaticFeedforwardSignValue newStaticFeedforwardSign)
    {
        StaticFeedforwardSign = std::move(newStaticFeedforwardSign);
        return *this;
    }

    static Slot0Configs From(const SlotConfigs &value);

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: Slot0" << std::endl;
        ss << "    kP: " << kP.to<double>() << std::endl;
        ss << "    kI: " << kI.to<double>() << std::endl;
        ss << "    kD: " << kD.to<double>() << std::endl;
        ss << "    kS: " << kS.to<double>() << std::endl;
        ss << "    kV: " << kV.to<double>() << std::endl;
        ss << "    kA: " << kA.to<double>() << std::endl;
        ss << "    kG: " << kG.to<double>() << std::endl;
        ss << "    GravityType: " << GravityType << std::endl;
        ss << "    StaticFeedforwardSign: " << StaticFeedforwardSign << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kP, kP.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kI, kI.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kD, kD.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kS, kS.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kV, kV.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kA, kA.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kG, kG.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Slot0_kG_Type, GravityType.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Slot0_kS_Sign, StaticFeedforwardSign.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double kPVal = kP.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kP, string_c_str, string_length, &kPVal);
        kP = units::dimensionless::scalar_t{kPVal};
        double kIVal = kI.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kI, string_c_str, string_length, &kIVal);
        kI = units::dimensionless::scalar_t{kIVal};
        double kDVal = kD.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kD, string_c_str, string_length, &kDVal);
        kD = units::dimensionless::scalar_t{kDVal};
        double kSVal = kS.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kS, string_c_str, string_length, &kSVal);
        kS = units::dimensionless::scalar_t{kSVal};
        double kVVal = kV.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kV, string_c_str, string_length, &kVVal);
        kV = units::dimensionless::scalar_t{kVVal};
        double kAVal = kA.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kA, string_c_str, string_length, &kAVal);
        kA = units::dimensionless::scalar_t{kAVal};
        double kGVal = kG.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot0_kG, string_c_str, string_length, &kGVal);
        kG = units::dimensionless::scalar_t{kGVal};
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Slot0_kG_Type, string_c_str, string_length, &GravityType.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Slot0_kS_Sign, string_c_str, string_length, &StaticFeedforwardSign.value);
        return 0;
    }
};


/**
 * \brief Gains for the specified slot.
 * 
 * \details If this slot is selected, these gains are used in closed
 *          loop control requests.
 */
class Slot1Configs : public ParentConfiguration
{
public:
    constexpr Slot1Configs() = default;

    /**
     * \brief Proportional Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input, the units
     * should be defined as units of output per unit of input error. For
     * example, when controlling velocity using a duty cycle closed loop,
     * the units for the proportional gain will be duty cycle per rps, or
     * 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kP = 0;
    /**
     * \brief Integral Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input integrated over
     * time (in units of seconds), the units should be defined as units of
     * output per unit of integrated input error. For example, when
     * controlling velocity using a duty cycle closed loop, integrating
     * velocity over time results in rps * s = rotations. Therefore, the
     * units for the integral gain will be duty cycle per rotation of
     * accumulated error, or 1/rot.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kI = 0;
    /**
     * \brief Derivative Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the derivative of error in the
     * input with respect to time (in units of seconds), the units should
     * be defined as units of output per unit of the differentiated input
     * error. For example, when controlling velocity using a duty cycle
     * closed loop, the derivative of velocity with respect to time is rot
     * per sec², which is acceleration. Therefore, the units for the
     * derivative gain will be duty cycle per unit of acceleration error,
     * or 1/(rot per sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kD = 0;
    /**
     * \brief Static Feedforward Gain.
     * 
     * \details This is added to the closed loop output. The unit for this
     * constant is dependent on the control mode, typically fractional
     * duty cycle, voltage, or torque current.
     * 
     * The sign is typically determined by reference velocity when using
     * position, velocity, and Motion Magic® closed loop modes. However,
     * when using position closed loop with zero velocity reference (no
     * motion profiling), the application can instead use the position
     * closed loop error by setting the Static Feedforward Sign
     * configuration parameter.  When doing so, we recommend the minimal
     * amount of kS, otherwise the motor output may dither when closed
     * loop error is near zero.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kS = 0;
    /**
     * \brief Velocity Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested velocity, the units
     * should be defined as units of output per unit of requested input
     * velocity. For example, when controlling velocity using a duty cycle
     * closed loop, the units for the velocity feedfoward gain will be
     * duty cycle per requested rps, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kV = 0;
    /**
     * \brief Acceleration Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested acceleration, the
     * units should be defined as units of output per unit of requested
     * input acceleration. For example, when controlling velocity using a
     * duty cycle closed loop, the units for the acceleration feedfoward
     * gain will be duty cycle per requested rot per sec², or 1/(rot per
     * sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kA = 0;
    /**
     * \brief Gravity Feedforward/Feedback Gain.
     * 
     * \details This is added to the closed loop output. The sign is
     * determined by GravityType. The unit for this constant is dependent
     * on the control mode, typically fractional duty cycle, voltage, or
     * torque current.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kG = 0;
    /**
     * \brief Gravity Feedforward/Feedback Type.
     * 
     * This determines the type of the gravity feedforward/feedback.
     * 
     * Choose Elevator_Static for systems where the gravity feedforward is
     * constant, such as an elevator. The gravity feedforward output will
     * always be positive.
     * 
     * Choose Arm_Cosine for systems where the gravity feedback is
     * dependent on the angular position of the mechanism, such as an arm.
     * The gravity feedback output will vary depending on the mechanism
     * angular position. Note that the sensor offset and ratios must be
     * configured so that the sensor position is 0 when the mechanism is
     * horizonal, and one rotation of the mechanism corresponds to one
     * rotation of the sensor position.
     * 
     */
    signals::GravityTypeValue GravityType = signals::GravityTypeValue::Elevator_Static;
    /**
     * \brief Static Feedforward Sign during position closed loop.
     * 
     * This determines the sign of the applied kS during position
     * closed-loop modes. The default behavior uses the velocity reference
     * sign. This works well with velocity closed loop, Motion Magic®
     * controls, and position closed loop when velocity reference is
     * specified (motion profiling).
     * 
     * However, when using position closed loop with zero velocity
     * reference (no motion profiling), the application may want to apply
     * static feedforward based on the closed loop error sign instead.
     * When doing so, we recommend using the minimal amount of kS,
     * otherwise the motor output may dither when closed loop error is
     * near zero.
     * 
     */
    signals::StaticFeedforwardSignValue StaticFeedforwardSign = signals::StaticFeedforwardSignValue::UseVelocitySign;
    
    /**
     * \brief Modifies this configuration's kP parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Proportional Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input, the units
     * should be defined as units of output per unit of input error. For
     * example, when controlling velocity using a duty cycle closed loop,
     * the units for the proportional gain will be duty cycle per rps, or
     * 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKP Parameter to modify
     * \returns Itself
     */
    constexpr Slot1Configs &WithKP(units::dimensionless::scalar_t newKP)
    {
        kP = std::move(newKP);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kI parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Integral Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input integrated over
     * time (in units of seconds), the units should be defined as units of
     * output per unit of integrated input error. For example, when
     * controlling velocity using a duty cycle closed loop, integrating
     * velocity over time results in rps * s = rotations. Therefore, the
     * units for the integral gain will be duty cycle per rotation of
     * accumulated error, or 1/rot.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKI Parameter to modify
     * \returns Itself
     */
    constexpr Slot1Configs &WithKI(units::dimensionless::scalar_t newKI)
    {
        kI = std::move(newKI);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kD parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Derivative Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the derivative of error in the
     * input with respect to time (in units of seconds), the units should
     * be defined as units of output per unit of the differentiated input
     * error. For example, when controlling velocity using a duty cycle
     * closed loop, the derivative of velocity with respect to time is rot
     * per sec², which is acceleration. Therefore, the units for the
     * derivative gain will be duty cycle per unit of acceleration error,
     * or 1/(rot per sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKD Parameter to modify
     * \returns Itself
     */
    constexpr Slot1Configs &WithKD(units::dimensionless::scalar_t newKD)
    {
        kD = std::move(newKD);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kS parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Static Feedforward Gain.
     * 
     * \details This is added to the closed loop output. The unit for this
     * constant is dependent on the control mode, typically fractional
     * duty cycle, voltage, or torque current.
     * 
     * The sign is typically determined by reference velocity when using
     * position, velocity, and Motion Magic® closed loop modes. However,
     * when using position closed loop with zero velocity reference (no
     * motion profiling), the application can instead use the position
     * closed loop error by setting the Static Feedforward Sign
     * configuration parameter.  When doing so, we recommend the minimal
     * amount of kS, otherwise the motor output may dither when closed
     * loop error is near zero.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     *
     * \param newKS Parameter to modify
     * \returns Itself
     */
    constexpr Slot1Configs &WithKS(units::dimensionless::scalar_t newKS)
    {
        kS = std::move(newKS);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kV parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Velocity Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested velocity, the units
     * should be defined as units of output per unit of requested input
     * velocity. For example, when controlling velocity using a duty cycle
     * closed loop, the units for the velocity feedfoward gain will be
     * duty cycle per requested rps, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKV Parameter to modify
     * \returns Itself
     */
    constexpr Slot1Configs &WithKV(units::dimensionless::scalar_t newKV)
    {
        kV = std::move(newKV);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kA parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Acceleration Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested acceleration, the
     * units should be defined as units of output per unit of requested
     * input acceleration. For example, when controlling velocity using a
     * duty cycle closed loop, the units for the acceleration feedfoward
     * gain will be duty cycle per requested rot per sec², or 1/(rot per
     * sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKA Parameter to modify
     * \returns Itself
     */
    constexpr Slot1Configs &WithKA(units::dimensionless::scalar_t newKA)
    {
        kA = std::move(newKA);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kG parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gravity Feedforward/Feedback Gain.
     * 
     * \details This is added to the closed loop output. The sign is
     * determined by GravityType. The unit for this constant is dependent
     * on the control mode, typically fractional duty cycle, voltage, or
     * torque current.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     *
     * \param newKG Parameter to modify
     * \returns Itself
     */
    constexpr Slot1Configs &WithKG(units::dimensionless::scalar_t newKG)
    {
        kG = std::move(newKG);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GravityType parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gravity Feedforward/Feedback Type.
     * 
     * This determines the type of the gravity feedforward/feedback.
     * 
     * Choose Elevator_Static for systems where the gravity feedforward is
     * constant, such as an elevator. The gravity feedforward output will
     * always be positive.
     * 
     * Choose Arm_Cosine for systems where the gravity feedback is
     * dependent on the angular position of the mechanism, such as an arm.
     * The gravity feedback output will vary depending on the mechanism
     * angular position. Note that the sensor offset and ratios must be
     * configured so that the sensor position is 0 when the mechanism is
     * horizonal, and one rotation of the mechanism corresponds to one
     * rotation of the sensor position.
     * 
     *
     * \param newGravityType Parameter to modify
     * \returns Itself
     */
    constexpr Slot1Configs &WithGravityType(signals::GravityTypeValue newGravityType)
    {
        GravityType = std::move(newGravityType);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's StaticFeedforwardSign parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Static Feedforward Sign during position closed loop.
     * 
     * This determines the sign of the applied kS during position
     * closed-loop modes. The default behavior uses the velocity reference
     * sign. This works well with velocity closed loop, Motion Magic®
     * controls, and position closed loop when velocity reference is
     * specified (motion profiling).
     * 
     * However, when using position closed loop with zero velocity
     * reference (no motion profiling), the application may want to apply
     * static feedforward based on the closed loop error sign instead.
     * When doing so, we recommend using the minimal amount of kS,
     * otherwise the motor output may dither when closed loop error is
     * near zero.
     * 
     *
     * \param newStaticFeedforwardSign Parameter to modify
     * \returns Itself
     */
    constexpr Slot1Configs &WithStaticFeedforwardSign(signals::StaticFeedforwardSignValue newStaticFeedforwardSign)
    {
        StaticFeedforwardSign = std::move(newStaticFeedforwardSign);
        return *this;
    }

    static Slot1Configs From(const SlotConfigs &value);

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: Slot1" << std::endl;
        ss << "    kP: " << kP.to<double>() << std::endl;
        ss << "    kI: " << kI.to<double>() << std::endl;
        ss << "    kD: " << kD.to<double>() << std::endl;
        ss << "    kS: " << kS.to<double>() << std::endl;
        ss << "    kV: " << kV.to<double>() << std::endl;
        ss << "    kA: " << kA.to<double>() << std::endl;
        ss << "    kG: " << kG.to<double>() << std::endl;
        ss << "    GravityType: " << GravityType << std::endl;
        ss << "    StaticFeedforwardSign: " << StaticFeedforwardSign << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kP, kP.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kI, kI.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kD, kD.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kS, kS.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kV, kV.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kA, kA.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kG, kG.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Slot1_kG_Type, GravityType.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Slot1_kS_Sign, StaticFeedforwardSign.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double kPVal = kP.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kP, string_c_str, string_length, &kPVal);
        kP = units::dimensionless::scalar_t{kPVal};
        double kIVal = kI.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kI, string_c_str, string_length, &kIVal);
        kI = units::dimensionless::scalar_t{kIVal};
        double kDVal = kD.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kD, string_c_str, string_length, &kDVal);
        kD = units::dimensionless::scalar_t{kDVal};
        double kSVal = kS.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kS, string_c_str, string_length, &kSVal);
        kS = units::dimensionless::scalar_t{kSVal};
        double kVVal = kV.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kV, string_c_str, string_length, &kVVal);
        kV = units::dimensionless::scalar_t{kVVal};
        double kAVal = kA.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kA, string_c_str, string_length, &kAVal);
        kA = units::dimensionless::scalar_t{kAVal};
        double kGVal = kG.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot1_kG, string_c_str, string_length, &kGVal);
        kG = units::dimensionless::scalar_t{kGVal};
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Slot1_kG_Type, string_c_str, string_length, &GravityType.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Slot1_kS_Sign, string_c_str, string_length, &StaticFeedforwardSign.value);
        return 0;
    }
};


/**
 * \brief Gains for the specified slot.
 * 
 * \details If this slot is selected, these gains are used in closed
 *          loop control requests.
 */
class Slot2Configs : public ParentConfiguration
{
public:
    constexpr Slot2Configs() = default;

    /**
     * \brief Proportional Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input, the units
     * should be defined as units of output per unit of input error. For
     * example, when controlling velocity using a duty cycle closed loop,
     * the units for the proportional gain will be duty cycle per rps, or
     * 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kP = 0;
    /**
     * \brief Integral Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input integrated over
     * time (in units of seconds), the units should be defined as units of
     * output per unit of integrated input error. For example, when
     * controlling velocity using a duty cycle closed loop, integrating
     * velocity over time results in rps * s = rotations. Therefore, the
     * units for the integral gain will be duty cycle per rotation of
     * accumulated error, or 1/rot.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kI = 0;
    /**
     * \brief Derivative Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the derivative of error in the
     * input with respect to time (in units of seconds), the units should
     * be defined as units of output per unit of the differentiated input
     * error. For example, when controlling velocity using a duty cycle
     * closed loop, the derivative of velocity with respect to time is rot
     * per sec², which is acceleration. Therefore, the units for the
     * derivative gain will be duty cycle per unit of acceleration error,
     * or 1/(rot per sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kD = 0;
    /**
     * \brief Static Feedforward Gain.
     * 
     * \details This is added to the closed loop output. The unit for this
     * constant is dependent on the control mode, typically fractional
     * duty cycle, voltage, or torque current.
     * 
     * The sign is typically determined by reference velocity when using
     * position, velocity, and Motion Magic® closed loop modes. However,
     * when using position closed loop with zero velocity reference (no
     * motion profiling), the application can instead use the position
     * closed loop error by setting the Static Feedforward Sign
     * configuration parameter.  When doing so, we recommend the minimal
     * amount of kS, otherwise the motor output may dither when closed
     * loop error is near zero.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kS = 0;
    /**
     * \brief Velocity Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested velocity, the units
     * should be defined as units of output per unit of requested input
     * velocity. For example, when controlling velocity using a duty cycle
     * closed loop, the units for the velocity feedfoward gain will be
     * duty cycle per requested rps, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kV = 0;
    /**
     * \brief Acceleration Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested acceleration, the
     * units should be defined as units of output per unit of requested
     * input acceleration. For example, when controlling velocity using a
     * duty cycle closed loop, the units for the acceleration feedfoward
     * gain will be duty cycle per requested rot per sec², or 1/(rot per
     * sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kA = 0;
    /**
     * \brief Gravity Feedforward/Feedback Gain.
     * 
     * \details This is added to the closed loop output. The sign is
     * determined by GravityType. The unit for this constant is dependent
     * on the control mode, typically fractional duty cycle, voltage, or
     * torque current.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kG = 0;
    /**
     * \brief Gravity Feedforward/Feedback Type.
     * 
     * This determines the type of the gravity feedforward/feedback.
     * 
     * Choose Elevator_Static for systems where the gravity feedforward is
     * constant, such as an elevator. The gravity feedforward output will
     * always be positive.
     * 
     * Choose Arm_Cosine for systems where the gravity feedback is
     * dependent on the angular position of the mechanism, such as an arm.
     * The gravity feedback output will vary depending on the mechanism
     * angular position. Note that the sensor offset and ratios must be
     * configured so that the sensor position is 0 when the mechanism is
     * horizonal, and one rotation of the mechanism corresponds to one
     * rotation of the sensor position.
     * 
     */
    signals::GravityTypeValue GravityType = signals::GravityTypeValue::Elevator_Static;
    /**
     * \brief Static Feedforward Sign during position closed loop.
     * 
     * This determines the sign of the applied kS during position
     * closed-loop modes. The default behavior uses the velocity reference
     * sign. This works well with velocity closed loop, Motion Magic®
     * controls, and position closed loop when velocity reference is
     * specified (motion profiling).
     * 
     * However, when using position closed loop with zero velocity
     * reference (no motion profiling), the application may want to apply
     * static feedforward based on the closed loop error sign instead.
     * When doing so, we recommend using the minimal amount of kS,
     * otherwise the motor output may dither when closed loop error is
     * near zero.
     * 
     */
    signals::StaticFeedforwardSignValue StaticFeedforwardSign = signals::StaticFeedforwardSignValue::UseVelocitySign;
    
    /**
     * \brief Modifies this configuration's kP parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Proportional Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input, the units
     * should be defined as units of output per unit of input error. For
     * example, when controlling velocity using a duty cycle closed loop,
     * the units for the proportional gain will be duty cycle per rps, or
     * 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKP Parameter to modify
     * \returns Itself
     */
    constexpr Slot2Configs &WithKP(units::dimensionless::scalar_t newKP)
    {
        kP = std::move(newKP);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kI parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Integral Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input integrated over
     * time (in units of seconds), the units should be defined as units of
     * output per unit of integrated input error. For example, when
     * controlling velocity using a duty cycle closed loop, integrating
     * velocity over time results in rps * s = rotations. Therefore, the
     * units for the integral gain will be duty cycle per rotation of
     * accumulated error, or 1/rot.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKI Parameter to modify
     * \returns Itself
     */
    constexpr Slot2Configs &WithKI(units::dimensionless::scalar_t newKI)
    {
        kI = std::move(newKI);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kD parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Derivative Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the derivative of error in the
     * input with respect to time (in units of seconds), the units should
     * be defined as units of output per unit of the differentiated input
     * error. For example, when controlling velocity using a duty cycle
     * closed loop, the derivative of velocity with respect to time is rot
     * per sec², which is acceleration. Therefore, the units for the
     * derivative gain will be duty cycle per unit of acceleration error,
     * or 1/(rot per sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKD Parameter to modify
     * \returns Itself
     */
    constexpr Slot2Configs &WithKD(units::dimensionless::scalar_t newKD)
    {
        kD = std::move(newKD);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kS parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Static Feedforward Gain.
     * 
     * \details This is added to the closed loop output. The unit for this
     * constant is dependent on the control mode, typically fractional
     * duty cycle, voltage, or torque current.
     * 
     * The sign is typically determined by reference velocity when using
     * position, velocity, and Motion Magic® closed loop modes. However,
     * when using position closed loop with zero velocity reference (no
     * motion profiling), the application can instead use the position
     * closed loop error by setting the Static Feedforward Sign
     * configuration parameter.  When doing so, we recommend the minimal
     * amount of kS, otherwise the motor output may dither when closed
     * loop error is near zero.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     *
     * \param newKS Parameter to modify
     * \returns Itself
     */
    constexpr Slot2Configs &WithKS(units::dimensionless::scalar_t newKS)
    {
        kS = std::move(newKS);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kV parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Velocity Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested velocity, the units
     * should be defined as units of output per unit of requested input
     * velocity. For example, when controlling velocity using a duty cycle
     * closed loop, the units for the velocity feedfoward gain will be
     * duty cycle per requested rps, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKV Parameter to modify
     * \returns Itself
     */
    constexpr Slot2Configs &WithKV(units::dimensionless::scalar_t newKV)
    {
        kV = std::move(newKV);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kA parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Acceleration Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested acceleration, the
     * units should be defined as units of output per unit of requested
     * input acceleration. For example, when controlling velocity using a
     * duty cycle closed loop, the units for the acceleration feedfoward
     * gain will be duty cycle per requested rot per sec², or 1/(rot per
     * sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKA Parameter to modify
     * \returns Itself
     */
    constexpr Slot2Configs &WithKA(units::dimensionless::scalar_t newKA)
    {
        kA = std::move(newKA);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kG parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gravity Feedforward/Feedback Gain.
     * 
     * \details This is added to the closed loop output. The sign is
     * determined by GravityType. The unit for this constant is dependent
     * on the control mode, typically fractional duty cycle, voltage, or
     * torque current.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     *
     * \param newKG Parameter to modify
     * \returns Itself
     */
    constexpr Slot2Configs &WithKG(units::dimensionless::scalar_t newKG)
    {
        kG = std::move(newKG);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GravityType parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gravity Feedforward/Feedback Type.
     * 
     * This determines the type of the gravity feedforward/feedback.
     * 
     * Choose Elevator_Static for systems where the gravity feedforward is
     * constant, such as an elevator. The gravity feedforward output will
     * always be positive.
     * 
     * Choose Arm_Cosine for systems where the gravity feedback is
     * dependent on the angular position of the mechanism, such as an arm.
     * The gravity feedback output will vary depending on the mechanism
     * angular position. Note that the sensor offset and ratios must be
     * configured so that the sensor position is 0 when the mechanism is
     * horizonal, and one rotation of the mechanism corresponds to one
     * rotation of the sensor position.
     * 
     *
     * \param newGravityType Parameter to modify
     * \returns Itself
     */
    constexpr Slot2Configs &WithGravityType(signals::GravityTypeValue newGravityType)
    {
        GravityType = std::move(newGravityType);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's StaticFeedforwardSign parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Static Feedforward Sign during position closed loop.
     * 
     * This determines the sign of the applied kS during position
     * closed-loop modes. The default behavior uses the velocity reference
     * sign. This works well with velocity closed loop, Motion Magic®
     * controls, and position closed loop when velocity reference is
     * specified (motion profiling).
     * 
     * However, when using position closed loop with zero velocity
     * reference (no motion profiling), the application may want to apply
     * static feedforward based on the closed loop error sign instead.
     * When doing so, we recommend using the minimal amount of kS,
     * otherwise the motor output may dither when closed loop error is
     * near zero.
     * 
     *
     * \param newStaticFeedforwardSign Parameter to modify
     * \returns Itself
     */
    constexpr Slot2Configs &WithStaticFeedforwardSign(signals::StaticFeedforwardSignValue newStaticFeedforwardSign)
    {
        StaticFeedforwardSign = std::move(newStaticFeedforwardSign);
        return *this;
    }

    static Slot2Configs From(const SlotConfigs &value);

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "Config Group: Slot2" << std::endl;
        ss << "    kP: " << kP.to<double>() << std::endl;
        ss << "    kI: " << kI.to<double>() << std::endl;
        ss << "    kD: " << kD.to<double>() << std::endl;
        ss << "    kS: " << kS.to<double>() << std::endl;
        ss << "    kV: " << kV.to<double>() << std::endl;
        ss << "    kA: " << kA.to<double>() << std::endl;
        ss << "    kG: " << kG.to<double>() << std::endl;
        ss << "    GravityType: " << GravityType << std::endl;
        ss << "    StaticFeedforwardSign: " << StaticFeedforwardSign << std::endl;
        return ss.str();
    }

    std::string Serialize() const override
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kP, kP.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kI, kI.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kD, kD.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kS, kS.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kV, kV.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kA, kA.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kG, kG.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Slot2_kG_Type, GravityType.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(ctre::phoenix6::spns::SpnValue::Slot2_kS_Sign, StaticFeedforwardSign.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize) override
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        double kPVal = kP.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kP, string_c_str, string_length, &kPVal);
        kP = units::dimensionless::scalar_t{kPVal};
        double kIVal = kI.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kI, string_c_str, string_length, &kIVal);
        kI = units::dimensionless::scalar_t{kIVal};
        double kDVal = kD.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kD, string_c_str, string_length, &kDVal);
        kD = units::dimensionless::scalar_t{kDVal};
        double kSVal = kS.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kS, string_c_str, string_length, &kSVal);
        kS = units::dimensionless::scalar_t{kSVal};
        double kVVal = kV.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kV, string_c_str, string_length, &kVVal);
        kV = units::dimensionless::scalar_t{kVVal};
        double kAVal = kA.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kA, string_c_str, string_length, &kAVal);
        kA = units::dimensionless::scalar_t{kAVal};
        double kGVal = kG.to<double>();
        c_ctre_phoenix6_deserialize_double(ctre::phoenix6::spns::SpnValue::Slot2_kG, string_c_str, string_length, &kGVal);
        kG = units::dimensionless::scalar_t{kGVal};
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Slot2_kG_Type, string_c_str, string_length, &GravityType.value);
        c_ctre_phoenix6_deserialize_int(ctre::phoenix6::spns::SpnValue::Slot2_kS_Sign, string_c_str, string_length, &StaticFeedforwardSign.value);
        return 0;
    }
};

/**
 * \brief Gains for the specified slot.
 * 
 * \details If this slot is selected, these gains are used in closed
 *          loop control requests.
 */
class SlotConfigs : public ParentConfiguration
{
    struct SlotSpns
    {
        int kPSpn;
        int kISpn;
        int kDSpn;
        int kSSpn;
        int kVSpn;
        int kASpn;
        int kGSpn;
        int GravityTypeSpn;
        int StaticFeedforwardSignSpn;
    };

    static inline std::map<int, SlotSpns> const genericMap{
        {0, SlotSpns{
            ctre::phoenix6::spns::SpnValue::Slot0_kP,
            ctre::phoenix6::spns::SpnValue::Slot0_kI,
            ctre::phoenix6::spns::SpnValue::Slot0_kD,
            ctre::phoenix6::spns::SpnValue::Slot0_kS,
            ctre::phoenix6::spns::SpnValue::Slot0_kV,
            ctre::phoenix6::spns::SpnValue::Slot0_kA,
            ctre::phoenix6::spns::SpnValue::Slot0_kG,
            ctre::phoenix6::spns::SpnValue::Slot0_kG_Type,
            ctre::phoenix6::spns::SpnValue::Slot0_kS_Sign,
        }},
        
        {1, SlotSpns{
            ctre::phoenix6::spns::SpnValue::Slot1_kP,
            ctre::phoenix6::spns::SpnValue::Slot1_kI,
            ctre::phoenix6::spns::SpnValue::Slot1_kD,
            ctre::phoenix6::spns::SpnValue::Slot1_kS,
            ctre::phoenix6::spns::SpnValue::Slot1_kV,
            ctre::phoenix6::spns::SpnValue::Slot1_kA,
            ctre::phoenix6::spns::SpnValue::Slot1_kG,
            ctre::phoenix6::spns::SpnValue::Slot1_kG_Type,
            ctre::phoenix6::spns::SpnValue::Slot1_kS_Sign,
        }},
        
        {2, SlotSpns{
            ctre::phoenix6::spns::SpnValue::Slot2_kP,
            ctre::phoenix6::spns::SpnValue::Slot2_kI,
            ctre::phoenix6::spns::SpnValue::Slot2_kD,
            ctre::phoenix6::spns::SpnValue::Slot2_kS,
            ctre::phoenix6::spns::SpnValue::Slot2_kV,
            ctre::phoenix6::spns::SpnValue::Slot2_kA,
            ctre::phoenix6::spns::SpnValue::Slot2_kG,
            ctre::phoenix6::spns::SpnValue::Slot2_kG_Type,
            ctre::phoenix6::spns::SpnValue::Slot2_kS_Sign,
        }},
        
    };

public:
    constexpr SlotConfigs() = default;

    /**
     * \brief Proportional Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input, the units
     * should be defined as units of output per unit of input error. For
     * example, when controlling velocity using a duty cycle closed loop,
     * the units for the proportional gain will be duty cycle per rps of
     * error, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kP = 0;
    /**
     * \brief Integral Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input integrated over
     * time (in units of seconds), the units should be defined as units of
     * output per unit of integrated input error. For example, when
     * controlling velocity using a duty cycle closed loop, integrating
     * velocity over time results in rps * s = rotations. Therefore, the
     * units for the integral gain will be duty cycle per rotation of
     * accumulated error, or 1/rot.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kI = 0;
    /**
     * \brief Derivative Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the derivative of error in the
     * input with respect to time (in units of seconds), the units should
     * be defined as units of output per unit of the differentiated input
     * error. For example, when controlling velocity using a duty cycle
     * closed loop, the derivative of velocity with respect to time is rot
     * per sec², which is acceleration. Therefore, the units for the
     * derivative gain will be duty cycle per unit of acceleration error,
     * or 1/(rot per sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kD = 0;
    /**
     * \brief Static Feedforward Gain.
     * 
     * \details This is added to the closed loop output. The unit for this
     * constant is dependent on the control mode, typically fractional
     * duty cycle, voltage, or torque current.
     * 
     * The sign is typically determined by reference velocity when using
     * position, velocity, and Motion Magic® closed loop modes. However,
     * when using position closed loop with zero velocity reference (no
     * motion profiling), the application can instead use the position
     * closed loop error by setting the Static Feedforward Sign
     * configuration parameter.  When doing so, we recommend the minimal
     * amount of kS, otherwise the motor output may dither when closed
     * loop error is near zero.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kS = 0;
    /**
     * \brief Velocity Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested velocity, the units
     * should be defined as units of output per unit of requested input
     * velocity. For example, when controlling velocity using a duty cycle
     * closed loop, the units for the velocity feedfoward gain will be
     * duty cycle per requested rps, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kV = 0;
    /**
     * \brief Acceleration Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested acceleration, the
     * units should be defined as units of output per unit of requested
     * input acceleration. For example, when controlling velocity using a
     * duty cycle closed loop, the units for the acceleration feedfoward
     * gain will be duty cycle per requested rot per sec², or 1/(rot per
     * sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kA = 0;
    /**
     * \brief Gravity Feedforward/Feedback Gain.
     * 
     * \details This is added to the closed loop output. The sign is
     * determined by GravityType. The unit for this constant is dependent
     * on the control mode, typically fractional duty cycle, voltage, or
     * torque current.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     */
    units::dimensionless::scalar_t kG = 0;
    /**
     * \brief Gravity Feedforward/Feedback Type.
     * 
     * This determines the type of the gravity feedforward/feedback.
     * 
     * Choose Elevator_Static for systems where the gravity feedforward is
     * constant, such as an elevator. The gravity feedforward output will
     * always have the same sign.
     * 
     * Choose Arm_Cosine for systems where the gravity feedback is
     * dependent on the angular position of the mechanism, such as an arm.
     * The gravity feedback output will vary depending on the mechanism
     * angular position. Note that the sensor offset and ratios must be
     * configured so that the sensor reports a position of 0 when the
     * mechanism is horizonal (parallel to the ground), and the reported
     * sensor position is 1:1 with the mechanism.
     * 
     */
    signals::GravityTypeValue GravityType = signals::GravityTypeValue::Elevator_Static;
    /**
     * \brief Static Feedforward Sign during position closed loop.
     * 
     * This determines the sign of the applied kS during position
     * closed-loop modes. The default behavior uses the velocity reference
     * sign. This works well with velocity closed loop, Motion Magic®
     * controls, and position closed loop when velocity reference is
     * specified (motion profiling).
     * 
     * However, when using position closed loop with zero velocity
     * reference (no motion profiling), the application may want to apply
     * static feedforward based on the sign of closed loop error instead.
     * When doing so, we recommend using the minimal amount of kS,
     * otherwise the motor output may dither when closed loop error is
     * near zero.
     * 
     */
    signals::StaticFeedforwardSignValue StaticFeedforwardSign = signals::StaticFeedforwardSignValue::UseVelocitySign;
    
    /**
     * \brief Modifies this configuration's kP parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Proportional Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input, the units
     * should be defined as units of output per unit of input error. For
     * example, when controlling velocity using a duty cycle closed loop,
     * the units for the proportional gain will be duty cycle per rps of
     * error, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKP Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKP(units::dimensionless::scalar_t newKP)
    {
        kP = std::move(newKP);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kI parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Integral Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by error in the input integrated over
     * time (in units of seconds), the units should be defined as units of
     * output per unit of integrated input error. For example, when
     * controlling velocity using a duty cycle closed loop, integrating
     * velocity over time results in rps * s = rotations. Therefore, the
     * units for the integral gain will be duty cycle per rotation of
     * accumulated error, or 1/rot.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKI Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKI(units::dimensionless::scalar_t newKI)
    {
        kI = std::move(newKI);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kD parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Derivative Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the derivative of error in the
     * input with respect to time (in units of seconds), the units should
     * be defined as units of output per unit of the differentiated input
     * error. For example, when controlling velocity using a duty cycle
     * closed loop, the derivative of velocity with respect to time is rot
     * per sec², which is acceleration. Therefore, the units for the
     * derivative gain will be duty cycle per unit of acceleration error,
     * or 1/(rot per sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKD Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKD(units::dimensionless::scalar_t newKD)
    {
        kD = std::move(newKD);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kS parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Static Feedforward Gain.
     * 
     * \details This is added to the closed loop output. The unit for this
     * constant is dependent on the control mode, typically fractional
     * duty cycle, voltage, or torque current.
     * 
     * The sign is typically determined by reference velocity when using
     * position, velocity, and Motion Magic® closed loop modes. However,
     * when using position closed loop with zero velocity reference (no
     * motion profiling), the application can instead use the position
     * closed loop error by setting the Static Feedforward Sign
     * configuration parameter.  When doing so, we recommend the minimal
     * amount of kS, otherwise the motor output may dither when closed
     * loop error is near zero.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     *
     * \param newKS Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKS(units::dimensionless::scalar_t newKS)
    {
        kS = std::move(newKS);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kV parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Velocity Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested velocity, the units
     * should be defined as units of output per unit of requested input
     * velocity. For example, when controlling velocity using a duty cycle
     * closed loop, the units for the velocity feedfoward gain will be
     * duty cycle per requested rps, or 1/rps.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKV Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKV(units::dimensionless::scalar_t newKV)
    {
        kV = std::move(newKV);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kA parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Acceleration Feedforward Gain.
     * 
     * \details The units for this gain is dependent on the control mode.
     * Since this gain is multiplied by the requested acceleration, the
     * units should be defined as units of output per unit of requested
     * input acceleration. For example, when controlling velocity using a
     * duty cycle closed loop, the units for the acceleration feedfoward
     * gain will be duty cycle per requested rot per sec², or 1/(rot per
     * sec²).
     * 
     * - Minimum Value: 0
     * - Maximum Value: 3.4e+38
     * - Default Value: 0
     * - Units: 
     *
     * \param newKA Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKA(units::dimensionless::scalar_t newKA)
    {
        kA = std::move(newKA);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's kG parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gravity Feedforward/Feedback Gain.
     * 
     * \details This is added to the closed loop output. The sign is
     * determined by GravityType. The unit for this constant is dependent
     * on the control mode, typically fractional duty cycle, voltage, or
     * torque current.
     * 
     * - Minimum Value: -512
     * - Maximum Value: 511
     * - Default Value: 0
     * - Units: 
     *
     * \param newKG Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithKG(units::dimensionless::scalar_t newKG)
    {
        kG = std::move(newKG);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GravityType parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Gravity Feedforward/Feedback Type.
     * 
     * This determines the type of the gravity feedforward/feedback.
     * 
     * Choose Elevator_Static for systems where the gravity feedforward is
     * constant, such as an elevator. The gravity feedforward output will
     * always have the same sign.
     * 
     * Choose Arm_Cosine for systems where the gravity feedback is
     * dependent on the angular position of the mechanism, such as an arm.
     * The gravity feedback output will vary depending on the mechanism
     * angular position. Note that the sensor offset and ratios must be
     * configured so that the sensor reports a position of 0 when the
     * mechanism is horizonal (parallel to the ground), and the reported
     * sensor position is 1:1 with the mechanism.
     * 
     *
     * \param newGravityType Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithGravityType(signals::GravityTypeValue newGravityType)
    {
        GravityType = std::move(newGravityType);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's StaticFeedforwardSign parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Static Feedforward Sign during position closed loop.
     * 
     * This determines the sign of the applied kS during position
     * closed-loop modes. The default behavior uses the velocity reference
     * sign. This works well with velocity closed loop, Motion Magic®
     * controls, and position closed loop when velocity reference is
     * specified (motion profiling).
     * 
     * However, when using position closed loop with zero velocity
     * reference (no motion profiling), the application may want to apply
     * static feedforward based on the sign of closed loop error instead.
     * When doing so, we recommend using the minimal amount of kS,
     * otherwise the motor output may dither when closed loop error is
     * near zero.
     * 
     *
     * \param newStaticFeedforwardSign Parameter to modify
     * \returns Itself
     */
    constexpr SlotConfigs &WithStaticFeedforwardSign(signals::StaticFeedforwardSignValue newStaticFeedforwardSign)
    {
        StaticFeedforwardSign = std::move(newStaticFeedforwardSign);
        return *this;
    }


    /**
     * \brief Chooses which slot these configs are for.
     */
    int SlotNumber = 0;

    static SlotConfigs From(const Slot0Configs &value);
    static SlotConfigs From(const Slot1Configs &value);
    static SlotConfigs From(const Slot2Configs &value);

    std::string ToString() const
    {
        std::stringstream ss;
        ss << "Config Group: Slot" << std::endl;
        ss << "    kP: " << kP.to<double>() << std::endl;
        ss << "    kI: " << kI.to<double>() << std::endl;
        ss << "    kD: " << kD.to<double>() << std::endl;
        ss << "    kS: " << kS.to<double>() << std::endl;
        ss << "    kV: " << kV.to<double>() << std::endl;
        ss << "    kA: " << kA.to<double>() << std::endl;
        ss << "    kG: " << kG.to<double>() << std::endl;
        ss << "    GravityType: " << GravityType << std::endl;
        ss << "    StaticFeedforwardSign: " << StaticFeedforwardSign << std::endl;
        return ss.str();
    }

    std::string Serialize() const
    {
        std::stringstream ss;
        SlotSpns currentSpns = genericMap.at(SlotNumber);
        char *ref;
        c_ctre_phoenix6_serialize_double(currentSpns.kPSpn, kP.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(currentSpns.kISpn, kI.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(currentSpns.kDSpn, kD.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(currentSpns.kSSpn, kS.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(currentSpns.kVSpn, kV.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(currentSpns.kASpn, kA.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_double(currentSpns.kGSpn, kG.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(currentSpns.GravityTypeSpn, GravityType.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        c_ctre_phoenix6_serialize_int(currentSpns.StaticFeedforwardSignSpn, StaticFeedforwardSign.value, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return ss.str();
    }

    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize)
    {
        const char *string_c_str = to_deserialize.c_str();
        size_t string_length = to_deserialize.length();
        SlotSpns currentSpns = genericMap.at(SlotNumber);
        double kPVal = kP.to<double>();
        c_ctre_phoenix6_deserialize_double(currentSpns.kPSpn, string_c_str, string_length, &kPVal);
        kP = units::dimensionless::scalar_t{kPVal};
        double kIVal = kI.to<double>();
        c_ctre_phoenix6_deserialize_double(currentSpns.kISpn, string_c_str, string_length, &kIVal);
        kI = units::dimensionless::scalar_t{kIVal};
        double kDVal = kD.to<double>();
        c_ctre_phoenix6_deserialize_double(currentSpns.kDSpn, string_c_str, string_length, &kDVal);
        kD = units::dimensionless::scalar_t{kDVal};
        double kSVal = kS.to<double>();
        c_ctre_phoenix6_deserialize_double(currentSpns.kSSpn, string_c_str, string_length, &kSVal);
        kS = units::dimensionless::scalar_t{kSVal};
        double kVVal = kV.to<double>();
        c_ctre_phoenix6_deserialize_double(currentSpns.kVSpn, string_c_str, string_length, &kVVal);
        kV = units::dimensionless::scalar_t{kVVal};
        double kAVal = kA.to<double>();
        c_ctre_phoenix6_deserialize_double(currentSpns.kASpn, string_c_str, string_length, &kAVal);
        kA = units::dimensionless::scalar_t{kAVal};
        double kGVal = kG.to<double>();
        c_ctre_phoenix6_deserialize_double(currentSpns.kGSpn, string_c_str, string_length, &kGVal);
        kG = units::dimensionless::scalar_t{kGVal};
        c_ctre_phoenix6_deserialize_int(currentSpns.GravityTypeSpn, string_c_str, string_length, &GravityType.value);
        c_ctre_phoenix6_deserialize_int(currentSpns.StaticFeedforwardSignSpn, string_c_str, string_length, &StaticFeedforwardSign.value);
        return 0;
    }
};


}
}
}
