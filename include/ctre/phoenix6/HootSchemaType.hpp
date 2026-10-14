/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

namespace ctre {
namespace phoenix6 {

    /**
     * \brief Supported schema types for a hoot user signal.
     */
    enum class HootSchemaType {
        /**
         * \brief Serialize using the WPILib Struct format.
         */
        Struct = 1,
        /**
         * \brief Serialize using the Protobuf format.
         */
        Protobuf = 2,
    };

}
}
