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

#include "rev/config/AbsoluteEncoderConfigAccessor.h"
#include "rev/config/AnalogSensorConfigAccessor.h"
#include "rev/config/ClosedLoopConfigAccessor.h"
#include "rev/config/EncoderConfigAccessor.h"
#include "rev/config/LimitSwitchConfigAccessor.h"
#include "rev/config/SignalsConfigAccessor.h"
#include "rev/config/SoftLimitConfigAccessor.h"
#include "rev/config/SparkBaseConfig.h"

namespace rev::spark {

class SparkBaseConfigAccessor {
protected:
    explicit SparkBaseConfigAccessor(void* sparkHandle);

private:
    void* m_sparkHandle;

public:
    /**
     * Accessor for parameters relating to the absolute encoder. To configure
     * these values, use AbsoluteEncoderConfig and call SparkBase::Configure.
     *
     * <p>NOTE: This uses calls that are blocking to retrieve parameters and
     * should be used infrequently.
     */
    AbsoluteEncoderConfigAccessor absoluteEncoder;

    /**
     * Accessor for parameters relating to the analog sensor. To configure
     * these values, use AnalogSensorConfig and call SparkBase::Configure.
     *
     * <p>NOTE: This uses calls that are blocking to retrieve parameters and
     * should be used infrequently.
     */
    AnalogSensorConfigAccessor analogSensor;

    /**
     * Accessor for parameters relating to the closed loop controller. To
     * configure these values, use ClosedLoopConfig and call
     * SparkBase::Configure.
     *
     * <p>NOTE: This uses calls that are blocking to retrieve parameters and
     * should be used infrequently.
     */
    ClosedLoopConfigAccessor closedLoop;

    /**
     * Accessor for parameters relating to the primary encoder. To configure
     * these values, use EncoderConfig and call SparkBase::Configure.
     *
     * <p>NOTE: This uses calls that are blocking to retrieve parameters and
     * should be used infrequently.
     */
    EncoderConfigAccessor encoder;

    /**
     * Accessor for parameters relating to the hardware limit switches. To
     * configure these values, use LimitSwitchConfig and call
     * SparkBase::Configure.
     *
     * <p>NOTE: This uses calls that are blocking to retrieve parameters and
     * should be used infrequently.
     */
    LimitSwitchConfigAccessor limitSwitch;

    /**
     * Accessor for parameters relating to status signals. To configure
     * these values, use SignalsConfig and call SparkBase::Configure.
     *
     * <p>NOTE: This uses calls that are blocking to retrieve parameters and
     * should be used infrequently.
     */
    SignalsConfigAccessor signals;

    /**
     * Accessor for parameters relating to the software limits. To configure
     * these values, use SoftLimitConfig and call SparkBase::Configure.
     *
     * <p>NOTE: This uses calls that are blocking to retrieve parameters and
     * should be used infrequently.
     */
    SoftLimitConfigAccessor softLimit;

    SparkBaseConfig::IdleMode GetIdleMode();
    bool GetInverted();
    int GetSmartCurrentLimit();
    int GetSmartCurrentFreeLimit();
    int GetSmartCurrentRPMLimit();
    double GetSecondaryCurrentLimit();
    int GetSecondaryCurrentLimitChopCycles();
    double GetAdvanceCommutation();
    double GetOpenLoopRampRate();
    double GetClosedLoopRampRate();
    double GetVoltageCompensation();
    bool GetVoltageCompensationEnabled();
    int GetFollowerModeLeaderId();
    bool GetFollowerModeInverted();
};  // class SparkBaseConfigAccessor

}  // namespace rev::spark
