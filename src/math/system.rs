use crate::{math::plant::DCMotor, prelude::*};
use nalgebra::{DMatrix, SMatrix, SVector};

pub fn discretize_ab<const STATES: usize, const INPUTS: usize>(
    cont_a: SMatrix<f64, STATES, STATES>,
    cont_b: SMatrix<f64, STATES, INPUTS>,
    dt: Time,
) -> (SMatrix<f64, STATES, STATES>, SMatrix<f64, STATES, INPUTS>) {
    let mut m = DMatrix::zeros(STATES + INPUTS, STATES + INPUTS);
    m.view_mut((0, 0), (STATES, STATES)).copy_from(&cont_a);
    m.view_mut((0, STATES), (STATES, INPUTS)).copy_from(&cont_b);
    m.view_mut((STATES, 0), (INPUTS, STATES + INPUTS)).fill(0.0);

    let phi = (m * dt.value).exp();

    (
        phi.fixed_view::<STATES, STATES>(0, 0).clone_owned(),
        phi.fixed_view::<STATES, INPUTS>(0, STATES).clone_owned(),
    )
}

#[derive(Debug, Clone, PartialEq)]
pub struct LinearSystem<const STATES: usize, const INPUTS: usize, const OUTPUTS: usize> {
    pub a: SMatrix<f64, STATES, STATES>,
    pub b: SMatrix<f64, STATES, INPUTS>,
    pub c: SMatrix<f64, OUTPUTS, STATES>,
    pub d: SMatrix<f64, OUTPUTS, INPUTS>,
}

impl<const STATES: usize, const INPUTS: usize, const OUTPUTS: usize>
    LinearSystem<STATES, INPUTS, OUTPUTS>
{
    /// Constructs a descrete plant with the given continuous system
    /// coefficients.
    ///
    /// ## Panics
    ///
    /// If any matrix element isn't finite.
    ///
    /// ## Parameters
    ///
    /// * a: System matrix.
    /// * b: Input matrix.
    /// * c: Output matrix.
    /// * d: Feedthrough matrix.
    pub fn new(
        a: SMatrix<f64, STATES, STATES>,
        b: SMatrix<f64, STATES, INPUTS>,
        c: SMatrix<f64, OUTPUTS, STATES>,
        d: SMatrix<f64, OUTPUTS, INPUTS>,
    ) -> Self {
        assert!(
            a.iter().all(|n| n.is_finite()),
            "Elements of A aren't finite, this is usually due to model implementation errors."
        );
        assert!(
            b.iter().all(|n| n.is_finite()),
            "Elements of A aren't finite, this is usually due to model implementation errors."
        );
        assert!(
            c.iter().all(|n| n.is_finite()),
            "Elements of A aren't finite, this is usually due to model implementation errors."
        );
        assert!(
            d.iter().all(|n| n.is_finite()),
            "Elements of A aren't finite, this is usually due to model implementation errors."
        );

        Self { a, b, c, d }
    }

    /**
     * Create a state-space model of a DC motor system from its kV
     * (volts/(unit/sec)) and kA (volts/(unit/sec²)). These constants can be
     * found using SysId. the states of the system are [angular position,
     * angular velocity]ᵀ, inputs are [voltage], and outputs are
     * [angular position, angular velocity]ᵀ.
     *
     * The parameters provided by the user are from this feedforward model:
     *
     * u = K_v v + K_a a
     *
     * ## Parameters
     *
     * * kV: The velocity gain, in volts/(unit/sec).
     * * kA: The acceleration gain, in volts/(unit/sec²).
     *
     * ## Panics
     *
     * If kV < 0 or Ka <= 0
     */
    pub fn dc_motor_system(kv: f64, ka: f64) -> Self {
        assert!(kv >= 0.0, "Kv must be greater than or equal to zero.");
        assert!(ka > 0.0, "Ka must be greater than zero.");

        let a = SMatrix::from_column_slice(&[0.0, 1.0, 0.0, -kv / ka]);
        let b = SMatrix::from_column_slice(&[0.0, 1.0 / ka]);
        let c = SMatrix::from_column_slice(&[1.0, 0.0, 0.0, 1.0]);
        let d = SMatrix::from_column_slice(&[0.0, 0.0]);

        Self::new(a, b, c, d)
    }

    pub fn from_dc_motor(motor: DCMotor, moi: MomentOfInertia, gearing: f64) -> Self {
        assert!(
            moi > 0.0.kilogram_square_meters(),
            "MOI (J) must be greater than zero."
        );
        assert!(gearing > 0.0, "Gearing must be greater than zero.");

        let a = SMatrix::from_column_slice(&[
            0.0,
            1.0,
            0.0,
            (-gearing.powi(2) * motor.kt / (motor.kv * motor.resistance)).value,
        ]);
        let b = SMatrix::from_column_slice(&[
            0.0,
            (gearing * motor.kt / (motor.resistance * moi)).value,
        ]);
        let c = SMatrix::from_column_slice(&[1.0, 0.0, 0.0, 1.0]);
        let d = SMatrix::from_column_slice(&[0.0, 0.0]);

        Self::new(a, b, c, d)
    }

    pub fn calculate_x(
        &self,
        x: SVector<f64, STATES>,
        clamped_u: SVector<f64, INPUTS>,
        dt: Time,
    ) -> SVector<f64, STATES> {
        let (disc_a, disc_b) = discretize_ab(self.a, self.b, dt);
        disc_a * x + disc_b * clamped_u
    }

    pub fn calculate_y(
        &self,
        x: SVector<f64, STATES>,
        clamped_u: SVector<f64, INPUTS>,
    ) -> SVector<f64, OUTPUTS> {
        self.c * x + self.d * clamped_u
    }
}
