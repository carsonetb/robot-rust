use crate::ffi;
use crate::logging::nt::NetworkTablesType;
use crate::logging::str_to_wpi;

/// Trait for basic types that WPILib provides logging functions for. This
/// trait is already implemented for all those types.
pub trait Loggable {
    /// The type the WPILib logging system provides for this type.
    const WPI_TYPE: &'static str;
    /// The NetworkTablesType of this type.
    const NT_TYPE: NetworkTablesType;

    /// Append this type at the entry and timestamp, to the logger.
    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self);
    /// Publish this value at the timestamp.
    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self);
}

impl Loggable for bool {
    const WPI_TYPE: &'static str = "boolean";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::Boolean;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
        unsafe {
            ffi::WPI_DataLog_AppendBoolean(datalog, entry, *value as i32, timestamp);
        }
    }

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        unsafe {
            ffi::NT_SetBoolean(publisher, timestamp, *value as ffi::NT_Bool);
        }
    }
}

impl Loggable for f64 {
    const WPI_TYPE: &'static str = "double";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::Double;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
        unsafe {
            ffi::WPI_DataLog_AppendDouble(datalog, entry, *value, timestamp);
        }
    }

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        unsafe {
            ffi::NT_SetDouble(publisher, timestamp, *value);
        }
    }
}

impl Loggable for f32 {
    const WPI_TYPE: &'static str = "float";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::Float;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
        unsafe {
            ffi::WPI_DataLog_AppendFloat(datalog, entry, *value, timestamp);
        }
    }

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        unsafe {
            ffi::NT_SetFloat(publisher, timestamp, *value);
        }
    }
}

impl Loggable for i64 {
    const WPI_TYPE: &'static str = "int";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::Integer;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
        unsafe {
            ffi::WPI_DataLog_AppendInteger(datalog, entry, *value, timestamp);
        }
    }

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        unsafe {
            ffi::NT_SetInteger(publisher, timestamp, *value);
        }
    }
}

impl Loggable for i32 {
    const WPI_TYPE: &'static str = "int";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::Integer;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
        unsafe {
            ffi::WPI_DataLog_AppendInteger(datalog, entry, *value as i64, timestamp);
        }
    }

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        unsafe {
            ffi::NT_SetInteger(publisher, timestamp, *value as i64);
        }
    }
}

impl Loggable for &str {
    const WPI_TYPE: &'static str = "string";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::String;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
        let value = str_to_wpi(&value);
        unsafe {
            ffi::WPI_DataLog_AppendString(datalog, entry, &value, timestamp);
        }
    }

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        let value = str_to_wpi(&value);
        unsafe {
            ffi::NT_SetString(publisher, timestamp, &value);
        }
    }
}

impl Loggable for String {
    const WPI_TYPE: &'static str = "string";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::String;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
        let value = str_to_wpi(&value);
        unsafe {
            ffi::WPI_DataLog_AppendString(datalog, entry, &value, timestamp);
        }
    }

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        let value = str_to_wpi(&value);
        unsafe {
            ffi::NT_SetString(publisher, timestamp, &value);
        }
    }
}

impl Loggable for &[bool] {
    const WPI_TYPE: &'static str = "boolean[]";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::BooleanArray;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
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

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        let value: Vec<i32> = value.iter().map(|&b| b as i32).collect();
        unsafe {
            ffi::NT_SetBooleanArray(publisher, timestamp, value.as_ptr(), value.len());
        }
    }
}

impl Loggable for &[f64] {
    const WPI_TYPE: &'static str = "double[]";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::DoubleArray;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
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

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        let value: Vec<f64> = value.iter().map(|&b| b as f64).collect();
        unsafe {
            ffi::NT_SetDoubleArray(publisher, timestamp, value.as_ptr(), value.len());
        }
    }
}

impl Loggable for &[f32] {
    const WPI_TYPE: &'static str = "float[]";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::FloatArray;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
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

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        let value: Vec<f32> = value.iter().map(|&b| b as f32).collect();
        unsafe {
            ffi::NT_SetFloatArray(publisher, timestamp, value.as_ptr(), value.len());
        }
    }
}

impl Loggable for &[i64] {
    const WPI_TYPE: &'static str = "int[]";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::IntegerArray;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
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

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        let value: Vec<f64> = value.iter().map(|&b| b as f64).collect();
        unsafe {
            ffi::NT_SetDoubleArray(publisher, timestamp, value.as_ptr(), value.len());
        }
    }
}

impl Loggable for &[&str] {
    const WPI_TYPE: &'static str = "string[]";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::StringArray;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
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

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        let value: Vec<ffi::WPI_String> = value.iter().map(|s| str_to_wpi(s)).collect();
        unsafe {
            ffi::NT_SetStringArray(publisher, timestamp, value.as_ptr(), value.len());
        }
    }
}

impl Loggable for &[String] {
    const WPI_TYPE: &'static str = "string[]";
    const NT_TYPE: NetworkTablesType = NetworkTablesType::StringArray;

    fn append(datalog: *mut ffi::WPI_DataLog, entry: i32, timestamp: i64, value: &Self) {
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

    fn set_nt(publisher: ffi::NT_Publisher, timestamp: i64, value: &Self) {
        let value: Vec<ffi::WPI_String> = value.iter().map(|s| str_to_wpi(s)).collect();
        unsafe {
            ffi::NT_SetStringArray(publisher, timestamp, value.as_ptr(), value.len());
        }
    }
}
