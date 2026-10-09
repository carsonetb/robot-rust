/*
 * Copyright (c) 2018-2026 REV Robotics
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of REV Robotics nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#ifdef _MSC_VER
// Disable deprecation warnings for this file when using VS compiler
#pragma warning(disable : 4996)
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

#include <atomic>

#include "rev/ConfigureTypes.h"
#include "rev/REVLibError.h"
#include "rev/SparkAbsoluteEncoder.h"
#include "rev/SparkAnalogSensor.h"
#include "rev/SparkClosedLoopController.h"
#include "rev/SparkLimitSwitch.h"
#include "rev/SparkLowLevel.h"
#include "rev/SparkRelativeEncoder.h"
#include "rev/SparkSoftLimit.h"

// Defined in HIL tester source
class ConfigBase;

namespace rev::spark {

class SparkBaseConfig;

class SparkBase : public SparkLowLevel {
    friend class SparkMax;
    friend class SparkFlex;
    friend class SparkLimitSwitch;
    friend class SparkSoftLimit;
    friend class SparkRelativeEncoder;
    friend class SparkMaxAlternateEncoder;
    friend class SparkAbsoluteEncoder;
    friend class SparkSim;
    friend class SparkClosedLoopController;

    // Defined in HIL tester source
    friend class ::ConfigBase;

public:
    enum class IdleMode { kCoast = 0, kBrake = 1 };

    enum class SoftLimitDirection { kForward, kReverse };

    enum class ResetMode { kNoResetSafeParameters, kResetSafeParameters };

    enum class PersistMode { kNoPersistParameters, kPersistParameters };

    struct Faults {
        bool other;
        bool motorType;
        bool sensor;
        bool can;
        bool temperature;
        bool gateDriver;
        bool escEeprom;
        bool firmware;
        int rawBits;

        Faults() {}

        explicit Faults(uint16_t faults) {
            rawBits = faults;
            other = (faults & 0x1) != 0;
            motorType = (faults & 0x2) != 0;
            sensor = (faults & 0x4) != 0;
            can = (faults & 0x8) != 0;
            temperature = (faults & 0x10) != 0;
            gateDriver = (faults & 0x20) != 0;
            escEeprom = (faults & 0x40) != 0;
            firmware = (faults & 0x80) != 0;
        }
    };

    struct Warnings {
        bool brownout;
        bool overcurrent;
        bool escEeprom;
        bool extEeprom;
        bool sensor;
        bool stall;
        bool hasReset;
        bool other;
        int rawBits;

        Warnings() {}

        explicit Warnings(uint16_t warnings) {
            rawBits = warnings;
            brownout = (warnings & 0x1) != 0;
            overcurrent = (warnings & 0x2) != 0;
            escEeprom = (warnings & 0x4) != 0;
            extEeprom = (warnings & 0x8) != 0;
            sensor = (warnings & 0x10) != 0;
            stall = (warnings & 0x20) != 0;
            hasReset = (warnings & 0x40) != 0;
            other = (warnings & 0x80) != 0;
        }
    };

    /**
     * Closes the SPARK motor controller
     */
    ~SparkBase() override = default;

    /**** Speed Controller Interface ****/
    /**
     * Common interface for setting the speed of a speed controller.
     *
     * @param speed The speed to set.  Value should be between -1.0 and 1.0.
     */
    void Set(double speed) override;

    /**
     * Sets the voltage output of the SpeedController.  This is equivalent to
     * a call to SetReference(output, SparkBase::ControlType::kVoltage). The
     * behavior of this call differs slightly from the WPILib documentation for
     * this call since the device internally sets the desired voltage (not a
     * compensation value). That means that this *can* be a 'set-and-forget'
     * call.
     *
     * @param output The voltage to output.
     */
    void SetVoltage(units::volt_t output) override;

    /**
     * Common interface for getting the current set speed of a speed controller.
     *
     * @return The current set speed.  Value is between -1.0 and 1.0.
     */
    double Get() const override;

    /**
     * Common interface for inverting direction of a speed controller.
     *
     * This call has no effect if the controller is a follower. To invert
     * a follower, see the follow() method.
     *
     * @param isInverted The state of inversion, true is inverted.
     * @deprecated Use SparkBaseConfig.Inverted() with Configure() instead
     */
    [[deprecated("Use SparkBaseConfig.Inverted() with Configure() instead")]]
    void SetInverted(bool isInverted) override;

    /**
     * Common interface for returning the inversion state of a speed controller.
     *
     * This call has no effect if the controller is a follower.
     *
     * @return isInverted The state of inversion, true is inverted.
     * @deprecated Use SparkBaseConfigAccessor.GetInverted() via
     * SparkMax.configAccessor or SparkFlex.configAccessor instead
     */
    [[deprecated(
        "Use SparkBaseConfigAccessor.GetInverted() via SparkMax.configAccessor "
        "or SparkFlex.configAccessor instead")]]
    bool GetInverted() const override;

    /**
     * Common interface for disabling a motor.
     */
    void Disable() override;

    /**
     * Common interface to stop the motor until Set is called again.
     */
    void StopMotor() override;

    /* ***** Extended Functions ****** */

    /**
     * Set the configuration for the SPARK.
     *
     * <p>If @c resetMode is ResetMode::kResetSafeParameters, this
     * method will reset safe writable parameters to their default values before
     * setting the given configuration. The following parameters will not be
     * reset by this action: CAN ID, Motor Type, Idle Mode, PWM Input Deadband,
     * and Duty Cycle Offset.
     *
     * <p>If @c persistMode is PersistMode::kPersistParameters, this
     * method will save all parameters to the SPARK's non-volatile memory after
     * setting the given configuration. This will allow parameters to persist
     * across power cycles.
     *
     * @param config The desired SPARK configuration
     * @param resetMode Whether to reset safe parameters before setting the
     * configuration
     * @param persistMode Whether to persist the parameters after setting the
     * configuration
     * @return REVLibError::kOk if successful
     * @deprecated Use {@link #Configure(SparkBaseConfig&, rev::ResetMode,
     * rev::PersistMode)} instead. This method will be removed in 2027.
     */
    [[deprecated(
        "Use Configure(SparkBaseConfig&, rev::ResetMode, rev::PersistMode) "
        "instead. This method will be removed in 2027.")]]
    virtual REVLibError Configure(SparkBaseConfig& config, ResetMode resetMode,
                                  PersistMode persistMode);

    /**
     * Set the configuration for the SPARK.
     *
     * <p>If @c resetMode is ResetMode::kResetSafeParameters, this
     * method will reset safe writable parameters to their default values before
     * setting the given configuration. The following parameters will not be
     * reset by this action: CAN ID, Motor Type, Idle Mode, PWM Input Deadband,
     * and Duty Cycle Offset.
     *
     * <p>If @c persistMode is PersistMode::kPersistParameters, this
     * method will save all parameters to the SPARK's non-volatile memory after
     * setting the given configuration. This will allow parameters to persist
     * across power cycles.
     *
     * @param config The desired SPARK configuration
     * @param resetMode Whether to reset safe parameters before setting the
     * configuration
     * @param persistMode Whether to persist the parameters after setting the
     * configuration
     * @return REVLibError::kOk if successful
     */
    virtual REVLibError Configure(SparkBaseConfig& config,
                                  rev::ResetMode resetMode,
                                  rev::PersistMode persistMode);

    /**
     * Set the configuration for the SPARK without waiting for a response.
     *
     * <p>If @c resetMode is ResetMode::kResetSafeParameters, this
     * method will reset safe writable parameters to their default values before
     * setting the given configuration. The following parameters will not be
     * reset by this action: CAN ID, Motor Type, Idle Mode, PWM Input Deadband,
     * and Duty Cycle Offset.
     *
     * <p>If @c persistMode is PersistMode::kPersistParameters, this
     * method will save all parameters to the SPARK's non-volatile memory after
     * setting the given configuration. This will allow parameters to persist
     * across power cycles.
     *
     * <p>NOTE: This method will immediately return REVLibError::kOk and the
     * action will be done in the background. Any errors that occur will be
     * reported to the driver station.
     *
     * @param config The desired SPARK configuration
     * @param resetMode Whether to reset safe parameters before setting the
     * configuration
     * @param persistMode Whether to persist the parameters after setting the
     * configuration
     * @return REVLibError::kOk
     * @see Configure()
     * @deprecated Use {@link #ConfigureAsync(SparkBaseConfig&, rev::ResetMode,
     * rev::PersistMode)} instead. This method will be removed in 2027.
     */
    [[deprecated(
        "Use ConfigureAsync(SparkBaseConfig&, rev::ResetMode, "
        "rev::PersistMode) instead. This method will be removed in 2027.")]]
    virtual REVLibError ConfigureAsync(SparkBaseConfig& config,
                                       ResetMode resetMode,
                                       PersistMode persistMode);

    /**
     * Set the configuration for the SPARK without waiting for a response.
     *
     * <p>If @c resetMode is ResetMode::kResetSafeParameters, this
     * method will reset safe writable parameters to their default values before
     * setting the given configuration. The following parameters will not be
     * reset by this action: CAN ID, Motor Type, Idle Mode, PWM Input Deadband,
     * and Duty Cycle Offset.
     *
     * <p>If @c persistMode is PersistMode::kPersistParameters, this
     * method will save all parameters to the SPARK's non-volatile memory after
     * setting the given configuration. This will allow parameters to persist
     * across power cycles.
     *
     * <p>NOTE: This method will immediately return REVLibError::kOk and the
     * action will be done in the background. Any errors that occur will be
     * reported to the driver station.
     *
     * @param config The desired SPARK configuration
     * @param resetMode Whether to reset safe parameters before setting the
     * configuration
     * @param persistMode Whether to persist the parameters after setting the
     * configuration
     * @return REVLibError::kOk
     * @see Configure()
     */
    virtual REVLibError ConfigureAsync(SparkBaseConfig& config,
                                       rev::ResetMode resetMode,
                                       rev::PersistMode persistMode);

    /**
     * Returns an object for interfacing with the encoder connected to the
     * encoder pins or front port of the SPARK MAX or the motor interface of the
     * SPARK Flex.
     */
    SparkRelativeEncoder& GetEncoder();

    /**
     * Returns an object for interfacing with a connected analog sensor.
     * By default, the mode is set to kAbsolute, thus treating the
     * sensor as an absolute sensor.
     */
    SparkAnalogSensor& GetAnalog();

    /**
     * Returns an object for interfacing with a connected absolute encoder.
     *
     * The default encoder type is assumed to be a duty cycle sensor.
     */
    virtual SparkAbsoluteEncoder& GetAbsoluteEncoder();

    /**
     * Returns an object for interfacing with the integrated Closed Loop
     * Controller.
     */
    SparkClosedLoopController& GetClosedLoopController();

    /**
     * Returns an object for interfacing with the forward limit switch connected
     * to the appropriate pins on the data port.
     *
     * This call will disable support for the alternate encoder.
     */
    virtual SparkLimitSwitch& GetForwardLimitSwitch();

    /**
     * Returns an object for interfacing with the reverse limit switch connected
     * to the appropriate pins on the data port.
     *
     * This call will disable support for the alternate encoder.
     */
    virtual SparkLimitSwitch& GetReverseLimitSwitch();

    /**
     * Returns an object for interfacing with the forward soft limit switch
     *
     */
    SparkSoftLimit& GetForwardSoftLimit();

    /**
     * Returns an object for interfacing with the reverse soft limit switch
     *
     */
    SparkSoftLimit& GetReverseSoftLimit();

    /**
     * Resume follower mode if the SPARK has a valid follower mode config.
     *
     * <p>NOTE: Follower mode will start automatically upon configuring follower
     * mode. If the SPARK experiences a power cycle and has follower mode
     * configured, follower mode will automatically restart. This method is only
     * useful after PauseFollowerMode() has been called.
     *
     * @return REVLibError::kOk if successful
     */
    rev::REVLibError ResumeFollowerMode();

    /**
     * Resume follower mode if the SPARK has a valid follower
     * mode config without waiting for a response.
     *
     * <p>NOTE: Follower mode will start automatically upon configuring follower
     * mode. If the SPARK experiences a power cycle and has follower mode
     * configured, follower mode will automatically restart. This method is only
     * useful after PauseFollowerMode() has been called.
     *
     * <p>NOTE: This method will immediately return REVLibError::kOk and the
     * action will be done in the background. Any errors that occur will be
     * reported to the driver station.
     *
     * @return REVLibError::kOk
     * @see ResumeFollowerMode()
     */
    rev::REVLibError ResumeFollowerModeAsync();

    /**
     * Pause follower mode.
     *
     * <p>NOTE: If the SPARK experiences a power cycle and has follower mode
     * configured, follower mode will automatically restart.
     *
     * @return REVLibError::kOk if successful
     */
    rev::REVLibError PauseFollowerMode();

    /**
     * Pause follower mode without waiting for a response.
     *
     * <p>NOTE: If the SPARK experiences a power cycle and has follower mode
     * configured, follower mode will automatically restart.
     *
     * <p>NOTE: This method will immediately return REVLibError::kOk and the
     * action will be done in the background. Any errors that occur will be
     * reported to the driver station.
     *
     * @return REVLibError::kOk
     * @see PauseFollowerMode()
     */
    rev::REVLibError PauseFollowerModeAsync();

    /**
     * Returns whether the controller is following another controller
     *
     * @return True if this device is following another controller false
     * otherwise
     */
    bool IsFollower();

    /**
     * Get whether the SPARK has one or more active faults.
     *
     * @return true if there is an active fault
     * @see GetFaults()
     */

    bool HasActiveFault();

    /**
     * Get whether the SPARK has one or more sticky faults.
     *
     * @return true if there is a sticky fault
     * @see GetStickyFaults()
     */
    bool HasStickyFault();

    /**
     * Get whether the SPARK has one or more active warnings.
     *
     * @return true if there is an active warning
     * @see GetWarnings()
     */
    bool HasActiveWarning();

    /**
     * Get whether the SPARK has one or more sticky warnings.
     *
     * @return true if there is a sticky warning
     * @see GetStickyWarnings()
     */
    bool HasStickyWarning();

    /**
     * Get the active faults that are currently present on the SPARK. Faults
     * are fatal errors that prevent the motor from running.
     *
     * @return A struct with each fault and their active value
     */
    Faults GetFaults();

    /**
     * Get the sticky faults that were present on the SPARK at one point
     * since the sticky faults were last cleared. Faults are fatal errors
     * that prevent the motor from running.
     *
     * <p>Sticky faults can be cleared with SparkBase::ClearFaults().
     *
     * @return A struct with each fault and their sticky value
     */
    Faults GetStickyFaults();

    /**
     * Get the active warnings that are currently present on the SPARK.
     * Warnings are non-fatal errors.
     *
     * @return A struct with each warning and their active value
     */
    Warnings GetWarnings();

    /**
     * Get the sticky warnings that were present on the SPARK at one point
     * since the sticky warnings were last cleared. Warnings are non-fatal
     * errors.
     *
     * <p>Sticky warnings can be cleared with SparkBase::clearFaults().
     *
     * @return A struct with each warning and their sticky value
     */
    Warnings GetStickyWarnings();

    /**
     * Returns the voltage fed into the motor controller.
     */
    double GetBusVoltage();

    /**
     * Simulation note: this value will not be updated during simulation
     * unless
     * {@link SparkSim#iterate} is called
     *
     * Returns motor controller's output duty cycle.
     */
    double GetAppliedOutput();

    /**
     * Returns motor controller's output current in Amps.
     */
    double GetOutputCurrent();

    /**
     * Returns the motor temperature in Celsius.
     */
    double GetMotorTemperature();

    /**
     * Clears all sticky faults.
     */
    REVLibError ClearFaults();

    /**
     * Sets the timeout duration for waiting for CAN responses from the device.
     *
     * @param milliseconds The timeout in milliseconds.
     */
    REVLibError SetCANTimeout(int milliseconds);

    /**
     * All device errors are tracked on a per thread basis for all
     * devices in that thread. This is meant to be called
     * immediately following another call that has the possibility
     * of throwing an error to validate if an  error has occurred.
     *
     * @return the last error that was generated.
     */
    REVLibError GetLastError();

protected:
    // Only used for Get() or Set() API
    double m_setpoint{0.0};

    /**
     * Create a new object to control a SPARK motor Controller
     *
     * @param deviceID The device ID.
     * @param type     The motor type connected to the controller. Brushless
     *                 motor wires must be connected to their matching
     *                 colors, and the hall sensor must be plugged in.
     *                 Brushed motors must be connected to the Red and Black
     *                 terminals only.
     * @param model    The model (kSparkMax or kSparkFlex) of the motor.
     */
    explicit SparkBase(int deviceID, MotorType type, SparkModel model);

    // Used by the HIL tester
    SparkRelativeEncoder GetEncoderEvenIfAlreadyCreated();

    /**
     * Get the current motor interface for the SPARK.
     * @return
     */
    uint8_t GetMotorInterface();

    /**
     * Get the Model of this SPARK Device. Useful for determining if this
     * is a Flex, MAX, or other device
     *
     * @return the model of this device
     */
    SparkBase::SparkModel GetSparkModel();

protected:
    SparkRelativeEncoder m_RelativeEncoder;
    std::atomic<bool> m_relativeEncoderCreated{false};

    SparkAnalogSensor m_AnalogSensor;
    std::atomic<bool> m_analogSensorCreated{false};

    SparkAbsoluteEncoder m_AbsoluteEncoder;
    std::atomic<bool> m_absoluteEncoderCreated{false};

    SparkClosedLoopController m_ClosedLoopController;
    std::atomic<bool> m_closedLoopControllerCreated{false};

    SparkLimitSwitch m_ForwardLimitSwitch;
    std::atomic<bool> m_forwardLimitSwitchCreated{false};

    SparkLimitSwitch m_ReverseLimitSwitch;
    std::atomic<bool> m_reverseLimitSwitchCreated{false};

    SparkSoftLimit m_ForwardSoftLimit;
    std::atomic<bool> m_forwardSoftLimitCreated{false};

    SparkSoftLimit m_ReverseSoftLimit;
    std::atomic<bool> m_reverseSoftLimitCreated{false};
};

}  // namespace rev::spark

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
