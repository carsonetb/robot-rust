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

#include "rev/config/BaseConfig.h"

namespace rev::spark {

class SignalsConfig : public BaseConfig {
public:
    SignalsConfig() = default;
    ~SignalsConfig() override = default;

    SignalsConfig(const SignalsConfig&) = default;
    SignalsConfig& operator=(const SignalsConfig&) = delete;
    SignalsConfig(SignalsConfig&&) noexcept = delete;
    SignalsConfig& operator=(SignalsConfig&&) noexcept = delete;

    /**
     * Applies settings from another SignalsConfig to this one.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The SignalsConfig to copy settings from
     * @return The updated SignalsConfig for method chaining
     */
    SignalsConfig& Apply(SignalsConfig& config);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkBase::GetAppliedOutput(). The default period is 10ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * <p><b>NOTE:</b> Applied output is used by other SPARK devices in follower
     * mode. Setting too long of a period should be avoided if this SPARK device
     * is the leader, as it can degrade follower mode performance.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& AppliedOutputPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkBase::GetAppliedOutput().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     * @deprecated Calling this method will have no effect, as status 0 cannot
     * be disabled.
     */
    [[deprecated]] SignalsConfig& AppliedOutputAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkBase::getBusVoltage(). The default period is 10ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * <p><b>NOTE:</b> This signal shares a status frame with applied output
     * which is used by other SPARK devices in follower mode. Setting too long
     * of a period should be avoided if this SPARK device is the leader, as it
     * can degrade follower mode performance.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& BusVoltagePeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkBase::getBusVoltage().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     * @deprecated Calling this method will have no effect, as status 0 cannot
     * be disabled.
     */
    [[deprecated]] SignalsConfig& BusVoltageAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkBase::GetOutputCurrent(). The default period is 10ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * <p><b>NOTE:</b> This signal shares a status frame with applied output
     * which is used by other SPARK devices in follower mode. Setting too long
     * of a period should be avoided if this SPARK device is the leader, as it
     * can degrade follower mode performance.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& OutputCurrentPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkBase::GetOutputCurrent().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     * @deprecated Calling this method will have no effect, as status 0 cannot
     * be disabled.
     */
    [[deprecated]] SignalsConfig& OutputCurrentAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkBase::GetMotorTemperature(). The default period is 10ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * <p><b>NOTE:</b> This signal shares a status frame with applied output
     * which is used by other SPARK devices in follower mode. Setting too long
     * of a period should be avoided if this SPARK device is the leader, as it
     * can degrade follower mode performance.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& MotorTemperaturePeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkBase::GetMotorTemperature().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     * @deprecated Calling this method will have no effect, as status 0 cannot
     * be disabled.
     */
    [[deprecated]] SignalsConfig& MotorTemperatureAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkLimitSwitch::IsPressed(). The default period is 10ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * <p><b>NOTE:</b> This signal shares a status frame with applied output
     * which is used by other SPARK devices in follower mode. Setting too long
     * of a period should be avoided if this SPARK device is the leader, as it
     * can degrade follower mode performance.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& LimitsPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkLimitSwitch::IsPressed().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     * @deprecated Calling this method will have no effect, as status 0 cannot
     * be disabled.
     */
    [[deprecated]] SignalsConfig& LimitsAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkBase::GetFaults() and SparkBase::GetStickyFaults().
     * The default period is 250ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& FaultsPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkBase::GetFaults() and
     * SparkBase::GetStickyFaults().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& FaultsAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkBase::GetWarnings() and SparkBase::GetStickyWarnings().
     * The default period is 250ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& WarningsPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkBase::GetWarnings() and
     * SparkBase::GetStickyWarnings().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& WarningsAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkRelativeEncoder::GetVelocity(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& PrimaryEncoderVelocityPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkRelativeEncoder::GetVelocity().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& PrimaryEncoderVelocityAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkRelativeEncoder::GetPosition(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& PrimaryEncoderPositionPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkRelativeEncoder::GetPosition().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& PrimaryEncoderPositionAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkAnalogSensor::GetVoltage(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& AnalogVoltagePeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkAnalogSensor::GetVoltage().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& AnalogVoltageAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkAnalogSensor::GetVelocity(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& AnalogVelocityPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkAnalogSensor::GetVelocity().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& AnalogVelocityAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkAnalogSensor::GetPosition(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& AnalogPositionPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkAnalogSensor::GetPosition().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& AnalogPositionAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkFlexExternalEncoder::GetVelocity() or
     * SparkMaxAlternateEncoder::GetVelocity(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& ExternalOrAltEncoderVelocity(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkFlexExternalEncoder::GetVelocity() or
     * SparkMaxAlternateEncoder::GetVelocity().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& ExternalOrAltEncoderVelocityAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkFlexExternalEncoder::GetPosition() or
     * SparkMaxAlternateEncoder::GetPosition(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& ExternalOrAltEncoderPosition(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkFlexExternalEncoder::GetPosition() or
     * SparkMaxAlternateEncoder::GetPosition().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& ExternalOrAltEncoderPositionAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkAbsoluteEncoder::GetVelocity(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& AbsoluteEncoderVelocityPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkAbsoluteEncoder::GetVelocity().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& AbsoluteEncoderVelocityAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkAbsoluteEncoder::GetPosition(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& AbsoluteEncoderPositionPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkAbsoluteEncoder::GetPosition().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& AbsoluteEncoderPositionAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal
     * representing the unadjusted duty cycle period. The default period is
     * 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& UnadjustedDutyCyclePeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * representing the unadjusted duty cycle period.
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& UnadjustedDutyCyclePeriodAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal
     * representing the duty cycle period. The default period is
     * 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& DutyCyclePeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * representing the duty cycle period.
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& DutyCyclePeriodAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkClosedLoopController::GetIAccum(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& IAccumulationPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkClosedLoopController::GetIAccum().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& IAccumulationAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkClosedLoopController::GetSetpoint(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& SetpointPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkClosedLoopController::GetSetpoint().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& SetpointAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkClosedLoopController::IsAtSetpoint(). The default period is 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& IsAtSetpointPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkClosedLoopController::IsAtSetpoint().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& IsAtSetpointAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by SparkClosedLoopController::GetSelectedSlot(). The default period is
     * 20ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& SelectedSlotPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by SparkClosedLoopController::GetSelectedSlot().
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified SignalsConfig object for method chaining
     */
    SignalsConfig& SelectedSlotAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by {@link
     * com.revrobotics.spark.SparkClosedLoopController#getMAXMotionSetpointPosition()
     * SparkClosedLoopController.getMAXMotionSetpointPosition()}. The default
     * period is 100ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified {@link SignalsConfig} object for method chaining
     */
    SignalsConfig& MaxMotionSetpointPositionPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by {@link
     * com.revrobotics.spark.SparkClosedLoopController#getMAXMotionSetpointPosition()
     * SparkClosedLoopController.getMAXMotionSetpointPosition()}
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified {@link SignalsConfig} object for method chaining
     */
    SignalsConfig& MaxMotionSetpointPositionAlwaysOn(bool enabled);

    /**
     * Set the period (ms) of the status frame that provides the signal returned
     * by {@link
     * com.revrobotics.spark.SparkClosedLoopController#getMAXMotionSetpointVelocity()
     * SparkClosedLoopController.getMAXMotionSetpointVelocity()}. The default
     * period is 100ms.
     *
     * <p>If multiple periods are set for signals within the same status frame,
     * the minimum given value will be used.
     *
     * @param periodMs The period in milliseconds
     * @return The modified {@link SignalsConfig} object for method chaining
     */
    SignalsConfig& MaxMotionSetpointVelocityPeriodMs(int periodMs);

    /**
     * Set whether to always enable the status frame that provides the signal
     * returned by {@link
     * com.revrobotics.spark.SparkClosedLoopController#getMAXMotionSetpointVelocity()
     * SparkClosedLoopController.getMAXMotionSetpointVelocity()}
     *
     * <p>Status frames are only enabled when a signal is requested via its
     * respective getter method, and there may be a small period of time where
     * the signal's data is unavailable due to waiting for the SPARK to receive
     * the command to enable the status frame. Use this method to enable the
     * status frame at all times.
     *
     * <p>If multiple alwaysOn values are set for signals within the same status
     * frame, the result from OR'ing the values will be used.
     *
     * @param enabled True to always enable the status frame
     * @return The modified {@link SignalsConfig} object for method chaining
     */
    SignalsConfig& MaxMotionSetpointVelocityAlwaysOn(bool enabled);

private:
    void SetPeriodMsCore(int parameterId, int periodMs);
    void SetAlwaysOnCore(int parameterId, bool enabled);
};  // class SignalsConfig

}  // namespace rev::spark
