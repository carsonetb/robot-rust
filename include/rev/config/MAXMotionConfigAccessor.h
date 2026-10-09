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

#include "rev/ClosedLoopTypes.h"
#include "rev/config/MAXMotionConfig.h"

namespace rev::spark {

class MAXMotionConfigAccessor {
    friend class ClosedLoopConfigAccessor;

protected:
    explicit MAXMotionConfigAccessor(void* sparkHandle);

private:
    void* m_sparkHandle;

public:
    /**
     * @deprecated Use GetCruiseVelocity instead
     */
    [[deprecated("Use GetCruiseVelocity instead")]] double GetMaxVelocity(
        ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    double GetMaxAcceleration(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    double GetCruiseVelocity(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    /**
     * @deprecated Use GetAllowedProfileError instead
     */
    [[deprecated("Use GetAllowedProfileError instead")]] double
    GetAllowedClosedLoopError(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    double GetAllowedProfileError(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    MAXMotionConfig::MAXMotionPositionMode GetPositionMode(
        ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
};

}  // namespace rev::spark
