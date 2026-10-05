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
#include "ctre/phoenix6/controls/TorqueCurrentFOC.hpp"
#include "ctre/phoenix6/controls/PositionTorqueCurrentFOC.hpp"
#include "ctre/phoenix6/controls/VelocityTorqueCurrentFOC.hpp"
#include "ctre/phoenix6/controls/MotionMagicTorqueCurrentFOC.hpp"
#include "ctre/phoenix6/controls/MotionMagicVelocityTorqueCurrentFOC.hpp"
#include "ctre/phoenix6/controls/MotionMagicExpoTorqueCurrentFOC.hpp"
#include "ctre/phoenix6/controls/DynamicMotionMagicTorqueCurrentFOC.hpp"
#include "ctre/phoenix6/controls/compound/Diff_TorqueCurrentFOC_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionTorqueCurrentFOC_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityTorqueCurrentFOC_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicTorqueCurrentFOC_Position.hpp"
#include "ctre/phoenix6/controls/compound/Diff_TorqueCurrentFOC_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_PositionTorqueCurrentFOC_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_VelocityTorqueCurrentFOC_Velocity.hpp"
#include "ctre/phoenix6/controls/compound/Diff_MotionMagicTorqueCurrentFOC_Velocity.hpp"


namespace ctre {
namespace phoenix6 {
namespace hardware {
namespace traits {

/**
 * Requires Phoenix Pro; Contains all FOC-exclusive control functions available
 * for devices that support FOC.
 */
class SupportsFOC
{
public:
    virtual ~SupportsFOC() = default;
    
    
    /**
     * \brief Request a specified motor current (field oriented control).
     * 
     * \details This control request will drive the motor to the requested
     * motor (stator) current value.  This leverages field oriented
     * control (FOC), which means greater peak power than what is
     * documented.  This scales to torque based on Motor's kT constant.
     * 
     * - TorqueCurrentFOC Parameters: 
     *   - Output: Amount of motor current in Amperes
     *   - MaxAbsDutyCycle: The maximum absolute motor output that can be applied,
     *                   which effectively limits the velocity. For example, 0.50
     *                   means no more than 50% output in either direction.  This is
     *                   useful for preventing the motor from spinning to its
     *                   terminal velocity when there is no external torque applied
     *                   unto the rotor.  Note this is absolute maximum, so the
     *                   value should be between zero and one.
     *   - Deadband: Deadband in Amperes.  If torque request is within deadband, the
     *            bridge output is neutral. If deadband is set to zero then there is
     *            effectively no deadband. Note if deadband is zero, a free spinning
     *            motor will spin for quite a while as the firmware attempts to hold
     *            the motor's bemf. If user expects motor to cease spinning quickly
     *            with a demand of zero, we recommend a deadband of one Ampere. This
     *            value will be converted to an integral value of amps.
     *   - OverrideCoastDurNeutral: Set to true to coast the rotor when output is zero
     *                           (or within deadband).  Set to false to use the
     *                           NeutralMode configuration setting (default). This
     *                           flag exists to provide the fundamental behavior of
     *                           this control when output is zero, which is to
     *                           provide 0A (zero torque).
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
    virtual ctre::phoenix::StatusCode SetControl(const controls::TorqueCurrentFOC &request) = 0;
    
    /**
     * \brief Request PID to target position with torque current
     * feedforward.
     * 
     * \details This control mode will set the motor's position setpoint
     * to the position specified by the user. In addition, it will apply
     * an additional torque current as an arbitrary feedforward value.
     * 
     * - PositionTorqueCurrentFOC Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - Velocity: Velocity to drive toward in rotations per second. This is
     *            typically used for motion profiles generated by the robot program.
     *   - FeedForward: Feedforward to apply in torque current in Amperes.  User can
     *               use motor's kT to scale Newton-meter to Amperes.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideCoastDurNeutral: Set to true to coast the rotor when output is zero
     *                           (or within deadband).  Set to false to use the
     *                           NeutralMode configuration setting (default). This
     *                           flag exists to provide the fundamental behavior of
     *                           this control when output is zero, which is to
     *                           provide 0A (zero torque).
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
    virtual ctre::phoenix::StatusCode SetControl(const controls::PositionTorqueCurrentFOC &request) = 0;
    
    /**
     * \brief Request PID to target velocity with torque current
     * feedforward.
     * 
     * \details This control mode will set the motor's velocity setpoint
     * to the velocity specified by the user. In addition, it will apply
     * an additional torque current as an arbitrary feedforward value.
     * 
     * - VelocityTorqueCurrentFOC Parameters: 
     *   - Velocity: Velocity to drive toward in rotations per second.
     *   - Acceleration: Acceleration to drive toward in rotations per second squared.
     *                This is typically used for motion profiles generated by the
     *                robot program.
     *   - FeedForward: Feedforward to apply in torque current in Amperes.  User can
     *               use motor's kT to scale Newton-meter to Amperes.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideCoastDurNeutral: Set to true to coast the rotor when output is zero
     *                           (or within deadband).  Set to false to use the
     *                           NeutralMode configuration setting (default). This
     *                           flag exists to provide the fundamental behavior of
     *                           this control when output is zero, which is to
     *                           provide 0A (zero torque).
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
    virtual ctre::phoenix::StatusCode SetControl(const controls::VelocityTorqueCurrentFOC &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  Users can optionally provide a torque current
     * feedforward.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the Cruise Velocity, Acceleration, and
     * (optional) Jerk specified via the Motion Magic® configuration
     * values.  This control mode does not use the Expo_kV or Expo_kA
     * configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile.  This control mode is based on
     * torque current, so relevant closed-loop gains will use Amperes for
     * the numerator.
     * 
     * - MotionMagicTorqueCurrentFOC Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - FeedForward: Feedforward to apply in torque current in Amperes.  User can
     *               use motor's kT to scale Newton-meter to Amperes.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideCoastDurNeutral: Set to true to coast the rotor when output is zero
     *                           (or within deadband).  Set to false to use the
     *                           NeutralMode configuration setting (default). This
     *                           flag exists to provide the fundamental behavior of
     *                           this control when output is zero, which is to
     *                           provide 0A (zero torque).
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
    virtual ctre::phoenix::StatusCode SetControl(const controls::MotionMagicTorqueCurrentFOC &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final velocity using a
     * motion profile.  This allows smooth transitions between velocity
     * set points.  Users can optionally provide a torque feedforward.
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
     * will do its best to adjust the profile.  This control mode is based
     * on torque current, so relevant closed-loop gains will use Amperes
     * for the numerator.
     * 
     * - MotionMagicVelocityTorqueCurrentFOC Parameters: 
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
     *   - FeedForward: Feedforward to apply in torque current in Amperes.  User can
     *               use motor's kT to scale Newton-meter to Amperes.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideCoastDurNeutral: Set to true to coast the rotor when output is zero
     *                           (or within deadband).  Set to false to use the
     *                           NeutralMode configuration setting (default). This
     *                           flag exists to provide the fundamental behavior of
     *                           this control when output is zero, which is to
     *                           provide 0A (zero torque).
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
    virtual ctre::phoenix::StatusCode SetControl(const controls::MotionMagicVelocityTorqueCurrentFOC &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using an
     * exponential motion profile.  Users can optionally provide a torque
     * current feedforward.
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
     * its best to adjust the profile.  This control mode is based on
     * torque current, so relevant closed-loop gains will use Amperes for
     * the numerator.
     * 
     * - MotionMagicExpoTorqueCurrentFOC Parameters: 
     *   - Position: Position to drive toward in rotations.
     *   - FeedForward: Feedforward to apply in torque current in Amperes.  User can
     *               use motor's kT to scale Newton-meter to Amperes.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideCoastDurNeutral: Set to true to coast the rotor when output is zero
     *                           (or within deadband).  Set to false to use the
     *                           NeutralMode configuration setting (default). This
     *                           flag exists to provide the fundamental behavior of
     *                           this control when output is zero, which is to
     *                           provide 0A (zero torque).
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
    virtual ctre::phoenix::StatusCode SetControl(const controls::MotionMagicExpoTorqueCurrentFOC &request) = 0;
    
    /**
     * \brief Requests Motion Magic® to target a final position using a
     * motion profile.  This dynamic request allows runtime changes to
     * Cruise Velocity, Acceleration, and Jerk.  Users can optionally
     * provide a torque current feedforward.  This control requires use of
     * a CANivore.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     * attempting to honor the specified Cruise Velocity, Acceleration,
     * and (optional) Jerk.  This control mode does not use the Expo_kV or
     * Expo_kA configs.
     * 
     * Target position can be changed on-the-fly and Motion Magic® will do
     * its best to adjust the profile. This control mode is based on
     * torque current, so relevant closed-loop gains will use Amperes for
     * the numerator.
     * 
     * - DynamicMotionMagicTorqueCurrentFOC Parameters: 
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
     *   - FeedForward: Feedforward to apply in torque current in Amperes.  User can
     *               use motor's kT to scale Newton-meter to Amperes.
     *   - Slot: Select which gains are applied by selecting the slot.  Use the
     *        configuration api to set the gain values for the selected slot before
     *        enabling this feature. Slot must be within [0,2].
     *   - OverrideCoastDurNeutral: Set to true to coast the rotor when output is zero
     *                           (or within deadband).  Set to false to use the
     *                           NeutralMode configuration setting (default). This
     *                           flag exists to provide the fundamental behavior of
     *                           this control when output is zero, which is to
     *                           provide 0A (zero torque).
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
    virtual ctre::phoenix::StatusCode SetControl(const controls::DynamicMotionMagicTorqueCurrentFOC &request) = 0;
    
    /**
     * \brief Differential control with torque current average target and
     * position difference target.
     * 
     * - Diff_TorqueCurrentFOC_Position Parameters: 
     *   - AverageRequest: Average TorqueCurrentFOC request of the mechanism.
     *   - DifferentialRequest: Differential PositionTorqueCurrentFOC request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_TorqueCurrentFOC_Position &request) = 0;
    
    /**
     * \brief Differential control with position average target and
     * position difference target using torque current control.
     * 
     * - Diff_PositionTorqueCurrentFOC_Position Parameters: 
     *   - AverageRequest: Average PositionTorqueCurrentFOC request of the mechanism.
     *   - DifferentialRequest: Differential PositionTorqueCurrentFOC request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_PositionTorqueCurrentFOC_Position &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and
     * position difference target using torque current control.
     * 
     * - Diff_VelocityTorqueCurrentFOC_Position Parameters: 
     *   - AverageRequest: Average VelocityTorqueCurrentFOC request of the mechanism.
     *   - DifferentialRequest: Differential PositionTorqueCurrentFOC request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_VelocityTorqueCurrentFOC_Position &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * position difference target using torque current control.
     * 
     * - Diff_MotionMagicTorqueCurrentFOC_Position Parameters: 
     *   - AverageRequest: Average MotionMagicTorqueCurrentFOC request of the
     *                  mechanism.
     *   - DifferentialRequest: Differential PositionTorqueCurrentFOC request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_MotionMagicTorqueCurrentFOC_Position &request) = 0;
    
    /**
     * \brief Differential control with torque current average target and
     * velocity difference target.
     * 
     * - Diff_TorqueCurrentFOC_Velocity Parameters: 
     *   - AverageRequest: Average TorqueCurrentFOC request of the mechanism.
     *   - DifferentialRequest: Differential VelocityTorqueCurrentFOC request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_TorqueCurrentFOC_Velocity &request) = 0;
    
    /**
     * \brief Differential control with position average target and
     * velocity difference target using torque current control.
     * 
     * - Diff_PositionTorqueCurrentFOC_Velocity Parameters: 
     *   - AverageRequest: Average PositionTorqueCurrentFOC request of the mechanism.
     *   - DifferentialRequest: Differential VelocityTorqueCurrentFOC request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_PositionTorqueCurrentFOC_Velocity &request) = 0;
    
    /**
     * \brief Differential control with velocity average target and
     * velocity difference target using torque current control.
     * 
     * - Diff_VelocityTorqueCurrentFOC_Velocity Parameters: 
     *   - AverageRequest: Average VelocityTorqueCurrentFOC request of the mechanism.
     *   - DifferentialRequest: Differential VelocityTorqueCurrentFOC request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_VelocityTorqueCurrentFOC_Velocity &request) = 0;
    
    /**
     * \brief Differential control with Motion Magic® average target and
     * velocity difference target using torque current control.
     * 
     * - Diff_MotionMagicTorqueCurrentFOC_Velocity Parameters: 
     *   - AverageRequest: Average MotionMagicTorqueCurrentFOC request of the
     *                  mechanism.
     *   - DifferentialRequest: Differential VelocityTorqueCurrentFOC request of the
     *                       mechanism.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::compound::Diff_MotionMagicTorqueCurrentFOC_Velocity &request) = 0;

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

