/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/controls/ControlRequest.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include "ctre/phoenix6/StatusSignal.hpp"

#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/temperature.h>
#include <units/voltage.h>

namespace ctre {
namespace phoenix6 {
namespace hardware {
namespace traits {

/**
 * Contains all status signals for motor controllers that support external
 * motors.
 */
class HasExternalMotor
{
public:
    virtual ~HasExternalMotor() = default;
        
    /**
     * \brief Status of the temperature sensor of the external motor.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ExternalMotorTempStatus Status Signal Object
     */
    virtual StatusSignal<signals::ExternalMotorTempStatusValue> &GetExternalMotorTempStatus(bool refresh = true) = 0;
        
    /**
     * \brief Temperature of the external motor.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 255.0
     * - Default Value: 0
     * - Units: ℃
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ExternalMotorTemp Status Signal Object
     */
    virtual StatusSignal<units::temperature::celsius_t> &GetExternalMotorTemp(bool refresh = true) = 0;
        
    /**
     * \brief The measured voltage of the 5V rail available on the JST and
     * dataport connectors.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 40.95
     * - Default Value: 0
     * - Units: Volts
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns FiveVRailVoltage Status Signal Object
     */
    virtual StatusSignal<units::voltage::volt_t> &GetFiveVRailVoltage(bool refresh = true) = 0;
        
    /**
     * \brief The voltage of the analog pin (pin 3) of the Talon FXS data
     * port. The analog pin reads a nominal voltage of 0-5V.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 6
     * - Default Value: 0
     * - Units: Volts
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AnalogVoltage Status Signal Object
     */
    virtual StatusSignal<units::voltage::volt_t> &GetAnalogVoltage(bool refresh = true) = 0;
        
    /**
     * \brief The raw position retrieved from the connected quadrature
     * encoder. This is only affected by the QuadratureEdgesPerRotation
     * config. In most situations, the user should instead configure the
     * ExternalFeedbackSensorSource and use the regular position getter.
     * 
     * This signal must have its update frequency configured before it
     * will have data.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns RawQuadraturePosition Status Signal Object
     */
    virtual StatusSignal<units::angle::turn_t> &GetRawQuadraturePosition(bool refresh = true) = 0;
        
    /**
     * \brief The raw velocity retrieved from the connected quadrature
     * encoder. This is only affected by the QuadratureEdgesPerRotation
     * config. In most situations, the user should instead configure the
     * ExternalFeedbackSensorSource and use the regular velocity getter.
     * 
     * This signal must have its update frequency configured before it
     * will have data.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns RawQuadratureVelocity Status Signal Object
     */
    virtual StatusSignal<units::angular_velocity::turns_per_second_t> &GetRawQuadratureVelocity(bool refresh = true) = 0;
        
    /**
     * \brief The raw position retrieved from the connected pulse-width
     * encoder. This is not affected by any config. In most situations,
     * the user should instead configure the ExternalFeedbackSensorSource
     * and use the regular position getter.
     * 
     * This signal must have its update frequency configured before it
     * will have data.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns RawPulseWidthPosition Status Signal Object
     */
    virtual StatusSignal<units::angle::turn_t> &GetRawPulseWidthPosition(bool refresh = true) = 0;
        
    /**
     * \brief The raw velocity retrieved from the connected pulse-width
     * encoder. This is not affected by any config. In most situations,
     * the user should instead configure the ExternalFeedbackSensorSource
     * and use the regular velocity getter.
     * 
     * This signal must have its update frequency configured before it
     * will have data.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns RawPulseWidthVelocity Status Signal Object
     */
    virtual StatusSignal<units::angular_velocity::turns_per_second_t> &GetRawPulseWidthVelocity(bool refresh = true) = 0;
        
    /**
     * \brief Bridge was disabled most likely due to a short in the motor
     * leads.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_BridgeShort Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_BridgeShort(bool refresh = true) = 0;
        
    /**
     * \brief Bridge was disabled most likely due to a short in the motor
     * leads.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_BridgeShort Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_BridgeShort(bool refresh = true) = 0;
        
    /**
     * \brief Hall sensor signals are invalid.  Check hall sensor and
     * cabling.  This fault can be used to detect when hall cable is
     * unplugged.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_HallSensorMissing Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_HallSensorMissing(bool refresh = true) = 0;
        
    /**
     * \brief Hall sensor signals are invalid.  Check hall sensor and
     * cabling.  This fault can be used to detect when hall cable is
     * unplugged.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_HallSensorMissing Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_HallSensorMissing(bool refresh = true) = 0;
        
    /**
     * \brief Hall sensor signals are invalid during motor drive, so motor
     * was disabled.  Check hall sensor and cabling.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_DriveDisabledHallSensor Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_DriveDisabledHallSensor(bool refresh = true) = 0;
        
    /**
     * \brief Hall sensor signals are invalid during motor drive, so motor
     * was disabled.  Check hall sensor and cabling.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_DriveDisabledHallSensor Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_DriveDisabledHallSensor(bool refresh = true) = 0;
        
    /**
     * \brief Motor temperature signal appears to not be connected.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_MotorTempSensorMissing Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_MotorTempSensorMissing(bool refresh = true) = 0;
        
    /**
     * \brief Motor temperature signal appears to not be connected.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_MotorTempSensorMissing Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_MotorTempSensorMissing(bool refresh = true) = 0;
        
    /**
     * \brief Motor temperature signal indicates motor is too hot.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_MotorTempSensorTooHot Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_MotorTempSensorTooHot(bool refresh = true) = 0;
        
    /**
     * \brief Motor temperature signal indicates motor is too hot.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_MotorTempSensorTooHot Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_MotorTempSensorTooHot(bool refresh = true) = 0;
    

    
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to a
     * short in the motor leads.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_BridgeShort(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to a
     * short in the motor leads.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_BridgeShort() = 0;
    
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid.  Check
     * hall sensor and cabling.  This fault can be used to detect when
     * hall cable is unplugged.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_HallSensorMissing(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid.  Check
     * hall sensor and cabling.  This fault can be used to detect when
     * hall cable is unplugged.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_HallSensorMissing() = 0;
    
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid during
     * motor drive, so motor was disabled.  Check hall sensor and cabling.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_DriveDisabledHallSensor(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Hall sensor signals are invalid during
     * motor drive, so motor was disabled.  Check hall sensor and cabling.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_DriveDisabledHallSensor() = 0;
    
    /**
     * \brief Clear sticky fault: Motor temperature signal appears to not
     * be connected.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorMissing(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Motor temperature signal appears to not
     * be connected.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorMissing() = 0;
    
    /**
     * \brief Clear sticky fault: Motor temperature signal indicates motor
     * is too hot.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorTooHot(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Motor temperature signal indicates motor
     * is too hot.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_MotorTempSensorTooHot() = 0;
};

}
}
}
}

