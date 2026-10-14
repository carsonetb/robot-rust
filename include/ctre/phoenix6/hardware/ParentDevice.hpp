/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/hardware/DeviceIdentifier.hpp"
#include "ctre/phoenix6/hardware/traits/CommonDevice.hpp"
#include "ctre/phoenix6/StatusSignal.hpp"
#include "ctre/phoenix6/Utils.hpp"
#include <map>
#include <mutex>

namespace ctre {
namespace phoenix6 {
namespace hardware {

    /**
     * \brief Parent class for all devices.
     */
    class ParentDevice : public virtual traits::CommonDevice {
    protected:
        static constexpr controls::EmptyControl _emptyControl{};

        DeviceIdentifier deviceIdentifier;

    private:
        std::map<uint32_t, std::unique_ptr<BaseStatusSignal>> _signalValues;
        std::recursive_mutex _signalValuesLck;
        /*
         * Use a shared pointer so users that access the control request via #GetAppliedControl has a copy
         * of the pointer without risk of it becoming a dangling pointer due to parallel operations
         */
        std::shared_ptr<controls::ControlRequest> _controlReq = std::make_shared<controls::EmptyControl>();
        std::mutex _controlReqLck;

        struct FirmwareVersChecker {
        private:
            DeviceIdentifier _deviceIdentifier;

        public:
            StatusSignal<int> _compliancy;

            double _creationTime = utils::GetCurrentTimeSeconds();
            double _timeToRefreshVersion = utils::GetCurrentTimeSeconds();
            ctre::phoenix::StatusCode _versionStatus{ctre::phoenix::StatusCode::CouldNotRetrieveV6Firmware};

            FirmwareVersChecker(DeviceIdentifier deviceIdentifier);
            void ReportIfTooOld();
        };

        std::shared_ptr<FirmwareVersChecker> _versChecker;
        StatusSignal<int> _resetSignal;

        template <typename T>
        StatusSignal<T> &LookupCommon(
            uint16_t spn, std::string signalName,
            std::function<std::map<uint16_t, std::string>()> mapFiller,
            bool reportOnConstruction, bool refresh)
        {
            static StatusSignal<T> failure{ctre::phoenix::StatusCode::InvalidParamValue};

            BaseStatusSignal *toFind;
            {
                /* lock access to the map */
                std::lock_guard<std::recursive_mutex> lock{_signalValuesLck};

                /* lookup and return if found */
                auto iter = _signalValues.find(spn);
                if (iter != _signalValues.end()) {
                    /* Found it, toFind is now the found StatusSignal */
                    toFind = iter->second.get();
                    /* since we didn't construct, report errors */
                    reportOnConstruction = true;
                } else {
                    /* insert into map */
                    if (!mapFiller) {
                        _signalValues.emplace(spn,
                            std::unique_ptr<StatusSignal<T>>{new StatusSignal<T>{
                                deviceIdentifier, spn,
                                std::move(signalName),
                                [versChecker=_versChecker]() mutable {
                                    versChecker->ReportIfTooOld();
                                }
                            }}
                        );
                    } else {
                        _signalValues.emplace(spn,
                            std::unique_ptr<StatusSignal<T>>{new StatusSignal<T>{
                                deviceIdentifier, spn,
                                std::move(signalName),
                                [versChecker=_versChecker]() mutable {
                                    versChecker->ReportIfTooOld();
                                },
                                mapFiller
                            }}
                        );
                    }

                    /* look up and return */
                    iter = _signalValues.find(spn);
                    toFind = iter->second.get();
                }
            }

            /* Now cast it up to the StatusSignal */
            StatusSignal<T> *ret = dynamic_cast<StatusSignal<T> *>(toFind);
            /* If ret is null, that means the cast failed. Otherwise we can return it */
            if (ret == nullptr) {
                /* Cast failed, let user know this doesn't exist */
                return failure;
            } else {
                /* Good cast, refresh it and return this now */
                if (refresh) {
                    ret->Refresh(reportOnConstruction);
                }
                return *ret;
            }
        }

    public:
        ParentDevice(int deviceID, std::string model, CANBus canbus);
        virtual ~ParentDevice() = 0; // Declare virtual destructor to make this class abstract

        ParentDevice(ParentDevice const &) = delete;
        ParentDevice &operator=(ParentDevice const &) = delete;

        /**
         * \returns The device ID of this device [0,62].
         */
        int GetDeviceID() const final
        {
            return deviceIdentifier.deviceID;
        }

        /**
         * \returns The network this device is on.
         */
        CANBus GetNetwork() const final
        {
            return CANBus{deviceIdentifier.network};
        }

        /**
         * \brief Gets a number unique for this device's hardware type and ID.
         * This number is not unique across networks.
         *
         * \details This can be used to easily reference hardware devices on
         * the same network in collections such as maps.
         *
         * \returns Hash of this device.
         */
        uint64_t GetDeviceHash() const final
        {
            return deviceIdentifier.deviceHash;
        }

        /**
         * \brief Get the latest applied control.
         *        Caller can cast this to the derived class if they know its type. Otherwise,
         *        use controls#ControlRequest#GetControlInfo to get info out of it.
         *
         * \details This returns a shared pointer to avoid becoming a dangling pointer
         *          due to parallel operations changing the underlying data. Make sure
         *          to save the shared_ptr to a variable before chaining function calls,
         *          otherwise the data may be freed early.
         *
         * \returns Latest applied control
         */
        std::shared_ptr<controls::ControlRequest const> GetAppliedControl() const final
        {
            return _controlReq;
        }

        /**
         * \brief Get the latest applied control.
         *        Caller can cast this to the derived class if they know its type. Otherwise,
         *        use controls#ControlRequest#GetControlInfo to get info out of it.
         *
         * \details This returns a shared pointer to avoid becoming a dangling pointer
         *          due to parallel operations changing the underlying data. Make sure
         *          to save the shared_ptr to a variable before chaining function calls,
         *          otherwise the data may be freed early.
         *
         * \returns Latest applied control
         */
        std::shared_ptr<controls::ControlRequest> GetAppliedControl() final
        {
            return _controlReq;
        }

        /**
         * \returns true if device has reset since the previous call of this routine.
         */
        bool HasResetOccurred() final
        {
            return _resetSignal.Refresh(false).HasUpdated();
        }

        /**
         * \returns a function that checks for device resets.
         */
        std::function<bool()> GetResetOccurredChecker() const final
        {
            return [resetSignal=_resetSignal]() mutable {
                return resetSignal.Refresh(false).HasUpdated();
            };
        }

        /**
         * \brief Returns whether the device is still connected to the robot.
         * This is equivalent to refreshing and checking the latency of the
         * Version status signal.
         *
         * \param maxLatencySeconds The maximum latency of the Version status signal
         *                          before the device is reported as disconnected
         * \returns true if the device is connected
         */
        bool IsConnected(units::second_t maxLatencySeconds = 500_ms) final
        {
            return _versChecker->_compliancy.Refresh(false).GetTimestamp().GetLatency() <= maxLatencySeconds;
        }

        /**
         * \brief This is a reserved routine for internal testing.  Use the other get routines to retrieve signal values.
         *
         * \param signal Signal to get.
         * \param refresh Whether to refresh
         * \returns StatusSignalValue holding value
         */
        StatusSignal<double> &GetGenericSignal(uint32_t signal, bool refresh = true)
        {
            return LookupStatusSignal<double>((uint16_t)signal, "Generic", true, refresh);
        }

        /**
         * \brief Optimizes the device's bus utilization by reducing the update frequencies of its status signals.
         *
         * All status signals that have not been explicitly given an update frequency using
         * BaseStatusSignal#SetUpdateFrequency will be slowed down. Note that if other status
         * signals in the same status frame have been given an update frequency, the update
         * frequency will be honored for the entire frame.
         *
         * This function only needs to be called once on this device in the robot program. Additionally, this
         * method does not necessarily need to be called after setting the update frequencies of other signals.
         *
         * To restore the default status update frequencies, call ResetSignalFrequencies.
         * Alternatively, remove this method call, redeploy the robot application, and power-cycle
         * the device on the bus. The user can also override individual status update frequencies
         * using BaseStatusSignal#SetUpdateFrequency.
         *
         * \param optimizedFreqHz The update frequency to apply to the optimized status signals. A frequency
         *                        of 0 Hz will turn off the signals. Otherwise, the minimum supported signal
         *                        frequency is 4 Hz (default).
         * \param timeoutSeconds Maximum amount of time to wait for each status frame when performing the action
         * \returns Status code of the first failed update frequency set call, or OK if all succeeded
         */
        ctre::phoenix::StatusCode OptimizeBusUtilization(units::frequency::hertz_t optimizedFreqHz = 4_Hz, units::time::second_t timeoutSeconds = 100_ms) final;

        /**
         * \brief Optimizes the bus utilization of the provided devices by reducing the update
         * frequencies of their status signals. This API defaults to an optimized update frequency
         * of 4 Hz to preserve log data.
         *
         * All status signals that have not been explicitly given an update frequency using
         * BaseStatusSignal#SetUpdateFrequency will be slowed down. Note that if other status
         * signals in the same status frame have been given an update frequency, the update
         * frequency will be honored for the entire frame.
         *
         * This function only needs to be called once in the robot program for the provided devices.
         * Additionally, this method does not necessarily need to be called after setting the update
         * frequencies of other signals.
         *
         * To restore the default status update frequencies, call ResetSignalFrequenciesForAll.
         * Alternatively, remove this method call, redeploy the robot application, and power-cycle
         * the devices on the bus. The user can also override individual status update frequencies
         * using BaseStatusSignal#SetUpdateFrequency.
         *
         * This will wait up to 0.100 seconds (100ms) for each status frame.
         *
         * \param devices Devices for which to optimize bus utilization, passed as a comma-separated list of device references.
         * \returns Status code of the first failed optimize call, or OK if all succeeded
         */
        template <std::derived_from<traits::CommonDevice>... Devices>
        static ctre::phoenix::StatusCode OptimizeBusUtilizationForAll(Devices &... devices)
        {
            return OptimizeBusUtilizationForAll(4_Hz, devices...);
        }

        /**
         * \brief Optimizes the bus utilization of the provided devices by reducing the update
         * frequencies of their status signals. This API defaults to an optimized update frequency
         * of 4 Hz to preserve log data.
         *
         * All status signals that have not been explicitly given an update frequency using
         * BaseStatusSignal#SetUpdateFrequency will be slowed down. Note that if other status
         * signals in the same status frame have been given an update frequency, the update
         * frequency will be honored for the entire frame.
         *
         * This function only needs to be called once in the robot program for the provided devices.
         * Additionally, this method does not necessarily need to be called after setting the update
         * frequencies of other signals.
         *
         * To restore the default status update frequencies, call ResetSignalFrequenciesForAll.
         * Alternatively, remove this method call, redeploy the robot application, and power-cycle
         * the devices on the bus. The user can also override individual status update frequencies
         * using BaseStatusSignal#SetUpdateFrequency.
         *
         * This will wait up to 0.100 seconds (100ms) for each status frame.
         *
         * \param devices Devices for which to optimize bus utilization, passed as a span of device pointers.
         * \returns Status code of the first failed optimize call, or OK if all succeeded
         */
        static ctre::phoenix::StatusCode OptimizeBusUtilizationForAll(std::span<traits::CommonDevice* const> devices)
        {
            return OptimizeBusUtilizationForAll(4_Hz, devices);
        }

        /**
         * \brief Optimizes the bus utilization of the provided devices by reducing the update
         * frequencies of their status signals.
         *
         * All status signals that have not been explicitly given an update frequency using
         * BaseStatusSignal#SetUpdateFrequency will be slowed down. Note that if other status
         * signals in the same status frame have been given an update frequency, the update
         * frequency will be honored for the entire frame.
         *
         * This function only needs to be called once in the robot program for the provided devices.
         * Additionally, this method does not necessarily need to be called after setting the update
         * frequencies of other signals.
         *
         * To restore the default status update frequencies, call ResetSignalFrequenciesForAll.
         * Alternatively, remove this method call, redeploy the robot application, and power-cycle
         * the devices on the bus. The user can also override individual status update frequencies
         * using BaseStatusSignal#SetUpdateFrequency.
         *
         * This will wait up to 0.100 seconds (100ms) for each status frame.
         *
         * \param optimizedFreqHz The update frequency to apply to the optimized status signals. A frequency
         *                        of 0 Hz will turn off the signals. Otherwise, the minimum supported signal
         *                        frequency is 4 Hz (default).
         * \param devices Devices for which to optimize bus utilization, passed as a comma-separated list of device references.
         * \returns Status code of the first failed optimize call, or OK if all succeeded
         */
        template <std::derived_from<traits::CommonDevice>... Devices>
        static ctre::phoenix::StatusCode OptimizeBusUtilizationForAll(units::frequency::hertz_t optimizedFreqHz, Devices &... devices)
        {
            return OptimizeBusUtilizationForAll(optimizedFreqHz, std::array<traits::CommonDevice *, sizeof...(Devices)>{(&devices)...});
        }

        /**
         * \brief Optimizes the bus utilization of the provided devices by reducing the update
         * frequencies of their status signals.
         *
         * All status signals that have not been explicitly given an update frequency using
         * BaseStatusSignal#SetUpdateFrequency will be slowed down. Note that if other status
         * signals in the same status frame have been given an update frequency, the update
         * frequency will be honored for the entire frame.
         *
         * This function only needs to be called once in the robot program for the provided devices.
         * Additionally, this method does not necessarily need to be called after setting the update
         * frequencies of other signals.
         *
         * To restore the default status update frequencies, call ResetSignalFrequenciesForAll.
         * Alternatively, remove this method call, redeploy the robot application, and power-cycle
         * the devices on the bus. The user can also override individual status update frequencies
         * using BaseStatusSignal#SetUpdateFrequency.
         *
         * This will wait up to 0.100 seconds (100ms) for each status frame.
         *
         * \param optimizedFreqHz The update frequency to apply to the optimized status signals. A frequency
         *                        of 0 Hz will turn off the signals. Otherwise, the minimum supported signal
         *                        frequency is 4 Hz (default).
         * \param devices Devices for which to optimize bus utilization, passed as a span of device pointers.
         * \returns Status code of the first failed optimize call, or OK if all succeeded
         */
        static ctre::phoenix::StatusCode OptimizeBusUtilizationForAll(units::frequency::hertz_t optimizedFreqHz, std::span<traits::CommonDevice* const> devices)
        {
            ctre::phoenix::StatusCode retval = ctre::phoenix::StatusCode::OK;
            for (auto device : devices) {
                auto const err = device->OptimizeBusUtilization(optimizedFreqHz);
                if (retval.IsOK()) {
                    retval = err;
                }
            }
            return retval;
        }

        /**
         * \brief Resets the update frequencies of all the device's status signals to the defaults.
         *
         * This restores the default update frequency of all status signals, including status signals
         * explicitly given an update frequency using BaseStatusSignal#SetUpdateFrequency and status
         * signals optimized out using OptimizeBusUtilization.
         *
         * \param timeoutSeconds Maximum amount of time to wait for each status frame when performing the action
         * \returns Status code of the first failed update frequency set call, or OK if all succeeded
         */
        ctre::phoenix::StatusCode ResetSignalFrequencies(units::time::second_t timeoutSeconds = 100_ms) final;

        /**
         * \brief Resets the update frequencies of all the devices' status signals to the defaults.
         *
         * This restores the default update frequency of all status signals, including status signals
         * explicitly given an update frequency using BaseStatusSignal#SetUpdateFrequency and status
         * signals optimized out using OptimizeBusUtilizationForAll.
         *
         * This will wait up to 0.100 seconds (100ms) for each status frame.
         *
         * \param devices Devices for which to restore default update frequencies, passed as a comma-separated list of device references.
         * \returns Status code of the first failed restore call, or OK if all succeeded
         */
        template <std::derived_from<traits::CommonDevice>... Devices>
        static ctre::phoenix::StatusCode ResetSignalFrequenciesForAll(Devices &... devices)
        {
            return ResetSignalFrequenciesForAll(std::array<traits::CommonDevice *, sizeof...(Devices)>{(&devices)...});
        }

        /**
         * \brief Resets the update frequencies of all the devices' status signals to the defaults.
         *
         * This restores the default update frequency of all status signals, including status signals
         * explicitly given an update frequency using BaseStatusSignal#SetUpdateFrequency and status
         * signals optimized out using OptimizeBusUtilizationForAll.
         *
         * This will wait up to 0.100 seconds (100ms) for each status frame.
         *
         * \param devices Devices for which to restore default update frequencies, passed as a span of device pointers.
         * \returns Status code of the first failed restore call, or OK if all succeeded
         */
        static ctre::phoenix::StatusCode ResetSignalFrequenciesForAll(std::span<traits::CommonDevice* const> devices)
        {
            ctre::phoenix::StatusCode retval = ctre::phoenix::StatusCode::OK;
            for (auto device : devices) {
                auto const err = device->ResetSignalFrequencies();
                if (retval.IsOK()) {
                    retval = err;
                }
            }
            return retval;
        }

    protected:
        virtual ctre::phoenix::StatusCode SetControlPrivate(controls::ControlRequest const &request);

        template <typename T>
        StatusSignal<T> &LookupStatusSignal(uint16_t spn, std::string signalName, bool reportOnConstruction, bool refresh)
        {
            return LookupCommon<T>(spn, std::move(signalName), nullptr, reportOnConstruction, refresh);
        }

        template <typename T>
        StatusSignal<T> &LookupStatusSignal(uint16_t spn, std::string signalName, std::function<std::map<uint16_t, std::string>()> mapFiller, bool reportOnConstruction, bool refresh)
        {
            return LookupCommon<T>(spn, std::move(signalName), std::move(mapFiller), reportOnConstruction, refresh);
        }
    };

}
}
}
