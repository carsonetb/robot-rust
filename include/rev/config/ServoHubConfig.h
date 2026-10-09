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

#include <array>
#include <string>

#include "rev/config/BaseConfig.h"
#include "rev/config/ServoChannelConfig.h"

namespace rev::servohub {

class ServoHubConfig : public BaseConfig {
public:
    ServoHubConfig() = default;
    ~ServoHubConfig() override = default;

    ServoHubConfig(const ServoHubConfig&) = delete;
    ServoHubConfig& operator=(const ServoHubConfig&) = delete;
    ServoHubConfig(ServoHubConfig&&) noexcept = delete;
    ServoHubConfig& operator=(ServoHubConfig&&) noexcept = delete;

    /**
     * Applies settings from another ServoHubConfig to this one.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param config The ServoChannelConfig to apply settings from
     * @return The updated ServoHubConfig for method chaining
     */
    ServoHubConfig& Apply(ServoHubConfig& config);

    /**
     * Applies settings from a ServoChannelConfig to this ServoHubConfig.
     *
     * <p>Settings in the provided config will overwrite existing values in this
     * object. Settings not specified in the provided config remain unchanged.
     *
     * @param channelId The channel to apply the settings to
     * @param config The ServoChannelConfig to apply settings from
     * @return The updated ServoHubConfig for method chaining
     */
    ServoHubConfig& Apply(ServoChannel::ChannelId channelId,
                          ServoChannelConfig& config);

    std::string Flatten() override;

    ServoChannelConfig channel0{ServoChannel::ChannelId::kChannelId0};
    ServoChannelConfig channel1{ServoChannel::ChannelId::kChannelId1};
    ServoChannelConfig channel2{ServoChannel::ChannelId::kChannelId2};
    ServoChannelConfig channel3{ServoChannel::ChannelId::kChannelId3};
    ServoChannelConfig channel4{ServoChannel::ChannelId::kChannelId4};
    ServoChannelConfig channel5{ServoChannel::ChannelId::kChannelId5};

private:
    const std::array<ServoChannelConfig*, ServoChannel::kNumServoChannels>
        m_ChannelConfigs{&channel0, &channel1, &channel2,
                         &channel3, &channel4, &channel5};
};  // class ServoHubConfig

}  // namespace rev::servohub
