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

#include <atomic>

#include "SparkBase.h"
#include "rev/ConfigureTypes.h"
#include "rev/SparkMaxAlternateEncoder.h"
#include "rev/config/SparkMaxConfigAccessor.h"

namespace rev::spark {

class SparkMax : public SparkBase {
    friend class SparkMaxAlternateEncoder;

public:
    /**
     * Accessor for SPARK parameter values. This object contains fields and
     * methods to retrieve parameters that have been applied to the device. To
     * set parameters, see SparkBaseConfig and SparkBase::Configure.
     *
     * NOTE: This uses calls that are blocking to retrieve parameters and should
     * be used infrequently.
     */
    SparkMaxConfigAccessor configAccessor;

    /**
     * Create a new object to control a SPARK MAX motor Controller
     *
     * @param deviceID The device ID.
     * @param type     The motor type connected to the controller. Brushless
     *                 motor wires must be connected to their matching colors,
     * and the hall sensor must be plugged in. Brushed motors must be connected
     *                 to the Red and Black terminals only.
     */
    explicit SparkMax(int deviceID, MotorType type);

    /**
     * Closes the SPARK MAX Controller
     */
    ~SparkMax() override = default;

    /*
     * @deprecated Use {@link #Configure(SparkBaseConfig&, rev::ResetMode,
     * rev::PersistMode)} instead. This method will be removed in 2027.
     */
    [[deprecated(
        "Use Configure(SparkBaseConfig&, rev::ResetMode, rev::PersistMode) "
        "instead. This method will be removed in 2027.")]]
    REVLibError Configure(SparkBaseConfig& config, ResetMode resetMode,
                          PersistMode persistMode) override;

    REVLibError Configure(SparkBaseConfig& config, rev::ResetMode resetMode,
                          rev::PersistMode persistMode) override;

    /**
     * Returns an object for interfacing with a quadrature encoder connected to
     * the alternate encoder mode data port pins. These are defined as:
     *
     * Pin 4 (Forward Limit Switch): Index
     * Pin 6 (Multi-function): Encoder A
     * Pin 8 (Reverse Limit Switch): Encoder B
     *
     * This call will disable support for the limit switch inputs.
     */
    SparkMaxAlternateEncoder& GetAlternateEncoder();

    SparkAbsoluteEncoder& GetAbsoluteEncoder() override;

    SparkLimitSwitch& GetForwardLimitSwitch() override;

    SparkLimitSwitch& GetReverseLimitSwitch() override;

private:
    SparkMaxAlternateEncoder m_AltEncoder;
    std::atomic<bool> m_altEncoderCreated{false};

    void CheckDataPortAlternateEncoder();
    void CheckDataPortAbsoluteEncoder();
    void CheckDataPortLimitSwitch();
};

}  // namespace rev::spark
