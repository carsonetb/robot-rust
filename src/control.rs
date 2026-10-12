#[derive(Debug, Clone, Copy)]
pub struct PIDGains {
    pub p: f64,
    pub i: f64,
    pub d: f64,
}

impl PIDGains {
    pub const fn new(p: f64, i: f64, d: f64) -> Self {
        Self { p, i, d }
    }
}
