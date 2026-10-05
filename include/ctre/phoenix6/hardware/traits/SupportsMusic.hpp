/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/controls/ControlRequest.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include "ctre/phoenix6/StatusSignal.hpp"
#include "ctre/phoenix6/controls/MusicTone.hpp"


namespace ctre {
namespace phoenix6 {
namespace hardware {
namespace traits {

/**
 * Contains all control functions available for motors that support playing
 * music.
 */
class SupportsMusic
{
public:
    virtual ~SupportsMusic() = default;
    
    
    /**
     * \brief Plays a single tone at the user specified frequency.
     * 
     * - MusicTone Parameters: 
     *   - AudioFrequency: Sound frequency to play.  A value of zero will silence the
     *                  device. The effective frequency range is 10-20000 Hz.  Any
     *                  nonzero frequency less than 10 Hz will be capped to 10 Hz. 
     *                  Any frequency above 20 kHz will be capped to 20 kHz.
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::MusicTone &request) = 0;

    /**
     * \brief Control device with generic control request object. User must make
     *        sure the specified object is castable to a valid control request,
     *        otherwise this function will fail at run-time and return the NotSupported
     *        StatusCode
     *
     * \param request Control object to request of the device
     * \returns Status Code of the request, 0 is OK
     */
    virtual ctre::phoenix::StatusCode SetControl(const controls::ControlRequest &request) = 0;
    
};

}
}
}
}

