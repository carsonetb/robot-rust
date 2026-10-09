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

#include <stdint.h>

#include "rev/CANDetachedEncoderParameters.h"
#include "rev/REVCommon.h"
#include "rev/REVLibErrors.h"

extern "C" {

typedef struct c_Detached_Obj* c_Detached_handle;

typedef enum {
    c_Detached_kUnknown = 0,
    c_Detached_kMAXSplineEncoder = 1,
} c_Detached_EncoderModel;

typedef struct {
    uint8_t hwMinor;
    uint8_t hwMajor;
    uint8_t fwPrerelease;
    uint8_t fwFix;
    uint8_t fwMinor;
    uint8_t fwYear;
} c_Detached_FirmwareVersion;

typedef enum {
    c_Detached_FaultOffset_kUnexpected = 0,
    c_Detached_FaultOffset_kHasReset = 1,
    c_Detached_FaultOffset_kCanTx = 2,
    c_Detached_FaultOffset_kCanRx = 3,
    c_Detached_FaultOffset_kEeprom = 4
} c_Detached_FaultOffset;

typedef enum {
    c_Detached_FaultMask_kUnexpected =
        (0x1u << c_Detached_FaultOffset_kUnexpected),
    c_Detached_FaultMask_kHasReset = (0x1u << c_Detached_FaultOffset_kHasReset),
    c_Detached_FaultMask_kCanTx = (0x1u << c_Detached_FaultOffset_kCanTx),
    c_Detached_FaultMask_kCanRx = (0x1u << c_Detached_FaultOffset_kCanRx),
    c_Detached_FaultMask_kEeprom = (0x1u << c_Detached_FaultOffset_kEeprom),
} c_Detached_FaultMask;

typedef struct {
    c_Detached_EncoderModel encoderModel;
    uint64_t timestamp;
} c_Detached_PeriodicStatus0;

typedef struct {
    uint8_t unexpectedFault;
    uint8_t hasResetFault;
    uint8_t canTxFault;
    uint8_t canRxFault;
    uint8_t eepromFault;
    uint8_t unexpectedStickyFault;
    uint8_t hasResetStickyFault;
    uint8_t canTxStickyFault;
    uint8_t canRxStickyFault;
    uint8_t eepromStickyFault;
    uint64_t timestamp;
} c_Detached_PeriodicStatus1;

typedef struct {
    float absoluteAngle;
    float rawAbsoluteAngle;
    uint64_t timestamp;
} c_Detached_PeriodicStatus2;

typedef struct {
    float relativePosition;
    uint32_t encoderTimestamp;
    uint64_t timestamp;
} c_Detached_PeriodicStatus3;

typedef struct {
    float encoderVelocity;
    uint32_t encoderTimestamp;
    uint64_t timestamp;
} c_Detached_PeriodicStatus4;

c_REVLib_ErrorCode c_Detached_RegisterId(int deviceId);
c_Detached_handle c_Detached_Create(int deviceId,
                                    c_Detached_EncoderModel unconfirmedModel,
                                    c_REVLib_ErrorCode* status);
/**
 * Logically close the Detached Encoder, stopping any threads it uses, and
 * freeing the id to be used again. No methods should be called after this, but
 * methods that have already started may complete until c_Detached_Destroy is
 * called.
 */
void c_Detached_Close(c_Detached_handle handle);
/**
 * Free any memory used by this handle. No methods can be called on it
 * afterward.
 */
void c_Detached_Destroy(c_Detached_handle handle);

c_REVLib_ErrorCode c_Detached_Configure(c_Detached_handle handle,
                                        const char* flattenedConfig,
                                        uint8_t resetSafeParameters);

void c_Detached_SetPeriodicFrameTimeout(c_Detached_handle handle,
                                        int timeout_ms);
c_REVLib_ErrorCode c_Detached_SetCANTimeout(c_Detached_handle handle,
                                            int timeout_ms);
void c_Detached_SetCANMaxRetries(c_Detached_handle handle, int numRetries);

void c_Detached_SetControlFramePeriod(c_Detached_handle handle, int period_ms);
int c_Detached_GetControlFramePeriod(c_Detached_handle handle);

c_REVLib_APIVersion c_Detached_GetAPIVersion(void);
c_REVLib_ErrorCode c_Detached_GetFirmwareVersion(
    c_Detached_handle handle, c_Detached_FirmwareVersion* fwVersion);

c_REVLib_ErrorCode c_Detached_GetEncoderModel(c_Detached_handle handle,
                                              c_Detached_EncoderModel* model);

c_REVLib_ErrorCode c_Detached_GetFaults(c_Detached_handle handle,
                                        uint16_t* faults);
c_REVLib_ErrorCode c_Detached_GetStickyFaults(c_Detached_handle handle,
                                              uint16_t* stickyFaults);

c_REVLib_ErrorCode c_Detached_GetPeriodicStatus0(
    c_Detached_handle handle, c_Detached_PeriodicStatus0* rawframe);
c_REVLib_ErrorCode c_Detached_GetPeriodicStatus1(
    c_Detached_handle handle, c_Detached_PeriodicStatus1* rawframe);
c_REVLib_ErrorCode c_Detached_GetPeriodicStatus2(
    c_Detached_handle handle, c_Detached_PeriodicStatus2* rawframe);
c_REVLib_ErrorCode c_Detached_GetPeriodicStatus3(
    c_Detached_handle handle, c_Detached_PeriodicStatus3* rawframe);
c_REVLib_ErrorCode c_Detached_GetPeriodicStatus4(
    c_Detached_handle handle, c_Detached_PeriodicStatus4* rawframe);

c_REVLib_ErrorCode c_Detached_GetInverted(c_Detached_handle handle,
                                          bool* inverted);
c_REVLib_ErrorCode c_Detached_GetPositionConversionFactor(
    c_Detached_handle handle, float* positionConversionFactor);
c_REVLib_ErrorCode c_Detached_GetVelocityConversionFactor(
    c_Detached_handle handle, float* velocityConversionFactor);
c_REVLib_ErrorCode c_Detached_GetAngleConversionFactor(
    c_Detached_handle handle, float* angleConversionFactor);

c_REVLib_ErrorCode c_Detached_GetQuadratureAverageDepth(
    c_Detached_handle handle, uint32_t* quadratureAverageDepth);

c_REVLib_ErrorCode c_Detached_GetZeroOffset(c_Detached_handle handle,
                                            float* zeroOffset);
c_REVLib_ErrorCode c_Detached_GetZeroCentered(c_Detached_handle handle,
                                              bool* zeroCentered);
c_REVLib_ErrorCode c_Detached_GetAbsoluteAverageDepth(
    c_Detached_handle handle, uint32_t* absoluteAverageDepth);

c_REVLib_ErrorCode c_Detached_GetStartPulseUs(c_Detached_handle handle,
                                              float* startPulseUs);
c_REVLib_ErrorCode c_Detached_GetEndPulseUs(c_Detached_handle handle,
                                            float* endPulseUs);
c_REVLib_ErrorCode c_Detached_GetAbsolutePeriodUs(c_Detached_handle handle,
                                                  float* periodUs);

c_REVLib_ErrorCode c_Detached_GetStatusPeriod(
    c_Detached_handle handle, c_Detached_ConfigParameter periodId,
    uint32_t* period);

c_REVLib_ErrorCode c_Detached_ClearFaults(c_Detached_handle handle);

// Relative Encoder
c_REVLib_ErrorCode c_Detached_GetEncoderPosition(c_Detached_handle handle,
                                                 float* position);
c_REVLib_ErrorCode c_Detached_SetEncoderPosition(c_Detached_handle handle,
                                                 float position);

c_REVLib_ErrorCode c_Detached_GetEncoderVelocity(c_Detached_handle handle,
                                                 float* velocity);

// Duty Cycle (Absolute)
c_REVLib_ErrorCode c_Detached_GetEncoderAngle(c_Detached_handle handle,
                                              float* angle);
c_REVLib_ErrorCode c_Detached_GetEncoderRawAngle(c_Detached_handle handle,
                                                 float* rawAngle);

void c_SIM_Detached_CreateSimFaultManager(c_Detached_handle handle);

}  // extern "C"
