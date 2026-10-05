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

#include "ctre/phoenix6/controls/ModulateVBatOut.hpp"
#include "ctre/phoenix6/controls/SolidColor.hpp"
#include "ctre/phoenix6/controls/EmptyAnimation.hpp"
#include "ctre/phoenix6/controls/ColorFlowAnimation.hpp"
#include "ctre/phoenix6/controls/FireAnimation.hpp"
#include "ctre/phoenix6/controls/LarsonAnimation.hpp"
#include "ctre/phoenix6/controls/RainbowAnimation.hpp"
#include "ctre/phoenix6/controls/RgbFadeAnimation.hpp"
#include "ctre/phoenix6/controls/SingleFadeAnimation.hpp"
#include "ctre/phoenix6/controls/StrobeAnimation.hpp"
#include "ctre/phoenix6/controls/TwinkleAnimation.hpp"
#include "ctre/phoenix6/controls/TwinkleOffAnimation.hpp"
#include "ctre/phoenix6/sim/CANdleSimState.hpp"
#include <units/current.h>
#include <units/dimensionless.h>
#include <units/temperature.h>
#include <units/voltage.h>

namespace ctre {
namespace phoenix6 {

namespace hardware {
namespace core {
    class CoreCANdle;
}
}

namespace configs {

/**
 * Class for CTR Electronics' CANdle® branded device, a device that controls
 * LEDs over the CAN bus.
 *
 * This handles the configurations for the hardware#CANdle
 */
class CANdleConfiguration : public ParentConfiguration
{
public:
    constexpr CANdleConfiguration() = default;

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
     * \brief Configs related to CANdle LED control.
     * 
     * \details All the configs related to controlling LEDs with the
     *          CANdle, including LED strip type and brightness.
     * 
     * Parameter list:
     * 
     * - LEDConfigs#StripType
     * - LEDConfigs#BrightnessScalar
     * - LEDConfigs#LossOfSignalBehavior
     * 
     */
    LEDConfigs LED;
    
    /**
     * \brief Configs related to general CANdle features.
     * 
     * \details This includes configs such as disabling the 5V rail and
     *          the behavior of VBat output.
     * 
     * Parameter list:
     * 
     * - CANdleFeaturesConfigs#Enable5VRail
     * - CANdleFeaturesConfigs#VBatOutputMode
     * - CANdleFeaturesConfigs#StatusLedWhenActive
     * 
     */
    CANdleFeaturesConfigs CANdleFeatures;
    
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
    constexpr CANdleConfiguration &WithCustomParams(CustomParamsConfigs newCustomParams)
    {
        CustomParams = std::move(newCustomParams);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's LED parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs related to CANdle LED control.
     * 
     * \details All the configs related to controlling LEDs with the
     *          CANdle, including LED strip type and brightness.
     * 
     * Parameter list:
     * 
     * - LEDConfigs#StripType
     * - LEDConfigs#BrightnessScalar
     * - LEDConfigs#LossOfSignalBehavior
     * 
     *
     * \param newLED Parameter to modify
     * \returns Itself
     */
    constexpr CANdleConfiguration &WithLED(LEDConfigs newLED)
    {
        LED = std::move(newLED);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's CANdleFeatures parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs related to general CANdle features.
     * 
     * \details This includes configs such as disabling the 5V rail and
     *          the behavior of VBat output.
     * 
     * Parameter list:
     * 
     * - CANdleFeaturesConfigs#Enable5VRail
     * - CANdleFeaturesConfigs#VBatOutputMode
     * - CANdleFeaturesConfigs#StatusLedWhenActive
     * 
     *
     * \param newCANdleFeatures Parameter to modify
     * \returns Itself
     */
    constexpr CANdleConfiguration &WithCANdleFeatures(CANdleFeaturesConfigs newCANdleFeatures)
    {
        CANdleFeatures = std::move(newCANdleFeatures);
        return *this;
    }

    /**
     * \brief Get the string representation of this configuration
     */
    std::string ToString() const
    {
        std::stringstream ss;
        ss << "CANdleConfiguration" << std::endl;
        ss << CustomParams.ToString();
        ss << LED.ToString();
        ss << CANdleFeatures.ToString();
        return ss.str();
    }

    /**
     * \brief Get the serialized form of this configuration
     */
    std::string Serialize() const
    {
        std::stringstream ss;
        ss << CustomParams.Serialize();
        ss << LED.Serialize();
        ss << CANdleFeatures.Serialize();
        return ss.str();
    }

    /**
     * \brief Take a string and deserialize it to this configuration
     */
    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize)
    {
        ctre::phoenix::StatusCode err = ctre::phoenix::StatusCode::OK;
        err = CustomParams.Deserialize(to_deserialize);
        err = LED.Deserialize(to_deserialize);
        err = CANdleFeatures.Deserialize(to_deserialize);
        return err;
    }
};

/**
 * Class for CTR Electronics' CANdle® branded device, a device that controls
 * LEDs over the CAN bus.
 *
 * This handles the configurations for the hardware#CANdle
 */
class CANdleConfigurator : public ParentConfigurator
{
private:
    CANdleConfigurator(hardware::DeviceIdentifier id) :
        ParentConfigurator{std::move(id)}
    {}

    friend hardware::core::CoreCANdle;

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
    ctre::phoenix::StatusCode Refresh(CANdleConfiguration &configs) const
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
    ctre::phoenix::StatusCode Refresh(CANdleConfiguration &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const CANdleConfiguration &configs)
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
    ctre::phoenix::StatusCode Apply(const CANdleConfiguration &configs, units::time::second_t timeoutSeconds)
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
    ctre::phoenix::StatusCode Refresh(LEDConfigs &configs) const
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
    ctre::phoenix::StatusCode Refresh(LEDConfigs &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const LEDConfigs &configs)
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
    ctre::phoenix::StatusCode Apply(const LEDConfigs &configs, units::time::second_t timeoutSeconds)
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
    ctre::phoenix::StatusCode Refresh(CANdleFeaturesConfigs &configs) const
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
    ctre::phoenix::StatusCode Refresh(CANdleFeaturesConfigs &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const CANdleFeaturesConfigs &configs)
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
    ctre::phoenix::StatusCode Apply(const CANdleFeaturesConfigs &configs, units::time::second_t timeoutSeconds)
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
    
    /**
     * \brief Clear sticky fault: Device supply voltage is too high (above
     * 30 V).
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
    ctre::phoenix::StatusCode ClearStickyFault_Overvoltage()
    {
        return ClearStickyFault_Overvoltage(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device supply voltage is too high (above
     * 30 V).
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
    ctre::phoenix::StatusCode ClearStickyFault_Overvoltage(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_CANDLE_OVERVOLTAGE, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Device 5V line is too high (above 6 V).
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
    ctre::phoenix::StatusCode ClearStickyFault_5VTooHigh()
    {
        return ClearStickyFault_5VTooHigh(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device 5V line is too high (above 6 V).
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
    ctre::phoenix::StatusCode ClearStickyFault_5VTooHigh(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_CANDLE_5V_TOO_HIGH, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Device 5V line is too low (below 4 V).
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
    ctre::phoenix::StatusCode ClearStickyFault_5VTooLow()
    {
        return ClearStickyFault_5VTooLow(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device 5V line is too low (below 4 V).
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
    ctre::phoenix::StatusCode ClearStickyFault_5VTooLow(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_CANDLE_5V_TOO_LOW, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: Device temperature exceeded limit.
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
    ctre::phoenix::StatusCode ClearStickyFault_Thermal()
    {
        return ClearStickyFault_Thermal(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device temperature exceeded limit.
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
    ctre::phoenix::StatusCode ClearStickyFault_Thermal(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_CANDLE_THERMAL, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: CANdle output current exceeded the 6 A
     * limit.
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
    ctre::phoenix::StatusCode ClearStickyFault_SoftwareFuse()
    {
        return ClearStickyFault_SoftwareFuse(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: CANdle output current exceeded the 6 A
     * limit.
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
    ctre::phoenix::StatusCode ClearStickyFault_SoftwareFuse(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_CANDLE_SOFTWARE_FUSE, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
    
    /**
     * \brief Clear sticky fault: CANdle has detected the output pin is
     * shorted.
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
    ctre::phoenix::StatusCode ClearStickyFault_ShortCircuit()
    {
        return ClearStickyFault_ShortCircuit(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: CANdle has detected the output pin is
     * shorted.
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
    ctre::phoenix::StatusCode ClearStickyFault_ShortCircuit(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_CANDLE_SHORT_CIRCUIT, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
};

}

namespace hardware {
namespace core {

/**
 * Class for CTR Electronics' CANdle® branded device, a device that controls
 * LEDs over the CAN bus.
 */
class CoreCANdle : public ParentDevice
{
private:
    configs::CANdleConfigurator _configs;

public:
    using Configuration = configs::CANdleConfiguration;

    /**
     * Constructs a new CANdle object.
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
    CoreCANdle(int deviceId, std::string canbus = "");

    /**
     * Constructs a new CANdle object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner.
     * \param canbus      The CAN bus this device is on.
     */
    CoreCANdle(int deviceId, CANBus canbus) :
        CoreCANdle{deviceId, std::string{canbus.GetName()}}
    {}

    /**
     * \brief Gets the configurator for this CANdle
     *
     * \details Gets the configurator for this CANdle
     *
     * \returns Configurator for this CANdle
     */
    configs::CANdleConfigurator &GetConfigurator()
    {
        return _configs;
    }

    /**
     * \brief Gets the configurator for this CANdle
     *
     * \details Gets the configurator for this CANdle
     *
     * \returns Configurator for this CANdle
     */
    configs::CANdleConfigurator const &GetConfigurator() const
    {
        return _configs;
    }


private:
    std::unique_ptr<sim::CANdleSimState> _simState{};
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
    sim::CANdleSimState &GetSimState()
    {
        if (_simState == nullptr)
            _simState = std::make_unique<sim::CANdleSimState>(*this);
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
     * \brief Measured supply voltage to the CANdle.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 32.767
     * - Default Value: 0
     * - Units: V
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 10.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns SupplyVoltage Status Signal Object
     */
    StatusSignal<units::voltage::volt_t> &GetSupplyVoltage(bool refresh = true);
        
    /**
     * \brief The measured voltage of the 5V rail line.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 10.23
     * - Default Value: 0
     * - Units: V
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 10.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns FiveVRailVoltage Status Signal Object
     */
    StatusSignal<units::voltage::volt_t> &GetFiveVRailVoltage(bool refresh = true);
        
    /**
     * \brief The measured output current. This includes both VBat and 5V
     * output current.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 10.23
     * - Default Value: 0
     * - Units: A
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 10.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns OutputCurrent Status Signal Object
     */
    StatusSignal<units::current::ampere_t> &GetOutputCurrent(bool refresh = true);
        
    /**
     * \brief The temperature that the CANdle measures itself to be at.
     * 
     * - Minimum Value: -128
     * - Maximum Value: 127
     * - Default Value: 0
     * - Units: ℃
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 10.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DeviceTemp Status Signal Object
     */
    StatusSignal<units::temperature::celsius_t> &GetDeviceTemp(bool refresh = true);
        
    /**
     * \brief The applied VBat modulation duty cycle.
     * 
     * This signal will report 1.0 if the VBatOutputMode is configured to
     * be always on, and 0.0 if configured to be always off. Otherwise,
     * this will report the applied modulation from the last
     * ModulateVBatOut request.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1.0
     * - Default Value: 0
     * - Units: frac
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 10.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns VBatModulation Status Signal Object
     */
    StatusSignal<units::dimensionless::scalar_t> &GetVBatModulation(bool refresh = true);
        
    /**
     * \brief The maximum number of simultaneous animations supported by
     * the current version of CANdle firmware.
     * 
     * Any control request using an animation slot greater than or equal
     * to this signal will be ignored.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 31
     * - Default Value: 0
     * - Units: 
     * 
     * Default Rates:
     * - CAN 2.0: 10.0 Hz
     * - CAN FD: 10.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MaxSimultaneousAnimationCount Status Signal Object
     */
    StatusSignal<int> &GetMaxSimultaneousAnimationCount(bool refresh = true);
        
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
     * \brief Device supply voltage is too high (above 30 V).
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_Overvoltage Status Signal Object
     */
    StatusSignal<bool> &GetFault_Overvoltage(bool refresh = true);
        
    /**
     * \brief Device supply voltage is too high (above 30 V).
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_Overvoltage Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_Overvoltage(bool refresh = true);
        
    /**
     * \brief Device 5V line is too high (above 6 V).
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_5VTooHigh Status Signal Object
     */
    StatusSignal<bool> &GetFault_5VTooHigh(bool refresh = true);
        
    /**
     * \brief Device 5V line is too high (above 6 V).
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_5VTooHigh Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_5VTooHigh(bool refresh = true);
        
    /**
     * \brief Device 5V line is too low (below 4 V).
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_5VTooLow Status Signal Object
     */
    StatusSignal<bool> &GetFault_5VTooLow(bool refresh = true);
        
    /**
     * \brief Device 5V line is too low (below 4 V).
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_5VTooLow Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_5VTooLow(bool refresh = true);
        
    /**
     * \brief Device temperature exceeded limit.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_Thermal Status Signal Object
     */
    StatusSignal<bool> &GetFault_Thermal(bool refresh = true);
        
    /**
     * \brief Device temperature exceeded limit.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_Thermal Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_Thermal(bool refresh = true);
        
    /**
     * \brief CANdle output current exceeded the 6 A limit.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_SoftwareFuse Status Signal Object
     */
    StatusSignal<bool> &GetFault_SoftwareFuse(bool refresh = true);
        
    /**
     * \brief CANdle output current exceeded the 6 A limit.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_SoftwareFuse Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_SoftwareFuse(bool refresh = true);
        
    /**
     * \brief CANdle has detected the output pin is shorted.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_ShortCircuit Status Signal Object
     */
    StatusSignal<bool> &GetFault_ShortCircuit(bool refresh = true);
        
    /**
     * \brief CANdle has detected the output pin is shorted.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_ShortCircuit Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_ShortCircuit(bool refresh = true);

    
    /**
     * \brief Modulates the CANdle VBat output to the specified duty
     * cycle. This can be used to control a single-color LED strip.
     * 
     * Note that configs::CANdleFeaturesConfigs::VBatOutputMode must be
     * set to signals::VBatOutputModeValue::Modulated.
     * 
     * \details 
     * 
     * - ModulateVBatOut Parameters: 
     *   - Output: Proportion of VBat to output in fractional units between 0.0 and
     *          1.0.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::ModulateVBatOut &request);
    
    /**
     * \brief Sets LEDs to a solid color.
     * 
     * \details 
     * 
     * - SolidColor Parameters: 
     *   - LEDStartIndex: The index of the first LED this animation controls
     *                 (inclusive). Indices 0-7 control the onboard LEDs, and 8-399
     *                 control an attached LED strip.
     *   - LEDEndIndex: The index of the last LED this animation controls (inclusive).
     *               Indices 0-7 control the onboard LEDs, and 8-399 control an
     *               attached LED strip.
     *   - Color: The color to apply to the LEDs.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::SolidColor &request);
    
    /**
     * \brief An empty animation, clearing any animation in the specified
     * slot.
     * 
     * \details 
     * 
     * - EmptyAnimation Parameters: 
     *   - Slot: The slot of this animation, within [0, 7]. Each slot on the CANdle can
     *        store and run one animation.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::EmptyAnimation &request);
    
    /**
     * \brief Animation that gradually lights the entire LED strip one LED
     * at a time.
     * 
     * \details 
     * 
     * - ColorFlowAnimation Parameters: 
     *   - LEDStartIndex: The index of the first LED this animation controls
     *                 (inclusive). Indices 0-7 control the onboard LEDs, and 8-399
     *                 control an attached LED strip
     *                 
     *                 If the start index is greater than the end index, the
     *                 direction will be reversed. The direction can also be changed
     *                 using the Direction parameter.
     *   - LEDEndIndex: The index of the last LED this animation controls (inclusive).
     *               Indices 0-7 control the onboard LEDs, and 8-399 control an
     *               attached LED strip.
     *               
     *               If the end index is less than the start index, the direction
     *               will be reversed. The direction can also be changed using the
     *               Direction parameter.
     *   - Slot: The slot of this animation, within [0, 7]. Each slot on the CANdle can
     *        store and run one animation.
     *   - Color: The color to use in the animation.
     *   - Direction: The direction of the animation.
     *   - FrameRate: The frame rate of the animation, from [2, 1000] Hz. This
     *             determines the speed of the animation.
     *             
     *             A frame is defined as a transition in the state of the LEDs,
     *             turning one on or off.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::ColorFlowAnimation &request);
    
    /**
     * \brief Animation that looks similar to a flame flickering.
     * 
     * \details 
     * 
     * - FireAnimation Parameters: 
     *   - LEDStartIndex: The index of the first LED this animation controls
     *                 (inclusive). Indices 0-7 control the onboard LEDs, and 8-399
     *                 control an attached LED strip
     *                 
     *                 If the start index is greater than the end index, the
     *                 direction will be reversed. The direction can also be changed
     *                 using the Direction parameter.
     *   - LEDEndIndex: The index of the last LED this animation controls (inclusive).
     *               Indices 0-7 control the onboard LEDs, and 8-399 control an
     *               attached LED strip.
     *               
     *               If the end index is less than the start index, the direction
     *               will be reversed. The direction can also be changed using the
     *               Direction parameter.
     *   - Slot: The slot of this animation, within [0, 7]. Each slot on the CANdle can
     *        store and run one animation.
     *   - Brightness: The brightness of the animation, as a scalar from 0.0 to 1.0.
     *   - Direction: The direction of the animation.
     *   - Sparking: The proportion of time in which sparks reignite the fire, as a
     *            scalar from 0.0 to 1.0.
     *   - Cooling: The rate at which the fire cools along the travel, as a scalar from
     *           0.0 to 1.0.
     *   - FrameRate: The frame rate of the animation, from [2, 1000] Hz. This
     *             determines the speed of the animation.
     *             
     *             A frame is defined as a transition in the state of the LEDs,
     *             advancing the animation of the fire.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::FireAnimation &request);
    
    /**
     * \brief Animation that bounces a pocket of light across the LED
     * strip.
     * 
     * \details 
     * 
     * - LarsonAnimation Parameters: 
     *   - LEDStartIndex: The index of the first LED this animation controls
     *                 (inclusive). Indices 0-7 control the onboard LEDs, and 8-399
     *                 control an attached LED strip.
     *   - LEDEndIndex: The index of the last LED this animation controls (inclusive).
     *               Indices 0-7 control the onboard LEDs, and 8-399 control an
     *               attached LED strip.
     *   - Slot: The slot of this animation, within [0, 7]. Each slot on the CANdle can
     *        store and run one animation.
     *   - Color: The color to use in the animation.
     *   - Size: The number of LEDs in the pocket of light, up to 15.
     *   - BounceMode: The behavior of the pocket of light when it reaches the end of
     *              the strip.
     *   - FrameRate: The frame rate of the animation, from [2, 1000] Hz. This
     *             determines the speed of the animation.
     *             
     *             A frame is defined as a transition in the state of the LEDs,
     *             advancing the pocket of light by one LED.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::LarsonAnimation &request);
    
    /**
     * \brief Animation that creates a rainbow throughout all the LEDs.
     * 
     * \details 
     * 
     * - RainbowAnimation Parameters: 
     *   - LEDStartIndex: The index of the first LED this animation controls
     *                 (inclusive). Indices 0-7 control the onboard LEDs, and 8-399
     *                 control an attached LED strip
     *                 
     *                 If the start index is greater than the end index, the
     *                 direction will be reversed. The direction can also be changed
     *                 using the Direction parameter.
     *   - LEDEndIndex: The index of the last LED this animation controls (inclusive).
     *               Indices 0-7 control the onboard LEDs, and 8-399 control an
     *               attached LED strip.
     *               
     *               If the end index is less than the start index, the direction
     *               will be reversed. The direction can also be changed using the
     *               Direction parameter.
     *   - Slot: The slot of this animation, within [0, 7]. Each slot on the CANdle can
     *        store and run one animation.
     *   - Brightness: The brightness of the animation, as a scalar from 0.0 to 1.0.
     *   - Direction: The direction of the animation.
     *   - FrameRate: The frame rate of the animation, from [2, 1000] Hz. This
     *             determines the speed of the animation.
     *             
     *             A frame is defined as a transition in the state of the LEDs,
     *             advancing the rainbow by about 3 degrees of hue (out of 360
     *             degrees).
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::RainbowAnimation &request);
    
    /**
     * \brief Animation that fades all the LEDs of a strip simultaneously
     * between Red, Green, and Blue.
     * 
     * \details 
     * 
     * - RgbFadeAnimation Parameters: 
     *   - LEDStartIndex: The index of the first LED this animation controls
     *                 (inclusive). Indices 0-7 control the onboard LEDs, and 8-399
     *                 control an attached LED strip.
     *   - LEDEndIndex: The index of the last LED this animation controls (inclusive).
     *               Indices 0-7 control the onboard LEDs, and 8-399 control an
     *               attached LED strip.
     *   - Slot: The slot of this animation, within [0, 7]. Each slot on the CANdle can
     *        store and run one animation.
     *   - Brightness: The brightness of the animation, as a scalar from 0.0 to 1.0.
     *   - FrameRate: The frame rate of the animation, from [2, 1000] Hz. This
     *             determines the speed of the animation.
     *             
     *             A frame is defined as a transition in the state of the LEDs,
     *             adjusting the brightness of the LEDs by 1%.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::RgbFadeAnimation &request);
    
    /**
     * \brief Animation that fades into and out of a specified color.
     * 
     * \details 
     * 
     * - SingleFadeAnimation Parameters: 
     *   - LEDStartIndex: The index of the first LED this animation controls
     *                 (inclusive). Indices 0-7 control the onboard LEDs, and 8-399
     *                 control an attached LED strip.
     *   - LEDEndIndex: The index of the last LED this animation controls (inclusive).
     *               Indices 0-7 control the onboard LEDs, and 8-399 control an
     *               attached LED strip.
     *   - Slot: The slot of this animation, within [0, 7]. Each slot on the CANdle can
     *        store and run one animation.
     *   - Color: The color to use in the animation.
     *   - FrameRate: The frame rate of the animation, from [2, 1000] Hz. This
     *             determines the speed of the animation.
     *             
     *             A frame is defined as a transition in the state of the LEDs,
     *             adjusting the brightness of the LEDs by 1%.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::SingleFadeAnimation &request);
    
    /**
     * \brief Animation that strobes the LEDs a specified color.
     * 
     * \details 
     * 
     * - StrobeAnimation Parameters: 
     *   - LEDStartIndex: The index of the first LED this animation controls
     *                 (inclusive). Indices 0-7 control the onboard LEDs, and 8-399
     *                 control an attached LED strip.
     *   - LEDEndIndex: The index of the last LED this animation controls (inclusive).
     *               Indices 0-7 control the onboard LEDs, and 8-399 control an
     *               attached LED strip.
     *   - Slot: The slot of this animation, within [0, 7]. Each slot on the CANdle can
     *        store and run one animation.
     *   - Color: The color to use in the animation.
     *   - FrameRate: The frame rate of the animation, from [1, 500] Hz. This
     *             determines the speed of the animation.
     *             
     *             A frame is defined as a transition in the state of the LEDs,
     *             turning all LEDs on or off.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::StrobeAnimation &request);
    
    /**
     * \brief Animation that randomly turns LEDs on and off to a certain
     * color.
     * 
     * \details 
     * 
     * - TwinkleAnimation Parameters: 
     *   - LEDStartIndex: The index of the first LED this animation controls
     *                 (inclusive). Indices 0-7 control the onboard LEDs, and 8-399
     *                 control an attached LED strip.
     *   - LEDEndIndex: The index of the last LED this animation controls (inclusive).
     *               Indices 0-7 control the onboard LEDs, and 8-399 control an
     *               attached LED strip.
     *   - Slot: The slot of this animation, within [0, 7]. Each slot on the CANdle can
     *        store and run one animation.
     *   - Color: The color to use in the animation.
     *   - MaxLEDsOnProportion: The max proportion of LEDs that can be on, in the range
     *                       [0.1, 1.0].
     *   - FrameRate: The frame rate of the animation, from [2, 1000] Hz. This
     *             determines the speed of the animation.
     *             
     *             A frame is defined as a transition in the state of the LEDs,
     *             turning one on or off.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::TwinkleAnimation &request);
    
    /**
     * \brief Animation that randomly turns on LEDs until it reaches the
     * maximum count, and then turns them all off.
     * 
     * \details 
     * 
     * - TwinkleOffAnimation Parameters: 
     *   - LEDStartIndex: The index of the first LED this animation controls
     *                 (inclusive). Indices 0-7 control the onboard LEDs, and 8-399
     *                 control an attached LED strip.
     *   - LEDEndIndex: The index of the last LED this animation controls (inclusive).
     *               Indices 0-7 control the onboard LEDs, and 8-399 control an
     *               attached LED strip.
     *   - Slot: The slot of this animation, within [0, 7]. Each slot on the CANdle can
     *        store and run one animation.
     *   - Color: The color to use in the animation.
     *   - MaxLEDsOnProportion: The max proportion of LEDs that can be on, in the range
     *                       [0.1, 1.0].
     *   - FrameRate: The frame rate of the animation, from [2, 1000] Hz. This
     *             determines the speed of the animation.
     *             
     *             A frame is defined as a transition in the state of the LEDs,
     *             turning one LED on or all LEDs off.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    ctre::phoenix::StatusCode SetControl(const controls::TwinkleOffAnimation &request);

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
        auto const *ModulateVBatOutValue = dynamic_cast<controls::ModulateVBatOut const *>(ptr);
        if (ModulateVBatOutValue != nullptr)
            return SetControl(*ModulateVBatOutValue);
        auto const *SolidColorValue = dynamic_cast<controls::SolidColor const *>(ptr);
        if (SolidColorValue != nullptr)
            return SetControl(*SolidColorValue);
        auto const *EmptyAnimationValue = dynamic_cast<controls::EmptyAnimation const *>(ptr);
        if (EmptyAnimationValue != nullptr)
            return SetControl(*EmptyAnimationValue);
        auto const *ColorFlowAnimationValue = dynamic_cast<controls::ColorFlowAnimation const *>(ptr);
        if (ColorFlowAnimationValue != nullptr)
            return SetControl(*ColorFlowAnimationValue);
        auto const *FireAnimationValue = dynamic_cast<controls::FireAnimation const *>(ptr);
        if (FireAnimationValue != nullptr)
            return SetControl(*FireAnimationValue);
        auto const *LarsonAnimationValue = dynamic_cast<controls::LarsonAnimation const *>(ptr);
        if (LarsonAnimationValue != nullptr)
            return SetControl(*LarsonAnimationValue);
        auto const *RainbowAnimationValue = dynamic_cast<controls::RainbowAnimation const *>(ptr);
        if (RainbowAnimationValue != nullptr)
            return SetControl(*RainbowAnimationValue);
        auto const *RgbFadeAnimationValue = dynamic_cast<controls::RgbFadeAnimation const *>(ptr);
        if (RgbFadeAnimationValue != nullptr)
            return SetControl(*RgbFadeAnimationValue);
        auto const *SingleFadeAnimationValue = dynamic_cast<controls::SingleFadeAnimation const *>(ptr);
        if (SingleFadeAnimationValue != nullptr)
            return SetControl(*SingleFadeAnimationValue);
        auto const *StrobeAnimationValue = dynamic_cast<controls::StrobeAnimation const *>(ptr);
        if (StrobeAnimationValue != nullptr)
            return SetControl(*StrobeAnimationValue);
        auto const *TwinkleAnimationValue = dynamic_cast<controls::TwinkleAnimation const *>(ptr);
        if (TwinkleAnimationValue != nullptr)
            return SetControl(*TwinkleAnimationValue);
        auto const *TwinkleOffAnimationValue = dynamic_cast<controls::TwinkleOffAnimation const *>(ptr);
        if (TwinkleOffAnimationValue != nullptr)
            return SetControl(*TwinkleOffAnimationValue);
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
    
    /**
     * \brief Clear sticky fault: Device supply voltage is too high (above
     * 30 V).
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Overvoltage(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_Overvoltage(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device supply voltage is too high (above
     * 30 V).
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Overvoltage()
    {
        return ClearStickyFault_Overvoltage(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Device 5V line is too high (above 6 V).
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_5VTooHigh(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_5VTooHigh(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device 5V line is too high (above 6 V).
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_5VTooHigh()
    {
        return ClearStickyFault_5VTooHigh(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Device 5V line is too low (below 4 V).
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_5VTooLow(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_5VTooLow(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device 5V line is too low (below 4 V).
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_5VTooLow()
    {
        return ClearStickyFault_5VTooLow(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: Device temperature exceeded limit.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Thermal(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_Thermal(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: Device temperature exceeded limit.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_Thermal()
    {
        return ClearStickyFault_Thermal(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: CANdle output current exceeded the 6 A
     * limit.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SoftwareFuse(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_SoftwareFuse(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: CANdle output current exceeded the 6 A
     * limit.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_SoftwareFuse()
    {
        return ClearStickyFault_SoftwareFuse(0.100_s);
    }
    
    /**
     * \brief Clear sticky fault: CANdle has detected the output pin is
     * shorted.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ShortCircuit(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_ShortCircuit(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: CANdle has detected the output pin is
     * shorted.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_ShortCircuit()
    {
        return ClearStickyFault_ShortCircuit(0.100_s);
    }
};

}
}

}
}

