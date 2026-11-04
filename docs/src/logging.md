# Logging

A logger is already setup for your use. It logs to the `wpilog` file on the roboRIO, as well as to NetworkTables. Tools such as [AdvantageScope](https://docs.advantagescope.org/) can read these logged values.

Most basic types implement the `Loggable` trait (booleans, floats, integers, `&str`, `String`, and arrays of all those values). You can log them in a system using the `Logger` resource like so:

```rust
fn log(mut logger: ResourceMut<Logger>) {
    logger.append_value("Path/Number", 5.0);
}
```

The `append_value` function is only for basic values that implement `Loggable`. If you want to log types that have multiple values, you should use the `append` function (which supports all `Loggable` types as well). 

## AutoLog

Similar to [AdvantageKit](https://docs.advantagekit.org/), there is an `AutoLog` trait which you can automatically implement for any `struct` that is made up of types that themselves implement `AutoLog`. 

For example, the state for an intake subsystem could be specified like so:

```rust
#[derive(AutoLog)]
struct IntakeState {
    speed: AngularVelocity,
    angle: Angle,
}
```

You could then log this by calling `logger.append("Intake", intake_state)`. Note that unit types also can all be logged.

You can also nest loggable types:

```rust
#[derive(AutoLog)]
struct IntakePivotState {
    angle: Angle,
    velocity: AngularVelocity,
}

#[derive(AutoLog)]
struct IntakeState {
    velocity: AngularVelocity,
    pivot: IntakePivotState,
}
```

The logging tree for the new `IntakeState` would look like this:

- Intake/velocity
- Intake/pivot/angle
- Intake/pivot/velocity
