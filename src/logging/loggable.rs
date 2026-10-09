use crate::ffi;

pub trait Loggable {
    fn typ() -> &'static str;
    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: Self);
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
