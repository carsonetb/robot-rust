/*
 * Copyright (c) 2024-2025 REV Robotics
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

class AnalogSensorConfig : public BaseConfig {
public:
    AnalogSensorConfig() = default;
    ~AnalogSensorConfig() override = default;

    AnalogSensorConfig(const AnalogSensorConfig&) = default;
    AnalogSensorConfig& operator=(const AnalogSensorConfig&) = delete;
    AnalogSensorConfig(AnalogSensorConfig&&) noexcept = delete;
    AnalogSensorConfig& operator=(AnalogSensorConfig&&) noexcept = delete;

    /**
     * Applies settings from another AnalogSensorConfig to this one.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The AnalogSensorConfig to copy settings from
     * @return The updated AnalogSensorConfig for method chaining
     */
    AnalogSensorConfig& Apply(AnalogSensorConfig& config);

    /**
     * Set the phase of the analog sensor so that it is in phase with the motor
     * itself.
     *
     * @param inverted The phase of the analog sensor
     * @return The modified AnalogSensorConfig object for method
     * chaining
     */
    AnalogSensorConfig& Inverted(bool inverted);

    /**
     * Set the conversion factor for the position of the analog sensor. Position
     * is returned in native units of volts and will be multiplied by this
     * conversion factor.
     *
     * @param factor The conversion factor to multiply the native units by
     * @return The modified AnalogSensorConfig object for method
     * chaining
     */
    AnalogSensorConfig& PositionConversionFactor(double factor);

    /**
     * Set the conversion factor for the velocity of the analog sensor. Velocity
     * is returned in native units of volts per second and will be multiplied by
     * this conversion factor.
     *
     * @param factor The conversion factor to multiply the native units by
     * @return The modified AnalogSensorConfig object for method
     * chaining
     */
    AnalogSensorConfig& VelocityConversionFactor(double factor);
};

}  // namespace rev::spark
