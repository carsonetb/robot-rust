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

class AlternateEncoderConfig : public BaseConfig {
public:
    enum Type { kQuadrature = 0 };

    static Type FromId(int id) { return kQuadrature; }

    AlternateEncoderConfig() = default;
    ~AlternateEncoderConfig() override = default;

    AlternateEncoderConfig(const AlternateEncoderConfig&) = default;
    AlternateEncoderConfig& operator=(const AlternateEncoderConfig&) = delete;
    AlternateEncoderConfig(AlternateEncoderConfig&&) noexcept = delete;
    AlternateEncoderConfig& operator=(AlternateEncoderConfig&&) noexcept =
        delete;

    struct Presets final {
        /** REV Robotics - Through Bore Encoder */
        static AlternateEncoderConfig& REV_ThroughBoreEncoder() {
            static AlternateEncoderConfig config{
                AlternateEncoderConfig().CountsPerRevolution(8192)};
            return config;
        }

        /** REV Robotics - Through Bore Encoder V2 */
        static AlternateEncoderConfig& REV_ThroughBoreEncoderV2() {
            static AlternateEncoderConfig config{
                AlternateEncoderConfig().CountsPerRevolution(8192)};
            return config;
        }

        /** REV Robotics - MAXSpline Encoder (via 6-pin JST) */
        static AlternateEncoderConfig& REV_SplineEncoder() {
            static AlternateEncoderConfig config{
                AlternateEncoderConfig().CountsPerRevolution(8192)};
            return config;
        }
    };

    /**
     * Applies settings from another AlternateEncoderConfig to this one.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The AlternateEncoderConfig to copy settings from
     * @return The updated AlternateEncoderConfig for method chaining
     */
    AlternateEncoderConfig& Apply(AlternateEncoderConfig& config);

    /**
     * Configures the data port to use the alternate encoder, which is
     * specifically required for SPARK MAX.
     *
     * <p>NOTE: This method is only necessary when using an alternate encoder
     * with a SPARK MAX without configuring any of its settings
     *
     * <p>IMPORTANT: SPARK MAX does not support using an alternate encoder in
     * conjunction with an absolute encoder and/or limit switches.
     *
     * @return The modified AlternateEncoderConfig object for method
     * chaining
     */
    AlternateEncoderConfig& SetSparkMaxDataPortConfig();

    /**
     * Set the counts per revolutions of the alternate encoder.
     *
     * @param cpr The counts per rotation
     * @return The modified AlternateEncoderConfig object for method
     * chaining
     */
    AlternateEncoderConfig& CountsPerRevolution(int cpr);

    /**
     * Set the phase of the alternate encoder so that it is in phase with the
     * motor itself.
     *
     * @param inverted The phase of the encoder
     * @return The modified AlternateEncoderConfig object for method
     * chaining
     */
    AlternateEncoderConfig& Inverted(bool inverted);

    /**
     * Set the conversion factor for the position of the alternate encoder.
     * Position is returned in native units of rotations and will be multiplied
     * by this conversion factor.
     *
     * @param factor The conversion factor to multiply the native units by
     * @return The modified AlternateEncoderConfig object for method
     * chaining
     */
    AlternateEncoderConfig& PositionConversionFactor(double factor);

    /**
     * Set the conversion factor for the velocity of the alternate encoder.
     * Velocity is returned in native units of rotations per minute and will be
     * multiplied by this conversion factor.
     *
     * @param factor The conversion factor to multiply the native units by
     * @return The modified AlternateEncoderConfig object for method
     * chaining
     */
    AlternateEncoderConfig& VelocityConversionFactor(double factor);

    /**
     * Set the sampling depth of the velocity calculation process of the
     * alternate encoder. This value sets the number of samples in the average
     * for velocity readings. For a quadrature encoder, this can be any value
     * from 1 to 64 (default).
     *
     * @param depth The velocity calculation process's sampling depth
     * @return The modified AlternateEncoderConfig object for method
     * chaining
     */
    AlternateEncoderConfig& AverageDepth(int depth);

    /**
     * Set the position measurement period used to calculate the velocity of the
     * alternate encoder. For a quadrature encoder, this number may be between 1
     * and 100 (default).
     *
     * <p>The basic formula to calculate velocity is change in position / change
     * in time. This parameter sets the change in time for measurement.
     *
     * @param periodMs Measurement period in milliseconds
     * @return The modified AlternateEncoderConfig object for method
     * chaining
     */
    AlternateEncoderConfig& MeasurementPeriod(int periodMs);
};

}  // namespace rev::spark
