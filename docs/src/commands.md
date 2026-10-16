# Commands

This library _does_ feature a commands system. However, although it has the same name, it is very different from the commands you may have used in Java or C++. Commands are a type of resource, and thus each command is a unique type. For example, the type for a motor spinner command would look like this:

```Rust
struct SpinMotorCommand
```

Notice that the command has no member values. That is because you cannot set the speed of a `SpinMotorCommand`. That is specified by the implementation. We could also let the command dispatcher set the speed like so:

```Rust
struct SpinMotorCommand {
    voltage: Voltage
}
```

However, usually it's best practice to abstract these values into the implementation to ensure the behavior of the command is consistent across the entire program.

We can then register the command using `state`:

```Rust
state.register_command(SpinMotorCommand);
```

Note that registering a command doesn't make it run. Commands are disabled by default. If we wanted the command to be enabled immediately, we could use `.enabled()` on the output of `register_command`:

```Rust
state.register_command(SpinMotorCommand).enabled();
```

If you don't do this, you can enable any command in a system like so:

```Rust
fn enables_command(mut command: CommandMut<SpinMotorCommand>) {
    command.enable();
}
```

Attaching this system to the `Init` schedule would function the same as calling `.enabled()` above.

## Handlers

Just as a command is itself a resource, the code that handles running the command is also a system. The system takes the command wrapped in the `Command` helper type, along with whatever other data it needs. The header for `SpinMotorCommand` would look like so:

```Rust
fn spin(command: Command<SpinMotorCommand>, mut spinner: ResourceMut<Spinner>) { ... }
```

Usually, we don't want to mutate the command itself, but if we did we could replace the first parameter with `mut command: CommandMut<SpinMotorCommand>`.

When the command is enabled, the handler should set the voltage of the spinner to some positive value, and when the command ends we should set the voltage of the spinner to zero:

```Rust
fn spin(spin: Command<SpinMotorCommand>, mut spinner: ResourceMut<Spinner>) {
    if spin.enabled() {
        spinner.set_voltage(5.0.volts());
    }

    if spin.just_ended() {
        spinner.set_voltage(0.0.volts());
    }
}
```

Usually it's a better idea to use `just_ended()` instead of `disabled()`, just in case some other command or system wants to set the voltage of the spinner in the future.

This system can be registered like any normal system:

```Rust
state.add_systems(TeleopPeriodic, spin);
```

But usually it's easier to read when we group the command handler along with the code that registers the command itself:

```Rust
state
    .register_command(SpinMotorCommand)
    .with_handler(TeleopPeriodic, spin);
```

## Triggers

A trigger is something that tells a command when to run. It is similar to a system in that it can take any arguments, but it must return a `bool`. Let's say we want to run the `SpinMotorCommand` command only when the user presses the "A" button on the controller:

```Rust
fn spin_trigger(controller: Resource<XboxController>) -> bool {
    controller.a()
}
```

> [!NOTE]
> The `XboxController` needs to be inserted as a resource.

We can then tell the command to only run on the trigger:

```Rust
state
    .register_command(SpinMotorCommand)
    .with_handler(TeleopPeriodic, spin)
    .while_trigger(spin_trigger);
```

The `while_trigger` function will constantly set the command's enabled state based on the value of the trigger. If this is used, it will have only bad affects to enable or disable the command anywhere else in your code. If you wish to only enable the command when a trigger changes from `false` to `true`, and not disable it, use `on_trigger`. If you wish to enable and disable the command only when the trigger's state changes, use `with_trigger`.

With that, you have everything you need to use commands!

> [!NOTE]
> Creating triggers for each joystick button can be tedious. Assuming the `XboxController` is registered as a resource, the triggers you need already exist:
>
> ```Rust
> state
>     .register_command(SpinMotorCommand)
>     .with_handler(TeleopPeriodic, spin)
>     .on_trigger(XboxController::a_trigger);
> ```
>
> If you have a custom controller resource, these won't work and you'll have to create your own functions.
