/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include <units/frequency.h>
#include <map>
#include <memory>
#include <string>

namespace ctre {
namespace phoenix6 {

namespace hardware {
    class ParentDevice;
}

namespace controls {

    /**
     * \brief Common interface implemented by all control requests.
     */
    class ControlRequest {
        friend hardware::ParentDevice;
        virtual ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const = 0;

    protected:
        /* don't allow copy and move of the base class, only derived classes */
        constexpr ControlRequest(ControlRequest const &) = default;
        constexpr ControlRequest(ControlRequest &&) = default;
        constexpr ControlRequest &operator=(ControlRequest const &) = default;
        constexpr ControlRequest &operator=(ControlRequest &&) = default;

    public:
        /**
         * \brief Constructs a new Control Request.
         */
        constexpr ControlRequest() = default;
        constexpr virtual ~ControlRequest() {}

        /**
         * \brief Gets the name of this control request.
         *
         * \returns Name of the control request
         */
        constexpr virtual std::string_view GetName() const = 0;

        /**
         * \brief Gets information about this control request.
         *
         * \returns Map of control parameter names and corresponding applied values
         */
        virtual std::map<std::string, std::string> GetControlInfo() const = 0;

        virtual std::string ToString() const = 0;
    };

    /**
     * \brief Generic Empty Control class used to do nothing.
     */
    class EmptyControl final : public ControlRequest {
        ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override;

    public:
        /**
         * \brief Constructs an empty control request.
         */
        constexpr EmptyControl() = default;
        constexpr ~EmptyControl() override {}

        /**
         * \brief Gets the name of this control request.
         *
         * \returns Name of the control request
         */
        constexpr std::string_view GetName() const override
        {
            return "EmptyControl";
        }

        std::string ToString() const override
        {
            return "class: EmptyControl";
        }

        /**
         * \brief Gets information about this control request.
         *
         * \returns Map of control parameter names and corresponding applied values
         */
        std::map<std::string, std::string> GetControlInfo() const override;

        constexpr EmptyControl &WithUpdateFreqHz(units::frequency::hertz_t) { return *this; }
    };

}

}
}
