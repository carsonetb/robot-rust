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

#ifndef FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SIM_SERVOHUBSIMFAULTMANAGER_H_
#define FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SIM_SERVOHUBSIMFAULTMANAGER_H_

#include <string>

#include <hal/SimDevice.h>

#include "rev/ServoHub.h"

namespace rev::servohub {

class ServoHubSimFaultManager {
public:
    /**
     * Create a Fault Manager object, which allows you to get and set the status
     * of simulated faults on your simulated Servo Hub. Constructing this object
     * will also cause the Fault Manager to appear in the sim gui. The state of
     * faults can be fetched on the original Servo Hub Object.
     *
     * @param servoHub The ServoHub associated with the Fault Manager
     */
    explicit ServoHubSimFaultManager(ServoHub* servoHub);

    ServoHubSimFaultManager() = delete;

    /**
     * Set the state of the simulated faults of the device.
     *
     * <p>Use device.getFaults() to get the object and modify the parameters.
     *
     * @param faults a Faults object indicating the state of the faults
     */
    void SetFaults(const ServoHub::Faults& faults);

    /**
     * Set the state of the simulated sticky faults of the device.
     *
     * <p>Use device.getStickyFaults() to get the object and modify the
     * parameters.
     *
     * @param faults a Faults object indicating the state of the sticky faults
     */
    void SetStickyFaults(const ServoHub::Faults& faults);

    /**
     * Set the state of the simulated warnings of the device.
     *
     * <p>Use device.getWarnings() to get the object and modify the parameters.
     *
     * @param warnings a Warnings object indicating the state of the warnings
     */
    void SetWarnings(const ServoHub::Warnings& warnings);

    /**
     * Set the state of the simulated sticky warnings of the device.
     *
     * <p>Use device.getStickyWarnings() to get the object and modify the
     * parameters.
     *
     * @param warnings a Warnings object indicating the state of the sticky
     * warnings
     */
    void SetStickyWarnings(const ServoHub::Warnings& warnings);

private:
    void SetupSimDevice();

    hal::SimBoolean m_regulatorPGoodFault;
    hal::SimBoolean m_firmwareFault;
    hal::SimBoolean m_hardwareFault;
    hal::SimBoolean m_lowBatteryFault;

    hal::SimBoolean m_regulatorPGoodStickyFault;
    hal::SimBoolean m_firmwareStickyFault;
    hal::SimBoolean m_hardwareStickyFault;
    hal::SimBoolean m_lowBatteryStickyFault;

    hal::SimBoolean m_brownoutWarning;
    hal::SimBoolean m_canWarning;
    hal::SimBoolean m_canBusOffWarning;
    hal::SimBoolean m_hasResetWarning;
    hal::SimBoolean m_channel0OvercurrentWarning;
    hal::SimBoolean m_channel1OvercurrentWarning;
    hal::SimBoolean m_channel2OvercurrentWarning;
    hal::SimBoolean m_channel3OvercurrentWarning;
    hal::SimBoolean m_channel4OvercurrentWarning;
    hal::SimBoolean m_channel5OvercurrentWarning;

    hal::SimBoolean m_brownoutStickyWarning;
    hal::SimBoolean m_canStickyWarning;
    hal::SimBoolean m_canBusOffStickyWarning;
    hal::SimBoolean m_hasResetStickyWarning;
    hal::SimBoolean m_channel0OvercurrentStickyWarning;
    hal::SimBoolean m_channel1OvercurrentStickyWarning;
    hal::SimBoolean m_channel2OvercurrentStickyWarning;
    hal::SimBoolean m_channel3OvercurrentStickyWarning;
    hal::SimBoolean m_channel4OvercurrentStickyWarning;
    hal::SimBoolean m_channel5OvercurrentStickyWarning;

    ServoHub* m_servoHub;
    std::string simDeviceName;
};

}  // namespace rev::servohub

#endif  // FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SIM_SERVOHUBSIMFAULTMANAGER_H_
