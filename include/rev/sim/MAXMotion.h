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

/*
 * maxmotion.h
 *
 *  Created on: Jan 24, 2019
 *      Author: Team195
 *  Renamed on: May 16, 2025
 *      Author: Rylan
 */

#ifndef FRC_REVLIB_SRC_MAIN_DRIVER_INCLUDE_REV_SIM_MAXMOTION_H_
#define FRC_REVLIB_SRC_MAIN_DRIVER_INCLUDE_REV_SIM_MAXMOTION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef enum {
    TRAPEZOIDAL = 0,
    SCURVE = 1,
    NUM_ACCEL_MODES
} maxmotion_accel_mode_t;

typedef struct {
    float kMAXMotionMaxVelocity;
    float kMAXMotionMaxAccel;
    float kMAXMotionMaxJerk;
    float kAllowedClosedLoopError;
    maxmotion_accel_mode_t kMAXMotionPositionMode;
    float positionConversionFactor;
    float velocityConversionFactor;
} maxmotion_constants_t;

typedef struct {
    float position;
    float velocity;
    float acceleration;
    float jerk;
} maxmotion_state_t;

typedef struct {
    float velocity;
    float acceleration;
} maxmotion_velocity_state_t;

typedef struct {
    maxmotion_state_t state;
    int time;
    bool is_valid;
} maxmotion_profile_point_t;

typedef struct {
    // always has 8 points (s-curve)
    maxmotion_profile_point_t points[8];
    maxmotion_constants_t motion_params;
    float unwrapped_setpoint;
    int current_time;
    bool is_valid;
} maxmotion_profile_t;

void maxmotion_profile_generate(maxmotion_profile_t* profile,
                                const maxmotion_constants_t motion_params,
                                maxmotion_state_t start, maxmotion_state_t end);

bool maxmotion_profile_check(maxmotion_profile_t* profile,
                             const maxmotion_constants_t motion_params,
                             maxmotion_state_t current_state,
                             maxmotion_state_t end_state);
maxmotion_state_t maxmotion_profile_get_point(maxmotion_profile_t* profile,
                                              int time);

#define VELOCITY_MARGIN(maxAccel) maxAccel / 20.0f
#define SECONDS_PER_MINUTE 60.0f

extern maxmotion_velocity_state_t smartervelocity_calculate_output_velocity(
    maxmotion_constants_t* motion_params, float setpoint, float prev_vel,
    float dt);
#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // FRC_REVLIB_SRC_MAIN_DRIVER_INCLUDE_REV_SIM_MAXMOTION_H_
