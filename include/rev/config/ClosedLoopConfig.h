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

#include "rev/ClosedLoopTypes.h"
#include "rev/config/BaseConfig.h"
#include "rev/config/FeedForwardConfig.h"
#include "rev/config/MAXMotionConfig.h"

namespace rev::detached {
class DetachedEncoder;
}

namespace rev::spark {

class ClosedLoopConfig : public BaseConfig {
public:
    ClosedLoopConfig() = default;
    ~ClosedLoopConfig() override = default;

    ClosedLoopConfig(const ClosedLoopConfig&) = default;
    ClosedLoopConfig& operator=(const ClosedLoopConfig&) = delete;
    ClosedLoopConfig(ClosedLoopConfig&&) noexcept = delete;
    ClosedLoopConfig& operator=(ClosedLoopConfig&&) noexcept = delete;

    /**
     * Applies settings from another ClosedLoopConfig to this one,
     * including all of its nested configurations.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The ClosedLoopConfig to copy settings from
     * @return The updated ClosedLoopConfig for method chaining
     */
    ClosedLoopConfig& Apply(ClosedLoopConfig& config);

    /**
     * Applies settings from a MAXMotionConfig to this {@link
     * ClosedLoopConfig}.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The MAXMotionConfig to copy settings from
     * @return The updated ClosedLoopConfig for method chaining
     */
    ClosedLoopConfig& Apply(MAXMotionConfig& config);

    /**
     * Applies settings from a FeedForwardConfig to this {@link
     * ClosedLoopConfig}.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The FeedForwardConfig to copy settings from
     * @return The updated ClosedLoopConfig for method chaining
     */
    ClosedLoopConfig& Apply(FeedForwardConfig& config);

    /**
     * Set the PIDF gains of the controller for a specific closed loop slot.
     *
     * @param p The proportional gain value
     * @param i The integral gain value
     * @param d The derivative gain value
     * @param ff The velocity feedforward value
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     * @deprecated Use FeedForwardConfig::V(double v, ClosedLoopSlot slot) to
     * set a Velocity Feedforward
     */
    [[deprecated(
        "Use FeedForwardConfig::V(double v, ClosedLoopSlot slot) to set a "
        "Velocity Feedforward")]] ClosedLoopConfig&
    Pidf(double p, double i, double d, double ff, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the PID gains of the controller for a specific closed loop slot.
     *
     * @param p The proportional gain value
     * @param i The integral gain value
     * @param d The derivative gain value
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& Pid(double p, double i, double d,
                          ClosedLoopSlot slot = kSlot0);

    /**
     * Set the proportional gain of the controller for a specific closed loop
     * slot.
     *
     * @param p The proportional gain value
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& P(double p, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the integral gain of the controller for a specific closed loop slot.
     *
     * @param i The integral gain value
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& I(double i, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the derivative gain of the controller for a specific closed loop
     * slot.
     *
     * @param d The derivative gain value
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& D(double d, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the velocity feedforward gain of the controller for a specific closed
     * loop slot.
     *
     * @param ff The velocity feedforward gain value
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     * @deprecated Use FeedForwardConfig::V(double v, ClosedLoopSlot slot) to
     * set this gain
     */
    [[deprecated(
        "Use FeedForwardConfig::V(double v, ClosedLoopSlot slot) to set this "
        "gain")]] ClosedLoopConfig&
    VelocityFF(double ff, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the derivative filter of the controller for a specific closed loop
     * slot.
     *
     * @param dFilter The derivative filter value
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& DFilter(double dFilter, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the integral zone of the controller for a specific closed loop slot.
     *
     * @param iZone The integral zone value
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& IZone(double iZone, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the minimum output of the controller for a specific closed loop slot.
     *
     * @param minOutput The minimum output value in the range [-1, 1]
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& MinOutput(double minOutput, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the maximum output of the controller for a specific closed loop slot.
     *
     * @param maxOutput The maximum output value in the range [-1, 1]
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& MaxOutput(double maxOutput, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the output range of the controller for a specific closed loop slot.
     *
     * @param minOutput The minimum output value in the range [-1, 1]
     * @param maxOutput The maximum output value in the range [-1, 1]
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& OutputRange(double minOutput, double maxOutput,
                                  ClosedLoopSlot slot = kSlot0);

    /**
     * Set the maximum I accumulator of the controller for a specific closed
     * loop slot. This value is used to constrain the I accumulator to help
     * manage integral wind-up.
     *
     * @param iMaxAccum The max value to constrain the I accumulator to
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& IMaxAccum(double iMaxAccum, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the allowed closed loop error for the controller for a specific
     * PID slot. This value is how much deviation from the setpoint is
     * tolerated and is useful in preventing oscillation around the setpoint.
     * Natively, the units are in rotations but will be affected by the
     * position conversion factor.
     *
     * @param allowedError The allowed error with the position conversion factor
     * applied
     * @param slot The closed loop slot to set the values for
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& AllowedClosedLoopError(double allowedError,
                                             ClosedLoopSlot slot = kSlot0);

    /**
     * Enable or disable PID wrapping for position closed loop control.
     *
     * @param enabled True to enable position PID wrapping
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& PositionWrappingEnabled(bool enabled);

    /**
     * Set the minimum input value for PID wrapping with position closed loop
     * control.
     *
     * @param minInput The value of min input for the position
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& PositionWrappingMinInput(double minInput);

    /**
     * Set the maximum input value for PID wrapping with position closed loop
     * control
     *
     * @param maxInput The value of max input for the position
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& PositionWrappingMaxInput(double maxInput);

    /**
     * Set the input range for PID wrapping with position closed loop control
     *
     * @param minInput The value of min input for the position
     * @param maxInput The value of max input for the position
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& PositionWrappingInputRange(double minInput,
                                                 double maxInput);

    /**
     * Set an attached sensor as the feedback sensor of the controller.
     * The controller will use this sensor as the source of feedback for its
     * closed loop control.
     *
     * To set a detached encoder, use SetFeedbackSensor(FeedbackSensor, int) or
     * SetFeedbackSensor(FeedbackSensor, rev::detached::DetachedEncoder&)
     * instead. This method will ignore @c sensor set to a Detached sensor.
     *
     * <p>The default feedback sensor is assumed to be the primary encoder for
     * either brushless or brushed mode. This can be changed to another feedback
     * sensor for the controller such as an analog sensor, absolute encoder, or
     * alternate/external encoder.
     *
     * @param sensor The attached feedback sensor
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& SetFeedbackSensor(FeedbackSensor sensor);

    /**
     * Set an external CAN Detached Encoder as the feedback sensor of the
     * controller. The controller will use this sensor as the source of feedback
     * for its closed loop control.
     *
     * To set an attached encoder, use the SetFeedbackSensor(FeedbackSensor)
     * method instead. This method will ignore @c sensor set to an attached
     * sensor.
     *
     * @param sensor The detached feedback sensor
     * @detachedEncoderDeviceId The device ID of the detached CAN encoder to use
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& SetFeedbackSensor(FeedbackSensor sensor,
                                        int detachedEncoderDeviceId);

    /**
     * Set an external CAN Detached Encoder as the feedback sensor of the
     * controller. The controller will use this sensor as the source of feedback
     * for its closed loop control.
     *
     * To set an attached encoder, use the SetFeedbackSensor(FeedbackSensor)
     * method instead. This method will ignore @c sensor set to an attached
     * sensor.
     *
     * @param sensor The detached feedback sensor
     * @splineEncoder The detached CAN encoder to use
     * @return The modified ClosedLoopConfig object for method chaining
     */
    ClosedLoopConfig& SetFeedbackSensor(
        FeedbackSensor sensor,
        const rev::detached::DetachedEncoder& detachedEncoder);

    std::string Flatten() override;

    MAXMotionConfig maxMotion;
    FeedForwardConfig feedForward;
};  // ClosedLoopConfig

}  // namespace rev::spark
