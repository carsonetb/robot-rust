/*
 * Copyright (c) 2024-2026 REV Robotics
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of REV Robotics nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <string>

#include "rev/SparkBase.h"
#include "rev/config/AbsoluteEncoderConfig.h"
#include "rev/config/AnalogSensorConfig.h"
#include "rev/config/BaseConfig.h"
#include "rev/config/ClosedLoopConfig.h"
#include "rev/config/EncoderConfig.h"
#include "rev/config/LimitSwitchConfig.h"
#include "rev/config/SignalsConfig.h"
#include "rev/config/SoftLimitConfig.h"
#include "rev/config/SparkParameters.h"

namespace rev::spark {

class SparkBaseConfig : public BaseConfig {
public:
    enum IdleMode : uint32_t { kCoast = 0, kBrake = 1 };

    SparkBaseConfig() = default;
    ~SparkBaseConfig() override = default;

    SparkBaseConfig(const SparkBaseConfig&) = default;
    SparkBaseConfig& operator=(const SparkBaseConfig&) = delete;
    SparkBaseConfig(SparkBaseConfig&&) noexcept = delete;
    SparkBaseConfig& operator=(SparkBaseConfig&&) noexcept = delete;

    struct Presets final {
        /** REV Robotics - NEO Brushless Motor V1.1 */
        static SparkBaseConfig& REV_NEO() {
            static SparkBaseConfig config{
                SparkBaseConfig().SmartCurrentLimit(60)};
            return config;
        }

        /** REV Robotics - NEO Brushless Motor 2.0 */
        static SparkBaseConfig& REV_NEO_2() {
            static SparkBaseConfig config{
                SparkBaseConfig().SmartCurrentLimit(60)};
            return config;
        }

        /** REV Robotics - NEO 550 Brushless Motor */
        static SparkBaseConfig& REV_NEO_550() {
            static SparkBaseConfig config{
                SparkBaseConfig().SmartCurrentLimit(15)};
            return config;
        }

        /** REV Robotics - NEO Vortex Brushless Motor */
        static SparkBaseConfig& REV_Vortex() {
            static SparkBaseConfig config{
                SparkBaseConfig().SmartCurrentLimit(80)};
            return config;
        }

        /* CTRE - Minion: Standalone Brushless Motor */
        static SparkBaseConfig& CTRE_Minion() {
            static SparkBaseConfig config{
                SparkBaseConfig().SmartCurrentLimit(30).AdvanceCommutation(
                    120.0)};
            return config;
        }
    };

    /**
     * Applies settings from another SparkBaseConfig to this one,
     * including all of its nested configurations.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The SparkBaseConfig to copy settings from
     * @return The updated SparkBaseConfig for method chaining
     */
    virtual SparkBaseConfig& Apply(SparkBaseConfig& config);

    /**
     * Applies settings from an  AbsoluteEncoderConfig to this
     * SparkBaseConfig.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The  AbsoluteEncoderConfig to copy settings from
     * @return The updated  SparkBaseConfig for method chaining
     */
    virtual SparkBaseConfig& Apply(AbsoluteEncoderConfig& config);

    /**
     * Applies settings from an  AnalogSensorConfig to this
     * SparkBaseConfig.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The  AnalogSensorConfig to copy settings from
     * @return The updated  SparkBaseConfig for method chaining
     */
    virtual SparkBaseConfig& Apply(AnalogSensorConfig& config);

    /**
     * Applies settings from an  EncoderConfig to this
     * SparkBaseConfig.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The  EncoderConfig to copy settings from
     * @return The updated  SparkBaseConfig for method chaining
     */
    virtual SparkBaseConfig& Apply(EncoderConfig& config);

    /**
     * Applies settings from a  LimitSwitchConfig to this
     * SparkBaseConfig.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The  LimitSwitchConfig to copy settings from
     * @return The updated  SparkBaseConfig for method chaining
     */
    virtual SparkBaseConfig& Apply(LimitSwitchConfig& config);

    /**
     * Applies settings from a  SoftLimitConfig to this
     * SparkBaseConfig.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The  SoftLimitConfig to copy settings from
     * @return The updated  SparkBaseConfig for method chaining
     */
    virtual SparkBaseConfig& Apply(SoftLimitConfig& config);

    /**
     * Applies settings from a  ClosedLoopConfig to this
     * SparkBaseConfig.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The  ClosedLoopConfig to copy settings from
     * @return The updated  SparkBaseConfig for method chaining
     */
    virtual SparkBaseConfig& Apply(ClosedLoopConfig& config);

    /**
     * Applies settings from a  SignalsConfig to this
     * SparkBaseConfig.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The  SignalsConfig to copy settings from
     * @return The updated  SparkBaseConfig for method chaining
     */
    virtual SparkBaseConfig& Apply(SignalsConfig& config);

    /**
     * Sets the idle mode setting for the SPARK.
     *
     * @param idleMode kCoast or kBrake
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& SetIdleMode(IdleMode idleMode);

    /**
     * Common interface for inverting direction of a speed controller.
     *
     * <p>This call has no effect if the controller is a follower. To invert a
     * follower, see the follow() method.
     *
     * @param inverted True for inverted
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& Inverted(bool inverted);

    /**
     * Sets the current limit in Amps.
     *
     * <p>The motor controller will reduce the controller voltage output to
     * avoid surpassing this limit. This limit is enabled by default and used
     * for brushless only. This limit is highly recommended when using the NEO
     * brushless motor.
     *
     * <p>The NEO Brushless Motor has a low internal resistance, which can mean
     * large current spikes that could be enough to cause damage to the motor
     * and controller. This current limit provides a smarter strategy to deal
     * with high current draws and keep the motor and controller operating in a
     * safe region.
     *
     * <p>The controller can also limit the current based on the RPM of the
     * motor in a linear fashion to help with controllability in closed loop
     * control. For a response that is linear the entire RPM range leave limit
     * RPM at 0.
     *
     * @param stallLimit The current limit in Amps at 0 RPM.
     * @param freeLimit The current limit at free speed (5700RPM for NEO).
     * @param limitRpm RPM less than this value will be set to the stallLimit,
     * RPM values greater than limitRpm will scale linearly to freeLimit
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& SmartCurrentLimit(int stallLimit, int freeLimit = 0,
                                       int limitRpm = 20000);

    /**
     * Sets the secondary current limit in Amps.
     *
     * <p>The motor controller will disable the output of the controller briefly
     * if the current limit is exceeded to reduce the current. This limit is a
     * simplified 'on/off' controller. This limit is enabled by default but is
     * set higher than the default Smart Current Limit.
     *
     * <p>The time the controller is off after the current limit is reached is
     * determined by the parameter limitCycles, which is the number of PWM
     * cycles (20kHz). The recommended value is the default of 0 which is the
     * minimum time and is part of a PWM cycle from when the over current is
     * detected. This allows the controller to regulate the current close to the
     * limit value.
     *
     * <p>The total time is set by the equation <code>
     * t = (50us - t0) + 50us * limitCycles
     * t = total off time after over current
     * t0 = time from the start of the PWM cycle until over current is detected
     * </code>
     *
     * @param limit The current limit in Amps.
     * @param chopCycles The number of additional PWM cycles to turn the driver
     * off after overcurrent is detected.
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& SecondaryCurrentLimit(double limit, int chopCycles = 0);

    /**
     * Advances the commutation angle of the motor by a specified number of
     * degrees.
     *
     * <p>Warning: This is an advanced feature that should only be used if you
     * know what you are doing. Incorrectly setting the commutation angle can
     * cause changes to torque, efficiency, and the operating range of the
     * motor.
     *
     * @param byDegrees The number of degrees to advance the commutation angle
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& AdvanceCommutation(double byDegrees = 0.0);

    /**
     * Sets the ramp rate for open loop control modes.
     *
     * <p>This is the maximum rate at which the motor controller's output is
     * allowed to change.
     *
     * @param rate Time in seconds to go from 0 to full throttle.
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& OpenLoopRampRate(double rate);

    /**
     * Sets the ramp rate for closed loop control modes.
     *
     * <p>This is the maximum rate at which the motor controller's output is
     * allowed to change.
     *
     * @param rate Time in seconds to go from 0 to full throttle.
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& ClosedLoopRampRate(double rate);

    /**
     * Sets the voltage compensation setting for all modes on the SPARK and
     * enables voltage compensation.
     *
     * @param nominalVoltage Nominal voltage to compensate output to
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& VoltageCompensation(double nominalVoltage);

    /**
     * Disables the voltage compensation setting for all modes on the SPARK.
     *
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& DisableVoltageCompensation();

    /**
     * Causes this controller's output to mirror the provided leader.
     *
     * <p>Only voltage output is mirrored. Settings changed on the leader do not
     * affect the follower.
     *
     * <p>Following anything other than a CAN-enabled SPARK is not officially
     * supported.
     *
     * @param leaderCanId The CAN ID of the device to follow.
     * @param invert Set the follower to output opposite of the leader
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& Follow(int leaderCanId, bool invert = false);

    /**
     * Causes this controller's output to mirror the provided leader.
     *
     * <p>Only voltage output is mirrored. Settings changed on the leader do not
     * affect the follower.
     *
     * <p>Following anything other than a CAN-enabled SPARK is not officially
     * supported.
     *
     * @param leader The motor controller to follow.
     * @param invert Set the follower to output opposite of the leader
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& Follow(const SparkBase& leader, bool invert = false);

    /**
     * Disables follower mode on the controller.
     *
     * @return The modified SparkBaseConfig object for method chaining
     */
    SparkBaseConfig& DisableFollowerMode();

    std::string Flatten() override;

    AbsoluteEncoderConfig absoluteEncoder;
    AnalogSensorConfig analogSensor;
    ClosedLoopConfig closedLoop;
    EncoderConfig encoder;
    LimitSwitchConfig limitSwitch;
    SignalsConfig signals;
    SoftLimitConfig softLimit;
};  // class SparkBaseConfig

}  // namespace rev::spark
