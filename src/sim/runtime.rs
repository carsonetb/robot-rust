use std::collections::HashMap;

use super::prelude::*;
use crate::ecs::SimulatorPeriodic;
use crate::math::plant::DCMotor;
use crate::math::system::LinearSystem;
use crate::prelude::*;

/// A simulation runtime creates systems that run on [`SimulatorPeriodic`], and
/// convert [`SimulatorInputs`] into [`SimulatorOutputs`]. Both of these are
/// global statics, not resources.
pub trait SimRuntime: Sized {
    const NAME: &'static str;

    /// Init function called by state.
    fn init(&mut self, state: &mut State<Self>);
}

/// A basic runtime that creates instances of [DCMotorSim] to simulate motors.
#[derive(Default, Debug, Clone, Copy)]
pub struct BasicRuntime;

impl SimRuntime for BasicRuntime {
    const NAME: &'static str = "Basic Runtime";

    fn init(&mut self, state: &mut State<Self>) {
        state.insert_resource(MotorPhysics::default());
        state.add_systems(SimulatorPeriodic, motor_update);
    }
}

#[derive(Default, Deref, DerefMut, Debug, Clone)]
struct MotorPhysics(HashMap<(&'static str, i32), DCMotorSim>);

fn motor_update(mut physics: ResourceMut<MotorPhysics>) {
    let inputs = &SimulatorInputs::get().motors;
    let mut outputs = SimulatorOutputs::get();

    for ((bus, id), input) in inputs {
        let output = outputs.motor(bus, *id);

        let physics = physics.entry((bus, *id)).or_insert_with(|| {
            DCMotorSim::new(
                LinearSystem::from_dc_motor(
                    DCMotor::from_motor_type(input.motor_type),
                    input.moi,
                    input.gearing,
                ),
                DCMotor::from_motor_type(input.motor_type),
            )
        });
        physics.set_input_voltage(input.applied_voltage, 12.0.volts());
        physics.update(20.0.milliseconds());

        output.supply_voltage = 12.0.volts();
        output.position = input.gearing * physics.get_position();
        output.velocity = input.gearing * physics.get_velocity();
    }
}
