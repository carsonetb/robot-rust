# Introduction

Welcome to the Robot in Rust project for FRC! This is a safe, all-in-one solution for writing robot code in Rust. If you are tired of using Java or C++, maybe this project is for you.

This exact thing, of course, has been tried many times before. See [FIRST Rust Competition](https://github.com/first-rust-competition/first-rust-competition), [frcrs](https://github.com/Team-2502/frcrs), and a few others you might find online. This project is different, because it's more than just bindings to WPILib. We have a custom ECS-based scheduler (instead of Commands & Subsystems), logging system, autonomous system, simulation system, as well as the traditional WPILib, CTRE, REV, and (subset of) NetworkTables bindings.

## Who this is for

To use this project for serious robot code (meaning you are bringing it to a competition or there will be time-pressure to fix bugs should they occur) you should be experienced in Rust and low-level programming, and have a backup robot program written in Java or C++.

If you're using this for other less serious projects, regardless of your experience you should give this a try and see if you can figure it out.

Regardless, you should still read through this book, and use it as a reference in the future. Good luck!
