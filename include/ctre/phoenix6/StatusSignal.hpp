/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix/platform/ConsoleUtil.hpp"
#include "ctre/phoenix/platform/Platform.hpp"
#include "ctre/phoenix6/hardware/DeviceIdentifier.hpp"
#include "ctre/phoenix6/Timestamp.hpp"
#include "ctre/phoenix6/networking/interfaces/ReportError_Interface.h"
#include <array>
#include <functional>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <units/base.h>
#include <units/frequency.h>
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
    class BaseStatusSignal
    {
        friend hardware::ParentDevice; // Allow ParentDevice to set error

    protected:
        hardware::DeviceIdentifier deviceIdentifier;
        uint16_t spn;
        std::string units;
        AllTimestamps timestamps{};
        double baseValue = 0;
        ctre::phoenix::StatusCode error = ctre::phoenix::StatusCode::SigNotUpdated;
        std::string signalName;

        std::function<void()> _checkFirmVersFunction;

        units::time::second_t _lastTimestamp{0_s};

        template <typename T>
        friend class StatusSignal;

        BaseStatusSignal(
            hardware::DeviceIdentifier deviceIdentifier,
            uint16_t spn,
            std::string signalName,
            std::function<void()> checkFirmVersFunction
        ) :
            deviceIdentifier{std::move(deviceIdentifier)},
            spn{spn},
            units{Status_GetUnits(spn)},
            signalName{std::move(signalName)},
            _checkFirmVersFunction{std::move(checkFirmVersFunction)}
        {
        }

        /* Constructor for an invalid BaseStatusSignal */
        BaseStatusSignal(ctre::phoenix::StatusCode error) :
            deviceIdentifier{hardware::DeviceIdentifier{}},
            spn{0},
            error{error},
            signalName{"Invalid"},
            _checkFirmVersFunction{[] {}}
        {
        }

        virtual void UpdateUnits(uint16_t unitsKey) = 0;

        /**
         * \brief Wait for multiple signals to arrive
         *
         * \param signals Signals to wait for
         * \param count Number of signals
         * \param network Network to wait for the signals on
         * \param timeoutSeconds Maximum time to wait for all these signals
         * \returns Status of the wait
         */
        static ctre::phoenix::StatusCode Status_WaitForAll(
            BaseStatusSignal* const *signals,
            size_t count,
            const char *network,
            double timeoutSeconds);

        static ctre::phoenix::StatusCode Status_SetUpdateFrequency(const char *canbus, uint32_t deviceHash, uint16_t spn, double frequencyHz, double timeoutSeconds);
        static ctre::phoenix::StatusCode Status_SetUpdateFrequencyForAll(BaseStatusSignal* const *signals, size_t count, double frequencyHz, double timeoutSeconds);
        static double Status_GetAppliedUpdateFrequency(const char *canbus, uint32_t deviceHash, uint16_t spn);

        /**
         * \brief Gets signal units.
         *
         * \param signal Signal to get
         * \returns Units of the signal
         */
        static std::string Status_GetUnits(uint32_t signal);

        /**
         * \brief Get signal update.  Caller either get last received, or wait for an update.
         *
         * \param signal Signal to update
         * \param network Name of bus (can, canfd, canivore-name, future protocols)
         * \param bWaitForUpdate  If true, API will wait up to timeoutSeconds for an update.  If false, routine will poll last received and use timeoutSeconds to return error code if too old.
         * \param timeoutSeconds How long to wait or how old the signal can be before error'ing
         * \returns Status of the get
         */
        static ctre::phoenix::StatusCode Status_Get(
            BaseStatusSignal &signal,
            const char *network,
            bool bWaitForUpdate,
            double timeoutSeconds);

        /**
         * \brief Implementation of the WaitForAll API.
         *
         * \tparam Arr \c std::array or \c std::vector of BaseStatusSignal*
         * \param location Location of the calling function
         * \param timeoutSeconds Maximum time to wait for all the signals
         * \param signals Signals to wait on
         * \return Status of the wait
         */
        template <typename Arr>
        static ctre::phoenix::StatusCode WaitForAllImpl(const char *location, units::time::second_t timeoutSeconds, const Arr &signals)
        {
            if (signals.size() < 1)
            {
                /* We don't have any signals to wait for, so return early */
                ctre::phoenix::StatusCode retval = ctre::phoenix::StatusCode::InvalidParamValue;
                c_ctre_phoenix_report_error(true, retval, 0,
                                            retval.GetDescription(),
                                            location,
                                            ctre::phoenix::platform::GetStackTrace(1).c_str());
                return retval;
            }
            const std::string &network = signals[0]->deviceIdentifier.network;

            for (auto signal : signals)
            {
                /* Check that they all have the same network */
                if (network != signal->deviceIdentifier.network)
                {
                    ctre::phoenix::StatusCode retval = ctre::phoenix::StatusCode::InvalidNetwork; // Networks don't match, return early

                    c_ctre_phoenix_report_error(true, retval, 0,
                                                retval.GetDescription(),
                                                location,
                                                ctre::phoenix::platform::GetStackTrace(1).c_str());
                    return retval;
                }
            }

            /* Report if any device firmware versions are too old */
            for (auto signal : signals)
            {
                signal->_checkFirmVersFunction();
            }

            /* Now wait for all the signals */
            ctre::phoenix::StatusCode retval = Status_WaitForAll(signals.data(), signals.size(), network.c_str(), timeoutSeconds.to<double>());

            /* error reporting */
            if (false == retval.IsOK())
            {
                c_ctre_phoenix_report_error(retval.IsError(), retval, 0,
                                            retval.GetDescription(),
                                            location,
                                            ctre::phoenix::platform::GetStackTrace(1).c_str());
            }
            return retval;
        }

        /**
         * \brief Type trait to verify that all types passed in are subclasses of BaseStatusSignal.
         */
        template <typename... Signals>
        struct is_all_status_signal :
            std::conjunction<std::is_base_of<BaseStatusSignal, std::remove_reference_t<Signals>>...>
        {};

        /**
         * \brief Whether all types passed in are subclasses of BaseStatusSignal.
         */
        template <typename... Signals>
        static constexpr bool is_all_status_signal_v = is_all_status_signal<Signals...>::value;

    public:
        virtual ~BaseStatusSignal() = 0; // Declare virtual destructor to make this class abstract

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
         * \return An InvalidParamValue if signals array is empty,
         *         InvalidNetwork if signals are on different CAN bus networks,
         *         RxTimeout if it took longer than timeoutSeconds to receive all the signals,
         *         MultiSignalNotSupported if using the roboRIO bus with more than one signal and a non-zero timeout.
         *         An OK status code means that all signals arrived within timeoutSeconds and they are all OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        template <typename... Signals, typename = std::enable_if_t<is_all_status_signal_v<Signals...>>>
        static ctre::phoenix::StatusCode WaitForAll(units::time::second_t timeoutSeconds, Signals &... signals)
        {
            return WaitForAll(timeoutSeconds,
                    std::array<BaseStatusSignal *, sizeof...(Signals)>{(&signals)...});
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
         * \param signals Signals to wait on, passed as a vector or initializer list of signal addresses.
         * \return An InvalidParamValue if signals array is empty,
         *         InvalidNetwork if signals are on different CAN bus networks,
         *         RxTimeout if it took longer than timeoutSeconds to receive all the signals,
         *         MultiSignalNotSupported if using the roboRIO bus with more than one signal and a non-zero timeout.
         *         An OK status code means that all signals arrived within timeoutSeconds and they are all OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        static ctre::phoenix::StatusCode WaitForAll(units::time::second_t timeoutSeconds, const std::vector<BaseStatusSignal *> &signals)
        {
            /* static string for location */
            constexpr char kLocation[] = "ctre::phoenix6::BaseStatusSignal::WaitForAll";
            return WaitForAllImpl(kLocation, timeoutSeconds, signals);
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
         * \param signals Signals to wait on, passed as an array of signal addresses.
         * \return An InvalidParamValue if signals array is empty,
         *         InvalidNetwork if signals are on different CAN bus networks,
         *         RxTimeout if it took longer than timeoutSeconds to receive all the signals,
         *         MultiSignalNotSupported if using the roboRIO bus with more than one signal and a non-zero timeout.
         *         An OK status code means that all signals arrived within timeoutSeconds and they are all OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        template <size_t N>
        static ctre::phoenix::StatusCode WaitForAll(units::time::second_t timeoutSeconds, const std::array<BaseStatusSignal *, N> &signals)
        {
            /* static string for location */
            constexpr char kLocation[] = "ctre::phoenix6::BaseStatusSignal::WaitForAll";
            return WaitForAllImpl(kLocation, timeoutSeconds, signals);
        }

        /**
         * \brief Performs a non-blocking refresh on all provided signals.
         *
         * This provides a performance improvement over separately calling Refresh() on each signal.
         *
         * \param signals Signals to refresh, passed as a comma-separated list of signal references.
         * \return An InvalidParamValue if signals array is empty,
         *         InvalidNetwork if signals are on different CAN bus networks.
         *         An OK status code means that all signals are OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        template <typename... Signals, typename = std::enable_if_t<is_all_status_signal_v<Signals...>>>
        static ctre::phoenix::StatusCode RefreshAll(Signals &... signals)
        {
            return RefreshAll(std::array<BaseStatusSignal *, sizeof...(Signals)>{(&signals)...});
        }
        /**
         * \brief Performs a non-blocking refresh on all provided signals.
         *
         * This provides a performance improvement over separately calling Refresh() on each signal.
         *
         * \param signals Signals to refresh, passed as a vector or initializer list of signal addresses.
         * \return An InvalidParamValue if signals array is empty,
         *         InvalidNetwork if signals are on different CAN bus networks.
         *         An OK status code means that all signals are OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        static ctre::phoenix::StatusCode RefreshAll(const std::vector<BaseStatusSignal *> &signals)
        {
            /* static string for location */
            constexpr char kLocation[] = "ctre::phoenix6::BaseStatusSignal::RefreshAll";
            return WaitForAllImpl(kLocation, 0_s, signals);
        }
        /**
         * \brief Performs a non-blocking refresh on all provided signals.
         *
         * This provides a performance improvement over separately calling Refresh() on each signal.
         *
         * \param signals Signals to refresh, passed as an array of signal addresses.
         * \return An InvalidParamValue if signals array is empty,
         *         InvalidNetwork if signals are on different CAN bus networks.
         *         An OK status code means that all signals are OK.
         *
         *         Any other value represents the StatusCode of the first failed signal.
         *         Call GetStatus() on each signal to determine which ones failed.
         */
        template <size_t N>
        static ctre::phoenix::StatusCode RefreshAll(const std::array<BaseStatusSignal *, N> &signals)
        {
            /* static string for location */
            constexpr char kLocation[] = "ctre::phoenix6::BaseStatusSignal::RefreshAll";
            return WaitForAllImpl(kLocation, 0_s, signals);
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
        static U GetLatencyCompensatedValue(StatusSignal<U> &signal, StatusSignal<U_PER_SEC> &signalSlope, units::time::second_t maxLatencySeconds = 0.300_s)
        {
            static_assert(units::traits::is_unit_t_v<U>, "signal must be a unit signal");
            static_assert(units::traits::is_unit_t_v<U_PER_SEC>, "signalSlope must be a unit signal");
            using lhs = typename units::traits::unit_t_traits<U>::unit_type;
            using rhs = typename units::traits::unit_t_traits<U_PER_SEC>::unit_type;
            static_assert(units::traits::is_convertible_unit_v<lhs, units::compound_unit<rhs, units::seconds>>,
                          "Compensation can only be performed on a signal with its derivative");

            const U nonCompensatedSignal = signal.GetValue();
            const U_PER_SEC changeInSignal = signalSlope.GetValue();
            units::second_t latency = signal.GetTimestamp().GetLatency();
            if (maxLatencySeconds > 0_s && latency > maxLatencySeconds) {
                latency = maxLatencySeconds;
            }
            return nonCompensatedSignal + (changeInSignal * latency);
        }

        /**
         * \brief Checks if all signals have an OK error code.
         *
         * \param signals Signals to check error code of, passed as a comma-separated list of signal references.
         * \returns True if all signals are OK, false otherwise
         */
        template <typename... Signals, typename = std::enable_if_t<is_all_status_signal_v<Signals...>>>
        static bool IsAllGood(Signals &... signals)
        {
            return IsAllGood(std::array<BaseStatusSignal *, sizeof...(Signals)>{(&signals)...});
        }
        /**
         * \brief Checks if all signals have an OK error code.
         *
         * \param signals Signals to check error code of, passed as a vector or initializer list of signal addresses.
         * \returns True if all signals are OK, false otherwise
         */
        static bool IsAllGood(const std::vector<BaseStatusSignal *> &signals)
        {
            for (auto signal : signals)
            {
                if (!signal->GetStatus().IsOK()) {
                    return false;
                }
            }
            return true;
        }
        /**
         * \brief Checks if all signals have an OK error code.
         *
         * \param signals Signals to check error code of, passed as an array of signal addresses.
         * \returns True if all signals are OK, false otherwise
         */
        template <size_t N>
        static bool IsAllGood(const std::array<BaseStatusSignal *, N> &signals)
        {
            for (auto signal : signals)
            {
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
         * is 4 Hz, and the maximum is 1000 Hz.
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
        template <typename... Signals, typename = std::enable_if_t<is_all_status_signal_v<Signals...>>>
        static ctre::phoenix::StatusCode SetUpdateFrequencyForAll(units::frequency::hertz_t frequencyHz, Signals &... signals)
        {
            return SetUpdateFrequencyForAll(frequencyHz, std::array<BaseStatusSignal *, sizeof...(Signals)>{(&signals)...});
        }
        /**
         * \brief Sets the update frequency of all specified status signals to the provided common frequency.
         *
         * A frequency of 0 Hz will turn off the signal. Otherwise, the minimum supported signal frequency
         * is 4 Hz, and the maximum is 1000 Hz.
         *
         * If other StatusSignals in the same status frame have been set to an update frequency,
         * the fastest requested update frequency will be applied to the frame.
         *
         * This will wait up to 0.100 seconds (100ms) for each signal.
         *
         * \param frequencyHz Rate to publish the signal in Hz.
         * \param signals Signals to apply the update frequency to, passed as a vector or initializer list of signal addresses.
         * \returns Status code of the first failed update frequency set call, or OK if all succeeded
         */
        static ctre::phoenix::StatusCode SetUpdateFrequencyForAll(units::frequency::hertz_t frequencyHz, const std::vector<BaseStatusSignal *> &signals)
        {
            return Status_SetUpdateFrequencyForAll(signals.data(), signals.size(), frequencyHz.to<double>(), 0.100);
        }
        /**
         * \brief Sets the update frequency of all specified status signals to the provided common frequency.
         *
         * A frequency of 0 Hz will turn off the signal. Otherwise, the minimum supported signal frequency
         * is 4 Hz, and the maximum is 1000 Hz.
         *
         * If other StatusSignals in the same status frame have been set to an update frequency,
         * the fastest requested update frequency will be applied to the frame.
         *
         * This will wait up to 0.100 seconds (100ms) for each signal.
         *
         * \param frequencyHz Rate to publish the signal in Hz.
         * \param signals Signals to apply the update frequency to, passed as an array of signal addresses.
         * \returns Status code of the first failed update frequency set call, or OK if all succeeded
         */
        template <size_t N>
        static ctre::phoenix::StatusCode SetUpdateFrequencyForAll(units::frequency::hertz_t frequencyHz, const std::array<BaseStatusSignal *, N> &signals)
        {
            return Status_SetUpdateFrequencyForAll(signals.data(), signals.size(), frequencyHz.to<double>(), 0.100);
        }

        /**
         * \brief Sets the rate at which the device will publish this signal.
         *
         * A frequency of 0 Hz will turn off the signal. Otherwise, the minimum supported signal
         * frequency is 4 Hz, and the maximum is 1000 Hz.
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
                this->deviceIdentifier.network.c_str(),
                this->deviceIdentifier.deviceHash,
                this->spn,
                frequencyHz.to<double>(),
                timeoutSeconds.to<double>()
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
         * \brief Gets the name of this signal.
         *
         * \returns Name of this signal
         */
        const std::string &GetName() const { return signalName; }
        /**
         * \brief Gets the units for this signal.
         *
         * \returns String representation of units for this signal
         */
        const std::string &GetUnits() const { return units; }
        /**
         * \brief Gets the value of this signal as a double.
         *
         * \return Value of this signal as a double instead of the generic type
         */
        double GetValueAsDouble() const { return baseValue; }
        /**
         * \brief Get the timestamps of this signals.
         *
         * \returns All timestamps for this signal
         */
        const AllTimestamps &GetAllTimestamps() const { return timestamps; }
        /**
         * \brief Get the most accurate timestamp available for this signal.
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
        const Timestamp &GetTimestamp() const { return timestamps.GetBestTimestamp(); }
        /**
         * \brief Get the error code from when we last received this signal.
         *
         * \returns Last cached Error Code
         */
        ctre::phoenix::StatusCode GetStatus() const { return error; }

        /**
         * \brief Check whether the signal has been updated since the last check.
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
            if (timestamp.IsValid())
            {
                /* if the update timestamp is new, then a new frame was sent */
                if (_lastTimestamp != timestamp.GetTime())
                {
                    _lastTimestamp = timestamp.GetTime();
                    retval = true;
                }
            }
            return retval;
        }
    };

    /**
     * \brief Information from a single measurement of a status signal.
     */
    template <typename L>
    struct SignalMeasurement
    {
        /**
         * \brief The value of the signal
         */
        L value;
        /**
         * \brief Timestamp of when the data point was taken
         */
        units::time::second_t timestamp;
        /**
         * \brief Status code response of getting the data
         */
        ctre::phoenix::StatusCode status;
        /**
         * \brief Units that correspond to this point
         */
        std::string units;
    };

    /**
     * \brief Represents a status signal with data of type T,
     * and operations available to retrieve information about
     * the signal.
     */
    template <typename T>
    class StatusSignal : public BaseStatusSignal
    {
        std::map<uint16_t, std::string> _unitStrings;
        uint16_t _unitsKey;

        void RefreshValue(bool block, units::time::second_t timeout, bool ReportOnError)
        {
            _checkFirmVersFunction();
            
            this->error = Status_Get(
                *this, this->deviceIdentifier.network.c_str(),
                block, timeout.to<double>()
            );

            if (ReportOnError && !(this->error.IsOK()))
            {
                std::stringstream location;
                location << this->deviceIdentifier.ToString() << " Status Signal " << this->signalName;
                c_ctre_phoenix_report_error(this->error.IsError(), this->error, 0, this->error.GetDescription(), location.str().c_str(), ctre::phoenix::platform::GetStackTrace(1).c_str());
            }
        }

        friend class hardware::ParentDevice;

        StatusSignal(
            hardware::DeviceIdentifier deviceIdentifier,
            uint16_t spn,
            std::function<void()> checkFirmVersFunction,
            std::string signalName
        ) :
            BaseStatusSignal{std::move(deviceIdentifier), spn, std::move(signalName), std::move(checkFirmVersFunction)},
            _unitStrings{},
            _unitsKey{spn}
        {
        }

        StatusSignal(
            hardware::DeviceIdentifier deviceIdentifier,
            uint16_t spn,
            std::function<void()> checkFirmVersFunction,
            std::function<std::map<uint16_t, std::string>()> mapFiller,
            std::string signalName
        ) :
            BaseStatusSignal{std::move(deviceIdentifier), spn, std::move(signalName), std::move(checkFirmVersFunction)},
            _unitStrings{mapFiller()},
            _unitsKey{spn}
        {
            for (auto &unitString : _unitStrings) {
                unitString.second = Status_GetUnits(unitString.first);
            }
        }

        /* Constructor for an invalid StatusSignal */
        StatusSignal(ctre::phoenix::StatusCode error) :
            BaseStatusSignal{error},
            _unitStrings{},
            _unitsKey{spn}
        {
        }

    protected:
        void UpdateUnits(uint16_t unitsKey) override
        {
            if (_unitsKey != unitsKey) {
                auto const it = _unitStrings.find(unitsKey);
                if (it != _unitStrings.end()) {
                    units = it->second;
                    _unitsKey = unitsKey;
                }
            }
        }

    public:
        friend std::ostream &operator<<(std::ostream &os, const StatusSignal<T> &data)
        {
            /* Units may contain UTF-8 characters */
            ctre::phoenix::platform::EnableConsoleUTF8Output();

            if constexpr(units::traits::is_unit_t_v<T>)
            {
                os << data.GetValue().value() << " " << data.GetUnits();
            }
            else
            {
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
            if constexpr(units::traits::is_unit_t_v<T>)
            {
                return units::make_unit<T>(this->baseValue);
            }
            else
            {
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
         * \param ReportOnError Whether to report any errors to the Driver Station/stderr.
         *
         * \returns Reference to itself
         */
        StatusSignal<T> &Refresh(bool ReportOnError = true)
        {
            RefreshValue(false, 0_s, ReportOnError); // Don't block and error if signal is older than a default timeout
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
         * \param ReportOnError Whether to report any errors to the Driver Station/stderr.
         *
         * \returns Reference to itself
         */
        StatusSignal<T> &WaitForUpdate(units::time::second_t timeoutSec, bool ReportOnError = true)
        {
            RefreshValue(true, timeoutSec, ReportOnError);
            return *this;
        }

        /**
         * \brief Get a basic data-only container with this information, to be used
         * for things such as data logging.
         *
         * Note if looking for Phoenix 6 logging features, see the SignalLogger class instead.
         *
         * \returns Basic structure with all relevant information
         */
        SignalMeasurement<T> GetDataCopy() const
        {
            SignalMeasurement<T> toRet;
            toRet.value = GetValue();
            toRet.status = GetStatus();
            toRet.units = GetUnits();
            toRet.timestamp = GetTimestamp().GetTime();
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
    };

}
}
