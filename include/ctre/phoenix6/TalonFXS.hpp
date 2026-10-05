/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/core/CoreTalonFXS.hpp"
#include "ctre/phoenix6/wpiutils/MotorSafetyImplem.hpp"

#include "frc/MotorSafety.h"
#include "wpi/sendable/Sendable.h"
#include "wpi/sendable/SendableBuilder.h"
#include "wpi/sendable/SendableHelper.h"
#include <hal/SimDevice.h>

#include <string>

namespace ctre {
namespace phoenix6 {
namespace hardware {

/**
 * Class description for the Talon FXS motor controller.
 */
class TalonFXS : public core::CoreTalonFXS,
                public wpi::Sendable,
                public wpi::SendableHelper<TalonFXS>
{
public:
    /**
     * \brief The default motor safety timeout IF calling
     * application enables the feature.
     */
    static constexpr auto kDefaultSafetyExpiration = 100_ms;

private:
    std::string m_description;

    /* Motor Safety */
    mutable std::unique_ptr<wpiutils::MotorSafetyImplem> m_motorSafety{};
    units::second_t m_motSafeExpiration{kDefaultSafetyExpiration};
    mutable std::recursive_mutex m_motorSafetyLock;

    /*
     * The StatusSignal getters are copies so that calls
     * to the WPI interface do not update any references
     *
     * These are also mutable so the const getter methods are
     * properly managed.
     */
    mutable StatusSignal<units::dimensionless::scalar_t> m_dutyCycle = GetDutyCycle(false);

    controls::DutyCycleOut m_setterControl{0.0};
    controls::NeutralOut m_brakeRef{};
    controls::VoltageOut m_voltageControl{0_V};

    hal::SimDevice m_simMotor;
    hal::SimDouble m_simSupplyVoltage;
    hal::SimDouble m_simDutyCycle;
    hal::SimDouble m_simMotorVoltage;
    hal::SimDouble m_simTorqueCurrent;
    hal::SimDouble m_simSupplyCurrent;

    hal::SimDevice m_simForwardLimit;
    hal::SimBoolean m_simForwardLimitValue;

    hal::SimDevice m_simReverseLimit;
    hal::SimBoolean m_simReverseLimitValue;

    hal::SimDevice m_simRotor;
    hal::SimDouble m_simRotorPos;
    hal::SimDouble m_simRotorRawPos;
    hal::SimDouble m_simRotorVel;
    hal::SimDouble m_simRotorAccel;

    int32_t m_simPeriodicUid{-1};
    std::vector<int32_t> m_simValueChangedUids;

    static void OnValueChanged(const char* name, void *param, HAL_SimValueHandle handle,
                               HAL_Bool readonly, const struct HAL_Value* value);
    static void OnPeriodic(void* param);

    /** caller must lock appropriately */
    wpiutils::MotorSafetyImplem &GetMotorSafety() const;

public:
    /**
     * Constructs a new Talon FXS motor controller object.
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
    TalonFXS(int deviceId, std::string canbus = "");
    /**
     * Constructs a new Talon FXS motor controller object.
     *
     * \param deviceId    ID of the device, as configured in Phoenix Tuner.
     * \param canbus      The CAN bus this device is on.
     */
    TalonFXS(int deviceId, CANBus canbus) :
        TalonFXS{deviceId, std::string{canbus.GetName()}}
    {}

    ~TalonFXS();

    /**
     * \brief Common interface for setting the speed of a motor controller.
     *
     * \param speed The speed to set. Value should be between -1.0 and 1.0.
     */
    void Set(double speed);
    /**
     * \brief Common interface for seting the direct voltage output of a motor controller.
     *
     * \param volts The voltage to output.
     */
    void SetVoltage(units::volt_t volts);
    /**
     * \brief Common interface for getting the current set speed of a motor controller.
     *
     * \returns The current set speed. Value is between -1.0 and 1.0.
     */
    double Get() const;
    /**
     * \brief Common interface for disabling a motor controller.
     */
    void Disable();
    /**
     * \brief Common interface to stop motor movement until Set is called again.
     */
    void StopMotor();
    /**
     * \brief Common interface for inverting direction of a motor controller.
     *
     * Since invert is a config, this API is blocking. We recommend that
     * users avoid calling this API periodically.
     *
     * Since invert affects the reported motor position, this API should
     * be called before any calls to #SetPosition.
     *
     * \deprecated This API is deprecated for removal in 2026. Since invert
     * is a config, apply the invert setting as part of a full
     * configs#TalonFXSConfiguration object. Invert can be found in the
     * MotorOutput config group.
     *
     * \param isInverted The state of inversion, true is inverted.
     * \returns Status of refrshing and applying the invet config
     */
    [[deprecated("This API is deprecated for removal in 2026."
                " Since invert is a config, apply the invert setting as part of a full configs::TalonFXSConfiguration object."
                " Invert can be found in the MotorOutput config group.")]]
    ctre::phoenix::StatusCode SetInverted(bool isInverted);
    /**
     * \brief Common interface for returning the inversion state of a motor controller.
     *
     * Since invert is a config, this API is blocking. We recommend that
     * users avoid calling this API periodically.
     *
     * \deprecated This API is deprecated for removal in 2026. Since invert
     * is a config, read the invert setting as part of a full
     * configs#TalonFXSConfiguration object or using a configs#MotorOutputConfigs
     * object. Applied invert, which may not match the invert config for followers,
     * can also be fetched using #GetAppliedRotorPolarity.
     *
     * \returns The state of the inversion, true is inverted.
     */
    [[deprecated("This API is deprecated for removal in 2026."
                " Since invert is a config, read the invert setting as part of a full configs::TalonFXSConfiguration object"
                " or using a configs::MotorOutputConfigs object."
                " Applied invert, which may not match the invert config for followers, can also be fetched using GetAppliedRotorPolarity.")]]
    bool GetInverted() const;
    /**
     * \brief Sets the mode of operation when output is neutral or disabled.
     *        This is equivalent to setting the configs#MotorOutputConfigs#NeutralMode
     *        when applying a configs#TalonFXSConfiguration to the motor.
     *
     * Since neutral mode is a config, this API is blocking. We recommend
     * that users avoid calling this API periodically.
     *
     * \param neutralMode The state of the motor controller bridge when output is neutral or disabled
     * \param timeoutSeconds Maximum amount of time to wait when performing configuration
     * \returns Status of refreshing and applying the neutral mode config
     */
    ctre::phoenix::StatusCode SetNeutralMode(signals::NeutralModeValue neutralMode, units::second_t timeoutSeconds = 100_ms);

    /**
     * \returns Description of motor controller
     */
    std::string GetDescription() const;
    void InitSendable(wpi::SendableBuilder &builder) override;

    /* ----- Motor Safety ----- */
    /**
     * \brief Feed the motor safety object.
     *
     * Resets the timer on this object that is used to do the timeouts.
     */
    void Feed();
    /**
     * \brief Set the expiration time for the corresponding motor safety object.
     *
     * \param expirationTime The timeout value.
     */
    void SetExpiration(units::second_t expirationTime);
    /**
     * \brief Retrieve the timeout value for the corresponding motor safety object.
     *
     * \returns the timeout value.
     */
    units::second_t GetExpiration() const;
    /**
     * \brief Determine of the motor is still operating or has timed out.
     *
     * \returns true if the motor is still operating normally and hasn't timed out.
     */
    bool IsAlive() const;
    /**
     * \brief Enable/disable motor safety for this device.
     *
     * Turn on and off the motor safety option for this object.
     *
     * \param enabled True if motor safety is enforced for this object.
     */
    void SetSafetyEnabled(bool enabled);
    /**
     * \brief Return the state of the motor safety enabled flag.
     *
     * Return if the motor safety is currently enabled for this device.
     *
     * \returns True if motor safety is enforced for this device
     */
    bool IsSafetyEnabled() const;

protected:
	//------------- Intercept CTRE calls for motor safety ------------//
    ctre::phoenix::StatusCode SetControlPrivate(const controls::ControlRequest &request) override;
};

}
}
}
