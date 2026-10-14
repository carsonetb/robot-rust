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
#include <units/angle.h>

namespace ctre {
namespace phoenix6 {
namespace controls {

/**
 * Requests Motion Magic® to target a final position using a motion profile, and
 * PID to a differential position setpoint.
 * 
 * Motion Magic® produces a motion profile in real-time while attempting to honor the Cruise Velocity,
 * Acceleration, and (optional) Jerk specified via the Motion Magic® configuration values.  This control mode
 * does not use the Expo_kV or Expo_kA configs.
 * 
 * Target position can be changed on-the-fly and Motion Magic® will do its best to adjust the profile.  This
 * control mode is voltage-based, so relevant closed-loop gains will use Volts for the numerator.
 */
class DifferentialMotionMagicVoltage final : public ControlRequest {
    ctre::phoenix::StatusCode SendRequest(const char *network, uint32_t deviceHash, std::shared_ptr<ControlRequest> &req) const override;

public:
    /**
     * \brief Average position to drive toward in rotations.
     * 
     * - Units: rotations
     * 
     */
    units::angle::turn_t AveragePosition;
    /**
     * \brief Differential position to drive toward in rotations.
     * 
     * - Units: rotations
     * 
     */
    units::angle::turn_t DifferentialPosition;
    /**
     * \brief Set to true to use FOC commutation (requires Phoenix Pro), which
     * increases peak power by ~15% on supported devices (see
     * hardware#traits#SupportsFOC). Set to false to use trapezoidal commutation.
     * 
     * FOC improves motor performance by leveraging torque (current) control. 
     * However, this may be inconvenient for applications that require specifying
     * duty cycle or voltage.  CTR-Electronics has developed a hybrid method that
     * combines the performances gains of FOC while still allowing applications to
     * provide duty cycle or voltage demand.  This not to be confused with simple
     * sinusoidal control or phase voltage control which lacks the performance
     * gains.
     */
    bool EnableFOC = true;
    /**
     * \brief Select which gains are applied to the average controller by selecting
     * the slot.  Use the configuration api to set the gain values for the selected
     * slot before enabling this feature. Slot must be within [0,2].
     */
    int AverageSlot = 0;
    /**
     * \brief Select which gains are applied to the differential controller by
     * selecting the slot.  Use the configuration api to set the gain values for the
     * selected slot before enabling this feature. Slot must be within [0,2].
     */
    int DifferentialSlot = 1;
    /**
     * \brief Set to true to static-brake the rotor when output is zero (or within
     * deadband).  Set to false to use the NeutralMode configuration setting
     * (default). This flag exists to provide the fundamental behavior of this
     * control when output is zero, which is to provide 0V to the motor.
     */
    bool OverrideBrakeDurNeutral = false;
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
     * \brief Requests Motion Magic® to target a final position using a motion
     *        profile, and PID to a differential position setpoint.
     * 
     * \details Motion Magic® produces a motion profile in real-time while
     *          attempting to honor the Cruise Velocity, Acceleration, and
     *          (optional) Jerk specified via the Motion Magic® configuration
     *          values.  This control mode does not use the Expo_kV or Expo_kA
     *          configs.
     *          
     *          Target position can be changed on-the-fly and Motion Magic® will do
     *          its best to adjust the profile.  This control mode is voltage-based,
     *          so relevant closed-loop gains will use Volts for the numerator.
     * 
     * \param AveragePosition Average position to drive toward in rotations.
     * \param DifferentialPosition Differential position to drive toward in
     *                             rotations.
     */
    constexpr DifferentialMotionMagicVoltage(units::angle::turn_t AveragePosition, units::angle::turn_t DifferentialPosition) : ControlRequest{},
        AveragePosition{std::move(AveragePosition)},
        DifferentialPosition{std::move(DifferentialPosition)}
    {}

    constexpr ~DifferentialMotionMagicVoltage() override {}

    /**
     * \brief Gets the name of this control request.
     *
     * \returns Name of the control request
     */
    constexpr std::string_view GetName() const override
    {
        return "DifferentialMotionMagicVoltage";
    }
    
    /**
     * \brief Modifies this Control Request's AveragePosition parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Average position to drive toward in rotations.
     * 
     * - Units: rotations
     * 
     *
     * \param newAveragePosition Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialMotionMagicVoltage &WithAveragePosition(units::angle::turn_t newAveragePosition)
    {
        AveragePosition = std::move(newAveragePosition);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's DifferentialPosition parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Differential position to drive toward in rotations.
     * 
     * - Units: rotations
     * 
     *
     * \param newDifferentialPosition Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialMotionMagicVoltage &WithDifferentialPosition(units::angle::turn_t newDifferentialPosition)
    {
        DifferentialPosition = std::move(newDifferentialPosition);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's EnableFOC parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Set to true to use FOC commutation (requires Phoenix Pro), which increases
     * peak power by ~15% on supported devices (see hardware#traits#SupportsFOC).
     * Set to false to use trapezoidal commutation.
     * 
     * FOC improves motor performance by leveraging torque (current) control. 
     * However, this may be inconvenient for applications that require specifying
     * duty cycle or voltage.  CTR-Electronics has developed a hybrid method that
     * combines the performances gains of FOC while still allowing applications to
     * provide duty cycle or voltage demand.  This not to be confused with simple
     * sinusoidal control or phase voltage control which lacks the performance
     * gains.
     *
     * \param newEnableFOC Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialMotionMagicVoltage &WithEnableFOC(bool newEnableFOC)
    {
        EnableFOC = std::move(newEnableFOC);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's AverageSlot parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Select which gains are applied to the average controller by selecting the
     * slot.  Use the configuration api to set the gain values for the selected slot
     * before enabling this feature. Slot must be within [0,2].
     *
     * \param newAverageSlot Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialMotionMagicVoltage &WithAverageSlot(int newAverageSlot)
    {
        AverageSlot = std::move(newAverageSlot);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's DifferentialSlot parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Select which gains are applied to the differential controller by selecting
     * the slot.  Use the configuration api to set the gain values for the selected
     * slot before enabling this feature. Slot must be within [0,2].
     *
     * \param newDifferentialSlot Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialMotionMagicVoltage &WithDifferentialSlot(int newDifferentialSlot)
    {
        DifferentialSlot = std::move(newDifferentialSlot);
        return *this;
    }
    
    /**
     * \brief Modifies this Control Request's OverrideBrakeDurNeutral parameter and returns itself for
     *        method-chaining and easier to use request API.
     *
     * Set to true to static-brake the rotor when output is zero (or within
     * deadband).  Set to false to use the NeutralMode configuration setting
     * (default). This flag exists to provide the fundamental behavior of this
     * control when output is zero, which is to provide 0V to the motor.
     *
     * \param newOverrideBrakeDurNeutral Parameter to modify
     * \returns Itself
     */
    constexpr DifferentialMotionMagicVoltage &WithOverrideBrakeDurNeutral(bool newOverrideBrakeDurNeutral)
    {
        OverrideBrakeDurNeutral = std::move(newOverrideBrakeDurNeutral);
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
    constexpr DifferentialMotionMagicVoltage &WithLimitForwardMotion(bool newLimitForwardMotion)
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
    constexpr DifferentialMotionMagicVoltage &WithLimitReverseMotion(bool newLimitReverseMotion)
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
    constexpr DifferentialMotionMagicVoltage &WithIgnoreHardwareLimits(bool newIgnoreHardwareLimits)
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
    constexpr DifferentialMotionMagicVoltage &WithIgnoreSoftwareLimits(bool newIgnoreSoftwareLimits)
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
    constexpr DifferentialMotionMagicVoltage &WithUseTimesync(bool newUseTimesync)
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
    constexpr DifferentialMotionMagicVoltage &WithUpdateFreqHz(units::frequency::hertz_t newUpdateFreqHz)
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

