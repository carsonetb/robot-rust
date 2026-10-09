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

#include "rev/REVCommon.h"
#include "rev/REVLibErrors.h"

extern "C" {

typedef struct c_ServoHub_Obj* c_ServoHub_handle;

typedef struct {
    uint8_t fwFix;
    uint8_t fwMinor;
    uint8_t fwYear;
    uint8_t hwMinor;
    uint8_t hwMajor;
    uint32_t reserved;
} c_ServoHub_FirmwareVersion;

typedef struct {
    bool channel0_programming_enabled;
    bool channel1_programming_enabled;
    bool channel2_programming_enabled;
    bool channel3_programming_enabled;
    bool channel4_programming_enabled;
    bool channel5_programming_enabled;
} c_ServoHub_ProgrammingEnableStates;

typedef enum {
    c_ServoHub_FaultOffset_kRegulatorPowerGood = 0,
    c_ServoHub_FaultOffset_kHardware = 1,
    c_ServoHub_FaultOffset_kFirmware = 2,
    c_servoHub_FaultOffset_kLowBattery = 3
} c_ServoHub_FaultOffset;

typedef enum {
    c_ServoHub_FaultMask_kRegulatorPowerGood =
        (0x1u << c_ServoHub_FaultOffset_kRegulatorPowerGood),
    c_ServoHub_FaultMask_kHardware = (0x1u << c_ServoHub_FaultOffset_kHardware),
    c_ServoHub_FaultMask_kFirmware = (0x1u << c_ServoHub_FaultOffset_kFirmware),
    c_ServoHub_FaultMask_kLowBattery =
        (0x1u << c_servoHub_FaultOffset_kLowBattery),
} c_ServoHub_FaultMask;

typedef enum {
    c_ServoHub_WarningOffset_kBrownout = 0,
    c_ServoHub_WarningOffset_kCanWarning = 1,
    c_ServoHub_WarningOffset_kCanBusOff = 2,
    c_ServoHub_WarningOffset_kHasReset = 3,
    c_ServoHub_WarningOffset_kChannel0Overcurrent = 4,
    c_ServoHub_WarningOffset_kChannel1Overcurrent = 5,
    c_ServoHub_WarningOffset_kChannel2Overcurrent = 6,
    c_ServoHub_WarningOffset_kChannel3Overcurrent = 7,
    c_ServoHub_WarningOffset_kChannel4Overcurrent = 8,
    c_ServoHub_WarningOffset_kChannel5Overcurrent = 9,
} c_ServoHub_WarningOffset;

typedef enum {
    c_ServoHub_WarningMask_kBrownout =
        (0x1u << c_ServoHub_WarningOffset_kBrownout),
    c_ServoHub_WarningMask_kCanWarning =
        (0x1u << c_ServoHub_WarningOffset_kCanWarning),
    c_ServoHub_WarningMask_kCanBusOff =
        (0x1u << c_ServoHub_WarningOffset_kCanBusOff),
    c_ServoHub_WarningMask_kHasReset =
        (0x1u << c_ServoHub_WarningOffset_kHasReset),
    c_ServoHub_WarningMask_kChannel0Overcurrent =
        (0x1u << c_ServoHub_WarningOffset_kChannel0Overcurrent),
    c_ServoHub_WarningMask_kChannel1Overcurrent =
        (0x1u << c_ServoHub_WarningOffset_kChannel1Overcurrent),
    c_ServoHub_WarningMask_kChannel2Overcurrent =
        (0x1u << c_ServoHub_WarningOffset_kChannel2Overcurrent),
    c_ServoHub_WarningMask_kChannel3Overcurrent =
        (0x1u << c_ServoHub_WarningOffset_kChannel3Overcurrent),
    c_ServoHub_WarningMask_kChannel4Overcurrent =
        (0x1u << c_ServoHub_WarningOffset_kChannel4Overcurrent),
    c_ServoHub_WarningMask_kChannel5Overcurrent =
        (0x1u << c_ServoHub_WarningOffset_kChannel5Overcurrent),
} c_ServoHub_WarningMask;

typedef struct {
    float voltage;
    float servoVoltage;
    float deviceCurrent;
    uint8_t primaryHeartbeatLock;
    uint8_t systemEnabled;
    uint8_t communicationMode;  // 0: None, 1: CAN, 2: RS-485
    uint8_t programmingEnabled;
    uint8_t activelyProgramming;
    uint8_t reserved;
    uint64_t timestamp;
} c_ServoHub_PeriodicStatus0;

typedef struct {
    uint8_t regulatorPowerGoodFault;
    uint8_t brownout;
    uint8_t canWarning;
    uint8_t canBusOff;
    uint8_t hardwareFault;
    uint8_t firmwareFault;
    uint8_t hasReset;
    uint8_t lowBatteryFault;
    uint8_t channel0Overcurrent;
    uint8_t channel1Overcurrent;
    uint8_t channel2Overcurrent;
    uint8_t channel3Overcurrent;
    uint8_t channel4Overcurrent;
    uint8_t channel5Overcurrent;
    uint8_t stickyRegulatorPowerGoodFault;
    uint8_t stickyBrownout;
    uint8_t stickyCanWarning;
    uint8_t stickyCanBusOff;
    uint8_t stickyHardwareFault;
    uint8_t stickyFirmwareFault;
    uint8_t stickyHasReset;
    uint8_t stickyLowBatteryFault;
    uint8_t stickyChannel0Overcurrent;
    uint8_t stickyChannel1Overcurrent;
    uint8_t stickyChannel2Overcurrent;
    uint8_t stickyChannel3Overcurrent;
    uint8_t stickyChannel4Overcurrent;
    uint8_t stickyChannel5Overcurrent;
    uint64_t timestamp;
} c_ServoHub_PeriodicStatus1;

typedef struct {
    uint16_t channel0PulseWidth;
    uint16_t channel1PulseWidth;
    uint16_t channel2PulseWidth;
    uint8_t channel0Enabled;
    uint8_t channel1Enabled;
    uint8_t channel2Enabled;
    uint8_t channel0OutOfRange;
    uint8_t channel1OutOfRange;
    uint8_t channel2OutOfRange;
    uint8_t reserved;
    uint64_t timestamp;
} c_ServoHub_PeriodicStatus2;

typedef struct {
    uint16_t channel3PulseWidth;
    uint16_t channel4PulseWidth;
    uint16_t channel5PulseWidth;
    uint8_t channel3Enabled;
    uint8_t channel4Enabled;
    uint8_t channel5Enabled;
    uint8_t channel3OutOfRange;
    uint8_t channel4OutOfRange;
    uint8_t channel5OutOfRange;
    uint8_t reserved;
    uint64_t timestamp;
} c_ServoHub_PeriodicStatus3;

typedef struct {
    float channel0Current;
    float channel1Current;
    float channel2Current;
    float channel3Current;
    float channel4Current;
    float channel5Current;
    uint8_t reserved;
    uint64_t timestamp;
} c_ServoHub_PeriodicStatus4;

typedef enum {
    c_ServoHub_kChannel0 = 0,
    c_ServoHub_kChannel1 = 1,
    c_ServoHub_kChannel2 = 2,
    c_ServoHub_kChannel3 = 3,
    c_ServoHub_kChannel4 = 4,
    c_ServoHub_kChannel5 = 5
} c_ServoHub_Channel;

typedef struct {
    uint16_t minPulse_us;
    uint16_t centerPulse_us;
    uint16_t maxPulse_us;
} c_ServoHub_ChannelPulseRange;

typedef enum c_ServoHub_DriveMode : uint32_t {
    c_ServoHub_kContinuous = 0,
    c_ServoHub_kServo = 1
} c_ServoHub_DriveMode;

typedef struct {
    c_ServoHub_DriveMode driveMode;
    uint32_t leftLimit;
    uint32_t rightLimit;
} c_ServoHub_ServoConfigs;

typedef enum {
    c_ServoHub_kBank0_2 = 0,
    c_ServoHub_kBank3_5 = 1
} c_ServoHub_Bank;

c_REVLib_ErrorCode c_ServoHub_RegisterId(int deviceId);
c_ServoHub_handle c_ServoHub_Create(int deviceId, c_REVLib_ErrorCode* status);
void c_ServoHub_Close(c_ServoHub_handle handle);
void c_ServoHub_Destroy(c_ServoHub_handle handle);

c_REVLib_ErrorCode c_ServoHub_Configure(c_ServoHub_handle handle,
                                        const char* flattenedConfig,
                                        uint8_t resetSafeParameters);

void c_ServoHub_SetPeriodicFrameTimeout(c_ServoHub_handle handle,
                                        int timeout_ms);
c_REVLib_ErrorCode c_ServoHub_SetCANTimeout(c_ServoHub_handle handle,
                                            int timeout_ms);
void c_ServoHub_SetCANMaxRetries(c_ServoHub_handle handle, int numRetries);

void c_ServoHub_SetControlFramePeriod(c_ServoHub_handle handle, int period_ms);
int c_ServoHub_GetControlFramePeriod(c_ServoHub_handle handle);

c_REVLib_APIVersion c_ServoHub_GetAPIVersion(void);
c_REVLib_ErrorCode c_ServoHub_GetFirmwareVersion(
    c_ServoHub_handle handle, c_ServoHub_FirmwareVersion* fwVersion);

c_REVLib_ErrorCode c_ServoHub_GetFaults(c_ServoHub_handle handle,
                                        uint16_t* faults);
c_REVLib_ErrorCode c_ServoHub_GetStickyFaults(c_ServoHub_handle handle,
                                              uint16_t* stickyFaults);
c_REVLib_ErrorCode c_ServoHub_GetWarnings(c_ServoHub_handle handle,
                                          uint16_t* warnings);
c_REVLib_ErrorCode c_ServoHub_GetStickyWarnings(c_ServoHub_handle handle,
                                                uint16_t* stickyWarnings);

c_REVLib_ErrorCode c_ServoHub_GetPeriodicStatus0(
    c_ServoHub_handle handle, c_ServoHub_PeriodicStatus0* rawFrame);
c_REVLib_ErrorCode c_ServoHub_GetPeriodicStatus1(
    c_ServoHub_handle handle, c_ServoHub_PeriodicStatus1* rawFrame);
c_REVLib_ErrorCode c_ServoHub_GetPeriodicStatus2(
    c_ServoHub_handle handle, c_ServoHub_PeriodicStatus2* rawFrame);
c_REVLib_ErrorCode c_ServoHub_GetPeriodicStatus3(
    c_ServoHub_handle handle, c_ServoHub_PeriodicStatus3* rawFrame);
c_REVLib_ErrorCode c_ServoHub_GetPeriodicStatus4(
    c_ServoHub_handle handle, c_ServoHub_PeriodicStatus4* rawFrame);

c_REVLib_ErrorCode c_ServoHub_GetDeviceVoltage(c_ServoHub_handle handle,
                                               float* deviceVoltage);
c_REVLib_ErrorCode c_ServoHub_GetDeviceCurrent(c_ServoHub_handle handle,
                                               float* deviceCurrent);
c_REVLib_ErrorCode c_ServoHub_GetServoVoltage(c_ServoHub_handle handle,
                                              float* servoVoltage);

c_REVLib_ErrorCode c_ServoHub_GetChannelPulseWidth(c_ServoHub_handle handle,
                                                   c_ServoHub_Channel channel,
                                                   int* pulseWidth_us);
c_REVLib_ErrorCode c_ServoHub_GetChannelEnabled(c_ServoHub_handle handle,
                                                c_ServoHub_Channel channel,
                                                bool* enabled);
c_REVLib_ErrorCode c_ServoHub_GetChannelCurrent(c_ServoHub_handle handle,
                                                c_ServoHub_Channel channel,
                                                float* current);
c_REVLib_ErrorCode c_ServoHub_GetChannelPulseRange(
    c_ServoHub_handle handle, c_ServoHub_Channel channel,
    c_ServoHub_ChannelPulseRange* pulseRange_us);
c_REVLib_ErrorCode c_ServoHub_GetChannelDisableBehavior(
    c_ServoHub_handle handle, c_ServoHub_Channel channel,
    bool* disableBehavior);

c_REVLib_ErrorCode c_ServoHub_SetChannelPulseWidth(c_ServoHub_handle handle,
                                                   c_ServoHub_Channel channel,
                                                   int pulseWidth_us);
c_REVLib_ErrorCode c_ServoHub_SetChannelEnabled(c_ServoHub_handle handle,
                                                c_ServoHub_Channel channel,
                                                bool enabled);
c_REVLib_ErrorCode c_ServoHub_SetChannelPowered(c_ServoHub_handle handle,
                                                c_ServoHub_Channel channel,
                                                bool powered);

c_REVLib_ErrorCode c_ServoHub_SetBankPulsePeriod(c_ServoHub_handle handle,
                                                 c_ServoHub_Bank bank,
                                                 int pulsePeriod_us);

c_REVLib_ErrorCode c_ServoHub_SetDriveMode(c_ServoHub_handle handle,
                                           uint8_t channel,
                                           c_ServoHub_DriveMode driveMode);

c_REVLib_ErrorCode c_ServoHub_SetServoLimits(c_ServoHub_handle handle,
                                             uint8_t channel,
                                             uint16_t leftLimit,
                                             uint16_t rightLimit);

c_REVLib_ErrorCode c_ServoHub_EnableProgrammingMode(
    c_ServoHub_handle handle, c_ServoHub_ProgrammingEnableStates enableStates);

c_REVLib_ErrorCode c_ServoHub_ClearFaults(c_ServoHub_handle handle);

// Async functions

c_REVLib_ErrorCode c_ServoHub_ConfigureAsync(c_ServoHub_handle handle,
                                             const char* flattenedConfig,
                                             uint8_t resetSafeParameters);

// Sim helpers

void c_SIM_ServoHub_CreateSimFaultManager(c_ServoHub_handle handle);
}  // extern "C"
