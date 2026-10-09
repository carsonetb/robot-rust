#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

#[allow(dead_code)]
#[allow(unused_variables)]
#[allow(non_snake_case)]
#[allow(non_camel_case_types)]
#[allow(non_upper_case_globals)]
#[allow(improper_ctypes)]
pub mod bindings {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

pub use bindings::*;

autocxx::include_cpp! {
    #include "ctre/phoenix6/TalonFX.hpp"
    #include "ctre_helpers.hpp"

    #include "rev_helpers.hpp"

    safety!(unsafe)

    generate!("ctre::phoenix6::hardware::TalonFX")
    generate!("ctre_helpers::set_voltage")

    generate!("rev_helpers::sparkmax_create")
    generate!("rev_helpers::sparkmax_set")
    generate!("rev_helpers::sparkmax_set_voltage")
    generate!("rev_helpers::sparkmax_destroy")

    block!("wpi::SendableBuilder")
    block!("wpi::Sendable")
    block!("wpi::SendableRegistry")
}

pub use ffi::ctre::phoenix6::hardware::TalonFX;
pub use ffi::ctre_helpers::set_voltage;
pub use ffi::rev_helpers::{
    SparkMaxHandle, sparkmax_create, sparkmax_destroy, sparkmax_set, sparkmax_set_voltage,
};
