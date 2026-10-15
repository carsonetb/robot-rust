# Systems, Resources, and Schedules

This project manages everything using an ECS, which stands for _Entity Component System_.
We will learn more later about the purpose of Entities and Components, but for now we only need to know how Systems work.

A system is an abstract concept. It is anything that takes some inputs, and modifies some of those inputs. In our case, this abstraction is realised in the form of _functions_. You saw an example of a system called `hello_world` in the previous chapter, although this one took no inputs. In reality, systems can (and usually do) take many inputs and many types of inputs. The most common input you will be using is called a Resource.

## Resources

Any type can be a resource. There can only be one resource per type (put simply, there can't be more than one `Intake` resource), and they must be instantiated when the program starts. If you've done some FRC programming before, this might ring some bells. A singleton object instantiated at the start of the program? Why, that's the same as a Subsystem! And, indeed, we do use Resources for Subsystems.

## Creating a resource

For now, let's just create a resource that wraps a single motor. We'll derive `Deref` and `DerefMut` so that we can interact with the type as if it was just a motor.

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

## Using a resource

The resource can now be used in a system. All resource arguments to a system need to be wrapped in either the `Resource` or `ResourceMut` type. For example, we'll create a system called `spin` that will spin `MyMotor`:

```Rust
fn spin(mut motor: ResourceMut<MyMotor>) {
    motor.set_voltage(5.0.volts());
}
```

The `volts` function is provided by the library so you can easily create unit-ed types. We use it because `TalonFX::set_voltage` requires a `Voltage` (or `ElectricPotential`) type.

## Schedules

In the previous chapter, we wrote `state.add_systems(Init, hello_robot)`. `Init` is a schedule, which specifies _when_ a system should be ran. There are a lot of different schedules:

- `Init`: Runs when the robot program starts
- `DisabledInit`/`TeleopInit`/`AutonomousInit`/`TestInit`: Runs when a certain state of the robot program starts.
- `DisabledExit`/`TeleopExit`/`AutonomousExit`/`TestExit`: Runs when a certain state of the robot program ends.
- `Periodic`: Runs every ~20ms.
- `DisabledPeriodic`/`TeleopPeriodic`/`AutonomousPeriodic`/`TestPeriodic`: Runs every ~20ms during a certain stage of the robot program.

For our purposes, we will use the `TeleopPeriodic` schedule to spin our motor. So after registering the resource, we can register the system like so:

```Rust
state.add_systems(TeleopPeriodic, spin);
```

Now, you should have a spinning motor!
