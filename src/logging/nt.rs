use num_enum::TryFromPrimitive;

use super::str_to_wpi;
use crate::{ffi::*, logging::Loggable};

pub struct NetworkTablesInstance {
    pub(crate) inst: NT_Inst,
}

impl NetworkTablesInstance {
    /// Create an instance. Use `default` for the default instance.
    pub fn new() -> Self {
        let inst = unsafe { NT_CreateInstance() };
        unsafe {
            NT_StartServer(
                inst,
                &str_to_wpi("networktables.json"),
                &str_to_wpi(""),
                1735,
                5810,
            );
        }
        Self { inst }
    }

    pub fn get_topic(&self, name: &str) -> NetworkTablesTopic {
        let out = NetworkTablesTopic::new(
            unsafe { NT_GetTopic(self.inst, &str_to_wpi(name)) },
            name.to_string(),
        );
        out
    }

    // pub fn get_entry(&'_ self, name: &str) -> NetworkTablesEntry<'_> {
    //     NetworkTablesEntry::new(unsafe { NT_GetEntry(self.inst, &str_to_wpi(name)) })
    // }
}

impl Default for NetworkTablesInstance {
    fn default() -> Self {
        let inst = unsafe { NT_GetDefaultInstance() };
        Self { inst }
    }
}

impl Drop for NetworkTablesInstance {
    fn drop(&mut self) {
        unsafe {
            NT_DestroyInstance(self.inst);
        }
    }
}

pub struct NetworkTablesTopic {
    pub(crate) topic: NT_Topic,
    pub name: String,
}

impl NetworkTablesTopic {
    pub(crate) fn new(topic: NT_Topic, name: String) -> Self {
        Self { topic, name }
    }

    pub fn get_type(&self) -> NetworkTablesType {
        let typ = unsafe { NT_GetTopicType(self.topic) };
        NetworkTablesType::try_from_primitive(typ).unwrap_or({
            crate::ds::alert(
                crate::ds::AlertType::Error,
                &format!(
                    "Failed to derive NetworkTables type for topic {}, type was {typ}",
                    self.name
                ),
            );
            NetworkTablesType::Unassigned
        })
    }

    pub fn publisher<T: Loggable>(&'_ self) -> NetworkTablesPublisher {
        NetworkTablesPublisher::new(unsafe {
            let out = NT_Publish(
                self.topic,
                T::NT_TYPE as u32,
                &str_to_wpi(T::NT_TYPE.to_str()),
                std::ptr::null(),
            );
            println!("created publisher");
            out
        })
    }
}

pub struct NetworkTablesPublisher {
    pub(crate) publisher: NT_Publisher,
}

impl<'t> NetworkTablesPublisher {
    pub(crate) fn new(publisher: NT_Publisher) -> Self {
        Self { publisher }
    }
}

impl Drop for NetworkTablesPublisher {
    fn drop(&mut self) {
        unsafe {
            NT_Unpublish(self.publisher);
        }
    }
}

// pub struct NetworkTablesEntry<'t> {
//     _phantom: PhantomData<&'t NetworkTablesInstance>,
//     entry: NT_Entry,
// }
//
// impl<'t> NetworkTablesEntry<'t> {
//     pub(crate) fn new(entry: NT_Entry) -> Self {
//         Self {
//             _phantom: PhantomData,
//             entry,
//         }
//     }
//
//     pub fn value(&self) -> NetworkTablesValue<'t> {
//         unsafe {
//             let value = MaybeUninit::zeroed();
//             NT_GetEntryValue(self.entry, value.as_mut_ptr());
//             NetworkTablesValue::new(value.assume_init())
//         }
//     }
// }
//
// impl<'t> Drop for NetworkTablesEntry<'t> {
//     fn drop(&mut self) {
//         unsafe {
//             NT_ReleaseEntry(self.entry);
//         }
//     }
// }

//
#[derive(Debug, PartialEq, Eq, TryFromPrimitive)]
#[repr(u32)]
pub enum NetworkTablesType {
    Unassigned = 0,
    Boolean = 0x01,
    Double = 0x02,
    String = 0x04,
    Raw = 0x08,
    BooleanArray = 0x10,
    DoubleArray = 0x20,
    StringArray = 0x40,
    RPC = 0x80,
    Integer = 0x100,
    Float = 0x200,
    IntegerArray = 0x400,
    FloatArray = 0x800,
}

impl NetworkTablesType {
    pub const fn to_str(&self) -> &'static str {
        match self {
            NetworkTablesType::Unassigned => "unassigned",
            NetworkTablesType::Boolean => "boolean",
            NetworkTablesType::Double => "double",
            NetworkTablesType::String => "string",
            NetworkTablesType::Raw => "raw",
            NetworkTablesType::BooleanArray => "boolean[]",
            NetworkTablesType::DoubleArray => "double[]",
            NetworkTablesType::StringArray => "string[]",
            NetworkTablesType::RPC => "rpc",
            NetworkTablesType::Integer => "int",
            NetworkTablesType::Float => "float",
            NetworkTablesType::IntegerArray => "int[]",
            NetworkTablesType::FloatArray => "float[]",
        }
    }
}

// pub struct NetworkTablesValue<'t> {
//     _phantom: PhantomData<&'t NetworkTablesInstance>,
//     pub(crate) value: NT_Value,
// }
//
// impl<'t> NetworkTablesValue<'t> {
//     pub(crate) fn new(value: NT_Value) -> Self {
//         Self {
//             _phantom: PhantomData,
//             value,
//         }
//     }
//
//     pub fn get_type(&self) -> NetworkTablesType {
//         NetworkTablesType::try_from_primitive(self.value.type_).unwrap_or({
//             crate::ds::alert(
//                 crate::ds::AlertType::Error,
//                 "Failed to derive NetworkTables type.",
//             );
//             NetworkTablesType::Unassigned
//         })
//     }
//
//     pub fn get<'r, T: FromNTValue<'r, 't>>(&'r self) -> Option<T> {
//         T::from_nt_value(self)
//     }
// }
//
// impl<'t> Drop for NetworkTablesValue<'t> {
//     fn drop(&mut self) {
//         unsafe {
//             NT_DisposeValue(&mut self.value);
//         }
//     }
// }
//
// pub trait FromNTValue<'r, 't: 'r>: Sized {
//     fn from_nt_value(value: &'r NetworkTablesValue<'t>) -> Option<Self>;
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for bool {
//     fn from_nt_value(value: &NetworkTablesValue) -> Option<Self> {
//         if value.get_type() != NetworkTablesType::Boolean {
//             None
//         } else {
//             Some(unsafe { value.value.data.v_boolean } != 0)
//         }
//     }
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for i64 {
//     fn from_nt_value(value: &NetworkTablesValue) -> Option<Self> {
//         if value.get_type() != NetworkTablesType::Integer {
//             None
//         } else {
//             Some(unsafe { value.value.data.v_int })
//         }
//     }
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for f32 {
//     fn from_nt_value(value: &NetworkTablesValue) -> Option<Self> {
//         if value.get_type() != NetworkTablesType::Float {
//             None
//         } else {
//             Some(unsafe { value.value.data.v_float })
//         }
//     }
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for f64 {
//     fn from_nt_value(value: &NetworkTablesValue) -> Option<Self> {
//         if value.get_type() != NetworkTablesType::Double {
//             None
//         } else {
//             Some(unsafe { value.value.data.v_double })
//         }
//     }
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for &'r str {
//     fn from_nt_value(value: &'r NetworkTablesValue) -> Option<Self> {
//         if value.get_type() != NetworkTablesType::String {
//             None
//         } else {
//             Some(wpi_to_str(unsafe { &value.value.data.v_string }))
//         }
//     }
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for String {
//     fn from_nt_value(value: &'r NetworkTablesValue) -> Option<Self> {
//         value.get::<&str>().map(|s| s.to_string())
//     }
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for &'r [bool] {
//     fn from_nt_value(value: &'r NetworkTablesValue) -> Option<Self> {
//         if value.get_type() != NetworkTablesType::BooleanArray {
//             None
//         } else {
//             let data = unsafe { value.value.data.arr_boolean };
//             Some(unsafe { std::slice::from_raw_parts(data.arr as *const bool, data.size) })
//         }
//     }
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for &'r [f64] {
//     fn from_nt_value(value: &'r NetworkTablesValue) -> Option<Self> {
//         if value.get_type() != NetworkTablesType::DoubleArray {
//             None
//         } else {
//             let data = unsafe { value.value.data.arr_double };
//             Some(unsafe { std::slice::from_raw_parts(data.arr as *const f64, data.size) })
//         }
//     }
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for &'r [f32] {
//     fn from_nt_value(value: &'r NetworkTablesValue) -> Option<Self> {
//         if value.get_type() != NetworkTablesType::FloatArray {
//             None
//         } else {
//             let data = unsafe { value.value.data.arr_float };
//             Some(unsafe { std::slice::from_raw_parts(data.arr as *const f32, data.size) })
//         }
//     }
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for &'r [i64] {
//     fn from_nt_value(value: &'r NetworkTablesValue) -> Option<Self> {
//         if value.get_type() != NetworkTablesType::IntegerArray {
//             None
//         } else {
//             let data = unsafe { value.value.data.arr_int };
//             Some(unsafe { std::slice::from_raw_parts(data.arr as *const i64, data.size) })
//         }
//     }
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for Vec<&'r str> {
//     fn from_nt_value(value: &'r NetworkTablesValue) -> Option<Self> {
//         if value.get_type() != NetworkTablesType::BooleanArray {
//             None
//         } else {
//             let data = unsafe { value.value.data.arr_string };
//             let wpi_strings =
//                 unsafe { std::slice::from_raw_parts(data.arr as *const WPI_String, data.size) };
//             let output = wpi_strings
//                 .iter()
//                 .map(|string| wpi_to_str(&string))
//                 .collect::<Vec<_>>();
//             Some(output)
//         }
//     }
// }
//
// impl<'r, 't: 'r> FromNTValue<'r, 't> for Vec<String> {
//     fn from_nt_value(value: &'r NetworkTablesValue) -> Option<Self> {
//         value
//             .get::<Vec<&str>>()
//             .map(|v| v.iter().map(|s| s.to_string()).collect())
//     }
// }
