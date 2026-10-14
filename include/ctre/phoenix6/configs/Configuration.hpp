/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix6/Serializable.hpp"
#include <iosfwd>

namespace ctre {
namespace phoenix6 {
namespace configs {

class ParentConfiguration : public ISerializable {
public:
    virtual std::string ToString() const = 0;
    friend std::ostream &operator<<(std::ostream &str, ParentConfiguration const &v);
    virtual ctre::phoenix::StatusCode Deserialize(std::string const &string) = 0;
};

class EmptyConfiguration : public configs::ParentConfiguration {
public:
    constexpr EmptyConfiguration() = default;

    std::string ToString() const override
    {
        return "";
    }
    std::string Serialize() const override
    {
        return "";
    }
    ctre::phoenix::StatusCode Deserialize(std::string const &) override
    {
        return ctre::phoenix::StatusCode::OK;
    }
};

}
}
}
