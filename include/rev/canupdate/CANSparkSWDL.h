/*
 * Copyright (c) 2018-2025 REV Robotics
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

#include <memory>

extern "C" {

/**
 * Set the list of devices to update.
 * @param numDevicesToAdd The total number of devices you wish to update
 * @param deviceIDlist The device IDs you wish to update as an array of
 * integers.
 * @return True if the devices were set successfully, false if there was an
 * error
 */
bool c_Spark_SetSWDLDevices(int numDevicesToAdd, const int* deviceIDlist);

/**
 * Close, free, and reset the SWDL state.
 */
void c_Spark_ResetSWDL(void);

/**
 * Set the SWDL binary file to be used for the update and load it into memory.
 * @param binFileName The name of the binary file to load. This file should be
 * in the
 * @param buffer A reference to a pointer that will point to the loaded binary
 * data.
 * @return false if there was an error opening the file, reading it, or if there
 * are no devices set
 */
bool c_Spark_PrepSWDLBinFile(const char* binFileName,
                             std::unique_ptr<uint8_t[]>& buffer,
                             size_t* fileLen);

/**
 * Iterate through the SWDL process, allowing for progress updates.
 * Devices must be set before calling this function.
 * This function should be called repeatedly until it returns 100% or -1
 * (error). It resets state on error but not completion. This function is not
 * thread-safe, and only one thread should call it at a time.
 * @param dfuFilePath The path to the DFU file.
 * @param binFilePath The path to the binary file.
 * @return The current progress percentage (0-100) or -1 if an error occurs.
 */
int c_Spark_IterateSWDL(const char* dfuFilePath, const char* binFilePath);

/**
 * Check if the checksum fail frame is present in the last 5 seconds.
 * This function checks if the checksum fail frame is present in the SWDL
 * process. A delay should be added before calling this function.
 * @param deviceId The device ID to check for the checksum fail frame.
 * @return true if the checksum fail frame is present, false otherwise.
 */
bool c_Spark_SWDLChecksumFailFramePresent(void);

}  // extern "C"
