/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "units/time.h"
#include <string>
#include <vector>

namespace ctre {
namespace phoenix6 {

/**
 * \brief Static class for controlling Phoenix 6 hoot log replay.
 *
 * This replays all signals in the given hoot log in simulation. Hoot logs can
 * be created by a robot program using SignalLogger. Only one hoot log,
 * corresponding to one CAN bus, may be replayed at a time.
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
     * \brief Stores information about a user signal from replay.
     */
    template <typename T>
    struct SignalData {
        /**
         * \brief The name of the signal
         */
        std::string_view name;
        /**
         * \brief The units of the signal
         */
        std::string units;
        /**
         * \brief The timestamp of the signal
         */
        units::second_t timestamp;
        /**
         * \brief Status code response of getting the signal
         */
        ctre::phoenix::StatusCode status;
        /**
         * \brief The value of the signal
         */
        T value;
    };

    /**
     * \brief Gets a raw-bytes user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalData<std::vector<uint8_t>> GetRaw(std::string_view name)
    {
        return GetRawImpl(name).ToSignalData();
    }
    /**
     * \brief Gets a boolean user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalData<bool> GetBoolean(std::string_view name)
    {
        return GetBooleanImpl(name).ToSignalData();
    }
    /**
     * \brief Gets an integer user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalData<int64_t> GetInteger(std::string_view name)
    {
        return GetIntegerImpl(name).ToSignalData();
    }
    /**
     * \brief Gets a float user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalData<float> GetFloat(std::string_view name)
    {
        return GetFloatImpl(name).ToSignalData();
    }
    /**
     * \brief Gets a double user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalData<double> GetDouble(std::string_view name)
    {
        return GetDoubleImpl(name).ToSignalData();
    }

    /**
     * \brief Gets a unit value user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    template <typename U, typename = std::enable_if_t<units::traits::is_unit_t_v<U>>>
    static SignalData<U> GetValue(std::string_view name)
    {
        SignalData<double> doubleSig = GetDouble(name);
        return {
            doubleSig.name,
            std::move(doubleSig.units),
            doubleSig.timestamp,
            doubleSig.status,
            U{doubleSig.value}
        };
    }

    /**
     * \brief Gets a string user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalData<std::string> GetString(std::string_view name)
    {
        return GetStringImpl(name).ToSignalData();
    }
    /**
     * \brief Get a boolean array user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalData<std::vector<uint8_t>> GetBooleanArray(std::string_view name)
    {
        return GetBooleanArrayImpl(name).ToSignalData();
    }
    /**
     * \brief Get an integer array user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalData<std::vector<int64_t>> GetIntegerArray(std::string_view name)
    {
        return GetIntegerArrayImpl(name).ToSignalData();
    }
    /**
     * \brief Get a float array user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalData<std::vector<float>> GetFloatArray(std::string_view name)
    {
        return GetFloatArrayImpl(name).ToSignalData();
    }
    /**
     * \brief Get a double array user signal.
     *
     * \param name Name of the signal
     * \returns Structure with all information about the signal
     */
    static SignalData<std::vector<double>> GetDoubleArray(std::string_view name)
    {
        return GetDoubleArrayImpl(name).ToSignalData();
    }

private:
    static bool WaitForPlayingImpl(double timeoutSeconds);
    static ctre::phoenix::StatusCode StepTimingImpl(double stepTimeSeconds);

    template <typename T>
    struct UnitlessSignalData {
        std::string_view name;
        std::string units;
        double timestampSec;
        ctre::phoenix::StatusCode status;
        T value;

        SignalData<T> ToSignalData() &&
        {
            return {
                name,
                std::move(units),
                units::second_t{timestampSec},
                status,
                std::move(value)
            };
        }
    };

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
};

}
}
