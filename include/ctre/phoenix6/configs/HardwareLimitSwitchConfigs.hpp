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

namespace ctre {
namespace phoenix6 {
namespace hardware::core { class CoreCANcoder; }
namespace hardware::core { class CoreCANdi; }
namespace hardware::core { class CoreCANrange; }
namespace hardware::traits { class CommonTalon; }

namespace configs {

/**
 * \brief Configs that change how the motor controller behaves under
 *        different limit switch states.
 * 
 * \details Includes configs such as enabling limit switches,
 *          configuring the remote sensor ID, the source, and the
 *          position to set on limit.
 */
class HardwareLimitSwitchConfigs : public ParentConfiguration {
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
     *        RemoteTalonFX forward limit switch by passing in the
     *        CommonTalon object. When using RemoteTalonFX, the Talon FX
     *        will use the forward limit switch attached to another Talon
     *        FX on the same CAN bus.
     * 
     * \param device CommonTalon reference to use for RemoteTalonFX forward limit
     *               switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithForwardLimitRemoteTalonFX(const hardware::traits::CommonTalon& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANcoder forward limit switch by passing in the
     *        CANcoder object. When using RemoteCANcoder, the Talon FX
     *        will use another CANcoder on the same CAN bus. The forward
     *        limit will assert when the CANcoder magnet strength changes
     *        from BAD (red) to ADEQUATE (orange) or GOOD (green).
     * 
     * \param device CANcoder reference to use for RemoteCANcoder forward limit
     *               switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithForwardLimitRemoteCANcoder(const hardware::core::CoreCANcoder& device);
    
    /**
     * \brief Helper method to configure this feedback group to use the
     *        RemoteCANrange by passing in the CANrange object. The
     *        forward limit will assert when the CANrange proximity detect
     *        is tripped.
     * 
     * \param device CANrange reference to use for RemoteCANrange forward limit
     *               switch
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
     *        RemoteTalonFX reverse limit switch by passing in the
     *        CommonTalon object. When using RemoteTalonFX, the Talon FX
     *        will use the reverse limit switch attached to another Talon
     *        FX on the same CAN bus.
     * 
     * \param device CommonTalon reference to use for RemoteTalonFX reverse limit
     *               switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithReverseLimitRemoteTalonFX(const hardware::traits::CommonTalon& device);
    
    /**
     * \brief Helper method to configure this feedback group to use
     *        RemoteCANcoder reverse limit switch by passing in the
     *        CANcoder object. When using RemoteCANcoder, the Talon FX
     *        will use another CANcoder on the same CAN bus. The reverse
     *        limit will assert when the CANcoder magnet strength changes
     *        from BAD (red) to ADEQUATE (orange) or GOOD (green).
     * 
     * \param device CANcoder reference to use for RemoteCANcoder reverse limit
     *               switch
     * \returns Itself
     */
    HardwareLimitSwitchConfigs &WithReverseLimitRemoteCANcoder(const hardware::core::CoreCANcoder& device);
    
    /**
     * \brief Helper method to configure this feedback group to use the
     *        RemoteCANrange by passing in the CANrange object. The
     *        reverse limit will assert when the CANrange proximity detect
     *        is tripped.
     * 
     * \param device CANrange reference to use for RemoteCANrange reverse limit
     *               switch
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
    
    

    std::string ToString() const override;

    std::string Serialize() const final;
    ctre::phoenix::StatusCode Deserialize(std::string const &to_deserialize) final;
};

}
}
}
