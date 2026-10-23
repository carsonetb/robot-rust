use rand_distr::Distribution;

use crate::math::prelude::*;
use crate::prelude::*;

fn make_white_noise_vector<const N: usize>(std_devs: [f64; N]) -> nalgebra::SVector<f64, N> {
    let mut rng = rand::rng();

    nalgebra::SVector::from_fn(|i, _| {
        let std_dev = std_devs[i];
        if std_dev == 0.0 {
            0.0
        } else {
            let distr = rand_distr::Normal::new(0.0, std_dev)
                .expect("Std dev must be finite and non-negative");
            distr.sample(&mut rng)
        }
    })
}

fn desaturate_input_vector<const N: usize>(
    u: nalgebra::SVector<f64, N>,
    max_magnitude: f64,
) -> nalgebra::SVector<f64, N> {
    let max_value = u.amax();

    if max_value > max_magnitude {
        u * max_magnitude / max_value
    } else {
        u
    }
}

#[derive(Debug, Clone, Deref, DerefMut)]
pub struct LinearSystemSim<const STATES: usize, const INPUTS: usize, const OUTPUTS: usize> {
    pub x: nalgebra::SVector<f64, STATES>,
    pub u: nalgebra::SVector<f64, INPUTS>,
    pub y: nalgebra::SVector<f64, OUTPUTS>,
    #[deref]
    #[deref_mut]
    pub plant: LinearSystem<STATES, INPUTS, OUTPUTS>,
    pub measurement_std_devs: [f64; OUTPUTS],
}

impl<const STATES: usize, const INPUTS: usize, const OUTPUTS: usize>
    LinearSystemSim<STATES, INPUTS, OUTPUTS>
{
    pub fn new(system: LinearSystem<STATES, INPUTS, OUTPUTS>) -> Self {
        Self {
            x: nalgebra::SVector::zeros(),
            u: nalgebra::SVector::zeros(),
            y: nalgebra::SVector::zeros(),
            plant: system,
            measurement_std_devs: std::array::repeat(0.0),
        }
    }

    pub fn with_std_devs(mut self, measurement_std_devs: [f64; OUTPUTS]) -> Self {
        self.measurement_std_devs = measurement_std_devs;
        self
    }

    pub fn update(&mut self, dt: Time) {
        self.x = self.update_x(self.x, self.u, dt);
        self.y = self.plant.calculate_y(self.x, self.u);
        self.y = make_white_noise_vector(self.measurement_std_devs)
    }

    pub fn set_state(&mut self, state: nalgebra::SVector<f64, STATES>) {
        self.x = state;
        self.y = self.plant.calculate_y(self.x, self.u);
    }

    fn update_x(
        &self,
        current_x_hat: nalgebra::SVector<f64, STATES>,
        u: nalgebra::SVector<f64, INPUTS>,
        dt: Time,
    ) -> nalgebra::SVector<f64, STATES> {
        self.plant.calculate_x(current_x_hat, u, dt)
    }

    pub fn get_output(&self, row: usize) -> f64 {
        self.y[row]
    }

    pub fn set_input(&mut self, row: usize, value: f64) {
        self.u[(row, 0)] = value;
    }

    pub fn get_input(&self, row: usize) -> f64 {
        self.u[row]
    }

    pub(crate) fn clamp_input(&mut self, max_input: f64) {
        self.u = desaturate_input_vector(self.u, max_input)
    }
}
