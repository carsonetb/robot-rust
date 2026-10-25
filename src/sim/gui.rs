use std::sync::{Arc, Mutex};
use std::time::Duration;

use crate::prelude::*;

#[derive(Default)]
pub struct GUICommunicator {
    pub selected: Mode,
    pub enable: bool,
    pub disable: bool,

    pub enabled: bool,
    pub mode: Mode,
}

#[cfg(not(target_arch = "arm"))]
pub fn spawn_simgui(comms: Arc<Mutex<GUICommunicator>>) {
    use eframe::egui;

    std::thread::spawn(move || {
        let native_options = eframe::NativeOptions {
            viewport: egui::ViewportBuilder::default()
                .with_inner_size([360.0, 420.0])
                .with_title("Simulation GUI"),
            event_loop_builder: Some(Box::new(|builder| {
                #[cfg(target_os = "linux")]
                {
                    {
                        use winit::platform::wayland::EventLoopBuilderExtWayland;
                        builder.with_any_thread(true);
                    }
                    {
                        use winit::platform::x11::EventLoopBuilderExtX11;
                        builder.with_any_thread(true);
                    }
                }
                #[cfg(target_os = "windows")]
                {
                    use winit::platform::windows::EventLoopBuilderExtWindows;
                    builder.with_any_thread(true);
                }
            })),
            ..Default::default()
        };

        let _ = eframe::run_ui_native("Simulation GUI", native_options, move |ctx, _frame| {
            let mut comms = comms.lock().unwrap();

            egui::CentralPanel::default_margins().show(ctx, |ui| {
                ui.horizontal(|ui| {
                    ui.selectable_value(&mut comms.selected, Mode::Autonomous, "Autonomous");
                    ui.selectable_value(&mut comms.selected, Mode::Teleop, "Teleop");
                    ui.selectable_value(&mut comms.selected, Mode::Test, "Test");
                });

                let enabled = comms.mode == Mode::Disabled;
                let text = if enabled { "Enabled" } else { "Enable" };
                if !comms.enable {
                    comms.enable = ui.button(text).clicked();
                }
                let text = if enabled {
                    "Tap To Disable"
                } else {
                    "Disabled"
                };
                if !comms.disable {
                    comms.disable = ui.button(text).clicked();
                }
            });

            ctx.request_repaint_after(Duration::from_millis(50));
        });
    });
}
