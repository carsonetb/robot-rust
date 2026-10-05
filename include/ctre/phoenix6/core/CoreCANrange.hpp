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


#include "ctre/phoenix6/sim/CANrangeSimState.hpp"
#include <units/angle.h>
#include <units/dimensionless.h>
#include <units/length.h>
#include <units/time.h>
#include <units/voltage.h>

namespace ctre {
namespace phoenix6 {

namespace hardware {
namespace core {
    class CoreCANrange;
}
}

namespace configs {

/**
 * Class for CANrange, a CAN based Time of Flight (ToF) sensor that measures the
 * distance to the front of the device.
 *
 * This handles the configurations for the hardware#CANrange
 */
class CANrangeConfiguration : public ParentConfiguration
{
public:
    constexpr CANrangeConfiguration() = default;

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
     * \brief Configs that affect the ToF sensor
     * 
     * \details Includes Update mode and frequency
     * 
     * Parameter list:
     * 
     * - ToFParamsConfigs#UpdateMode
     * - ToFParamsConfigs#UpdateFrequency
     * 
     */
    ToFParamsConfigs ToFParams;
    
    /**
     * \brief Configs that affect the ToF Proximity detection
     * 
     * \details Includes proximity mode and the threshold for simple
     *          detection
     * 
     * Parameter list:
     * 
     * - ProximityParamsConfigs#ProximityThreshold
     * - ProximityParamsConfigs#ProximityHysteresis
     * - ProximityParamsConfigs#MinSignalStrengthForValidMeasurement
     * 
     */
    ProximityParamsConfigs ProximityParams;
    
    /**
     * \brief Configs that affect the ToF Field of View
     * 
     * \details Includes range and center configs
     * 
     * Parameter list:
     * 
     * - FovParamsConfigs#FOVCenterX
     * - FovParamsConfigs#FOVCenterY
     * - FovParamsConfigs#FOVRangeX
     * - FovParamsConfigs#FOVRangeY
     * 
     */
    FovParamsConfigs FovParams;
    
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
    constexpr CANrangeConfiguration &WithCustomParams(CustomParamsConfigs newCustomParams)
    {
        CustomParams = std::move(newCustomParams);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ToFParams parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that affect the ToF sensor
     * 
     * \details Includes Update mode and frequency
     * 
     * Parameter list:
     * 
     * - ToFParamsConfigs#UpdateMode
     * - ToFParamsConfigs#UpdateFrequency
     * 
     *
     * \param newToFParams Parameter to modify
     * \returns Itself
     */
    constexpr CANrangeConfiguration &WithToFParams(ToFParamsConfigs newToFParams)
    {
        ToFParams = std::move(newToFParams);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's ProximityParams parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that affect the ToF Proximity detection
     * 
     * \details Includes proximity mode and the threshold for simple
     *          detection
     * 
     * Parameter list:
     * 
     * - ProximityParamsConfigs#ProximityThreshold
     * - ProximityParamsConfigs#ProximityHysteresis
     * - ProximityParamsConfigs#MinSignalStrengthForValidMeasurement
     * 
     *
     * \param newProximityParams Parameter to modify
     * \returns Itself
     */
    constexpr CANrangeConfiguration &WithProximityParams(ProximityParamsConfigs newProximityParams)
    {
        ProximityParams = std::move(newProximityParams);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's FovParams parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs that affect the ToF Field of View
     * 
     * \details Includes range and center configs
     * 
     * Parameter list:
     * 
     * - FovParamsConfigs#FOVCenterX
     * - FovParamsConfigs#FOVCenterY
     * - FovParamsConfigs#FOVRangeX
     * - FovParamsConfigs#FOVRangeY
     * 
     *
     * \param newFovParams Parameter to modify
     * \returns Itself
     */
    constexpr CANrangeConfiguration &WithFovParams(FovParamsConfigs newFovParams)
    {
        FovParams = std::move(newFovParams);
        return *this;
    }

    /**
     * \brief Get the string representation of this configuration
     */
    std::string ToString() const
    {
        std::stringstream ss;
        ss << "CANrangeConfiguration" << std::endl;
        ss << CustomParams.ToString();
        ss << ToFParams.ToString();
        ss << ProximityParams.ToString();
        ss << FovParams.ToString();
        return ss.str();
    }

    /**
     * \brief Get the serialized form of this configuration
     */
    std::string Serialize() const
    {
        std::stringstream ss;
        ss << CustomParams.Serialize();
        ss << ToFParams.Serialize();
        ss << ProximityParams.Serialize();
        ss << FovParams.Serialize();
        return ss.str();
    }

    /**
     * \brief Take a string and deserialize it to this configuration
     */
    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize)
    {
        ctre::phoenix::StatusCode err = ctre::phoenix::StatusCode::OK;
        err = CustomParams.Deserialize(to_deserialize);
        err = ToFParams.Deserialize(to_deserialize);
        err = ProximityParams.Deserialize(to_deserialize);
        err = FovParams.Deserialize(to_deserialize);
        return err;
    }
};

/**
 * Class for CANrange, a CAN based Time of Flight (ToF) sensor that measures the
 * distance to the front of the device.
 *
 * This handles the configurations for the hardware#CANrange
 */
class CANrangeConfigurator : public ParentConfigurator
{
private:
    CANrangeConfigurator(hardware::DeviceIdentifier id) :
        ParentConfigurator{std::move(id)}
    {}

    friend hardware::core::CoreCANrange;

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
    ctre::phoenix::StatusCode Refresh(CANrangeConfiguration &configs) const
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
    ctre::phoenix::StatusCode Refresh(CANrangeConfiguration &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const CANrangeConfiguration &configs)
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
    ctre::phoenix::StatusCode Apply(const CANrangeConfiguration &configs, units::time::second_t timeoutSeconds)
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
     * \brief Refreshes the values of the specified config group.
     *
     * This will wait up to #DefaultTimeoutSeconds.
     *
     * \details Call to refresh the selected configs from the device.
     *
     * \param configs The configs to refresh
     * \returns StatusCode of refreshing the configs
     */
    ctre::phoenix::StatusCode Refresh(ToFParamsConfigs &configs) const
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
    ctre::phoenix::StatusCode Refresh(ToFParamsConfigs &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const ToFParamsConfigs &configs)
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
    ctre::phoenix::StatusCode Apply(const ToFParamsConfigs &configs, units::time::second_t timeoutSeconds)
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
    ctre::phoenix::StatusCode Refresh(ProximityParamsConfigs &configs) const
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
    ctre::phoenix::StatusCode Refresh(ProximityParamsConfigs &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const ProximityParamsConfigs &configs)
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
    ctre::phoenix::StatusCode Apply(const ProximityParamsConfigs &configs, units::time::second_t timeoutSeconds)
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
    ctre::phoenix::StatusCode Refresh(FovParamsConfigs &configs) const
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
    ctre::phoenix::StatusCode Refresh(FovParamsConfigs &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const FovParamsConfigs &configs)
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
    ctre::phoenix::StatusCode Apply(const FovParamsConfigs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
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
};

}

namespace hardware {
namespace core {

/**
 * Class for CANrange, a CAN based Time of Flight (ToF) sensor that measures the
 * distance to the front of the device.
 */
class CoreCANrange : public ParentDevice
{
private:
    configs::CANrangeConfigurator _configs;

public:
    using Configuration = configs::CANrangeConfiguration;

    /**
     * Constructs a new CANrange object.
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
    CoreCANrange(int deviceId, std::string canbus = "");

    /**
     * Constructs a new CANrange object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner.
     * \param canbus      The CAN bus this device is on.
     */
    CoreCANrange(int deviceId, CANBus canbus) :
        CoreCANrange{deviceId, std::string{canbus.GetName()}}
    {}

    /**
     * \brief Gets the configurator for this CANrange
     *
     * \details Gets the configurator for this CANrange
     *
     * \returns Configurator for this CANrange
     */
    configs::CANrangeConfigurator &GetConfigurator()
    {
        return _configs;
    }

    /**
     * \brief Gets the configurator for this CANrange
     *
     * \details Gets the configurator for this CANrange
     *
     * \returns Configurator for this CANrange
     */
    configs::CANrangeConfigurator const &GetConfigurator() const
    {
        return _configs;
    }


private:
    std::unique_ptr<sim::CANrangeSimState> _simState{};
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
    sim::CANrangeSimState &GetSimState()
    {
        if (_simState == nullptr)
            _simState = std::make_unique<sim::CANrangeSimState>(*this);
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
     * \brief Measured supply voltage to the CANrange.
     * 
     * - Minimum Value: 4
     * - Maximum Value: 16.75
     * - Default Value: 4
     * - Units: V
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns SupplyVoltage Status Signal Object
     */
    StatusSignal<units::voltage::volt_t> &GetSupplyVoltage(bool refresh = true);
        
    /**
     * \brief Distance to the nearest object in the configured field of
     * view of the CANrange.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 65.535
     * - Default Value: 0
     * - Units: m
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Distance Status Signal Object
     */
    StatusSignal<units::length::meter_t> &GetDistance(bool refresh = true);
        
    /**
     * \brief Timestamp of the most recent measurements. This is not
     * synchronized to any other clock source.
     * 
     * Users can use this to check when the measurements are updated.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 65.535
     * - Default Value: 0
     * - Units: s
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MeasurementTime Status Signal Object
     */
    StatusSignal<units::time::second_t> &GetMeasurementTime(bool refresh = true);
        
    /**
     * \brief Approximate signal strength of the measurement. A higher
     * value indicates a higher strength of signal.
     * 
     * A value of ~2500 is typical when detecting an object under
     * short-range conditions.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 65535
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns SignalStrength Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetSignalStrength(bool refresh = true);
        
    /**
     * \brief Whether the CANrange detects an object using the configured
     * proximity parameters.
     * 
     * - Default Value: 0
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns IsDetected Status Signal Object
     */
    StatusSignal<bool> &GetIsDetected(bool refresh = true);
        
    /**
     * \brief Health of the distance measurement.
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MeasurementHealth Status Signal Object
     */
    StatusSignal<signals::MeasurementHealthValue> &GetMeasurementHealth(bool refresh = true);
        
    /**
     * \brief The amount of ambient infrared light that the sensor is
     * detecting. For ideal operation, this should be as low as possible.
     * 
     * \details Short-range mode reduces the influence of ambient infrared
     * light.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 65535
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 20.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AmbientSignal Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetAmbientSignal(bool refresh = true);
        
    /**
     * \brief Standard Deviation of the distance measurement.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.3107000000000002
     * - Default Value: 0
     * - Units: m
     * 
     * Default Rates:
     * - CAN 2.0: 20.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DistanceStdDev Status Signal Object
     */
    StatusSignal<units::length::meter_t> &GetDistanceStdDev(bool refresh = true);
        
    /**
     * \brief The actual center of the FOV in the X direction. This takes
     * into account the user-configured FOVCenterX and FOVRangeX.
     * 
     * - Minimum Value: -16.0
     * - Maximum Value: 15.875
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
     * \returns RealFOVCenterX Status Signal Object
     */
    StatusSignal<units::angle::degree_t> &GetRealFOVCenterX(bool refresh = true);
        
    /**
     * \brief The actual center of the FOV in the Y direction. This takes
     * into account the user-configured FOVCenterY and FOVRangeY.
     * 
     * - Minimum Value: -16.0
     * - Maximum Value: 15.875
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
     * \returns RealFOVCenterY Status Signal Object
     */
    StatusSignal<units::angle::degree_t> &GetRealFOVCenterY(bool refresh = true);
        
    /**
     * \brief The actual range of the FOV in the X direction. This takes
     * into account the user-configured FOVRangeX.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 31.875
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
     * \returns RealFOVRangeX Status Signal Object
     */
    StatusSignal<units::angle::degree_t> &GetRealFOVRangeX(bool refresh = true);
        
    /**
     * \brief The actual range of the FOV in the Y direction. This takes
     * into account the user-configured FOVRangeY.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 31.875
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
     * \returns RealFOVRangeY Status Signal Object
     */
    StatusSignal<units::angle::degree_t> &GetRealFOVRangeY(bool refresh = true);
        
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
};

}
}

}
}

