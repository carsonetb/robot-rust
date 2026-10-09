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

#ifndef FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SPARKSIM_H_
#define FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SPARKSIM_H_

#include <memory>
#include <string>

#include <frc/simulation/SimDeviceSim.h>
#include <frc/system/plant/DCMotor.h>

#include "rev/SparkBase.h"
#include "rev/sim/MovingAverageFilterSim.h"
#include "rev/sim/SparkAbsoluteEncoderSim.h"
#include "rev/sim/SparkAnalogSensorSim.h"
#include "rev/sim/SparkLimitSwitchSim.h"
#include "rev/sim/SparkRelativeEncoderSim.h"
#include "rev/sim/SparkSimFaultManager.h"

namespace rev::spark {

class SparkSim {
public:
    SparkSim(SparkBase* spark, frc::DCMotor* motor);

    double GetAppliedOutput() const;
    void SetAppliedOutput(double appliedOutput);

    double GetSetpoint() const;
    ClosedLoopSlot GetClosedLoopSlot() const;

    void iterate(double velocity, double vbus, double dt);

    double GetVelocity() const;
    void SetVelocity(double velocity);

    double GetPosition() const;
    void SetPosition(double position);

    double GetBusVoltage() const;
    void SetBusVoltage(double voltage);

    double GetMotorCurrent() const;
    void SetMotorCurrent(double current);

    void enable();
    void disable();
    void useDriverStationEnable();

    SparkRelativeEncoderSim GetRelativeEncoderSim();
    SparkAbsoluteEncoderSim GetAbsoluteEncoderSim();
    SparkAnalogSensorSim GetAnalogSensorSim();
    SparkLimitSwitchSim GetForwardLimitSwitchSim();
    SparkLimitSwitchSim GetReverseLimitSwitchSim();
    SparkSimFaultManager GetFaultManager();

private:
    bool runLimitLogic(bool forward);

    hal::SimDouble m_appliedOutput;
    hal::SimDouble m_velocity;
    hal::SimDouble m_position;
    hal::SimDouble m_busVoltage;
    hal::SimDouble m_motorCurrent;
    hal::SimDouble m_setpoint;
    hal::SimDouble m_arbFF;
    hal::SimInt m_closedLoopSlot;
    hal::SimInt m_arbFFUnits;
    SparkBase* m_spark;
    frc::DCMotor* m_dcMotor;
    hal::SimInt m_controlMode;
    MovingAverageFilterSim m_velocityAverage;
    std::unique_ptr<bool> m_enable;
    std::string m_deviceName;
    std::string m_unknownDeviceTypeMessage;
};

}  // namespace rev::spark

#endif  // FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SPARKSIM_H_
