/*
 * Copyright (c) 2018-2025 REV Robotics
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

#include "SparkBase.h"
#include "rev/SparkFlexExternalEncoder.h"
#include "rev/config/SparkFlexConfigAccessor.h"

namespace rev::spark {

class SparkFlex : public SparkBase {
    friend class SparkFlexExternalEncoder;

public:
    /**
     * Accessor for SPARK parameter values. This object contains fields and
     * methods to retrieve parameters that have been applied to the device. To
     * set parameters, see SparkBaseConfig and SparkBase::Configure.
     *
     * NOTE: This uses calls that are blocking to retrieve parameters and should
     * be used infrequently.
     */
    SparkFlexConfigAccessor configAccessor;

    /**
     * Create a new object to control a SPARK Flex motor Controller
     *
     * @param deviceID The device ID.
     * @param type     The motor type connected to the controller. Brushless
     *                 motor wires must be connected to their matching colors,
     *                 and the hall sensor must be plugged in. Brushed motors
     *                 must be connected to the Red and Black terminals only.
     */
    explicit SparkFlex(int deviceID, MotorType type);

    /**
     * Returns an object for interfacing with an external quadrature encoder
     */
    SparkFlexExternalEncoder& GetExternalEncoder();

    /**
     * Closes the SPARK Flex Controller
     */
    ~SparkFlex() override = default;

private:
    SparkFlexExternalEncoder m_ExternalEncoder;
};

}  // namespace rev::spark
