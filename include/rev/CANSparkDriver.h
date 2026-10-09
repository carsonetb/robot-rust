/*
 * Copyright (c) 2018-2026 REV Robotics
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

#include "rev/CANSparkParameters.h"
#include "rev/REVCommon.h"
#include "rev/REVLibErrors.h"
#include "rev/REVLibVersion.h"
#include "rev/REVUtils.h"

extern "C" {

const uint16_t c_Spark_kAPIMajorVersion = REVLibMajorVersion;
const uint8_t c_Spark_kAPIMinorVersion = REVLibMinorVersion;
const uint8_t c_Spark_kAPIBuildVersion = REVLibBuildVersion;
const uint32_t c_Spark_kAPIVersion = REVLibVersion;
const uint32_t kMinFirmwareVersion = 0x1a000000;  // v26.0.0
const bool kAllowDebugFirmwareBuilds = true;

// Other useful constants about firmware
const uint32_t kMinAnalogFirmwareVersion = 0x1040000;
const uint32_t kMinAltEncFirmwareVersion = 0x1050000;
const uint32_t kMinAbsEncFirmwareVersion = 0x1060000;

typedef struct c_Spark_Obj* c_Spark_handle;

typedef enum {
    c_Spark_kForward = 0,
    c_Spark_kReverse = 1,
} c_Spark_LimitDirection;

typedef enum {
    c_Spark_kNormallyOpen = 0,
    c_Spark_kNormallyClosed = 1,
} c_Spark_LimitPolarity;

typedef enum {
    c_Spark_Unknown = 0,
    c_Spark_SparkFlex = 1,
    c_Spark_SparkMax = 2,
} c_Spark_SparkModel;

typedef enum {
    c_Spark_Fault_kOther = 0,
    c_Spark_Fault_kMotorType = 1,
    c_Spark_Fault_kSensor = 2,
    c_Spark_Fault_kCan = 3,
    c_Spark_Fault_kTemperature = 4,
    c_Spark_Fault_kDrv = 5,
    c_Spark_Fault_kEscEeprom = 6,
    c_Spark_Fault_kFirmware = 7
} c_Spark_Fault;

typedef enum {
    c_Spark_Warning_kBrownout = 0,
    c_Spark_Warning_kOvercurrent = 1,
    c_Spark_Warning_kEscEeprom = 2,
    c_Spark_Warning_kExtEeprom = 3,
    c_Spark_Warning_kSensor = 4,
    c_Spark_Warning_kStall = 5,
    c_Spark_Warning_kHasReset = 6,
    c_Spark_Warning_kOther = 7
} c_Spark_Warning;

typedef enum {
    c_Spark_kStatus0 = 0,
    c_Spark_kStatus1 = 1,
    c_Spark_kStatus2 = 2,
    c_Spark_kStatus3 = 3,
    c_Spark_kStatus4 = 4,
    c_Spark_kStatus5 = 5,
    c_Spark_kStatus6 = 6,
    c_Spark_kStatus7 = 7,
} c_Spark_PeriodicFrame;

typedef enum {
    c_Spark_kDataPortConfigInvalid =
        -1,  // For internal use only, cannot be sent to the SPARK
    c_Spark_kDataPortConfigDefault = 0,
    c_Spark_kDataPortConfigAltEncoder = 1,
} c_Spark_DataPortConfig;

typedef struct {
    float appliedOutput;
    float voltage;
    float current;
    uint8_t motorTemperature;
    uint8_t hardForwardLimitReached;
    uint8_t hardReverseLimitReached;
    uint8_t softForwardLimitReached;
    uint8_t softReverseLimitReached;
    uint8_t inverted;
    uint8_t primaryHeartbeatLock;
    uint8_t sparkModel;
    uint64_t timestamp;
} c_Spark_PeriodicStatus0;

typedef struct {
    uint8_t otherFault;
    uint8_t motorTypeFault;
    uint8_t sensorFault;
    uint8_t canFault;
    uint8_t temperatureFault;
    uint8_t drvFault;
    uint8_t escEepromFault;
    uint8_t firmwareFault;
    uint8_t brownoutWarning;
    uint8_t overcurrentWarning;
    uint8_t escEepromWarning;
    uint8_t extEepromWarning;
    uint8_t sensorWarning;
    uint8_t stallWarning;
    uint8_t hasResetWarning;
    uint8_t otherWarning;
    uint8_t otherStickyFault;
    uint8_t motorTypeStickyFault;
    uint8_t sensorStickyFault;
    uint8_t canStickyFault;
    uint8_t temperatureStickyFault;
    uint8_t drvStickyFault;
    uint8_t escEepromStickyFault;
    uint8_t firmwareStickyFault;
    uint8_t brownoutStickyWarning;
    uint8_t overcurrentStickyWarning;
    uint8_t escEepromStickyWarning;
    uint8_t extEepromStickyWarning;
    uint8_t sensorStickyWarning;
    uint8_t stallStickyWarning;
    uint8_t hasResetStickyWarning;
    uint8_t otherStickyWarning;
    uint8_t isFollower;
    uint64_t timestamp;
} c_Spark_PeriodicStatus1;

typedef struct {
    float primaryEncoderVelocity;
    float primaryEncoderPosition;
    uint64_t timestamp;
} c_Spark_PeriodicStatus2;

typedef struct {
    float analogVoltage;
    float analogVelocity;
    float analogPosition;
    uint64_t timestamp;
} c_Spark_PeriodicStatus3;

typedef struct {
    float externalOrAltEncoderVelocity;
    float externalOrAltEncoderPosition;
    uint64_t timestamp;
} c_Spark_PeriodicStatus4;

typedef struct {
    float dutyCycleEncoderVelocity;
    float dutyCycleEncoderPosition;
    uint64_t timestamp;
} c_Spark_PeriodicStatus5;

typedef struct {
    float unadjustedDutyCycle;
    float dutyCyclePeriod;
    uint8_t dutyCycleNoSignal;
    uint64_t timestamp;
} c_Spark_PeriodicStatus6;

typedef struct {
    float iAccumulation;
    uint64_t timestamp;
} c_Spark_PeriodicStatus7;

typedef struct {
    float setpoint;
    uint8_t isAtSetpoint;
    uint8_t selectedPidSlot;
    uint64_t timestamp;
} c_Spark_PeriodicStatus8;

typedef struct {
    float maxmotion_setpoint_position;
    float maxmotion_setpoint_velocity;
    uint64_t timestamp;
} c_Spark_PeriodicStatus9;

typedef struct {
    uint8_t major;
    uint8_t minor;
    uint16_t build;
    uint8_t debugBuild;
    uint32_t versionRaw;
} c_Spark_FirmwareVersion;

c_REVLib_ErrorCode c_Spark_RegisterId(int deviceId);
c_Spark_handle c_Spark_Create(int deviceId, c_Spark_MotorType motorType,
                              c_Spark_SparkModel unconfirmedModel,
                              c_REVLib_ErrorCode* status);
c_Spark_handle c_Spark_Create_Inplace(int deviceId,
                                      c_Spark_SparkModel unconfirmedModel,
                                      c_REVLib_ErrorCode* status);
/**
 * Logically close the SPARK, stopping any threads it uses, and freeing the id
 * to be used again. No methods should be called after this, but methods that
 * have already started may complete until c_Spark_Destroy is called.
 */
void c_Spark_Close(c_Spark_handle handle);
/**
 * Free any memory used by this handle. No methods can be called on it
 * afterward.
 */
void c_Spark_Destroy(c_Spark_handle handle);
c_REVLib_ErrorCode c_Spark_GetFirmwareVersion(
    c_Spark_handle handle, c_Spark_FirmwareVersion* fwVersion);
c_REVLib_ErrorCode c_Spark_GetSerialNumber(c_Spark_handle handle,
                                           uint32_t* serialNumber[3]);
c_REVLib_ErrorCode c_Spark_GetDeviceId(c_Spark_handle handle, int* deviceId);
c_REVLib_ErrorCode c_Spark_SetMotorType(c_Spark_handle handle,
                                        c_Spark_MotorType type);
void c_Spark_SetPeriodicFrameTimeout(c_Spark_handle handle, int timeoutMs);
void c_Spark_SetCANMaxRetries(c_Spark_handle handle, int numRetries);

void c_Spark_SetControlFramePeriod(c_Spark_handle handle, int periodMs);
int c_Spark_GetControlFramePeriod(c_Spark_handle handle);

c_REVLib_ErrorCode c_Spark_SetParameterFloat32(c_Spark_handle handle,
                                               c_Spark_ConfigParameter paramId,
                                               float value);
c_REVLib_ErrorCode c_Spark_SetParameterInt32(c_Spark_handle handle,
                                             c_Spark_ConfigParameter paramId,
                                             int32_t value);
c_REVLib_ErrorCode c_Spark_SetParameterUint32(c_Spark_handle handle,
                                              c_Spark_ConfigParameter paramId,
                                              uint32_t value);
c_REVLib_ErrorCode c_Spark_SetParameterBool(c_Spark_handle handle,
                                            c_Spark_ConfigParameter paramId,
                                            uint8_t value);
c_REVLib_ErrorCode c_Spark_GetParameterFloat32(c_Spark_handle handle,
                                               c_Spark_ConfigParameter paramId,
                                               float* value);
c_REVLib_ErrorCode c_Spark_GetParameterInt32(c_Spark_handle handle,
                                             c_Spark_ConfigParameter paramId,
                                             int32_t* value);
c_REVLib_ErrorCode c_Spark_GetParameterUint32(c_Spark_handle handle,
                                              c_Spark_ConfigParameter paramId,
                                              uint32_t* value);
c_REVLib_ErrorCode c_Spark_GetParameterBool(c_Spark_handle handle,
                                            c_Spark_ConfigParameter paramId,
                                            uint8_t* value);

c_REVLib_ErrorCode c_Spark_GetPeriodicStatus0(
    c_Spark_handle handle, c_Spark_PeriodicStatus0* rawframe);
c_REVLib_ErrorCode c_Spark_GetPeriodicStatus1(
    c_Spark_handle handle, c_Spark_PeriodicStatus1* rawframe);
c_REVLib_ErrorCode c_Spark_GetPeriodicStatus2(
    c_Spark_handle handle, c_Spark_PeriodicStatus2* rawframe);
c_REVLib_ErrorCode c_Spark_GetPeriodicStatus3(
    c_Spark_handle handle, c_Spark_PeriodicStatus3* rawframe);
c_REVLib_ErrorCode c_Spark_GetPeriodicStatus4(
    c_Spark_handle handle, c_Spark_PeriodicStatus4* rawframe);
c_REVLib_ErrorCode c_Spark_GetPeriodicStatus5(
    c_Spark_handle handle, c_Spark_PeriodicStatus5* rawframe);
c_REVLib_ErrorCode c_Spark_GetPeriodicStatus6(
    c_Spark_handle handle, c_Spark_PeriodicStatus6* rawframe);
c_REVLib_ErrorCode c_Spark_GetPeriodicStatus7(
    c_Spark_handle handle, c_Spark_PeriodicStatus7* rawframe);
c_REVLib_ErrorCode c_Spark_GetPeriodicStatus8(
    c_Spark_handle handle, c_Spark_PeriodicStatus8* rawframe);
c_REVLib_ErrorCode c_Spark_GetPeriodicStatus9(
    c_Spark_handle handle, c_Spark_PeriodicStatus9* rawframe);

c_REVLib_ErrorCode c_Spark_SetEncoderPosition(c_Spark_handle handle,
                                              float position);
c_REVLib_ErrorCode c_Spark_SetAltEncoderPosition(c_Spark_handle handle,
                                                 float position);
c_REVLib_ErrorCode c_Spark_ResetSafeParameters(c_Spark_handle handle,
                                               uint8_t persist);

float c_Spark_SafeFloat(float f);

c_REVLib_ErrorCode c_Spark_SetpointCommand(c_Spark_handle handle, float value,
                                           c_Spark_ControlType ctrl,
                                           int pidSlot, float arbFeedforward,
                                           int arbFFUnits);

c_REVLib_ErrorCode c_Spark_SetInverted(c_Spark_handle handle, uint8_t inverted);
c_REVLib_ErrorCode c_Spark_GetInverted(c_Spark_handle handle,
                                       uint8_t* inverted);
c_REVLib_ErrorCode c_Spark_GetSparkModel(c_Spark_handle handle,
                                         c_Spark_SparkModel* model);
c_REVLib_ErrorCode c_Spark_IsFollower(c_Spark_handle handle,
                                      uint8_t* isFollower);
c_REVLib_ErrorCode c_Spark_GetFaults(c_Spark_handle handle, uint16_t* faults);
c_REVLib_ErrorCode c_Spark_GetStickyFaults(c_Spark_handle handle,
                                           uint16_t* stickyFaults);
c_REVLib_ErrorCode c_Spark_GetWarnings(c_Spark_handle handle,
                                       uint16_t* warnings);
c_REVLib_ErrorCode c_Spark_GetStickyWarnings(c_Spark_handle handle,
                                             uint16_t* stickyWarnings);
c_REVLib_ErrorCode c_Spark_GetBusVoltage(c_Spark_handle handle,
                                         float* busVoltage);
c_REVLib_ErrorCode c_Spark_GetAppliedOutput(c_Spark_handle handle,
                                            float* appliedOutput);
void c_Spark_SetSimAppliedOutput(c_Spark_handle handle, float appliedOutput);
c_REVLib_ErrorCode c_Spark_GetOutputCurrent(c_Spark_handle handle,
                                            float* outputCurrent);
c_REVLib_ErrorCode c_Spark_GetMotorTemperature(c_Spark_handle handle,
                                               float* motorTemperature);
c_REVLib_ErrorCode c_Spark_ClearFaults(c_Spark_handle handle);
c_REVLib_ErrorCode c_Spark_PersistParameters(c_Spark_handle handle);
c_REVLib_ErrorCode c_Spark_SetCANTimeout(c_Spark_handle handle, int timeoutMs);
c_REVLib_ErrorCode c_Spark_GetMotorInterface(c_Spark_handle handle,
                                             uint8_t* motorInterface);
c_REVLib_ErrorCode c_Spark_IDQuery(uint32_t* uniqueIdArray,
                                   size_t uniqueIdArraySize,
                                   size_t* numberOfDevices);
c_REVLib_ErrorCode c_Spark_IDAssign(uint32_t uniqueId, uint8_t deviceId);
c_REVLib_ErrorCode c_Spark_Identify(c_Spark_handle handle);
c_REVLib_ErrorCode c_Spark_IdentifyUniqueId(uint32_t uniqueId);

// Digital Input
c_REVLib_ErrorCode c_Spark_GetLimitSwitch(c_Spark_handle handle,
                                          c_Spark_LimitDirection sw,
                                          uint8_t* limit);

c_REVLib_ErrorCode c_Spark_GetSoftLimit(c_Spark_handle handle,
                                        c_Spark_LimitDirection sw,
                                        uint8_t* limit);

// Analog
c_REVLib_ErrorCode c_Spark_GetAnalogPosition(c_Spark_handle handle,
                                             float* position);
c_REVLib_ErrorCode c_Spark_GetAnalogVelocity(c_Spark_handle handle,
                                             float* velocity);
c_REVLib_ErrorCode c_Spark_GetAnalogVoltage(c_Spark_handle, float* voltage);

// CANEncoder
c_REVLib_ErrorCode c_Spark_GetEncoderPosition(c_Spark_handle handle,
                                              float* position);
c_REVLib_ErrorCode c_Spark_GetEncoderVelocity(c_Spark_handle handle,
                                              float* velocity);

// Alt Encoder
c_REVLib_ErrorCode c_Spark_GetAltEncoderPosition(c_Spark_handle handle,
                                                 float* position);
c_REVLib_ErrorCode c_Spark_GetAltEncoderVelocity(c_Spark_handle handle,
                                                 float* velocity);

// Duty Cycle
c_REVLib_ErrorCode c_Spark_GetDutyCyclePosition(c_Spark_handle handle,
                                                float* position);
c_REVLib_ErrorCode c_Spark_GetDutyCycleVelocity(c_Spark_handle handle,
                                                float* velocity);

c_REVLib_ErrorCode c_Spark_GetDataPortConfig(c_Spark_handle handle,
                                             c_Spark_DataPortConfig* config);

c_REVLib_ErrorCode c_Spark_IsDataPortConfigured(c_Spark_handle handle,
                                                uint8_t* configured);

// Closed Loop Controller
c_REVLib_ErrorCode c_Spark_SetIAccum(c_Spark_handle handle, float iAccum);
c_REVLib_ErrorCode c_Spark_GetIAccum(c_Spark_handle handle, float* iAccum);
c_REVLib_ErrorCode c_Spark_GetSetpoint(c_Spark_handle handle, float* setpoint);
c_REVLib_ErrorCode c_Spark_IsAtSetpoint(c_Spark_handle handle,
                                        uint8_t* isAtSetpoint);
c_REVLib_ErrorCode c_Spark_GetSelectedSlot(c_Spark_handle handle,
                                           uint8_t* selectedSlot);
c_REVLib_ErrorCode c_Spark_GetMaxMotionSetpointPosition(c_Spark_handle handle,
                                                        float* position);
c_REVLib_ErrorCode c_Spark_GetMaxMotionSetpointVelocity(c_Spark_handle handle,
                                                        float* velocity);

// Other helpers
c_REVLib_APIVersion c_Spark_GetAPIVersion(void);
void c_Spark_SetLastError(c_Spark_handle handle, c_REVLib_ErrorCode error);
c_REVLib_ErrorCode c_Spark_GetLastError(c_Spark_handle handle);
c_REVLib_ErrorCode c_Spark_GenerateError(int deviceID,
                                         c_REVLib_ErrorCode error);

c_REVLib_ErrorCode c_Spark_Configure(c_Spark_handle handle,
                                     const char* flattenedConfig,
                                     uint8_t resetSafeParameters,
                                     uint8_t persistParameters);

c_REVLib_ErrorCode c_Spark_StartFollowerMode(c_Spark_handle handle);

c_REVLib_ErrorCode c_Spark_StopFollowerMode(c_Spark_handle handle);

// Sim helpers

c_REVLib_ErrorCode c_SIM_Spark_GetSimPIDOutput(c_Spark_handle handle,
                                               float* value, float setpoint,
                                               float pv, float dt);

c_REVLib_ErrorCode c_SIM_Spark_GetSimMAXMotionPositionControlOutput(
    c_Spark_handle handle, float* value, float dt);

c_REVLib_ErrorCode c_SIM_Spark_GetSimMAXMotionVelocityControlOutput(
    c_Spark_handle handle, float* value, float dt);

c_REVLib_ErrorCode c_SIM_Spark_GetSimCurrentLimitOutput(c_Spark_handle handle,
                                                        float* value,
                                                        float appliedOutput,
                                                        float current);

void c_SIM_Spark_CreateSimExtOrAltEncoder(c_Spark_handle handle);
void c_SIM_Spark_CreateSimAbsoluteEncoder(c_Spark_handle handle);
void c_SIM_Spark_CreateSimAnalogSensor(c_Spark_handle handle);
void c_SIM_Spark_CreateSimForwardLimitSwitch(c_Spark_handle handle);
void c_SIM_Spark_CreateSimReverseLimitSwitch(c_Spark_handle handle);
void c_SIM_Spark_CreateSimFaultManager(c_Spark_handle handle);
void c_SIM_Spark_CreateSimRelativeEncoder(c_Spark_handle handle);

c_REVLib_ErrorCode c_Spark_ConfigureAsync(c_Spark_handle handle,
                                          const char* flattenedConfig,
                                          uint8_t resetSafeParameters,
                                          uint8_t persistParameters);
c_REVLib_ErrorCode c_Spark_StartFollowerModeAsync(c_Spark_handle handle);
c_REVLib_ErrorCode c_Spark_StopFollowerModeAsync(c_Spark_handle handle);

}  // extern "C"
