use crate::math::plant::DCMotor;
use crate::math::system::LinearSystem;
use crate::prelude::*;
use crate::sim::system::LinearSystemSim;

/// https://github.wpilib.org/allwpilib/docs/release/cpp/classfrc_1_1sim_1_1_d_c_motor_sim.html
#[derive(Debug, Clone)]
pub struct DCMotorSim {
    pub plant: LinearSystemSim<2, 1, 2>,
    pub gearbox: DCMotor,
    pub gearing: f64,
    pub moi: MomentOfInertia,
}

impl DCMotorSim {
    pub fn new(plant: LinearSystem<2, 1, 2>, gearbox: DCMotor) -> Self {
        let gearing = -gearbox.kv.value * plant.a[(1, 1)] / plant.b[(1, 0)];
        let moi = (gearing * gearbox.kt.value / (gearbox.resistance.value * plant.b[(1, 0)]))
            .moment_of_inertia();
        Self {
            plant: LinearSystemSim::new(plant),
            gearbox,
            gearing,
            moi,
        }
    }

    pub fn neo(kv: f64, ka: f64) -> Self {
        Self::new(LinearSystem::dc_motor_system(kv, ka), DCMotor::neo())
    }

    pub fn neo_550(kv: f64, ka: f64) -> Self {
        Self::new(LinearSystem::dc_motor_system(kv, ka), DCMotor::neo_550())
    }

    pub fn neo_vortex(kv: f64, ka: f64) -> Self {
        Self::new(LinearSystem::dc_motor_system(kv, ka), DCMotor::neo_vortex())
    }

    pub fn falcon_500(kv: f64, ka: f64) -> Self {
        Self::new(LinearSystem::dc_motor_system(kv, ka), DCMotor::falcon_500())
    }

    pub fn falcon_500_foc(kv: f64, ka: f64) -> Self {
        Self::new(
            LinearSystem::dc_motor_system(kv, ka),
            DCMotor::falcon_500_foc(),
        )
    }

    pub fn kraken_x60(kv: f64, ka: f64) -> Self {
        Self::new(LinearSystem::dc_motor_system(kv, ka), DCMotor::kraken_x60())
    }

    pub fn kraken_x60_foc(kv: f64, ka: f64) -> Self {
        Self::new(
            LinearSystem::dc_motor_system(kv, ka),
            DCMotor::kraken_x60_foc(),
        )
    }

    pub fn kraken_x44(kv: f64, ka: f64) -> Self {
        Self::new(LinearSystem::dc_motor_system(kv, ka), DCMotor::kraken_x44())
    }

    pub fn kraken_x44_foc(kv: f64, ka: f64) -> Self {
        Self::new(
            LinearSystem::dc_motor_system(kv, ka),
            DCMotor::kraken_x44_foc(),
        )
    }

    pub fn with_std_devs(mut self, measurement_std_devs: [f64; 2]) -> Self {
        self.plant.measurement_std_devs = measurement_std_devs;
        self
    }

    pub fn set_state(&mut self, position: Angle, velocity: AngularVelocity) {
        self.plant
            .set_state(nalgebra::vector![position.value, velocity.value]);
    }

    pub fn set_angle(&mut self, position: Angle) {
        self.set_state(position, self.plant.x[1].radians_per_second());
    }

    pub fn set_velocity(&mut self, velocity: AngularVelocity) {
        self.set_state(self.plant.x[1].radians(), velocity);
    }

    pub fn get_position(&self) -> Angle {
        self.plant.get_output(0).radians()
    }

    pub fn get_velocity(&self) -> AngularVelocity {
        self.plant.get_output(1).radians_per_second()
    }

    pub fn get_acceleration(&self) -> AngularAcceleration {
        (self.plant.a * self.plant.x + self.plant.b * self.plant.u)[(1, 0)]
            .radians_per_second_squared()
    }

    pub fn get_torque(&self) -> Torque {
        (self.get_acceleration().value * self.moi.value).newton_meters()
    }

    pub fn get_current_draw(&self) -> Current {
        self.gearbox.current(
            self.plant.x[1].radians_per_second() * self.gearing,
            self.plant.u[0].volts(),
        ) * self.plant.u[0].signum()
    }

    pub fn get_input_voltage(&self) -> Voltage {
        self.plant.get_input(0).volts()
    }

    pub fn set_input_voltage(&mut self, voltage: Voltage, battery_voltage: Voltage) {
        self.plant.u = nalgebra::vector![voltage.value];
        self.plant.clamp_input(battery_voltage.value);
    }

    pub fn update(&mut self, dt: Time) {
        self.plant.update(dt);
    }
}
