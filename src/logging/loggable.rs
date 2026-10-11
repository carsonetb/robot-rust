use crate::{ffi, logging::str_to_wpi};

pub trait Loggable {
    fn typ() -> &'static str;
    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self);
}

impl Loggable for bool {
    fn typ() -> &'static str {
        "boolean"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        unsafe {
            ffi::WPI_DataLog_AppendBoolean(datalog, entry, value as i32, timestamp);
        }
    }
}

impl Loggable for f64 {
    fn typ() -> &'static str {
        "double"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        unsafe {
            ffi::WPI_DataLog_AppendDouble(datalog, entry, value, timestamp);
        }
    }
}

impl Loggable for f32 {
    fn typ() -> &'static str {
        "float"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        unsafe {
            ffi::WPI_DataLog_AppendFloat(datalog, entry, value, timestamp);
        }
    }
}

impl Loggable for i64 {
    fn typ() -> &'static str {
        "int"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        unsafe {
            ffi::WPI_DataLog_AppendInteger(datalog, entry, value, timestamp);
        }
    }
}

impl Loggable for i32 {
    fn typ() -> &'static str {
        "int"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        unsafe {
            ffi::WPI_DataLog_AppendInteger(datalog, entry, value as i64, timestamp);
        }
    }
}

impl Loggable for &str {
    fn typ() -> &'static str {
        "string"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        let value = str_to_wpi(&value);
        unsafe {
            ffi::WPI_DataLog_AppendString(datalog, entry, &value, timestamp);
        }
    }
}

impl Loggable for String {
    fn typ() -> &'static str {
        "string"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        let value = str_to_wpi(&value);
        unsafe {
            ffi::WPI_DataLog_AppendString(datalog, entry, &value, timestamp);
        }
    }
}

impl Loggable for &[bool] {
    fn typ() -> &'static str {
        "boolean[]"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        let value: Vec<i32> = value.iter().map(|&b| b as i32).collect();
        unsafe {
            ffi::WPI_DataLog_AppendBooleanArray(
                datalog,
                entry,
                value.as_ptr(),
                value.len(),
                timestamp,
            );
        }
    }
}

impl Loggable for &[f64] {
    fn typ() -> &'static str {
        "double[]"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        unsafe {
            ffi::WPI_DataLog_AppendDoubleArray(
                datalog,
                entry,
                value.as_ptr(),
                value.len(),
                timestamp,
            );
        }
    }
}

impl Loggable for &[f32] {
    fn typ() -> &'static str {
        "float[]"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        unsafe {
            ffi::WPI_DataLog_AppendFloatArray(
                datalog,
                entry,
                value.as_ptr(),
                value.len(),
                timestamp,
            );
        }
    }
}

impl Loggable for &[i64] {
    fn typ() -> &'static str {
        "int[]"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        unsafe {
            ffi::WPI_DataLog_AppendIntegerArray(
                datalog,
                entry,
                value.as_ptr(),
                value.len(),
                timestamp,
            );
        }
    }
}

impl Loggable for &[&str] {
    fn typ() -> &'static str {
        "string[]"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        let value: Vec<ffi::WPI_String> = value.iter().map(|s| str_to_wpi(s)).collect();
        unsafe {
            ffi::WPI_DataLog_AppendStringArray(
                datalog,
                entry,
                value.as_ptr(),
                value.len(),
                timestamp,
            );
        }
    }
}

impl Loggable for &[String] {
    fn typ() -> &'static str {
        "string[]"
    }

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self) {
        let value: Vec<ffi::WPI_String> = value.iter().map(|s| str_to_wpi(s)).collect();
        unsafe {
            ffi::WPI_DataLog_AppendStringArray(
                datalog,
                entry,
                value.as_ptr(),
                value.len(),
                timestamp,
            );
        }
    }
}
