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


#include "ctre/phoenix6/sim/CANdiSimState.hpp"
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/current.h>
#include <units/time.h>
#include <units/voltage.h>

namespace ctre {
namespace phoenix6 {

namespace hardware {
namespace core {
    class CoreCANdi;
}
}

namespace configs {

/**
 * Class for CTR Electronics' CANdi™ branded device, a device that integrates
 * digital signals into the existing CAN bus network.
 *
 * This handles the configurations for the hardware#CANdi
 */
class CANdiConfiguration : public ParentConfiguration
{
public:
    constexpr CANdiConfiguration() = default;

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
     * \brief Configs related to the CANdi™ branded device's digital I/O
     *        settings
     * 
     * \details Contains float-state settings and when to assert the S1/S2
     *          inputs.
     * 
     * Parameter list:
     * 
     * - DigitalInputsConfigs#S1FloatState
     * - DigitalInputsConfigs#S2FloatState
     * - DigitalInputsConfigs#S1CloseState
     * - DigitalInputsConfigs#S2CloseState
     * 
     */
    DigitalInputsConfigs DigitalInputs;
    
    /**
     * \brief Configs related to the CANdi™ branded device's quadrature
     *        interface using both the S1IN and S2IN inputs
     * 
     * \details All the configs related to the quadrature interface for
     *          the CANdi™ branded device , including encoder edges per
     *          revolution and sensor direction.
     * 
     * Parameter list:
     * 
     * - QuadratureConfigs#QuadratureEdgesPerRotation
     * - QuadratureConfigs#SensorDirection
     * 
     */
    QuadratureConfigs Quadrature;
    
    /**
     * \brief Configs related to the CANdi™ branded device's PWM interface
     *        on the Signal 1 input (S1IN)
     * 
     * \details All the configs related to the PWM interface for the
     *          CANdi™ branded device on S1, including absolute sensor
     *          offset, absolute sensor discontinuity point and sensor
     *          direction.
     * 
     * Parameter list:
     * 
     * - PWM1Configs#AbsoluteSensorOffset
     * - PWM1Configs#AbsoluteSensorDiscontinuityPoint
     * - PWM1Configs#SensorDirection
     * 
     */
    PWM1Configs PWM1;
    
    /**
     * \brief Configs related to the CANdi™ branded device's PWM interface
     *        on the Signal 2 input (S2IN)
     * 
     * \details All the configs related to the PWM interface for the
     *          CANdi™ branded device on S1, including absolute sensor
     *          offset, absolute sensor discontinuity point and sensor
     *          direction.
     * 
     * Parameter list:
     * 
     * - PWM2Configs#AbsoluteSensorOffset
     * - PWM2Configs#AbsoluteSensorDiscontinuityPoint
     * - PWM2Configs#SensorDirection
     * 
     */
    PWM2Configs PWM2;
    
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
    constexpr CANdiConfiguration &WithCustomParams(CustomParamsConfigs newCustomParams)
    {
        CustomParams = std::move(newCustomParams);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's DigitalInputs parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs related to the CANdi™ branded device's digital I/O settings
     * 
     * \details Contains float-state settings and when to assert the S1/S2
     *          inputs.
     * 
     * Parameter list:
     * 
     * - DigitalInputsConfigs#S1FloatState
     * - DigitalInputsConfigs#S2FloatState
     * - DigitalInputsConfigs#S1CloseState
     * - DigitalInputsConfigs#S2CloseState
     * 
     *
     * \param newDigitalInputs Parameter to modify
     * \returns Itself
     */
    constexpr CANdiConfiguration &WithDigitalInputs(DigitalInputsConfigs newDigitalInputs)
    {
        DigitalInputs = std::move(newDigitalInputs);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's Quadrature parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs related to the CANdi™ branded device's quadrature interface
     * using both the S1IN and S2IN inputs
     * 
     * \details All the configs related to the quadrature interface for
     *          the CANdi™ branded device , including encoder edges per
     *          revolution and sensor direction.
     * 
     * Parameter list:
     * 
     * - QuadratureConfigs#QuadratureEdgesPerRotation
     * - QuadratureConfigs#SensorDirection
     * 
     *
     * \param newQuadrature Parameter to modify
     * \returns Itself
     */
    constexpr CANdiConfiguration &WithQuadrature(QuadratureConfigs newQuadrature)
    {
        Quadrature = std::move(newQuadrature);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PWM1 parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs related to the CANdi™ branded device's PWM interface on the
     * Signal 1 input (S1IN)
     * 
     * \details All the configs related to the PWM interface for the
     *          CANdi™ branded device on S1, including absolute sensor
     *          offset, absolute sensor discontinuity point and sensor
     *          direction.
     * 
     * Parameter list:
     * 
     * - PWM1Configs#AbsoluteSensorOffset
     * - PWM1Configs#AbsoluteSensorDiscontinuityPoint
     * - PWM1Configs#SensorDirection
     * 
     *
     * \param newPWM1 Parameter to modify
     * \returns Itself
     */
    constexpr CANdiConfiguration &WithPWM1(PWM1Configs newPWM1)
    {
        PWM1 = std::move(newPWM1);
        return *this;
    }
    
    /**
     * \brief Modifies this configuration's PWM2 parameter and returns itself for
     *        method-chaining and easier to use config API.
     *
     * Configs related to the CANdi™ branded device's PWM interface on the
     * Signal 2 input (S2IN)
     * 
     * \details All the configs related to the PWM interface for the
     *          CANdi™ branded device on S1, including absolute sensor
     *          offset, absolute sensor discontinuity point and sensor
     *          direction.
     * 
     * Parameter list:
     * 
     * - PWM2Configs#AbsoluteSensorOffset
     * - PWM2Configs#AbsoluteSensorDiscontinuityPoint
     * - PWM2Configs#SensorDirection
     * 
     *
     * \param newPWM2 Parameter to modify
     * \returns Itself
     */
    constexpr CANdiConfiguration &WithPWM2(PWM2Configs newPWM2)
    {
        PWM2 = std::move(newPWM2);
        return *this;
    }

    /**
     * \brief Get the string representation of this configuration
     */
    std::string ToString() const
    {
        std::stringstream ss;
        ss << "CANdiConfiguration" << std::endl;
        ss << CustomParams.ToString();
        ss << DigitalInputs.ToString();
        ss << Quadrature.ToString();
        ss << PWM1.ToString();
        ss << PWM2.ToString();
        return ss.str();
    }

    /**
     * \brief Get the serialized form of this configuration
     */
    std::string Serialize() const
    {
        std::stringstream ss;
        ss << CustomParams.Serialize();
        ss << DigitalInputs.Serialize();
        ss << Quadrature.Serialize();
        ss << PWM1.Serialize();
        ss << PWM2.Serialize();
        return ss.str();
    }

    /**
     * \brief Take a string and deserialize it to this configuration
     */
    ctre::phoenix::StatusCode Deserialize(const std::string &to_deserialize)
    {
        ctre::phoenix::StatusCode err = ctre::phoenix::StatusCode::OK;
        err = CustomParams.Deserialize(to_deserialize);
        err = DigitalInputs.Deserialize(to_deserialize);
        err = Quadrature.Deserialize(to_deserialize);
        err = PWM1.Deserialize(to_deserialize);
        err = PWM2.Deserialize(to_deserialize);
        return err;
    }
};

/**
 * Class for CTR Electronics' CANdi™ branded device, a device that integrates
 * digital signals into the existing CAN bus network.
 *
 * This handles the configurations for the hardware#CANdi
 */
class CANdiConfigurator : public ParentConfigurator
{
private:
    CANdiConfigurator(hardware::DeviceIdentifier id) :
        ParentConfigurator{std::move(id)}
    {}

    friend hardware::core::CoreCANdi;

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
    ctre::phoenix::StatusCode Refresh(CANdiConfiguration &configs) const
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
    ctre::phoenix::StatusCode Refresh(CANdiConfiguration &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const CANdiConfiguration &configs)
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
    ctre::phoenix::StatusCode Apply(const CANdiConfiguration &configs, units::time::second_t timeoutSeconds)
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
    ctre::phoenix::StatusCode Refresh(DigitalInputsConfigs &configs) const
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
    ctre::phoenix::StatusCode Refresh(DigitalInputsConfigs &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const DigitalInputsConfigs &configs)
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
    ctre::phoenix::StatusCode Apply(const DigitalInputsConfigs &configs, units::time::second_t timeoutSeconds)
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
    ctre::phoenix::StatusCode Refresh(QuadratureConfigs &configs) const
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
    ctre::phoenix::StatusCode Refresh(QuadratureConfigs &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const QuadratureConfigs &configs)
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
    ctre::phoenix::StatusCode Apply(const QuadratureConfigs &configs, units::time::second_t timeoutSeconds)
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
    ctre::phoenix::StatusCode Refresh(PWM1Configs &configs) const
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
    ctre::phoenix::StatusCode Refresh(PWM1Configs &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const PWM1Configs &configs)
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
    ctre::phoenix::StatusCode Apply(const PWM1Configs &configs, units::time::second_t timeoutSeconds)
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
    ctre::phoenix::StatusCode Refresh(PWM2Configs &configs) const
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
    ctre::phoenix::StatusCode Refresh(PWM2Configs &configs, units::time::second_t timeoutSeconds) const
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
    ctre::phoenix::StatusCode Apply(const PWM2Configs &configs)
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
    ctre::phoenix::StatusCode Apply(const PWM2Configs &configs, units::time::second_t timeoutSeconds)
    {
        return SetConfigsPrivate(configs.Serialize(), timeoutSeconds, false, false);
    }

    
    /**
     * \brief Sets the position of the quadrature input.
     * 
     * This will wait up to #DefaultTimeoutSeconds.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param newValue Value to set to. Units are in rotations.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetQuadraturePosition(units::angle::turn_t newValue)
    {
        return SetQuadraturePosition(newValue, DefaultTimeoutSeconds);
    }
    /**
     * \brief Sets the position of the quadrature input.
     * 
     * This is available in the configurator in case the user wants
     * to initialize their device entirely without passing a device
     * reference down to the code that performs the initialization.
     * In this case, the user passes down the configurator object
     * and performs all the initialization code on the object.
     * 
     * \param newValue Value to set to. Units are in rotations.
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetQuadraturePosition(units::angle::turn_t newValue, units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::CANdi_SetQuadPosition, newValue.to<double>(), &ref); if (ref != nullptr) { ss << ref; free(ref); }
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
     * \brief Clear sticky fault: The CTR Electronics' CANdi™ branded
     * device has detected a 5V fault. This may be due to overcurrent or a
     * short-circuit.
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
    ctre::phoenix::StatusCode ClearStickyFault_5V()
    {
        return ClearStickyFault_5V(DefaultTimeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The CTR Electronics' CANdi™ branded
     * device has detected a 5V fault. This may be due to overcurrent or a
     * short-circuit.
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
    ctre::phoenix::StatusCode ClearStickyFault_5V(units::time::second_t timeoutSeconds)
    {
        std::stringstream ss;
        char *ref;
        c_ctre_phoenix6_serialize_double(ctre::phoenix6::spns::SpnValue::ClearStickyFault_CANDI_5V, 0, &ref); if (ref != nullptr) { ss << ref; free(ref); }
        return SetConfigsPrivate(ss.str(), timeoutSeconds, false, true);
    }
};

}

namespace hardware {
namespace core {

/**
 * Class for CTR Electronics' CANdi™ branded device, a device that integrates
 * digital signals into the existing CAN bus network.
 */
class CoreCANdi : public ParentDevice
{
private:
    configs::CANdiConfigurator _configs;

public:
    using Configuration = configs::CANdiConfiguration;

    /**
     * Constructs a new CANdi object.
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
    CoreCANdi(int deviceId, std::string canbus = "");

    /**
     * Constructs a new CANdi object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner.
     * \param canbus      The CAN bus this device is on.
     */
    CoreCANdi(int deviceId, CANBus canbus) :
        CoreCANdi{deviceId, std::string{canbus.GetName()}}
    {}

    /**
     * \brief Gets the configurator for this CANdi
     *
     * \details Gets the configurator for this CANdi
     *
     * \returns Configurator for this CANdi
     */
    configs::CANdiConfigurator &GetConfigurator()
    {
        return _configs;
    }

    /**
     * \brief Gets the configurator for this CANdi
     *
     * \details Gets the configurator for this CANdi
     *
     * \returns Configurator for this CANdi
     */
    configs::CANdiConfigurator const &GetConfigurator() const
    {
        return _configs;
    }


private:
    std::unique_ptr<sim::CANdiSimState> _simState{};
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
    sim::CANdiSimState &GetSimState()
    {
        if (_simState == nullptr)
            _simState = std::make_unique<sim::CANdiSimState>(*this);
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
     * \brief State of the Signal 1 input (S1IN).
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns S1State Status Signal Object
     */
    StatusSignal<signals::S1StateValue> &GetS1State(bool refresh = true);
        
    /**
     * \brief State of the Signal 2 input (S2IN).
     * 
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns S2State Status Signal Object
     */
    StatusSignal<signals::S2StateValue> &GetS2State(bool refresh = true);
        
    /**
     * \brief Position from a quadrature encoder sensor connected to both
     * the S1IN and S2IN inputs.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * Default Rates:
     * - CAN 2.0: 20.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns QuadraturePosition Status Signal Object
     */
    StatusSignal<units::angle::turn_t> &GetQuadraturePosition(bool refresh = true);
        
    /**
     * \brief Measured rise to rise time of the PWM signal at the S1 input
     * of the CTR Electronics' CANdi™.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 131070
     * - Default Value: 0
     * - Units: us
     * 
     * Default Rates:
     * - CAN 2.0: 20.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns PWM1RiseToRise Status Signal Object
     */
    StatusSignal<units::time::microsecond_t> &GetPWM1RiseToRise(bool refresh = true);
        
    /**
     * \brief Measured position of the PWM sensor at the S1 input of the
     * CTR Electronics' CANdi™.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * Default Rates:
     * - CAN 2.0: 20.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns PWM1Position Status Signal Object
     */
    StatusSignal<units::angle::turn_t> &GetPWM1Position(bool refresh = true);
        
    /**
     * \brief Measured velocity of the PWM sensor at the S1 input of the
     * CTR Electronics' CANdi™.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * Default Rates:
     * - CAN 2.0: 20.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns PWM1Velocity Status Signal Object
     */
    StatusSignal<units::angular_velocity::turns_per_second_t> &GetPWM1Velocity(bool refresh = true);
        
    /**
     * \brief Measured rise to rise time of the PWM signal at the S2 input
     * of the CTR Electronics' CANdi™.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 131070
     * - Default Value: 0
     * - Units: us
     * 
     * Default Rates:
     * - CAN 2.0: 20.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns PWM2RiseToRise Status Signal Object
     */
    StatusSignal<units::time::microsecond_t> &GetPWM2RiseToRise(bool refresh = true);
        
    /**
     * \brief Measured position of the PWM sensor at the S2 input of the
     * CTR Electronics' CANdi™.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * Default Rates:
     * - CAN 2.0: 20.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns PWM2Position Status Signal Object
     */
    StatusSignal<units::angle::turn_t> &GetPWM2Position(bool refresh = true);
        
    /**
     * \brief True when the CANdi™ is in overcurrent protection mode. This
     * may be due to either overcurrent or a short-circuit.
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
     * \returns Overcurrent Status Signal Object
     */
    StatusSignal<bool> &GetOvercurrent(bool refresh = true);
        
    /**
     * \brief Measured supply voltage to the CANdi™.
     * 
     * - Minimum Value: 4.0
     * - Maximum Value: 29.5
     * - Default Value: 0
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
     * \brief Measured output current. This includes both Vbat and 5V
     * output current.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 0.51
     * - Default Value: 0
     * - Units: A
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns OutputCurrent Status Signal Object
     */
    StatusSignal<units::current::ampere_t> &GetOutputCurrent(bool refresh = true);
        
    /**
     * \brief Measured velocity of the PWM sensor at the S2 input of the
     * CTR Electronics' CANdi™.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * Default Rates:
     * - CAN 2.0: 20.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns PWM2Velocity Status Signal Object
     */
    StatusSignal<units::angular_velocity::turns_per_second_t> &GetPWM2Velocity(bool refresh = true);
        
    /**
     * \brief Velocity from a quadrature encoder sensor connected to both
     * the S1IN and S2IN inputs.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * Default Rates:
     * - CAN 2.0: 20.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns QuadratureVelocity Status Signal Object
     */
    StatusSignal<units::angular_velocity::turns_per_second_t> &GetQuadratureVelocity(bool refresh = true);
        
    /**
     * \brief True if the Signal 1 input (S1IN) matches the configured S1
     * Closed State.
     * 
     * \details Configure the S1 closed state in the Digitals
     * configuration object to change when this is asserted.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns S1Closed Status Signal Object
     */
    StatusSignal<bool> &GetS1Closed(bool refresh = true);
        
    /**
     * \brief True if the Signal 2 input (S2IN) matches the configured S2
     * Closed State.
     * 
     * \details Configure the S2 closed state in the Digitals
     * configuration object to change when this is asserted.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN 2.0: 100.0 Hz
     * - CAN FD: 100.0 Hz (TimeSynced with Pro)
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns S2Closed Status Signal Object
     */
    StatusSignal<bool> &GetS2Closed(bool refresh = true);
        
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
     * \brief The CTR Electronics' CANdi™ branded device has detected a 5V
     * fault. This may be due to overcurrent or a short-circuit.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_5V Status Signal Object
     */
    StatusSignal<bool> &GetFault_5V(bool refresh = true);
        
    /**
     * \brief The CTR Electronics' CANdi™ branded device has detected a 5V
     * fault. This may be due to overcurrent or a short-circuit.
     * 
     * - Default Value: False
     * 
     * Default Rates:
     * - CAN: 4.0 Hz
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_5V Status Signal Object
     */
    StatusSignal<bool> &GetStickyFault_5V(bool refresh = true);

    

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
     * \brief Sets the position of the quadrature input.
     * 
     * \param newValue Value to set to. Units are in rotations.
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetQuadraturePosition(units::angle::turn_t newValue, units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().SetQuadraturePosition(newValue, timeoutSeconds);
    }
    /**
     * \brief Sets the position of the quadrature input.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \param newValue Value to set to. Units are in rotations.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode SetQuadraturePosition(units::angle::turn_t newValue)
    {
        return SetQuadraturePosition(newValue, 0.100_s);
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
     * \brief Clear sticky fault: The CTR Electronics' CANdi™ branded
     * device has detected a 5V fault. This may be due to overcurrent or a
     * short-circuit.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_5V(units::time::second_t timeoutSeconds)
    {
        return GetConfigurator().ClearStickyFault_5V(timeoutSeconds);
    }
    /**
     * \brief Clear sticky fault: The CTR Electronics' CANdi™ branded
     * device has detected a 5V fault. This may be due to overcurrent or a
     * short-circuit.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    ctre::phoenix::StatusCode ClearStickyFault_5V()
    {
        return ClearStickyFault_5V(0.100_s);
    }
};

}
}

}
}

