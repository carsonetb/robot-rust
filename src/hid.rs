use autocxx::WithinUniquePtr;
use autocxx::c_int;

use crate::ffi;
use crate::prelude::*;

/// An XBox controller connected to the driver station. `*_trigger` functions
/// can be used with systems if this is present as a resource.
pub struct XboxController {
    cont: cxx::UniquePtr<ffi::XboxController>,
}

impl XboxController {
    pub fn new(port: i32) -> Self {
        Self {
            cont: ffi::XboxController::new(c_int(port)).within_unique_ptr(),
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
