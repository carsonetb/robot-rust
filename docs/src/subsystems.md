# Subsystem Design

In Java and C++, the choice of how to encapsulate different systems on the robot was largely made up for you: Implement the `Subsystem` interface, and register commands on that subsystem. In Rust, that decision is completely yours, and truly it is. If you have a design you think would work better for your robot or for your team, by all means skip this chapter. Here, I will layout a design you can use that is both similar to the old framework, but still elegant and functional within the new.

With that said, the first type that almost all subsystem designs have is the one that contains the hardware interface, like motors and encoders. This type will be private, so no other subsystems directly interface with it. For this section, we'll use an intake subsystem as an example:

```Rust
struct Intake {
    motor: TalonFX,
    pivot_motor: TalonFX,
    encoder: CANcoder,
}
```
