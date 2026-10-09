use std::collections::HashMap;

use crate::logging::{Loggable, now};
use crate::{AutoLog, ffi};

fn str_to_wpi(s: &str) -> ffi::WPI_String {
    ffi::WPI_String {
        str_: s.as_ptr(),
        len: s.len(),
    }
}

pub struct Logger {
    datalog: *mut ffi::WPI_DataLog,
    // TODO: Looking up in hashmap is inefficient
    entries: HashMap<String, i32>,
}

impl Logger {
    pub fn new(filename: &str) -> Self {
        let mut filename = str_to_wpi(filename);
        let mut empty = str_to_wpi("");

        let mut error = 0;
        let datalog =
            unsafe { ffi::WPI_DataLog_CreateWriter(&mut filename, &mut error, &mut empty) };

        Self {
            datalog,
            entries: HashMap::new(),
        }
    }

    pub fn append_value<T: Loggable>(&mut self, path: &str, value: T) {
        let entry = *self.entries.entry(path.to_string()).or_insert_with(|| {
            let mut name = str_to_wpi(path);
            let mut typ = str_to_wpi(T::typ());
            let mut empty = str_to_wpi("");

            unsafe { ffi::WPI_DataLog_Start(self.datalog, &mut name, &mut typ, &mut empty, now()) }
        });

        T::append(self.datalog, entry, now(), value);
    }

    pub fn append<T: AutoLog>(&mut self, path: &str, value: &T) {
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
