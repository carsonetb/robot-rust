use std::collections::HashMap;
use std::sync::{LazyLock, Mutex, MutexGuard};

use crate::prelude::*;

static SIMULATOR_INPUTS: LazyLock<Mutex<SimulatorInputs>> =
    LazyLock::new(|| Mutex::new(SimulatorInputs::new()));
static SIMULATOR_OUTPUTS: LazyLock<Mutex<SimulatorOutputs>> =
    LazyLock::new(|| Mutex::new(SimulatorOutputs::new()));

/// Inputs to the simulator. Do not create this type manually.
#[derive(Clone)]
pub struct SimulatorInputs {
    /// Time since last update.
    pub delta: Time,
    /// All motor inputs, with bus and ID as key.
    pub motors: HashMap<(&'static str, i32), MotorInputs>,
    /// All gyro inputs, with bus and ID as key.
    pub gyros: HashMap<(&'static str, i32), GyroInputs>,
}

impl SimulatorInputs {
    /// Create new inputs to the simulator. There is not reason to use this
    /// method.
    pub fn new() -> Self {
        Self {
            delta: 20.0.milliseconds(),
            motors: HashMap::new(),
            gyros: HashMap::new(),
        }
    }

    /// Get the static inputs to the simulator.
    pub fn get() -> MutexGuard<'static, Self> {
        SIMULATOR_INPUTS.lock().unwrap()
    }

    /// Get a motor from the database, one will be created using the default
    /// [`MotorInputs`] if it doesn't exist.
    pub fn motor(&mut self, bus: &'static str, id: i32) -> &mut MotorInputs {
        self.motors.entry((bus, id)).or_default()
    }

    /// Get a motor from the database, one will be created using the default
    /// [`GyroInputs`] if it doesn't exist.
    pub fn gyro(&mut self, bus: &'static str, id: i32) -> &mut GyroInputs {
        self.gyros.entry((bus, id)).or_default()
    }
}

/// Outputs of the simulator. Do not create this type manually.
#[derive(Clone)]
pub struct SimulatorOutputs {
    pub battery_voltage: Voltage,
    pub motors: HashMap<(&'static str, i32), MotorOutputs>,
    pub gyros: HashMap<(&'static str, i32), GyroOutputs>,
}

impl SimulatorOutputs {
    /// Create new outputs of the simulator. There is not reason to use this
    /// method.
    pub fn new() -> Self {
        Self {
            battery_voltage: 12.0.volts(),
            motors: HashMap::new(),
            gyros: HashMap::new(),
        }
    }

    /// Get the static outputs of the simulator.
    pub fn get() -> MutexGuard<'static, Self> {
        SIMULATOR_OUTPUTS.lock().unwrap()
    }

    /// Get a motor from the database, one will be created using the default
    /// [`MotorInputs`] if it doesn't exist.
    pub fn motor(&mut self, bus: &'static str, id: i32) -> &mut MotorOutputs {
        self.motors.entry((bus, id)).or_default()
    }

    /// Get a motor from the database, one will be created using the default
    /// [`GyroInputs`] if it doesn't exist.
    pub fn gyro(&mut self, bus: &'static str, id: i32) -> &mut GyroOutputs {
        self.gyros.entry((bus, id)).or_default()
    }
}

/// A motor type, for simulation purposes.
#[derive(Debug, Clone, Copy, Default)]
pub enum MotorType {
    #[default]
    None,
    Neo,
    Neo550,
    NeoVortex,
    Falcon500,
    Falcon500FOC,
    KrakenX60,
    KrakenX60FOC,
    KrakenX44,
    KrakenX44FOC,
}

#[derive(Debug, Clone, Default)]
pub struct MotorInputs {
    pub motor_type: MotorType,
    /// Gear ratio of the motor to the mechanism.
    pub gearing: f64,
    /// Moment of inertia of the mechanism.
    pub moi: MomentOfInertia,
    /// Voltage applied to the motor by the controller.
    pub applied_voltage: Voltage,
    /// Torque current applied to the motor by the motor controller.
    pub torque_current: Current,
}

#[derive(Debug, Clone)]
pub struct MotorOutputs {
    /// Voltage supplied to the motor by the battery (12.0).
    pub supply_voltage: Voltage,
    /// The position of the motor, that would be measured by an encoder. This is
    /// the position of the rotor, not the position of the mechanism.
    pub position: Angle,
    /// The velocity of the motor, that would be measured by an encoder. This is
    /// the velocity of the rotor, not the velocity. of the mechanism.
    pub velocity: AngularVelocity,
}

impl Default for MotorOutputs {
    fn default() -> Self {
        Self {
            supply_voltage: 12.0.volts(),
            position: 0.0.degrees(),
            velocity: 0.0.degrees_per_second(),
        }
    }
}

#[derive(Debug, Clone, Copy, Default)]
pub enum GyroType {
    #[default]
    None,
    Pigeon2,
}

#[derive(Debug, Clone, Default)]
pub struct GyroInputs {
    pub gyro_type: GyroType,
}

#[derive(Debug, Clone)]
pub struct GyroOutputs {
    pub supply_voltage: Voltage,
    pub xvel: AngularVelocity,
    pub yvel: AngularVelocity,
    pub zvel: AngularVelocity,
}

impl Default for GyroOutputs {
    fn default() -> Self {
        Self {
            supply_voltage: 12.0.volts(),
            xvel: 0.0.degrees_per_second(),
            yvel: 0.0.degrees_per_second(),
            zvel: 0.0.degrees_per_second(),
        }
    }
}
