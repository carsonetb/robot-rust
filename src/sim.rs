use crate::prelude::*;

pub mod gui;
pub mod io;
pub mod motor;
pub mod prelude;
pub mod runtime;
pub mod system;

pub struct DriverStationSim {
    pub mode: Mode,
    auto_timer: Timer,
}

impl DriverStationSim {
    pub fn new() -> Self {
        info!("Simulated driver station initializing ...");
        Self {
            mode: Mode::None,
            auto_timer: Timer::new(20.0.seconds()),
        }
    }

    pub fn set_auto_length(&mut self, length: Time) {
        assert!(
            self.mode != Mode::Autonomous,
            "Cannot change auto length in autonomous period."
        );
        self.auto_timer.set_duration(length);
    }

    pub(crate) fn process(&mut self) {
        self.auto_timer.update();
        if self.mode == Mode::Autonomous && self.auto_timer.just_ended() {
            self.auto_timer.reset();
            self.disable();
        }
    }

    pub fn enable(&mut self) {
        self.teleop();
    }

    pub fn teleop(&mut self) {
        info!("Driver station simulator enter teleop.");
        self.mode = Mode::Teleop;
    }

    pub fn autonomous(&mut self) {
        info!("Driver station simulator enter autonomous.");
        self.mode = Mode::Autonomous;
        self.auto_timer.start();
    }

    pub fn disable(&mut self) {
        info!("Driver station simulator disable from {}.", self.mode);
        self.mode = Mode::Disabled;
    }
}
