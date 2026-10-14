/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix6/HootSchemaType.hpp"
#include "ctre/phoenix6/SignalMeasurement.hpp"
#include <units/time.h>
#include <string>
#include <vector>

#if __has_include("wpi/struct/Struct.h")
#include "wpi/struct/Struct.h"
#endif
#if __has_include("wpi/protobuf/Protobuf.h")
#include "wpi/protobuf/Protobuf.h"
#endif

namespace ctre {
namespace phoenix6 {

/**
 * \brief Static class for controlling Phoenix 6 hoot log replay.
 *
 * This replays all signals in the given hoot log in simulation. Hoot logs can
 * be created by a robot program using SignalLogger. Only one hoot log,
 * corresponding to one CAN bus, may be replayed at a time.
 *
 * The signal logger always runs while replay is running. All custom signals written
 * during replay will be automatically placed under `hoot_replay/`. Additionally, the
 * log will contain all status signals and custom signals from the original log.
 *
 * During replay, all transmits from the robot program are ignored. This includes
 * features such as control requests, configs, and setting signal update frequency.
 * Additionally, Tuner X is not functional during log replay.
 *
 * To use Hoot Replay, call LoadFile(char const *) before any devices are constructed
 * to load a hoot file and start replay. Alternatively, the CANBus(std::string_view, char const *)
 * constructor can be used when constructing devices.
 *
 * After devices are constructed, Hoot Replay can be controlled using Play(), Pause(), Stop(),
 * and Restart(). Additionally, Hoot Replay supports StepTiming(units::second_t) while paused.
 * The current file can be closed using CloseFile(), after which a new file may be loaded.
 */
class HootReplay {
public:
    /**
     * \brief Loads the given file and starts signal log replay. Only one
     * hoot log, corresponding to one CAN bus, may be replayed at a time.
     *
     * This must be called before constructing any devices or checking
     * CAN bus status. The CANBus(std::string_view, char const *)
     * constructor can be used when constructing devices to guarantee
     * that this API is called first.
     *
     * When using relative paths, the file path is typically relative
     * to the top-level folder of the robot project.
     *
     * This API is blocking on the file read.
     *
     * \param filepath Path and name of the hoot file to load
     * \returns Status of opening and reading the file for replay
     * \throws std::invalid_argument - The file is invalid, unlicensed, or
     *         targets a different version of Phoenix 6
     */
    static ctre::phoenix::StatusCode LoadFile(char const *filepath);
    /**
     * \brief Ends the hoot log replay. This stops the replay if it is running,
     * closes the hoot log, and clears all signals read from the file.
     */
    static void CloseFile();
    /**
     * \brief Gets whether a valid hoot log file is currently loaded.
     *
     * \returns true if a valid hoot log file is loaded
     */
    static bool IsFileLoaded();

    /**
     * \brief Starts or resumes the hoot log replay.
     *
     * \returns Status of starting or resuming replay
     */
    static ctre::phoenix::StatusCode Play();
    /**
     * \brief Pauses the hoot log replay. This maintains the current position
     * in the log replay so it can be resumed later.
     *
     * \returns Status of pausing replay
     */
    static ctre::phoenix::StatusCode Pause();
    /**
     * \brief Stops the hoot log replay. This resets the current position in
     * the log replay to the start.
     *
     * \returns Status of stopping replay
     */
    static ctre::phoenix::StatusCode Stop();
    /**
     * \brief Restarts the hoot log replay from the start of the log.
     * This is equivalent to calling #Stop followed by #Play.
     *
     * \returns Status of restarting replay
     */
    static ctre::phoenix::StatusCode Restart()
    {
        auto retval = Stop();
        if (retval.IsOK()) {
            retval = Play();
        }
        return retval;
    }

    /**
     * \brief Gets whether hoot log replay is actively playing.
     *
     * This API will return true in programs that do not support
     * replay, making it safe to call without first checking if
     * the program supports replay.
     *
     * \returns true if replay is playing back signals
     */
    static bool IsPlaying()
    {
        return WaitForPlaying(0_s);
    }

    /**
     * \brief Waits until hoot log replay is actively playing.
     *
     * This API will immediately return true in programs that do
     * not support replay, making it safe to call without first
     * checking if the program supports replay
     *
     * Since this can block the calling thread, this should not
     * be called with a non-zero timeout on the main thread.
     *
     * This can also be used with a timeout of 0 to perform
     * a non-blocking check, which is equivalent to #IsPlaying.
     *
     * \param timeout Max time to wait for replay to start playing
     * \returns true if replay is playing back signals
     */
    static bool WaitForPlaying(units::second_t timeout)
    {
        return WaitForPlayingImpl(timeout.value());
    }

    /**
     * \brief Gets whether hoot log replay has reached the end of the log.
     *
     * \returns true if replay has reached the end of the log, or
     *          if no log is currently loaded
     */
    static bool IsFinished();

    /**
     * \brief Sets the speed of the hoot log replay. A speed of 1.0 corresponds
     * to replaying the file in real time, and larger values increase the speed.
     *
     * - Minimum Value: 0.01
     * - Maximum Value: 100.0
     * - Default Value: 1.0
     *
     * \param speed Speed of the hoot log replay
     */
    static void SetSpeed(double speed);
    /**
     * \brief Advances the hoot log replay time by the given value. Replay must
     * be paused or stopped before advancing its time.
     *
     * \param stepTimeSeconds The amount of time to advance
     * \returns Status of advancing the replay time
     */
    static ctre::phoenix::StatusCode StepTiming(units::time::second_t stepTimeSeconds)
    {
        return StepTimingImpl(stepTimeSeconds.value());
    }

    /**
     * \brief Gets a schema-serialized user signal.
     *
     * In an FRC robot program, users can call #GetStruct, #GetStructArray,
     * and #GetProtobuf to directly get schema values instead.
     *
     * \param name Name of the signal
     * \param type Type of the associated schema, such as struct or protobuf
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<std::vector<uint8_t>> GetSchemaValue(std::string_view name, HootSchemaType type)
    {
        return GetSchemaValueImpl(name, type).ToSignalMeasurement();
    }

#if __has_include("wpi/struct/Struct.h") || defined(_CTRE_DOCS_)
    /**
     * \brief Gets a WPILib Struct user signal.
     *
     * \param name Name of the signal
     * \param info Optional struct type info
     * \returns Structure with all information about the signal
     */
    template <typename T, typename... I>
        requires wpi::StructSerializable<T, I...>
    static SignalMeasurement<std::optional<T>> GetStruct(std::string_view name, I const &... info)
    {
        auto rawSig = GetSchemaValue(name, HootSchemaType::Struct);

        std::optional<T> value;
        if (rawSig.status.IsOK()) {
            if (rawSig.value.size() == wpi::Struct<T>::GetSize(info...)) {
                value = wpi::Struct<T>::Unpack(rawSig.value, info...);
            } else {
                value = std::nullopt;
                rawSig.status = ctre::phoenix::StatusCode::InvalidParamValue;
            }
        } else {
            value = std::nullopt;
        }

        return {
            rawSig.name,
            std::move(value),
            rawSig.timestamp,
            std::move(rawSig.units),
            rawSig.status
        };
    }
    /**
     * \brief Gets a WPILib Struct array user signal.
     *
     * \param name Name of the signal
     * \param info Optional struct type info
     * \returns Structure with all information about the signal
     */
    template <typename T, typename... I>
        requires wpi::StructSerializable<T, I...>
    static SignalMeasurement<std::optional<std::vector<T>>> GetStructArray(std::string_view name, I const &... info)
    {
        auto rawSig = GetSchemaValue(name, HootSchemaType::Struct);

        std::optional<std::vector<T>> value;
        if (rawSig.status.IsOK()) {
            std::span<uint8_t const> data{rawSig.value};
            auto const size = wpi::Struct<T>::GetSize(info...);
            size_t const arr_size = data.size() / size;

            if (arr_size * size == data.size()) {
                std::vector<T> arr;
                arr.reserve(arr_size);
                for (size_t i = 0; i < arr_size; ++i) {
                    arr.emplace_back(wpi::UnpackStruct<T>(data, info...));
                    data = data.subspan(size);
                }
                value = std::move(arr);
            } else {
                value = std::nullopt;
                rawSig.status = ctre::phoenix::StatusCode::InvalidParamValue;
            }
        } else {
            value = std::nullopt;
        }

        return {
            rawSig.name,
            std::move(value),
            rawSig.timestamp,
            std::move(rawSig.units),
            rawSig.status
        };
    }
#endif

#if __has_include("wpi/protobuf/Protobuf.h") || defined(_CTRE_DOCS_)
    /**
     * \brief Gets a Protobuf user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    template <wpi::ProtobufSerializable T>
    static SignalMeasurement<std::optional<T>> GetProtobuf(std::string_view name)
    {
        auto rawSig = GetSchemaValue(name, HootSchemaType::Protobuf);
        return {
            rawSig.name,
            rawSig.status.IsOK()
                ? wpi::ProtobufMessage<T>{}.Unpack(rawSig.value)
                : std::nullopt,
            rawSig.timestamp,
            std::move(rawSig.units),
            rawSig.status
        };
    }
#endif

    /**
     * \brief Gets a raw-bytes user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<std::vector<uint8_t>> GetRaw(std::string_view name)
    {
        return GetRawImpl(name).ToSignalMeasurement();
    }
    /**
     * \brief Gets a boolean user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<bool> GetBoolean(std::string_view name)
    {
        return GetBooleanImpl(name).ToSignalMeasurement();
    }
    /**
     * \brief Gets an integer user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<int64_t> GetInteger(std::string_view name)
    {
        return GetIntegerImpl(name).ToSignalMeasurement();
    }
    /**
     * \brief Gets a float user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<float> GetFloat(std::string_view name)
    {
        return GetFloatImpl(name).ToSignalMeasurement();
    }
    /**
     * \brief Gets a double user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<double> GetDouble(std::string_view name)
    {
        return GetDoubleImpl(name).ToSignalMeasurement();
    }

    /**
     * \brief Gets a unit value user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    template <typename U>
        requires units::traits::is_unit_t_v<U>
    static SignalMeasurement<U> GetValue(std::string_view name)
    {
        SignalMeasurement<double> doubleSig = GetDouble(name);
        return {
            doubleSig.name,
            U{doubleSig.value},
            doubleSig.timestamp,
            std::move(doubleSig.units),
            doubleSig.status
        };
    }

    /**
     * \brief Gets a string user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<std::string> GetString(std::string_view name)
    {
        return GetStringImpl(name).ToSignalMeasurement();
    }
    /**
     * \brief Get a boolean array user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<std::vector<uint8_t>> GetBooleanArray(std::string_view name)
    {
        return GetBooleanArrayImpl(name).ToSignalMeasurement();
    }
    /**
     * \brief Get an integer array user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<std::vector<int64_t>> GetIntegerArray(std::string_view name)
    {
        return GetIntegerArrayImpl(name).ToSignalMeasurement();
    }
    /**
     * \brief Get a float array user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<std::vector<float>> GetFloatArray(std::string_view name)
    {
        return GetFloatArrayImpl(name).ToSignalMeasurement();
    }
    /**
     * \brief Get a double array user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<std::vector<double>> GetDoubleArray(std::string_view name)
    {
        return GetDoubleArrayImpl(name).ToSignalMeasurement();
    }
    /**
     * \brief Get a string array user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalMeasurement<std::vector<std::string>> GetStringArray(std::string_view name)
    {
        return GetStringArrayImpl(name).ToSignalMeasurement();
    }

private:
    static bool WaitForPlayingImpl(double timeoutSeconds);
    static ctre::phoenix::StatusCode StepTimingImpl(double stepTimeSeconds);

    template <typename T>
    struct UnitlessSignalData {
        std::string_view name;
        T value;
        double timestampSec;
        std::string units;
        ctre::phoenix::StatusCode status;

        SignalMeasurement<T> ToSignalMeasurement() &&
        {
            return {
                name,
                std::move(value),
                timestampSec * 1_s,
                std::move(units),
                status
            };
        }
    };

    static UnitlessSignalData<std::vector<uint8_t>> GetSchemaValueImpl(std::string_view name, HootSchemaType type);
    static UnitlessSignalData<std::vector<uint8_t>> GetRawImpl(std::string_view name);
    static UnitlessSignalData<bool> GetBooleanImpl(std::string_view name);
    static UnitlessSignalData<int64_t> GetIntegerImpl(std::string_view name);
    static UnitlessSignalData<float> GetFloatImpl(std::string_view name);
    static UnitlessSignalData<double> GetDoubleImpl(std::string_view name);
    static UnitlessSignalData<std::string> GetStringImpl(std::string_view name);
    static UnitlessSignalData<std::vector<uint8_t>> GetBooleanArrayImpl(std::string_view name);
    static UnitlessSignalData<std::vector<int64_t>> GetIntegerArrayImpl(std::string_view name);
    static UnitlessSignalData<std::vector<float>> GetFloatArrayImpl(std::string_view name);
    static UnitlessSignalData<std::vector<double>> GetDoubleArrayImpl(std::string_view name);
    static UnitlessSignalData<std::vector<std::string>> GetStringArrayImpl(std::string_view name);
};

}
}
