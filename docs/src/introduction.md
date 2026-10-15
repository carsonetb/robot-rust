# Introduction

Welcome to the Robot in Rust project for FRC! This is a safe, all-in-one solution for writing robot code in Rust. If you are tired of using Java or C++, or simply want to be special, maybe this project is for you.

## Features

Normally, different functionality is separated into different modules created by different teams (Core functionality, CTRE motors, REV motors, Logging, Autonomoous, etc). In Rust, we don't get this luxury because there are no other teams to write modules! So, the goal of this library is to support all those needs:

- HAL bindings: A State type that sets everything up and runs your robot for you.
- CTRE bindings: TalonFX, CANCoder, Pigeon2, a subset of configs.
- REV bindings: SparkMax, Spark Relative & Absolute Encoders, a subset of configs.
- Logging system: Similar to the [AdvantageKit](https://docs.advantagekit.org/) system, supports logging basic Rust types, Units, and automatically making your own types loggable via the `AutoLog` derive-macro.
- Units: Everything, when possible, is unit-ed using [`uom`](https://docs.rs/uom/latest/uom/). Helper functions are provided to make using these easier.
- Math: PID controller support, (planned) drivetrain kinematics support.
- (planned) Autonomous System

## Commands and Subsystems

Originally I tried to create a 1-1 replica of Commands and Subsystems. But it turns out mapping complex OOP concepts to Rust quickly becomes a mess. So I scrapped it all and moved to an ECS!

Don't worry, I created this book precisely so that people could learn to use this foreign system.

## Who this is for

To use this project for serious robot code (meaning you are bringing it to a competition or there will be time-pressure to fix bugs should they occur) you should be _experienced_ in Rust. You should have built one or two projects in Rust before. If you've used the [Bevy Game Engine](https://bevy.org/) before, all the better! If you aren't so experienced, continue at your own risk, but you may find yourself staring at a foreign wall of errors while your robot is queueing.

To use this for side-projects or offseason events, you sohuld still know Rust, but you don't need any serious experience. In fact, this will be your experience!

Regardless, you should still read through this book, and use it as a reference in the future. Good luck!
