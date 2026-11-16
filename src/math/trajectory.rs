use crate::prelude::*;

#[derive(Debug, Default, Clone, Copy)]
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

#[derive(Debug, Default, Clone, Copy)]
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

#[derive(Debug, Clone)]
pub struct FeedforwardOut {
    pub pose: Pose2D,
    pub velocity: RobotVelocity2D,
    pub acceleration: RobotAcceleration2D,
}

impl FeedforwardOut {
    pub fn new(pose: Pose2D, velocity: RobotVelocity2D, acceleration: RobotAcceleration2D) -> Self {
        Self {
            pose,
            velocity,
            acceleration,
        }
    }
}

// pub struct BezierCurve<const N: usize> {
//     pub points: [Vec2; N],
//     pub precision: f64,
// }
//
// impl<const N: usize> BezierCurve<N> {
//     pub fn compute(&self, t: f64) -> Vec2 {
//         let mut lerps = self.points;
//         for i in N..=1 {
//             for j in 0..(i - 1) {
//                 lerps[j] = lerps[j] + (lerps[j + 1] - lerps[j]) * t;
//             }
//         }
//         lerps[0]
//     }
// }

/// A cubic bezier curve, based off https://www.desmos.com/calculator/ce52fa8a60
///
/// Coming in the future is an N-degree bezier curve once I can figure out the
/// derivative.
#[derive(Debug, Clone)]
pub struct BezierCurve {
    /// Start point
    pub p0: Vec2,
    /// Start control point
    pub p1: Vec2,
    /// End control point
    pub p2: Vec2,
    /// End point
    pub p3: Vec2,
}

impl BezierCurve {
    pub fn new(start: Vec2, control_start: Vec2, end: Vec2, control_end: Vec2) -> Self {
        Self {
            p0: start,
            p1: control_start,
            p2: control_end,
            p3: end,
        }
    }

    /// Compute the bezier curve function at t, where t is in 0..1.
    pub fn compute(&self, t: f64) -> Vec2 {
        let f1 = self.p0 + (self.p1 - self.p0) * t;
        let f2 = self.p1 + (self.p2 - self.p1) * t;
        let f3 = self.p2 + (self.p3 - self.p2) * t;

        let g1 = f1 + (f2 - f1) * t;
        let g2 = f2 + (f3 - f1) * t;

        g1 + (g2 - g1) * t
    }

    /// Compute the derivative of the bezier curve function at t, where t is in
    /// 0..1. The derivative is the velocity of the bezier curve at t.
    pub fn derivative(&self, t: f64) -> Vec2 {
        (self.p1 - self.p0) * 3.0 * (1.0 - t).powi(2)
            + (self.p2 - self.p1) * 6.0 * (1.0 - t) * t
            + (self.p3 - self.p2) * 3.0 * t.powi(2)
    }

    /// Compute the length of the bezier curve with a precision. A precision of
    /// 0.01 will result in 100 samples.
    ///
    /// WARNING: This function is somewhat costly to run, at O(1/precision)
    /// time. Consider caching the length if you aren't actively changing
    /// the parameters of the curve.
    pub fn length(&self, precision: f64) -> Length {
        let limit = (1.0 / precision) as usize;
        let samples = (0..=limit)
            .map(|i| self.compute(i as f64 * precision))
            .collect::<Vec<_>>();

        let mut sum = 0.0.meters();
        for i in 1..(limit + 1) {
            sum += (samples[i] - samples[i - 1]).length();
        }
        sum
    }
}

#[derive(Debug, Clone, Copy)]
pub struct BezierTarget {
    pub pose: Pose2D,
    pub velocity: Velocity,
    pub direction: Vec2,
}

impl BezierTarget {
    pub fn new(pose: Pose2D, velocity: Velocity) -> Self {
        Self {
            pose,
            velocity,
            direction: Vec2::new(0.0.meters(), 0.0.meters()),
        }
    }

    pub fn with_direction(mut self, direction: Vec2) -> Self {
        self.direction = direction;
        self
    }
}

#[derive(Debug, Clone)]
pub struct BezierCurveFeedforward {
    curve: BezierCurve,
    length: Length,
    target: BezierTarget,
    linear_profile: LinearTrapezoidProfile,
    angular_profile: AngularTrapezoidProfile,
    linear_current: LinearTrapezoidState,
    angular_current: AngularTrapezoidState,
    p: f64,
    last_goal: f64,
}

impl BezierCurveFeedforward {
    pub fn new(
        start: BezierTarget,
        target: BezierTarget,
        linear_profile: LinearTrapezoidProfile,
        angular_profile: AngularTrapezoidProfile,
    ) -> Self {
        let curve = BezierCurve::new(
            start.pose.pos,
            start.pose.pos + start.direction * start.velocity.value,
            target.pose.pos,
            target.pose.pos - target.direction * target.velocity.value,
        );
        let length = curve.length(0.005);
        Self {
            curve,
            length,
            target,
            linear_profile,
            angular_profile,
            linear_current: LinearTrapezoidState::new(0.0.meters(), start.velocity),
            angular_current: AngularTrapezoidState::new(
                start.pose.rotation.value,
                0.0.radians_per_second(),
            ),
            p: 0.0,
            last_goal: 0.0,
        }
    }

    pub fn calculate(&mut self, dt: Time) -> FeedforwardOut {
        let goal = self.linear_profile.calculate(
            dt,
            self.linear_current,
            LinearTrapezoidState::new(self.length, self.target.velocity),
        );
        self.linear_current = goal;

        let deriv = self.curve.derivative(self.p);
        self.p += (goal.position.value - self.last_goal) / deriv.length().value;
        self.last_goal = goal.position.value;

        let angular_goal = self.angular_profile.calculate(
            dt,
            self.angular_current,
            AngularTrapezoidState::new(self.target.pose.rotation.value, 0.0.radians_per_second()),
        );

        FeedforwardOut::new(
            Pose2D::new(
                self.curve.compute(self.p),
                Rotation2D::new(angular_goal.position),
            ),
            RobotVelocity2D::new(
                (deriv.normalized() * goal.velocity.value).to_velocity2(),
                angular_goal.velocity,
            ),
            RobotAcceleration2D::new(
                Acceleration2::new(
                    0.0.meters_per_second_squared(),
                    0.0.meters_per_second_squared(),
                ),
                0.0.radians_per_second_squared(),
            ),
        )
    }
}
