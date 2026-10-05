#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

autocxx::include_cpp! {
    #include "ctre/phoenix6/TalonFX.hpp"
    safety!(unsafe)

    generate!("ctre::phoenix6::hardware::TalonFX")
    generate!("ctre::phoenix6::controls::DutyCycleOut")

    block!("wpi::SendableBuilder")
    block!("wpi::Sendable")
    block!("wpi::SendableRegistry")
}

pub use ffi::ctre::phoenix6::hardware::TalonFX;
