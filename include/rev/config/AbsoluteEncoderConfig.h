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

class AbsoluteEncoderConfig : public BaseConfig {
public:
    AbsoluteEncoderConfig() = default;
    ~AbsoluteEncoderConfig() override = default;

    AbsoluteEncoderConfig(const AbsoluteEncoderConfig&) = default;
    AbsoluteEncoderConfig& operator=(const AbsoluteEncoderConfig&) = delete;
    AbsoluteEncoderConfig(AbsoluteEncoderConfig&&) noexcept = delete;
    AbsoluteEncoderConfig& operator=(AbsoluteEncoderConfig&&) noexcept = delete;

    struct Presets final {
        /** REV Robotics - Through Bore Encoder */
        static AbsoluteEncoderConfig& REV_ThroughBoreEncoder() {
            static AbsoluteEncoderConfig config{
                AbsoluteEncoderConfig().StartPulseUs(1.0).EndPulseUs(1.0)};
            return config;
        }

        /** REV Robotics - Through Bore Encoder V2 */
        static AbsoluteEncoderConfig& REV_ThroughBoreEncoderV2() {
            static AbsoluteEncoderConfig config{AbsoluteEncoderConfig()
                                                    .StartPulseUs(3.88443797)
                                                    .EndPulseUs(1.94221899)};
            return config;
        }

        /** REV Robotics - MAXSpline Encoder (via 6-pin JST) */
        static AbsoluteEncoderConfig& REV_SplineEncoder() {
            static AbsoluteEncoderConfig config{
                AbsoluteEncoderConfig().StartPulseUs(1.0).EndPulseUs(1.0)};
            return config;
        }
    };

    /**
     * Applies settings from another AbsoluteEncoderConfig to this one.
     *
     * <p>Settings in the provided config will overwrite existing values in
     * this object. Settings not specified in the provided config remain
     * unchanged.
     *
     * @param config The AbsoluteEncoderConfig to copy settings from
     * @return The updated AbsoluteEncoderConfig for method chaining
     */
    AbsoluteEncoderConfig& Apply(AbsoluteEncoderConfig& config);

    /**
     * Configures the data port to use the absolute encoder, which is
     * specifically required for SPARK MAX.
     *
     * <p>NOTE: This method is only necessary when using an absolute encoder
     * with a SPARK MAX without configuring any of its settings
     *
     * <p>IMPORTANT: SPARK MAX does not support using an absolute encoder in
     * conjunction with an alternate encoder.
     *
     * @return The modified AbsoluteEncoderConfig object for method
     * chaining
     */
    AbsoluteEncoderConfig& SetSparkMaxDataPortConfig();

    /**
     * Set the phase of the absolute encoder so that it is in phase with the
     * motor itself.
     *
     * @param inverted The phase of the encoder
     * @return The modified AbsoluteEncoderConfig object for method
     * chaining
     */
    AbsoluteEncoderConfig& Inverted(bool inverted);

    /**
     * Set the conversion factor for the position of the absolute encoder.
     * Position is returned in native units of rotations and will be
     * multiplied by this conversion factor.
     *
     * @param factor The conversion factor to multiply the native units by
     * @return The modified AbsoluteEncoderConfig object for method
     * chaining
     */
    AbsoluteEncoderConfig& PositionConversionFactor(double factor);

    /**
     * Set the conversion factor for the velocity of the absolute encoder.
     * Velocity is returned in native units of rotations per minute and will
     * be multiplied by this conversion factor.
     *
     * @param factor The conversion factor to multiply the native units by
     * @return The modified AbsoluteEncoderConfig object for method
     * chaining
     */
    AbsoluteEncoderConfig& VelocityConversionFactor(double factor);

    /**
     * Set the zero offset of the absolute encoder, the position that is
     * reported as zero.
     *
     * <p>The zero offset is specified as the reported position of the
     * encoder in the desired zero position as if the zero offset was set to
     * 0, the position conversion factor was set to 1, and inverted was set
     * to false.
     *
     * @param offset The zero offset in the range [0, 1)
     * @return The modified AbsoluteEncoderConfig object for method
     * chaining
     */
    AbsoluteEncoderConfig& ZeroOffset(double offset);

    /**
     * Set the average sampling depth of the absolute encoder. This is a bit
     * size and should be either 1, 2, 4, 8, 16, 32, 64, or 128 (default).
     *
     * @param depth The average sampling depth of 1, 2, 4, 8, 16, 32, 64, or
     * 128
     * @return The modified AbsoluteEncoderConfig object for method
     * chaining
     */
    AbsoluteEncoderConfig& AverageDepth(int depth);

    /**
     * Set the length of the start pulse for this encoder. This pulse will
     * be treated as the 0.0 position.
     *
     * @param startPulseUs The minimum high pulse in microseconds
     * @return The modified AbsoluteEncoderConfig object for method
     * chaining
     */
    AbsoluteEncoderConfig& StartPulseUs(double startPulseUs);

    /**
     * Set the length of the end pulse for this encoder. This pulse will be
     * treated as the 1.0 position.
     *
     * @param endPulseUs The minimum low pulse in microseconds
     * @return The modified AbsoluteEncoderConfig object for method
     * chaining
     */
    AbsoluteEncoderConfig& EndPulseUs(double endPulseUs);

    /**
     * Set whether to enable zero-centering for the absolute encoder. If
     * enabled, the position will be reported in the range (-0.5, 0.5], instead
     * of the default range [0, 1), assuming the default units of rotations.
     *
     * @param zeroCentered Whether to enable zero centering
     * @return The modified AbsoluteEncoderConfig object for method
     * chaining
     */
    AbsoluteEncoderConfig& ZeroCentered(bool zeroCentered);
};

}  // namespace rev::spark
