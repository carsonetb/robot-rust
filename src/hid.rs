use autocxx::WithinUniquePtr;
use autocxx::c_int;

use crate::ffi;
use crate::prelude::*;

/// An XBox controller connected to the driver station. `*_trigger` functions
/// can be used with systems if this is present as a resource.
pub struct XboxController {
    cont: cxx::UniquePtr<ffi::XboxController>,
    #[cfg(simulation)]
    gilrs: gilrs::Gilrs,
    #[cfg(simulation)]
    port: i32,
}

#[derive(Debug, Default, Clone, Copy)]
#[cfg(simulation)]
struct XboxSimInputs {
    pub axes: [f32; 6],
    pub buttons: u32,
    pub pov: i16,
}

impl XboxController {
    pub fn new(port: i32) -> Self {
        Self {
            cont: ffi::XboxController::new(c_int(port)).within_unique_ptr(),
            #[cfg(simulation)]
            gilrs: gilrs::Gilrs::new().unwrap(),
            #[cfg(simulation)]
            port,
        }
    }

    #[cfg(simulation)]
    fn poll(&mut self) -> XboxSimInputs {
        use gilrs::{Axis, Button};

        while let Some(_) = self.gilrs.next_event() {}

        let Some((_, gamepad)) = self
            .gilrs
            .gamepads()
            .filter(|(_, g)| g.is_connected())
            .nth(self.port as usize)
        else {
            warn!("No controller {} is plugged in to simulate!", self.port);
            return XboxSimInputs {
                pov: -1,
                ..Default::default()
            };
        };

        let axes = [
            gamepad.value(Axis::LeftStickX),
            -gamepad.value(Axis::LeftStickY),
            gamepad.value(Axis::LeftZ).clamp(0.0, 1.0),
            gamepad.value(Axis::RightZ).clamp(0.0, 1.0),
            gamepad.value(Axis::RightStickX),
            -gamepad.value(Axis::RightStickY),
        ];

        let button_map = [
            Button::South,
            Button::East,
            Button::West,
            Button::North,
            Button::LeftTrigger,
            Button::RightTrigger,
            Button::Select,
            Button::Start,
            Button::LeftThumb,
            Button::RightThumb,
        ];

        let mut buttons: u32 = 0;
        for (i, &btn) in button_map.iter().enumerate() {
            if gamepad.is_pressed(btn) {
                buttons |= 1 << i;
            }
        }

        let up = gamepad.is_pressed(Button::DPadUp);
        let down = gamepad.is_pressed(Button::DPadDown);
        let left = gamepad.is_pressed(Button::DPadLeft);
        let right = gamepad.is_pressed(Button::DPadRight);

        // magic
        let pov = match (up, right, down, left) {
            (true, false, false, false) => 0,
            (true, true, false, false) => 45,
            (false, true, false, false) => 90,
            (false, true, true, false) => 135,
            (false, false, true, false) => 180,
            (false, false, true, true) => 225,
            (false, false, false, true) => 270,
            (true, false, false, true) => 315,
            _ => -1,
        };

        XboxSimInputs { axes, buttons, pov }
    }

    pub fn simulate(&mut self) {
        #[cfg(simulation)]
        {
            let input = self.poll();

            unsafe {
                let mut axes: ffi::sim::HAL_JoystickAxes = std::mem::zeroed();
                axes.count = 6;
                axes.axes[..6].copy_from_slice(&input.axes);
                ffi::sim::HALSIM_SetJoystickAxes(self.port, &axes);

                let mut buttons: ffi::sim::HAL_JoystickButtons = std::mem::zeroed();
                buttons.count = 10;
                buttons.buttons = input.buttons;
                ffi::sim::HALSIM_SetJoystickButtons(self.port, &buttons);

                let mut povs: ffi::sim::HAL_JoystickPOVs = std::mem::zeroed();
                povs.count = 1;
                povs.povs[0] = input.pov;
                ffi::sim::HALSIM_SetJoystickPOVs(self.port, &povs);

                ffi::sim::HALSIM_SetJoystickIsXbox(self.port, 1);
                ffi::sim::HALSIM_SetJoystickType(self.port, 1);
                ffi::sim::HALSIM_NotifyDriverStationNewData();
                ffi::sim::HAL_RefreshDSData();
                ffi::DriverStation::RefreshData();
            }
        }
    }

    pub fn left_x(&self) -> f64 {
        self.cont.GetLeftX()
    }

    pub fn right_x(&self) -> f64 {
        self.cont.GetRightX()
    }

    pub fn left_y(&self) -> f64 {
        self.cont.GetLeftY()
    }

    pub fn right_y(&self) -> f64 {
        self.cont.GetRightY()
    }

    /// WARNING: Not a trigger, the physical trigger on the controller.
    pub fn left_trigger(&self) -> f64 {
        self.cont.GetLeftTriggerAxis()
    }

    /// WARNING: Not a trigger, the physical trigger on the controller.
    pub fn right_trigger(&self) -> f64 {
        self.cont.GetRightTriggerAxis()
    }

    pub fn a(&self) -> bool {
        self.cont.GetAButton()
    }

    pub fn a_pressed(&mut self) -> bool {
        self.cont.pin_mut().GetAButtonPressed()
    }

    pub fn a_released(&mut self) -> bool {
        self.cont.pin_mut().GetAButtonReleased()
    }

    pub fn a_trigger(controller: Resource<Self>) -> bool {
        controller.a()
    }

    pub fn b(&self) -> bool {
        self.cont.GetBButton()
    }

    pub fn b_pressed(&mut self) -> bool {
        self.cont.pin_mut().GetBButtonPressed()
    }

    pub fn b_released(&mut self) -> bool {
        self.cont.pin_mut().GetBButtonReleased()
    }

    pub fn b_trigger(controller: Resource<Self>) -> bool {
        controller.b()
    }

    pub fn x(&self) -> bool {
        self.cont.GetXButton()
    }

    pub fn x_pressed(&mut self) -> bool {
        self.cont.pin_mut().GetXButtonPressed()
    }

    pub fn x_released(&mut self) -> bool {
        self.cont.pin_mut().GetXButtonReleased()
    }

    pub fn x_trigger(controller: Resource<Self>) -> bool {
        controller.x()
    }

    pub fn y(&self) -> bool {
        self.cont.GetYButton()
    }

    pub fn y_pressed(&mut self) -> bool {
        self.cont.pin_mut().GetYButtonPressed()
    }

    pub fn y_released(&mut self) -> bool {
        self.cont.pin_mut().GetYButtonReleased()
    }

    pub fn y_trigger(controller: Resource<Self>) -> bool {
        controller.y()
    }

    pub fn left_bumper(&self) -> bool {
        self.cont.GetLeftBumperButton()
    }

    pub fn left_bumper_pressed(&mut self) -> bool {
        self.cont.pin_mut().GetLeftBumperButtonPressed()
    }

    pub fn left_bumper_released(&mut self) -> bool {
        self.cont.pin_mut().GetLeftBumperButtonReleased()
    }

    pub fn left_bumper_trigger(controller: Resource<Self>) -> bool {
        controller.left_bumper()
    }

    pub fn right_bumper(&self) -> bool {
        self.cont.GetRightBumperButton()
    }

    pub fn right_bumper_pressed(&mut self) -> bool {
        self.cont.pin_mut().GetRightBumperButtonPressed()
    }

    pub fn right_bumper_released(&mut self) -> bool {
        self.cont.pin_mut().GetRightBumperButtonReleased()
    }

    pub fn right_bumper_trigger(controller: Resource<Self>) -> bool {
        controller.right_bumper()
    }

    pub fn back(&self) -> bool {
        self.cont.GetBackButton()
    }

    pub fn back_pressed(&mut self) -> bool {
        self.cont.pin_mut().GetBackButtonPressed()
    }

    pub fn back_released(&mut self) -> bool {
        self.cont.pin_mut().GetBackButtonReleased()
    }

    pub fn back_trigger(controller: Resource<Self>) -> bool {
        controller.back()
    }

    pub fn start(&self) -> bool {
        self.cont.GetStartButton()
    }

    pub fn start_pressed(&mut self) -> bool {
        self.cont.pin_mut().GetStartButtonPressed()
    }

    pub fn start_released(&mut self) -> bool {
        self.cont.pin_mut().GetStartButtonReleased()
    }

    pub fn start_trigger(controller: Resource<Self>) -> bool {
        controller.start()
    }

    pub fn left_stick(&self) -> bool {
        self.cont.GetLeftStickButton()
    }

    pub fn left_stick_pressed(&mut self) -> bool {
        self.cont.pin_mut().GetLeftStickButtonPressed()
    }

    pub fn left_stick_released(&mut self) -> bool {
        self.cont.pin_mut().GetLeftStickButtonReleased()
    }

    pub fn left_stick_trigger(controller: Resource<Self>) -> bool {
        controller.left_stick()
    }

    pub fn right_stick(&self) -> bool {
        self.cont.GetRightStickButton()
    }

    pub fn right_stick_pressed(&mut self) -> bool {
        self.cont.pin_mut().GetRightStickButtonPressed()
    }

    pub fn right_stick_released(&mut self) -> bool {
        self.cont.pin_mut().GetRightStickButtonReleased()
    }

    pub fn right_stick_trigger(controller: Resource<Self>) -> bool {
        controller.right_stick()
    }
}
