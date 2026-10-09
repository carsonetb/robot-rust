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

#include <array>

#include "rev/CANCommonParameters.h"

extern "C" {

typedef enum {
    c_ServoHub_kChannel0_MinPulseWidth = 0,
    c_ServoHub_kChannel0_CenterPulseWidth = 1,
    c_ServoHub_kChannel0_MaxPulseWidth = 2,
    c_ServoHub_kChannel1_MinPulseWidth = 3,
    c_ServoHub_kChannel1_CenterPulseWidth = 4,
    c_ServoHub_kChannel1_MaxPulseWidth = 5,
    c_ServoHub_kChannel2_MinPulseWidth = 6,
    c_ServoHub_kChannel2_CenterPulseWidth = 7,
    c_ServoHub_kChannel2_MaxPulseWidth = 8,
    c_ServoHub_kChannel3_MinPulseWidth = 9,
    c_ServoHub_kChannel3_CenterPulseWidth = 10,
    c_ServoHub_kChannel3_MaxPulseWidth = 11,
    c_ServoHub_kChannel4_MinPulseWidth = 12,
    c_ServoHub_kChannel4_CenterPulseWidth = 13,
    c_ServoHub_kChannel4_MaxPulseWidth = 14,
    c_ServoHub_kChannel5_MinPulseWidth = 15,
    c_ServoHub_kChannel5_CenterPulseWidth = 16,
    c_ServoHub_kChannel5_MaxPulseWidth = 17,
    c_ServoHub_kChannel0_DisableBehavior = 18,
    c_ServoHub_kChannel1_DisableBehavior = 19,
    c_ServoHub_kChannel2_DisableBehavior = 20,
    c_ServoHub_kChannel3_DisableBehavior = 21,
    c_ServoHub_kChannel4_DisableBehavior = 22,
    c_ServoHub_kChannel5_DisableBehavior = 23,
    c_ServoHub_kNumConfigParameters
} c_ServoHub_ConfigParameter;

struct parameter_table_entry_t {
    c_ServoHub_ConfigParameter id;
    c_REVLib_ParameterType type;
    uint32_t defaultValue;
};

static const std::array<parameter_table_entry_t,
                        c_ServoHub_kNumConfigParameters>
    s_ServoHub_ParameterTable{
        {{c_ServoHub_kChannel0_MinPulseWidth, c_REVLib_kUint32, 500u},
         {c_ServoHub_kChannel0_CenterPulseWidth, c_REVLib_kUint32, 1500u},
         {c_ServoHub_kChannel0_MaxPulseWidth, c_REVLib_kUint32, 2500u},
         {c_ServoHub_kChannel1_MinPulseWidth, c_REVLib_kUint32, 500u},
         {c_ServoHub_kChannel1_CenterPulseWidth, c_REVLib_kUint32, 1500u},
         {c_ServoHub_kChannel1_MaxPulseWidth, c_REVLib_kUint32, 2500u},
         {c_ServoHub_kChannel2_MinPulseWidth, c_REVLib_kUint32, 500u},
         {c_ServoHub_kChannel2_CenterPulseWidth, c_REVLib_kUint32, 1500u},
         {c_ServoHub_kChannel2_MaxPulseWidth, c_REVLib_kUint32, 2500u},
         {c_ServoHub_kChannel3_MinPulseWidth, c_REVLib_kUint32, 500u},
         {c_ServoHub_kChannel3_CenterPulseWidth, c_REVLib_kUint32, 1500u},
         {c_ServoHub_kChannel3_MaxPulseWidth, c_REVLib_kUint32, 2500u},
         {c_ServoHub_kChannel4_MinPulseWidth, c_REVLib_kUint32, 500u},
         {c_ServoHub_kChannel4_CenterPulseWidth, c_REVLib_kUint32, 1500u},
         {c_ServoHub_kChannel4_MaxPulseWidth, c_REVLib_kUint32, 2500u},
         {c_ServoHub_kChannel5_MinPulseWidth, c_REVLib_kUint32, 500u},
         {c_ServoHub_kChannel5_CenterPulseWidth, c_REVLib_kUint32, 1500u},
         {c_ServoHub_kChannel5_MaxPulseWidth, c_REVLib_kUint32, 2500u},
         {c_ServoHub_kChannel0_DisableBehavior, c_REVLib_kBool,
          static_cast<uint32_t>(true)},
         {c_ServoHub_kChannel1_DisableBehavior, c_REVLib_kBool,
          static_cast<uint32_t>(true)},
         {c_ServoHub_kChannel2_DisableBehavior, c_REVLib_kBool,
          static_cast<uint32_t>(true)},
         {c_ServoHub_kChannel3_DisableBehavior, c_REVLib_kBool,
          static_cast<uint32_t>(true)},
         {c_ServoHub_kChannel4_DisableBehavior, c_REVLib_kBool,
          static_cast<uint32_t>(true)},
         {c_ServoHub_kChannel5_DisableBehavior, c_REVLib_kBool,
          static_cast<uint32_t>(true)}}};

c_REVLib_ParameterType c_ServoHub_GetParameterType(
    c_ServoHub_ConfigParameter parameterId);

}  // extern "C"
