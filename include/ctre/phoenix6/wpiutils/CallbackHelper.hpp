/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include <hal/Value.h>

namespace ctre {
namespace phoenix6 {
namespace wpiutils {

class CallbackHelper
{
public:
    static double GetRawValue(HAL_Value const *value)
    {
        switch (value->type)
        {
        case HAL_DOUBLE:
            return value->data.v_double;
        case HAL_BOOLEAN:
            return value->data.v_boolean;
        case HAL_INT:
            return value->data.v_int;
        case HAL_LONG:
            return value->data.v_long;
        case HAL_ENUM:
            return value->data.v_enum;
        default:
            return 0;
        }
    }
};

} // namespace wpiutils
} // namespace phoenix6
} // namespace ctre