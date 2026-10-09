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

#ifndef FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SERVOHUBSIM_H_
#define FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SERVOHUBSIM_H_

#include <memory>
#include <string>
#include <vector>

#include "rev/ServoHub.h"
#include "rev/sim/ServoHubSimFaultManager.h"

namespace rev::servohub {

class ServoHubSim {
public:
    /**
     * Create a simulated CAN Servo Hub object. This class simulates some of the
     * internal behavior of the device. This class is not required to display to
     * the sim GUI, but is required to interact with it.
     *
     * @param servoHub The Servo Hub to simulate
     */
    explicit ServoHubSim(ServoHub* servoHub);

    /**
     * Get the simulated device voltage output. This matches the value from
     * the ServoHub::GetDeviceVoltage().
     *
     * @return device voltage in volts
     */
    double GetDeviceVoltage() const;

    /**
     * Set the simulated device voltage.
     *
     * @param voltage device voltage in volts
     */
    void SetDeviceVoltage(double voltage);

    /**
     * Get the simulated device current output. This matches the value from
     * the ServoHub::GetDeviceCurrent().
     *
     * @return device current in amps
     */
    double GetDeviceCurrent() const;

    /**
     * Set the simulated device current.
     *
     * @param current device current in amps
     */
    void SetDeviceCurrent(double current);

    /**
     * Get the simulated servo voltage output. This matches the value from
     * the ServoHub::GetServoVoltage().
     *
     * @return servo voltage in volts
     */
    double GetServoVoltage() const;

    /**
     * Set the simulated device voltage.
     *
     * @param voltage device voltage in volts
     */
    void SetServoVoltage(double voltage);

    /**
     * Get the simulated bank pulse period. This matches the value from
     * the ServoHub::GetBankPulsePeriod().
     *
     * @param bank the specific bank (0-2, or 3-5)to get
     *
     * @return pulse period (in microseconds)for the specified bank
     */
    int GetBankPulsePeriod(ServoHub::Bank bank) const;

    /**
     * Set the simulated bank pulse period
     *
     * @param bank the specific bank (0-2, or 3-5)to get
     * @param pulsePeriod_us pulse period (in microseconds)for the specified
     * bank
     */
    void SetBankPulsePeriod(ServoHub::Bank bank, int pulsePeriod_us);

    /** Enable the Servo Hub Device. */
    void enable();

    /** Disable the Servo Hub Device */
    void disable();

    /**
     * Use the driver station enable as the method to enable/disable the Servo
     * Hub. This is the default, so you do not need to call this unless you
     * previously called enable() or disable().
     */
    void useDriverStationEnable();

    /**
     * Get the ServoHubSimFaultManager object associated with this Servo
     * Hub Device. This will allow you to set simulated faults on your simulated
     * device and view the Fault Manager in the Sim GUI.
     *
     * @return The ServoHubSimFaultManager object associated with this
     * Servo Hub Device
     */
    ServoHubSimFaultManager GetFaultManager();

private:
    hal::SimDouble m_deviceVoltage;
    hal::SimDouble m_deviceCurrent;
    hal::SimDouble m_servoVoltage;
    hal::SimInt m_bankPulsePeriods[2];

    ServoHub* m_servoHub;
    std::string m_deviceName;
    std::unique_ptr<bool> m_enable;
};

}  // namespace rev::servohub

#endif  // FRC_REVLIB_SRC_MAIN_NATIVE_INCLUDE_REV_SERVOHUBSIM_H_
