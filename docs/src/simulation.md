# Simulation

Traditionally, robots use seperate code for competition and simulation in their subsystems. Usually, the differences are abstracted by an "IO" class, which has a competition and simulation implementation, but is used the same way by the subsystem either way. 

Here, we take that a step further by abstracting the differences away into the hardware types themselves (the motors, gyros, etc) so that robot code is exactly the same in competition and simulation. 

Under the hood, hardware types take their inputs (set speed, set voltage), and send them to the simulator when their `simulate` method is called. The simulator runs after all robot code, and during the next call to `simulate` the simulator's outputs (position, velocity, supply voltage) are passed back into the hardware. The `simulate` function is called in both competition and simulation, but does nothing in competition.

The code that actually simulates the robot (called a simulation runtime) can be anything. This library provides a `BasicRuntime`, which simulates the robot using basic WPILib-style motor simulations. You can apply any runtime that implements `SimRuntime` to the state like so:

```rust
fn main() {
    let mut state: State = State::new().unwrap();
    state.set_runtime(BasicRuntime);
}
```

You may have seen that many of the examples call this function so that they'll work when tested on desktop.

Other runtimes will have to be written yourself (they are relatively simple to develop), or provided by other crates. I also created a [runtime for MuJoCo](https://github.com/carsonetb/mjfrc). If you want to see examples for writing your own runtime, you can look in `sim::runtime` or at the aforementioned crate.

## Driver Station in Simulation

Right now the simulator only has a fairly crude driver station GUI, because the current FRC Driver Station only works on Windows. When the 2027 versions of WPILib are stabilized, I will remove the custom GUI and add compatibility with the new Driver Station which works on Windows, MacOS, and Linux.
