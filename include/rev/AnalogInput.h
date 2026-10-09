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

namespace rev {

namespace spark {
class SparkAnalogSensor;
}  // namespace spark

/**
 * Get an instance of AnalogInput by using
 * SparkBase::GetAnalog(SparkAnalogSensor::Mode)}.
 */
class AnalogInput {
    // Friend to allow construction
    friend class spark::SparkAnalogSensor;

public:
    virtual ~AnalogInput() {}

    /**
     * Get the voltage of the analog sensor.
     *
     * @return Voltage of the sensor
     */
    virtual double GetVoltage() const = 0;

    /**
     * Get the position of the motor. Returns value in the native unit
     * of 'volt' by default, and can be changed by a scale factor
     * using AnalogSensorConfig::PositionConversionFactor().
     *
     * @return Position of the sensor in volts
     */
    virtual double GetPosition() const = 0;

private:
    AnalogInput() {}
};

}  // namespace rev
