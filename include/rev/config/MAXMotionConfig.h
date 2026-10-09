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
#include "rev/config/BaseConfig.h"

namespace rev::spark {

class MAXMotionConfig : public BaseConfig {
public:
    enum MAXMotionPositionMode : uint32_t {
        kMAXMotionTrapezoidal = 0,
#if 0  // TODO(rylan): Add when S-curve is supported
        kMAXMotionSCurve = 1
#endif
    };

    MAXMotionConfig() = default;
    ~MAXMotionConfig() override = default;

    MAXMotionConfig(const MAXMotionConfig&) = default;
    MAXMotionConfig& operator=(const MAXMotionConfig&) = delete;
    MAXMotionConfig(MAXMotionConfig&&) noexcept = delete;
    MAXMotionConfig& operator=(MAXMotionConfig&&) noexcept = delete;

    /**
     * Applies settings from another MAXMotionConfig to this one.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The MAXMotionConfig to copy settings from
     * @return The updated MAXMotionConfig for method chaining
     */
    MAXMotionConfig& Apply(MAXMotionConfig& config);

    /**
     * Set the cruise velocity for the MAXMotion mode of the controller for a
     * specific closed loop slot. Natively, the units are in RPM but will be
     * affected by the velocity conversion factor.
     *
     * @param maxVelocity The maximum velocity with the velocity conversion
     * factor applied
     * @param slot The closed loop slot to set the values for
     * @return The modified MAXMotionConfig object for method chaining
     * @deprecated Use MAXMotionConfig::CruiseVelocity instead
     */
    [[deprecated(
        "Use MAXMotionConfig::CruiseVelocity instead")]] MAXMotionConfig&
    MaxVelocity(double maxVelocity, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the cruise velocity for the MAXMotion mode of the controller for a
     * specific closed loop slot. Natively, the units are in RPM but will be
     * affected by the velocity conversion factor.
     *
     * @param maxVelocity The maximum velocity with the velocity conversion
     * factor applied
     * @param slot The closed loop slot to set the values for
     * @return The modified MAXMotionConfig object for method chaining
     */
    MAXMotionConfig& CruiseVelocity(double cruiseVelocity,
                                    ClosedLoopSlot slot = kSlot0);

    /**
     * Set the maximum acceleration for the MAXMotion mode of the controller for
     * a specific closed loop slot. This is the rate at which the velocity will
     * increase until the max velocity is reached. Natively, the units are in
     * RPM per second but will be affected by the velocity conversion factor.
     *
     * @param maxAcceleration The maximum acceleration with the velocity
     * conversion factor applied
     * @param slot The closed loop slot to set the values for
     * @return The modified MAXMotionConfig object for method chaining
     */
    MAXMotionConfig& MaxAcceleration(double maxAcceleration,
                                     ClosedLoopSlot slot = kSlot0);

    /**
     * Set the allowed profile error for the MAXMotion mode of the controller
     * for a specific PID slot. This value is how much deviation from the
     * profile is tolerated before the profile is regenerated. Natively, the
     * units are in rotations but will be affected by the position conversion
     * factor.
     *
     * @param allowedError The allowed error with the position conversion factor
     * applied
     * @param slot The closed loop slot to set the values for
     * @return The modified MAXMotionConfig object for method chaining
     * @deprecated Use MAXMotionConfig::AllowedProfileError instead
     */
    [[deprecated(
        "Use MAXMotionConfig::AllowedProfileError instead")]] MAXMotionConfig&
    AllowedClosedLoopError(double allowedError, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the allowed profile error for the MAXMotion mode of the controller
     * for a specific PID slot. This value is how much deviation from the
     * profile is tolerated before the profile is regenerated. Natively, the
     * units are in rotations but will be affected by the position conversion
     * factor.
     *
     * @param allowedError The allowed error with the position conversion factor
     * applied
     * @param slot The closed loop slot to set the values for
     * @return The modified MAXMotionConfig object for method chaining
     */
    MAXMotionConfig& AllowedProfileError(double allowedError,
                                         ClosedLoopSlot slot = kSlot0);

    /**
     * Set the MAXMotion position control mode of the controller for a specific
     * closed loop slot.
     *
     * @param mode The MAXmotion position mode
     * @param slot The closed loop slot to set the values for
     * @return The modified MAXMotionConfig object for method chaining
     */
    MAXMotionConfig& PositionMode(MAXMotionPositionMode mode,
                                  ClosedLoopSlot slot = kSlot0);
};

}  // namespace rev::spark
