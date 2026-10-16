use revolution_per_second_cubed::revolution_per_second_cubed as revolution_per_second_cubed_;
use revolution_per_second_squared::revolution_per_second_squared as revolution_per_second_squared_;
use rpm::rpm as rpm_;
pub use uom::si::acceleration::{
    foot_per_second_squared, meter_per_second_squared, standard_gravity,
};
pub use uom::si::angle::{degree, radian, revolution};
pub use uom::si::angular_acceleration::{degree_per_second_squared, radian_per_second_squared};
pub use uom::si::angular_jerk::{degree_per_second_cubed, radian_per_second_cubed};
pub use uom::si::angular_velocity::{degree_per_second, radian_per_second, revolution_per_second};
pub use uom::si::area::square_meter;
pub use uom::si::electric_current::{ampere, milliampere};
pub use uom::si::electric_potential::{millivolt, volt};
pub use uom::si::f64::{
    Acceleration, Angle, AngularAcceleration, AngularJerk, AngularVelocity, Area, ElectricCurrent,
    ElectricPotential, Force, Frequency, Length, Mass, ThermodynamicTemperature, Time, Velocity,
};
pub use uom::si::force::newton;
pub use uom::si::frequency::{hertz, millihertz};
pub use uom::si::length::{centimeter, foot, inch, meter, millimeter};
pub use uom::si::mass::{gram, kilogram, ounce, pound};
pub use uom::si::thermodynamic_temperature::{degree_celsius, degree_fahrenheit, kelvin};
pub use uom::si::time::{microsecond, millisecond, minute, second};
pub use uom::si::velocity::{foot_per_second, inch_per_second, meter_per_second};
use uom::si::{Dimension, Quantity, Units};

use crate::prelude::*;

pub mod revolution_per_second_squared {
    unit! {
        system: uom::si;
        quantity: uom::si::angular_acceleration;
        @revolution_per_second_squared: 6.283185307179586;
        "rev/s^2", "revolution per second squared", "revolutions per second squared";
    }
}

pub mod revolution_per_second_cubed {
    unit! {
        system: uom::si;
        quantity: uom::si::angular_jerk;
        @revolution_per_second_cubed: 6.283185307179586;
        "rev/s^3", "revolution per second cubed", "revolutions per second cubed";
    }
}

pub mod rpm {
    unit! {
        system: uom::si;
        quantity: uom::si::angular_velocity;
        @rpm: 1.047_197_551_196_597_7E-1;
        "rpm", "rotation per minute", "rotations per minute";
    }
}

macro_rules! define_unit_helpers {
    (
        pub trait $TraitName:ident for $Type:ty {
            $(
                fn $method:ident -> $RetType:ident<$Unit:ident>;
            )+
        }
    ) => {
        pub trait $TraitName {
            $(
                fn $method(self) -> $RetType;
            )+
        }

        impl $TraitName for $Type {
            $(
                fn $method(self) -> $RetType {
                    $RetType::new::<$Unit>(self)
                }
            )+
        }
    };
}

pub type Voltage = ElectricPotential;
pub type Amps = ElectricCurrent;
pub type Current = ElectricCurrent;
pub type Temperature = ThermodynamicTemperature;

define_unit_helpers! {
    pub trait UnitHelpers for f64 {
        fn meters -> Length<meter>;
        fn centimeters -> Length<centimeter>;
        fn millimeters -> Length<millimeter>;
        fn inches -> Length<inch>;
        fn feet -> Length<foot>;

        fn square_meters -> Area<square_meter>;

        fn seconds -> Time<second>;
        fn milliseconds -> Time<millisecond>;
        fn microseconds -> Time<microsecond>;
        fn minutes -> Time<minute>;

        fn radians -> Angle<radian>;
        fn rotations -> Angle<revolution>;
        fn degrees -> Angle<degree>;

        fn meters_per_second -> Velocity<meter_per_second>;
        fn feet_per_second -> Velocity<foot_per_second>;
        fn inches_per_second -> Velocity<inch_per_second>;

        fn rotations_per_second -> AngularVelocity<revolution_per_second>;
        fn radians_per_second -> AngularVelocity<radian_per_second>;
        fn degrees_per_second -> AngularVelocity<degree_per_second>;
        fn rpm -> AngularVelocity<rpm_>;

        fn meters_per_second_squared -> Acceleration<meter_per_second_squared>;
        fn feet_per_second_squared -> Acceleration<foot_per_second_squared>;
        fn gravities -> Acceleration<standard_gravity>;

        fn degrees_per_second_squared -> AngularAcceleration<degree_per_second_squared>;
        fn rotations_per_second_squared -> AngularAcceleration<revolution_per_second_squared_>;
        fn radians_per_second_squared -> AngularAcceleration<radian_per_second_squared>;

        fn degrees_per_second_cubed -> AngularJerk<degree_per_second_cubed>;
        fn rotations_per_second_cubed -> AngularJerk<revolution_per_second_cubed_>;
        fn radians_per_second_cubed -> AngularJerk<radian_per_second_cubed>;

        fn hertz -> Frequency<hertz>;
        fn millihertz -> Frequency<millihertz>;

        fn kilograms -> Mass<kilogram>;
        fn grams -> Mass<gram>;
        fn pounds -> Mass<pound>;
        fn ounces -> Mass<ounce>;

        fn newtons -> Force<newton>;

        fn volts -> ElectricPotential<volt>;
        fn millivolts -> ElectricPotential<millivolt>;

        fn amps -> ElectricCurrent<ampere>;
        fn milliamps -> ElectricCurrent<milliampere>;

        fn kelvin -> ThermodynamicTemperature<kelvin>;
        fn celsius -> ThermodynamicTemperature<degree_celsius>;
        fn fahrenheit -> ThermodynamicTemperature<degree_fahrenheit>;
    }
}

impl<D: ?Sized + Dimension, U: ?Sized + Units<f64>> AutoLog for Quantity<D, U, f64> {
    fn append_to(self, logger: &mut Logger, path: &str) {
        self.value.append_to(logger, path);
    }
}
