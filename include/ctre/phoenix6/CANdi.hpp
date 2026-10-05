/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/core/CoreCANdi.hpp"

#include "wpi/sendable/Sendable.h"
#include "wpi/sendable/SendableBuilder.h"
#include "wpi/sendable/SendableHelper.h"
#include <hal/SimDevice.h>

namespace ctre {
namespace phoenix6 {
namespace hardware {

/**
 * Class for CTR Electronics' CANdi™ branded device,
 * a device that integrates digital signals into the existing CAN bus network.
 */
class CANdi : public core::CoreCANdi,
              public wpi::Sendable,
              public wpi::SendableHelper<CANdi>
{
    /*
     * The StatusSignal getters are copies so that calls
     * to the WPI interface do not update any references
     *
     * These are also mutable so the const getter methods are
     * properly managed.
     */

    hal::SimDevice m_simCANdi;
    hal::SimDouble m_simSupplyVoltage;
    hal::SimDouble m_simRequestedOutputCurrent;
    hal::SimDouble m_simOutputCurrent;

    hal::SimDevice m_simPwm1;
    hal::SimDouble m_simPwm1Position;
    hal::SimBoolean m_simPwm1Connected;
    hal::SimDouble m_simPwm1Velocity;
    hal::SimDouble m_simPwm1RiseRise;
    hal::SimDouble m_simPwm1RiseFall;

    hal::SimDevice m_simPwm2;
    hal::SimDouble m_simPwm2Position;
    hal::SimBoolean m_simPwm2Connected;
    hal::SimDouble m_simPwm2Velocity;
    hal::SimDouble m_simPwm2RiseRise;
    hal::SimDouble m_simPwm2RiseFall;

    hal::SimDevice m_simQuadrature;
    hal::SimDouble m_simQuadPos;
    hal::SimDouble m_simQuadRawPos;
    hal::SimDouble m_simQuadVel;

    hal::SimDevice m_simS1DIO;
    hal::SimBoolean m_simS1Closed;
    hal::SimEnum m_simS1State;

    hal::SimDevice m_simS2DIO;
    hal::SimBoolean m_simS2Closed;
    hal::SimEnum m_simS2State;

    int32_t m_simPeriodicUid{-1};
    std::vector<int32_t> m_simValueChangedUids;

    static void OnValueChanged(const char *name, void *param, HAL_SimValueHandle handle,
                                HAL_Bool readonly, const struct HAL_Value *value);
    static void OnPeriodic(void *param);

public:
    /**
     * Constructs a new CANdi object.
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
    CANdi(int deviceId, std::string canbus = "");
    /**
     * Constructs a new CANdi object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner.
     * \param canbus      The CAN bus this device is on.
     */
    CANdi(int deviceId, CANBus canbus) :
        CANdi{deviceId, std::string{canbus.GetName()}}
    {}

    ~CANdi();

    void InitSendable(wpi::SendableBuilder &builder) override;
};

}
}
}
