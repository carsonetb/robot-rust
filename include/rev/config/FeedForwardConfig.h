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

class FeedForwardConfig : public BaseConfig {
public:
    FeedForwardConfig() = default;
    ~FeedForwardConfig() override = default;

    FeedForwardConfig(const FeedForwardConfig&) = default;
    FeedForwardConfig& operator=(const FeedForwardConfig&) = delete;
    FeedForwardConfig(FeedForwardConfig&&) noexcept = delete;
    FeedForwardConfig& operator=(FeedForwardConfig&&) noexcept = delete;

    /**
     * Applies settings from another {@link FeedForwardConfig} to this one.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The {@link FeedForwardConfig} to copy settings from
     * @return The updated {@link FeedForwardConfig} for method chaining
     */
    FeedForwardConfig& Apply(FeedForwardConfig& config);

    /**
     * Set the kS Static Gain of the controller for a specific closed loop slot.
     *
     * @param kS The kS gain in Volts
     * @param slot The closed loop slot to set the values for
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& kS(double kS, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the kV Velocity Gain of the controller for a specific closed loop
     * slot.
     *
     * <p>This is not applied in Position control mode.
     *
     * @param kV The kV gain in Volts
     * @param slot The closed loop slot to set the values for
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& kV(double kV, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the kA Acceleration Gain of the controller for a specific closed loop
     * slot.
     *
     * <p>This is only applied in MAXMotion control modes
     *
     * @param kA The kA gain in Volts
     * @param slot The closed loop slot to set the values for
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& kA(double kA, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the kG Static Gravity Gain of the controller for a specific closed
     * loop slot.
     *
     * <p>This is statically applied, for an elevator or linear mechanism. Set
     * it to 0 if kCos is being used.
     *
     * <p>This is only applied in Position and MAXMotion Position control modes
     *
     * @param kG The kG gain in Volts
     * @param slot The closed loop slot to set the values for
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& kG(double kG, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the kCos Cosine Gravity Gain of the controller for a specific closed
     * loop slot.
     *
     * <p>This is multiplied by the cosine of the absolute position of the
     * mechanism (See {@link FeedForwardConfig#kCosRatio(double kCosRatio,
     * ClosedLoopSlot slot)} for info on configuring this) for an arm mechanism.
     * Set it to 0 if kG is being used.
     *
     * <p>This is only applied in Position and MAXMotion Position control modes
     *
     * @param kCos The kCos gain in Volts
     * @param slot The closed loop slot to set the values for
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& kCos(double kCos, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the kCosRatio of the controller for a specific closed loop slot.
     *
     * <p>This sets the ratio that is used to calculate the absolute position of
     * your arm mechanism for use with kCos. This is applied after the
     * conversion factor and should convert from those units to absolute
     * rotations of your mechanism. Ensure your selected encoder is zeroed such
     * that 0 = horizontal.
     *
     * @param kCosRatio The kCosRatio in Volts
     * @param slot The closed loop slot to set the values for
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& kCosRatio(double kCosRatio,
                                 ClosedLoopSlot slot = kSlot0);

    /**
     * Set the kS and kV gains for the provided slot in one call.
     *
     * <p>For more information on the kS and kV gains, see {@link
     * FeedForwardConfig#kS(double)} and
     * {@link FeedForwardConfig#kV(double)}.
     *
     * @param kS The kS gain in Volts
     * @param kV The kV gain in Volts per velocity
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& sv(double kS, double kV, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the kS, kV, and kA gains for the provided slot in one call.
     *
     * <p>For more information on the kS, kV, and kA gains, see {@link
     * FeedForwardConfig#kS(double)},
     * {@link FeedForwardConfig#kV(double)}, and {@link
     * FeedForwardConfig#kA(double)}.
     *
     * @param kS The kS gain in Volts
     * @param kV The kV gain in Volts per velocity
     * @param kA The kA gain in Volts per velocity per second
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& sva(double kS, double kV, double kA,
                           ClosedLoopSlot slot = kSlot0);

    /**
     * Set the kS, kV, kA, and kG gains for the provided slot in one call.
     *
     * <p>For more information on the kS, kV, kA, and kG gains, see {@link
     * FeedForwardConfig#kS(double)},
     * {@link FeedForwardConfig#kV(double)}, {@link
     * FeedForwardConfig#kA(double)}, and
     * {@link FeedForwardConfig#kG(double)}.
     *
     * @param kS The kS gain in Volts
     * @param kV The kV gain in Volts per velocity
     * @param kA The kA gain in Volts per velocity per second
     * @param kG The kG gain in Volts
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& svag(double kS, double kV, double kA, double kG,
                            ClosedLoopSlot slot = kSlot0);

    /**
     * Set the kS, kV, kA, kCos, and kCosRatio gains for the provided slot in
     * one call.
     *
     * <p>For more information on the kS, kV, kA, kCos, and kCosRatio gains, see
     * {@link FeedForwardConfig#kS(double)}, {@link
     * FeedForwardConfig#kV(double)}, {@link FeedForwardConfig#kA(double)},
     * {@link FeedForwardConfig#kCos(double)}, and {@link
     * FeedForwardConfig#kCosRatio(double)}.
     *
     * @param kS The kS gain in Volts
     * @param kV The kV gain in Volts per velocity
     * @param kA The kA gain in Volts per velocity per second
     * @param kCos The kCos gain in Volts
     * @param kCosRatio The ratio used to calculate the absolute position of
     * your arm mechanism for use with kCos
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& svacr(double kS, double kV, double kA, double kCos,
                             double kCosRatio, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the kS and kG gains for the provided slot in one call.
     *
     * <p>For more information on the kS and kG gains, see {@link
     * FeedForwardConfig#kS(double)} and
     * {@link FeedForwardConfig#kG(double)}.
     *
     * @param kS The kS gain in Volts
     * @param kG The kG gain in Volts
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& sg(double kS, double kG, ClosedLoopSlot slot = kSlot0);

    /**
     * Set the kS, kCos, and kCosRatio gains for the provided slot in one call.
     *
     * <p>For more information on the kS, kCos, and kCosRatio gains, see {@link
     * FeedForwardConfig#kS(double)},
     * {@link FeedForwardConfig#kCos(double)}, and {@link
     * FeedForwardConfig#kCosRatio(double)}.
     *
     * @param kS The kS gain in Volts
     * @param kCos The kCos gain in Volts
     * @param kCosRatio The ratio used to calculate the absolute position of
     * your arm mechanism for use with kCos
     * @return The modified {@link FeedForwardConfig} object for method chaining
     */
    FeedForwardConfig& scr(double kS, double kCos, double kCosRatio,
                           ClosedLoopSlot slot = kSlot0);
};
}  // namespace rev::spark
