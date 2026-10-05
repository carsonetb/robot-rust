/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/hardware/ParentDevice.hpp"
#include "ctre/phoenix6/CANBus.hpp"
#include "ctre/phoenix6/configs/Configs.hpp"
#include "ctre/phoenix6/configs/Configurator.hpp"


#include "ctre/phoenix6/sim/Pigeon2SimState.hpp"
#include <units/acceleration.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/dimensionless.h>
#include <units/magnetic_field_strength.h>
#include <units/temperature.h>
#include <units/time.h>
#include <units/voltage.h>

namespace ctre {
namespace phoenix6 {

namespace hardware {
namespace core {
    class CorePigeon2;
}
}

namespace configs {

/**
 * Class description for the Pigeon 2 IMU sensor that measures orientation.
 *
 * This handles the configurations for the hardware#Pigeon2
 */
class Pigeon2Configuration : public ParentConfiguration
{
public:
    constexpr Pigeon2Configuration() = default;

    /**
     * \brief True if we should factory default newer unsupported configs,
     *        false to leave newer unsupported configs alone.
     *
     * \details This flag addresses a corner case where the device may have
     *          firmware with newer configs that didn't exist when this
     *          version of the API was built. If this occurs and this
     *          flag is true, unsupported new configs will be factory
     *          defaulted to avoid unexpected behavior.
     *
     *          This is also the behavior in Phoenix 5, so this flag
     *          is defaulted to true to match.
     */
    bool FutureProofConfigs{true};

    
    /**
     * \brief Configs for Pigeon 2's Mount Pose configuration.
     * 
     * \details These configs allow the Pigeon2 to be mounted in whatever
     *          orientation that's desired and ensure the reported
     *          Yaw/Pitch/Roll is from the robot's reference.
     * 
     * Parameter list:
     * 
     * - MountPoseConfigs#MountPoseYaw
     * - MountPoseConfigs#MountPosePitch
     * - MountPoseConfigs#MountPoseRoll
     * 
     */
    MountPoseConfigs MountPose;
    
    /**
     * \brief Configs to trim the Pigeon2's gyroscope.
     * 
     * \details Pigeon2 allows the user to trim the gyroscope's
     *          sensitivity. While this isn't necessary for the Pigeon2,
     *          as it comes calibrated out-of-the-box, users can make use
     *          of this to make the Pigeon2 even more accurate for their
     *          application.
     * 
     * Parameter list:
     * 
     * - GyroTrimConfigs#GyroScalarX
     * - GyroTrimConfigs#GyroScalarY
     * - GyroTrimConfigs#GyroScalarZ
     * 
     */
    GyroTrimConfigs GyroTrim;
    
    /**
     * \brief Configs to enable/disable various features of the Pigeon2.
     * 
     * \details These configs allow the user to enable or disable various
     *          aspects of the Pigeon2.
     * 
     * Parameter list:
     * 
     * - Pigeon2FeaturesConfigs#EnableCompass
     * - Pigeon2FeaturesConfigs#DisableTemperatureCompensation
     * - Pigeon2FeaturesConfigs#DisableNoMotionCalibration
     * 
     */
    Pigeon2FeaturesConfigs Pigeon2Features;
    
    /**
     * \brief Custom Params.
     * 
     * \details Custom paramaters that have no real impact on controller.
     * 
     * Parameter list:
     * 
     * - CustomParamsConfigs#CustomParam0
     * - CustomParamsConfigs#CustomParam1
     * 
     */
    CustomParamsConfigs CustomParams;
    
    /**
     * \brief Modifies this configuration's MountPose parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs for Pigeon 2's Mount Pose configuration.
     * 
     * \details These configs allow the Pigeon2 to be mounted in whatever
     *          orientation that's desired and ensure the reported
     *          Yaw/Pitch/Roll is from the robot's reference.
     * 
     * Parameter list:
     * 
     * - MountPoseConfigs#MountPoseYaw
     * - MountPoseConfigs#MountPosePitch
     * - MountPoseConfigs#MountPoseRoll
     * 
     *
     * \param newMountPose Parameter to modify
     * \returns Itself
     */
    constexpr Pigeon2Configuration &WithMountPose(MountPoseConfigs newMountPose)
    {
        MountPose = std::move(newMountPose);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's GyroTrim parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs to trim the Pigeon2's gyroscope.
     * 
     * \details Pigeon2 allows the user to trim the gyroscope's
     *          sensitivity. While this isn't necessary for the Pigeon2,
     *          as it comes calibrated out-of-the-box, users can make use
     *          of this to make the Pigeon2 even more accurate for their
     *          application.
     * 
     * Parameter list:
     * 
     * - GyroTrimConfigs#GyroScalarX
     * - GyroTrimConfigs#GyroScalarY
     * - GyroTrimConfigs#GyroScalarZ
     * 
     *
     * \param newGyroTrim Parameter to modify
     * \returns Itself
     */
    constexpr Pigeon2Configuration &WithGyroTrim(GyroTrimConfigs newGyroTrim)
    {
        GyroTrim = std::move(newGyroTrim);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's Pigeon2Features parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs to enable/disable various features of the Pigeon2.
     * 
     * \details These configs allow the user to enable or disable various
     *          aspects of the Pigeon2.
     * 
     * Parameter list:
     * 
     * - Pigeon2FeaturesConfigs#EnableCompass
     * - Pigeon2FeaturesConfigs#DisableTemperatureCompensation
     * - Pigeon2FeaturesConfigs#DisableNoMotionCalibration
     * 
     *
     * \param newPigeon2Features Parameter to modify
     * \returns Itself
     */
    constexpr Pigeon2Configuration &WithPigeon2Features(Pigeon2FeaturesConfigs newPigeon2Features)
    {
        Pigeon2Features = std::move(newPigeon2Features);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's CustomParams parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Custom Params.
     * 
     * \details Custom paramaters that have no real impact on controller.
     * 
     * Parameter list:
     * 
     * - CustomParamsConfigs#CustomParam0
     * - CustomParamsConfigs#CustomParam1
     * 
     *
     * \param newCustomParams Parameter to modify
     * \returns Itself
     */
    constexpr Pigeon2Configuration &WithCustomParams(CustomParamsConfigs newCustomParams)
    {
        CustomParams = std::move(newCustomParams);
        return *this;
    }

    /**
     * \brief Get the string representation of this configuration
     */
    std::string ToString() const
    {
        std::stringstream ss;
        ss << "Pigeon2Configuration" << std::endl;
        ss << MountPose.ToString();
        ss << GyroTrim.ToString();
        ss << Pigeon2Features.ToString();
        ss << CustomParams.ToString();
        return ss.str();
    }

    /**
     * \brief Get the serialized form of this configuration
     */
    std::string Serialize() const
    {
        std::stringstream ss;
        ss << MountPose.Serialize();
        ss << GyroTrim.Serialize();
        ss << Pigeon2Features.Serialize();
        ss << CustomParams.Serialize();
        return ss.str();
    }

    /**
     * \brief Take a string and deserialize it to this configuration
     */
    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize)
    {
        ctre::phoenix::StatusCode err = ctre::phoenix::StatusCode::OK;
        err = MountPose.Deserialize(to_deserialize);
        err = GyroTrim.Deserialize(to_deserialize);
        err = Pigeon2Features.Deserialize(to_deserialize);
        err = CustomParams.Deserialize(to_deserialize);
        return err;
    }
};

/**
 * Class description for the Pigeon 2 IMU sensor that measures orientation.
 *
 * This handles the configurations for the hardware#Pigeon2
 */
class Pigeon2Configurator : public ParentConfigurator
{
private:
    Pigeon2Configurator(hardware::DeviceIdentifier id) :
        ParentConfigurator{std::move(id)}
    {}

    friend hardware::core::CorePigeon2;

public:
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns StatusCode of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(Pigeon2Configuration &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns StatusCode of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(Pigeon2Configuration &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode Apply(const Pigeon2Configuration &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode Apply(const Pigeon2Configuration &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, configs.FutureProofConfigs, false);
    }


    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns StatusCode of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(MountPoseConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns StatusCode of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(MountPoseConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode Apply(const MountPoseConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode Apply(const MountPoseConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns StatusCode of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(GyroTrimConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns StatusCode of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(GyroTrimConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode Apply(const GyroTrimConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode Apply(const GyroTrimConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns StatusCode of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(Pigeon2FeaturesConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns StatusCode of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(Pigeon2FeaturesConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode Apply(const Pigeon2FeaturesConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode Apply(const Pigeon2FeaturesConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    /**
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns StatusCode of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(CustomParamsConfigs &configs) const
    {
        return Refresh(configs, DefaultTimeoutSeconds);
    }
    /**
     * \brief Refreshes the values of the specified config group.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns StatusCode of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(CustomParamsConfigs &configs, units::time::second_t timeoutSeconds) const
    {
        std::string ref;
        ctre::phoenix::StatusCode ret = GetConfigsPrivate(ref, timeoutSeconds);
        configs.Deserialize(ref);
        return ret;
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode Apply(const CustomParamsConfigs &configs)
    {
        return Apply(configs, DefaultTimeoutSeconds);
    }

    /**
     * \brief Applies the contents of the specified config to the device.
     *
     * \details Call to apply the selected configs.
     *
     * \param configs Configs to apply against.
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode Apply(const CustomParamsConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    
    /**
     * \brief The yaw to set the Pigeon2 to right now.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param newValue Value to set to. Units are in deg.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetYaw(units::angle::degree_t newValue)
    {
        return SetYaw(newValue, DefaultTimeoutSeconds);
    }
    /**
     * \brief The yaw to set the Pigeon2 to right now.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param newValue Value to set to. Units are in deg.
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetYaw(units::angle::degree_t newValue, units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::Pigeon2_SetYaw, newValue.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear the sticky faults in the device.
     * 
     * \details This typically has no impact on the device functionality. 
     * Instead, it just clears telemetry faults that are accessible via
     * API and Tuner Self-Test.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFaults()
    {
        return ClearStickyFaults(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear the sticky faults in the device.
     * 
     * \details This typically has no impact on the device functionality. 
     * Instead, it just clears telemetry faults that are accessible via
     * API and Tuner Self-Test.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFaults(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::SPN_ClearStickyFaults, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Hardware fault occurred
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Hardware()
    {
        return ClearStickyFault_Hardware(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Hardware fault occurred
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Hardware(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_Hardware, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Device supply voltage dropped to near
     * brownout levels
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Undervoltage()
    {
        return ClearStickyFault_Undervoltage(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device supply voltage dropped to near
     * brownout levels
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Undervoltage(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_Undervoltage, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Device boot while detecting the enable
     * signal
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootDuringEnable()
    {
        return ClearStickyFault_BootDuringEnable(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device boot while detecting the enable
     * signal
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootDuringEnable(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_BootDuringEnable, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: An unlicensed feature is in use, device
     * may not behave as expected.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnlicensedFeatureInUse()
    {
        return ClearStickyFault_UnlicensedFeatureInUse(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: An unlicensed feature is in use, device
     * may not behave as expected.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnlicensedFeatureInUse(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_UnlicensedFeatureInUse, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Bootup checks failed: Accelerometer
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupAccelerometer()
    {
        return ClearStickyFault_BootupAccelerometer(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Bootup checks failed: Accelerometer
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupAccelerometer(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_PIGEON2_BootupAccel, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Bootup checks failed: Gyroscope
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupGyroscope()
    {
        return ClearStickyFault_BootupGyroscope(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Bootup checks failed: Gyroscope
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupGyroscope(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_PIGEON2_BootupGyros, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Bootup checks failed: Magnetometer
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupMagnetometer()
    {
        return ClearStickyFault_BootupMagnetometer(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Bootup checks failed: Magnetometer
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupMagnetometer(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_PIGEON2_BootupMagne, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Motion Detected during bootup.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootIntoMotion()
    {
        return ClearStickyFault_BootIntoMotion(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motion Detected during bootup.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootIntoMotion(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_PIGEON2_BootIntoMotion, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Motion stack data acquisition was slower
     * than expected
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DataAcquiredLate()
    {
        return ClearStickyFault_DataAcquiredLate(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motion stack data acquisition was slower
     * than expected
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DataAcquiredLate(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_PIGEON2_DataAcquiredLate, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Motion stack loop time was slower than
     * expected.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_LoopTimeSlow()
    {
        return ClearStickyFault_LoopTimeSlow(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motion stack loop time was slower than
     * expected.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_LoopTimeSlow(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_PIGEON2_LoopTimeSlow, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Magnetometer values are saturated
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedMagnetometer()
    {
        return ClearStickyFault_SaturatedMagnetometer(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Magnetometer values are saturated
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedMagnetometer(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_PIGEON2_SaturatedMagne, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Accelerometer values are saturated
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedAccelerometer()
    {
        return ClearStickyFault_SaturatedAccelerometer(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Accelerometer values are saturated
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedAccelerometer(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_PIGEON2_SaturatedAccel, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Gyroscope values are saturated
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedGyroscope()
    {
        return ClearStickyFault_SaturatedGyroscope(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Gyroscope values are saturated
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedGyroscope(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_PIGEON2_SaturatedGyros, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
};

}

namespace hardware {
namespace core {

/**
 * Class description for the Pigeon 2 IMU sensor that measures orientation.
 */
class CorePigeon2 : public ParentDevice
{
private:
    configs::Pigeon2Configurator _configs;

public:
    using Configuration = configs::Pigeon2Configuration;

    /**
     * Constructs a new Pigeon 2 sensor object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner.
     * \param canbus      Name of the CAN bus this device is on. Possible CAN bus strings are:
     *                    - "rio" for the native roboRIO CAN bus
     *                    - CANivore name or serial number
     *                    - SocketCAN interface (non-FRC Linux only)
     *                    - "*" for any CANivore seen by the program
     *                    - empty string (default) to select the default for the system:
     *                      - "rio" on roboRIO
     *                      - "can0" on Linux
     *                      - "*" on Windows
     */
    CorePigeon2(int deviceId, std::string canbus = "");

    /**
     * Constructs a new Pigeon 2 sensor object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner.
     * \param canbus      The CAN bus this device is on.
     */
    CorePigeon2(int deviceId, CANBus canbus) :
        CorePigeon2{deviceId, std::string{canbus.GetName()}}
    {}

    /**
     * \brief Gets the configurator for this Pigeon2
     *
     * \details Gets the configurator for this Pigeon2
     *
     * \returns Configurator for this Pigeon2
     */
    configs::Pigeon2Configurator &GetConfigurator()
    {
        return _configs;
    }

    /**
     * \brief Gets the configurator for this Pigeon2
     *
     * \details Gets the configurator for this Pigeon2
     *
     * \returns Configurator for this Pigeon2
     */
    configs::Pigeon2Configurator const &GetConfigurator() const
    {
        return _configs;
    }


private:
    std::unique_ptr<sim::Pigeon2SimState> _simState{};
public:
    /**
     * \brief Get the simulation state for this device.
     *
     * \details This function reuses an allocated simulation
     * state object, so it is safe to call this function multiple
     * times in a robot loop.
     *
     * \returns Simulation state
     */
    sim::Pigeon2SimState &GetSimState()
    {
        if (_simState == nullptr)
            _simState = std::make_unique<sim::Pigeon2SimState>(*this);
        return *_simState;
    }


        
    /**
     * \brief App Major Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns VersionMajor Status Signal Object
     */
    StatusSignal<int> &GetVersionMajor(bool refresh = true);
        
    /**
     * \brief App Minor Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns VersionMinor Status Signal Object
     */
    StatusSignal<int> &GetVersionMinor(bool refresh = true);
        
    /**
     * \brief App Bugfix Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns VersionBugfix Status Signal Object
     */
    StatusSignal<int> &GetVersionBugfix(bool refresh = true);
        
    /**
     * \brief App Build Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns VersionBuild Status Signal Object
     */
    StatusSignal<int> &GetVersionBuild(bool refresh = true);
        
    /**
     * \brief Full Version of firmware in device.  The format is a four
     * byte value.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 4294967295
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Version Status Signal Object
     */
    StatusSignal<int> &GetVersion(bool refresh = true);
        
    /**
     * \brief Integer representing all fault flags reported by the device.
     * 
     * \details These are device specific and are not used directly in
     * typical applications. Use the signal specific GetFault_*() methods
     * instead.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 4294967295
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns FaultField Status Signal Object
     */
    StatusSignal<int> &GetFaultField(bool refresh = true);
        
    /**
     * \brief Integer representing all (persistent) sticky fault flags
     * reported by the device.
     * 
     * \details These are device specific and are not used directly in
     * typical applications. Use the signal specific GetStickyFault_*()
     * methods instead.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 4294967295
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFaultField Status Signal Object
     */
    StatusSignal<int> &GetStickyFaultField(bool refresh = true);
        
    /**
     * \brief Current reported yaw of the Pigeon2.
     * 
     * - Minimum Value: -368640.0
     * - Maximum Value: 368639.99725341797
     * - Default Value: 0
     * - Units: deg
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Yaw Status Signal Object
     */
    StatusSignal<units::angle::degree_t> &GetYaw(bool refresh = true);
        
    /**
     * \brief Current reported pitch of the Pigeon2.
     * 
     * - Minimum Value: -90.0
     * - Maximum Value: 89.9560546875
     * - Default Value: 0
     * - Units: deg
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Pitch Status Signal Object
     */
    StatusSignal<units::angle::degree_t> &GetPitch(bool refresh = true);
        
    /**
     * \brief Current reported roll of the Pigeon2.
     * 
     * - Minimum Value: -180.0
     * - Maximum Value: 179.9560546875
     * - Default Value: 0
     * - Units: deg
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Roll Status Signal Object
     */
    StatusSignal<units::angle::degree_t> &GetRoll(bool refresh = true);
        
    /**
     * \brief The W component of the reported Quaternion.
     * 
     * - Minimum Value: -1.0001220852154804
     * - Maximum Value: 1.0
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 50.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns QuatW Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetQuatW(bool refresh = true);
        
    /**
     * \brief The X component of the reported Quaternion.
     * 
     * - Minimum Value: -1.0001220852154804
     * - Maximum Value: 1.0
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 50.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns QuatX Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetQuatX(bool refresh = true);
        
    /**
     * \brief The Y component of the reported Quaternion.
     * 
     * - Minimum Value: -1.0001220852154804
     * - Maximum Value: 1.0
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 50.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns QuatY Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetQuatY(bool refresh = true);
        
    /**
     * \brief The Z component of the reported Quaternion.
     * 
     * - Minimum Value: -1.0001220852154804
     * - Maximum Value: 1.0
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 50.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns QuatZ Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetQuatZ(bool refresh = true);
        
    /**
     * \brief The X component of the gravity vector.
     * 
     * \details This is the X component of the reported gravity-vector.
     * The gravity vector is not the acceleration experienced by the
     * Pigeon2, rather it is where the Pigeon2 believes "Down" is. This
     * can be used for mechanisms that are linearly related to gravity,
     * such as an arm pivoting about a point, as the contribution of
     * gravity to the arm is directly proportional to the contribution of
     * gravity about one of these primary axis.
     * 
     * - Minimum Value: -1.000030518509476
     * - Maximum Value: 1.0
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns GravityVectorX Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetGravityVectorX(bool refresh = true);
        
    /**
     * \brief The Y component of the gravity vector.
     * 
     * \details This is the X component of the reported gravity-vector.
     * The gravity vector is not the acceleration experienced by the
     * Pigeon2, rather it is where the Pigeon2 believes "Down" is. This
     * can be used for mechanisms that are linearly related to gravity,
     * such as an arm pivoting about a point, as the contribution of
     * gravity to the arm is directly proportional to the contribution of
     * gravity about one of these primary axis.
     * 
     * - Minimum Value: -1.000030518509476
     * - Maximum Value: 1.0
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns GravityVectorY Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetGravityVectorY(bool refresh = true);
        
    /**
     * \brief The Z component of the gravity vector.
     * 
     * \details This is the Z component of the reported gravity-vector.
     * The gravity vector is not the acceleration experienced by the
     * Pigeon2, rather it is where the Pigeon2 believes "Down" is. This
     * can be used for mechanisms that are linearly related to gravity,
     * such as an arm pivoting about a point, as the contribution of
     * gravity to the arm is directly proportional to the contribution of
     * gravity about one of these primary axis.
     * 
     * - Minimum Value: -1.000030518509476
     * - Maximum Value: 1.0
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns GravityVectorZ Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetGravityVectorZ(bool refresh = true);
        
    /**
     * \brief Temperature of the Pigeon 2.
     * 
     * - Minimum Value: -128.0
     * - Maximum Value: 127.99609375
     * - Default Value: 0
     * - Units: ℃
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Temperature Status Signal Object
     */
    StatusSignal<units::temperature::celsius_t> &GetTemperature(bool refresh = true);
        
    /**
     * \brief Whether the no-motion calibration feature is enabled.
     * 
     * - Default Value: 0
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns NoMotionEnabled Status Signal Object
     */
    StatusSignal<bool> &GetNoMotionEnabled(bool refresh = true);
        
    /**
     * \brief The number of times a no-motion event occurred, wraps at 15.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 15
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns NoMotionCount Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetNoMotionCount(bool refresh = true);
        
    /**
     * \brief Whether the temperature-compensation feature is disabled.
     * 
     * - Default Value: 0
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns TemperatureCompensationDisabled Status Signal Object
     */
    StatusSignal<bool> &GetTemperatureCompensationDisabled(bool refresh = true);
        
    /**
     * \brief How long the Pigeon 2's been up in seconds, caps at 255
     * seconds.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: s
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns UpTime Status Signal Object
     */
    StatusSignal<units::time::second_t> &GetUpTime(bool refresh = true);
        
    /**
     * \brief The accumulated gyro about the X axis without any sensor
     * fusing.
     * 
     * - Minimum Value: -23040.0
     * - Maximum Value: 23039.9560546875
     * - Default Value: 0
     * - Units: deg
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AccumGyroX Status Signal Object
     */
    StatusSignal<units::angle::degree_t> &GetAccumGyroX(bool refresh = true);
        
    /**
     * \brief The accumulated gyro about the Y axis without any sensor
     * fusing.
     * 
     * - Minimum Value: -23040.0
     * - Maximum Value: 23039.9560546875
     * - Default Value: 0
     * - Units: deg
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AccumGyroY Status Signal Object
     */
    StatusSignal<units::angle::degree_t> &GetAccumGyroY(bool refresh = true);
        
    /**
     * \brief The accumulated gyro about the Z axis without any sensor
     * fusing.
     * 
     * - Minimum Value: -23040.0
     * - Maximum Value: 23039.9560546875
     * - Default Value: 0
     * - Units: deg
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AccumGyroZ Status Signal Object
     */
    StatusSignal<units::angle::degree_t> &GetAccumGyroZ(bool refresh = true);
        
    /**
     * \brief The angular velocity (ω) of the Pigeon 2 about the X axis
     * with respect to the world frame.  This value is mount-calibrated.
     * 
     * - Minimum Value: -2048.0
     * - Maximum Value: 2047.99609375
     * - Default Value: 0
     * - Units: dps
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AngularVelocityXWorld Status Signal Object
     */
    StatusSignal<units::angular_velocity::degrees_per_second_t> &GetAngularVelocityXWorld(bool refresh = true);
        
    /**
     * \brief The angular velocity (ω) of the Pigeon 2 about the Y axis
     * with respect to the world frame.  This value is mount-calibrated.
     * 
     * - Minimum Value: -2048.0
     * - Maximum Value: 2047.99609375
     * - Default Value: 0
     * - Units: dps
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AngularVelocityYWorld Status Signal Object
     */
    StatusSignal<units::angular_velocity::degrees_per_second_t> &GetAngularVelocityYWorld(bool refresh = true);
        
    /**
     * \brief The angular velocity (ω) of the Pigeon 2 about the Z axis
     * with respect to the world frame.  This value is mount-calibrated.
     * 
     * - Minimum Value: -2048.0
     * - Maximum Value: 2047.99609375
     * - Default Value: 0
     * - Units: dps
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AngularVelocityZWorld Status Signal Object
     */
    StatusSignal<units::angular_velocity::degrees_per_second_t> &GetAngularVelocityZWorld(bool refresh = true);
        
    /**
     * \brief The acceleration measured by Pigeon2 in the X direction.
     * 
     * \details This value includes the acceleration due to gravity. If
     * this is undesirable, get the gravity vector and subtract out the
     * contribution in this direction.
     * 
     * - Minimum Value: -2.0
     * - Maximum Value: 1.99993896484375
     * - Default Value: 0
     * - Units: g
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AccelerationX Status Signal Object
     */
    StatusSignal<units::acceleration::standard_gravity_t> &GetAccelerationX(bool refresh = true);
        
    /**
     * \brief The acceleration measured by Pigeon2 in the Y direction.
     * 
     * \details This value includes the acceleration due to gravity. If
     * this is undesirable, get the gravity vector and subtract out the
     * contribution in this direction.
     * 
     * - Minimum Value: -2.0
     * - Maximum Value: 1.99993896484375
     * - Default Value: 0
     * - Units: g
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AccelerationY Status Signal Object
     */
    StatusSignal<units::acceleration::standard_gravity_t> &GetAccelerationY(bool refresh = true);
        
    /**
     * \brief The acceleration measured by Pigeon2 in the Z direction.
     * 
     * \details This value includes the acceleration due to gravity. If
     * this is undesirable, get the gravity vector and subtract out the
     * contribution in this direction.
     * 
     * - Minimum Value: -2.0
     * - Maximum Value: 1.99993896484375
     * - Default Value: 0
     * - Units: g
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AccelerationZ Status Signal Object
     */
    StatusSignal<units::acceleration::standard_gravity_t> &GetAccelerationZ(bool refresh = true);
        
    /**
     * \brief Measured supply voltage to the Pigeon2.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 31.99951171875
     * - Default Value: 0
     * - Units: V
     * 
     * Default Rates:
     * - CAN 2.0: 4.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns SupplyVoltage Status Signal Object
     */
    StatusSignal<units::voltage::volt_t> &GetSupplyVoltage(bool refresh = true);
        
    /**
     * \brief The angular velocity (ω) of the Pigeon 2 about the device's
     * X axis.
     * 
     * \details This value is not mount-calibrated.
     * 
     * - Minimum Value: -1998.048780487805
     * - Maximum Value: 1997.987804878049
     * - Default Value: 0
     * - Units: dps
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AngularVelocityXDevice Status Signal Object
     */
    StatusSignal<units::angular_velocity::degrees_per_second_t> &GetAngularVelocityXDevice(bool refresh = true);
        
    /**
     * \brief The angular velocity (ω) of the Pigeon 2 about the device's
     * Y axis.
     * 
     * \details This value is not mount-calibrated.
     * 
     * - Minimum Value: -1998.048780487805
     * - Maximum Value: 1997.987804878049
     * - Default Value: 0
     * - Units: dps
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AngularVelocityYDevice Status Signal Object
     */
    StatusSignal<units::angular_velocity::degrees_per_second_t> &GetAngularVelocityYDevice(bool refresh = true);
        
    /**
     * \brief The angular velocity (ω) of the Pigeon 2 about the device's
     * Z axis.
     * 
     * \details This value is not mount-calibrated.
     * 
     * - Minimum Value: -1998.048780487805
     * - Maximum Value: 1997.987804878049
     * - Default Value: 0
     * - Units: dps
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AngularVelocityZDevice Status Signal Object
     */
    StatusSignal<units::angular_velocity::degrees_per_second_t> &GetAngularVelocityZDevice(bool refresh = true);
        
    /**
     * \brief The biased magnitude of the magnetic field measured by the
     * Pigeon 2 in the X direction. This is only valid after performing a
     * magnetometer calibration.
     * 
     * - Minimum Value: -19660.8
     * - Maximum Value: 19660.2
     * - Default Value: 0
     * - Units: uT
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MagneticFieldX Status Signal Object
     */
    StatusSignal<units::magnetic_field_strength::microtesla_t> &GetMagneticFieldX(bool refresh = true);
        
    /**
     * \brief The biased magnitude of the magnetic field measured by the
     * Pigeon 2 in the Y direction. This is only valid after performing a
     * magnetometer calibration.
     * 
     * - Minimum Value: -19660.8
     * - Maximum Value: 19660.2
     * - Default Value: 0
     * - Units: uT
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MagneticFieldY Status Signal Object
     */
    StatusSignal<units::magnetic_field_strength::microtesla_t> &GetMagneticFieldY(bool refresh = true);
        
    /**
     * \brief The biased magnitude of the magnetic field measured by the
     * Pigeon 2 in the Z direction. This is only valid after performing a
     * magnetometer calibration.
     * 
     * - Minimum Value: -19660.8
     * - Maximum Value: 19660.2
     * - Default Value: 0
     * - Units: uT
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MagneticFieldZ Status Signal Object
     */
    StatusSignal<units::magnetic_field_strength::microtesla_t> &GetMagneticFieldZ(bool refresh = true);
        
    /**
     * \brief The raw magnitude of the magnetic field measured by the
     * Pigeon 2 in the X direction. This is only valid after performing a
     * magnetometer calibration.
     * 
     * - Minimum Value: -19660.8
     * - Maximum Value: 19660.2
     * - Default Value: 0
     * - Units: uT
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns RawMagneticFieldX Status Signal Object
     */
    StatusSignal<units::magnetic_field_strength::microtesla_t> &GetRawMagneticFieldX(bool refresh = true);
        
    /**
     * \brief The raw magnitude of the magnetic field measured by the
     * Pigeon 2 in the Y direction. This is only valid after performing a
     * magnetometer calibration.
     * 
     * - Minimum Value: -19660.8
     * - Maximum Value: 19660.2
     * - Default Value: 0
     * - Units: uT
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns RawMagneticFieldY Status Signal Object
     */
    StatusSignal<units::magnetic_field_strength::microtesla_t> &GetRawMagneticFieldY(bool refresh = true);
        
    /**
     * \brief The raw magnitude of the magnetic field measured by the
     * Pigeon 2 in the Z direction. This is only valid after performing a
     * magnetometer calibration.
     * 
     * - Minimum Value: -19660.8
     * - Maximum Value: 19660.2
     * - Default Value: 0
     * - Units: uT
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns RawMagneticFieldZ Status Signal Object
     */
    StatusSignal<units::magnetic_field_strength::microtesla_t> &GetRawMagneticFieldZ(bool refresh = true);
        
    /**
     * \brief Whether the device is Phoenix Pro licensed.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns IsProLicensed Status Signal Object
     */
    StatusSignal<bool> &GetIsProLicensed(bool refresh = true);
        
    /**
     * \brief Hardware fault occurred
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_Hardware Status Signal Object
     */
    StatusSignal<bool> &GetFault_Hardware(bool refresh = true);
        
    /**
     * \brief Hardware fault occurred
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_Hardware Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_Hardware(bool refresh = true);
        
    /**
     * \brief Device supply voltage dropped to near brownout levels
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_Undervoltage Status Signal Object
     */
    StatusSignal<bool> &GetFault_Undervoltage(bool refresh = true);
        
    /**
     * \brief Device supply voltage dropped to near brownout levels
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_Undervoltage Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_Undervoltage(bool refresh = true);
        
    /**
     * \brief Device boot while detecting the enable signal
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_BootDuringEnable Status Signal Object
     */
    StatusSignal<bool> &GetFault_BootDuringEnable(bool refresh = true);
        
    /**
     * \brief Device boot while detecting the enable signal
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_BootDuringEnable Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_BootDuringEnable(bool refresh = true);
        
    /**
     * \brief An unlicensed feature is in use, device may not behave as
     * expected.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_UnlicensedFeatureInUse Status Signal Object
     */
    StatusSignal<bool> &GetFault_UnlicensedFeatureInUse(bool refresh = true);
        
    /**
     * \brief An unlicensed feature is in use, device may not behave as
     * expected.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_UnlicensedFeatureInUse Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_UnlicensedFeatureInUse(bool refresh = true);
        
    /**
     * \brief Bootup checks failed: Accelerometer
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_BootupAccelerometer Status Signal Object
     */
    StatusSignal<bool> &GetFault_BootupAccelerometer(bool refresh = true);
        
    /**
     * \brief Bootup checks failed: Accelerometer
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_BootupAccelerometer Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_BootupAccelerometer(bool refresh = true);
        
    /**
     * \brief Bootup checks failed: Gyroscope
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_BootupGyroscope Status Signal Object
     */
    StatusSignal<bool> &GetFault_BootupGyroscope(bool refresh = true);
        
    /**
     * \brief Bootup checks failed: Gyroscope
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_BootupGyroscope Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_BootupGyroscope(bool refresh = true);
        
    /**
     * \brief Bootup checks failed: Magnetometer
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_BootupMagnetometer Status Signal Object
     */
    StatusSignal<bool> &GetFault_BootupMagnetometer(bool refresh = true);
        
    /**
     * \brief Bootup checks failed: Magnetometer
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_BootupMagnetometer Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_BootupMagnetometer(bool refresh = true);
        
    /**
     * \brief Motion Detected during bootup.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_BootIntoMotion Status Signal Object
     */
    StatusSignal<bool> &GetFault_BootIntoMotion(bool refresh = true);
        
    /**
     * \brief Motion Detected during bootup.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_BootIntoMotion Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_BootIntoMotion(bool refresh = true);
        
    /**
     * \brief Motion stack data acquisition was slower than expected
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_DataAcquiredLate Status Signal Object
     */
    StatusSignal<bool> &GetFault_DataAcquiredLate(bool refresh = true);
        
    /**
     * \brief Motion stack data acquisition was slower than expected
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_DataAcquiredLate Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_DataAcquiredLate(bool refresh = true);
        
    /**
     * \brief Motion stack loop time was slower than expected.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_LoopTimeSlow Status Signal Object
     */
    StatusSignal<bool> &GetFault_LoopTimeSlow(bool refresh = true);
        
    /**
     * \brief Motion stack loop time was slower than expected.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_LoopTimeSlow Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_LoopTimeSlow(bool refresh = true);
        
    /**
     * \brief Magnetometer values are saturated
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_SaturatedMagnetometer Status Signal Object
     */
    StatusSignal<bool> &GetFault_SaturatedMagnetometer(bool refresh = true);
        
    /**
     * \brief Magnetometer values are saturated
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_SaturatedMagnetometer Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_SaturatedMagnetometer(bool refresh = true);
        
    /**
     * \brief Accelerometer values are saturated
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_SaturatedAccelerometer Status Signal Object
     */
    StatusSignal<bool> &GetFault_SaturatedAccelerometer(bool refresh = true);
        
    /**
     * \brief Accelerometer values are saturated
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_SaturatedAccelerometer Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_SaturatedAccelerometer(bool refresh = true);
        
    /**
     * \brief Gyroscope values are saturated
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_SaturatedGyroscope Status Signal Object
     */
    StatusSignal<bool> &GetFault_SaturatedGyroscope(bool refresh = true);
        
    /**
     * \brief Gyroscope values are saturated
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_SaturatedGyroscope Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_SaturatedGyroscope(bool refresh = true);

    

    /**
     * \brief Control device with generic control request object. User must make
     *        sure the specified object is castable to a valid control request,
     *        otherwise this function will fail at run-time and return the NotSupported
     *        StatusCode
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::ControlRequest &request)
    {
        controls::ControlRequest const *ptr = &request;
        (void)ptr;
        
        return ctre::phoenix::StatusCode::NotSupported;
    }

    
    /**
     * \brief The yaw to set the Pigeon2 to right now.
     * 
     * \param newValue Value to set to. Units are in deg.
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetYaw(units::angle::degree_t newValue, units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().SetYaw(newValue, timeoutSeconds);
    }
    /**
     * \brief The yaw to set the Pigeon2 to right now.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \param newValue Value to set to. Units are in deg.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetYaw(units::angle::degree_t newValue)
    {
        return SetYaw(newValue, 0.100_s);
    }
    
    /**
     * \brief Clear the sticky faults in the device.
     * 
     * \details This typically has no impact on the device functionality. 
     * Instead, it just clears telemetry faults that are accessible via
     * API and Tuner Self-Test.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFaults(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFaults(timeoutSeconds);
    }
    /**
     * \brief Clear the sticky faults in the device.
     * 
     * \details This typically has no impact on the device functionality. 
     * Instead, it just clears telemetry faults that are accessible via
     * API and Tuner Self-Test.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFaults()
    {
        return ClearStickyFaults(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Hardware fault occurred
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Hardware(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_Hardware(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Hardware fault occurred
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Hardware()
    {
        return ClearStickyFault_Hardware(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Device supply voltage dropped to near
     * brownout levels
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Undervoltage(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_Undervoltage(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device supply voltage dropped to near
     * brownout levels
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Undervoltage()
    {
        return ClearStickyFault_Undervoltage(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Device boot while detecting the enable
     * signal
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootDuringEnable(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_BootDuringEnable(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device boot while detecting the enable
     * signal
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootDuringEnable()
    {
        return ClearStickyFault_BootDuringEnable(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: An unlicensed feature is in use, device
     * may not behave as expected.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnlicensedFeatureInUse(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_UnlicensedFeatureInUse(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: An unlicensed feature is in use, device
     * may not behave as expected.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_UnlicensedFeatureInUse()
    {
        return ClearStickyFault_UnlicensedFeatureInUse(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Bootup checks failed: Accelerometer
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupAccelerometer(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_BootupAccelerometer(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Bootup checks failed: Accelerometer
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupAccelerometer()
    {
        return ClearStickyFault_BootupAccelerometer(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Bootup checks failed: Gyroscope
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupGyroscope(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_BootupGyroscope(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Bootup checks failed: Gyroscope
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupGyroscope()
    {
        return ClearStickyFault_BootupGyroscope(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Bootup checks failed: Magnetometer
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupMagnetometer(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_BootupMagnetometer(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Bootup checks failed: Magnetometer
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootupMagnetometer()
    {
        return ClearStickyFault_BootupMagnetometer(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Motion Detected during bootup.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootIntoMotion(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_BootIntoMotion(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motion Detected during bootup.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_BootIntoMotion()
    {
        return ClearStickyFault_BootIntoMotion(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Motion stack data acquisition was slower
     * than expected
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DataAcquiredLate(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_DataAcquiredLate(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motion stack data acquisition was slower
     * than expected
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_DataAcquiredLate()
    {
        return ClearStickyFault_DataAcquiredLate(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Motion stack loop time was slower than
     * expected.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_LoopTimeSlow(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_LoopTimeSlow(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Motion stack loop time was slower than
     * expected.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_LoopTimeSlow()
    {
        return ClearStickyFault_LoopTimeSlow(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Magnetometer values are saturated
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedMagnetometer(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_SaturatedMagnetometer(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Magnetometer values are saturated
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedMagnetometer()
    {
        return ClearStickyFault_SaturatedMagnetometer(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Accelerometer values are saturated
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedAccelerometer(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_SaturatedAccelerometer(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Accelerometer values are saturated
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedAccelerometer()
    {
        return ClearStickyFault_SaturatedAccelerometer(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Gyroscope values are saturated
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedGyroscope(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_SaturatedGyroscope(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Gyroscope values are saturated
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SaturatedGyroscope()
    {
        return ClearStickyFault_SaturatedGyroscope(0.100_s);
    }
};

}
}

}
}

