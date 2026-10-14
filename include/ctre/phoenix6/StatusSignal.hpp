/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix6/hardware/DeviceIdentifier.hpp"
#include "ctre/phoenix6/SignalMeasurement.hpp"
#include "ctre/phoenix6/Timestamp.hpp"
#include <array>
#include <functional>
#include <map>
#include <ostream>
#include <span>
#include <sstream>
#include <string>
#include <units/frequency.h>
#include <units/math.h>
#include <units/time.h>

namespace ctre {
namespace phoenix6 {

    namespace hardware {
        class ParentDevice;
    }

    template <typename T>
    class StatusSignal;

    /**
     * \brief Class that provides operations to
     * retrieve information about a status signal.
     */
    class BaseStatusSignal {
    private:
        hardware::DeviceIdentifier deviceIdentifier;
        uint16_t spn;
        std::string name;
        std::function<void()> _checkFirmVersFunction;

        std::map<uint16_t, std::string> _unitStrings{};
        uint16_t _unitsKey;

        units::time::second_t _lastTimestamp{0_s};

    protected:
        std::string units;
        double baseValue = 0;
        AllTimestamps timestamps{};
        ctre::phoenix::StatusCode error = ctre::phoenix::StatusCode::SigNotUpdated;

        BaseStatusSignal(
            hardware::DeviceIdentifier deviceIdentifier,
            uint16_t spn,
            std::string signalName,
            std::function<void()> checkFirmVersFunction
        ) :
            deviceIdentifier{std::move(deviceIdentifier)},
            spn{spn},
            name{std::move(signalName)},
            _checkFirmVersFunction{std::move(checkFirmVersFunction)},
            _unitsKey{spn},
            units{Status_GetUnits(spn)}
        {
        }

        BaseStatusSignal(
            hardware::DeviceIdentifier deviceIdentifier,
            uint16_t spn,
            std::string signalName,
            std::function<void()> checkFirmVersFunction,
            std::function<std::map<uint16_t, std::string>()> const &unitsGenerator
        ) :
            deviceIdentifier{std::move(deviceIdentifier)},
            spn{spn},
            name{std::move(signalName)},
            _checkFirmVersFunction{std::move(checkFirmVersFunction)},
            _unitStrings{unitsGenerator()},
            _unitsKey{spn},
            units{Status_GetUnits(spn)}
        {
            for (auto &unitString : _unitStrings) {
                unitString.second = Status_GetUnits(unitString.first);
            }
        }

        /* Constructor for an invalid BaseStatusSignal */
        BaseStatusSignal(ctre::phoenix::StatusCode error) :
            deviceIdentifier{hardware::DeviceIdentifier{}},
            spn{0},
            name{"Invalid"},
            _checkFirmVersFunction{[] {}},
            _unitsKey{spn},
            error{error}
        {
        }

        static std::string Status_GetUnits(uint32_t signal);

        static ctre::phoenix::StatusCode Status_Get(
            BaseStatusSignal &signal,
            char const *network,
            bool bWaitForUpdate,
            double timeoutSeconds);
        static ctre::phoenix::StatusCode Status_WaitForAll(
            std::span<BaseStatusSignal* const> signals,
            char const *network,
            double timeoutSeconds);

        static ctre::phoenix::StatusCode Status_SetUpdateFrequency(
            BaseStatusSignal &signal,
            double frequencyHz,
            double timeoutSeconds);
        static ctre::phoenix::StatusCode Status_SetUpdateFrequencyForAll(
            std::span<BaseStatusSignal* const> signals,
            double frequencyHz,
            double timeoutSeconds);
        static double Status_GetAppliedUpdateFrequency(char const *canbus, uint32_t deviceHash, uint16_t spn);

        static ctre::phoenix::StatusCode WaitForAllImpl(
            char const *location,
            units::time::second_t timeoutSeconds,
            bool reportError,
            std::span<BaseStatusSignal* const> signals);

        void RefreshValue(bool waitForUpdate, units::time::second_t timeout, bool reportError);
        void UpdateUnits(uint16_t unitsKey);

    public:
        virtual ~BaseStatusSignal() = 0; // Declare virtual destructor to make this class abstract

        /**
         * \brief Gets the name of this signal.
         *
         * \returns Name of this signal
         */
        std::string const &GetName() const { return name; }
        /**
         * \brief Gets the units for this signal.
         *
         * \returns String representation of units for this signal
         */
        std::string const &GetUnits() const { return units; }
        /**
         * \brief Gets the value of this signal as a double.
         *
         * \return Value of this signal as a double instead of the generic type
         */
        double GetValueAsDouble() const { return baseValue; }
        /**
         * \brief Gets the timestamps of this signals.
         *
         * \returns All timestamps for this signal
         */
        AllTimestamps const &GetAllTimestamps() const { return timestamps; }
        /**
         * \brief Gets the most accurate timestamp available for this signal.
         *
         * \details The timestamp sources from most to least accurate are:
         *
         * - Timestamp#TimestampSource#Device
         * - Timestamp#TimestampSource#CANivore
         * - Timestamp#TimestampSource#System
         *
         * Note that some of these sources may not be available.
         *
         * \returns The most accurate timestamp available for this signal
         */
        Timestamp const &GetTimestamp() const { return timestamps.GetBestTimestamp(); }
        /**
         * \brief Gets the status code of the last time this signal was refreshed.
         *
         * \returns Status code of the last time this signal was refreshed
         */
        ctre::phoenix::StatusCode GetStatus() const { return error; }

        /**
         * \brief Checks whether the signal has been updated since the last check.
         *
         * Note that the signal must be refreshed before calling this routine.
         *
         * \returns true if the signal has updated since the previous call of this routine
         */
        bool HasUpdated()
        {
            bool retval = false;
            /* did we receive an update */
            auto const &timestamp = GetAllTimestamps().GetSystemTimestamp();
            if (timestamp.IsValid()) {
                /* if the update timestamp is new, then a new frame was sent */
                if (_lastTimestamp != timestamp.GetTime()) {
                    _lastTimestamp = timestamp.GetTime();
                    retval = true;
                }
            }
            return retval;
        }

        /**
         * \brief Sets the rate at which the device will publish this signal.
         *
         * A frequency of 0 Hz will turn off the signal. Otherwise, the minimum supported signal
         * frequency is 4 Hz, and the maximum is 1000 Hz. Additionally, some update frequencies are
         * not supported and will be promoted up to the next highest supported frequency.
         *
         * If other StatusSignals in the same status frame have been set to an update frequency,
         * the fastest requested update frequency will be applied to the frame.
         *
         * \param frequencyHz Rate to publish the signal in Hz.
         * \param timeoutSeconds Maximum amount of time to wait when performing the action
         * \returns Status code of setting the update frequency
         */
        ctre::phoenix::StatusCode SetUpdateFrequency(units::frequency::hertz_t frequencyHz, units::time::second_t timeoutSeconds = 100_ms)
        {
            return Status_SetUpdateFrequency(
                *this,
                frequencyHz.value(),
                timeoutSeconds.value()
            );
        }

        /**
         * \brief Gets the rate at which the device will publish this signal.
         *
         * This is typically the last value passed into #SetUpdateFrequency. The returned value
         * may be higher if another StatusSignal in the same status frame has been set to a higher
         * update frequency.
         *
         * \returns Applied update frequency of the signal in Hz
         */
        units::frequency::hertz_t GetAppliedUpdateFrequency() const
        {
            return units::frequency::hertz_t{
                Status_GetAppliedUpdateFrequency(
                    this->deviceIdentifier.network.c_str(),
                    this->deviceIdentifier.deviceHash,
                    this->spn
                )
            };
        }

        /**
         * \brief Performs latency compensation on signal using the signalSlope and signal's latency to determine
         *        the magnitude of compensation. The caller must refresh these StatusSignals beforehand;
         *        this function only does the math required for latency compensation.
         *
         * \details Example usage:
         * \code
         * units::turn_t compensatedTurns = BaseStatusSignal::GetLatencyCompensatedValue(fx.GetPosition(), fx.GetVelocity());
         * \endcode
         *
         * \tparam U Type of signal's underlying type. This is the type that the function will return.
         * \tparam U_PER_SEC Type of signalSlope's underlying type. This must be the derivative of U.
         * \param signal Signal to be latency compensated. Caller must make sure this signal is up to date
         *               either by calling \c Refresh() or \c WaitForUpdate().
         * \param signalSlope Derivative of signal that informs compensation magnitude. Caller must make sure this
         *                    signal is up to date either by calling \c Refresh() or \c WaitForUpdate().
         * \param maxLatencySeconds The maximum amount of latency to compensate for in seconds. A negative or zero
         *                          value disables the max latency cap. This is used to cap the contribution of
         *                          latency compensation for stale signals, such as after the device has been
         *                          disconnected from the CAN bus.
         * \returns Latency compensated value from the signal StatusSignal.
         */
        template <typename U, typename U_PER_SEC>
            requires units::traits::is_unit_t_v<U> && units::traits::is_unit_t_v<U_PER_SEC> &&
                units::traits::is_convertible_unit_v<
                    typename units::traits::unit_t_traits<U>::unit_type,
                    units::compound_unit<typename units::traits::unit_t_traits<U_PER_SEC>::unit_type, units::seconds>
                >
        static U GetLatencyCompensatedValue(StatusSignal<U> const &signal, StatusSignal<U_PER_SEC> const &signalSlope, units::time::second_t maxLatencySeconds = 0.300_s)
        {
            U const nonCompensatedSignal = signal.GetValue();
            U_PER_SEC const changeInSignal = signalSlope.GetValue();
            units::second_t latency = signal.GetTimestamp().GetLatency();
            if (maxLatencySeconds > 0_s && latency > maxLatencySeconds) {
                latency = maxLatencySeconds;
            }
            return nonCompensatedSignal + (changeInSignal * latency);
        }

        /**
         * \brief Waits for new data on all provided signals up to timeout.
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
         *        the individual status codes using GetStatus() when this happens.
         *
         * \param timeoutSeconds Maximum time to wait for all the signals to arrive.
         *                       Pass zero to refresh all signals without blocking.
         * \param signals Signals to wait on, passed as a comma-separated list of signal references.
         * \return InvalidNetwork if signals are on different CAN bus networks,
         *         RxTimeout if it took longer than timeoutSeconds to receive all the signals,
         *         MultiSignalNotSupported if using the roboRIO bus with more than one signal and a non-zero timeout.
         *         An OK status code means that all signals arrived within timeoutSeconds and they are all OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        template <std::derived_from<BaseStatusSignal>... Signals>
        static ctre::phoenix::StatusCode WaitForAll(units::time::second_t timeoutSeconds, Signals &... signals)
        {
            return WaitForAll(timeoutSeconds, true, signals...);
        }
        /**
         * \brief Waits for new data on all provided signals up to timeout.
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
         *        the individual status codes using GetStatus() when this happens.
         *
         * \param timeoutSeconds Maximum time to wait for all the signals to arrive.
         *                       Pass zero to refresh all signals without blocking.
         * \param signals Signals to wait on, passed as a span of signal pointers.
         * \return InvalidNetwork if signals are on different CAN bus networks,
         *         RxTimeout if it took longer than timeoutSeconds to receive all the signals,
         *         MultiSignalNotSupported if using the roboRIO bus with more than one signal and a non-zero timeout.
         *         An OK status code means that all signals arrived within timeoutSeconds and they are all OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        static ctre::phoenix::StatusCode WaitForAll(units::time::second_t timeoutSeconds, std::span<BaseStatusSignal* const> signals)
        {
            return WaitForAll(timeoutSeconds, true, signals);
        }

        /**
         * \brief Waits for new data on all provided signals up to timeout.
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
         *        the individual status codes using GetStatus() when this happens.
         *
         * \param timeoutSeconds Maximum time to wait for all the signals to arrive.
         *                       Pass zero to refresh all signals without blocking.
         * \param reportError Whether to report any errors to the Driver Station/stderr, defaults to true
         * \param signals Signals to wait on, passed as a comma-separated list of signal references.
         * \return InvalidNetwork if signals are on different CAN bus networks,
         *         RxTimeout if it took longer than timeoutSeconds to receive all the signals,
         *         MultiSignalNotSupported if using the roboRIO bus with more than one signal and a non-zero timeout.
         *         An OK status code means that all signals arrived within timeoutSeconds and they are all OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        template <std::derived_from<BaseStatusSignal>... Signals>
        static ctre::phoenix::StatusCode WaitForAll(units::time::second_t timeoutSeconds, bool reportError, Signals &... signals)
        {
            return WaitForAll(
                timeoutSeconds,
                reportError,
                std::array<BaseStatusSignal *, sizeof...(Signals)>{(&signals)...}
            );
        }
        /**
         * \brief Waits for new data on all provided signals up to timeout.
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
         *        the individual status codes using GetStatus() when this happens.
         *
         * \param timeoutSeconds Maximum time to wait for all the signals to arrive.
         *                       Pass zero to refresh all signals without blocking.
         * \param reportError Whether to report any errors to the Driver Station/stderr, defaults to true
         * \param signals Signals to wait on, passed as a span of signal pointers.
         * \return InvalidNetwork if signals are on different CAN bus networks,
         *         RxTimeout if it took longer than timeoutSeconds to receive all the signals,
         *         MultiSignalNotSupported if using the roboRIO bus with more than one signal and a non-zero timeout.
         *         An OK status code means that all signals arrived within timeoutSeconds and they are all OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        static ctre::phoenix::StatusCode WaitForAll(units::time::second_t timeoutSeconds, bool reportError, std::span<BaseStatusSignal* const> signals)
        {
            static constexpr char kLocation[] = "ctre::phoenix6::BaseStatusSignal::WaitForAll";
            return WaitForAllImpl(kLocation, timeoutSeconds, reportError, signals);
        }

        /**
         * \brief Performs a non-blocking refresh on all provided signals.
         *
         * This provides a performance improvement over separately calling Refresh() on each signal.
         *
         * \param signals Signals to refresh, passed as a comma-separated list of signal references.
         * \return InvalidNetwork if signals are on different CAN bus networks.
         *         An OK status code means that all signals are OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        template <std::derived_from<BaseStatusSignal>... Signals>
        static ctre::phoenix::StatusCode RefreshAll(Signals &... signals)
        {
            return RefreshAll(true, signals...);
        }
        /**
         * \brief Performs a non-blocking refresh on all provided signals.
         *
         * This provides a performance improvement over separately calling Refresh() on each signal.
         *
         * \param signals Signals to refresh, passed as a span of signal pointers.
         * \return InvalidNetwork if signals are on different CAN bus networks.
         *         An OK status code means that all signals are OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        static ctre::phoenix::StatusCode RefreshAll(std::span<BaseStatusSignal* const> signals)
        {
            return RefreshAll(true, signals);
        }

        /**
         * \brief Performs a non-blocking refresh on all provided signals.
         *
         * This provides a performance improvement over separately calling Refresh() on each signal.
         *
         * \param reportError Whether to report any errors to the Driver Station/stderr, defaults to true
         * \param signals Signals to refresh, passed as a comma-separated list of signal references.
         * \return InvalidNetwork if signals are on different CAN bus networks.
         *         An OK status code means that all signals are OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        template <std::derived_from<BaseStatusSignal>... Signals>
        static ctre::phoenix::StatusCode RefreshAll(bool reportError, Signals &... signals)
        {
            return RefreshAll(reportError, std::array<BaseStatusSignal *, sizeof...(Signals)>{(&signals)...});
        }
        /**
         * \brief Performs a non-blocking refresh on all provided signals.
         *
         * This provides a performance improvement over separately calling Refresh() on each signal.
         *
         * \param reportError Whether to report any errors to the Driver Station/stderr, defaults to true
         * \param signals Signals to refresh, passed as a span of signal pointers.
         * \return InvalidNetwork if signals are on different CAN bus networks.
         *         An OK status code means that all signals are OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        static ctre::phoenix::StatusCode RefreshAll(bool reportError, std::span<BaseStatusSignal* const> signals)
        {
            static constexpr char kLocation[] = "ctre::phoenix6::BaseStatusSignal::RefreshAll";
            return WaitForAllImpl(kLocation, 0_s, reportError, signals);
        }

        /**
         * \brief Checks if all signals have an OK error code.
         *
         * \param signals Signals to check error code of, passed as a comma-separated list of signal references.
         * \returns True if all signals are OK, false otherwise
         */
        template <std::derived_from<BaseStatusSignal>... Signals>
        static bool IsAllGood(Signals const &... signals)
        {
            return IsAllGood(std::array<BaseStatusSignal const *, sizeof...(Signals)>{(&signals)...});
        }
        /**
         * \brief Checks if all signals have an OK error code.
         *
         * \param signals Signals to check error code of, passed as a span of signal pointers.
         * \returns True if all signals are OK, false otherwise
         */
        static bool IsAllGood(std::span<BaseStatusSignal const *const> signals)
        {
            for (auto signal : signals) {
                if (!signal->GetStatus().IsOK()) {
                    return false;
                }
            }
            return true;
        }

        /**
         * \brief Sets the update frequency of all specified status signals to the provided common frequency.
         *
         * A frequency of 0 Hz will turn off the signal. Otherwise, the minimum supported signal frequency
         * is 4 Hz, and the maximum is 1000 Hz. Additionally, some update frequencies are not supported and
         * will be promoted up to the next highest supported frequency.
         *
         * If other StatusSignals in the same status frame have been set to an update frequency,
         * the fastest requested update frequency will be applied to the frame.
         *
         * This will wait up to 0.100 seconds (100ms) for each signal.
         *
         * \param frequencyHz Rate to publish the signal in Hz.
         * \param signals Signals to apply the update frequency to, passed as a comma-separated list of signal references.
         * \returns Status code of the first failed update frequency set call, or OK if all succeeded
         */
        template <std::derived_from<BaseStatusSignal>... Signals>
        static ctre::phoenix::StatusCode SetUpdateFrequencyForAll(units::frequency::hertz_t frequencyHz, Signals &... signals)
        {
            return SetUpdateFrequencyForAll(frequencyHz, std::array<BaseStatusSignal *, sizeof...(Signals)>{(&signals)...});
        }
        /**
         * \brief Sets the update frequency of all specified status signals to the provided common frequency.
         *
         * A frequency of 0 Hz will turn off the signal. Otherwise, the minimum supported signal frequency
         * is 4 Hz, and the maximum is 1000 Hz. Additionally, some update frequencies are not supported and
         * will be promoted up to the next highest supported frequency.
         *
         * If other StatusSignals in the same status frame have been set to an update frequency,
         * the fastest requested update frequency will be applied to the frame.
         *
         * This will wait up to 0.100 seconds (100ms) for each signal.
         *
         * \param frequencyHz Rate to publish the signal in Hz.
         * \param signals Signals to apply the update frequency to, passed as a span of signal pointers.
         * \returns Status code of the first failed update frequency set call, or OK if all succeeded
         */
        static ctre::phoenix::StatusCode SetUpdateFrequencyForAll(units::frequency::hertz_t frequencyHz, std::span<BaseStatusSignal* const> signals)
        {
            return Status_SetUpdateFrequencyForAll(signals, frequencyHz.value(), 0.100);
        }
    };

    /**
     * \brief Represents a status signal with data of type T,
     * and operations available to retrieve information about
     * the signal.
     */
    template <typename T>
    class StatusSignal : public BaseStatusSignal {
        friend class hardware::ParentDevice;

        StatusSignal(
            hardware::DeviceIdentifier deviceIdentifier,
            uint16_t spn,
            std::string signalName,
            std::function<void()> checkFirmVersFunction
        ) :
            BaseStatusSignal{
                std::move(deviceIdentifier),
                spn, std::move(signalName),
                std::move(checkFirmVersFunction)
            }
        {
        }

        StatusSignal(
            hardware::DeviceIdentifier deviceIdentifier,
            uint16_t spn,
            std::string signalName,
            std::function<void()> checkFirmVersFunction,
            std::function<std::map<uint16_t, std::string>()> const &unitsGenerator
        ) :
            BaseStatusSignal{
                std::move(deviceIdentifier),
                spn, std::move(signalName),
                std::move(checkFirmVersFunction),
                unitsGenerator
            }
        {
        }

        /* Constructor for an invalid StatusSignal */
        StatusSignal(ctre::phoenix::StatusCode error) :
            BaseStatusSignal{error}
        {
        }

    public:
        /**
         * \brief Gets the cached value from this status signal.
         *
         * \details Gets the cached value. To make sure the value is up-to-date
         *          call \c Refresh() or \c WaitForUpdate()
         *
         * \returns Cached value
         */
        T GetValue() const
        {
            if constexpr(units::traits::is_unit_t_v<T>) {
                return units::make_unit<T>(this->baseValue);
            } else {
                return static_cast<T>(this->baseValue);
            }
        }

        /**
         * \brief Refreshes the value of this status signal.
         *
         * If the user application caches this StatusSignal object
         * instead of periodically fetching it from the hardware device,
         * this function must be called to fetch fresh data.
         *
         * \details This performs a non-blocking refresh operation. If
         *          you want to wait until you receive the signal, call
         *          \c WaitForUpdate() instead.
         *
         * \param reportError Whether to report any errors to the Driver Station/stderr
         * \returns Reference to itself
         */
        StatusSignal<T> &Refresh(bool reportError = true)
        {
            RefreshValue(false, 0_s, reportError); // Don't block and error if signal is older than a default timeout
            return *this;
        }
        /**
         * \brief Waits up to timeoutSec to get the up-to-date status signal value.
         *
         * \details This performs a blocking refresh operation. If
         *          you want to non-blocking refresh the signal, call
         *          \c Refresh() instead.
         *
         * \param timeoutSec Maximum time to wait for the signal to update
         * \param reportError Whether to report any errors to the Driver Station/stderr
         * \returns Reference to itself
         */
        StatusSignal<T> &WaitForUpdate(units::time::second_t timeoutSec, bool reportError = true)
        {
            RefreshValue(true, timeoutSec, reportError);
            return *this;
        }

        /**
         * \brief Checks whether the signal is near a target value within the
         * given tolerance.
         *
         * \param target The target value of the signal
         * \param tolerance The error tolerance between the target and measured values
         * \returns Whether the signal is near the target value
         */
        bool IsNear(T target, T tolerance) const
            requires (std::same_as<T, double>)
        {
            return fabs(GetValue() - target) <= tolerance;
        }

        /**
         * \brief Checks whether the signal is near a target value within the
         * given tolerance.
         *
         * \param target The target value of the signal
         * \param tolerance The error tolerance between the target and measured values
         * \returns Whether the signal is near the target value
         */
        bool IsNear(T target, T tolerance) const
            requires (units::traits::is_unit_t_v<T>)
        {
            return units::math::abs(GetValue() - target) <= tolerance;
        }

        /**
         * \brief Get a basic data-only container with a copy of the current signal data.
         *
         * If looking for Phoenix 6 logging features, see the SignalLogger class instead.
         *
         * \returns Basic structure with all relevant information
         */
        SignalMeasurement<T> GetDataCopy() const
        {
            SignalMeasurement<T> toRet;
            toRet.name = GetName();
            toRet.value = GetValue();
            toRet.timestamp = GetTimestamp().GetTime();
            toRet.units = GetUnits();
            toRet.status = GetStatus();
            return toRet;
        }

        /**
         * \brief Returns a lambda that calls #Refresh and #GetValue on this object. This is useful for command-based programming.
         *
         * \returns std::function<T()> that calls #Refresh and returns this signal's value.
         */
        std::function<T()> AsSupplier()
        {
            return [this]() { return Refresh().GetValue(); };
        }

        friend std::ostream &operator<<(std::ostream &os, StatusSignal<T> const &data)
        {
            if constexpr(units::traits::is_unit_t_v<T>) {
                os << data.GetValue().value() << " " << data.GetUnits();
            } else {
                os << data.GetValue() << " " << data.GetUnits();
            }
            return os;
        }
        std::string ToString() const
        {
            std::stringstream ss;
            ss << *this;
            return ss.str();
        }
    };

}
}
