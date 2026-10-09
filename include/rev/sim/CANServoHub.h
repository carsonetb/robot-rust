/*
 * Copyright (c) 2024 REV Robotics
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

#include "rev/CANServoHubDriver.h"
#include "rev/CANServoHubParameters.h"
#include "rev/REVLibErrors.h"
#include "rev/REVUtils.h"

extern "C" {

typedef struct c_SIM_ServoHub_Obj* c_SIM_ServoHub_handle;

typedef struct c_SIM_ServoHub_FaultManager_Obj*
    c_SIM_ServoHub_FaultManager_handle;

c_SIM_ServoHub_handle c_SIM_ServoHub_Create(int deviceId);
void c_SIM_ServoHub_Destroy(c_SIM_ServoHub_handle handle);
bool c_SIM_ServoHub_IsSim(c_SIM_ServoHub_handle handle);

c_REVLib_ErrorCode c_SIM_ServoHub_ResetParameters(c_SIM_ServoHub_handle handle);

c_REVLib_ErrorCode c_SIM_ServoHub_SetParameter(
    c_SIM_ServoHub_handle handle, c_ServoHub_ConfigParameter parameter,
    uint32_t value);

float c_SIM_ServoHub_GetDeviceVoltage(c_SIM_ServoHub_handle handle);
float c_SIM_ServoHub_GetDeviceCurrent(c_SIM_ServoHub_handle handle);
float c_SIM_ServoHub_GetServoVoltage(c_SIM_ServoHub_handle handle);

int c_SIM_ServoHub_GetChannelPulseWidth(c_SIM_ServoHub_handle handle,
                                        c_ServoHub_Channel channel);
c_REVLib_ErrorCode c_SIM_ServoHub_SetChannelPulseWidth(
    c_SIM_ServoHub_handle handle, c_ServoHub_Channel channel,
    int pulseWidth_us);

bool c_SIM_ServoHub_GetChannelEnabled(c_SIM_ServoHub_handle handle,
                                      c_ServoHub_Channel channel);
c_REVLib_ErrorCode c_SIM_ServoHub_SetChannelEnabled(
    c_SIM_ServoHub_handle handle, c_ServoHub_Channel channel, bool enabled);

c_REVLib_ErrorCode c_SIM_ServoHub_SetChannelPowered(
    c_SIM_ServoHub_handle handle, c_ServoHub_Channel channel, bool powered);

c_REVLib_ErrorCode c_SIM_ServoHub_SetBankPulsePeriod(
    c_SIM_ServoHub_handle handle, c_ServoHub_Bank bank, int pulsePeriod_us);

c_REVLib_ErrorCode c_SIM_ServoHub_GetChannelPulseRange(
    c_SIM_ServoHub_handle handle, c_ServoHub_Channel channel,
    c_ServoHub_ChannelPulseRange* pulseRange);

c_REVLib_ErrorCode c_SIM_ServoHub_GetChannelDisableBehavior(
    c_SIM_ServoHub_handle handle, c_ServoHub_Channel channel,
    bool* disableBehavior);

c_SIM_ServoHub_FaultManager_handle c_SIM_ServoHub_GetOrCreateSimFaultManager(
    c_SIM_ServoHub_handle handle);

bool c_SIM_ServoHub_GetSimFaultManagerExists(c_SIM_ServoHub_handle handle);
void c_SIM_ServoHub_SetRawFrameFromSimFaults(
    c_SIM_ServoHub_FaultManager_handle handle,
    c_ServoHub_PeriodicStatus1* rawFrame);
void c_SIM_ServoHub_ClearSimFaults(c_SIM_ServoHub_FaultManager_handle handle);

}  // extern "C"
