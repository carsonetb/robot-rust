/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/controls/ControlRequest.hpp"
#include <units/frequency.h>
#include <units/time.h>
#include <units/current.h>
#include <units/dimensionless.h>

namespace ctre {
namespace phoenix6 {
namespace controls {

/**
 * Requires Phoenix Pro;
 * Request a specified motor current (field oriented control).
 * 
 * This control request will drive the motor to the requested motor (stator) current value.  This leverages
 * field oriented control (FOC), which means greater peak power than what is documented.  This scales to
 * torque based on Motor's kT constant.
 */
class TorqueCurrentFOC final : public ControlRequest {
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override;

public:
    /**
     * \brief Amount of motor current in Amperes
     * 
     * - Units: A
     * 
     */
    units::current::ampere_t Output;
    /**
     * \brief The maximum absolute motor output that can be applied, which
     * effectively limits the velocity. For example, 0.50 means no more than 50%
     * output in either direction.  This is useful for preventing the motor from
     * spinning to its terminal velocity when there is no external torque applied
     * unto the rotor.  Note this is absolute maximum, so the value should be
     * between zero and one.
     * 
     * - Units: fractional
     * 
     */
    units::dimensionless::scalar_t MaxAbsDutyCycle = 1.0;
    /**
     * \brief Deadband in Amperes.  If torque request is within deadband, the bridge
     * output is neutral. If deadband is set to zero then there is effectively no
     * deadband. Note if deadband is zero, a free spinning motor will spin for quite
     * a while as the firmware attempts to hold the motor's bemf. If user expects
     * motor to cease spinning quickly with a demand of zero, we recommend a
     * deadband of one Ampere. This value will be converted to an integral value of
     * amps.
     * 
     * - Units: A
     * 
     */
    units::current::ampere_t Deadband = 0.0_A;
    /**
     * \brief Set to true to coast the rotor when output is zero (or within
     * deadband).  Set to false to use the NeutralMode configuration setting
     * (default). This flag exists to provide the fundamental behavior of this
     * control when output is zero, which is to provide 0A (zero torque).
     */
    bool OverrideCoastDurNeutral = false;
    /**
     * \brief Set to true to force forward limiting.  This allows users to use other
     * limit switch sensors connected to robot controller.  This also allows use of
     * active sensors that require external power.
     */
    bool LimitForwardMotion = false;
    /**
     * \brief Set to true to force reverse limiting.  This allows users to use other
     * limit switch sensors connected to robot controller.  This also allows use of
     * active sensors that require external power.
     */
    bool LimitReverseMotion = false;
    /**
     * \brief Set to true to ignore hardware limit switches and the
     * LimitForwardMotion and LimitReverseMotion parameters, instead allowing
     * motion.
     * 
     * This can be useful on mechanisms such as an intake/feeder, where a limit
     * switch stops motion while intaking but should be ignored when feeding to a
     * shooter.
     * 
     * The hardware limit faults and Forward/ReverseLimit signals will still report
     * the values of the limit switches regardless of this parameter.
     */
    bool IgnoreHardwareLimits = false;
    /**
     * \brief Set to true to ignore software limits, instead allowing motion.
     * 
     * This can be useful when calibrating the zero point of a mechanism such as an
     * elevator.
     * 
     * The software limit faults will still report the values of the software limits
     * regardless of this parameter.
     */
    bool IgnoreSoftwareLimits = false;
    /**
     * \brief Set to true to delay applying this control request until a timesync
     * boundary (requires Phoenix Pro and CANivore). This eliminates the impact of
     * nondeterministic network delays in exchange for a larger but deterministic
     * control latency.
     * 
     * This requires setting the ControlTimesyncFreqHz config in MotorOutputConfigs.
     * Additionally, when this is enabled, the UpdateFreqHz of this request should
     * be set to 0 Hz.
     */
    bool UseTimesync = false;

    /**
     * \brief The frequency at which this control will update.
     * This is designated in Hertz, with a minimum of 20 Hz
     * (every 50 ms) and a maximum of 1000 Hz (every 1 ms).
     * Some update frequencies are not supported and will be
     * promoted up to the next highest supported frequency.
     *
     * If this field is set to 0 Hz, the control request will
     * be sent immediately as a one-shot frame. This may be useful
     * for advanced applications that require outputs to be
     * synchronized with data acquisition. In this case, we
     * recommend not exceeding 50 ms between control calls.
     */
    units::frequency::hertz_t UpdateFreqHz{100_Hz};

    /**
     * \brief Requires Phoenix Pro;
     *        Request a specified motor current (field oriented control).
     * 
     * \details This control request will drive the motor to the requested motor
     *          (stator) current value.  This leverages field oriented control
     *          (FOC), which means greater peak power than what is documented.  This
     *          scales to torque based on Motor's kT constant.
     * 
     * \param Output Amount of motor current in Amperes
     */
    constexpr TorqueCurrentFOC(units::current::ampere_t Output) : ControlRequest{},
        Output{std::move(Output)}
    {}

    constexpr ~TorqueCurrentFOC() override {}

    /**
     * \brief Gets the name of this control request.
     *
     * \returns Name of the control request
     */
    constexpr std::string_view GetName() const override
    {
        return "TorqueCurrentFOC";
    }
    
    /**
     * \brief Modifies this Control Request's Output parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Amount of motor current in Amperes
     * 
     * - Units: A
     * 
     *
     * \param newOutput Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentFOC &WithOutput(units::current::ampere_t newOutput)
    {
        Output = std::move(newOutput);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's MaxAbsDutyCycle parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * The maximum absolute motor output that can be applied, which effectively
     * limits the velocity. For example, 0.50 means no more than 50% output in
     * either direction.  This is useful for preventing the motor from spinning to
     * its terminal velocity when there is no external torque applied unto the
     * rotor.  Note this is absolute maximum, so the value should be between zero
     * and one.
     * 
     * - Units: fractional
     * 
     *
     * \param newMaxAbsDutyCycle Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentFOC &WithMaxAbsDutyCycle(units::dimensionless::scalar_t newMaxAbsDutyCycle)
    {
        MaxAbsDutyCycle = std::move(newMaxAbsDutyCycle);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's Deadband parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Deadband in Amperes.  If torque request is within deadband, the bridge output
     * is neutral. If deadband is set to zero then there is effectively no deadband.
     * Note if deadband is zero, a free spinning motor will spin for quite a while
     * as the firmware attempts to hold the motor's bemf. If user expects motor to
     * cease spinning quickly with a demand of zero, we recommend a deadband of one
     * Ampere. This value will be converted to an integral value of amps.
     * 
     * - Units: A
     * 
     *
     * \param newDeadband Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentFOC &WithDeadband(units::current::ampere_t newDeadband)
    {
        Deadband = std::move(newDeadband);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's OverrideCoastDurNeutral parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Set to true to coast the rotor when output is zero (or within deadband).  Set
     * to false to use the NeutralMode configuration setting (default). This flag
     * exists to provide the fundamental behavior of this control when output is
     * zero, which is to provide 0A (zero torque).
     *
     * \param newOverrideCoastDurNeutral Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentFOC &WithOverrideCoastDurNeutral(bool newOverrideCoastDurNeutral)
    {
        OverrideCoastDurNeutral = std::move(newOverrideCoastDurNeutral);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's LimitForwardMotion parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Set to true to force forward limiting.  This allows users to use other limit
     * switch sensors connected to robot controller.  This also allows use of active
     * sensors that require external power.
     *
     * \param newLimitForwardMotion Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentFOC &WithLimitForwardMotion(bool newLimitForwardMotion)
    {
        LimitForwardMotion = std::move(newLimitForwardMotion);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's LimitReverseMotion parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Set to true to force reverse limiting.  This allows users to use other limit
     * switch sensors connected to robot controller.  This also allows use of active
     * sensors that require external power.
     *
     * \param newLimitReverseMotion Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentFOC &WithLimitReverseMotion(bool newLimitReverseMotion)
    {
        LimitReverseMotion = std::move(newLimitReverseMotion);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's IgnoreHardwareLimits parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Set to true to ignore hardware limit switches and the LimitForwardMotion and
     * LimitReverseMotion parameters, instead allowing motion.
     * 
     * This can be useful on mechanisms such as an intake/feeder, where a limit
     * switch stops motion while intaking but should be ignored when feeding to a
     * shooter.
     * 
     * The hardware limit faults and Forward/ReverseLimit signals will still report
     * the values of the limit switches regardless of this parameter.
     *
     * \param newIgnoreHardwareLimits Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentFOC &WithIgnoreHardwareLimits(bool newIgnoreHardwareLimits)
    {
        IgnoreHardwareLimits = std::move(newIgnoreHardwareLimits);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's IgnoreSoftwareLimits parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Set to true to ignore software limits, instead allowing motion.
     * 
     * This can be useful when calibrating the zero point of a mechanism such as an
     * elevator.
     * 
     * The software limit faults will still report the values of the software limits
     * regardless of this parameter.
     *
     * \param newIgnoreSoftwareLimits Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentFOC &WithIgnoreSoftwareLimits(bool newIgnoreSoftwareLimits)
    {
        IgnoreSoftwareLimits = std::move(newIgnoreSoftwareLimits);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's UseTimesync parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Set to true to delay applying this control request until a timesync boundary
     * (requires Phoenix Pro and CANivore). This eliminates the impact of
     * nondeterministic network delays in exchange for a larger but deterministic
     * control latency.
     * 
     * This requires setting the ControlTimesyncFreqHz config in MotorOutputConfigs.
     * Additionally, when this is enabled, the UpdateFreqHz of this request should
     * be set to 0 Hz.
     *
     * \param newUseTimesync Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentFOC &WithUseTimesync(bool newUseTimesync)
    {
        UseTimesync = std::move(newUseTimesync);
        return *this;
    }

    /**
     * \brief Sets the frequency at which this control will update.
     * This is designated in Hertz, with a minimum of 20 Hz
     * (every 50 ms) and a maximum of 1000 Hz (every 1 ms).
     * Some update frequencies are not supported and will be
     * promoted up to the next highest supported frequency.
     *
     * If this field is set to 0 Hz, the control request will
     * be sent immediately as a one-shot frame. This may be useful
     * for advanced applications that require outputs to be
     * synchronized with data acquisition. In this case, we
     * recommend not exceeding 50 ms between control calls.
     *
     * \param newUpdateFreqHz Parameter to modify
     * \returns Itself
     */
    constexpr TorqueCurrentFOC &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
    {
        UpdateFreqHz = newUpdateFreqHz;
        return *this;
    }

    /**
     * \brief Returns a string representation of the object.
     *
     * \returns a string representation of the object.
     */
    std::string ToString() const override;

    /**
     * \brief Gets information about this control request.
     *
     * \returns Map of control parameter names and corresponding applied values
     */
    std::map<std::string, std::string> GetControlInfo() const override;
};

}
}
}

