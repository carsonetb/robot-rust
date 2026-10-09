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
#include "rev/config/ClosedLoopConfig.h"
#include "rev/config/FeedForwardConfigAccessor.h"
#include "rev/config/MAXMotionConfigAccessor.h"

namespace rev::spark {

class ClosedLoopConfigAccessor {
    friend class SparkBaseConfigAccessor;

protected:
    explicit ClosedLoopConfigAccessor(void* sparkHandle);

private:
    void* m_sparkHandle;

public:
    MAXMotionConfigAccessor maxMotion;
    FeedForwardConfigAccessor feedForward;

    double GetP(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    double GetI(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    double GetD(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    /**
     * @deprecated Use FeedForwardConfigAccessor::GetV instead
     */
    [[deprecated]] double GetFF(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    double GetDFilter(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    double GetIZone(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    double GetMinOutput(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    double GetMaxOutput(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    double GetMaxIAccumulation(ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    double GetAllowedClosedLoopError(
        ClosedLoopSlot slot = ClosedLoopSlot::kSlot0);
    bool GetPositionWrappingEnabled();
    double GetPositionWrappingMinInput();
    double GetPositionWrappingMaxInput();
    FeedbackSensor GetFeedbackSensor();
};

}  // namespace rev::spark
