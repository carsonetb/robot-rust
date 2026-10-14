/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix6/HootSchemaType.hpp"
#include <units/time.h>
#include <array>
#include <span>
#include <string>

#if __has_include("wpi/struct/Struct.h")
#include "wpi/struct/Struct.h"
#include "wpi/SmallVector.h"
#endif
#if __has_include("wpi/protobuf/Protobuf.h")
#include "wpi/protobuf/Protobuf.h"
#include "wpi/SmallVector.h"
#endif

namespace ctre {
namespace phoenix6 {

/**
 * \brief Static class for controlling the Phoenix 6 signal logger.
 *
 * This logs all the signals from the CAN buses into .hoot files. Each file name starts with the
 * CANivore serial number or "rio" for the roboRIO CAN bus, followed by the timestamp. In the
 * header of a hoot file, the CANivore name and firmware version are logged in plain text.
 *
 * During an FRC match, the log file will be renamed to include the event name, match type, and
 * match number at the start of the file name. The match type will be 'P' for practice matches,
 * 'Q' for qualification matches, and 'E' for elimination matches.
 *
 * During Hoot Replay, the signal logger always runs while replay is running. All custom signals
 * written during replay will be automatically placed under `hoot_replay/`. Additionally, the log
 * will contain all status signals and custom signals from the original log.
 */
class SignalLogger {
public:
    /**
     * \brief Sets the destination for logging, restarting logger if the path changed.
     *
     * If this is not called or the path is left empty, the default path will be used. The
     * default path on the roboRIO is a logs folder on the first USB flash drive found, or
     * /home/lvuser/logs if none is available. The default path on all other platforms is
     * a logs folder in the current working directory.
     *
     * Typical use for this routine is to use a removable USB flash drive for logging.
     *
     * This is ignored during Hoot Replay, where the hoot log will always be written to a
     * subfolder next to the log being replayed.
     *
     * \param path Folder path for the log files; path must exist
     * \returns Status of setting the path and restarting the log
     */
    static ctre::phoenix::StatusCode SetPath(const char *path);
    /**
     * \brief Starts logging status signals. Starts regardless of auto logging status.
     *
     * If using a roboRIO 1, we recommend setting the logging path to an external drive
     * using #SetPath to avoid running out of internal storage space.
     *
     * This is ignored during Hoot Replay, where logging is automatically started when
     * Hoot Replay starts running or restarts.
     *
     * \returns Status of starting the logger
     */
    static ctre::phoenix::StatusCode Start();
    /**
     * \brief Stops logging status signals. Stops regardless of auto logging status.
     *
     * This is ignored during Hoot Replay, where logging is automatically stopped when
     * Hoot Replay is stopped or reaches the end of the file.
     *
     * \returns Status of stopping the logger
     */
    static ctre::phoenix::StatusCode Stop();
    /**
     * \brief Enables or disables auto logging.
     *
     * Auto logging is enabled by default on the roboRIO and disabled by default on
     * other systems. Additionally, on a roboRIO 1, auto logging will only be active
     * if a USB flash drive is present.
     *
     * When auto logging is enabled, logging is started by any of the following
     * (whichever occurs first):
     *
     * - It has been at least 1 second since program startup (allowing for calls to
     *   #SetPath), and the robot is enabled.
     *
     * - It has been at least 5 seconds since program startup (allowing for calls to
     *   #SetPath), and the Driver Station is connected to the robot (if on a roboRIO).
     *
     * After auto logging has started the log once, logging will not be automatically
     * stopped or restarted by auto logging.
     *
     * \param enable Whether to enable auto logging
     * \returns Status of auto logging enable/disable
     */
    static ctre::phoenix::StatusCode EnableAutoLogging(bool enable);

    /**
     * \brief Adds the schema to the log file.
     *
     * In an FRC robot program, users can call WriteStruct and WriteProtobuf
     * to directly write schema values instead.
     *
     * The schema name should typically exactly match the name of the type
     * (without any extra prefix or suffix).
     *
     * For protobuf, first register all relevant file descriptors by file name
     * (such as "geometry2d.proto"). Then, for each top-level type being used,
     * add a separate empty schema with the full name of the type (such as
     * "wpi.proto.ProtobufPose2d").
     *
     * \param name Name of the schema
     * \param type Type of the schema, such as struct or protobuf
     * \param schema Schema bytes to write
     * \returns Status of adding the schema
     */
    static ctre::phoenix::StatusCode AddSchema(std::string_view name, HootSchemaType type, std::span<uint8_t const> schema);
    /**
     * \brief Adds the schema to the log file.
     *
     * In an FRC robot program, users can call WriteStruct and WriteProtobuf
     * to directly write schema values instead.
     *
     * The schema name should typically exactly match the name of the type
     * (without any extra prefix or suffix).
     *
     * For protobuf, first register all relevant file descriptors by file name
     * (such as "geometry2d.proto"). Then, for each top-level type being used,
     * add a separate empty schema with the full name of the type (such as
     * "wpi.proto.ProtobufPose2d").
     *
     * \param name Name of the schema
     * \param type Type of the schema, such as struct or protobuf
     * \param schema Schema string to write
     * \returns Status of adding the schema
     */
    static ctre::phoenix::StatusCode AddSchema(std::string_view name, HootSchemaType type, std::string_view schema)
    {
        return AddSchema(name, type, {(uint8_t const *)schema.data(), schema.size()});
    }

    /**
     * \brief Checks if the schema has already been added to the log files.
     *
     * \param name Name of the schema
     * \param type Type of the schema, such as struct or protobuf
     * \returns Whether the schema has been added to the log files
     */
    static bool HasSchema(std::string_view name, HootSchemaType type);

    /**
     * \brief Writes the schema-serialized bytes to the log file.
     *
     * In an FRC robot program, users can call #WriteStruct, #WriteStructArray,
     * and #WriteProtobuf to directly write schema values instead.
     *
     * The name of the associated schema must exactly match the type of the
     * data (such as "Pose2d" or "wpi.proto.ProtobufPose2d"). Additionally, the
     * schema name must be registered with #AddSchema before calling this API.
     *
     * \param name Name of the signal
     * \param schema Name of the associated schema
     * \param type Type of the associated schema, such as struct or protobuf
     * \param data Span of serialized data bytes
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteSchemaValue(std::string_view name, std::string_view schema, HootSchemaType type, std::span<uint8_t const> data, units::time::second_t latencySeconds = 0_s)
    {
        return WriteSchemaValue_Impl(name, schema, type, data, latencySeconds.value());
    }

#if __has_include("wpi/struct/Struct.h") || defined(_CTRE_DOCS_)
    /**
     * \brief Writes the WPILib Struct to the log file.
     *
     * \param name Name of the signal
     * \param value Value to write
     * \param info Optional struct type info
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    template <typename T, typename... I>
        requires wpi::StructSerializable<T, I...>
    static ctre::phoenix::StatusCode WriteStruct(std::string_view name, T const &value, I const &... info, units::time::second_t latencySeconds = 0_s)
    {
        using S = wpi::Struct<T, I...>;

        auto const typeName = S::GetTypeName(info...);

        if (!HasSchema(typeName, HootSchemaType::Struct)) {
            if constexpr (wpi::HasNestedStruct<T, I...>) {
                S::ForEachNested([](std::string_view typeName, auto schema) {
                    if (typeName.starts_with("struct:")) {
                        typeName.remove_prefix(7);
                    }
                    if (!HasSchema(typeName, HootSchemaType::Struct)) {
                        AddSchema(typeName, HootSchemaType::Struct, schema);
                    }
                }, info...);
            }
            AddSchema(typeName, HootSchemaType::Struct, S::GetSchema(info...));
        }

        if constexpr (sizeof...(I) == 0) {
            if constexpr (wpi::is_constexpr([] { S::GetSize(); })) {
                std::array<uint8_t, S::GetSize()> data;
                S::Pack(data, value);
                return WriteSchemaValue(name, typeName, HootSchemaType::Struct, data, latencySeconds);
            }
        }

        wpi::SmallVector<uint8_t, 128> buf;
        buf.resize_for_overwrite(S::GetSize(info...));
        S::Pack(buf, value, info...);
        return WriteSchemaValue(name, typeName, HootSchemaType::Struct, buf, latencySeconds);
    }

    /**
     * \brief Writes the array of WPILib Structs to the log file.
     *
     * \param name Name of the signal
     * \param values Values to write
     * \param info Optional struct type info
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    template <typename T, typename... I>
        requires wpi::StructSerializable<T, I...>
    static ctre::phoenix::StatusCode WriteStructArray(std::string_view name, std::span<T const> values, I const &... info, units::time::second_t latencySeconds = 0_s)
    {
        using S = wpi::Struct<T, I...>;

        auto const typeName = MakeStructArrayTypeName<T, std::dynamic_extent>(info...);

        if (!HasSchema(typeName, HootSchemaType::Struct)) {
            wpi::ForEachStructSchema<T>([](std::string_view typeName, auto schema) {
                if (typeName.starts_with("struct:")) {
                    typeName.remove_prefix(7);
                }
                if (!HasSchema(typeName, HootSchemaType::Struct)) {
                    AddSchema(typeName, HootSchemaType::Struct, schema);
                }
            }, info...);
            AddSchema(typeName, HootSchemaType::Struct, "");
        }

        auto const size = S::GetSize(info...);
        wpi::SmallVector<uint8_t, 256> buf;
        buf.resize_for_overwrite(size * values.size());

        uint8_t *out = buf.data();
        for (auto &&val : values) {
            S::Pack(
                std::span<uint8_t>{out, size},
                std::forward<decltype(val)>(val), info...
            );
            out += size;
        }
        return WriteSchemaValue(name, typeName, HootSchemaType::Struct, buf, latencySeconds);
    }
#endif

#if __has_include("wpi/protobuf/Protobuf.h") || defined(_CTRE_DOCS_)
    /**
     * \brief Writes the protobuf to the log file.
     *
     * \param name Name of the signal
     * \param value Value to write
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    template <wpi::ProtobufSerializable T>
    static ctre::phoenix::StatusCode WriteProtobuf(std::string_view name, T const &value, units::time::second_t latencySeconds = 0_s)
    {
        std::string_view const typeName = wpi::Protobuf<std::remove_cvref_t<T>>::MessageStruct::msg_descriptor()->proto_name;

        wpi::ProtobufMessage<T> proto;
        if (!HasSchema(typeName, HootSchemaType::Protobuf)) {
            proto.ForEachProtobufDescriptor(
                [](std::string_view typeName) {
                    if (typeName.starts_with("proto:")) {
                        typeName.remove_prefix(6);
                    }
                    return HasSchema(typeName, HootSchemaType::Protobuf);
                },
                [](std::string_view typeName, auto schema) {
                    if (typeName.starts_with("proto:")) {
                        typeName.remove_prefix(6);
                    }
                    AddSchema(typeName, HootSchemaType::Protobuf, schema);
                }
            );
            AddSchema(typeName, HootSchemaType::Protobuf, "");
        }

        wpi::SmallVector<uint8_t, 128> buf;
        proto.Pack(buf, value);
        return WriteSchemaValue(name, typeName, HootSchemaType::Protobuf, buf, latencySeconds);
    }
#endif

    /**
     * \brief Writes the raw data bytes to the log file.
     *
     * \param name Name of the signal
     * \param data Span of raw data bytes
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteRaw(std::string_view name, std::span<uint8_t const> data, units::time::second_t latencySeconds = 0_s)
    {
        return WriteRaw_Impl(name, data, latencySeconds.value());
    }
    /**
     * \brief Writes the boolean to the log file.
     *
     * \param name Name of the signal
     * \param value Value to write
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteBoolean(std::string_view name, bool value, units::time::second_t latencySeconds = 0_s)
    {
        return WriteBoolean_Impl(name, value, latencySeconds.value());
    }
    /**
     * \brief Writes the integer to the log file.
     *
     * \param name Name of the signal
     * \param value Value to write
     * \param units Units of the signal
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteInteger(std::string_view name, int64_t value, std::string_view units = "", units::time::second_t latencySeconds = 0_s)
    {
        return WriteInteger_Impl(name, value, units, latencySeconds.value());
    }
    /**
     * \brief Writes the float to the log file.
     *
     * \param name Name of the signal
     * \param value Value to write
     * \param units Units of the signal
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteFloat(std::string_view name, float value, std::string_view units = "", units::time::second_t latencySeconds = 0_s)
    {
        return WriteFloat_Impl(name, value, units, latencySeconds.value());
    }
    /**
     * \brief Writes the double to the log file.
     *
     * \param name Name of the signal
     * \param value Value to write
     * \param units Units of the signal
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteDouble(std::string_view name, double value, std::string_view units = "", units::time::second_t latencySeconds = 0_s)
    {
        return WriteDouble_Impl(name, value, units, latencySeconds.value());
    }
    /**
     * \brief Writes the string to the log file.
     *
     * \param name Name of the signal
     * \param value Value to write
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteString(std::string_view name, std::string_view value, units::time::second_t latencySeconds = 0_s)
    {
        return WriteString_Impl(name, value, latencySeconds.value());
    }

    /**
     * \brief Writes the unit value to the log file.
     *
     * \param name Name of the signal
     * \param value Value to write
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    template <typename U>
        requires units::traits::is_unit_t_v<U>
    static ctre::phoenix::StatusCode WriteValue(std::string_view name, U value, units::time::second_t latencySeconds = 0_s)
    {
        return WriteDouble(name, value.value(), units::abbreviation(value), latencySeconds);
    }

    /**
     * \brief Writes the array of booleans to the log file.
     *
     * \param name Name of the signal
     * \param values Span of values to write
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteBooleanArray(std::string_view name, std::span<bool const> values, units::time::second_t latencySeconds = 0_s)
    {
        return WriteBooleanArray_Impl(name, values, latencySeconds.value());
    }
    /**
     * \brief Writes the array of booleans to the log file.
     *
     * \param name Name of the signal
     * \param values Span of values to write, passed as a span of bytes
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteBooleanArray(std::string_view name, std::span<uint8_t const> values, units::time::second_t latencySeconds = 0_s)
    {
        return WriteBooleanArray_Impl(name, values, latencySeconds.value());
    }

    /**
     * \brief Writes the array of integers to the log file.
     *
     * \param name Name of the signal
     * \param values Span of values to write
     * \param units Units of the signals
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteIntegerArray(std::string_view name, std::span<int64_t const> values, std::string_view units = "", units::time::second_t latencySeconds = 0_s)
    {
        return WriteIntegerArray_Impl(name, values, units, latencySeconds.value());
    }

    /**
     * \brief Writes the array of floats to the log file.
     *
     * \param name Name of the signal
     * \param values Span of values to write
     * \param units Units of the signals
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteFloatArray(std::string_view name, std::span<float const> values, std::string_view units = "", units::time::second_t latencySeconds = 0_s)
    {
        return WriteFloatArray_Impl(name, values, units, latencySeconds.value());
    }

    /**
     * \brief Writes the array of doubles to the log file.
     *
     * \param name Name of the signal
     * \param values Span of values to write
     * \param units Units of the signals
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteDoubleArray(std::string_view name, std::span<double const> values, std::string_view units = "", units::time::second_t latencySeconds = 0_s)
    {
        return WriteDoubleArray_Impl(name, values, units, latencySeconds.value());
    }

    /**
     * \brief Writes the array of strings to the log file.
     *
     * \param name Name of the signal
     * \param values Span of values to write
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteStringArray(std::string_view name, std::span<std::string_view const> values, units::time::second_t latencySeconds = 0_s)
    {
        return WriteStringArray_Impl(name, values, latencySeconds.value());
    }
    /**
     * \brief Writes the array of strings to the log file.
     *
     * \param name Name of the signal
     * \param values Span of values to write
     * \param latencySeconds Latency of the signal in seconds; this value is subtracted
     *                       from the current time to get the timestamp written to the log
     * \returns Status of writing the data
     */
    static ctre::phoenix::StatusCode WriteStringArray(std::string_view name, std::span<std::string const> values, units::time::second_t latencySeconds = 0_s)
    {
        return WriteStringArray_Impl(name, values, latencySeconds.value());
    }

private:
    static ctre::phoenix::StatusCode WriteRaw_Impl(std::string_view name, std::span<uint8_t const> data, double latencySeconds);
    static ctre::phoenix::StatusCode WriteBoolean_Impl(std::string_view name, bool value, double latencySeconds);
    static ctre::phoenix::StatusCode WriteInteger_Impl(std::string_view name, int64_t value, std::string_view units, double latencySeconds);
    static ctre::phoenix::StatusCode WriteFloat_Impl(std::string_view name, float value, std::string_view units, double latencySeconds);
    static ctre::phoenix::StatusCode WriteDouble_Impl(std::string_view name, double value, std::string_view units, double latencySeconds);
    static ctre::phoenix::StatusCode WriteString_Impl(std::string_view name, std::string_view value, double latencySeconds);

    static ctre::phoenix::StatusCode WriteBooleanArray_Impl(std::string_view name, std::span<bool const> values, double latencySeconds)
    {
        static_assert(sizeof(bool) == sizeof(uint8_t), "bool is not uint8_t");
        return WriteBooleanArray_Impl(name, std::span{(uint8_t const *)values.data(), values.size()}, latencySeconds);
    }
    static ctre::phoenix::StatusCode WriteBooleanArray_Impl(std::string_view name, std::span<uint8_t const> values, double latencySeconds);
    static ctre::phoenix::StatusCode WriteIntegerArray_Impl(std::string_view name, std::span<int64_t const> values, std::string_view units, double latencySeconds);
    static ctre::phoenix::StatusCode WriteFloatArray_Impl(std::string_view name, std::span<float const> values, std::string_view units, double latencySeconds);
    static ctre::phoenix::StatusCode WriteDoubleArray_Impl(std::string_view name, std::span<double const> values, std::string_view units, double latencySeconds);
    static ctre::phoenix::StatusCode WriteStringArray_Impl(std::string_view name, std::span<std::string_view const> values, double latencySeconds);
    static ctre::phoenix::StatusCode WriteStringArray_Impl(std::string_view name, std::span<std::string const> values, double latencySeconds);

    static ctre::phoenix::StatusCode WriteSchemaValue_Impl(std::string_view name, std::string_view schema, HootSchemaType type, std::span<uint8_t const> data, double latencySeconds);

#if __has_include("wpi/struct/Struct.h")
    template <typename T, size_t N, typename... I>
        requires wpi::StructSerializable<T, I...>
    static constexpr auto MakeStructArrayTypeName(I const &... info) {
        using namespace wpi;
        using S = Struct<T, typename std::remove_cvref_t<I>...>;
        if constexpr (
            sizeof...(I) == 0 &&
            is_constexpr([&info...] { S::GetTypeName(info...); })
        ) {
            constexpr auto typeName = S::GetTypeName(info...);
            using namespace literals;
            if constexpr (N == std::dynamic_extent) {
                return Concat(
                    ct_string<char, std::char_traits<char>, typeName.size()>{typeName},
                    "[]"_ct_string
                );
            } else {
                return Concat(
                    ct_string<char, std::char_traits<char>, typeName.size()>{typeName},
                    "["_ct_string, NumToCtString<N>(), "]"_ct_string
                );
            }
        } else {
            if constexpr (N == std::dynamic_extent) {
                return fmt::format("{}[]", S::GetTypeName(info...));
            } else {
                return fmt::format("{}[{}]", S::GetTypeName(info...), N);
            }
        }
    }
#endif
};

}
}
