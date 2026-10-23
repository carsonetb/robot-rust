use crate::prelude::*;

#[derive(Debug, Clone)]
pub struct DCMotor {
    pub kt: MotorTorqueConstant,
    pub kv: MotorVelocityConstant,
    pub gearing: f64,
    pub nominal_voltage: Voltage,
    pub stall_torque: Torque,
    pub stall_current: Current,
    pub free_current: Current,
    pub free_speed: AngularVelocity,
    pub resistance: Ohms,
}

impl DCMotor {
    pub fn new(
        nominal_voltage: Voltage,
        stall_torque: Torque,
        stall_current: Current,
        free_current: Current,
        free_speed: AngularVelocity,
        gearing: f64,
    ) -> Self {
        let resistance = nominal_voltage / stall_current;
        Self {
            kt: stall_torque / stall_current,
            kv: free_speed / (nominal_voltage - resistance * free_current),
            gearing,
            nominal_voltage,
            stall_torque,
            stall_current,
            free_current,
            free_speed,
            resistance,
        }
    }

    pub fn neo(gearing: f64) -> Self {
        Self::new(
            12.0.volts(),
            2.6.newton_meters(),
            105.0.amps(),
            1.8.amps(),
            5676.0.rpm(),
            gearing,
        )
    }

    pub fn neo_550(gearing: f64) -> Self {
        Self::new(
            12.0.volts(),
            0.97.newton_meters(),
            100.0.amps(),
            1.4.amps(),
            11000.0.rpm(),
            gearing,
        )
    }

    pub fn neo_vortex(gearing: f64) -> Self {
        Self::new(
            12.0.volts(),
            3.6.newton_meters(),
            211.0.amps(),
            3.615.amps(),
            6784.0.rpm(),
            gearing,
        )
    }

    pub fn falcon_500(gearing: f64) -> Self {
        Self::new(
            12.0.volts(),
            4.69.newton_meters(),
            257.0.amps(),
            1.5.amps(),
            6380.0.rpm(),
            gearing,
        )
    }

    pub fn falcon_500_foc(gearing: f64) -> Self {
        Self::new(
            12.0.volts(),
            5.84.newton_meters(),
            304.0.amps(),
            1.5.amps(),
            6080.0.rpm(),
            gearing,
        )
    }

    pub fn kraken_x60(gearing: f64) -> Self {
        Self::new(
            12.0.volts(),
            7.09.newton_meters(),
            366.0.amps(),
            2.0.amps(),
            6000.0.rpm(),
            gearing,
        )
    }

    pub fn kraken_x60_foc(gearing: f64) -> Self {
        Self::new(
            12.0.volts(),
            9.37.newton_meters(),
            483.0.amps(),
            2.0.amps(),
            5800.0.rpm(),
            gearing,
        )
    }

    pub fn kraken_x44(gearing: f64) -> Self {
        Self::new(
            12.0.volts(),
            4.11.newton_meters(),
            279.0.amps(),
            2.0.amps(),
            7758.0.rpm(),
            gearing,
        )
    }

    pub fn kraken_x44_foc(gearing: f64) -> Self {
        Self::new(
            12.0.volts(),
            5.01.newton_meters(),
            329.0.amps(),
            2.0.amps(),
            7368.0.rpm(),
            gearing,
        )
    }

    pub fn current(&self, speed: AngularVelocity, input_voltage: Voltage) -> Current {
        -1.0 / self.kv / self.resistance * speed + 1.0 / self.resistance * input_voltage
    }

    pub fn torque_to_current(&self, torque: Torque) -> Current {
        torque / self.kt
    }

    pub fn torque(&self, current: Current) -> Torque {
        let energy: Energy = current * self.kt;
        energy.value.newton_meters()
    }

    pub fn voltage(&self, torque: Torque, speed: AngularVelocity) -> Voltage {
        1.0 / self.kv * speed + 1.0 / self.kt * self.resistance * torque
    }

    pub fn speed(&self, torque: Torque, input_voltage: Voltage) -> AngularVelocity {
        let torque = torque.value.joules();
        let frequency =
            input_voltage * self.kv - 1.0 / self.kt * torque * self.resistance * self.kv;
        frequency.value.radians_per_second()
    }
}
