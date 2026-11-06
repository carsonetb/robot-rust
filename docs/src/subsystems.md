# Subsystem Design

In Java and C++, the choice of how to encapsulate different systems on the robot was largely made up for you: Implement the `Subsystem` interface, and register commands on that subsystem. In Rust, that decision is completely yours, and truly it is. If you have a design you think would work better for your robot or for your team, by all means skip this chapter. Here, I will layout a design you can use that is both similar to the old framework, but still elegant and functional within the new.

With that said, the first type that almost all subsystem designs have is the one that contains the hardware interface, like motors and encoders. This type will be private, so no other subsystems directly interface with it. For this section, we'll use an intake subsystem as an example:

```Rust
// In intake.rs, seperate file from main.rs

struct Intake {
    motor: TalonFX,
    pivot_motor: TalonFX,
    encoder: CANcoder,
}

impl Intake {
    fn new() -> Self {
        // Code to do this not specified ...
    }
}
```

We will then define another type, `IntakeTargets`, that will be public. The intake subsystem will be responsible for getting the physical hardware to these targets. Any other code will be able to modify these targets, so you should make sure multiple peices of code aren't modifying it at the same time. Checks in the Commands system are planned to make sure this doesn't happen, but do not yet exist. 

For the intake, our targets specify the pivot position and the intake state.

```Rust
pub enum IntakeState {
    Stopped,
    Intake,
    Outtake,
}

pub enum PivotState {
    Stowed,
    Extended,
}

pub struct IntakeTargets {
    pub intake: IntakeState,
    pub pivot: PivotState,
}

impl IntakeTargets {
    pub fn new() -> Self {
        Self {
            intake: IntakeState::Stopped,
            pivot: PivotState::Stowed,
        }
    }
}
```

We'll then create some function that reads the targets and modifies the hardware:

```rust
fn periodic(mut intake: ResourceMut<Intake>, targets: Resource<IntakeTargets>) {
    // Code to do this not specified ...
}
```

We are already almost finished making our Subsystem. We just need a function that can be called from `main.rs` that inserts the `Intake` and `IntakeTargets` resources and adds the `periodic` system:

```rust
pub fn setup(state: &mut State) {
    state.insert_resource(Intake::new());
    state.insert_resource(IntakeTargets::new());

    // Make sure to add the system in both teleop and autonomous.
    state.add_systems(TeleopPeriodic, periodic);
    state.add_systems(AutonomousPeriodic, periodic);
}
```

Now we have a usable Subsystem. We can call the setup from the `main` function:

```rust
// main.rs

mod intake;

fn main() {
    // ...
    intake::setup(&mut state);
    state.run();
}
```

## Subsystem commands

Up until this point, we've ignored the use of commands with Subsystems. For this, depending on the complexity of the subsystem, you have two options. If the subsystem is relatively simple, like the intake we wrote earlier, you can replace the targets with a few commands (`Intake`, `Outtake`, `Stow`, and `Extend`, for example), and have the command handlers directly interface with the hardware. For more complex subsystems (like a drivetrain), it will probably make more sense for commands to interface with a targets type, which would be in turn handled by something like the `periodic` function we wrote earlier.
