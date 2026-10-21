use crate::prelude::*;

pub struct AngularTrapezoidState {
    pub position: Angle,
    pub velocity: AngularVelocity,
}

impl AngularTrapezoidState {
    pub fn new(position: Angle, velocity: AngularVelocity) -> Self {
        Self { position, velocity }
    }

    pub fn from(state: TrapezoidState) -> Self {
        Self::new(
            state.position.radians(),
            state.velocity.radians_per_second(),
        )
    }

    pub fn to(&self) -> TrapezoidState {
        TrapezoidState::new(self.position.value, self.velocity.value)
    }
}

pub struct LinearTrapezoidState {
    pub position: Length,
    pub velocity: Velocity,
}

impl LinearTrapezoidState {
    pub fn new(position: Length, velocity: Velocity) -> Self {
        Self { position, velocity }
    }

    pub fn from(state: TrapezoidState) -> Self {
        Self::new(state.position.meters(), state.velocity.meters_per_second())
    }

    pub fn to(&self) -> TrapezoidState {
        TrapezoidState::new(self.position.value, self.velocity.value)
    }
}

#[derive(Debug, Default, Clone, Copy)]
pub struct TrapezoidState {
    pub position: f64,
    pub velocity: f64,
}

impl TrapezoidState {
    pub fn new(position: f64, velocity: f64) -> Self {
        Self { position, velocity }
    }
}

#[derive(Debug, Deref, DerefMut, Clone)]
pub struct AngularTrapezoidProfile(TrapezoidProfile);

impl AngularTrapezoidProfile {
    pub fn new(max_velocity: AngularVelocity, max_acceleration: AngularAcceleration) -> Self {
        Self(TrapezoidProfile::new(
            max_velocity.value,
            max_acceleration.value,
        ))
    }

    pub fn calculate(
        &mut self,
        timestep: Time,
        current: AngularTrapezoidState,
        goal: AngularTrapezoidState,
    ) -> AngularTrapezoidState {
        AngularTrapezoidState::from(self.0.calculate(timestep, current.to(), goal.to()))
    }
}

#[derive(Debug, Deref, DerefMut, Clone)]
pub struct LinearTrapezoidProfile(TrapezoidProfile);

impl LinearTrapezoidProfile {
    pub fn new(max_velocity: Velocity, max_acceleration: Acceleration) -> Self {
        Self(TrapezoidProfile::new(
            max_velocity.value,
            max_acceleration.value,
        ))
    }

    pub fn calculate(
        &mut self,
        timestep: Time,
        current: LinearTrapezoidState,
        goal: LinearTrapezoidState,
    ) -> LinearTrapezoidState {
        LinearTrapezoidState::from(self.0.calculate(timestep, current.to(), goal.to()))
    }
}

#[derive(Debug, Clone)]
pub struct TrapezoidProfile {
    pub max_velocity: f64,
    pub max_acceleration: f64,
    direction: i32,
}

impl TrapezoidProfile {
    pub fn new(max_velocity: f64, max_acceleration: f64) -> Self {
        Self {
            max_velocity,
            max_acceleration,
            direction: 1,
        }
    }

    fn should_flip_acceleration(initial: TrapezoidState, goal: TrapezoidState) -> bool {
        initial.position > goal.position
    }

    fn direct(&self, mut of: TrapezoidState) -> TrapezoidState {
        of.position *= self.direction as f64;
        of.velocity *= self.direction as f64;
        of
    }

    pub fn calculate(
        &mut self,
        timestep: Time,
        current: TrapezoidState,
        goal: TrapezoidState,
    ) -> TrapezoidState {
        self.direction = if Self::should_flip_acceleration(current, goal) {
            -1
        } else {
            1
        };
        let mut current = self.direct(current);
        let goal = self.direct(goal);

        if current.velocity.abs() > self.max_velocity {
            current.velocity = self.max_velocity.copysign(current.velocity);
        }

        let cutoff_begin = current.velocity / self.max_acceleration;
        let cutoff_dist_begin = cutoff_begin.powi(2) * self.max_acceleration / 2.0;

        let cutoff_end = goal.velocity / self.max_acceleration;
        let cutoff_dist_end = cutoff_end.powi(2) * self.max_acceleration / 2.0;

        let full_trapezoid_dist =
            cutoff_dist_begin + (goal.position - current.position) + cutoff_dist_end;
        let mut acceleration_time = self.max_velocity / self.max_acceleration;

        let mut full_speed_dist =
            full_trapezoid_dist - acceleration_time.powi(2) * self.max_acceleration;

        if full_speed_dist < 0.0 {
            acceleration_time = (full_trapezoid_dist / self.max_acceleration).sqrt();
            full_speed_dist = 0.0;
        }

        let end_accel = acceleration_time - cutoff_begin;
        let end_full_speed = end_accel + full_speed_dist / self.max_velocity;
        let end_decel = end_full_speed + acceleration_time - cutoff_end;

        let mut result = current;

        let t = timestep.get::<second>();
        if t < end_accel {
            result.velocity += t * self.max_acceleration;
            result.position += (current.velocity + t * self.max_acceleration / 2.0) * t;
        } else if t < end_full_speed {
            result.velocity = self.max_velocity;
            result.position += (current.velocity + end_accel * self.max_acceleration / 2.0)
                * end_accel
                + self.max_velocity * (t - end_accel);
        } else if t <= end_decel {
            result.velocity = goal.velocity + (end_decel - t) * self.max_acceleration;
            let time_left = end_decel - t;
            result.position = goal.position
                - (goal.velocity + time_left * self.max_acceleration / 2.0) * time_left;
        } else {
            result = goal;
        }

        self.direct(result)
    }
}
