# Robot-Rust

This project is a new way to write code for FRC. At its completion, it will be a complete safe wrapper of (a subset of) WPILib, CTRE, and REV. When writing robot code in Rust, you are working in an ecosystem that is both faster and safer.

## Why Use Rust?

- **Performance**: Rust, like C++ which FRC libraries are natively written in, is a _compiled programming language_. Compared to Java, complex math or logic can be sped up by around 1.5-2.5X. Rust also has a much lower memory profile than Java.
- **Safety**: Runtime errors are just about the worst thing that can happen during a match. Rust's compile-time guarantees and the library's design work hand-in-hand to prevent these.
- **Idiomatic**: This library doesn't try to port object-oriented concepts like Commands, Subsystems, or even the Robot abstraction into Rust. Instead, we use the [ECS system](https://docs.rs/bevy_ecs/latest/bevy_ecs/) from the Bevy game engine, so you can write your robot functionality in an elegant, Rust-like manner.
- **Logging**: A logger resource is built-in to the framework, along with an `AutoLog` trait and derive-macro. `AutoLog` objects can automatically be logged, and can be viewed in AdvantageScope.
- **Units**: Everything uses the same units system, with helper functions to make creating a unitted value as simple as `1.0.meters()`. CTRE and REV motors all use the unit types, and unit types are all loggable.
- **Simplicity**: The crate provides a prelude which includes everything you need to write your robot. CTRE and REV also have a prelude.
- **Control & Math**: PID logic and other math (coming soon) is builtin to the crate.

## State of this Project

WPILib 2026 is supported. 2027 support is planned when CTRE, REV, and WPILib can stabilize their APIs.

Currently the project is too early-stages for me to even bother versioning it. It is currently possible to create a simple robot, but not much more. Unless I have stopped commiting to the project, I am actively working on it.
