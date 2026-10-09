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

class EncoderConfig : public BaseConfig {
public:
    EncoderConfig() = default;
    ~EncoderConfig() override = default;

    EncoderConfig(const EncoderConfig&) = default;
    EncoderConfig& operator=(const EncoderConfig&) = delete;
    EncoderConfig(EncoderConfig&&) noexcept = delete;
    EncoderConfig& operator=(EncoderConfig&&) noexcept = delete;

    struct Presets final {
        // REV Robotics - Through Bore Encoder
        static EncoderConfig& REV_ThroughBoreEncoder() {
            static EncoderConfig config{
                EncoderConfig().CountsPerRevolution(8192)};
            return config;
        }

        // REV Robotics - Through Bore Encoder V2
        static EncoderConfig& REV_ThroughBoreEncoderV2() {
            static EncoderConfig config{
                EncoderConfig().CountsPerRevolution(8192)};
            return config;
        }

        /** REV Robotics - MAXSpline Encoder (via 6-pin JST) */
        static EncoderConfig& REV_SplineEncoder() {
            static EncoderConfig config{
                EncoderConfig().CountsPerRevolution(8192)};
            return config;
        }
    };

    /**
     * Applies settings from another EncoderConfig to this one.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The EncoderConfig to copy settings from
     * @return The updated EncoderConfig for method chaining
     */
    EncoderConfig& Apply(EncoderConfig& config);

    /**
     * Set the counts per revolutions of the encoder.
     *
     * <p>NOTE: This only applies to an encoder used in brushed mode.
     *
     * @param cpr The counts per rotation
     * @return The modified EncoderConfig object for method chaining
     */
    EncoderConfig& CountsPerRevolution(int cpr);

    /**
     * Set the phase of the encoder so that it is in phase with the motor
     * itself.
     *
     * <p>NOTE: This only applies to an encoder used in brushed mode.
     *
     * @param inverted The phase of the encoder
     * @return The modified EncoderConfig object for method chaining
     */
    EncoderConfig& Inverted(bool inverted);

    /**
     * Set the conversion factor for the position of the encoder. Position is
     * returned in native units of rotations and will be multiplied by this
     * conversion factor.
     *
     * @param factor The conversion factor to multiply the native units by
     * @return The modified EncoderConfig object for method chaining
     */
    EncoderConfig& PositionConversionFactor(double factor);

    /**
     * Set the conversion factor for the velocity of the encoder. Velocity is
     * returned in native units of rotations per minute and will be multiplied
     * by this conversion factor.
     *
     * @param factor The conversion factor to multiply the native units by
     * @return The modified EncoderConfig object for method chaining
     */
    EncoderConfig& VelocityConversionFactor(double factor);

    /**
     * Set the sampling depth of the velocity calculation process of the
     * encoder. This value sets the number of samples in the average for
     * velocity readings. This value must be in the range [1, 64]. The default
     * value is 64.
     *
     * @param depth The velocity calculation process's sampling depth
     * @return The modified EncoderConfig object for method chaining
     */
    EncoderConfig& QuadratureAverageDepth(int depth);

    /**
     * Set the position measurement period used to calculate the velocity of the
     * encoder. This value is in units of milliseconds and must be in a range
     * [1, 100]. The default value is 100ms
     *
     * <p>The basic formula to calculate velocity is change in position / change
     * in time. This parameter sets the change in time for measurement.
     *
     * @param periodMs Measurement period in milliseconds
     * @return The modified EncoderConfig object for method chaining
     */
    EncoderConfig& QuadratureMeasurementPeriod(int periodMs);

    /**
     * Set the sampling depth of the velocity calculation process of the
     * encoder. This value sets the number of samples in the average for
     * velocity readings. This value must be either 1, 2, 4, or 8 (default).
     *
     * @param depth The velocity calculation process's sampling depth
     * @return The modified EncoderConfig object for method chaining
     */
    EncoderConfig& UvwAverageDepth(int depth);

    /**
     * Set the position measurement period used to calculate the velocity of the
     * encoder. This value is in units of milliseconds and must be in a range
     * [8, 64]. The default value is 32ms.
     *
     * <p>The basic formula to calculate velocity is change in position / change
     * in time. This parameter sets the change in time for measurement.
     *
     * @param periodMs Measurement period in milliseconds
     * @return The modified EncoderConfig object for method chaining
     */
    EncoderConfig& UvwMeasurementPeriod(int periodMs);
};

}  // namespace rev::spark
