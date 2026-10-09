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

namespace rev::detached {

enum DetachedEncoderParameter : uint8_t {
    kEncoderAverageDepth = 0,  // uint32_t
    kEncoderInverted = 1,  // bool
    kPositionConversionFactor = 2,  // float
    kVelocityConversionFactor = 3,  // float
    kDutyCycleZeroCentered = 4,  // bool
    kDutyCycleAverageDepth = 5,  // uint32_t
    kDutyCycleOffset = 6,  // float
    kStatus0Period = 7,  // uint32_t
    kStatus1Period = 8,  // uint32_t
    kStatus2Period = 9,  // uint32_t
    kStatus3Period = 10,  // uint32_t
    kStatus4Period = 11,  // uint32_t
    kAngleConversionFactor = 12,  // float
    kDutyCycleStartPulseUs = 13,  // float
    kDutyCycleEndPulseUs = 14,  // float
    kDutyCyclePeriodUs = 15,  // float
};

}  // namespace rev::detached
