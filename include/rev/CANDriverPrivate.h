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

#include <mutex>
#include <set>
#include <span>
#include <string_view>

#include "rev/CANSparkDriver.h"
#include "rev/REVCommon.h"

class CAN_ExistingDeviceIds {
public:
    CAN_ExistingDeviceIds() : m_existingDeviceIds() {}

    CAN_ExistingDeviceIds(const CAN_ExistingDeviceIds&) = delete;
    CAN_ExistingDeviceIds& operator=(const CAN_ExistingDeviceIds&) = delete;
    CAN_ExistingDeviceIds(CAN_ExistingDeviceIds&&) = delete;
    CAN_ExistingDeviceIds& operator=(CAN_ExistingDeviceIds&&) = delete;

    bool InsertDevice(uint8_t deviceId) {
        std::scoped_lock<std::mutex> lock{m_mutex};
        return m_existingDeviceIds.insert(deviceId).second;
    }

    bool ContainsDevice(uint8_t deviceId) {
        std::scoped_lock<std::mutex> lock{m_mutex};
        return m_existingDeviceIds.count(deviceId) > 0;
    }

    void RemoveDevice(uint8_t deviceId) {
        std::scoped_lock<std::mutex> lock{m_mutex};
        m_existingDeviceIds.erase(deviceId);
    }

private:
    std::mutex m_mutex;
    std::set<uint8_t> m_existingDeviceIds;
};

enum { kMinCANId = 0, kMaxCANId = 62 };
static inline bool CAN_IsValidId(int deviceId) {
    return (deviceId >= kMinCANId) && (deviceId <= kMaxCANId);
}

constexpr int32_t kBaseDefaultControlFramePeriod_ms{20};

constexpr int32_t kBaseDefaultPeriodicFrameTimeout_ms{500};
constexpr float kPeriodicTimeoutMultiplier{2.1f};  // Nyquist

constexpr int32_t kBaseDefaultStatus0Period_ms{10};
constexpr int32_t kBaseDefaultStatus1Period_ms{250};
constexpr int32_t kBaseDefaultStatus2Period_ms{20};
constexpr int32_t kBaseDefaultStatus3Period_ms{20};
constexpr int32_t kBaseDefaultStatus4Period_ms{20};
constexpr int32_t kBaseDefaultStatus5Period_ms{20};
constexpr int32_t kBaseDefaultStatus6Period_ms{20};
constexpr int32_t kBaseDefaultStatus7Period_ms{20};
constexpr int32_t kBaseDefaultStatus8Period_ms{20};
constexpr int32_t kBaseDefaultStatus9Period_ms{20};

struct c_BaseCAN_Obj {
    c_BaseCAN_Obj(REVDevice deviceType, int deviceId,
                  c_REVLib_ErrorCode* lastErrors, size_t maxErrors);

    c_BaseCAN_Obj() = delete;
    virtual ~c_BaseCAN_Obj() = default;

    c_REVLib_ErrorCode* m_lastErrors;
    size_t m_MaxErrors;

    REVDevice m_deviceType{UnknownREVDevice};
    int m_deviceId{-1};

    static int32_t m_canTimeout_ms;
    static int32_t m_canMaxRetryCount;

    int32_t m_controlFramePeriod_ms{kBaseDefaultControlFramePeriod_ms};

    int32_t m_periodicFrameTimeout_ms{kBaseDefaultPeriodicFrameTimeout_ms};

    int32_t m_status0Period_ms{kBaseDefaultStatus0Period_ms};
    int32_t m_status1Period_ms{kBaseDefaultStatus1Period_ms};
    int32_t m_status2Period_ms{kBaseDefaultStatus2Period_ms};
    int32_t m_status3Period_ms{kBaseDefaultStatus3Period_ms};
    int32_t m_status4Period_ms{kBaseDefaultStatus4Period_ms};
    int32_t m_status5Period_ms{kBaseDefaultStatus5Period_ms};
    int32_t m_status6Period_ms{kBaseDefaultStatus6Period_ms};
    int32_t m_status7Period_ms{kBaseDefaultStatus7Period_ms};
    int32_t m_status8Period_ms{kBaseDefaultStatus8Period_ms};
    int32_t m_status9Period_ms{kBaseDefaultStatus9Period_ms};

    static void SetBaseDefaultCanTimeoutMs(int32_t timeout_ms);
    static void SetBaseDefaultCanRetries(int32_t retries);
};

///////////////////////////////////
// Free functions:

void REVLib_SendError(c_BaseCAN_handle handle, c_REVLib_ErrorCode error);
void REVLib_SendErrorText(c_BaseCAN_handle handle, c_REVLib_ErrorCode error,
                          const std::string_view context = "");
void REVLib_SetLastError(c_BaseCAN_handle handle, c_REVLib_ErrorCode error);
c_REVLib_ErrorCode REVLib_HALErrorCheck(c_BaseCAN_handle handle, int32_t status,
                                        const std::string_view context = "");

c_REVLib_ErrorCode REVLib_ReadCANPacketTimeout(
    c_BaseCAN_handle handle, std::span<uint8_t> packet, uint64_t& timestamp,
    int32_t frameId, int32_t timeoutPeriod_ms, int32_t expectedLength,
    const std::string_view context);

c_REVLib_ErrorCode REVLib_WriteCANPacket(c_BaseCAN_handle handle,
                                         std::span<const uint8_t> packet,
                                         int32_t frameId,
                                         const std::string_view context = "");

c_REVLib_ErrorCode REVLib_WriteCANPacketRepeating(
    c_BaseCAN_handle handle, std::span<const uint8_t> packet, int32_t frameId,
    const std::string_view context = "");

c_REVLib_ErrorCode REVLib_StopCANPacketRepeating(
    c_BaseCAN_handle handle, int32_t frameId,
    const std::string_view context = "");

c_REVLib_ErrorCode REVLib_WriteBroadcastCANPacket(
    std::span<const uint8_t> packet, int32_t frameId,
    const std::string_view context = "");

c_REVLib_ErrorCode REVLib_WriteAndReadCANPacket(
    c_BaseCAN_handle handle, std::span<const uint8_t> writePacket,
    int32_t writeFrameId, std::span<uint8_t> readPacket, int32_t readFrameId,
    int32_t readExpectedLength, const std::string_view context = "");

c_REVLib_ErrorCode REVLib_WriteAndReadCANPacketWithReadTimeout(
    c_BaseCAN_handle handle, std::span<const uint8_t> writePacket,
    int32_t writeFrameId, std::span<uint8_t> readPacket, int32_t readFrameId,
    int32_t readExpectedLength, int32_t customReadTimeout_ms,
    const std::string_view context);

c_REVLib_ErrorCode REVLib_WriteAndReadRtrCANPacket(
    c_BaseCAN_handle handle, std::span<uint8_t> readPacket, int32_t frameId,
    int32_t expectedLength, const std::string_view context = "");

void REVLib_SendLowLevelError(int32_t errorCode, const std::string_view details,
                              bool alsoStdout = false);
void REVLib_SendLowLevelWarning(int32_t errorCode,
                                const std::string_view details,
                                bool alsoStdout = false);

extern "C" {
void REVLib_SetBaseDefaultCanTimeoutMs(int32_t timeout_ms);
void REVLIB_SetBaseDefaultCanRetries(int32_t retries);
}  // extern "C"
