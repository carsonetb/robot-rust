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

#ifndef FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SIM_SPARKSIMFAULTMANAGER_H_
#define FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SIM_SPARKSIMFAULTMANAGER_H_

#include <string>

#include <frc/simulation/SimDeviceSim.h>
#include <hal/SimDevice.h>

#include "rev/SparkBase.h"
#include "rev/SparkFlex.h"
#include "rev/SparkMax.h"

namespace rev::spark {

class SparkSimFaultManager {
public:
    explicit SparkSimFaultManager(SparkMax* motor);
    explicit SparkSimFaultManager(SparkFlex* motor);

    void SetFaults(const SparkBase::Faults& faults);
    void SetStickyFaults(const SparkBase::Faults& faults);
    void SetWarnings(const SparkBase::Warnings& warnings);
    void SetStickyWarnings(const SparkBase::Warnings& warnings);

private:
    void SetupSimDevice();

    hal::SimBoolean m_otherFault;
    hal::SimBoolean m_motorTypeFault;
    hal::SimBoolean m_sensorFault;
    hal::SimBoolean m_canFault;
    hal::SimBoolean m_temperatureFault;
    hal::SimBoolean m_drvFault;
    hal::SimBoolean m_escEepromFault;
    hal::SimBoolean m_firmwareFault;
    hal::SimBoolean m_brownoutWarning;
    hal::SimBoolean m_overCurrentWarning;
    hal::SimBoolean m_escEepromWarning;
    hal::SimBoolean m_extEepromWarning;
    hal::SimBoolean m_sensorWarning;
    hal::SimBoolean m_stallWarning;
    hal::SimBoolean m_hasResetWarning;
    hal::SimBoolean m_otherWarning;
    hal::SimBoolean m_otherStickyFault;
    hal::SimBoolean m_motorTypeStickyFault;
    hal::SimBoolean m_sensorStickyFault;
    hal::SimBoolean m_canStickyFault;
    hal::SimBoolean m_temperatureStickyFault;
    hal::SimBoolean m_drvStickyFault;
    hal::SimBoolean m_escEepromStickyFault;
    hal::SimBoolean m_firmwareStickyFault;
    hal::SimBoolean m_brownoutStickyWarning;
    hal::SimBoolean m_overCurrentStickyWarning;
    hal::SimBoolean m_escEepromStickyWarning;
    hal::SimBoolean m_extEepromStickyWarning;
    hal::SimBoolean m_sensorStickyWarning;
    hal::SimBoolean m_stallStickyWarning;
    hal::SimBoolean m_hasResetStickyWarning;
    hal::SimBoolean m_otherStickyWarning;

    SparkBase* m_spark;
    std::string simDeviceName;
};

}  // namespace rev::spark

#endif  // FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SIM_SPARKSIMFAULTMANAGER_H_
