/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include <functional>
#include <limits>
#include <units/time.h>

namespace ctre {
namespace phoenix6 {
namespace swerve {

/**
 * \brief Phoenix-centric PID controller taken from WPI's frc#PIDController class.
 *
 * This class differs from the WPI implementation by using explicit timestamps for
 * integral/derivative calculations. Ideally, these timestamps come from the StatusSignal.
 */
class PhoenixPIDController {
public:
    /**
     * Allocates a PhoenixPIDController with the given constants for Kp, Ki, and Kd.
     *
     * \param Kp The proportional coefficient. Must be >= 0.
     * \param Ki The integral coefficient. Must be >= 0.
     * \param Kd The derivative coefficient. Must be >= 0.
     */
    PhoenixPIDController(double Kp, double Ki, double Kd);

    /**
     * Sets the PID Controller gain parameters.
     *
     * Sets the proportional, integral, and differential coefficients.
     *
     * \param Kp The proportional coefficient. Must be >= 0.
     * \param Ki The integral coefficient. Must be >= 0.
     * \param Kd The differential coefficient. Must be >= 0.
     */
    void SetPID(double Kp, double Ki, double Kd);

    /**
     * Sets the proportional coefficient of the PID controller gain.
     *
     * \param Kp The proportional coefficient. Must be >= 0.
     */
    void SetP(double Kp);

    /**
     * Sets the integral coefficient of the PID controller gain.
     *
     * \param Ki The integral coefficient. Must be >= 0.
     */
    void SetI(double Ki);

    /**
     * Sets the differential coefficient of the PID controller gain.
     *
     * \param Kd The differential coefficient. Must be >= 0.
     */
    void SetD(double Kd);

    /**
     * Sets the IZone range. When the absolute value of the position error is
     * greater than IZone, the total accumulated error will reset to zero,
     * disabling integral gain until the absolute value of the position error is
     * less than IZone. This is used to prevent integral windup. Must be
     * non-negative. Passing a value of zero will effectively disable integral
     * gain. Passing a value of infinity disables IZone functionality.
     *
     * \param iZone Maximum magnitude of error to allow integral control. Must be
     *   >= 0.
     */
    void SetIZone(double iZone);

    /**
     * Gets the proportional coefficient.
     *
     * \returns proportional coefficient
     */
    double GetP() const;

    /**
     * Gets the integral coefficient.
     *
     * \returns integral coefficient
     */
    double GetI() const;

    /**
     * Gets the differential coefficient.
     *
     * \returns differential coefficient
     */
    double GetD() const;

    /**
     * Get the IZone range.
     *
     * \returns Maximum magnitude of error to allow integral control.
     */
    double GetIZone() const;

    /**
     * Gets the position tolerance of this controller.
     *
     * \returns The position tolerance of the controller.
     */
    double GetPositionTolerance() const;

    /**
     * Gets the velocity tolerance of this controller.
     *
     * \returns The velocity tolerance of the controller.
     */
    double GetVelocityTolerance() const;

    /**
     * Returns the current setpoint of the PIDController.
     *
     * \returns The current setpoint.
     */
    double GetSetpoint() const;

    /**
     * Returns true if the error is within the tolerance of the setpoint.
     *
     * This will return false until at least one input value has been computed.
     */
    bool AtSetpoint() const;

    /**
     * Enables continuous input.
     *
     * Rather then using the max and min input range as constraints, it considers
     * them to be the same point and automatically calculates the shortest route
     * to the setpoint.
     *
     * \param minimumInput The minimum value expected from the input.
     * \param maximumInput The maximum value expected from the input.
     */
    void EnableContinuousInput(double minimumInput, double maximumInput);

    /**
     * Disables continuous input.
     */
    void DisableContinuousInput();

    /**
     * Returns true if continuous input is enabled.
     */
    bool IsContinuousInputEnabled() const;

    /**
     * Sets the minimum and maximum values for the integrator.
     *
     * When the cap is reached, the integrator value is added to the controller
     * output rather than the integrator value times the integral gain.
     *
     * \param minimumIntegral The minimum value of the integrator.
     * \param maximumIntegral The maximum value of the integrator.
     */
    void SetIntegratorRange(double minimumIntegral, double maximumIntegral);

    /**
     * Sets the error which is considered tolerable for use with AtSetpoint().
     *
     * \param positionTolerance Position error which is tolerable.
     * \param velocityTolerance Velocity error which is tolerable.
     */
    void SetTolerance(
            double positionTolerance,
            double velocityTolerance = std::numeric_limits<double>::infinity());

    /**
     * Returns the difference between the setpoint and the measurement.
     */
    double GetPositionError() const;

    /**
     * Returns the velocity error.
     */
    double GetVelocityError() const;

    /**
     * Returns the next output of the PID controller.
     *
     * \param measurement The current measurement of the process variable.
     * \param setpoint The new setpoint of the controller.
     * \param currentTimestamp The current timestamp to use for calculating integral/derivative error
     */
    double Calculate(double measurement, double setpoint, units::second_t currentTimestamp);

    /**
     * Returns the last applied output from this PID controller.
     */
    double GetLastAppliedOutput() const;

    /**
     * Reset the previous error, the integral term, and disable the controller.
     */
    void Reset();

private:
    // Factor for "proportional" control
    double m_Kp;

    // Factor for "integral" control
    double m_Ki;

    // Factor for "derivative" control
    double m_Kd;

    // The error range where "integral" control applies
    double m_iZone = std::numeric_limits<double>::infinity();

    double m_maximumIntegral = 1.0;

    double m_minimumIntegral = -1.0;

    double m_maximumInput = 0;

    double m_minimumInput = 0;

    // Do the endpoints wrap around? eg. Absolute encoder
    bool m_continuous = false;

    // The error at the time of the most recent call to Calculate()
    double m_positionError = 0;
    double m_velocityError = 0;

    // The error at the time of the second-most-recent call to Calculate() (used
    // to compute velocity)
    double m_prevError = 0;

    // The sum of the errors for use in the integral calc
    double m_totalError = 0;

    // The error that is considered at setpoint.
    double m_positionTolerance = 0.05;
    double m_velocityTolerance = std::numeric_limits<double>::infinity();

    double m_setpoint = 0;
    double m_measurement = 0;

    bool m_haveSetpoint = false;
    bool m_haveMeasurement = false;

    double m_lastAppliedOutput;

    // The last timestamp acquired when performing a calculation
    units::second_t m_lastTimestamp;
};

}
}
}
