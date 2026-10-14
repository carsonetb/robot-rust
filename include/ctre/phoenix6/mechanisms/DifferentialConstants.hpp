/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/configs/Configuration.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"

namespace ctre {
namespace phoenix6 {
namespace mechanisms {

/**
 * \brief Sensor sources for a differential Pigeon 2.
 */
enum class DifferentialPigeon2Source {
    /**
     * \brief Use the yaw component of the Pigeon 2.
     */
    Yaw,
    /**
     * \brief Use the pitch component of the Pigeon 2.
     */
    Pitch,
    /**
     * \brief Use the roll component of the Pigeon 2.
     */
    Roll,
};

/**
 * \brief Sensor sources for a differential CTR Electronics'
 * CANdi™ branded device.
 */
enum class DifferentialCANdiSource {
    /**
     * \brief Use a pulse-width encoder remotely attached to the Sensor Input 1 (S1IN).
     */
    PWM1,
    /**
     * \brief Use a pulse-width encoder remotely attached to the Sensor Input 2 (S2IN).
     */
    PWM2,
    /**
     * \brief Use a quadrature encoder remotely attached to the two Sensor Inputs.
     */
    Quadrature,
};

/**
 * \brief All constants for setting up the motors of a differential mechanism.
 */
template <std::derived_from<configs::ParentConfiguration> MotorConfigsT>
struct DifferentialMotorConstants final {
    constexpr DifferentialMotorConstants() = default;

    /**
     * \brief Name of the CAN bus the mechanism is on. Possible CAN bus strings are:
     * 
     * - "rio" for the native roboRIO CAN bus
     * - CANivore name or serial number
     * - SocketCAN interface (non-FRC Linux only)
     * - "*" for any CANivore seen by the program
     * - empty string (default) to select the default for the system:
     *   - "rio" on roboRIO
     *   - "can0" on Linux
     *   - "*" on Windows
     * 
     * Note that all devices must be on the same CAN bus.
     */
    std::string_view CANBusName = "";
    /**
     * \brief CAN ID of the leader motor in the differential mechanism. The leader
     * will have the differential output added to its regular output.
     */
    int LeaderId = 0;
    /**
     * \brief CAN ID of the follower motor in the differential mechanism. The
     * follower will have the differential output subtracted from its regular
     * output.
     */
    int FollowerId = 0;
    /**
     * \brief The alignment of the differential leader and follower motors, ignoring
     * the configured inverts.
     */
    signals::MotorAlignmentValue Alignment = signals::MotorAlignmentValue::Aligned;
    /**
     * \brief The ratio of sensor rotations to the differential mechanism's
     * difference output, where a ratio greater than 1 is a reduction.
     * 
     * When not using a separate sensor on the difference axis, the sensor is
     * considered half of the difference between the two motor controllers'
     * mechanism positions/velocities. As a result, this should be set to the gear
     * ratio on the difference axis in that scenario, or any gear ratio between the
     * sensor and the mechanism differential when using another sensor source.
     */
    units::dimensionless::scalar_t SensorToDifferentialRatio = 1.0;
    /**
     * \brief The update rate of the closed-loop controllers. This determines the
     * update rate of the differential leader's DifferentialOutput status signal,
     * the follower's Position and Velocity signals, and the relevant signals for
     * any other selected differential sensor.
     */
    units::frequency::hertz_t ClosedLoopRate = 100_Hz;
    /**
     * \brief The initial configs used to configure the differential leader. The
     * default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the DifferentialMotorConstants class is available to be
     * changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#DifferentialSensorsConfigs (automatic based on the devices used)
     * 
     */
    MotorConfigsT LeaderInitialConfigs = {};
    /**
     * \brief The initial configs used to configure the differential follower. The
     * default value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the DifferentialMotorConstants class is available to be
     * changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#DifferentialSensorsConfigs (factory defaulted)
     * - configs#MotorOutputConfigs#Inverted (determined from #Alignment and the
     *   #LeaderInitialConfigs invert)
     * 
     * If #FollowerUsesCommonLeaderConfigs is set to true (default), the following
     * configs are copied from #LeaderInitialConfigs:
     * 
     * - configs#AudioConfigs
     * - configs#CurrentLimitsConfigs
     * - configs#MotorOutputConfigs (except configs#MotorOutputConfigs#Inverted)
     * - configs#TorqueCurrentConfigs
     * - configs#VoltageConfigs
     * 
     */
    MotorConfigsT FollowerInitialConfigs = {};
    /**
     * \brief Whether the follower should overwrite some of its initial configs with
     * common configs from the #LeaderInitialConfigs, such as current limits. The
     * list of configs that are copied is documented in #FollowerInitialConfigs.
     */
    bool FollowerUsesCommonLeaderConfigs = true;
    
    /**
     * \brief Modifies the CANBusName parameter and returns itself.
     *
     * Name of the CAN bus the mechanism is on. Possible CAN bus strings are:
     * 
     * - "rio" for the native roboRIO CAN bus
     * - CANivore name or serial number
     * - SocketCAN interface (non-FRC Linux only)
     * - "*" for any CANivore seen by the program
     * - empty string (default) to select the default for the system:
     *   - "rio" on roboRIO
     *   - "can0" on Linux
     *   - "*" on Windows
     * 
     * Note that all devices must be on the same CAN bus.
     *
     * \param newCANBusName Parameter to modify
     * \returns this object
     */
    constexpr DifferentialMotorConstants<MotorConfigsT> &WithCANBusName(std::string_view newCANBusName)
    {
        this->CANBusName = newCANBusName;
        return *this;
    }
    
    /**
     * \brief Modifies the LeaderId parameter and returns itself.
     *
     * CAN ID of the leader motor in the differential mechanism. The leader will
     * have the differential output added to its regular output.
     *
     * \param newLeaderId Parameter to modify
     * \returns this object
     */
    constexpr DifferentialMotorConstants<MotorConfigsT> &WithLeaderId(int newLeaderId)
    {
        this->LeaderId = newLeaderId;
        return *this;
    }
    
    /**
     * \brief Modifies the FollowerId parameter and returns itself.
     *
     * CAN ID of the follower motor in the differential mechanism. The follower will
     * have the differential output subtracted from its regular output.
     *
     * \param newFollowerId Parameter to modify
     * \returns this object
     */
    constexpr DifferentialMotorConstants<MotorConfigsT> &WithFollowerId(int newFollowerId)
    {
        this->FollowerId = newFollowerId;
        return *this;
    }
    
    /**
     * \brief Modifies the Alignment parameter and returns itself.
     *
     * The alignment of the differential leader and follower motors, ignoring the
     * configured inverts.
     *
     * \param newAlignment Parameter to modify
     * \returns this object
     */
    constexpr DifferentialMotorConstants<MotorConfigsT> &WithAlignment(signals::MotorAlignmentValue newAlignment)
    {
        this->Alignment = newAlignment;
        return *this;
    }
    
    /**
     * \brief Modifies the SensorToDifferentialRatio parameter and returns itself.
     *
     * The ratio of sensor rotations to the differential mechanism's difference
     * output, where a ratio greater than 1 is a reduction.
     * 
     * When not using a separate sensor on the difference axis, the sensor is
     * considered half of the difference between the two motor controllers'
     * mechanism positions/velocities. As a result, this should be set to the gear
     * ratio on the difference axis in that scenario, or any gear ratio between the
     * sensor and the mechanism differential when using another sensor source.
     *
     * \param newSensorToDifferentialRatio Parameter to modify
     * \returns this object
     */
    constexpr DifferentialMotorConstants<MotorConfigsT> &WithSensorToDifferentialRatio(units::dimensionless::scalar_t newSensorToDifferentialRatio)
    {
        this->SensorToDifferentialRatio = newSensorToDifferentialRatio;
        return *this;
    }
    
    /**
     * \brief Modifies the ClosedLoopRate parameter and returns itself.
     *
     * The update rate of the closed-loop controllers. This determines the update
     * rate of the differential leader's DifferentialOutput status signal, the
     * follower's Position and Velocity signals, and the relevant signals for any
     * other selected differential sensor.
     *
     * \param newClosedLoopRate Parameter to modify
     * \returns this object
     */
    constexpr DifferentialMotorConstants<MotorConfigsT> &WithClosedLoopRate(units::frequency::hertz_t newClosedLoopRate)
    {
        this->ClosedLoopRate = newClosedLoopRate;
        return *this;
    }
    
    /**
     * \brief Modifies the LeaderInitialConfigs parameter and returns itself.
     *
     * The initial configs used to configure the differential leader. The default
     * value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the DifferentialMotorConstants class is available to be
     * changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#DifferentialSensorsConfigs (automatic based on the devices used)
     * 
     *
     * \param newLeaderInitialConfigs Parameter to modify
     * \returns this object
     */
    constexpr DifferentialMotorConstants<MotorConfigsT> &WithLeaderInitialConfigs(const MotorConfigsT& newLeaderInitialConfigs)
    {
        this->LeaderInitialConfigs = newLeaderInitialConfigs;
        return *this;
    }
    
    /**
     * \brief Modifies the FollowerInitialConfigs parameter and returns itself.
     *
     * The initial configs used to configure the differential follower. The default
     * value is the factory-default.
     * 
     * Users may change the initial configuration as they need. Any config that's
     * not referenced in the DifferentialMotorConstants class is available to be
     * changed.
     * 
     * The list of configs that will be overwritten is as follows:
     * 
     * - configs#DifferentialSensorsConfigs (factory defaulted)
     * - configs#MotorOutputConfigs#Inverted (determined from #Alignment and the
     *   #LeaderInitialConfigs invert)
     * 
     * If #FollowerUsesCommonLeaderConfigs is set to true (default), the following
     * configs are copied from #LeaderInitialConfigs:
     * 
     * - configs#AudioConfigs
     * - configs#CurrentLimitsConfigs
     * - configs#MotorOutputConfigs (except configs#MotorOutputConfigs#Inverted)
     * - configs#TorqueCurrentConfigs
     * - configs#VoltageConfigs
     * 
     *
     * \param newFollowerInitialConfigs Parameter to modify
     * \returns this object
     */
    constexpr DifferentialMotorConstants<MotorConfigsT> &WithFollowerInitialConfigs(const MotorConfigsT& newFollowerInitialConfigs)
    {
        this->FollowerInitialConfigs = newFollowerInitialConfigs;
        return *this;
    }
    
    /**
     * \brief Modifies the FollowerUsesCommonLeaderConfigs parameter and returns itself.
     *
     * Whether the follower should overwrite some of its initial configs with common
     * configs from the #LeaderInitialConfigs, such as current limits. The list of
     * configs that are copied is documented in #FollowerInitialConfigs.
     *
     * \param newFollowerUsesCommonLeaderConfigs Parameter to modify
     * \returns this object
     */
    constexpr DifferentialMotorConstants<MotorConfigsT> &WithFollowerUsesCommonLeaderConfigs(bool newFollowerUsesCommonLeaderConfigs)
    {
        this->FollowerUsesCommonLeaderConfigs = newFollowerUsesCommonLeaderConfigs;
        return *this;
    }
};

}
}
}
