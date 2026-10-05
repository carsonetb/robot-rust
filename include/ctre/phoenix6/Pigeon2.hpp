/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/core/CorePigeon2.hpp"

#include "frc/geometry/Rotation2d.h"
#include "frc/geometry/Rotation3d.h"
#include "wpi/sendable/Sendable.h"
#include "wpi/sendable/SendableBuilder.h"
#include "wpi/sendable/SendableHelper.h"
#include <hal/SimDevice.h>


namespace ctre {
namespace phoenix6 {
namespace hardware {

/**
 * Class description for the Pigeon 2 IMU sensor that measures orientation.
 */
class Pigeon2 : public core::CorePigeon2,
                public wpi::Sendable,
                public wpi::SendableHelper<Pigeon2>
{
    /*
     * The StatusSignal getters are copies so that calls
     * to the WPI interface do not update any references
     *
     * These are also mutable so the const getter methods are
     * properly managed.
     */
    mutable StatusSignal<units::angle::degree_t> m_yawGetter = GetYaw(false);
    mutable StatusSignal<units::angular_velocity::degrees_per_second_t> m_yawRateGetter = GetAngularVelocityZWorld(false);
    mutable StatusSignal<units::dimensionless::scalar_t> m_quatWGetter = GetQuatW(false);
    mutable StatusSignal<units::dimensionless::scalar_t> m_quatXGetter = GetQuatX(false);
    mutable StatusSignal<units::dimensionless::scalar_t> m_quatYGetter = GetQuatY(false);
    mutable StatusSignal<units::dimensionless::scalar_t> m_quatZGetter = GetQuatZ(false);

    hal::SimDevice m_simPigeon;
    hal::SimDouble m_simSupplyVoltage;
    hal::SimDouble m_simYaw;
    hal::SimDouble m_simRawYaw;
    hal::SimDouble m_simPitch;
    hal::SimDouble m_simRoll;
    hal::SimDouble m_simAngularVelocityX;
    hal::SimDouble m_simAngularVelocityY;
    hal::SimDouble m_simAngularVelocityZ;

    int32_t m_simPeriodicUid{-1};
    std::vector<int32_t> m_simValueChangedUids;

    static void OnValueChanged(const char* name, void* param, HAL_SimValueHandle handle,
                               HAL_Bool readonly, const struct HAL_Value* value);
    static void OnPeriodic(void* param);

public:
    /**
     * Constructs a new Pigeon 2 sensor object.
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
    Pigeon2(int deviceId, std::string canbus = "");
    /**
     * Constructs a new Pigeon 2 sensor object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner.
     * \param canbus      The CAN bus this device is on.
     */
    Pigeon2(int deviceId, CANBus canbus) :
        Pigeon2{deviceId, std::string{canbus.GetName()}}
    {}

    ~Pigeon2();

    void InitSendable(wpi::SendableBuilder& builder) override;

    /**
     * \brief Resets the Pigeon 2 to a heading of zero.
     *
     * \details This can be used if there is significant drift in the gyro,
     * and it needs to be recalibrated after it has been running.
     */
    void Reset();
    /**
     * \brief Returns the heading of the robot in degrees.
     *
     * The angle increases as the Pigeon 2 turns clockwise when looked
     * at from the top. This follows the NED axis convention.
     *
     * \details The angle is continuous; that is, it will continue from
     * 360 to 361 degrees. This allows for algorithms that wouldn't want
     * to see a discontinuity in the gyro output as it sweeps past from
     * 360 to 0 on the second time around.
     *
     * \deprecated This API is deprecated for removal in the 2026 season.
     * Users should use #GetYaw instead. Note that Yaw is CCW+, whereas
     * this API is CW+.
     *
     * \returns The current heading of the robot in degrees
     */
    [[deprecated("This API is deprecated for removal in the 2026 season."
                "Users should use GetYaw() instead."
                "Note that Yaw is CCW+, whereas this API is CW+.")]]
    double GetAngle() const;
    /**
     * \brief Returns the rate of rotation of the Pigeon 2.
     *
     * The rate is positive as the Pigeon 2 turns clockwise when looked
     * at from the top.
     *
     * \deprecated This API is deprecated for removal in the 2026 season.
     * Users should use #GetAngularVelocityZWorld instead. Note that
     * AngularVelocityZWorld is CCW+, whereas this API is CW+.
     *
     * \returns The current rate in degrees per second
     */
    [[deprecated("This API is deprecated for removal in the 2026 season."
                "Users should use GetAngularVelocityZWorld() instead."
                "Note that AngularVelocityZWorld is CCW+, whereas this API is CW+.")]]
    double GetRate() const;
    /**
     * \brief Returns the heading of the robot as a frc#Rotation2d.
     *
     * The angle increases as the Pigeon 2 turns counterclockwise when
     * looked at from the top. This follows the NWU axis convention.
     *
     * \details The angle is continuous; that is, it will continue from
     * 360 to 361 degrees. This allows for algorithms that wouldn't want
     * to see a discontinuity in the gyro output as it sweeps past from
     * 360 to 0 on the second time around.
     *
     * \returns The current heading of the robot as a frc#Rotation2d
     */
    frc::Rotation2d GetRotation2d() const;
    /**
     * \brief Returns the orientation of the robot as a frc#Rotation3d
     * created from the quaternion signals.
     *
     * \returns The current orientation of the robot as a frc#Rotation3d
     */
    frc::Rotation3d GetRotation3d() const;
};

}
}
}