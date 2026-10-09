// Copyright (c) 2025 FRC 6328
// http://github.com/Mechanical-Advantage
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file at
// the root directory of this project.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void StatusLoggerDriver_start(void);

void StatusLoggerDriver_manualStart(void);

void StatusLoggerDriver_stop(void);

bool StatusLoggerDriver_getAutoLogging(void);

void StatusLoggerDriver_read(void);

void StatusLoggerDriver_disableAutoLogging(void);

#ifdef __cplusplus
}  // extern "C"
#endif
