/*
 * Copyright (c) 2024-2026 REV Robotics
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
 * This file is auto-generated. Do NOT modify it directly.
 * See https://github.com/REVrobotics/SparkParameters
 */

#pragma once

#include <stdint.h>

#include "rev/CANCommonParameters.h"

#ifdef __cplusplus
extern "C" {
#endif

static const uint32_t c_Spark_NumParameters = 227;

typedef enum {
    c_Spark_kCANID = 0,
    c_Spark_kInputMode = 1,
    c_Spark_kMotorType = 2,
    c_Spark_kCommutationAdvance = 3,
    c_Spark_kControlType = 5,
    c_Spark_kIdleMode = 6,
    c_Spark_kInputDeadband = 7,
    c_Spark_kClosedLoopControlSensor = 9,
    c_Spark_kPolePairs = 10,
    c_Spark_kCurrentChop = 11,
    c_Spark_kCurrentChopCycles = 12,
    c_Spark_kP_0 = 13,
    c_Spark_kI_0 = 14,
    c_Spark_kD_0 = 15,
    c_Spark_kV_0 = 16,
    c_Spark_kIZone_0 = 17,
    c_Spark_kDFilter_0 = 18,
    c_Spark_kOutputMin_0 = 19,
    c_Spark_kOutputMax_0 = 20,
    c_Spark_kP_1 = 21,
    c_Spark_kI_1 = 22,
    c_Spark_kD_1 = 23,
    c_Spark_kV_1 = 24,
    c_Spark_kIZone_1 = 25,
    c_Spark_kDFilter_1 = 26,
    c_Spark_kOutputMin_1 = 27,
    c_Spark_kOutputMax_1 = 28,
    c_Spark_kP_2 = 29,
    c_Spark_kI_2 = 30,
    c_Spark_kD_2 = 31,
    c_Spark_kV_2 = 32,
    c_Spark_kIZone_2 = 33,
    c_Spark_kDFilter_2 = 34,
    c_Spark_kOutputMin_2 = 35,
    c_Spark_kOutputMax_2 = 36,
    c_Spark_kP_3 = 37,
    c_Spark_kI_3 = 38,
    c_Spark_kD_3 = 39,
    c_Spark_kV_3 = 40,
    c_Spark_kIZone_3 = 41,
    c_Spark_kDFilter_3 = 42,
    c_Spark_kOutputMin_3 = 43,
    c_Spark_kOutputMax_3 = 44,
    c_Spark_kInverted = 45,
    c_Spark_kLimitSwitchFwdPolarity = 50,
    c_Spark_kLimitSwitchRevPolarity = 51,
    c_Spark_kHardLimitFwdEn = 52,
    c_Spark_kHardLimitRevEn = 53,
    c_Spark_kSoftLimitFwdEn = 54,
    c_Spark_kSoftLimitRevEn = 55,
    c_Spark_kOpenLoopRampRate = 56,
    c_Spark_kLegacyFollowerID = 57,
    c_Spark_kLegacyFollowerConfig = 58,
    c_Spark_kSmartCurrentStallLimit = 59,
    c_Spark_kSmartCurrentFreeLimit = 60,
    c_Spark_kSmartCurrentConfig = 61,
    c_Spark_kSmartCurrentReserved = 62,
    c_Spark_kMotorKv = 63,
    c_Spark_kEncoderCountsPerRev = 69,
    c_Spark_kEncoderAverageDepth = 70,
    c_Spark_kEncoderSampleDelta = 71,
    c_Spark_kEncoderInverted = 72,
    c_Spark_kVoltageCompensationMode = 74,
    c_Spark_kCompensatedNominalVoltage = 75,
    c_Spark_kIMaxAccum_0 = 96,
    c_Spark_kAllowedClosedLoopError_0 = 97,
    c_Spark_kIMaxAccum_1 = 100,
    c_Spark_kAllowedClosedLoopError_1 = 101,
    c_Spark_kIMaxAccum_2 = 104,
    c_Spark_kAllowedClosedLoopError_2 = 105,
    c_Spark_kIMaxAccum_3 = 108,
    c_Spark_kAllowedClosedLoopError_3 = 109,
    c_Spark_kPositionConversionFactor = 112,
    c_Spark_kVelocityConversionFactor = 113,
    c_Spark_kClosedLoopRampRate = 114,
    c_Spark_kSoftLimitForward = 115,
    c_Spark_kSoftLimitReverse = 116,
    c_Spark_kAnalogPositionConversion = 119,
    c_Spark_kAnalogVelocityConversion = 120,
    c_Spark_kAnalogAverageDepth = 121,
    c_Spark_kAnalogSensorMode = 122,
    c_Spark_kAnalogInverted = 123,
    c_Spark_kAnalogSampleDelta = 124,
    c_Spark_kCompatibilityPortConfig = 127,
    c_Spark_kAltEncoderCountsPerRev = 128,
    c_Spark_kAltEncoderAverageDepth = 129,
    c_Spark_kAltEncoderSampleDelta = 130,
    c_Spark_kAltEncoderInverted = 131,
    c_Spark_kAltEncoderPositionConversion = 132,
    c_Spark_kAltEncoderVelocityConversion = 133,
    c_Spark_kUvwSensorSampleRate = 136,
    c_Spark_kUvwSensorAverageDepth = 137,
    c_Spark_kNumParameters = 138,
    c_Spark_kDutyCyclePositionFactor = 139,
    c_Spark_kDutyCycleVelocityFactor = 140,
    c_Spark_kDutyCycleInverted = 141,
    c_Spark_kDutyCycleSensorMode = 142,
    c_Spark_kDutyCycleAverageDepth = 143,
    c_Spark_kDutyCycleOffsetLegacy = 145,
    c_Spark_kPositionPIDWrapEnable = 149,
    c_Spark_kPositionPIDMinInput = 150,
    c_Spark_kPositionPIDMaxInput = 151,
    c_Spark_kDutyCycleZeroCentered = 152,
    c_Spark_kDutyCycleSensorPrescaler = 153,
    c_Spark_kDutyCycleOffset = 154,
    c_Spark_kProductId = 155,
    c_Spark_kDeviceMajorVersion = 156,
    c_Spark_kDeviceMinorVersion = 157,
    c_Spark_kStatus0Period = 158,
    c_Spark_kStatus1Period = 159,
    c_Spark_kStatus2Period = 160,
    c_Spark_kStatus3Period = 161,
    c_Spark_kStatus4Period = 162,
    c_Spark_kStatus5Period = 163,
    c_Spark_kStatus6Period = 164,
    c_Spark_kStatus7Period = 165,
    c_Spark_kMAXMotionCruiseVelocity_0 = 166,
    c_Spark_kMAXMotionMaxAccel_0 = 167,
    c_Spark_kMAXMotionMaxJerk_0 = 168,
    c_Spark_kMAXMotionAllowedProfileError_0 = 169,
    c_Spark_kMAXMotionPositionMode_0 = 170,
    c_Spark_kMAXMotionCruiseVelocity_1 = 171,
    c_Spark_kMAXMotionMaxAccel_1 = 172,
    c_Spark_kMAXMotionMaxJerk_1 = 173,
    c_Spark_kMAXMotionAllowedProfileError_1 = 174,
    c_Spark_kMAXMotionPositionMode_1 = 175,
    c_Spark_kMAXMotionCruiseVelocity_2 = 176,
    c_Spark_kMAXMotionMaxAccel_2 = 177,
    c_Spark_kMAXMotionMaxJerk_2 = 178,
    c_Spark_kMAXMotionAllowedProfileError_2 = 179,
    c_Spark_kMAXMotionPositionMode_2 = 180,
    c_Spark_kMAXMotionCruiseVelocity_3 = 181,
    c_Spark_kMAXMotionMaxAccel_3 = 182,
    c_Spark_kMAXMotionMaxJerk_3 = 183,
    c_Spark_kMAXMotionAllowedProfileError_3 = 184,
    c_Spark_kMAXMotionPositionMode_3 = 185,
    c_Spark_kForceEnableStatus_0 = 186,
    c_Spark_kForceEnableStatus_1 = 187,
    c_Spark_kForceEnableStatus_2 = 188,
    c_Spark_kForceEnableStatus_3 = 189,
    c_Spark_kForceEnableStatus_4 = 190,
    c_Spark_kForceEnableStatus_5 = 191,
    c_Spark_kForceEnableStatus_6 = 192,
    c_Spark_kForceEnableStatus_7 = 193,
    c_Spark_kFollowerModeLeaderId = 194,
    c_Spark_kFollowerModeIsInverted = 195,
    c_Spark_kDutyCycleEncoderStartPulseUs = 196,
    c_Spark_kDutyCycleEncoderEndPulseUs = 197,
    c_Spark_kParamTableVersion = 198,
    c_Spark_kStatus8Period = 199,
    c_Spark_kForceEnableStatus_8 = 200,
    c_Spark_kLimitSwitchPositionSensor = 201,
    c_Spark_kLimitSwitchFwdPosition = 202,
    c_Spark_kLimitSwitchRevPosition = 203,
    c_Spark_kS_0 = 204,
    c_Spark_kA_0 = 205,
    c_Spark_kG_0 = 206,
    c_Spark_kCos_0 = 207,
    c_Spark_kCosRatio_0 = 208,
    c_Spark_kS_1 = 209,
    c_Spark_kA_1 = 210,
    c_Spark_kG_1 = 211,
    c_Spark_kCos_1 = 212,
    c_Spark_kCosRatio_1 = 213,
    c_Spark_kS_2 = 214,
    c_Spark_kA_2 = 215,
    c_Spark_kG_2 = 216,
    c_Spark_kCos_2 = 217,
    c_Spark_kCosRatio_2 = 218,
    c_Spark_kS_3 = 219,
    c_Spark_kA_3 = 220,
    c_Spark_kG_3 = 221,
    c_Spark_kCos_3 = 222,
    c_Spark_kCosRatio_3 = 223,
    c_Spark_kStatus9Period = 224,
    c_Spark_kForceEnableStatus_9 = 225,
    c_Spark_kDetachedEncoderDeviceID = 226,
} c_Spark_ConfigParameter;

static const c_Spark_ConfigParameter c_Spark_kUnused =
    (c_Spark_ConfigParameter)(-1);

typedef enum {
    c_Spark_kInputMode_PWM,
    c_Spark_kInputMode_CAN,
    c_Spark_kInputMode_USB,
    c_Spark_kNumInputModes
} c_Spark_InputMode;

typedef enum {
    c_Spark_kMotorType_BRUSHED,
    c_Spark_kMotorType_BRUSHLESS,
    c_Spark_kNumMotorTypes
} c_Spark_MotorType;

typedef enum {
    c_Spark_kIdleMode_COAST,
    c_Spark_kIdleMode_BRAKE,
    c_Spark_kNumIdleModes
} c_Spark_IdleMode;

typedef enum {
    c_Spark_kSensor_NONE,
    c_Spark_kSensor_MAIN_ENCODER,
    c_Spark_kSensor_ANALOG,
    c_Spark_kSensor_ALT_ENCODER,
    c_Spark_kSensor_DUTY_CYCLE,
    c_Spark_kSensor_DETACHED_ABSOLUTE,
    c_Spark_kSensor_DETACHED_RELATIVE,
    c_Spark_kNumSensors
} c_Spark_Sensor;

typedef enum {
    c_Spark_kControlType_DUTY_CYCLE,
    c_Spark_kControlType_VELOCITY,
    c_Spark_kControlType_VOLTAGE,
    c_Spark_kControlType_POSITION,
    c_Spark_kControlType_CURRENT,
    c_Spark_kControlType_MAXMOTION_POSITION,
    c_Spark_kControlType_MAXMOTION_VELOCITY,
    c_Spark_kNumControlTypes
} c_Spark_ControlType;

typedef enum {
    c_Spark_kVoltageCompMode_NO_VOLTAGE_COMP,
    c_Spark_kVoltageCompMode_CLOSED_LOOP_VOLTAGE_OUTPUT,
    c_Spark_kVoltageCompMode_NOMINAL_VOLTAGE_COMP,
    c_Spark_kNumVoltageCompModes
} c_Spark_VoltageCompMode;

typedef enum {
    c_Spark_kAccelerationStrategy_TRAPEZOIDAL,
    c_Spark_kAccelerationStrategy_SCURVE,
    c_Spark_kNumAccelerationStrategys
} c_Spark_AccelerationStrategy;

typedef enum {
    c_Spark_kAnalogMode_ABSOLUTE,
    c_Spark_kAnalogMode_RELATIVE,
    c_Spark_kNumAnalogModes
} c_Spark_AnalogMode;

typedef enum {
    c_Spark_kCompatibilityPort_DEFAULT,
    c_Spark_kCompatibilityPort_ALTERNATE_ENCODER,
    c_Spark_kNumCompatibilityPorts
} c_Spark_CompatibilityPort;

typedef enum {
    c_Spark_kDutyCycleMode_ABSOLUTE,
    c_Spark_kDutyCycleMode_RELATIVE,
    c_Spark_kDutyCycleMode_RELATIVE_STARTING_OFFSET,
    c_Spark_kNumDutyCycleModes
} c_Spark_DutyCycleMode;

typedef enum {
    c_Spark_kMAXMotionPositionMode_TRAPEZOIDAL,
    c_Spark_kNumMAXMotionPositionModes
} c_Spark_MAXMotionPositionMode;

typedef enum {
    c_Spark_kLimitSwBehavior_KEEP_MOVING_MOTOR,
    c_Spark_kLimitSwBehavior_STOP_MOVING_MOTOR,
    c_Spark_kLimitSwBehavior_KEEP_MOVING_MOTOR_AND_SET_POSITION,
    c_Spark_kLimitSwBehavior_STOP_MOVING_MOTOR_AND_SET_POSITION,
    c_Spark_kNumLimitSwBehaviors
} c_Spark_LimitSwBehavior;

c_REVLib_ParameterType c_Spark_GetParameterType(
    c_Spark_ConfigParameter parameterId);

uint32_t c_Spark_GetParameterDefaultValue(c_Spark_ConfigParameter parameterId);

const char* c_Spark_GetParameterName(c_Spark_ConfigParameter parameterId);

// For debugging purposes, to verify internal state.
c_Spark_ConfigParameter c_Spark_GetConfigParameter(
    c_Spark_ConfigParameter parameterId);

#ifdef __cplusplus
}  // extern "C"
#endif
