/*
 * Copyright (c) 2025 REV Robotics
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

#include "rev/CANDetachedEncoderDriver.h"
#include "rev/CANDetachedEncoderParameters.h"
#include "rev/REVLibErrors.h"
#include "rev/REVUtils.h"

extern "C" {

typedef struct c_SIM_Detached_Obj* c_SIM_Detached_handle;

typedef struct c_SIM_Detached_FaultManager_Obj*
    c_SIM_Detached_FaultManager_handle;

c_SIM_Detached_handle c_SIM_Detached_Create(
    int deviceId, c_Detached_EncoderModel encoderModel);
void c_SIM_Detached_Close(c_SIM_Detached_handle handle);
void c_SIM_Detached_Destroy(c_SIM_Detached_handle handle);
bool c_SIM_Detached_IsSim(c_SIM_Detached_handle handle);

c_REVLib_ErrorCode c_SIM_Detached_ResetParameters(c_SIM_Detached_handle handle);

c_REVLib_ErrorCode c_SIM_Detached_SetParameter(
    c_SIM_Detached_handle handle, c_Detached_ConfigParameter parameter,
    uint32_t value);
c_REVLib_ErrorCode c_SIM_Detached_GetParameter(
    c_SIM_Detached_handle handle, c_Detached_ConfigParameter parameterID,
    uint32_t* value);

uint8_t c_SIM_Detached_GetEncoderModel(c_SIM_Detached_handle handle);

c_SIM_Detached_FaultManager_handle c_SIM_Detached_GetOrCreateSimFaultManager(
    c_SIM_Detached_handle handle);

void c_SIM_Detached_SetEncoderPosition(c_SIM_Detached_handle handle,
                                       double position);
double c_SIM_Detached_GetEncoderPosition(c_SIM_Detached_handle handle);
void c_SIM_Detached_SetEncoderVelocity(c_SIM_Detached_handle handle,
                                       double velocity);
double c_SIM_Detached_GetEncoderVelocity(c_SIM_Detached_handle handle);

void c_SIM_Detached_SetEncoderAngle(c_SIM_Detached_handle handle, double angle);
double c_SIM_Detached_GetEncoderAngle(c_SIM_Detached_handle handle);
void c_SIM_Detached_SetEncoderRawAngle(c_SIM_Detached_handle handle,
                                       double rawAngle);
double c_SIM_Detached_GetEncoderRawAngle(c_SIM_Detached_handle handle);
void c_SIM_Detached_SetEncoderZeroOffset(c_SIM_Detached_handle handle,
                                         double offset);
double c_SIM_Detached_GetEncoderZeroOffset(c_SIM_Detached_handle handle);

void c_SIM_Detached_SetEncoderInverted(c_SIM_Detached_handle handle,
                                       bool inverted);
bool c_SIM_Detached_GetEncoderInverted(c_SIM_Detached_handle handle);
void c_SIM_Detached_SetEncoderPositionFactor(c_SIM_Detached_handle handle,
                                             double posFactor);
double c_SIM_Detached_GetEncoderPositionFactor(c_SIM_Detached_handle handle);
void c_SIM_Detached_SetEncoderVelocityFactor(c_SIM_Detached_handle handle,
                                             double velFactor);
double c_SIM_Detached_GetEncoderVelocityFactor(c_SIM_Detached_handle handle);

void c_SIM_Detached_SetRawframeFromSimFaults(
    c_SIM_Detached_FaultManager_handle handle,
    c_Detached_PeriodicStatus1* rawframe);
void c_SIM_Detached_ClearSimFaults(c_SIM_Detached_FaultManager_handle handle);
bool c_SIM_Detached_GetSimFaultManagerExists(c_SIM_Detached_handle handle);

}  // extern "C"
