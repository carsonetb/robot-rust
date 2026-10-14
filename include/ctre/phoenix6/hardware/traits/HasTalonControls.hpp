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
#include "ctre/phoenix6/hardware/traits/CommonDevice.hpp"
#include "ctre/phoenix6/controls/DutyCycleOut.hpp"
#include "ctre/phoenix6/controls/VoltageOut.hpp"
#include "ctre/phoenix6/controls/PositionDutyCycle.hpp"
#include "ctre/phoenix6/controls/PositionVoltage.hpp"
#include "ctre/phoenix6/controls/VelocityDutyCycle.hpp"
#include "ctre/phoenix6/controls/VelocityVoltage.hpp"
#include "ctre/phoenix6/controls/MotionMagicDutyCycle.hpp"
#include "ctre/phoenix6/controls/MotionMagicVoltage.hpp"
#include "ctre/phoenix6/controls/MotionMagicVelocityDutyCycle.hpp"
#include "ctre/phoenix6/controls/MotionMagicVelocityVoltage.hpp"
#include "ctre/phoenix6/controls/MotionMagicExpoDutyCycle.hpp"
#include "ctre/phoenix6/controls/MotionMagicExpoVoltage.hpp"
#include "ctre/phoenix6/controls/DynamicMotionMagicDutyCycle.hpp"
#include "ctre/phoenix6/controls/DynamicMotionMagicVoltage.hpp"
#include "ctre/phoenix6/controls/DynamicMotionMagicExpoDutyCycle.hpp"
#include "ctre/phoenix6/controls/DynamicMotionMagicExpoVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialPositionDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialPositionVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialVelocityDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialVelocityVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicExpoDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicExpoVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicVelocityDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicVelocityVoltage.hpp"
#include "ctre/phoenix6/controls/Follower.hpp"
#include "ctre/phoenix6/controls/StrictFollower.hpp"
#include "ctre/phoenix6/controls/DifferentialFollower.hpp"
#include "ctre/phoenix6/controls/DifferentialStrictFollower.hpp"
#include "ctre/phoenix6/controls/StaticBrake.hpp"
#include "ctre/phoenix6/controls/NeutralOut.hpp"
#include "ctre/phoenix6/controls/CoastOut.hpp"
#include "ctre/phoenix6/controls/compound/Diff_DutyCycleOut_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionDutyCycle_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityDutyCycle_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicDutyCycle_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoDutyCycle_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityDutyCycle_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_DutyCycleOut_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_DutyCycleOut_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionDutyCycle_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityDutyCycle_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicDutyCycle_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoDutyCycle_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityDutyCycle_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VoltageOut_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VoltageOut_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VoltageOut_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionVoltage_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityVoltage_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVoltage_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicExpoVoltage_Open.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVelocityVoltage_Open.hpp"


namespace ctre {
namespace phoenix6 {
namespace hardware {
namespace traits {

/**
 * Contains all control functions available for devices that support Talon
 * controls.
 */
class HasTalonControls : public virtual CommonDevice
{
public:
    virtual ~HasTalonControls() = default;
    
    
    /**
     * \brief Request a specified motor duty cycle.
     * 
     * \details This control mode will output a proportion of the supplied
     * voltage which is supplied by the user.
     * 
     * - DutyCycleOut Parameters: 
     *   - Output: Proportion of supply voltage to apply in fractional units between
     *             -1 and +1
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DutyCycleOut const &request) = 0;
    
    /**
     * \brief Request a specified voltage.
     * 
     * \details This control mode will attempt to apply the specified
     * voltage to the motor. If the supply voltage is below the requested
     * voltage, the motor controller will output the supply voltage.
     * 
     * - VoltageOut Parameters: 
     *   - Output: Voltage to attempt to drive at
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::VoltageOut const &request) = 0;
    
    /**
     * \brief Request PID to target position with duty cycle feedforward.
     * 
     * \details This control mode will set the motor's position setpoint
     * to the position specified by the user. In addition, it will apply
     * an additional duty cycle as an arbitrary feedforward value.
     * 
     * - PositionDutyCycle Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - Velocity: Velocity to drive toward in rotations per second. This is
     *               typically used for motion profiles generated by the robot
     *               program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::PositionDutyCycle const &request) = 0;
    
    /**
     * \brief Request PID to target position with voltage feedforward
     * 
     * \details This control mode will set the motor's position setpoint
     * to the position specified by the user. In addition, it will apply
     * an additional voltage as an arbitrary feedforward value.
     * 
     * - PositionVoltage Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - Velocity: Velocity to drive toward in rotations per second. This is
     *               typically used for motion profiles generated by the robot
     *               program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::PositionVoltage const &request) = 0;
    
    /**
     * \brief Request PID to target velocity with duty cycle feedforward.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. In addition, it will apply
     * an additional voltage as an arbitrary feedforward value.
     * 
     * - VelocityDutyCycle Parameters: 
     *   - Velocity: Velocity to drive toward in rotations per second.
     *   - Acceleration: Acceleration to drive toward in rotations per second
     *                   squared. This is typically used for motion profiles
     *                   generated by the robot program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::VelocityDutyCycle const &request) = 0;
    
    /**
     * \brief Request PID to target velocity with voltage feedforward.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. In addition, it will apply
     * an additional voltage as an arbitrary feedforward value.
     * 
     * - VelocityVoltage Parameters: 
     *   - Velocity: Velocity to drive toward in rotations per second.
     *   - Acceleration: Acceleration to drive toward in rotations per second
     *                   squared. This is typically used for motion profiles
     *                   generated by the robot program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts This is added to the output of
     *                  the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::VelocityVoltage const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  Users can optionally provide a duty cycle
     * feedforward.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the Cruise Velocity, Acceleration, and
     * (optional) Jerk specified via the Motion Magic® configuration
     * values.  This control mode does not use the Expo_kV or Expo_kA
     * configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - MotionMagicDutyCycle Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::MotionMagicDutyCycle const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  Users can optionally provide a voltage
     * feedforward.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the Cruise Velocity, Acceleration, and
     * (optional) Jerk specified via the Motion Magic® configuration
     * values.  This control mode does not use the Expo_kV or Expo_kA
     * configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - MotionMagicVoltage Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::MotionMagicVoltage const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final velocity using a
     * motion profile.  This allows smooth transitions between velocity
     * set points.  Users can optionally provide a duty cycle feedforward.
     * 
     * \details Motion Magic® Velocity produces a motion profile in
     * real-time while attempting to honor the specified Acceleration and
     * (optional) Jerk.  This control mode does not use the
     * CruiseVelocity, Expo_kV, or Expo_kA configs.
     * 
     * If the specified acceleration is zero, the Acceleration under
     * Motion Magic® configuration parameter is used instead.  This allows
     * for runtime adjustment of acceleration for advanced users.  Jerk is
     * also specified in the Motion Magic® persistent configuration
     * values.  If Jerk is set to zero, Motion Magic® will produce a
     * trapezoidal acceleration profile.
     * 
     * Target velocity can also be changed on-the-fly and Motion Magic®
     * will do its best to adjust the profile.  This control mode is duty
     * cycle based, so relevant closed-loop gains will use fractional duty
     * cycle for the numerator:  +1.0 represents full forward output.
     * 
     * - MotionMagicVelocityDutyCycle Parameters: 
     *   - Velocity: Target velocity to drive toward in rotations per second.  This
     *               can be changed on-the fly.
     *   - Acceleration: This is the absolute Acceleration to use generating the
     *                   profile.  If this parameter is zero, the Acceleration
     *                   persistent configuration parameter is used instead.
     *                   Acceleration is in rotations per second squared.  If
     *                   nonzero, the signage does not matter as the absolute value
     *                   is used.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::MotionMagicVelocityDutyCycle const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final velocity using a
     * motion profile.  This allows smooth transitions between velocity
     * set points.  Users can optionally provide a voltage feedforward.
     * 
     * \details Motion Magic® Velocity produces a motion profile in
     * real-time while attempting to honor the specified Acceleration and
     * (optional) Jerk.  This control mode does not use the
     * CruiseVelocity, Expo_kV, or Expo_kA configs.
     * 
     * If the specified acceleration is zero, the Acceleration under
     * Motion Magic® configuration parameter is used instead.  This allows
     * for runtime adjustment of acceleration for advanced users.  Jerk is
     * also specified in the Motion Magic® persistent configuration
     * values.  If Jerk is set to zero, Motion Magic® will produce a
     * trapezoidal acceleration profile.
     * 
     * Target velocity can also be changed on-the-fly and Motion Magic®
     * will do its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - MotionMagicVelocityVoltage Parameters: 
     *   - Velocity: Target velocity to drive toward in rotations per second.  This
     *               can be changed on-the fly.
     *   - Acceleration: This is the absolute Acceleration to use generating the
     *                   profile.  If this parameter is zero, the Acceleration
     *                   persistent configuration parameter is used instead.
     *                   Acceleration is in rotations per second squared.  If
     *                   nonzero, the signage does not matter as the absolute value
     *                   is used.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::MotionMagicVelocityVoltage const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using an
     * exponential motion profile.  Users can optionally provide a duty
     * cycle feedforward.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the Cruise Velocity (optional) and the
     * mechanism kV and kA, specified via the Motion Magic® configuration
     * values.  Note that unlike the slot gains, the Expo_kV and Expo_kA
     * configs are always in output units of Volts.
     * 
     * Setting Cruise Velocity to 0 will allow the profile to run to the
     * max possible velocity based on Expo_kV.  This control mode does not
     * use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - MotionMagicExpoDutyCycle Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::MotionMagicExpoDutyCycle const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using an
     * exponential motion profile.  Users can optionally provide a voltage
     * feedforward.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the Cruise Velocity (optional) and the
     * mechanism kV and kA, specified via the Motion Magic® configuration
     * values.  Note that unlike the slot gains, the Expo_kV and Expo_kA
     * configs are always in output units of Volts.
     * 
     * Setting Cruise Velocity to 0 will allow the profile to run to the
     * max possible velocity based on Expo_kV.  This control mode does not
     * use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - MotionMagicExpoVoltage Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::MotionMagicExpoVoltage const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  This dynamic request allows runtime changes to
     * Cruise Velocity, Acceleration, and (optional) Jerk.  Users can
     * optionally provide a duty cycle feedforward.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the specified Cruise Velocity, Acceleration,
     * and (optional) Jerk.  This control mode does not use the Expo_kV or
     * Expo_kA configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile. This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - DynamicMotionMagicDutyCycle Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - Velocity: Cruise velocity for profiling.  The signage does not matter as
     *               the device will use the absolute value for profile generation.
     *   - Acceleration: Acceleration for profiling.  The signage does not matter as
     *                   the device will use the absolute value for profile
     *                   generation
     *   - Jerk: Jerk for profiling.  The signage does not matter as the device will
     *           use the absolute value for profile generation.
     *           
     *           Jerk is optional; if this is set to zero, then Motion Magic® will
     *           not apply a Jerk limit.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DynamicMotionMagicDutyCycle const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  This dynamic request allows runtime changes to
     * Cruise Velocity, Acceleration, and (optional) Jerk.  Users can
     * optionally provide a voltage feedforward.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the specified Cruise Velocity, Acceleration,
     * and (optional) Jerk.  This control mode does not use the Expo_kV or
     * Expo_kA configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - DynamicMotionMagicVoltage Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - Velocity: Cruise velocity for profiling.  The signage does not matter as
     *               the device will use the absolute value for profile generation.
     *   - Acceleration: Acceleration for profiling.  The signage does not matter as
     *                   the device will use the absolute value for profile
     *                   generation.
     *   - Jerk: Jerk for profiling.  The signage does not matter as the device will
     *           use the absolute value for profile generation.
     *           
     *           Jerk is optional; if this is set to zero, then Motion Magic® will
     *           not apply a Jerk limit.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DynamicMotionMagicVoltage const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® Expo to target a final position using
     * an exponential motion profile.  This dynamic request allows runtime
     * changes to the profile kV, kA, and (optional) Cruise Velocity. 
     * Users can optionally provide a duty cycle feedforward.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the specified Cruise Velocity (optional)
     * and the mechanism kV and kA.  Note that unlike the slot gains, the
     * Expo_kV and Expo_kA parameters are always in output units of Volts.
     * 
     * Setting the Cruise Velocity to 0 will allow the profile to run to
     * the max possible velocity based on Expo_kV.  This control mode does
     * not use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile. This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - DynamicMotionMagicExpoDutyCycle Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - kV: Mechanism kV for profiling.  Unlike the kV slot gain, this is always
     *         in units of V/rps.
     *         
     *         This represents the amount of voltage necessary to hold a velocity. 
     *         In terms of the Motion Magic® Expo profile, a higher kV results in a
     *         slower maximum velocity.
     *   - kA: Mechanism kA for profiling.  Unlike the kA slot gain, this is always
     *         in units of V/rps².
     *         
     *         This represents the amount of voltage necessary to achieve an
     *         acceleration.  In terms of the Motion Magic® Expo profile, a higher
     *         kA results in a slower acceleration.
     *   - Velocity: Cruise velocity for profiling.  The signage does not matter as
     *               the device will use the absolute value for profile generation. 
     *               Setting this to 0 will allow the profile to run to the max
     *               possible velocity based on Expo_kV.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *                  This is added to the output of the onboard feedforward
     *                  terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DynamicMotionMagicExpoDutyCycle const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® Expo to target a final position using
     * an exponential motion profile.  This dynamic request allows runtime
     * changes to the profile kV, kA, and (optional) Cruise Velocity. 
     * Users can optionally provide a voltage feedforward.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the specified Cruise Velocity (optional)
     * and the mechanism kV and kA.  Note that unlike the slot gains, the
     * Expo_kV and Expo_kA parameters are always in output units of Volts.
     * 
     * Setting the Cruise Velocity to 0 will allow the profile to run to
     * the max possible velocity based on Expo_kV.  This control mode does
     * not use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - DynamicMotionMagicExpoVoltage Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - kV: Mechanism kV for profiling.  Unlike the kV slot gain, this is always
     *         in units of V/rps.
     *         
     *         This represents the amount of voltage necessary to hold a velocity. 
     *         In terms of the Motion Magic® Expo profile, a higher kV results in a
     *         slower maximum velocity.
     *   - kA: Mechanism kA for profiling.  Unlike the kA slot gain, this is always
     *         in units of V/rps².
     *         
     *         This represents the amount of voltage necessary to achieve an
     *         acceleration.  In terms of the Motion Magic® Expo profile, a higher
     *         kA results in a slower acceleration.
     *   - Velocity: Cruise velocity for profiling.  The signage does not matter as
     *               the device will use the absolute value for profile generation. 
     *               Setting this to 0 will allow the profile to run to the max
     *               possible velocity based on Expo_kV.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - FeedForward: Feedforward to apply in volts. This is added to the output
     *                  of the onboard feedforward terms.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *           configuration api to set the gain values for the selected slot
     *           before enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DynamicMotionMagicExpoVoltage const &request) = 0;
    
    /**
     * \brief Request a specified motor duty cycle with a differential
     * position closed-loop.
     * 
     * \details This control mode will output a proportion of the supplied
     * voltage which is supplied by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialDutyCycle Parameters: 
     *   - AverageOutput: Proportion of supply voltage to apply on the Average axis
     *                    in fractional units between -1 and +1.
     *   - DifferentialPosition: Differential position to drive towards in
     *                           rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialDutyCycle const &request) = 0;
    
    /**
     * \brief Request a specified voltage with a differential position
     * closed-loop.
     * 
     * \details This control mode will attempt to apply the specified
     * voltage to the motor. If the supply voltage is below the requested
     * voltage, the motor controller will output the supply voltage. It
     * will also set the motor's differential position setpoint to the
     * specified position.
     * 
     * - DifferentialVoltage Parameters: 
     *   - AverageOutput: Voltage to attempt to drive at on the Average axis.
     *   - DifferentialPosition: Differential position to drive towards in
     *                           rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialVoltage const &request) = 0;
    
    /**
     * \brief Request PID to target position with a differential position
     * setpoint.
     * 
     * \details This control mode will set the motor's position setpoint
     * to the position specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialPositionDutyCycle Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialPositionDutyCycle const &request) = 0;
    
    /**
     * \brief Request PID to target position with a differential position
     * setpoint
     * 
     * \details This control mode will set the motor's position setpoint
     * to the position specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialPositionVoltage Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialPositionVoltage const &request) = 0;
    
    /**
     * \brief Request PID to target velocity with a differential position
     * setpoint.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialVelocityDutyCycle Parameters: 
     *   - AverageVelocity: Average velocity to drive toward in rotations per
     *                      second.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialVelocityDutyCycle const &request) = 0;
    
    /**
     * \brief Request PID to target velocity with a differential position
     * setpoint.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialVelocityVoltage Parameters: 
     *   - AverageVelocity: Average velocity to drive toward in rotations per
     *                      second.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialVelocityVoltage const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile, and PID to a differential position setpoint.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the Cruise Velocity, Acceleration, and
     * (optional) Jerk specified via the Motion Magic® configuration
     * values.  This control mode does not use the Expo_kV or Expo_kA
     * configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - DifferentialMotionMagicDutyCycle Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicDutyCycle const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile, and PID to a differential position setpoint.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the Cruise Velocity, Acceleration, and
     * (optional) Jerk specified via the Motion Magic® configuration
     * values.  This control mode does not use the Expo_kV or Expo_kA
     * configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - DifferentialMotionMagicVoltage Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicVoltage const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using an
     * exponential motion profile, and PID to a differential position
     * setpoint.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the Cruise Velocity (optional) and the
     * mechanism kV and kA, specified via the Motion Magic® configuration
     * values.  Note that unlike the slot gains, the Expo_kV and Expo_kA
     * configs are always in output units of Volts.
     * 
     * Setting Cruise Velocity to 0 will allow the profile to run to the
     * max possible velocity based on Expo_kV.  This control mode does not
     * use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is duty cycle
     * based, so relevant closed-loop gains will use fractional duty cycle
     * for the numerator:  +1.0 represents full forward output.
     * 
     * - DifferentialMotionMagicExpoDutyCycle Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicExpoDutyCycle const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using an
     * exponential motion profile, and PID to a differential position
     * setpoint.
     * 
     * \details Motion Magic® Expo produces a motion profile in real-time
     * while attempting to honor the Cruise Velocity (optional) and the
     * mechanism kV and kA, specified via the Motion Magic® configuration
     * values.  Note that unlike the slot gains, the Expo_kV and Expo_kA
     * configs are always in output units of Volts.
     * 
     * Setting Cruise Velocity to 0 will allow the profile to run to the
     * max possible velocity based on Expo_kV.  This control mode does not
     * use the Acceleration or Jerk configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - DifferentialMotionMagicExpoVoltage Parameters: 
     *   - AveragePosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicExpoVoltage const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final velocity using a
     * motion profile, and PID to a differential position setpoint.  This
     * allows smooth transitions between velocity set points.
     * 
     * \details Motion Magic® Velocity produces a motion profile in
     * real-time while attempting to honor the specified Acceleration and
     * (optional) Jerk.  This control mode does not use the
     * CruiseVelocity, Expo_kV, or Expo_kA configs.
     * 
     * Acceleration and jerk are specified in the Motion Magic® persistent
     * configuration values.  If Jerk is set to zero, Motion Magic® will
     * produce a trapezoidal acceleration profile.
     * 
     * Target velocity can also be changed on-the-fly and Motion Magic®
     * will do its best to adjust the profile.  This control mode is duty
     * cycle based, so relevant closed-loop gains will use fractional duty
     * cycle for the numerator:  +1.0 represents full forward output.
     * 
     * - DifferentialMotionMagicVelocityDutyCycle Parameters: 
     *   - AverageVelocity: Average velocity to drive toward in rotations per
     *                      second.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicVelocityDutyCycle const &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final velocity using a
     * motion profile, and PID to a differential position setpoint.  This
     * allows smooth transitions between velocity set points.
     * 
     * \details Motion Magic® Velocity produces a motion profile in
     * real-time while attempting to honor the specified Acceleration and
     * (optional) Jerk.  This control mode does not use the
     * CruiseVelocity, Expo_kV, or Expo_kA configs.
     * 
     * Acceleration and jerk are specified in the Motion Magic® persistent
     * configuration values.  If Jerk is set to zero, Motion Magic® will
     * produce a trapezoidal acceleration profile.
     * 
     * Target velocity can also be changed on-the-fly and Motion Magic®
     * will do its best to adjust the profile.  This control mode is
     * voltage-based, so relevant closed-loop gains will use Volts for the
     * numerator.
     * 
     * - DifferentialMotionMagicVelocityVoltage Parameters: 
     *   - AverageVelocity: Average velocity to drive toward in rotations per
     *                      second.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro),
     *                which increases peak power by ~15% on supported devices (see
     *                hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *                commutation.
     *                
     *                FOC improves motor performance by leveraging torque (current)
     *                control.  However, this may be inconvenient for applications
     *                that require specifying duty cycle or voltage. 
     *                CTR-Electronics has developed a hybrid method that combines
     *                the performances gains of FOC while still allowing
     *                applications to provide duty cycle or voltage demand.  This
     *                not to be confused with simple sinusoidal control or phase
     *                voltage control which lacks the performance gains.
     *   - AverageSlot: Select which gains are applied to the average controller by
     *                  selecting the slot.  Use the configuration api to set the
     *                  gain values for the selected slot before enabling this
     *                  feature. Slot must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                       controller by selecting the slot.  Use the
     *                       configuration api to set the gain values for the
     *                       selected slot before enabling this feature. Slot must
     *                       be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when
     *                              output is zero (or within deadband).  Set to
     *                              false to use the NeutralMode configuration
     *                              setting (default). This flag exists to provide
     *                              the fundamental behavior of this control when
     *                              output is zero, which is to provide 0V to the
     *                              motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                         users to use other limit switch sensors connected to
     *                         robot controller.  This also allows use of active
     *                         sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and
     *                           the LimitForwardMotion and LimitReverseMotion
     *                           parameters, instead allowing motion.
     *                           
     *                           This can be useful on mechanisms such as an
     *                           intake/feeder, where a limit switch stops motion
     *                           while intaking but should be ignored when feeding
     *                           to a shooter.
     *                           
     *                           The hardware limit faults and Forward/ReverseLimit
     *                           signals will still report the values of the limit
     *                           switches regardless of this parameter.
     *   - IgnoreSoftwareLimits: Set to true to ignore software limits, instead
     *                           allowing motion.
     *                           
     *                           This can be useful when calibrating the zero point
     *                           of a mechanism such as an elevator.
     *                           
     *                           The software limit faults will still report the
     *                           values of the software limits regardless of this
     *                           parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialMotionMagicVelocityVoltage const &request) = 0;
    
    /**
     * \brief Follow the motor output of another Talon.
     * 
     * \details The follower will atomically change its output type when
     * it receives the leader's latest output status signal (DutyCycle,
     * MotorVoltage, TorqueCurrent). If Talon is in torque control, the
     * torque is copied - which will increase the total torque applied. If
     * Talon is in duty cycle output control, the duty cycle is matched.
     * If Talon is in voltage output control, the motor voltage is
     * matched. Motor direction either matches the leader's configured
     * direction or opposes it based on the MotorAlignment.
     * 
     * The leader must ensure the status signal corresponding to its
     * control output type (DutyCycle, MotorVoltage, TorqueCurrent) is
     * enabled. The update rate of the status signal determines the update
     * rate of the follower's output and should be no slower than 20 Hz.
     * 
     * - Follower Parameters: 
     *   - LeaderID: Device ID of the leader to follow.
     *   - MotorAlignment: Set to Aligned for motor invert to match the leader's
     *                     configured Invert - which is typical when leader and
     *                     follower are mechanically linked and spin in the same
     *                     direction.  Set to Opposed for motor invert to oppose the
     *                     leader's configured Invert - this is typical where the
     *                     leader and follower mechanically spin in opposite
     *                     directions.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::Follower const &request) = 0;
    
    /**
     * \brief Follow the motor output of another Talon while ignoring the
     * leader's invert setting.
     * 
     * \details The follower will atomically change its output type when
     * it receives the leader's latest output status signal (DutyCycle,
     * MotorVoltage, TorqueCurrent). If Talon is in torque control, the
     * torque is copied - which will increase the total torque applied. If
     * Talon is in duty cycle output control, the duty cycle is matched.
     * If Talon is in voltage output control, the motor voltage is
     * matched. Motor direction is strictly determined by the configured
     * invert and not the leader. If you want motor direction to match or
     * oppose the leader, use Follower instead.
     * 
     * The leader must ensure the status signal corresponding to its
     * control output type (DutyCycle, MotorVoltage, TorqueCurrent) is
     * enabled. The update rate of the status signal determines the update
     * rate of the follower's output and should be no slower than 20 Hz.
     * 
     * - StrictFollower Parameters: 
     *   - LeaderID: Device ID of the leader to follow.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::StrictFollower const &request) = 0;
    
    /**
     * \brief Follow the differential motor output of another Talon.
     * 
     * \details If Talon is in torque control, the differential torque is
     * copied - which will increase the total torque applied. If Talon is
     * in duty cycle output control, the differential duty cycle is
     * matched. If Talon is in voltage output control, the differential
     * motor voltage is matched. Motor direction either matches leader's
     * configured direction or opposes it based on the MotorAlignment.
     * 
     * The leader must enable its DifferentialOutput status signal. The
     * update rate of the status signal determines the update rate of the
     * follower's output and should be no slower than 20 Hz.
     * 
     * - DifferentialFollower Parameters: 
     *   - LeaderID: Device ID of the differential leader to follow.
     *   - MotorAlignment: Set to Aligned for motor invert to match the leader's
     *                     configured Invert - which is typical when leader and
     *                     follower are mechanically linked and spin in the same
     *                     direction.  Set to Opposed for motor invert to oppose the
     *                     leader's configured Invert - this is typical where the
     *                     leader and follower mechanically spin in opposite
     *                     directions.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialFollower const &request) = 0;
    
    /**
     * \brief Follow the differential motor output of another Talon while
     * ignoring the leader's invert setting.
     * 
     * \details If Talon is in torque control, the differential torque is
     * copied - which will increase the total torque applied. If Talon is
     * in duty cycle output control, the differential duty cycle is
     * matched. If Talon is in voltage output control, the differential
     * motor voltage is matched. Motor direction is strictly determined by
     * the configured invert and not the leader. If you want motor
     * direction to match or oppose the leader, use DifferentialFollower
     * instead.
     * 
     * The leader must enable its DifferentialOutput status signal. The
     * update rate of the status signal determines the update rate of the
     * follower's output and should be no slower than 20 Hz.
     * 
     * - DifferentialStrictFollower Parameters: 
     *   - LeaderID: Device ID of the differential leader to follow.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::DifferentialStrictFollower const &request) = 0;
    
    /**
     * \brief Applies full neutral-brake by shorting motor leads together.
     * 
     * - StaticBrake Parameters: 
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::StaticBrake const &request) = 0;
    
    /**
     * \brief Request neutral output of actuator. The applied brake type
     * is determined by the NeutralMode configuration.
     * 
     * - NeutralOut Parameters: 
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::NeutralOut const &request) = 0;
    
    /**
     * \brief Request coast neutral output of actuator.  The bridge is
     * disabled and the rotor is allowed to coast.
     * 
     * - CoastOut Parameters: 
     *   - UseTimesync: Set to true to delay applying this control request until a
     *                  timesync boundary (requires Phoenix Pro and CANivore). This
     *                  eliminates the impact of nondeterministic network delays in
     *                  exchange for a larger but deterministic control latency.
     *                  
     *                  This requires setting the ControlTimesyncFreqHz config in
     *                  MotorOutputConfigs. Additionally, when this is enabled, the
     *                  UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::CoastOut const &request) = 0;
    
    /**
     * \brief Differential control with duty cycle average target and
     * position difference target.
     * 
     * - Diff_DutyCycleOut_Position Parameters: 
     *   - AverageRequest: Average DutyCycleOut request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_DutyCycleOut_Position const &request) = 0;
    
    /**
     * \brief Differential control with position average target and
     * position difference target using duty cycle control.
     * 
     * - Diff_PositionDutyCycle_Position Parameters: 
     *   - AverageRequest: Average PositionDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionDutyCycle_Position const &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and
     * position difference target using duty cycle control.
     * 
     * - Diff_VelocityDutyCycle_Position Parameters: 
     *   - AverageRequest: Average VelocityDutyCYcle request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityDutyCycle_Position const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * position difference target using duty cycle control.
     * 
     * - Diff_MotionMagicDutyCycle_Position Parameters: 
     *   - AverageRequest: Average MotionMagicDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicDutyCycle_Position const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and position difference target using duty cycle control.
     * 
     * - Diff_MotionMagicExpoDutyCycle_Position Parameters: 
     *   - AverageRequest: Average MotionMagicExpoDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoDutyCycle_Position const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and position difference target using duty cycle control.
     * 
     * - Diff_MotionMagicVelocityDutyCycle_Position Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityDutyCycle_Position const &request) = 0;
    
    /**
     * \brief Differential control with duty cycle average target and
     * velocity difference target.
     * 
     * - Diff_DutyCycleOut_Velocity Parameters: 
     *   - AverageRequest: Average DutyCycleOut request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_DutyCycleOut_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with position average target and
     * velocity difference target using duty cycle control.
     * 
     * - Diff_PositionDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average PositionDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionDutyCycle_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and
     * velocity difference target using duty cycle control.
     * 
     * - Diff_VelocityDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average VelocityDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityDutyCycle_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * velocity difference target using duty cycle control.
     * 
     * - Diff_MotionMagicDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicDutyCycle_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and velocity difference target using duty cycle control.
     * 
     * - Diff_MotionMagicExpoDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicExpoDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoDutyCycle_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and velocity difference target using duty cycle control.
     * 
     * - Diff_MotionMagicVelocityDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityDutyCycle_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with duty cycle average target and duty
     * cycle difference target.
     * 
     * - Diff_DutyCycleOut_Open Parameters: 
     *   - AverageRequest: Average DutyCycleOut request of the mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_DutyCycleOut_Open const &request) = 0;
    
    /**
     * \brief Differential control with position average target and duty
     * cycle difference target.
     * 
     * - Diff_PositionDutyCycle_Open Parameters: 
     *   - AverageRequest: Average PositionDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionDutyCycle_Open const &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and duty
     * cycle difference target.
     * 
     * - Diff_VelocityDutyCycle_Open Parameters: 
     *   - AverageRequest: Average VelocityDutyCYcle request of the mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityDutyCycle_Open const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * duty cycle difference target.
     * 
     * - Diff_MotionMagicDutyCycle_Open Parameters: 
     *   - AverageRequest: Average MotionMagicDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicDutyCycle_Open const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and duty cycle difference target.
     * 
     * - Diff_MotionMagicExpoDutyCycle_Open Parameters: 
     *   - AverageRequest: Average MotionMagicExpoDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoDutyCycle_Open const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and duty cycle difference target.
     * 
     * - Diff_MotionMagicVelocityDutyCycle_Open Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityDutyCycle request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential DutyCycleOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityDutyCycle_Open const &request) = 0;
    
    /**
     * \brief Differential control with voltage average target and
     * position difference target.
     * 
     * - Diff_VoltageOut_Position Parameters: 
     *   - AverageRequest: Average VoltageOut request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VoltageOut_Position const &request) = 0;
    
    /**
     * \brief Differential control with position average target and
     * position difference target using voltage control.
     * 
     * - Diff_PositionVoltage_Position Parameters: 
     *   - AverageRequest: Average PositionVoltage request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionVoltage_Position const &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and
     * position difference target using voltage control.
     * 
     * - Diff_VelocityVoltage_Position Parameters: 
     *   - AverageRequest: Average VelocityVoltage request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityVoltage_Position const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * position difference target using voltage control.
     * 
     * - Diff_MotionMagicVoltage_Position Parameters: 
     *   - AverageRequest: Average MotionMagicVoltage request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVoltage_Position const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and position difference target using voltage control.
     * 
     * - Diff_MotionMagicExpoVoltage_Position Parameters: 
     *   - AverageRequest: Average MotionMagicExpoVoltage request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoVoltage_Position const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and position difference target using voltage control.
     * 
     * - Diff_MotionMagicVelocityVoltage_Position Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityVoltage request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityVoltage_Position const &request) = 0;
    
    /**
     * \brief Differential control with voltage average target and
     * velocity difference target.
     * 
     * - Diff_VoltageOut_Velocity Parameters: 
     *   - AverageRequest: Average VoltageOut request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VoltageOut_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with position average target and
     * velocity difference target using voltage control.
     * 
     * - Diff_PositionVoltage_Velocity Parameters: 
     *   - AverageRequest: Average PositionVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionVoltage_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and
     * velocity difference target using voltage control.
     * 
     * - Diff_VelocityVoltage_Velocity Parameters: 
     *   - AverageRequest: Average VelocityVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityVoltage_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * velocity difference target using voltage control.
     * 
     * - Diff_MotionMagicVoltage_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVoltage_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and velocity difference target using voltage control.
     * 
     * - Diff_MotionMagicExpoVoltage_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicExpoVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoVoltage_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and velocity difference target using voltage control.
     * 
     * - Diff_MotionMagicVelocityVoltage_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityVoltage request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the
     *                          mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityVoltage_Velocity const &request) = 0;
    
    /**
     * \brief Differential control with voltage average target and voltage
     * difference target.
     * 
     * - Diff_VoltageOut_Open Parameters: 
     *   - AverageRequest: Average VoltageOut request of the mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VoltageOut_Open const &request) = 0;
    
    /**
     * \brief Differential control with position average target and
     * voltage difference target.
     * 
     * - Diff_PositionVoltage_Open Parameters: 
     *   - AverageRequest: Average PositionVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_PositionVoltage_Open const &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and
     * voltage difference target.
     * 
     * - Diff_VelocityVoltage_Open Parameters: 
     *   - AverageRequest: Average VelocityVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_VelocityVoltage_Open const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * voltage difference target.
     * 
     * - Diff_MotionMagicVoltage_Open Parameters: 
     *   - AverageRequest: Average MotionMagicVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVoltage_Open const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Expo average target
     * and voltage difference target.
     * 
     * - Diff_MotionMagicExpoVoltage_Open Parameters: 
     *   - AverageRequest: Average MotionMagicExpoVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicExpoVoltage_Open const &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® Velocity average
     * target and voltage difference target.
     * 
     * - Diff_MotionMagicVelocityVoltage_Open Parameters: 
     *   - AverageRequest: Average MotionMagicVelocityVoltage request of the
     *                     mechanism.
     *   - DifferentialRequest: Differential VoltageOut request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::compound::Diff_MotionMagicVelocityVoltage_Open const &request) = 0;

    /**
     * \brief Apply a generic empty control used to do nothing.
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::EmptyControl const &request) = 0;

    /**
     * \brief Control device with generic control request object. User must make
     *        sure the specified object is castable to a valid control request,
     *        otherwise this function will fail at run-time and return the NotSupported
     *        StatusCode
     *
     * \param request Control object to request of the device
     * \returns Status code of the request
     */
    virtual ctre::phoenix::StatusCode SetControl(controls::ControlRequest const &request) = 0;
    
};

}
}
}
}

