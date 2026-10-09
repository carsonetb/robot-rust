/*
 * Copyright (c) 2025-2026 REV Robotics
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

#include "rev/ConfigureTypes.h"
#include "rev/DetachedEncoderLowLevel.h"
#include "rev/REVLibError.h"
#include "rev/RelativeEncoder.h"
#include "rev/config/DetachedEncoderConfigAccessor.h"

namespace rev::detached {

class DetachedEncoderConfig;

class DetachedEncoder : public RelativeEncoder, public DetachedEncoderLowLevel {
public:
    /**
     * Accessor for Detached encoder parameter values. This object contains
     * fields and methods to retrieve parameters that have been applied to the
     * device. To set parameters, see DetachedEncoderConfig and
     * DetachedEncoder::Configure().
     *
     * NOTE: This uses calls that are blocking to retrieve parameters and should
     * be used infrequently.
     */
    DetachedEncoderConfigAccessor configAccessor;

    DetachedEncoder(DetachedEncoder&& rhs) = default;
    DetachedEncoder& operator=(DetachedEncoder&& rhs) = default;

    DetachedEncoder(const DetachedEncoder& rhs) = default;

    /**
     * Closes the Detached encoder controller
     */
    ~DetachedEncoder() override = default;

    /**
     * Get the position of the encoder. This returns the native units
     * of 'rotations' by default, and can be changed by a scale factor
     * using DetachedEncoderConfig::PositionConversionFactor().
     *
     * @return Number of rotations of the encoder
     *
     */
    double GetPosition() const override;

    /**
     * Get the velocity of the encoder. This returns the native units
     * of 'RPM' by default, and can be changed by a scale factor
     * using DetachedEncoderConfig::VelocityConversionFactor().
     *
     * @return Number the RPM of the encoder
     *
     */
    double GetVelocity() const override;

    /**
     * Get the absolute position of the encoder. This returns the native units
     * of 'rotations' [0, 1) by default, and can be changed by a scale factor
     * using DetachedEncoderConfig::PositionConversionFactor().
     *
     * @return Number of rotations of the encoder
     *
     */
    double GetAngle() const;

    /**
     * Get the absolute position of the encoder. This returns the native units
     * of 'rotations' [0, 1) without scaling from conversion factors.
     *
     * @return Number of rotations of the encoder
     *
     */
    double GetRawAngle() const;

    /**
     * Set the position of the encoder.
     *
     * @param position Number of rotations of the encoder
     *
     * @return REVLibError::kOk if successful
     */
    REVLibError SetPosition(double position) override;

    /* ***** Extended Functions ****** */

    /**
     * Set the configuration for the Detached encoder.
     *
     * <p>If @c resetMode is ResetMode::kResetSafeParameters, this
     * method will reset safe writable parameters to their default values before
     * setting the given configuration. The following parameters will not be
     * reset by this action: CAN ID and Absolute (Duty Cycle) Zero Offset.
     *
     * @param config The desired Detached encoder configuration
     * @param resetMode Whether to reset safe parameters before setting the
     * configuration
     * @return REVLibError::kOk if successful
     */
    REVLibError Configure(DetachedEncoderConfig& config,
                          rev::ResetMode resetMode);

    struct Faults {
        bool unexpected;
        bool hasReset;
        bool canTx;
        bool canRx;
        bool eeprom;

        int rawBits;
    };

    /**
     * Get the active faults that are currently present on the detached encoder.
     *
     * @return A struct with each fault and their active value
     */
    Faults GetFaults() const;

    /**
     * Get the sticky faults that were present on the detached encoder at one
     * point since the sticky faults were last cleared.
     *
     * <p>Sticky faults can be cleared with DetachedEncoder::ClearFaults().
     *
     * @return A struct with each fault and their sticky value
     */
    Faults GetStickyFaults() const;

    /**
     * Clears all sticky faults.
     */
    REVLibError ClearFaults();

protected:
    /**
     * Create a new object to control a Detached Encoder
     *
     * @param deviceID The device ID.
     * @param model The specific model of detached encoder
     */
    DetachedEncoder(int deviceID, EncoderModel model);
};

}  // namespace rev::detached
