# Systems, Resources, and Schedules

This project manages everything using an ECS, which stands for _Entity Component System_.
We will learn more later about the purpose of Entities and Components, but for now we only need to know how Systems work.

A system is anything that takes some inputs, and modifies some of those inputs. You saw an example of a system called `hello_world` in the previous chapter, although this one took no inputs. In reality, systems can (and usually do) take many inputs and many types of inputs. The most common input you will be using is called a Resource.

## Resources

Any type can be a resource. There can only be one resource per type (put simply, there can't be more than one `Intake` resource), and they must be instantiated when the program starts. If you've done some FRC programming before, you'll probably notice that this design is very similar to what a Subsystem is. Subsystems are stored in resources, but also are controllers, program state, and many other things. For the most part, all the inputs to your systems will be resources.

## Schedules

In the previous chapter, we wrote `state.add_systems(Init, hello_robot)`. `Init` is a schedule, which specifies _when_ a system should be ran. There are a lot of different schedules:

- `Init`: Runs when the robot program starts
- `DisabledInit`/`TeleopInit`/`AutonomousInit`/`TestInit`: Runs when a certain state of the robot program starts.
- `DisabledExit`/`TeleopExit`/`AutonomousExit`/`TestExit`: Runs when a certain state of the robot program ends.
- `Periodic`: Runs every ~20ms.
- `DisabledPeriodic`/`TeleopPeriodic`/`AutonomousPeriodic`/`TestPeriodic`: Runs every ~20ms during a certain stage of the robot program.

## The `State`

In the main function, the program creates the State. You can configure how the program will run using the state, which holds both the systems and the resources used by the systems. Then, after calling `state.run()`, the state will handle running systems at the correct time, and passing the resources into the systems.

We saw a basic example of the usage of the State in the previous chapter:

```rust
fn main() {
    let mut state: State = State::new().unwrap(); // Create the state.
    state.add_systems(Init, hello_robot); // Tell the state to run hello_robot when the program initializes
    state.run(); // Now the program runs, and state will handle calling hello_robot at the correct time.
}
```

When calling `run`, the state first runs the `Init` schedule. Then, it enters into a loop that runs until the program is terminated:

- First it polls all the data from the driver station.
- Then, if the mode changes (for example from Disabled to Teleop), it runs the matching schedules (DisabledExit, TeleopInit).
- Then, it runs the periodic schedule for the respective mode (like TeleopPeriodic).
- Lastly, it runs the general Periodic schedule.

During each schedule, the system you assigned to it will run. The resources you specified (if available) will be passed into the system, which the system can then modify. Resources are global, so if you modify them in one system or in one schedule, it will be modified for everything else.

Now that we've got all the theory out of the way, we can see how to actually do things.

## Creating a resource

For now, let's just create a resource that wraps a single motor. We'll derive `Deref` and `DerefMut` so that we can interact with the type as if it was just a motor (you can read about what those do [here](https://doc.rust-lang.org/std/ops/trait.Deref.html)).

For this example we'll use CTRE's `TalonFX` motor controller. If you want to use REV, you can simply replace wherever it says `TalonFX` with `SparkMax`.

We'll start by creating a `MyMotor` resource:

```Rust
#[derive(Deref, DerefMut)]
struct MyMotor(TalonFX);
```

This resource can be added to `state` like so (you can set the CAN ID and CAN Bus to be whatever corresponds to your actual motor):

```Rust
state.insert_resource(MyMotor(TalonFX::new(1, "*")));
```

The resource we've added will now be available for use in systems. We can now write a system that will use it.

## Using a resource

The resource can now be used in a system. All resource arguments to a system need to be wrapped in either the `Resource` or `ResourceMut` type. For example, we'll create a system called `spin` that will spin `MyMotor`:

```Rust
fn spin(mut motor: ResourceMut<MyMotor>) {
    motor.set_voltage(5.0.volts());
}
```

The `volts` function is provided by the library so you can easily create unit-ed types. We use it because `TalonFX::set_voltage` requires a `Voltage` (or `ElectricPotential`) type.

For our purposes, we will use the `TeleopPeriodic` schedule to spin our motor. So after registering the resource, we can add the system like so:

```Rust
state.add_systems(TeleopPeriodic, spin);
state.run();
```

When you call `state.run()` and go into Teleop mode, the state will see that the `spin` system takes the `MyMotor` resource. Knowing that, it will automatically route the resource into the system, which can then modify the resource.

Now, you should have a spinning motor!

> [!WARNING]
> Systems in a schedule don't run in any specified order, and will usually run in different orders every iteration. If you want to specify the order systems are ran, you can use `state.add_systems(Schedule, (first, second).chain());`.

## Game state

There are some resources that are automatically added which can give you information about the game state.

- There is the `Mode` enum, which specifies whether the robot is disabled, in teleop, or autonomous (although using schedules is usually preferred).
- You can also get the `Alliance` (`Red`, `Blue`, or `Unknown`), and the `AllianceStation` (`Red1`, `Red2`, `Blue1`, etc).
- Lastly there is the `Model` enum, which is either `Simulation` or `Competition`.

All these are added when the state is created, before the `Init` schedule (besides `Mode`, which will be `None`, but you can assume the robot will be disabled).
