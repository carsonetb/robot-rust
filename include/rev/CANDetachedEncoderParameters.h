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

/*
 * This file is auto-generated. Do NOT modify it directly.
 * See https://github.com/REVrobotics/SparkParameters
 */

#pragma once

#include <stdint.h>

#include "rev/CANCommonParameters.h"

#ifdef __cplusplus
extern "C" {
#endif

static const uint32_t c_Detached_NumParameters = 16;

typedef enum {
    c_Detached_kEncoderAverageDepth = 0,
    c_Detached_kEncoderInverted = 1,
    c_Detached_kPositionConversionFactor = 2,
    c_Detached_kVelocityConversionFactor = 3,
    c_Detached_kDutyCycleZeroCentered = 4,
    c_Detached_kDutyCycleAverageDepth = 5,
    c_Detached_kDutyCycleOffset = 6,
    c_Detached_kStatus0Period = 7,
    c_Detached_kStatus1Period = 8,
    c_Detached_kStatus2Period = 9,
    c_Detached_kStatus3Period = 10,
    c_Detached_kStatus4Period = 11,
    c_Detached_kAngleConversionFactor = 12,
    c_Detached_kDutyCycleStartPulseUs = 13,
    c_Detached_kDutyCycleEndPulseUs = 14,
    c_Detached_kDutyCyclePeriodUs = 15,
} c_Detached_ConfigParameter;

static const c_Detached_ConfigParameter c_Detached_kUnused =
    (c_Detached_ConfigParameter)(-1);

c_REVLib_ParameterType c_Detached_GetParameterType(
    c_Detached_ConfigParameter parameterId);

uint32_t c_Detached_GetParameterDefaultValue(c_Detached_ConfigParameter parameterId);

const char* c_Detached_GetParameterName(c_Detached_ConfigParameter parameterId);

// For debugging purposes, to verify internal state.
c_Detached_ConfigParameter c_Detached_GetConfigParameter(
    c_Detached_ConfigParameter parameterId);

#ifdef __cplusplus
}  // extern "C"
#endif
