use std::time::Instant;

use crate::prelude::*;

#[inline]
fn signum_zero(val: f64) -> f64 {
    if val > 0.0 {
        1.0
    } else if val < 0.0 {
        -1.0
    } else {
        0.0
    }
}

/// PIDGains used in a [`PIDController`] or motor params.
#[derive(Debug, Clone, Copy)]
pub struct PIDGains {
    /// Proportional component, also written as Kp.
    pub p: f64,
    /// Integral component, also written as Ki.
    pub i: f64,
    /// Derivative component, also written as Kd.
    pub d: f64,
}

impl PIDGains {
    /// Create a new gains, with Kp, Ki, and Kd.
    pub const fn new(p: f64, i: f64, d: f64) -> Self {
        Self { p, i, d }
    }
}

/// A simple feedback controller. After setting the parameters, every update
/// you should call `with_current` and `with_setpoint` to update those parameters,
/// if necessary.
///
/// Want information on how these work and how to tune them effectively? Read
/// chapter 2 of https://file.tavsys.net/control/controls-engineering-in-frc.pdf.
///
/// This type isn't unit-ed because a PID controller can run on many different
/// types of units.
#[derive(Debug, Clone)]
pub struct PIDController {
    /// The gains used by the controller.
    pub gains: PIDGains,
    /// The current physical value of the variable being controlled.
    pub current: f64,
    /// The target value of the variable being controlled.
    pub setpoint: f64,

    last_time: Instant,
    last_error: f64,
    error_accum: f64,
}

impl PIDController {
    /// Create a new controller from Kp, Ki, and Kd components.
    pub fn new(p: f64, i: f64, d: f64) -> Self {
        Self::from_gains(PIDGains::new(p, i, d))
    }

    /// Create a new controller from gains.
    pub fn from_gains(gains: PIDGains) -> Self {
        Self {
            gains,
            current: 0.0,
            setpoint: 0.0,

            last_time: Instant::now(),
            last_error: 0.0,
            error_accum: 0.0,
        }
    }

    /// Set the current physical value of the variable being controlled.
    pub fn with_current(&mut self, current: f64) -> &mut Self {
        self.current = current;
        self
    }

    /// Set the target value of the variable being controlled.
    pub fn with_setpoint(&mut self, setpoint: f64) -> &mut Self {
        self.setpoint = setpoint;
        self
    }

    /// Get the time since the past call to `process`, with microsecond
    /// precision.
    pub fn dt(&self) -> Time {
        (self.last_time.elapsed().as_micros() as f64).microseconds()
    }

    /// Get the error between the setpoint and the current value.
    pub fn error(&self) -> f64 {
        self.setpoint - self.current
    }

    /// Get the proportional component of the controller.
    pub fn proportional(&self) -> f64 {
        self.gains.p * self.error()
    }

    /// Get the derivative component of the controller.
    pub fn derivative(&mut self) -> f64 {
        let de = self.error() - self.last_error;
        let out = self.gains.d * (de / self.dt().get::<second>());

        self.last_time = Instant::now();
        self.last_error = self.error();

        out
    }

    /// Get the integral component of the controller.
    pub fn integral(&mut self) -> f64 {
        let out = self.gains.i * self.error_accum;
        self.error_accum += self.error() * self.dt().get::<second>();
        out
    }

    /// Process the controller and output the value that should be applied to
    /// the variable. The value is something that will create a force, most
    /// commonly voltage.
    pub fn process(&mut self) -> f64 {
        self.proportional() + self.integral() + self.derivative()
    }
}

/// Whereas a PID is a feedback controller (it accounts for the physical
/// mechanism's position), this type doesn't take feedback and so is called
/// a feedforward. It's values are the coefficients that correspond to the
/// voltage needed to set the motor to a velocity and the voltage needed to
/// set the motor to an acceleration, and some other values.
pub struct SimpleMotorFeedforward {
    /// Ks, the static friction coefficient, which is the voltage required to
    /// get the motor turning as slow as possible.
    pub s: f64,
    /// Ks, the velocity coefficient, which converts velocity to voltage.
    pub v: f64,
    /// Ka, the acceleration coefficient, which converts acceleration to
    /// voltage.
    pub a: f64,
    /// The timestep of the feedforward, typically 20ms.
    pub dt: Time,
    exponential: f64,
}

impl SimpleMotorFeedforward {
    /// Create a new feedforward with Ks, Kv, and Ka. The timestep will be set
    /// to 20ms.
    pub fn new(s: f64, v: f64, a: f64) -> Self {
        let dt = 20.0.milliseconds();
        let mut out = Self {
            s,
            v,
            a,
            dt,
            exponential: 0.0,
        };
        out.calculate_exponential();
        out
    }

    /// Set the timestep of the feedforward to a custom value.
    pub fn with_dt(mut self, dt: Time) -> Self {
        self.dt = dt;
        self.calculate_exponential();
        self
    }

    /// Calculate the voltage required to meet a certain velocity and
    /// acceleration.
    pub fn calculate(&self, velocity: f64, acceleration: f64) -> Voltage {
        (self.s * signum_zero(velocity) + self.v * velocity + self.a * acceleration).volts()
    }

    /// Calculate the voltage required to get from the current setpoint to the
    /// next setpoint.
    pub fn setpoints(&self, current: f64, next: f64) -> Voltage {
        if self.a < 1e-9 {
            self.s * signum_zero(next) + self.v * next
        } else {
            self.s * signum_zero(current)
                + (self.v * (next - self.exponential * current)) / (1.0 - self.exponential)
        }
        .volts()
    }

    pub fn max_achievable_velocity(&self, max_voltage: Voltage, acceleration: f64) -> f64 {
        (max_voltage.get::<volt>() - self.s - self.a * acceleration) / self.v
    }

    pub fn min_achievable_velocity(&self, max_voltage: Voltage, acceleration: f64) -> f64 {
        (-max_voltage.get::<volt>() + self.s - self.a * acceleration) / self.v
    }

    pub fn max_achievable_acceleration(&self, max_voltage: Voltage, velocity: f64) -> f64 {
        (max_voltage.get::<volt>() - self.s * signum_zero(velocity) - self.v * velocity) / self.a
    }

    pub fn min_achievable_acceleration(&self, max_voltage: Voltage, velocity: f64) -> f64 {
        self.max_achievable_acceleration(-max_voltage, velocity)
    }

    fn calculate_exponential(&mut self) {
        if self.a < 1e-9 {
            self.a = 0.0;
        } else {
            self.exponential = (-(self.v / self.a) * self.dt.get::<second>()).exp();
        }
    }
}
