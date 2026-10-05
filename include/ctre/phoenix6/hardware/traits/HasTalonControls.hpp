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
#include "ctre/phoenix6/controls/DifferentialDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialPositionDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialPositionVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialVelocityDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialVelocityVoltage.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicDutyCycle.hpp"
#include "ctre/phoenix6/controls/DifferentialMotionMagicVoltage.hpp"
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
#include "ctre/phoenix6/controls/compound/Diff_DutyCycleOut_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicDutyCycle_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VoltageOut_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVoltage_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VoltageOut_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityVoltage_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicVoltage_Velocity.hpp"


namespace ctre {
namespace phoenix6 {
namespace hardware {
namespace traits {

/**
 * Contains all control functions available for devices that support Talon
 * controls.
 */
class HasTalonControls
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
     *   - Output: Proportion of supply voltage to apply in fractional units between -1
     *          and +1
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DutyCycleOut &request) = 0;
    
    /**
     * \brief Request a specified voltage.
     * 
     * \details This control mode will attempt to apply the specified
     * voltage to the motor. If the supply voltage is below the requested
     * voltage, the motor controller will output the supply voltage.
     * 
     * - VoltageOut Parameters: 
     *   - Output: Voltage to attempt to drive at
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::VoltageOut &request) = 0;
    
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
     *            typically used for motion profiles generated by the robot program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::PositionDutyCycle &request) = 0;
    
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
     *            typically used for motion profiles generated by the robot program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in volts
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::PositionVoltage &request) = 0;
    
    /**
     * \brief Request PID to target velocity with duty cycle feedforward.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. In addition, it will apply
     * an additional voltage as an arbitrary feedforward value.
     * 
     * - VelocityDutyCycle Parameters: 
     *   - Velocity: Velocity to drive toward in rotations per second.
     *   - Acceleration: Acceleration to drive toward in rotations per second squared.
     *                This is typically used for motion profiles generated by the
     *                robot program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::VelocityDutyCycle &request) = 0;
    
    /**
     * \brief Request PID to target velocity with voltage feedforward.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. In addition, it will apply
     * an additional voltage as an arbitrary feedforward value.
     * 
     * - VelocityVoltage Parameters: 
     *   - Velocity: Velocity to drive toward in rotations per second.
     *   - Acceleration: Acceleration to drive toward in rotations per second squared.
     *                This is typically used for motion profiles generated by the
     *                robot program.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in volts
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::VelocityVoltage &request) = 0;
    
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
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::MotionMagicDutyCycle &request) = 0;
    
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
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in volts
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::MotionMagicVoltage &request) = 0;
    
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
     *   - Velocity: Target velocity to drive toward in rotations per second.  This can
     *            be changed on-the fly.
     *   - Acceleration: This is the absolute Acceleration to use generating the
     *                profile.  If this parameter is zero, the Acceleration
     *                persistent configuration parameter is used instead.
     *                Acceleration is in rotations per second squared.  If nonzero,
     *                the signage does not matter as the absolute value is used.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::MotionMagicVelocityDutyCycle &request) = 0;
    
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
     *   - Velocity: Target velocity to drive toward in rotations per second.  This can
     *            be changed on-the fly.
     *   - Acceleration: This is the absolute Acceleration to use generating the
     *                profile.  If this parameter is zero, the Acceleration
     *                persistent configuration parameter is used instead.
     *                Acceleration is in rotations per second squared.  If nonzero,
     *                the signage does not matter as the absolute value is used.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in volts
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::MotionMagicVelocityVoltage &request) = 0;
    
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
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::MotionMagicExpoDutyCycle &request) = 0;
    
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
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in volts
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::MotionMagicExpoVoltage &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  This dynamic request allows runtime changes to
     * Cruise Velocity, Acceleration, and Jerk.  Users can optionally
     * provide a duty cycle feedforward.  This control requires use of a
     * CANivore.
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
     *   - Velocity: Cruise velocity for profiling.  The signage does not matter as the
     *            device will use the absolute value for profile generation.
     *   - Acceleration: Acceleration for profiling.  The signage does not matter as
     *                the device will use the absolute value for profile generation
     *   - Jerk: Jerk for profiling.  The signage does not matter as the device will
     *        use the absolute value for profile generation.
     *        
     *        Jerk is optional; if this is set to zero, then Motion Magic® will not
     *        apply a Jerk limit.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in fractional units between -1 and +1.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DynamicMotionMagicDutyCycle &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  This dynamic request allows runtime changes to
     * Cruise Velocity, Acceleration, and Jerk.  Users can optionally
     * provide a voltage feedforward.  This control requires use of a
     * CANivore.
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
     *   - Velocity: Cruise velocity for profiling.  The signage does not matter as the
     *            device will use the absolute value for profile generation.
     *   - Acceleration: Acceleration for profiling.  The signage does not matter as
     *                the device will use the absolute value for profile generation.
     *   - Jerk: Jerk for profiling.  The signage does not matter as the device will
     *        use the absolute value for profile generation.
     *        
     *        Jerk is optional; if this is set to zero, then Motion Magic® will not
     *        apply a Jerk limit.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - FeedForward: Feedforward to apply in volts
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DynamicMotionMagicVoltage &request) = 0;
    
    /**
     * \brief Request a specified motor duty cycle with a differential
     * position closed-loop.
     * 
     * \details This control mode will output a proportion of the supplied
     * voltage which is supplied by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialDutyCycle Parameters: 
     *   - TargetOutput: Proportion of supply voltage to apply in fractional units
     *                between -1 and +1
     *   - DifferentialPosition: Differential position to drive towards in rotations
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                    controller by selecting the slot.  Use the configuration
     *                    api to set the gain values for the selected slot before
     *                    enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DifferentialDutyCycle &request) = 0;
    
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
     *   - TargetOutput: Voltage to attempt to drive at
     *   - DifferentialPosition: Differential position to drive towards in rotations
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                    controller by selecting the slot.  Use the configuration
     *                    api to set the gain values for the selected slot before
     *                    enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DifferentialVoltage &request) = 0;
    
    /**
     * \brief Request PID to target position with a differential position
     * setpoint.
     * 
     * \details This control mode will set the motor's position setpoint
     * to the position specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialPositionDutyCycle Parameters: 
     *   - TargetPosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - TargetSlot: Select which gains are applied to the primary controller by
     *              selecting the slot.  Use the configuration api to set the gain
     *              values for the selected slot before enabling this feature. Slot
     *              must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                    controller by selecting the slot.  Use the configuration
     *                    api to set the gain values for the selected slot before
     *                    enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DifferentialPositionDutyCycle &request) = 0;
    
    /**
     * \brief Request PID to target position with a differential position
     * setpoint
     * 
     * \details This control mode will set the motor's position setpoint
     * to the position specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialPositionVoltage Parameters: 
     *   - TargetPosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - TargetSlot: Select which gains are applied to the primary controller by
     *              selecting the slot.  Use the configuration api to set the gain
     *              values for the selected slot before enabling this feature. Slot
     *              must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                    controller by selecting the slot.  Use the configuration
     *                    api to set the gain values for the selected slot before
     *                    enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DifferentialPositionVoltage &request) = 0;
    
    /**
     * \brief Request PID to target velocity with a differential position
     * setpoint.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialVelocityDutyCycle Parameters: 
     *   - TargetVelocity: Average velocity to drive toward in rotations per second.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - TargetSlot: Select which gains are applied to the primary controller by
     *              selecting the slot.  Use the configuration api to set the gain
     *              values for the selected slot before enabling this feature. Slot
     *              must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                    controller by selecting the slot.  Use the configuration
     *                    api to set the gain values for the selected slot before
     *                    enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DifferentialVelocityDutyCycle &request) = 0;
    
    /**
     * \brief Request PID to target velocity with a differential position
     * setpoint.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. It will also set the motor's
     * differential position setpoint to the specified position.
     * 
     * - DifferentialVelocityVoltage Parameters: 
     *   - TargetVelocity: Average velocity to drive toward in rotations per second.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - TargetSlot: Select which gains are applied to the primary controller by
     *              selecting the slot.  Use the configuration api to set the gain
     *              values for the selected slot before enabling this feature. Slot
     *              must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                    controller by selecting the slot.  Use the configuration
     *                    api to set the gain values for the selected slot before
     *                    enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DifferentialVelocityVoltage &request) = 0;
    
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
     *   - TargetPosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - TargetSlot: Select which gains are applied to the primary controller by
     *              selecting the slot.  Use the configuration api to set the gain
     *              values for the selected slot before enabling this feature. Slot
     *              must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                    controller by selecting the slot.  Use the configuration
     *                    api to set the gain values for the selected slot before
     *                    enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DifferentialMotionMagicDutyCycle &request) = 0;
    
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
     *   - TargetPosition: Average position to drive toward in rotations.
     *   - DifferentialPosition: Differential position to drive toward in rotations.
     *   - EnableFOC: Set to true to use FOC commutation (requires Phoenix Pro), which
     *             increases peak power by ~15% on supported devices (see
     *             hardware#traits#SupportsFOC). Set to false to use trapezoidal
     *             commutation.
     *             
     *             FOC improves motor performance by leveraging torque (current)
     *             control.  However, this may be inconvenient for applications that
     *             require specifying duty cycle or voltage.  CTR-Electronics has
     *             developed a hybrid method that combines the performances gains of
     *             FOC while still allowing applications to provide duty cycle or
     *             voltage demand.  This not to be confused with simple sinusoidal
     *             control or phase voltage control which lacks the performance
     *             gains.
     *   - TargetSlot: Select which gains are applied to the primary controller by
     *              selecting the slot.  Use the configuration api to set the gain
     *              values for the selected slot before enabling this feature. Slot
     *              must be within [0,2].
     *   - DifferentialSlot: Select which gains are applied to the differential
     *                    controller by selecting the slot.  Use the configuration
     *                    api to set the gain values for the selected slot before
     *                    enabling this feature. Slot must be within [0,2].
     *   - OverrideBrakeDurNeutral: Set to true to static-brake the rotor when output
     *                           is zero (or within deadband).  Set to false to use
     *                           the NeutralMode configuration setting (default).
     *                           This flag exists to provide the fundamental
     *                           behavior of this control when output is zero, which
     *                           is to provide 0V to the motor.
     *   - LimitForwardMotion: Set to true to force forward limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - LimitReverseMotion: Set to true to force reverse limiting.  This allows
     *                      users to use other limit switch sensors connected to
     *                      robot controller.  This also allows use of active
     *                      sensors that require external power.
     *   - IgnoreHardwareLimits: Set to true to ignore hardware limit switches and the
     *                        LimitForwardMotion and LimitReverseMotion parameters,
     *                        instead allowing motion.
     *                        
     *                        This can be useful on mechanisms such as an
     *                        intake/feeder, where a limit switch stops motion while
     *                        intaking but should be ignored when feeding to a
     *                        shooter.
     *                        
     *                        The hardware limit faults and Forward/ReverseLimit
     *                        signals will still report the values of the limit
     *                        switches regardless of this parameter.
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DifferentialMotionMagicVoltage &request) = 0;
    
    /**
     * \brief Follow the motor output of another Talon.
     * 
     * \details If Talon is in torque control, the torque is copied -
     * which will increase the total torque applied. If Talon is in
     * percent supply output control, the duty cycle is matched.  Motor
     * direction either matches master's configured direction or opposes
     * it based on OpposeMasterDirection.
     * 
     * - Follower Parameters: 
     *   - MasterID: Device ID of the master to follow.
     *   - OpposeMasterDirection: Set to false for motor invert to match the master's
     *                         configured Invert - which is typical when master and
     *                         follower are mechanically linked and spin in the same
     *                         direction.  Set to true for motor invert to oppose
     *                         the master's configured Invert - this is typical
     *                         where the the master and follower mechanically spin
     *                         in opposite directions.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::Follower &request) = 0;
    
    /**
     * \brief Follow the motor output of another Talon while ignoring the
     * master's invert setting.
     * 
     * \details If Talon is in torque control, the torque is copied -
     * which will increase the total torque applied. If Talon is in
     * percent supply output control, the duty cycle is matched.  Motor
     * direction is strictly determined by the configured invert and not
     * the master.  If you want motor direction to match or oppose the
     * master, use FollowerRequest instead.
     * 
     * - StrictFollower Parameters: 
     *   - MasterID: Device ID of the master to follow.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::StrictFollower &request) = 0;
    
    /**
     * \brief Follow the differential motor output of another Talon.
     * 
     * \details If Talon is in torque control, the torque is copied -
     * which will increase the total torque applied. If Talon is in
     * percent supply output control, the duty cycle is matched.  Motor
     * direction either matches master's configured direction or opposes
     * it based on OpposeMasterDirection.
     * 
     * - DifferentialFollower Parameters: 
     *   - MasterID: Device ID of the differential master to follow.
     *   - OpposeMasterDirection: Set to false for motor invert to match the master's
     *                         configured Invert - which is typical when master and
     *                         follower are mechanically linked and spin in the same
     *                         direction.  Set to true for motor invert to oppose
     *                         the master's configured Invert - this is typical
     *                         where the the master and follower mechanically spin
     *                         in opposite directions.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DifferentialFollower &request) = 0;
    
    /**
     * \brief Follow the differential motor output of another Talon while
     * ignoring the master's invert setting.
     * 
     * \details If Talon is in torque control, the torque is copied -
     * which will increase the total torque applied. If Talon is in
     * percent supply output control, the duty cycle is matched.  Motor
     * direction is strictly determined by the configured invert and not
     * the master.  If you want motor direction to match or oppose the
     * master, use FollowerRequest instead.
     * 
     * - DifferentialStrictFollower Parameters: 
     *   - MasterID: Device ID of the differential master to follow.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::DifferentialStrictFollower &request) = 0;
    
    /**
     * \brief Applies full neutral-brake by shorting motor leads together.
     * 
     * - StaticBrake Parameters: 
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::StaticBrake &request) = 0;
    
    /**
     * \brief Request neutral output of actuator. The applied brake type
     * is determined by the NeutralMode configuration.
     * 
     * - NeutralOut Parameters: 
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::NeutralOut &request) = 0;
    
    /**
     * \brief Request coast neutral output of actuator.  The bridge is
     * disabled and the rotor is allowed to coast.
     * 
     * - CoastOut Parameters: 
     *   - UseTimesync: Set to true to delay applying this control request until a
     *               timesync boundary (requires Phoenix Pro and CANivore). This
     *               eliminates the impact of nondeterministic network delays in
     *               exchange for a larger but deterministic control latency.
     *               
     *               This requires setting the ControlTimesyncFreqHz config in
     *               MotorOutputConfigs. Additionally, when this is enabled, the
     *               UpdateFreqHz of this request should be set to 0 Hz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::CoastOut &request) = 0;
    
    /**
     * \brief Differential control with duty cycle average target and
     * position difference target.
     * 
     * - Diff_DutyCycleOut_Position Parameters: 
     *   - AverageRequest: Average DutyCycleOut request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_DutyCycleOut_Position &request) = 0;
    
    /**
     * \brief Differential control with position average target and
     * position difference target using dutycycle control.
     * 
     * - Diff_PositionDutyCycle_Position Parameters: 
     *   - AverageRequest: Average PositionDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_PositionDutyCycle_Position &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and
     * position difference target using dutycycle control.
     * 
     * - Diff_VelocityDutyCycle_Position Parameters: 
     *   - AverageRequest: Average VelocityDutyCYcle request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_VelocityDutyCycle_Position &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * position difference target using dutycycle control.
     * 
     * - Diff_MotionMagicDutyCycle_Position Parameters: 
     *   - AverageRequest: Average MotionMagicDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential PositionDutyCycle request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_MotionMagicDutyCycle_Position &request) = 0;
    
    /**
     * \brief Differential control with duty cycle average target and
     * velocity difference target.
     * 
     * - Diff_DutyCycleOut_Velocity Parameters: 
     *   - AverageRequest: Average DutyCycleOut request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_DutyCycleOut_Velocity &request) = 0;
    
    /**
     * \brief Differential control with position average target and
     * velocity difference target using dutycycle control.
     * 
     * - Diff_PositionDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average PositionDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_PositionDutyCycle_Velocity &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and
     * velocity difference target using dutycycle control.
     * 
     * - Diff_VelocityDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average VelocityDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_VelocityDutyCycle_Velocity &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * velocity difference target using dutycycle control.
     * 
     * - Diff_MotionMagicDutyCycle_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicDutyCycle request of the mechanism.
     *   - DifferentialRequest: Differential VelocityDutyCycle request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_MotionMagicDutyCycle_Velocity &request) = 0;
    
    /**
     * \brief Differential control with voltage average target and
     * position difference target.
     * 
     * - Diff_VoltageOut_Position Parameters: 
     *   - AverageRequest: Average VoltageOut request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_VoltageOut_Position &request) = 0;
    
    /**
     * \brief Differential control with position average target and
     * position difference target using voltage control.
     * 
     * - Diff_PositionVoltage_Position Parameters: 
     *   - AverageRequest: Average PositionVoltage request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_PositionVoltage_Position &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and
     * position difference target using voltage control.
     * 
     * - Diff_VelocityVoltage_Position Parameters: 
     *   - AverageRequest: Average VelocityVoltage request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_VelocityVoltage_Position &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * position difference target using voltage control.
     * 
     * - Diff_MotionMagicVoltage_Position Parameters: 
     *   - AverageRequest: Average MotionMagicVoltage request of the mechanism.
     *   - DifferentialRequest: Differential PositionVoltage request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_MotionMagicVoltage_Position &request) = 0;
    
    /**
     * \brief Differential control with voltage average target and
     * velocity difference target.
     * 
     * - Diff_VoltageOut_Velocity Parameters: 
     *   - AverageRequest: Average VoltageOut request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_VoltageOut_Velocity &request) = 0;
    
    /**
     * \brief Differential control with position average target and
     * velocity difference target using voltage control.
     * 
     * - Diff_PositionVoltage_Velocity Parameters: 
     *   - AverageRequest: Average PositionVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_PositionVoltage_Velocity &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and
     * velocity difference target using voltage control.
     * 
     * - Diff_VelocityVoltage_Velocity Parameters: 
     *   - AverageRequest: Average VelocityVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_VelocityVoltage_Velocity &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * velocity difference target using voltage control.
     * 
     * - Diff_MotionMagicVoltage_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicVoltage request of the mechanism.
     *   - DifferentialRequest: Differential VelocityVoltage request of the mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_MotionMagicVoltage_Velocity &request) = 0;

    /**
     * \brief Control device with generic control request object. User must make
     *        sure the specified object is castable to a valid control request,
     *        otherwise this function will fail at run-time and return the NotSupported
     *        StatusCode
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::ControlRequest &request) = 0;
    
};

}
}
}
}

