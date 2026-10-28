use std::collections::HashMap;

use crate::ffi;
use crate::logging::nt::*;
use crate::logging::{now, str_to_wpi};
use crate::prelude::*;

/// A logging system that logs to the log file and to (optionally)
/// NetworkTables.
pub struct Logger {
    datalog: *mut ffi::WPI_DataLog,
    nt: NetworkTablesInstance,
    // TODO: Looking up in hashmap is inefficient
    entries: HashMap<String, i32>,
    nt_publishers: HashMap<String, NetworkTablesPublisher>,
    networktables: bool,
}

impl Logger {
    /// Create a new logger that logs to `filename`. If `networktables` is true,
    /// the logger will publish values to NetworkTables, which can be viewed in
    /// programs like AdvantageScope.
    pub fn new(filename: &str, networktables: bool) -> Self {
        let mut filename = str_to_wpi(filename);
        let mut empty = str_to_wpi("");

        let mut error = 0;
        let datalog =
            unsafe { ffi::WPI_DataLog_CreateWriter(&mut filename, &mut error, &mut empty) };

        Self {
            datalog,
            nt: NetworkTablesInstance::default(),
            entries: HashMap::new(),
            nt_publishers: HashMap::new(),
            networktables,
        }
    }

    /// Add a value that implements [`Loggable`] at a path. This is for basic
    /// values which WPILib provides direct publish functions for. If the type
    /// instead derives [`AutoLog`], you should use [`Self::append`].
    pub fn append_value<T: Loggable>(&mut self, path: &str, value: T) {
        let entry = *self.entries.entry(path.to_string()).or_insert_with(|| {
            let mut name = str_to_wpi(path);
            let mut typ = str_to_wpi(T::WPI_TYPE);
            let mut empty = str_to_wpi("");

            unsafe { ffi::WPI_DataLog_Start(self.datalog, &mut name, &mut typ, &mut empty, now()) }
        });

        T::append(self.datalog, entry, now(), &value);

        if self.networktables {
            let publisher = self
                .nt_publishers
                .entry(path.to_string())
                .or_insert_with(|| {
                    let path = if path.starts_with("/") {
                        path.to_string()
                    } else {
                        format!("/{path}")
                    };
                    let out = self.nt.get_topic(&path).publisher::<T>();

                    out
                });
            T::set_nt(publisher.publisher, now(), &value);
        }
    }

    /// Add a value that implements [`AutoLog`] (or [`Loggable`]) at the path.
    pub fn append<T: AutoLog>(&mut self, path: &str, value: T) {
        value.append_to(self, path);
    }
}

impl Drop for Logger {
    fn drop(&mut self) {
        unsafe {
            ffi::WPI_DataLog_Release(self.datalog);
        }
    }
}
