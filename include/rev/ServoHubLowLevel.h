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

#include <stdint.h>

#include <string>

#include "rev/REVLibError.h"

namespace rev::servohub {

class ServoHubLowLevel {
    //     friend class ServoChannelSim;
    friend class ServoHubSimFaultManager;

public:
    /**
     * Closes the ServoHub
     */
    virtual ~ServoHubLowLevel();

    /**
     * Get the configured Device ID of the ServoHub.
     *
     * @return int device ID
     */
    int GetDeviceId() const;

    struct FirmwareVersion {
        uint8_t firmwareFix;
        uint8_t firmwareMinor;
        uint8_t firmwareYear;
        uint8_t hardwareMinor;
        uint8_t hardwareMajor;
    };
    /**
     * Get the firmware version of the ServoHub.
     *
     * @return Firmware version represented in the struct
     */
    FirmwareVersion GetFirmwareVersion() const;

    /**
     * Get the firmware version of the ServoHub as a string.
     *
     * @return std::string Human readable firmware version string
     */
    std::string GetFirmwareVersionString() const;

    /**
     * Set the amount of time to wait for a periodic status frame before
     * returning a timeout error. This timeout will apply to all periodic status
     * frames for the ServoHub servo controller.
     *
     * To prevent invalid timeout errors, the minimum timeout for a given
     * periodic status is 2.1 times its period. To use the minimum timeout for
     * all status frames, set timeout_ms to 0.
     *
     * The default timeout is 500ms.
     *
     * @param timeout_ms The timeout in milliseconds
     */
    void SetPeriodicFrameTimeout(int timeout_ms);

    /**
     * Sets the timeout duration for waiting for CAN responses from the device.
     *
     * @param timeout_ms The timeout in milliseconds.
     * @return REVLibError::kOk if successful
     */
    REVLibError SetCANTimeout(int timeout_ms);

    /**
     * Set the maximum number of times to retry an RTR CAN frame. This applies
     * to calls such as GetFirmwareVersion where a request is made to the
     * ServoHub and a response is expected. Anytime sending the request or
     * receiving the response fails, it will retry the request a number of
     * times, no more than the value set by this method. If an attempt succeeds,
     * it will immediately return. The minimum number of retries is 0, where
     * only a single attempt will be made and will return regardless of success
     * or failure.
     *
     * The default maximum is 5 retries.
     *
     * @param numRetries The maximum number of retries
     */
    void SetCANMaxRetries(int numRetries);

    /**
     * Set the control frame send period for the native CAN Send thread.
     *
     * @param period_ms The send period in milliseconds between 1ms and 100ms or
     * set to 0 to disable periodic sends.
     */
    void SetControlFramePeriodMs(int period_ms);

    /**
     * Set the control frame send period for the native CAN Send thread.
     *
     * @return int The send period in milliseconds.
     */
    int GetControlFramePeriodMs() const;

    enum class CommunicationMode { kNone = 0, kCAN = 1, kRS_485 = 2 };

    struct PeriodicStatus0 {
        double voltage;
        double servoVoltage;
        double deviceCurrent;
        bool primaryHeartbeatLock;
        bool systemEnabled;
        CommunicationMode communicationMode;
        bool programmingEnabled;
        bool activelyProgramming;
        uint64_t timestamp;
    };
    PeriodicStatus0 GetPeriodicStatus0() const;

    struct PeriodicStatus1 {
        bool regulatorPowerGoodFault;
        bool brownout;
        bool canWarning;
        bool canBusOff;
        bool hardwareFault;
        bool firmwareFault;
        bool hasReset;
        bool channel0Overcurrent;
        bool channel1Overcurrent;
        bool channel2Overcurrent;
        bool channel3Overcurrent;
        bool channel4Overcurrent;
        bool channel5Overcurrent;
        bool stickyRegulatorPowerGoodFault;
        bool stickyBrownout;
        bool stickyCanWarning;
        bool stickyCanBusOff;
        bool stickyHardwareFault;
        bool stickyFirmwareFault;
        bool stickyHasReset;
        bool stickyChannel0Overcurrent;
        bool stickyChannel1Overcurrent;
        bool stickyChannel2Overcurrent;
        bool stickyChannel3Overcurrent;
        bool stickyChannel4Overcurrent;
        bool stickyChannel5Overcurrent;
        uint64_t timestamp;
    };
    PeriodicStatus1 GetPeriodicStatus1() const;

    struct PeriodicStatus2 {
        uint16_t channel0PulseWidth;
        uint16_t channel1PulseWidth;
        uint16_t channel2PulseWidth;
        bool channel0Enabled;
        bool channel1Enabled;
        bool channel2Enabled;
        bool channel0OutOfRange;
        bool channel1OutOfRange;
        bool channel2OutOfRange;
        uint64_t timestamp;
    };
    PeriodicStatus2 GetPeriodicStatus2() const;

    struct PeriodicStatus3 {
        uint16_t channel3PulseWidth;
        uint16_t channel4PulseWidth;
        uint16_t channel5PulseWidth;
        bool channel3Enabled;
        bool channel4Enabled;
        bool channel5Enabled;
        bool channel3OutOfRange;
        bool channel4OutOfRange;
        bool channel5OutOfRange;
        uint64_t timestamp;
    };
    PeriodicStatus3 GetPeriodicStatus3() const;

    struct PeriodicStatus4 {
        double channel0Current;
        double channel1Current;
        double channel2Current;
        double channel3Current;
        double channel4Current;
        double channel5Current;
        uint64_t timestamp;
    };
    PeriodicStatus4 GetPeriodicStatus4() const;

    /**
     * Create the sim gui Fault Manager for this Servo Hub device
     */
    void CreateSimFaultManager();

protected:
    explicit ServoHubLowLevel(int deviceID);

    // The type is void* because we don't want to expose c_ServoHub_handle to
    // the consumers of this header file
    void* m_servoHubHandle{nullptr};

private:
    int m_deviceID;
};

}  // namespace rev::servohub
