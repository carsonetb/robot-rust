use std::collections::HashMap;

use crate::ffi;

/// Send a selection of options to the dashboard.
pub struct SendableChooser<T> {
    handle: *mut ffi::ChooserHandle,
    options: HashMap<String, T>,
    default: Option<String>,
}

impl<T> SendableChooser<T> {
    pub fn new() -> Self {
        Self {
            handle: ffi::chooser_create(),
            options: HashMap::new(),
            default: None,
        }
    }

    pub fn add_option(&mut self, name: &str, value: T) {
        unsafe {
            ffi::chooser_add_option(self.handle, name);
        }

        self.options.insert(name.to_string(), value);
    }

    pub fn set_default(&mut self, name: &str, value: T) {
        self.add_option(name, value);
        self.default = Some(name.to_string());
    }

    pub fn publish(&self, name: &str) {
        unsafe {
            ffi::chooser_publish(self.handle, name);
        }
    }

    pub fn get_selected(&self) -> Option<&T> {
        let selected = unsafe { ffi::chooser_get_selected(self.handle) }.to_string();
        self.options.get(&selected)
    }
}

impl<T> Drop for SendableChooser<T> {
    fn drop(&mut self) {
        unsafe {
            ffi::chooser_destroy(self.handle);
        }
    }
}
