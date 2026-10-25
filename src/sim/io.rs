use std::collections::HashMap;
use std::sync::{LazyLock, Mutex, MutexGuard};

use crate::prelude::*;

static SIMULATOR_INPUTS: LazyLock<Mutex<SimulatorInputs>> =
    LazyLock::new(|| Mutex::new(SimulatorInputs::new()));
static SIMULATOR_OUTPUTS: LazyLock<Mutex<SimulatorOutputs>> =
    LazyLock::new(|| Mutex::new(SimulatorOutputs::new()));

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

#[derive(Clone, Default)]
pub struct MotorInputs {
    pub motor_type: MotorType,
    pub gearing: f64,
    pub moi: MomentOfInertia,
    pub applied_voltage: Voltage,
    pub torque_current: Current,
}

#[derive(Debug, Clone)]
pub struct MotorOutputs {
    pub supply_voltage: Voltage,
    pub position: Angle,
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

#[derive(Clone)]
pub struct SimulatorInputs {
    pub delta: Time,
    pub motors: HashMap<(&'static str, i32), MotorInputs>,
}

impl SimulatorInputs {
    pub fn new() -> Self {
        Self {
            delta: 20.0.milliseconds(),
            motors: HashMap::new(),
        }
    }

    pub fn get() -> MutexGuard<'static, Self> {
        SIMULATOR_INPUTS.lock().unwrap()
    }

    pub fn motor(&mut self, bus: &'static str, id: i32) -> &mut MotorInputs {
        self.motors.entry((bus, id)).or_default()
    }
}

#[derive(Clone)]
pub struct SimulatorOutputs {
    pub battery_voltage: Voltage,
    pub motors: HashMap<(&'static str, i32), MotorOutputs>,
}

impl SimulatorOutputs {
    pub fn new() -> Self {
        Self {
            battery_voltage: 12.0.volts(),
            motors: HashMap::new(),
        }
    }

    pub fn get() -> MutexGuard<'static, Self> {
        SIMULATOR_OUTPUTS.lock().unwrap()
    }

    pub fn motor(&mut self, bus: &'static str, id: i32) -> &mut MotorOutputs {
        self.motors.entry((bus, id)).or_default()
    }
}
