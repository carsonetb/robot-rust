use crate::prelude::*;

pub struct TimeInterpolatableBuffer<T> {
    history_size: Time,
    past_snapshots: Vec<(Time, T)>,
    interpolating_func: Box<dyn Fn(&T, &T, f64) -> T>,
}

impl<T: Clone> TimeInterpolatableBuffer<T> {
    pub fn new(history_size: Time, func: impl Fn(&T, &T, f64) -> T + 'static) -> Self {
        Self {
            history_size,
            past_snapshots: Vec::new(),
            interpolating_func: Box::new(func),
        }
    }

    pub fn add_sample(&mut self, time: Time, sample: T) {
        if self.past_snapshots.len() == 0 || time > self.past_snapshots.last().unwrap().0 {
            self.past_snapshots.push((time, sample));
        } else {
            let first_after = self.past_snapshots.partition_point(|(t, _)| *t <= time);
            // let (first_after_time, first_after_t) =
            //     self.past_snapshots.get(first_after_index).unwrap();

            if first_after == 0 {
                self.past_snapshots.insert(first_after, (time, sample));
            } else if first_after == 1 || self.past_snapshots[first_after - 1].0 < time {
                self.past_snapshots.insert(first_after, (time, sample));
            } else {
                self.past_snapshots[first_after - 1].1 = sample;
            }
        }

        while time - self.past_snapshots[0].0 > self.history_size {
            self.past_snapshots.remove(0);
        }
    }

    pub fn clear(&mut self) {
        self.past_snapshots.clear();
    }

    pub fn sample(&self, time: Time) -> Option<T> {
        if self.past_snapshots.is_empty() {
            return None;
        }

        let (first_time, first_t) = self.past_snapshots.first().unwrap();
        let (last_time, last_t) = self.past_snapshots.last().unwrap();

        if time <= *first_time {
            return Some(first_t.clone());
        }
        if time > *last_time {
            return Some(last_t.clone());
        }
        if self.past_snapshots.len() < 2 {
            return Some(self.past_snapshots[0].1.clone());
        }

        let upper_bound = self.past_snapshots.partition_point(|(t, _)| *t < time);
        let (upper_bound_time, upper_bound_t) = self.past_snapshots.get(upper_bound).unwrap();

        if upper_bound == 0 {
            return Some(self.past_snapshots.get(upper_bound).unwrap().1.clone());
        }

        let lower_bound = upper_bound - 1;
        let (lower_bound_time, lower_bound_t) = self.past_snapshots.get(lower_bound).unwrap();

        let t = (time - *lower_bound_time) / (*upper_bound_time - *lower_bound_time);

        Some(self.interpolating_func.as_ref()(
            lower_bound_t,
            upper_bound_t,
            t.value,
        ))
    }

    pub fn is_empty(&self) -> bool {
        self.past_snapshots.is_empty()
    }

    pub fn get_buffer(&self) -> &Vec<(Time, T)> {
        &self.past_snapshots
    }
}
