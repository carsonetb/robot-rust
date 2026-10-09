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

#include "rev/config/AlternateEncoderConfig.h"
#include "rev/config/SparkBaseConfig.h"

namespace rev::spark {

class SparkMaxConfig : public SparkBaseConfig {
public:
    enum DataPortConfig {
        kInvalid = -1,
        kLimitSwitchesAndAbsoluteEncoder = 0,
        kAlternateEncoder = 1
    };

    SparkMaxConfig() = default;
    ~SparkMaxConfig() override = default;

    SparkMaxConfig(const SparkMaxConfig&) = delete;
    SparkMaxConfig& operator=(const SparkMaxConfig&) = delete;
    SparkMaxConfig(SparkMaxConfig&&) noexcept = delete;
    SparkMaxConfig& operator=(SparkMaxConfig&&) noexcept = delete;

    using SparkBaseConfig::Apply;

    /**
     * Applies settings from a SparkBaseConfig to this one; primarily
     * used to apply Presets.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The SparkBaseConfig to copy settings from
     * @return The updated SparkMaxConfig for method chaining
     */
    SparkMaxConfig& Apply(SparkBaseConfig& config) override;

    /**
     * Applies settings from another SparkMaxConfig to this one,
     * including all of its nested configurations.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The SparkMaxConfig to copy settings from
     * @return The updated SparkMaxConfig for method chaining
     */
    SparkMaxConfig& Apply(SparkMaxConfig& config);

    /**
     * Applies settings from an AlternateEncoderConfig to this
     * SparkMaxConfig.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The AlternateEncoderConfig to copy settings from
     * @return The updated SparkMaxConfig for method chaining
     */
    SparkMaxConfig& Apply(AlternateEncoderConfig& config);

    std::string Flatten() override;

    AlternateEncoderConfig alternateEncoder;

private:
    void Sanitize();
};  // class SparkMaxConfig

}  // namespace rev::spark
