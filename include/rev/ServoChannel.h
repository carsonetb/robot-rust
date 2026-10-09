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

#include <stdint.h>

#include <cstddef>

#include "rev/REVLibError.h"

namespace rev::servohub {

class ServoChannel {
    friend class ServoHub;

public:
    /**
     * Closes the ServoChannel
     */
    ~ServoChannel();

    enum class ChannelId {
        kChannelId0 = 0,
        kChannelId1 = 1,
        kChannelId2 = 2,
        kChannelId3 = 3,
        kChannelId4 = 4,
        kChannelId5 = 5
    };
    static constexpr size_t kNumServoChannels{6u};

    /**
     * Get the channel ID this ServoChannel.
     *
     * @return Channel channel ID
     */
    ChannelId GetChannelId() const { return m_channelId; }

    /**
     * @return The pulse width applied to this channel in microseconds.
     */
    int GetPulseWidth() const;

    /**
     * @return true if the channel is enabled; false, otherwise
     */
    bool IsEnabled() const;

    /**
     * @return The channel's output current in Amps.
     */
    double GetCurrent() const;

    /**
     * Sets the servo to the desired location based on the pulse width (in
     * microseconds)
     *
     * @param[in] pulseWidth_us The desired pulse width in microseconds
     */
    REVLibError SetPulseWidth(int pulseWidth_us);

    /**
     * Enables/Disables the servo
     *
     * @param[in] enabled true = enabled, false = disabled
     */
    REVLibError SetEnabled(bool enabled);

    /**
     * Turns on/off the power to the servo
     *
     * @param[in] powered true = powered on, false = powered off
     */
    REVLibError SetPowered(bool powered);

private:
    /**
     * Create a new object to control a ServoHub Servo Channel
     *
     * @param[in] channelId The specific channel ID.
     * @param[in] servoHubHandle The handle of the containing ServoHub
     */
    explicit ServoChannel(ChannelId channelId, void* servoHubHandle);

    ChannelId m_channelId;

    // The type is void* because we don't want to expose c_ServoHub_handle to
    // the consumers of this header file
    void* m_servoHubHandle{nullptr};
};

}  // namespace rev::servohub
