/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/core/CoreCANrange.hpp"

#include "wpi/sendable/Sendable.h"
#include "wpi/sendable/SendableBuilder.h"
#include "wpi/sendable/SendableHelper.h"
#include <hal/SimDevice.h>

namespace ctre {
namespace phoenix6 {
namespace hardware {

/**
 * Class for CANrange, a CAN based Time of Flight (ToF) sensor that measures the
 * distance to the front of the device.
 */
class CANrange : public core::CoreCANrange,
                 public wpi::Sendable,
                 public wpi::SendableHelper<CANrange>
{
    /*
     * The StatusSignal getters are copies so that calls
     * to the WPI interface do not update any references
     *
     * These are also mutable so the const getter methods are
     * properly managed.
     */
    mutable StatusSignal<units::length::meter_t> m_distanceGetter = GetDistance(false);
    mutable StatusSignal<bool> m_isDetectedGetter = GetIsDetected(false);

    hal::SimDevice m_simCANrange;
    hal::SimDouble m_simSupplyVoltage;
    hal::SimDouble m_simDistance;
    hal::SimBoolean m_simIsDetected;

    int32_t m_simPeriodicUid{-1};
    std::vector<int32_t> m_simValueChangedUids;

    static void OnValueChanged(const char *name, void *param, HAL_SimValueHandle handle,
                                HAL_Bool readonly, const struct HAL_Value *value);
    static void OnPeriodic(void *param);

public:
    /**
     * Constructs a new CANrange object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner.
     * \param canbus      Name of the CAN bus this device is on. Possible CAN bus strings are:
     *                    - "rio" for the native roboRIO CAN bus
     *                    - CANivore name or serial number
     *                    - SocketCAN interface (non-FRC Linux only)
     *                    - "*" for any CANivore seen by the program
     *                    - empty string (default) to select the default for the system:
     *                      - "rio" on roboRIO
     *                      - "can0" on Linux
     *                      - "*" on Windows
     */
    CANrange(int deviceId, std::string canbus = "");
    /**
     * Constructs a new CANrange object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner.
     * \param canbus      The CAN bus this device is on.
     */
    CANrange(int deviceId, CANBus canbus) :
        CANrange{deviceId, std::string{canbus.GetName()}}
    {}

    ~CANrange();

    void InitSendable(wpi::SendableBuilder &builder) override;
};

}
}
}