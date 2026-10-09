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

namespace rev::servohub {

enum ServoHubParameter : uint8_t {
    kChannel0_MinPulseWidth = 0,  // uint32_t
    kChannel0_CenterPulseWidth,   // uint32_t
    kChannel0_MaxPulseWidth,      // uint32_t
    kChannel1_MinPulseWidth,      // uint32_t
    kChannel1_CenterPulseWidth,   // uint32_t
    kChannel1_MaxPulseWidth,      // uint32_t
    kChannel2_MinPulseWidth,      // uint32_t
    kChannel2_CenterPulseWidth,   // uint32_t
    kChannel2_MaxPulseWidth,      // uint32_t
    kChannel3_MinPulseWidth,      // uint32_t
    kChannel3_CenterPulseWidth,   // uint32_t
    kChannel3_MaxPulseWidth,      // uint32_t
    kChannel4_MinPulseWidth,      // uint32_t
    kChannel4_CenterPulseWidth,   // uint32_t
    kChannel4_MaxPulseWidth,      // uint32_t
    kChannel5_MinPulseWidth,      // uint32_t
    kChannel5_CenterPulseWidth,   // uint32_t
    kChannel5_MaxPulseWidth,      // uint32_t
    kChannel0_DisableBehavior,    // bool
    kChannel1_DisableBehavior,    // bool
    kChannel2_DisableBehavior,    // bool
    kChannel3_DisableBehavior,    // bool
    kChannel4_DisableBehavior,    // bool
    kChannel5_DisableBehavior     // bool
};

}  // namespace rev::servohub
