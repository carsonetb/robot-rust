/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/HootReplay.hpp"
#include "ctre/phoenix6/SignalLogger.hpp"
#include "ctre/phoenix6/SignalMeasurement.hpp"
#include "ctre/phoenix6/Utils.hpp"
#include <functional>

namespace ctre {
namespace phoenix6 {

/**
 * \brief Class for handling automatic logging and replay of custom signal inputs.
 * Each subsystem typically creates a new instance of this class.
 *
 * Note that all StatusSignals are automatically logged and replayed, so they
 * do not need to be registered with this class. Additionally, the SignalLogger
 * must be separately started at the start of the robot program.
 *
 * \details "Inputs" are signals measured directly from devices that should be
 * replayed unmodified. By comparison, a processed signal, such as a signal
 * indicating that a mechanism has reached the target, is considered an "output".
 * This class should only be used with inputs.
 *
 * Inputs are registered with a getter that returns a value to log and a setter
 * that updates the value in your robot program. For example, a `Vision` class
 * with a `Pose2d cameraPose` input would register the input using:
 *
 * ```
 * HootAutoReplay autoReplay = HootAutoReplay{}
 *   .WithStruct<frc::Pose2d>(
 *     "Vision/CameraPose",
 *     [this]() -> frc::Pose2d const& { return cameraPose; },
 *     [this](SignalMeasurement<frc::Pose2d> val) {
 *         cameraPose = val.value;
 *     }
 *   );
 * ```
 *
 * After registering all relevant inputs, call #Update() periodically
 * to perform the following:
 *
 * - In normal/simulated robot operation, registered inputs will be
 *   fetched from your robot code using the provided getter, and then
 *   logged using the SignalLogger.
 *
 * - During Hoot Replay, registered inputs will be fetched from
 *   HootReplay and then updated in your robot code using the
 *   provided setter.
 *
 * Note that for non-primitive types, the getter function must return a
 * reference to or std::span over the original data. As a result, they cannot
 * return temporary values. If a getter lambda must return a temporary value,
 * capture a unique_ptr or shared_ptr in the lambda, then modify and return the
 * value of the unique_ptr/shared_ptr.
 */
class HootAutoReplay {
    std::vector<std::function<void()>> updates;

public:
    /**
     * \brief Updates the state of the robot program by doing one of the following:
     *
     * - In normal/simulated robot operation, registered signals will be
     *   fetched from your robot code using the provided getter, and then
     *   logged using the SignalLogger.
     *
     * - During Hoot Replay, registered signals will be fetched from
     *   HootReplay and then updated in your robot code using the
     *   provided setter.
     *
     * This should be called periodically, typically in the subsystem.
     */
    void Update() const
    {
        for (auto const &update : updates) {
            update();
        }
    }

#if (__has_include("frc/RobotController.h") && __has_include("frc/Timer.h")) || defined(_CTRE_DOCS_)
    /**
     * \brief Registers Timer::GetTimestamp() logging and playback with this
     * instance. This should only be applied to one instance in the robot
     * program.
     *
     * The #Update() of this HootAutoReplay instance must be run at the
     * start of RobotPeriodic() before the CommandScheduler is run.
     *
     * \returns this object
     */
    HootAutoReplay &WithTimestampReplay();
#endif

#if (__has_include("frc/DriverStation.h") && __has_include("frc/simulation/DriverStationSim.h")) || defined(_CTRE_DOCS_)
    /**
     * \brief Registers joystick logging and playback with this instance.
     * This should only be applied to one instance in the robot program.
     *
     * To get joysticks to playback during Hoot Replay, "Turn off DS" must be
     * checked in the simulation GUI (under "DS" at the top of the window).
     * Additionally, the #Update() of this HootAutoReplay instance must be run
     * at the start of RobotPeriodic() before the CommandScheduler is run.
     *
     * \returns this object
     */
    HootAutoReplay &WithJoystickReplay();
#endif

    /**
     * \brief Registers the schema-serialized bytes as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param schemaName Name of the schema
     * \param type Type of the schema, such as struct or protobuf
     * \param schema Schema bytes to write
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithSchemaValue(
        std::string name, std::string schemaName,
        HootSchemaType type, std::span<uint8_t const> schema,
        std::function<std::span<uint8_t const>()> getter,
        std::function<void(SignalMeasurement<std::vector<uint8_t>>)> setter
    );

    /**
     * \brief Registers the schema-serialized bytes as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param schemaName Name of the schema
     * \param type Type of the schema, such as struct or protobuf
     * \param schema Schema string to write
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithSchemaValue(
        std::string name, std::string schemaName,
        HootSchemaType type, std::string_view schema,
        std::function<std::span<uint8_t const>()> getter,
        std::function<void(SignalMeasurement<std::vector<uint8_t>>)> setter
    );

#if __has_include("wpi/struct/Struct.h") || defined(_CTRE_DOCS_)
    /**
     * \brief Registers the WPILib Struct as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param info Optional struct type info
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    template <typename T, typename... I>
        requires wpi::StructSerializable<T, I...>
    HootAutoReplay &WithStruct(
        std::string name, I &&... info,
        std::function<T const &()> getter,
        std::function<void(SignalMeasurement<T>)> setter
    ) {
        if (utils::IsReplay()) {
            updates.emplace_back([name=std::move(name), ... info = std::forward<I>(info), setter=std::move(setter)] {
                auto val = HootReplay::GetStruct<T>(name, info...);
                if (val.status.IsOK() && val.value) {
                    SignalMeasurement<T> v{
                        std::move(val.name),
                        std::move(*val.value),
                        val.timestamp,
                        std::move(val.units),
                        val.status
                    };
                    setter(std::move(v));
                }
            });
        } else {
            updates.emplace_back([name=std::move(name), ... info = std::forward<I>(info), getter=std::move(getter)] {
                SignalLogger::WriteStruct(name, info..., getter());
            });
        }
        return *this;
    }

    /**
     * \brief Registers the array of WPILib Structs as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param info Optional struct type info
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    template <typename T, typename... I>
        requires wpi::StructSerializable<T, I...>
    HootAutoReplay &WithStructArray(
        std::string name, I &&... info,
        std::function<std::span<T const>()> getter,
        std::function<void(SignalMeasurement<std::vector<T>>)> setter
    ) {
        if (utils::IsReplay()) {
            updates.emplace_back([name=std::move(name), ... info = std::forward<I>(info), setter=std::move(setter)] {
                auto val = HootReplay::GetStructArray<T>(name, info...);
                if (val.status.IsOK() && val.value) {
                    SignalMeasurement<std::vector<T>> v{
                        std::move(val.name),
                        std::move(*val.value),
                        val.timestamp,
                        std::move(val.units),
                        val.status
                    };
                    setter(std::move(v));
                }
            });
        } else {
            updates.emplace_back([name=std::move(name), ... info = std::forward<I>(info), getter=std::move(getter)] {
                SignalLogger::WriteStructArray(name, info..., getter());
            });
        }
        return *this;
    }
#endif

#if __has_include("wpi/protobuf/Protobuf.h") || defined(_CTRE_DOCS_)
    /**
     * \brief Registers the protobuf as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    template <wpi::ProtobufSerializable T>
    HootAutoReplay &WithProtobuf(
        std::string name,
        std::function<T const &()> getter,
        std::function<void(SignalMeasurement<T>)> setter
    ) {
        if (utils::IsReplay()) {
            updates.emplace_back([name=std::move(name), setter=std::move(setter)] {
                auto val = HootReplay::GetProtobuf<T>(name);
                if (val.status.IsOK() && val.value) {
                    SignalMeasurement<T> v{
                        std::move(val.name),
                        std::move(*val.value),
                        val.timestamp,
                        std::move(val.units),
                        val.status
                    };
                    setter(std::move(v));
                }
            });
        } else {
            updates.emplace_back([name=std::move(name), getter=std::move(getter)] {
                SignalLogger::WriteProtobuf(name, getter());
            });
        }
        return *this;
    }
#endif

    /**
     * \brief Registers the raw data bytes as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithRaw(
        std::string name,
        std::function<std::span<uint8_t const>()> getter,
        std::function<void(SignalMeasurement<std::vector<uint8_t>>)> setter
    );

    /**
     * \brief Registers the boolean as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithBoolean(
        std::string name,
        std::function<bool()> getter,
        std::function<void(SignalMeasurement<bool>)> setter
    );

    /**
     * \brief Registers the integer as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithInteger(
        std::string name,
        std::function<int64_t()> getter,
        std::function<void(SignalMeasurement<int64_t>)> setter
    );

    /**
     * \brief Registers the float as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithFloat(
        std::string name,
        std::function<float()> getter,
        std::function<void(SignalMeasurement<float>)> setter
    );

    /**
     * \brief Registers the double as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithDouble(
        std::string name,
        std::function<double()> getter,
        std::function<void(SignalMeasurement<double>)> setter
    );

    /**
     * \brief Registers the string as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithString(
        std::string name,
        std::function<std::string_view()> getter,
        std::function<void(SignalMeasurement<std::string>)> setter
    );

    /**
     * \brief Registers the unit value as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    template <typename U>
        requires units::traits::is_unit_t_v<U>
    HootAutoReplay &WithValue(
        std::string name,
        std::function<U()> getter,
        std::function<void(SignalMeasurement<U>)> setter
    ) {
        if (utils::IsReplay()) {
            updates.emplace_back([name=std::move(name), setter=std::move(setter)] {
                auto val = HootReplay::GetValue<U>(name);
                if (val.status.IsOK()) {
                    setter(std::move(val));
                }
            });
        } else {
            updates.emplace_back([name=std::move(name), getter=std::move(getter)] {
                SignalLogger::WriteValue(name, getter());
            });
        }
        return *this;
    }

    /**
     * \brief Registers the array of booleans as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithBooleanArray(
        std::string name,
        std::function<std::span<bool const>()> getter,
        std::function<void(SignalMeasurement<std::vector<uint8_t>>)> setter
    );

    /**
     * \brief Registers the array of booleans as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithBooleanArray(
        std::string name,
        std::function<std::span<uint8_t const>()> getter,
        std::function<void(SignalMeasurement<std::vector<uint8_t>>)> setter
    );

    /**
     * \brief Registers the array of integers as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithIntegerArray(
        std::string name,
        std::function<std::span<int64_t const>()> getter,
        std::function<void(SignalMeasurement<std::vector<int64_t>>)> setter
    );

    /**
     * \brief Registers the array of floats as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithFloatArray(
        std::string name,
        std::function<std::span<float const>()> getter,
        std::function<void(SignalMeasurement<std::vector<float>>)> setter
    );

    /**
     * \brief Registers the array of doubles as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithDoubleArray(
        std::string name,
        std::function<std::span<double const>()> getter,
        std::function<void(SignalMeasurement<std::vector<double>>)> setter
    );

    /**
     * \brief Registers the array of strings as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithStringArray(
        std::string name,
        std::function<std::span<std::string_view const>()> getter,
        std::function<void(SignalMeasurement<std::vector<std::string>>)> setter
    );

    /**
     * \brief Registers the array of strings as a Hoot-Replayed input.
     *
     * \param name Name of the signal in the log
     * \param getter Function that returns the current value of the input
     * \param setter Function that sets the input to a new value
     * \returns this object
     */
    HootAutoReplay &WithStringArray(
        std::string name,
        std::function<std::span<std::string const>()> getter,
        std::function<void(SignalMeasurement<std::vector<std::string>>)> setter
    );
};

}
}
