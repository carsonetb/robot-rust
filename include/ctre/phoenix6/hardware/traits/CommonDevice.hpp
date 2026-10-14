/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/CANBus.hpp"
#include "ctre/phoenix6/controls/ControlRequest.hpp"
#include <functional>
#include <memory>
#include <units/time.h>

namespace ctre {
namespace phoenix6 {
namespace hardware {
namespace traits {

/**
 * Contains everything common between Phoenix 6 devices.
 */
class CommonDevice {
public:
    virtual ~CommonDevice() = default;

    /**
     * \returns The device ID of this device [0,62].
     */
    virtual int GetDeviceID() const = 0;

    /**
     * \returns The network this device is on.
     */
    virtual CANBus GetNetwork() const = 0;

    /**
     * \brief Gets a number unique for this device's hardware type and ID.
     * This number is not unique across networks.
     *
     * \details This can be used to easily reference hardware devices on
     * the same network in collections such as maps.
     *
     * \returns Hash of this device.
     */
    virtual uint64_t GetDeviceHash() const = 0;

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
    virtual std::shared_ptr<controls::ControlRequest const> GetAppliedControl() const = 0;

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
    virtual std::shared_ptr<controls::ControlRequest> GetAppliedControl() = 0;

    /**
     * \returns true if device has reset since the previous call of this routine.
     */
    virtual bool HasResetOccurred() = 0;

    /**
     * \returns a function that checks for device resets.
     */
    virtual std::function<bool()> GetResetOccurredChecker() const = 0;

    /**
     * \brief Returns whether the device is still connected to the robot.
     * This is equivalent to refreshing and checking the latency of the
     * Version status signal.
     *
     * \param maxLatencySeconds The maximum latency of the Version status signal
     *                          before the device is reported as disconnected
     * \returns true if the device is connected
     */
    virtual bool IsConnected(units::second_t maxLatencySeconds = 500_ms) = 0;

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
    virtual ctre::phoenix::StatusCode OptimizeBusUtilization(units::frequency::hertz_t optimizedFreqHz = 4_Hz, units::time::second_t timeoutSeconds = 100_ms) = 0;

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
    virtual ctre::phoenix::StatusCode ResetSignalFrequencies(units::time::second_t timeoutSeconds = 100_ms) = 0;
};

}
}
}
}
