use crate::prelude::*;

#[derive(Debug, Clone)]
pub struct TrapezoidProfile {
    pub max_velocity: f64,
    pub max_acceleration: f64,

    current: TrapezoidState,
    direction: i32,

    end_accel: f64,
    end_full_speed: f64,
    end_decel: f64,
}

#[derive(Debug, Default, Clone, Copy)]
pub struct TrapezoidState {
    position: f64,
    velocity: f64,
}

impl TrapezoidProfile {
    pub fn new(max_velocity: f64, max_acceleration: f64) -> Self {
        Self {
            max_velocity,
            max_acceleration,

            current: TrapezoidState::default(),
            direction: 1,

            end_accel: 0.0,
            end_full_speed: 0.0,
            end_decel: 0.0,
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
        t: Time,
        current: TrapezoidState,
        goal: TrapezoidState,
    ) -> TrapezoidState {
        self.direction = if Self::should_flip_acceleration(current, goal) {
            -1
        } else {
            1
        };
        self.current = self.direct(current);
        let goal = self.direct(goal);

        if self.current.velocity.abs() > self.max_velocity {
            self.current.velocity = self.max_velocity.copysign(self.current.velocity);
        }

        let cutoff_begin = self.current.velocity / self.max_acceleration;
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

        self.end_accel = acceleration_time - cutoff_begin;
        self.end_full_speed = self.end_accel + full_speed_dist / self.max_velocity;
        self.end_decel = self.end_full_speed + acceleration_time - cutoff_end;

        let mut result = self.current;

        let t = t.get::<second>();
        if t < self.end_accel {
            result.velocity += t * self.max_acceleration;
            result.position += (self.current.velocity + t * self.max_acceleration / 2.0) * t;
        } else if t < self.end_full_speed {
            result.velocity = self.max_velocity;
            result.position += (self.current.velocity
                + self.end_accel * self.max_acceleration / 2.0)
                * self.end_accel
                + self.max_velocity * (t - self.end_accel);
        } else if t <= self.end_decel {
            result.velocity = goal.velocity + (self.end_decel - t) * self.max_acceleration;
            let time_left = self.end_decel - t;
            result.position = goal.position
                - (goal.velocity + time_left * self.max_acceleration / 2.0) * time_left;
        } else {
            result = goal;
        }

        self.direct(result)
    }
}
