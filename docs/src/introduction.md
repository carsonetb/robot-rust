# Introduction

Welcome to the Robot in Rust project for FRC! This is a safe, all-in-one solution for writing robot code in Rust. If you are tired of using Java or C++, maybe this project is for you.

This exact thing, of course, has been tried many times before. See [FIRST Rust Competition](https://github.com/first-rust-competition/first-rust-competition), [frcrs](https://github.com/Team-2502/frcrs), and a few others you might find online. This project is different, because it's more than just bindings to WPILib. We have a custom ECS-based scheduler (instead of Commands & Subsystems), logging system, autonomous system, simulation system, as well as the traditional WPILib, CTRE, REV, and (subset of) NetworkTables bindings.

## Features

Normally, different functionality is separated into different modules created by different teams (Core functionality, CTRE motors, REV motors, Logging, Autonomoous, etc). In Rust, we don't get this luxury because there are no other teams to write modules! So, the goal of this library is to support all those needs:

- HAL bindings: A State type that sets everything up and runs your robot for you.
- CTRE bindings: TalonFX, CANCoder, Pigeon2, a subset of configs.
- REV bindings: SparkMax, Spark Relative & Absolute Encoders, a subset of configs.
- Logging system: Similar to the [AdvantageKit](https://docs.advantagekit.org/) system, supports logging basic Rust types, Units, and automatically making your own types loggable via the `AutoLog` derive-macro. NetworkTables is supported.
- Units: Everything, when possible, is unit-ed using [`uom`](https://docs.rs/uom/latest/uom/). Helper functions are provided to make using these easier.
- Math: Feedback and feedforward controllers, simple math types, kinematics, odometry, ported manually from WPILib. If a math type exists, it should work the same as it does in WPILib.
- Autonomous System: Support for tank drive autonomous point-to-point path following, and (planned) support for swerve drive path following.
- Simulation: Many of the WPILib simulation types are manually ported, and future support for integrating [MuJoCo](https://mujoco.org/) is planned.

## Commands and Subsystems

The main difference between this and WPILib is the absence of the Commands and Subsystems framework. Instead we use the [ECS](https://docs.rs/bevy_ecs/latest/bevy_ecs/) from the [Bevy Game Engine](https://bevy.org/), which is lightweight and much more suited for Rust than Commands.

## Who this is for

To use this project for serious robot code (meaning you are bringing it to a competition or there will be time-pressure to fix bugs should they occur) you should be experienced in Rust and low-level programming, and have a backup robot program written in Java or C++.

If you're using this for other less serious projects, regardless of your experience you should give this a try and see if you can figure it out.

Regardless, you should still read through this book, and use it as a reference in the future. Good luck!

## Installation

All you need installed is WPILib. If it's already installed it should appear in your home directory. You can follow the official guide [here](https://docs.wpilib.org/en/stable/docs/zero-to-robot/step-2/wpilib-setup.html). This library officially supports Linux and MacOS, and Windows support is planned.
