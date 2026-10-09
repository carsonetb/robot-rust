/*
 * Copyright (c) 2025-2026 REV Robotics
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

namespace rev::detached {

class DetachedEncoderLowLevel {
public:
    /**
     * Closes the Detached Encoder
     */
    virtual ~DetachedEncoderLowLevel();

    /**
     * Get the configured Device ID of the Detached encoder.
     *
     * @return int device ID
     *
     */
    int GetDeviceId() const;

    enum class EncoderModel {
        kUnknown = 0,
        kMAXSplineEncoder = 1,
    };

    /**
     * Get the Model of this Detached Encoder Device. Useful for determining
     * if this is a MAXSpline, or other device
     *
     * @return the model of this encoder
     */
    EncoderModel GetEncoderModel() const;

    struct FirmwareVersion {
        int year;
        int minor;
        int fix;
        int prerelease;
        int hardwareMajor;
        int hardwareMinor;
    };

    /**
     * Get the firmware version of the detached encoder.
     *
     * @return Firmware version object
     */
    FirmwareVersion GetFirmwareVersion() const;

    struct PeriodicStatus0 {
        EncoderModel model;
    };

    /**
     * Get Periodic Status 0 for the Detached Encoder.
     *
     * @return PeriodicStatus0 Periodic status 0
     *
     */
    PeriodicStatus0 GetPeriodicStatus0() const;

    struct PeriodicStatus1 {
        bool unexpectedFault;
        bool hasResetFault;
        bool canTxFault;
        bool canRxFault;
        bool eepromFault;
        bool stickyUnexpectedFault;
        bool stickyHasResetFault;
        bool stickyCanTxFault;
        bool stickyCanRxFault;
        bool stickyEepromFault;
    };

    /**
     * Get Periodic Status 1 for the Detached Encoder.
     *
     * @return PeriodicStatus1 Periodic status 1
     *
     */
    PeriodicStatus1 GetPeriodicStatus1() const;

    struct PeriodicStatus2 {
        float rawAngle;
        float angle;
    };

    /**
     * Get Periodic Status 2 for the Detached Encoder.
     *
     * @return PeriodicStatus2 Periodic status 2
     *
     */
    PeriodicStatus2 GetPeriodicStatus2() const;

    struct PeriodicStatus3 {
        float position;
    };

    /**
     * Get Periodic Status 3 for the Detached Encoder.
     *
     * @return PeriodicStatus3 Periodic status 3
     *
     */
    PeriodicStatus3 GetPeriodicStatus3() const;

    struct PeriodicStatus4 {
        float velocity;
    };

    /**
     * Get Periodic Status 4 for the Detached Encoder.
     *
     * @return PeriodicStatus4 Periodic status 4
     *
     */
    PeriodicStatus4 GetPeriodicStatus4() const;

    /**
     * Create the sim gui Fault Manager for this Detached Encoder device
     */
    void CreateSimFaultManager();

protected:
    explicit DetachedEncoderLowLevel(int deviceID, EncoderModel model);

    // Opaque pointer to underlying driver.
    void* m_detachedEncoderHandle{nullptr};

private:
    int m_deviceID;
};

}  // namespace rev::detached
