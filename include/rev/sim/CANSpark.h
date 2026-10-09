/*
 * Copyright (c) 2020-2025 REV Robotics
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

#include "rev/CANSparkDriver.h"
#include "rev/REVLibErrors.h"
#include "rev/REVUtils.h"
#include "rev/sim/MAXMotion.h"
#include "rev/sim/SmartCurrentLimit.h"

extern "C" {

typedef struct c_SIM_Spark_Obj* c_SIM_Spark_handle;

typedef struct c_SIM_Spark_ExtOrAltEncoder_Obj*
    c_SIM_Spark_ExtOrAltEncoder_handle;
typedef struct c_SIM_Spark_AbsoluteEncoder_Obj*
    c_SIM_Spark_AbsoluteEncoder_handle;
typedef struct c_SIM_Spark_AnalogSensor_Obj* c_SIM_Spark_AnalogSensor_handle;
typedef struct c_SIM_Spark_LimitSwitch_Obj* c_SIM_Spark_LimitSwitch_handle;
typedef struct c_SIM_Spark_FaultManager_Obj* c_SIM_Spark_FaultManager_handle;
typedef struct c_SIM_Spark_RelativeEncoder_Obj*
    c_SIM_Spark_RelativeEncoder_handle;
typedef struct c_SIM_Spark_MAXMotion_Obj* c_SIM_Spark_MAXMotion_handle;
typedef struct c_SIM_Spark_FeedForward_Obj* c_SIM_Spark_FeedForward_handle;

typedef struct {
    float kP;
    float kI;
    float kD;
    float iZone;
    float kDFilter;  // [1,0]
    float kMinOutput;
    float kMaxOutput;
    float iMaxAccum;
    float kAllowedClosedLoopError;
    float kRsrvd1;
    float kRsrvd2;
} pid_constants_t;

typedef struct {
    float kS;
    float kV;
    float kA;
    float kG;
    float kCos;
    float kCosRatio;
} feedforward_constants_t;

typedef struct {
    float position;
    float velocity;
    float acceleration;
    bool positionErrorDirection;
} feedforward_state_t;

typedef struct {
    bool s;
    bool v;
    bool a;
    bool g;
    bool cos;
} feedforward_signals_t;

c_SIM_Spark_handle c_SIM_Spark_Create(int deviceId,
                                      c_Spark_SparkModel sparkModel);
void c_SIM_Spark_Close(c_SIM_Spark_handle handle);
void c_SIM_Spark_Destroy(c_SIM_Spark_handle handle);
bool c_SIM_Spark_IsSim(c_SIM_Spark_handle handle);

c_REVLib_ErrorCode c_SIM_Spark_SetParameter(c_SIM_Spark_handle handle,
                                            uint8_t parameterID, uint8_t type,
                                            uint32_t value);
c_REVLib_ErrorCode c_SIM_Spark_GetParameter(c_SIM_Spark_handle handle,
                                            uint8_t parameterID, uint8_t type,
                                            uint32_t* value);

typedef enum {
    CTRL_DUTY_CYCLE = 0,
    CTRL_VELOCITY = 1,
    CTRL_VOLTAGE = 2,
    CTRL_POSITION = 3,
    CTRL_CURRENT = 4,
    CTRL_MAXMOTIONPOSITION = 5,
    CTRL_MAXMOTIONVELOCITY = 6,
    CTRL_NONE  // Should be the last element and 1 + number of controllers
} ctrlType_t;

#define PI 3.14159265358979323846

// New sim functions, telemetry 'get' functions only, HAL_SimDevice Values
// handle setting
uint32_t c_SIM_Spark_GetFirmwareVersion(c_SIM_Spark_handle handle);
float c_SIM_Spark_GetAppliedOutput(c_SIM_Spark_handle handle);
uint16_t c_SIM_Spark_GetFaults(c_SIM_Spark_handle handle);
uint8_t c_SIM_Spark_GetInverted(c_SIM_Spark_handle handle);
uint8_t c_SIM_Spark_IsFollower(c_SIM_Spark_handle handle);
uint16_t c_SIM_Spark_GetStickyFaults(c_SIM_Spark_handle handle);
float c_SIM_Spark_GetOutputCurrent(c_SIM_Spark_handle handle);
float c_SIM_Spark_GetBusVoltage(c_SIM_Spark_handle handle);
uint8_t c_SIM_Spark_GetMotorTemperature(c_SIM_Spark_handle handle);
float c_SIM_Spark_GetVelocity(c_SIM_Spark_handle handle);
float c_SIM_Spark_GetPosition(c_SIM_Spark_handle handle);
void c_SIM_Spark_SetAppliedOutput(c_SIM_Spark_handle handle, float value);
ctrlType_t c_SIM_Spark_GetControlMode(c_SIM_Spark_handle handle);

c_REVLib_ErrorCode c_SIM_Spark_StartFollowerMode(c_SIM_Spark_handle handle);
c_REVLib_ErrorCode c_SIM_Spark_StopFollowerMode(c_SIM_Spark_handle handle);

c_REVLib_ErrorCode c_SIM_Spark_SetTelemetry(c_SIM_Spark_handle handle,
                                            float value, int apiId);
c_REVLib_ErrorCode c_SIM_Spark_RestoreFactoryDefaults(c_SIM_Spark_handle handle,
                                                      bool persist,
                                                      bool resetAll);
c_REVLib_ErrorCode c_SIM_Spark_SetSetpoint(c_SIM_Spark_handle handle,
                                           float value, uint8_t ctrl,
                                           int pidSlot, float arbFeedforward,
                                           int arbFFUnits);
c_REVLib_ErrorCode c_SIM_Spark_GetDRVStatus(c_SIM_Spark_handle handle,
                                            uint16_t* DRVStat0,
                                            uint16_t* DRVStat1,
                                            uint16_t* faults,
                                            uint16_t* stickyFaults);
c_REVLib_ErrorCode c_SIM_Spark_ClearFaults(c_SIM_Spark_handle handle);
uint8_t c_SIM_Spark_GetSparkModel(c_SIM_Spark_handle handle);
uint8_t c_SIM_Spark_GetMotorInterface(c_SIM_Spark_handle handle);
void c_SIM_Spark_SetSimMAXMotionTelemetry(c_SIM_Spark_MAXMotion_handle handle,
                                          double position, double velocity,
                                          double acceleration, bool isValid);
void c_SIM_Spark_SetSimFeedForwardTelemetry(
    c_SIM_Spark_FeedForward_handle handle, double s, double v, double a,
    double g, double cos);
feedforward_constants_t c_SIM_Spark_GetFeedforwardConstants(
    c_SIM_Spark_handle handle);
float c_SIM_Spark_CalculateFeedforward(c_SIM_Spark_handle handle,
                                       const feedforward_constants_t* constants,
                                       feedforward_state_t state,
                                       feedforward_signals_t signals,
                                       const float Vbus);

float c_SIM_Spark_GetSetpoint(c_SIM_Spark_handle handle);
bool c_SIM_Spark_IsAtSetpoint(c_SIM_Spark_handle handle);
int c_SIM_Spark_GetClosedLoopSlot(c_SIM_Spark_handle handle);

float c_SIM_Spark_GetMAXMotionSetpointPosition(c_SIM_Spark_handle handle);
float c_SIM_Spark_GetMAXMotionSetpointVelocity(c_SIM_Spark_handle handle);

float c_SIM_Spark_CalculatePID(c_SIM_Spark_handle handle, float setpoint,
                               float pv, float dt, float feedforward);
float c_SIM_Spark_SimulateMaxMotionPositionControl(c_SIM_Spark_handle handle,
                                                   float dt);
float c_SIM_Spark_SimulateMaxMotionVelocityControl(c_SIM_Spark_handle handle,
                                                   float dt);
float c_SIM_Spark_SimulateCurrentLimit(c_SIM_Spark_handle handle,
                                       float appliedOutput, float current);

c_SIM_Spark_ExtOrAltEncoder_handle c_SIM_Spark_GetOrCreateSimExtOrAltEncoder(
    c_SIM_Spark_handle handle);
c_SIM_Spark_AbsoluteEncoder_handle c_SIM_Spark_GetOrCreateSimAbsoluteEncoder(
    c_SIM_Spark_handle handle);
c_SIM_Spark_AnalogSensor_handle c_SIM_Spark_GetOrCreateSimAnalogSensor(
    c_SIM_Spark_handle handle);
c_SIM_Spark_LimitSwitch_handle c_SIM_Spark_GetOrCreateSimForwardLimitSwitch(
    c_SIM_Spark_handle handle);
c_SIM_Spark_LimitSwitch_handle c_SIM_Spark_GetOrCreateSimReverseLimitSwitch(
    c_SIM_Spark_handle handle);
c_SIM_Spark_FaultManager_handle c_SIM_Spark_GetOrCreateSimFaultManager(
    c_SIM_Spark_handle handle);
c_SIM_Spark_RelativeEncoder_handle c_SIM_Spark_GetOrCreateSimRelativeEncoder(
    c_SIM_Spark_handle handle);
c_SIM_Spark_MAXMotion_handle c_SIM_Spark_GetOrCreateSimMaxMotion(
    c_SIM_Spark_handle handle);
c_SIM_Spark_FeedForward_handle c_SIM_Spark_GetOrCreateSimFeedForward(
    c_SIM_Spark_handle handle);

void c_SIM_Spark_SetSimRelativeEncoderPosition(
    c_SIM_Spark_RelativeEncoder_handle handle, double position);
double c_SIM_Spark_GetSimRelativeEncoderPosition(
    c_SIM_Spark_RelativeEncoder_handle handle);
void c_SIM_Spark_SetSimRelativeEncoderVelocity(
    c_SIM_Spark_RelativeEncoder_handle handle, double velocity);
double c_SIM_Spark_GetSimRelativeEncoderVelocity(
    c_SIM_Spark_RelativeEncoder_handle handle);
void c_SIM_Spark_SetSimRelativeEncoderInverted(
    c_SIM_Spark_RelativeEncoder_handle handle, bool inverted);
bool c_SIM_Spark_GetSimRelativeEncoderInverted(
    c_SIM_Spark_RelativeEncoder_handle handle);
void c_SIM_Spark_SetSimRelativeEncoderPositionFactor(
    c_SIM_Spark_RelativeEncoder_handle handle, double posFactor);
double c_SIM_Spark_GetSimRelativeEncoderPositionFactor(
    c_SIM_Spark_RelativeEncoder_handle handle);
void c_SIM_Spark_SetSimRelativeEncoderVelocityFactor(
    c_SIM_Spark_RelativeEncoder_handle handle, double velFactor);
double c_SIM_Spark_GetSimRelativeEncoderVelocityFactor(
    c_SIM_Spark_RelativeEncoder_handle handle);

void c_SIM_Spark_SetSimExtOrAltEncoderPosition(
    c_SIM_Spark_ExtOrAltEncoder_handle handle, double position);
double c_SIM_Spark_GetSimExtOrAltEncoderPosition(
    c_SIM_Spark_ExtOrAltEncoder_handle handle);
void c_SIM_Spark_SetSimExtOrAltEncoderVelocity(
    c_SIM_Spark_ExtOrAltEncoder_handle handle, double velocity);
double c_SIM_Spark_GetSimExtOrAltEncoderVelocity(
    c_SIM_Spark_ExtOrAltEncoder_handle handle);
void c_SIM_Spark_SetSimExtOrAltEncoderInverted(
    c_SIM_Spark_ExtOrAltEncoder_handle handle, bool inverted);
bool c_SIM_Spark_GetSimExtOrAltEncoderInverted(
    c_SIM_Spark_ExtOrAltEncoder_handle handle);
void c_SIM_Spark_SetSimExtOrAltEncoderZeroOffset(
    c_SIM_Spark_ExtOrAltEncoder_handle handle, double offset);
double c_SIM_Spark_GetSimExtOrAltEncoderZeroOffset(
    c_SIM_Spark_ExtOrAltEncoder_handle handle);
void c_SIM_Spark_SetSimExtOrAltEncoderPositionFactor(
    c_SIM_Spark_ExtOrAltEncoder_handle handle, double posFactor);
double c_SIM_Spark_GetSimExtOrAltEncoderPositionFactor(
    c_SIM_Spark_ExtOrAltEncoder_handle handle);
void c_SIM_Spark_SetSimExtOrAltEncoderVelocityFactor(
    c_SIM_Spark_ExtOrAltEncoder_handle handle, double velFactor);
double c_SIM_Spark_GetSimExtOrAltEncoderVelocityFactor(
    c_SIM_Spark_ExtOrAltEncoder_handle handle);

void c_SIM_Spark_SetSimAbsoluteEncoderPosition(
    c_SIM_Spark_AbsoluteEncoder_handle handle, double position);
double c_SIM_Spark_GetSimAbsoluteEncoderPosition(
    c_SIM_Spark_AbsoluteEncoder_handle handle);
void c_SIM_Spark_SetSimAbsoluteEncoderVelocity(
    c_SIM_Spark_AbsoluteEncoder_handle handle, double velocity);
double c_SIM_Spark_GetSimAbsoluteEncoderVelocity(
    c_SIM_Spark_AbsoluteEncoder_handle handle);
void c_SIM_Spark_SetSimAbsoluteEncoderInverted(
    c_SIM_Spark_AbsoluteEncoder_handle handle, bool inverted);
bool c_SIM_Spark_GetSimAbsoluteEncoderInverted(
    c_SIM_Spark_AbsoluteEncoder_handle handle);
void c_SIM_Spark_SetSimAbsoluteEncoderZeroOffset(
    c_SIM_Spark_AbsoluteEncoder_handle handle, double offset);
double c_SIM_Spark_GetSimAbsoluteEncoderZeroOffset(
    c_SIM_Spark_AbsoluteEncoder_handle handle);

void c_SIM_Spark_SetSimAbsoluteEncoderPositionFactor(
    c_SIM_Spark_AbsoluteEncoder_handle handle, double posFactor);
double c_SIM_Spark_GetSimAbsoluteEncoderPositionFactor(
    c_SIM_Spark_AbsoluteEncoder_handle handle);
void c_SIM_Spark_SetSimAbsoluteEncoderVelocityFactor(
    c_SIM_Spark_AbsoluteEncoder_handle handle, double velFactor);
double c_SIM_Spark_GetSimAbsoluteEncoderVelocityFactor(
    c_SIM_Spark_AbsoluteEncoder_handle handle);

void c_SIM_Spark_SetSimAnalogSensorVoltage(
    c_SIM_Spark_AnalogSensor_handle handle, double voltage);
double c_SIM_Spark_GetSimAnalogSensorVoltage(
    c_SIM_Spark_AnalogSensor_handle handle);
void c_SIM_Spark_SetSimAnalogSensorPosition(
    c_SIM_Spark_AnalogSensor_handle handle, double position);
double c_SIM_Spark_GetSimAnalogSensorPosition(
    c_SIM_Spark_AnalogSensor_handle handle);
void c_SIM_Spark_SetSimAnalogSensorVelocity(
    c_SIM_Spark_AnalogSensor_handle handle, double velocity);
double c_SIM_Spark_GetSimAnalogSensorVelocity(
    c_SIM_Spark_AnalogSensor_handle handle);
void c_SIM_Spark_SetSimAnalogSensorInverted(
    c_SIM_Spark_AnalogSensor_handle handle, bool inverted);
bool c_SIM_Spark_GetSimAnalogSensorInverted(
    c_SIM_Spark_AnalogSensor_handle handle);
void c_SIM_Spark_SetSimAnalogSensorPositionFactor(
    c_SIM_Spark_AnalogSensor_handle handle, double posFactor);
double c_SIM_Spark_GetSimAnalogSensorPositionFactor(
    c_SIM_Spark_AnalogSensor_handle handle);
void c_SIM_Spark_SetSimAnalogSensorVelocityFactor(
    c_SIM_Spark_AnalogSensor_handle handle, double velFactor);
double c_SIM_Spark_GetSimAnalogSensorVelocityFactor(
    c_SIM_Spark_AnalogSensor_handle handle);

void c_SIM_Spark_SetSimLimitSwitchIsPressed(
    c_SIM_Spark_LimitSwitch_handle handle, bool pressed);
bool c_SIM_Spark_GetSimLimitSwitchIsPressed(
    c_SIM_Spark_LimitSwitch_handle handle);
void c_SIM_Spark_SetSimLimitSwitchIsEnabled(
    c_SIM_Spark_LimitSwitch_handle handle, bool enabled);
bool c_SIM_Spark_GetSimLimitSwitchIsEnabled(
    c_SIM_Spark_LimitSwitch_handle handle);

bool c_SIM_Spark_GetSimLimitSwitchExists(c_SIM_Spark_handle handle,
                                         bool forward);

bool c_SIM_Spark_SoftForwardLimitReached(c_SIM_Spark_handle handle);

bool c_SIM_Spark_SoftReverseLimitReached(c_SIM_Spark_handle handle);

void c_SIM_Spark_SetRawframeFromSimFaults(
    c_SIM_Spark_FaultManager_handle handle, c_Spark_PeriodicStatus1* rawframe);
void c_SIM_Spark_ClearSimFaults(c_SIM_Spark_FaultManager_handle handle);
bool c_SIM_Spark_GetSimFaultManagerExists(c_SIM_Spark_handle handle);

float c_SIM_Spark_GetSimIAccum(c_SIM_Spark_handle handle);
void c_SIM_Spark_SetSimIAccum(c_SIM_Spark_handle handle, float value);

}  // extern "C"
