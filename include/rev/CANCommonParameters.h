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

extern "C" {

typedef enum {
    c_REVLib_kUnused = 0,
    c_REVLib_kInt32 = 1,
    c_REVLib_kUint32 = 2,
    c_REVLib_kFloat32 = 3,
    c_REVLib_kBool = 4
} c_REVLib_ParameterType;

void c_REVLib_FlattenParameterInt32(uint8_t parameterId, int32_t value,
                                    char* flattenedString,
                                    uint32_t maxStringLength);

void c_REVLib_FlattenParameterUint32(uint8_t parameterId, uint32_t value,
                                     char* flattenedString,
                                     uint32_t maxStringLength);

void c_REVLib_FlattenParameterFloat(uint8_t parameterId, float value,
                                    char* flattenedString,
                                    uint32_t maxStringLength);

void c_REVLib_FlattenParameterBool(uint8_t parameterId, bool value,
                                   char* flattenedString,
                                   uint32_t maxStringLength);
}  // extern "C"
