/*
 * Copyright (c) 2021-2025 REV Robotics
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

#ifdef _MSC_VER
// Disable deprecation warnings for this file when using VS compiler
#pragma warning(disable : 4996)
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

#include <stdint.h>

#include "rev/AnalogInput.h"
#include "rev/REVLibError.h"

namespace rev::spark {

class SparkBase;

class SparkAnalogSensor : public AnalogInput {
    friend class SparkBase;

public:
    SparkAnalogSensor(SparkAnalogSensor&&) = default;
    SparkAnalogSensor& operator=(SparkAnalogSensor&&) = default;

    SparkAnalogSensor(const SparkAnalogSensor& rhs) = default;

    ~SparkAnalogSensor() override = default;

    /**
     * Get the voltage of the analog sensor.
     *
     * @return Voltage of the sensor
     */
    double GetVoltage() const override;

    /**
     * Get the position of the sensor. Returns value in the native unit
     * of 'volt' by default, and can be changed by a scale factor
     * using AnalogSensorConfig::PositionConversionFactor().
     *
     * @return Position of the sensor in volts
     */
    double GetPosition() const override;

    /**
     * Get the velocity of the sensor. Returns value in the native units of
     * 'volts per second' by default, and can be changed by a
     * scale factor using AnalogSensorConfig::VelocityConversionFactor().
     *
     * @return Velocity of the sensor in volts per second
     */
    double GetVelocity() const;

private:
    SparkBase* m_device;

    explicit SparkAnalogSensor(SparkBase& device);

    /**
     * Set the voltage of the analog sensor in simulation.
     *
     */
    void SetSimVoltage(double voltage);

    /**
     * Set the position of the sensor in simulation.
     *
     */
    void SetSimPosition(double position);

    /**
     * Set the velocity of the sensor in simulation.
     *
     */
    void SetSimVelocity(double velocity);
};

}  // namespace rev::spark

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
