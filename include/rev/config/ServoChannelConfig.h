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

#include "rev/ServoChannel.h"
#include "rev/config/BaseConfig.h"

namespace rev::servohub {

class ServoChannelConfig : public BaseConfig {
public:
    explicit ServoChannelConfig(ServoChannel::ChannelId channelId);
    ~ServoChannelConfig() override = default;

    ServoChannelConfig(const ServoChannelConfig&) = delete;
    ServoChannelConfig& operator=(const ServoChannelConfig&) = delete;
    ServoChannelConfig(ServoChannelConfig&&) noexcept = delete;
    ServoChannelConfig& operator=(ServoChannelConfig&&) noexcept = delete;

    /**
     * Applies settings from another ServoChannelConfig to this one.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param[in] config The ServoChannelConfig to copy settings from
     * @return The updated ServoChannelConfig for method chaining
     */
    ServoChannelConfig& Apply(ServoChannelConfig& config);

    /**
     * Set the min/center/max pulse widths on this channel.
     *
     * @param[in] minPulse_us The minimum pulse width (in microseconds)
     * @param[in] centerPulse_us The center pulse width (in microseconds)
     * @param[in] maxPulse_us The maximum pulse width (in microseconds)
     * @return The modified ServoChannelConfig object for method chaining
     */
    ServoChannelConfig& PulseRange(uint32_t minPulse_us,
                                   uint32_t centerPulse_us,
                                   uint32_t maxPulse_us);

    struct PulseRange_t {
        uint32_t minPulse_us;
        uint32_t centerPulse_us;
        uint32_t maxPulse_us;
    };

    /**
     * Set the min/center/max pulse widths on this channel.
     *
     * @param[in] pulseRange_us The minimum/center/max pulse widths (in
     * microseconds)
     * @return The modified ServoChannelConfig object for method chaining
     */
    ServoChannelConfig& PulseRange(const PulseRange_t& pulseRange_us);

    enum class BehaviorWhenDisabled {
        kDoNotSupplyPower = 0,
        kSupplyPower = 1,
    };
    /**
     * Set the output power behavior when the channel is disabled.
     *
     * <p>When the channel is enabled [ServoChannel::SetEnabled(true)],
     * the output power to the servo follows the channel's power setting
     * [ServoChannel::SetPowered()].
     *
     * <p>When the channel is disabled [ServoChannel::SetEnabled(false)],
     * the output power to the servo follows the channel's disableBehavior.
     *
     * @param[in] behavior The disable behavior as described above.
     * @return The modified ServoChannelConfig object for method chaining
     */
    ServoChannelConfig& DisableBehavior(BehaviorWhenDisabled behavior);

private:
    ServoChannel::ChannelId m_channelId;
};

}  // namespace rev::servohub
