/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/Utils.hpp"

namespace ctre {
namespace phoenix6 {

    /**
     * \brief Information about the timestamp of a signal.
     */
    class Timestamp final {
    public:
        /**
         * \brief Source of the timestamp.
         */
        enum class TimestampSource {
            /**
             * Timestamp as reported by the system.
             * This timestamp is captured when the system receives the signal value.
             *
             * This timestamp is present on all systems and is guaranteed to be monotonic.
             * However, this timestamp is the least accurate due to latency from processing
             * delays within the system.
             */
            System = 0,
            /**
             * Timestamp as reported by the CANivore.
             * This timestamp is captured when the CANivore receives the signal value.
             *
             * The CANivore is synchronized to the system monotonic clock and benefits
             * from reduced latency over the TimestampSource#System timestamp.
             *
             * On the native roboRIO CAN bus, this timestamp is equivalent to the TimestampSource#System timestamp.
             *
             * When used with CANivore, the only inaccuracy in this measurement is latency
             * from CAN bus arbitration.
             */
            CANivore = 1,
            /**
             * This timestamp source requires Phoenix Pro.
             *
             * Timestamp as reported by the device.
             * This timestamp is captured when the device transmits the signal value.
             * Because it is timestamped in the device, it is the most accurate timestamp source.
             *
             * This timestamp is synchronized to the CANivore clock, which is itself synchronized
             * to the system monotonic clock. As a result, this timestamp source requires a CANivore.
             *
             * It can be assumed there is no latency between this timestamp and when the data was taken.
             */
            Device = 2,
        };

    private:
        units::time::second_t time{};
        TimestampSource source{};
        bool valid{false};

    public:
        /**
         * \brief Construct a new invalid Timestamp.
         */
        constexpr Timestamp() = default;

        /**
         * \brief Construct a new Timestamp for the given source.
         *
         * \param time The time in seconds
         * \param source The timestamp source
         * \param valid Whether the timestamp is valid
         */
        constexpr Timestamp(units::time::second_t time, TimestampSource source, bool valid = true) :
            time{time},
            source{source},
            valid{valid}
        {}

        /**
         * \brief Get the time in seconds as reported from this timestamp
         *
         * \returns Time in seconds
         */
        constexpr units::time::second_t GetTime() const
        {
            return this->time;
        }
        /**
         * \brief Get the source of this timestamp
         *
         * \returns Source of this timestamp
         */
        constexpr TimestampSource GetSource() const
        {
            return this->source;
        }
        /**
         * \brief Get the latency of this timestamp compared to now
         *
         * \returns Difference between now and this timestamp
         */
        units::time::second_t GetLatency() const
        {
            return utils::GetCurrentTime() - this->time;
        }
        /**
         * \brief Returns if this Timestamp is valid or not.
         *
         * \returns true when this is valid
         */
        constexpr bool IsValid() const
        {
            return this->valid;
        }
    };

    /**
     * \brief A collection of timestamps for a received signal.
     */
    class AllTimestamps final {
    private:
        Timestamp systemTimestamp{};
        Timestamp canivoreTimestamp{};
        Timestamp deviceTimestamp{};

    public:
        void Update(Timestamp const &newSystemTimestamp, Timestamp const &newCanivoreTimestamp, Timestamp const &newDeviceTimestamp)
        {
            systemTimestamp = newSystemTimestamp;
            canivoreTimestamp = newCanivoreTimestamp;
            deviceTimestamp = newDeviceTimestamp;
        }

        /**
         * \brief Get the most accurate timestamp available.
         *
         * \details The timestamp sources from most to least accurate are:
         *
         * - Timestamp#TimestampSource#Device
         * - Timestamp#TimestampSource#CANivore
         * - Timestamp#TimestampSource#System
         *
         * Note that some of these sources may not be available.
         *
         * \returns The most accurate timestamp available
         */
        Timestamp const &GetBestTimestamp() const
        {
            if (deviceTimestamp.IsValid()) {
                return deviceTimestamp;
            }
            if (canivoreTimestamp.IsValid()) {
                return canivoreTimestamp;
            }
            /* System timestamp is always available */
            return systemTimestamp;
        }

        /**
         * \brief Get the timestamp as reported by the Timestamp#TimestampSource#System source.
         *
         * \returns Timestamp as reported by the System
         */
        Timestamp const &GetSystemTimestamp() const { return systemTimestamp; }
        /**
         * \brief Get the timestamp as reported by the Timestamp#TimestampSource#CANivore source.
         *
         * \returns Timestamp as reported by the CANivore
         */
        Timestamp const &GetCANivoreTimestamp() const { return canivoreTimestamp; }
        /**
         * \brief Get the timestamp as reported by the Timestamp#TimestampSource#Device source.
         *
         * \returns Timestamp as reported by the device
         */
        Timestamp const &GetDeviceTimestamp() const { return deviceTimestamp; }
    };

}
}
