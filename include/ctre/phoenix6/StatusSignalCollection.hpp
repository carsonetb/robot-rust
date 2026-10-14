/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/StatusSignal.hpp"
#include <vector>

namespace ctre {
namespace phoenix6 {

    /**
     * \brief Class to manage bulk refreshing device status signals.
     *
     * This class does not own copies of the provided status signals. As a result,
     * the usage of this class cannot outlive the lifetime of the status signals.
     */
    class StatusSignalCollection {
    protected:
        /** Signals stored by this collection */
        std::vector<BaseStatusSignal *> _signals;

    public:
        /**
         * \brief Creates a new collection of status signals, optionally
         * adding the provided signals to the collection.
         *
         * This collection does not own copies of the provided status signals.
         * As a result, the usage of this collection cannot outlive the lifetime
         * of the status signals.
         *
         * \param signals Signals to add, passed as a comma-separated list of signal references
         */
        template <std::derived_from<BaseStatusSignal>... Signals>
        StatusSignalCollection(Signals &... signals) :
            _signals{(&signals)...}
        {}
        /**
         * \brief Creates a new collection of status signals, adding the
         * provided span of signals to the collection.
         *
         * This collection does not own copies of the provided status signals.
         * As a result, the usage of this collection cannot outlive the lifetime
         * of the status signals.
         *
         * \param signals Signals to add, passed as a span of signal pointers
         */
        StatusSignalCollection(std::span<BaseStatusSignal *const> signals) :
            _signals(signals.begin(), signals.end())
        {}

        /**
         * \brief Creates a new collection of status signals, reserving
         * capacity for the specified number of signals.
         *
         * \param signalCount Number of signals to reserve space for
         */
        StatusSignalCollection(size_t signalCount)
        {
            _signals.reserve(signalCount);
        }

        /**
         * \brief Adds the provided signals to the collection.
         *
         * This collection does not own copies of the provided status signals.
         * As a result, the usage of this collection cannot outlive the lifetime
         * of the status signals.
         *
         * \param signals Signals to add, passed as a comma-separated list of signal references
         */
        template <std::derived_from<BaseStatusSignal>... Signals>
        void AddSignals(Signals &... signals)
        {
            return AddSignals(std::array<BaseStatusSignal *, sizeof...(Signals)>{(&signals)...});
        }

        /**
         * \brief Adds the provided signals to the collection.
         *
         * This collection does not own copies of the provided status signals.
         * As a result, the usage of this collection cannot outlive the lifetime
         * of the status signals.
         *
         * \param signals Signals to add, passed as a span of signal pointers
         */
        void AddSignals(std::span<BaseStatusSignal *const> signals)
        {
            _signals.insert(_signals.end(), signals.begin(), signals.end());
        }

        /**
         * \brief Waits for new data on all signals up to timeout.
         *        This API is typically used with CANivore Bus signals as they will be synced using the
         *        CANivore Timesync feature and arrive simultaneously. Signals on a roboRIO bus cannot
         *        be synced and may require a significantly longer blocking call to receive all signals.
         *
         *        Note that CANivore Timesync requires Phoenix Pro.
         *
         *        This can also be used with a timeout of zero to refresh many signals at once, which
         *        is faster than calling Refresh() on every signal. This is equivalent to calling #RefreshAll.
         *
         *        If a signal arrives multiple times while waiting, such as when *not* using CANivore
         *        Timesync, the newest signal data is fetched. Additionally, if this function times out,
         *        the newest signal data is fetched for all signals (when possible). We recommend checking
         *        the individual status codes using BaseStatusSignal#GetStatus() when this happens.
         *
         * \param timeout Maximum time to wait for all the signals to arrive.
         *                Pass zero to refresh all signals without blocking.
         * \param reportError Whether to report any errors to the Driver Station/stderr
         * \return InvalidNetwork if signals are on different CAN bus networks,
         *         RxTimeout if it took longer than timeoutSeconds to receive all the signals,
         *         MultiSignalNotSupported if using the roboRIO bus with more than one signal and a non-zero timeout.
         *         An OK status code means that all signals arrived within timeoutSeconds and they are all OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        ctre::phoenix::StatusCode WaitForAll(units::time::second_t timeout, bool reportError = true)
        {
            return BaseStatusSignal::WaitForAll(timeout, reportError, _signals);
        }

        /**
         * \brief Performs a non-blocking refresh on all signals.
         *
         * This provides a performance improvement over separately calling Refresh() on each signal.
         *
         * \param reportError Whether to report any errors to the Driver Station/stderr
         * \return InvalidNetwork if signals are on different CAN bus networks.
         *         An OK status code means that all signals are OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        ctre::phoenix::StatusCode RefreshAll(bool reportError = true)
        {
            return BaseStatusSignal::RefreshAll(reportError, _signals);
        }

        /**
         * \brief Sets the update frequency of all status signals to the provided common frequency.
         *
         * A frequency of 0 Hz will turn off the signal. Otherwise, the minimum supported signal frequency
         * is 4 Hz, and the maximum is 1000 Hz.
         *
         * If other StatusSignals in the same status frame have been set to an update frequency,
         * the fastest requested update frequency will be applied to the frame.
         *
         * This will wait up to 0.100 seconds (100ms) for each signal.
         *
         * \param frequency Rate to publish the signal in Hz.
         * \returns Status code of the first failed update frequency set call, or OK if all succeeded
         */
        ctre::phoenix::StatusCode SetUpdateFrequencyForAll(units::frequency::hertz_t frequency)
        {
            return BaseStatusSignal::SetUpdateFrequencyForAll(frequency, _signals);
        }

        /**
         * \brief Checks if all signals have an OK error code.
         *
         * \returns True if all signals are OK, false otherwise
         */
        bool IsAllGood() const
        {
            return BaseStatusSignal::IsAllGood(_signals);
        }
    };

}
}
