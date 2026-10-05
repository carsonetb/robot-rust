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

#include "ctre/unit/motor_constants.h"
#include <units/angle.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/current.h>
#include <units/dimensionless.h>
#include <units/temperature.h>
#include <units/voltage.h>

namespace ctre {
namespace phoenix6 {
namespace hardware {
namespace traits {

/**
 * Contains all status signals available for devices that support Talon signals.
 */
class HasTalonSignals
{
public:
    virtual ~HasTalonSignals() = default;
        
    /**
     * \brief App Major Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns VersionMajor Status Signal Object
     */
    virtual StatusSignal<int> &GetVersionMajor(bool refresh = true) = 0;
        
    /**
     * \brief App Minor Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns VersionMinor Status Signal Object
     */
    virtual StatusSignal<int> &GetVersionMinor(bool refresh = true) = 0;
        
    /**
     * \brief App Bugfix Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns VersionBugfix Status Signal Object
     */
    virtual StatusSignal<int> &GetVersionBugfix(bool refresh = true) = 0;
        
    /**
     * \brief App Build Version number.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 255
     * - Default Value: 0
     * - Units: 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns VersionBuild Status Signal Object
     */
    virtual StatusSignal<int> &GetVersionBuild(bool refresh = true) = 0;
        
    /**
     * \brief Full Version of firmware in device.  The format is a four
     * byte value.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 4294967295
     * - Default Value: 0
     * - Units: 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Version Status Signal Object
     */
    virtual StatusSignal<int> &GetVersion(bool refresh = true) = 0;
        
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
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns FaultField Status Signal Object
     */
    virtual StatusSignal<int> &GetFaultField(bool refresh = true) = 0;
        
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
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFaultField Status Signal Object
     */
    virtual StatusSignal<int> &GetStickyFaultField(bool refresh = true) = 0;
        
    /**
     * \brief The applied (output) motor voltage.
     * 
     * - Minimum Value: -40.96
     * - Maximum Value: 40.95
     * - Default Value: 0
     * - Units: V
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MotorVoltage Status Signal Object
     */
    virtual StatusSignal<units::voltage::volt_t> &GetMotorVoltage(bool refresh = true) = 0;
        
    /**
     * \brief Forward Limit Pin.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ForwardLimit Status Signal Object
     */
    virtual StatusSignal<signals::ForwardLimitValue> &GetForwardLimit(bool refresh = true) = 0;
        
    /**
     * \brief Reverse Limit Pin.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ReverseLimit Status Signal Object
     */
    virtual StatusSignal<signals::ReverseLimitValue> &GetReverseLimit(bool refresh = true) = 0;
        
    /**
     * \brief The applied rotor polarity as seen from the front of the
     * motor.  This typically is determined by the Inverted config, but
     * can be overridden if using Follower features.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AppliedRotorPolarity Status Signal Object
     */
    virtual StatusSignal<signals::AppliedRotorPolarityValue> &GetAppliedRotorPolarity(bool refresh = true) = 0;
        
    /**
     * \brief The applied motor duty cycle.
     * 
     * - Minimum Value: -2.0
     * - Maximum Value: 1.9990234375
     * - Default Value: 0
     * - Units: fractional
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DutyCycle Status Signal Object
     */
    virtual StatusSignal<units::dimensionless::scalar_t> &GetDutyCycle(bool refresh = true) = 0;
        
    /**
     * \brief Current corresponding to the torque output by the motor.
     * Similar to StatorCurrent. Users will likely prefer this current to
     * calculate the applied torque to the rotor.
     * 
     * \details Stator current where positive current means torque is
     * applied in the forward direction as determined by the Inverted
     * setting.
     * 
     * - Minimum Value: -327.68
     * - Maximum Value: 327.67
     * - Default Value: 0
     * - Units: A
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns TorqueCurrent Status Signal Object
     */
    virtual StatusSignal<units::current::ampere_t> &GetTorqueCurrent(bool refresh = true) = 0;
        
    /**
     * \brief Current corresponding to the stator windings. Similar to
     * TorqueCurrent. Users will likely prefer TorqueCurrent over
     * StatorCurrent.
     * 
     * \details Stator current where Positive current indicates motoring
     * regardless of direction. Negative current indicates regenerative
     * braking regardless of direction.
     * 
     * - Minimum Value: -327.68
     * - Maximum Value: 327.66
     * - Default Value: 0
     * - Units: A
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StatorCurrent Status Signal Object
     */
    virtual StatusSignal<units::current::ampere_t> &GetStatorCurrent(bool refresh = true) = 0;
        
    /**
     * \brief Measured supply side current.
     * 
     * - Minimum Value: -327.68
     * - Maximum Value: 327.66
     * - Default Value: 0
     * - Units: A
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns SupplyCurrent Status Signal Object
     */
    virtual StatusSignal<units::current::ampere_t> &GetSupplyCurrent(bool refresh = true) = 0;
        
    /**
     * \brief Measured supply voltage to the device.
     * 
     * - Minimum Value: 4
     * - Maximum Value: 29.575
     * - Default Value: 4
     * - Units: V
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns SupplyVoltage Status Signal Object
     */
    virtual StatusSignal<units::voltage::volt_t> &GetSupplyVoltage(bool refresh = true) = 0;
        
    /**
     * \brief Temperature of device.
     * 
     * \details This is the temperature that the device measures itself to
     * be at. Similar to Processor Temperature.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 255.0
     * - Default Value: 0
     * - Units: ℃
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DeviceTemp Status Signal Object
     */
    virtual StatusSignal<units::temperature::celsius_t> &GetDeviceTemp(bool refresh = true) = 0;
        
    /**
     * \brief Temperature of the processor.
     * 
     * \details This is the temperature that the processor measures itself
     * to be at. Similar to Device Temperature.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 255.0
     * - Default Value: 0
     * - Units: ℃
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ProcessorTemp Status Signal Object
     */
    virtual StatusSignal<units::temperature::celsius_t> &GetProcessorTemp(bool refresh = true) = 0;
        
    /**
     * \brief Velocity of the motor rotor. This velocity is not affected
     * by any feedback configs.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns RotorVelocity Status Signal Object
     */
    virtual StatusSignal<units::angular_velocity::turns_per_second_t> &GetRotorVelocity(bool refresh = true) = 0;
        
    /**
     * \brief Position of the motor rotor. This position is only affected
     * by the RotorOffset config and calls to setPosition.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns RotorPosition Status Signal Object
     */
    virtual StatusSignal<units::angle::turn_t> &GetRotorPosition(bool refresh = true) = 0;
        
    /**
     * \brief Velocity of the device in mechanism rotations per second.
     * This can be the velocity of a remote sensor and is affected by the
     * RotorToSensorRatio and SensorToMechanismRatio configs.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Velocity Status Signal Object
     */
    virtual StatusSignal<units::angular_velocity::turns_per_second_t> &GetVelocity(bool refresh = true) = 0;
        
    /**
     * \brief Position of the device in mechanism rotations. This can be
     * the position of a remote sensor and is affected by the
     * RotorToSensorRatio and SensorToMechanismRatio configs, as well as
     * calls to setPosition.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Position Status Signal Object
     */
    virtual StatusSignal<units::angle::turn_t> &GetPosition(bool refresh = true) = 0;
        
    /**
     * \brief Acceleration of the device in mechanism rotations per
     * second². This can be the acceleration of a remote sensor and is
     * affected by the RotorToSensorRatio and SensorToMechanismRatio
     * configs.
     * 
     * - Minimum Value: -2048.0
     * - Maximum Value: 2047.75
     * - Default Value: 0
     * - Units: rotations per second²
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Acceleration Status Signal Object
     */
    virtual StatusSignal<units::angular_acceleration::turns_per_second_squared_t> &GetAcceleration(bool refresh = true) = 0;
        
    /**
     * \brief The active control mode of the motor controller.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ControlMode Status Signal Object
     */
    virtual StatusSignal<signals::ControlModeValue> &GetControlMode(bool refresh = true) = 0;
        
    /**
     * \brief Check if Motion Magic® is running.  This is equivalent to
     * checking that the reported control mode is a Motion Magic® based
     * mode.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MotionMagicIsRunning Status Signal Object
     */
    virtual StatusSignal<signals::MotionMagicIsRunningValue> &GetMotionMagicIsRunning(bool refresh = true) = 0;
        
    /**
     * \brief Indicates if the robot is enabled.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns RobotEnable Status Signal Object
     */
    virtual StatusSignal<signals::RobotEnableValue> &GetRobotEnable(bool refresh = true) = 0;
        
    /**
     * \brief Indicates if device is actuator enabled.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DeviceEnable Status Signal Object
     */
    virtual StatusSignal<signals::DeviceEnableValue> &GetDeviceEnable(bool refresh = true) = 0;
        
    /**
     * \brief The slot that the closed-loop PID is using.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 2
     * - Default Value: 0
     * - Units: 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopSlot Status Signal Object
     */
    virtual StatusSignal<int> &GetClosedLoopSlot(bool refresh = true) = 0;
        
    /**
     * \brief Assess the status of the motor output with respect to load
     * and supply.
     * 
     * \details This routine can be used to determine the general status
     * of motor commutation.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MotorOutputStatus Status Signal Object
     */
    virtual StatusSignal<signals::MotorOutputStatusValue> &GetMotorOutputStatus(bool refresh = true) = 0;
        
    /**
     * \brief The active control mode of the differential controller.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialControlMode Status Signal Object
     */
    virtual StatusSignal<signals::DifferentialControlModeValue> &GetDifferentialControlMode(bool refresh = true) = 0;
        
    /**
     * \brief Average component of the differential velocity of device.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialAverageVelocity Status Signal Object
     */
    virtual StatusSignal<units::angular_velocity::turns_per_second_t> &GetDifferentialAverageVelocity(bool refresh = true) = 0;
        
    /**
     * \brief Average component of the differential position of device.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialAveragePosition Status Signal Object
     */
    virtual StatusSignal<units::angle::turn_t> &GetDifferentialAveragePosition(bool refresh = true) = 0;
        
    /**
     * \brief Difference component of the differential velocity of device.
     * 
     * - Minimum Value: -512.0
     * - Maximum Value: 511.998046875
     * - Default Value: 0
     * - Units: rotations per second
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialDifferenceVelocity Status Signal Object
     */
    virtual StatusSignal<units::angular_velocity::turns_per_second_t> &GetDifferentialDifferenceVelocity(bool refresh = true) = 0;
        
    /**
     * \brief Difference component of the differential position of device.
     * 
     * - Minimum Value: -16384.0
     * - Maximum Value: 16383.999755859375
     * - Default Value: 0
     * - Units: rotations
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialDifferencePosition Status Signal Object
     */
    virtual StatusSignal<units::angle::turn_t> &GetDifferentialDifferencePosition(bool refresh = true) = 0;
        
    /**
     * \brief The slot that the closed-loop differential PID is using.
     * 
     * - Minimum Value: 0
     * - Maximum Value: 2
     * - Default Value: 0
     * - Units: 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopSlot Status Signal Object
     */
    virtual StatusSignal<int> &GetDifferentialClosedLoopSlot(bool refresh = true) = 0;
        
    /**
     * \brief The torque constant (K_T) of the motor.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 0.025500000000000002
     * - Default Value: 0
     * - Units: Nm/A
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MotorKT Status Signal Object
     */
    virtual StatusSignal<ctre::unit::newton_meters_per_ampere_t> &GetMotorKT(bool refresh = true) = 0;
        
    /**
     * \brief The velocity constant (K_V) of the motor.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 2047.0
     * - Default Value: 0
     * - Units: RPM/V
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MotorKV Status Signal Object
     */
    virtual StatusSignal<ctre::unit::rpm_per_volt_t> &GetMotorKV(bool refresh = true) = 0;
        
    /**
     * \brief The stall current of the motor at 12 V output.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 1023.0
     * - Default Value: 0
     * - Units: A
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns MotorStallCurrent Status Signal Object
     */
    virtual StatusSignal<units::current::ampere_t> &GetMotorStallCurrent(bool refresh = true) = 0;
        
    /**
     * \brief The applied output of the bridge.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns BridgeOutput Status Signal Object
     */
    virtual StatusSignal<signals::BridgeOutputValue> &GetBridgeOutput(bool refresh = true) = 0;
        
    /**
     * \brief Whether the device is Phoenix Pro licensed.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns IsProLicensed Status Signal Object
     */
    virtual StatusSignal<bool> &GetIsProLicensed(bool refresh = true) = 0;
        
    /**
     * \brief Temperature of device from second sensor.
     * 
     * \details Newer versions of Talon have multiple temperature
     * measurement methods.
     * 
     * - Minimum Value: 0.0
     * - Maximum Value: 255.0
     * - Default Value: 0
     * - Units: ℃
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns AncillaryDeviceTemp Status Signal Object
     */
    virtual StatusSignal<units::temperature::celsius_t> &GetAncillaryDeviceTemp(bool refresh = true) = 0;
        
    /**
     * \brief The type of motor attached to the Talon.
     * 
     * \details This can be used to determine what motor is attached to
     * the Talon FX.  Return will be "Unknown" if firmware is too old or
     * device is not present.
     * 
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ConnectedMotor Status Signal Object
     */
    virtual StatusSignal<signals::ConnectedMotorValue> &GetConnectedMotor(bool refresh = true) = 0;
        
    /**
     * \brief Hardware fault occurred
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_Hardware Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_Hardware(bool refresh = true) = 0;
        
    /**
     * \brief Hardware fault occurred
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_Hardware Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_Hardware(bool refresh = true) = 0;
        
    /**
     * \brief Processor temperature exceeded limit
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_ProcTemp Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_ProcTemp(bool refresh = true) = 0;
        
    /**
     * \brief Processor temperature exceeded limit
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_ProcTemp Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_ProcTemp(bool refresh = true) = 0;
        
    /**
     * \brief Device temperature exceeded limit
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_DeviceTemp Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_DeviceTemp(bool refresh = true) = 0;
        
    /**
     * \brief Device temperature exceeded limit
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_DeviceTemp Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_DeviceTemp(bool refresh = true) = 0;
        
    /**
     * \brief Device supply voltage dropped to near brownout levels
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_Undervoltage Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_Undervoltage(bool refresh = true) = 0;
        
    /**
     * \brief Device supply voltage dropped to near brownout levels
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_Undervoltage Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_Undervoltage(bool refresh = true) = 0;
        
    /**
     * \brief Device boot while detecting the enable signal
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_BootDuringEnable Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_BootDuringEnable(bool refresh = true) = 0;
        
    /**
     * \brief Device boot while detecting the enable signal
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_BootDuringEnable Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_BootDuringEnable(bool refresh = true) = 0;
        
    /**
     * \brief An unlicensed feature is in use, device may not behave as
     * expected.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_UnlicensedFeatureInUse Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_UnlicensedFeatureInUse(bool refresh = true) = 0;
        
    /**
     * \brief An unlicensed feature is in use, device may not behave as
     * expected.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_UnlicensedFeatureInUse Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_UnlicensedFeatureInUse(bool refresh = true) = 0;
        
    /**
     * \brief Bridge was disabled most likely due to supply voltage
     * dropping too low.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_BridgeBrownout Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_BridgeBrownout(bool refresh = true) = 0;
        
    /**
     * \brief Bridge was disabled most likely due to supply voltage
     * dropping too low.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_BridgeBrownout Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_BridgeBrownout(bool refresh = true) = 0;
        
    /**
     * \brief The remote sensor has reset.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_RemoteSensorReset Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_RemoteSensorReset(bool refresh = true) = 0;
        
    /**
     * \brief The remote sensor has reset.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_RemoteSensorReset Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_RemoteSensorReset(bool refresh = true) = 0;
        
    /**
     * \brief The remote Talon used for differential control is not
     * present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_MissingDifferentialFX Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_MissingDifferentialFX(bool refresh = true) = 0;
        
    /**
     * \brief The remote Talon used for differential control is not
     * present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_MissingDifferentialFX Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_MissingDifferentialFX(bool refresh = true) = 0;
        
    /**
     * \brief The remote sensor position has overflowed. Because of the
     * nature of remote sensors, it is possible for the remote sensor
     * position to overflow beyond what is supported by the status signal
     * frame. However, this is rare and cannot occur over the course of an
     * FRC match under normal use.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_RemoteSensorPosOverflow Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_RemoteSensorPosOverflow(bool refresh = true) = 0;
        
    /**
     * \brief The remote sensor position has overflowed. Because of the
     * nature of remote sensors, it is possible for the remote sensor
     * position to overflow beyond what is supported by the status signal
     * frame. However, this is rare and cannot occur over the course of an
     * FRC match under normal use.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_RemoteSensorPosOverflow Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_RemoteSensorPosOverflow(bool refresh = true) = 0;
        
    /**
     * \brief Supply Voltage has exceeded the maximum voltage rating of
     * device.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_OverSupplyV Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_OverSupplyV(bool refresh = true) = 0;
        
    /**
     * \brief Supply Voltage has exceeded the maximum voltage rating of
     * device.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_OverSupplyV Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_OverSupplyV(bool refresh = true) = 0;
        
    /**
     * \brief Supply Voltage is unstable.  Ensure you are using a battery
     * and current limited power supply.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_UnstableSupplyV Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_UnstableSupplyV(bool refresh = true) = 0;
        
    /**
     * \brief Supply Voltage is unstable.  Ensure you are using a battery
     * and current limited power supply.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_UnstableSupplyV Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_UnstableSupplyV(bool refresh = true) = 0;
        
    /**
     * \brief Reverse limit switch has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_ReverseHardLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_ReverseHardLimit(bool refresh = true) = 0;
        
    /**
     * \brief Reverse limit switch has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_ReverseHardLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_ReverseHardLimit(bool refresh = true) = 0;
        
    /**
     * \brief Forward limit switch has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_ForwardHardLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_ForwardHardLimit(bool refresh = true) = 0;
        
    /**
     * \brief Forward limit switch has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_ForwardHardLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_ForwardHardLimit(bool refresh = true) = 0;
        
    /**
     * \brief Reverse soft limit has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_ReverseSoftLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_ReverseSoftLimit(bool refresh = true) = 0;
        
    /**
     * \brief Reverse soft limit has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_ReverseSoftLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_ReverseSoftLimit(bool refresh = true) = 0;
        
    /**
     * \brief Forward soft limit has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_ForwardSoftLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_ForwardSoftLimit(bool refresh = true) = 0;
        
    /**
     * \brief Forward soft limit has been asserted.  Output is set to
     * neutral.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_ForwardSoftLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_ForwardSoftLimit(bool refresh = true) = 0;
        
    /**
     * \brief The remote soft limit device is not present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_MissingSoftLimitRemote Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_MissingSoftLimitRemote(bool refresh = true) = 0;
        
    /**
     * \brief The remote soft limit device is not present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_MissingSoftLimitRemote Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_MissingSoftLimitRemote(bool refresh = true) = 0;
        
    /**
     * \brief The remote limit switch device is not present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_MissingHardLimitRemote Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_MissingHardLimitRemote(bool refresh = true) = 0;
        
    /**
     * \brief The remote limit switch device is not present on CAN Bus.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_MissingHardLimitRemote Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_MissingHardLimitRemote(bool refresh = true) = 0;
        
    /**
     * \brief The remote sensor's data is no longer trusted. This can
     * happen if the remote sensor disappears from the CAN bus or if the
     * remote sensor indicates its data is no longer valid, such as when a
     * CANcoder's magnet strength falls into the "red" range.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_RemoteSensorDataInvalid Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_RemoteSensorDataInvalid(bool refresh = true) = 0;
        
    /**
     * \brief The remote sensor's data is no longer trusted. This can
     * happen if the remote sensor disappears from the CAN bus or if the
     * remote sensor indicates its data is no longer valid, such as when a
     * CANcoder's magnet strength falls into the "red" range.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_RemoteSensorDataInvalid Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_RemoteSensorDataInvalid(bool refresh = true) = 0;
        
    /**
     * \brief The remote sensor used for fusion has fallen out of sync to
     * the local sensor. A re-synchronization has occurred, which may
     * cause a discontinuity. This typically happens if there is
     * significant slop in the mechanism, or if the RotorToSensorRatio
     * configuration parameter is incorrect.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_FusedSensorOutOfSync Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_FusedSensorOutOfSync(bool refresh = true) = 0;
        
    /**
     * \brief The remote sensor used for fusion has fallen out of sync to
     * the local sensor. A re-synchronization has occurred, which may
     * cause a discontinuity. This typically happens if there is
     * significant slop in the mechanism, or if the RotorToSensorRatio
     * configuration parameter is incorrect.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_FusedSensorOutOfSync Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_FusedSensorOutOfSync(bool refresh = true) = 0;
        
    /**
     * \brief Stator current limit occured.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_StatorCurrLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_StatorCurrLimit(bool refresh = true) = 0;
        
    /**
     * \brief Stator current limit occured.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_StatorCurrLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_StatorCurrLimit(bool refresh = true) = 0;
        
    /**
     * \brief Supply current limit occured.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_SupplyCurrLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_SupplyCurrLimit(bool refresh = true) = 0;
        
    /**
     * \brief Supply current limit occured.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_SupplyCurrLimit Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_SupplyCurrLimit(bool refresh = true) = 0;
        
    /**
     * \brief Using Fused CANcoder feature while unlicensed. Device has
     * fallen back to remote CANcoder.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_UsingFusedCANcoderWhileUnlicensed Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_UsingFusedCANcoderWhileUnlicensed(bool refresh = true) = 0;
        
    /**
     * \brief Using Fused CANcoder feature while unlicensed. Device has
     * fallen back to remote CANcoder.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_UsingFusedCANcoderWhileUnlicensed Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_UsingFusedCANcoderWhileUnlicensed(bool refresh = true) = 0;
        
    /**
     * \brief Static brake was momentarily disabled due to excessive
     * braking current while disabled.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns Fault_StaticBrakeDisabled Status Signal Object
     */
    virtual StatusSignal<bool> &GetFault_StaticBrakeDisabled(bool refresh = true) = 0;
        
    /**
     * \brief Static brake was momentarily disabled due to excessive
     * braking current while disabled.
     * 
     * - Default Value: False
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns StickyFault_StaticBrakeDisabled Status Signal Object
     */
    virtual StatusSignal<bool> &GetStickyFault_StaticBrakeDisabled(bool refresh = true) = 0;
    
    /**
     * \brief Closed loop proportional component
     * 
     * \details The portion of the closed loop output that is the
     * proportional to the error. Alternatively, the p-Contribution of the
     * closed loop output.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopProportionalOutput Status Signal object
     */
    virtual StatusSignal<double> &GetClosedLoopProportionalOutput(bool refresh = true) = 0;
    
    /**
     * \brief Closed loop integrated component
     * 
     * \details The portion of the closed loop output that is proportional
     * to the integrated error. Alternatively, the i-Contribution of the
     * closed loop output.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopIntegratedOutput Status Signal object
     */
    virtual StatusSignal<double> &GetClosedLoopIntegratedOutput(bool refresh = true) = 0;
    
    /**
     * \brief Feedforward passed by the user
     * 
     * \details This is the general feedforward that the user provides for
     * the closed loop.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopFeedForward Status Signal object
     */
    virtual StatusSignal<double> &GetClosedLoopFeedForward(bool refresh = true) = 0;
    
    /**
     * \brief Closed loop derivative component
     * 
     * \details The portion of the closed loop output that is the
     * proportional to the deriviative the error. Alternatively, the
     * d-Contribution of the closed loop output.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopDerivativeOutput Status Signal object
     */
    virtual StatusSignal<double> &GetClosedLoopDerivativeOutput(bool refresh = true) = 0;
    
    /**
     * \brief Closed loop total output
     * 
     * \details The total output of the closed loop output.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopOutput Status Signal object
     */
    virtual StatusSignal<double> &GetClosedLoopOutput(bool refresh = true) = 0;
    
    /**
     * \brief Value that the closed loop is targeting
     * 
     * \details This is the value that the closed loop PID controller
     * targets.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopReference Status Signal object
     */
    virtual StatusSignal<double> &GetClosedLoopReference(bool refresh = true) = 0;
    
    /**
     * \brief Derivative of the target that the closed loop is targeting
     * 
     * \details This is the change in the closed loop reference. This may
     * be used in the feed-forward calculation, the derivative-error, or
     * in application of the signage for kS. Typically, this represents
     * the target velocity during Motion Magic®.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopReferenceSlope Status Signal object
     */
    virtual StatusSignal<double> &GetClosedLoopReferenceSlope(bool refresh = true) = 0;
    
    /**
     * \brief The difference between target reference and current
     * measurement
     * 
     * \details This is the value that is treated as the error in the PID
     * loop.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns ClosedLoopError Status Signal object
     */
    virtual StatusSignal<double> &GetClosedLoopError(bool refresh = true) = 0;
    
    /**
     * \brief The calculated motor output for differential followers.
     * 
     * \details This is a torque request when using the TorqueCurrentFOC
     * control output type, and a duty cycle in all other control types.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialOutput Status Signal object
     */
    virtual StatusSignal<double> &GetDifferentialOutput(bool refresh = true) = 0;
    
    /**
     * \brief Differential closed loop proportional component
     * 
     * \details The portion of the differential closed loop output that is
     * the proportional to the error. Alternatively, the p-Contribution of
     * the closed loop output.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopProportionalOutput Status Signal object
     */
    virtual StatusSignal<double> &GetDifferentialClosedLoopProportionalOutput(bool refresh = true) = 0;
    
    /**
     * \brief Differential closed loop integrated component
     * 
     * \details The portion of the differential closed loop output that is
     * proportional to the integrated error. Alternatively, the
     * i-Contribution of the closed loop output.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopIntegratedOutput Status Signal object
     */
    virtual StatusSignal<double> &GetDifferentialClosedLoopIntegratedOutput(bool refresh = true) = 0;
    
    /**
     * \brief Differential Feedforward passed by the user
     * 
     * \details This is the general feedforward that the user provides for
     * the differential closed loop.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopFeedForward Status Signal object
     */
    virtual StatusSignal<double> &GetDifferentialClosedLoopFeedForward(bool refresh = true) = 0;
    
    /**
     * \brief Differential closed loop derivative component
     * 
     * \details The portion of the differential closed loop output that is
     * the proportional to the deriviative the error. Alternatively, the
     * d-Contribution of the closed loop output.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopDerivativeOutput Status Signal object
     */
    virtual StatusSignal<double> &GetDifferentialClosedLoopDerivativeOutput(bool refresh = true) = 0;
    
    /**
     * \brief Differential closed loop total output
     * 
     * \details The total output of the differential closed loop output.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopOutput Status Signal object
     */
    virtual StatusSignal<double> &GetDifferentialClosedLoopOutput(bool refresh = true) = 0;
    
    /**
     * \brief Value that the differential closed loop is targeting
     * 
     * \details This is the value that the differential closed loop PID
     * controller targets.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopReference Status Signal object
     */
    virtual StatusSignal<double> &GetDifferentialClosedLoopReference(bool refresh = true) = 0;
    
    /**
     * \brief Derivative of the target that the differential closed loop
     * is targeting
     * 
     * \details This is the change in the closed loop reference. This may
     * be used in the feed-forward calculation, the derivative-error, or
     * in application of the signage for kS. Typically, this represents
     * the target velocity during Motion Magic®.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopReferenceSlope Status Signal object
     */
    virtual StatusSignal<double> &GetDifferentialClosedLoopReferenceSlope(bool refresh = true) = 0;
    
    /**
     * \brief The difference between target differential reference and
     * current measurement
     * 
     * \details This is the value that is treated as the error in the
     * differential PID loop.
     * 
     * This refreshes and returns a cached StatusSignal object.
     * 
     * \param refresh Whether to refresh the StatusSignal before returning it; defaults to true
     * \returns DifferentialClosedLoopError Status Signal object
     */
    virtual StatusSignal<double> &GetDifferentialClosedLoopError(bool refresh = true) = 0;
    

    
    /**
     * \brief Sets the mechanism position of the device in mechanism
     * rotations.
     * 
     * \param newValue Value to set to. Units are in rotations.
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode SetPosition(units::angle::turn_t newValue, units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Sets the mechanism position of the device in mechanism
     * rotations.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \param newValue Value to set to. Units are in rotations.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode SetPosition(units::angle::turn_t newValue) = 0;
    
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
    virtual ctre::phoenix::StatusCode ClearStickyFaults(units::time::second_t timeoutSeconds) = 0;
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
    virtual ctre::phoenix::StatusCode ClearStickyFaults() = 0;
    
    /**
     * \brief Clear sticky fault: Hardware fault occurred
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_Hardware(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Hardware fault occurred
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_Hardware() = 0;
    
    /**
     * \brief Clear sticky fault: Processor temperature exceeded limit
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_ProcTemp(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Processor temperature exceeded limit
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_ProcTemp() = 0;
    
    /**
     * \brief Clear sticky fault: Device temperature exceeded limit
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_DeviceTemp(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Device temperature exceeded limit
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_DeviceTemp() = 0;
    
    /**
     * \brief Clear sticky fault: Device supply voltage dropped to near
     * brownout levels
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_Undervoltage(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Device supply voltage dropped to near
     * brownout levels
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_Undervoltage() = 0;
    
    /**
     * \brief Clear sticky fault: Device boot while detecting the enable
     * signal
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_BootDuringEnable(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Device boot while detecting the enable
     * signal
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_BootDuringEnable() = 0;
    
    /**
     * \brief Clear sticky fault: An unlicensed feature is in use, device
     * may not behave as expected.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_UnlicensedFeatureInUse(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: An unlicensed feature is in use, device
     * may not behave as expected.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_UnlicensedFeatureInUse() = 0;
    
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to
     * supply voltage dropping too low.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_BridgeBrownout(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Bridge was disabled most likely due to
     * supply voltage dropping too low.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_BridgeBrownout() = 0;
    
    /**
     * \brief Clear sticky fault: The remote sensor has reset.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorReset(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: The remote sensor has reset.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorReset() = 0;
    
    /**
     * \brief Clear sticky fault: The remote Talon used for differential
     * control is not present on CAN Bus.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_MissingDifferentialFX(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: The remote Talon used for differential
     * control is not present on CAN Bus.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_MissingDifferentialFX() = 0;
    
    /**
     * \brief Clear sticky fault: The remote sensor position has
     * overflowed. Because of the nature of remote sensors, it is possible
     * for the remote sensor position to overflow beyond what is supported
     * by the status signal frame. However, this is rare and cannot occur
     * over the course of an FRC match under normal use.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorPosOverflow(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: The remote sensor position has
     * overflowed. Because of the nature of remote sensors, it is possible
     * for the remote sensor position to overflow beyond what is supported
     * by the status signal frame. However, this is rare and cannot occur
     * over the course of an FRC match under normal use.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorPosOverflow() = 0;
    
    /**
     * \brief Clear sticky fault: Supply Voltage has exceeded the maximum
     * voltage rating of device.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_OverSupplyV(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Supply Voltage has exceeded the maximum
     * voltage rating of device.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_OverSupplyV() = 0;
    
    /**
     * \brief Clear sticky fault: Supply Voltage is unstable.  Ensure you
     * are using a battery and current limited power supply.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_UnstableSupplyV(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Supply Voltage is unstable.  Ensure you
     * are using a battery and current limited power supply.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_UnstableSupplyV() = 0;
    
    /**
     * \brief Clear sticky fault: Reverse limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_ReverseHardLimit(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Reverse limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_ReverseHardLimit() = 0;
    
    /**
     * \brief Clear sticky fault: Forward limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_ForwardHardLimit(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Forward limit switch has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_ForwardHardLimit() = 0;
    
    /**
     * \brief Clear sticky fault: Reverse soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_ReverseSoftLimit(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Reverse soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_ReverseSoftLimit() = 0;
    
    /**
     * \brief Clear sticky fault: Forward soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_ForwardSoftLimit(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Forward soft limit has been asserted. 
     * Output is set to neutral.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_ForwardSoftLimit() = 0;
    
    /**
     * \brief Clear sticky fault: The remote soft limit device is not
     * present on CAN Bus.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_MissingSoftLimitRemote(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: The remote soft limit device is not
     * present on CAN Bus.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_MissingSoftLimitRemote() = 0;
    
    /**
     * \brief Clear sticky fault: The remote limit switch device is not
     * present on CAN Bus.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_MissingHardLimitRemote(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: The remote limit switch device is not
     * present on CAN Bus.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_MissingHardLimitRemote() = 0;
    
    /**
     * \brief Clear sticky fault: The remote sensor's data is no longer
     * trusted. This can happen if the remote sensor disappears from the
     * CAN bus or if the remote sensor indicates its data is no longer
     * valid, such as when a CANcoder's magnet strength falls into the
     * "red" range.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorDataInvalid(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: The remote sensor's data is no longer
     * trusted. This can happen if the remote sensor disappears from the
     * CAN bus or if the remote sensor indicates its data is no longer
     * valid, such as when a CANcoder's magnet strength falls into the
     * "red" range.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_RemoteSensorDataInvalid() = 0;
    
    /**
     * \brief Clear sticky fault: The remote sensor used for fusion has
     * fallen out of sync to the local sensor. A re-synchronization has
     * occurred, which may cause a discontinuity. This typically happens
     * if there is significant slop in the mechanism, or if the
     * RotorToSensorRatio configuration parameter is incorrect.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_FusedSensorOutOfSync(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: The remote sensor used for fusion has
     * fallen out of sync to the local sensor. A re-synchronization has
     * occurred, which may cause a discontinuity. This typically happens
     * if there is significant slop in the mechanism, or if the
     * RotorToSensorRatio configuration parameter is incorrect.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_FusedSensorOutOfSync() = 0;
    
    /**
     * \brief Clear sticky fault: Stator current limit occured.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_StatorCurrLimit(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Stator current limit occured.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_StatorCurrLimit() = 0;
    
    /**
     * \brief Clear sticky fault: Supply current limit occured.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_SupplyCurrLimit(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Supply current limit occured.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_SupplyCurrLimit() = 0;
    
    /**
     * \brief Clear sticky fault: Using Fused CANcoder feature while
     * unlicensed. Device has fallen back to remote CANcoder.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_UsingFusedCANcoderWhileUnlicensed(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Using Fused CANcoder feature while
     * unlicensed. Device has fallen back to remote CANcoder.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_UsingFusedCANcoderWhileUnlicensed() = 0;
    
    /**
     * \brief Clear sticky fault: Static brake was momentarily disabled
     * due to excessive braking current while disabled.
     * 
     * \param timeoutSeconds Maximum time to wait up to in seconds.
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_StaticBrakeDisabled(units::time::second_t timeoutSeconds) = 0;
    /**
     * \brief Clear sticky fault: Static brake was momentarily disabled
     * due to excessive braking current while disabled.
     * 
     * This will wait up to 0.100 seconds (100ms) by default.
     * 
     * \returns StatusCode of the set command
     */
    virtual ctre::phoenix::StatusCode ClearStickyFault_StaticBrakeDisabled() = 0;
};

}
}
}
}

