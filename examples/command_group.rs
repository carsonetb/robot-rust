use robot_rust::{ctre::TalonFXMotorType, prelude::*};

struct Shooter {
    flywheel: TalonFX,
    feeder: TalonFX,
}

impl Shooter {
    fn new() -> Self {
        Self {
            flywheel: TalonFX::new(0, "*").with_simulation_params(
                TalonFXMotorType::KrakenX60FOC,
                1.0,
                0.001.moment_of_inertia(),
            ),
            feeder: TalonFX::new(1, "*").with_simulation_params(
                TalonFXMotorType::KrakenX60FOC,
                1.0,
                0.001.moment_of_inertia(),
            ),
        }
    }
}

struct ShootCommand;
struct FeedCommand;

fn periodic(mut controller: ResourceMut<XboxController>) {
    controller.simulate();
}

fn shoot(shoot: Command<ShootCommand>, mut shooter: ResourceMut<Shooter>) {
    if shoot.enabled() {
        println!(
            "shoot {}",
            shooter
                .flywheel
                .get_velocity()
                .get::<revolution_per_second>()
        );
        shooter.flywheel.set_voltage(12.0.volts());
    }

    if shoot.just_ended() {
        shooter.flywheel.set_voltage(0.0.volts());
    }

    shooter.flywheel.simulate();
}

fn at_desired_velocity(shooter: Resource<Shooter>) -> bool {
    shooter.flywheel.get_velocity() > 100.0.rotations_per_second()
}

fn feed(feed: Command<FeedCommand>, mut shooter: ResourceMut<Shooter>) {
    if feed.enabled() {
        println!("feed");
        shooter.feeder.set_voltage(5.0.volts());
    }

    if feed.just_ended() {
        shooter.feeder.set_voltage(0.0.volts());
    }

    shooter.feeder.simulate();
}

fn main() {
    let mut state: State = State::new().unwrap();
    state.set_runtime(BasicRuntime);

    state.insert_resource(Shooter::new());
    state.insert_resource(XboxController::new(0));

    state.add_systems(Periodic, periodic);

    state
        .register_command(ShootCommand)
        .with_handler(Periodic, shoot);
    state
        .register_command(FeedCommand)
        .with_handler(Periodic, feed);

    command!(state, ShootUntilSpunUp: Just(ShootCommand).until_trigger(at_desired_velocity));
    command!(state, ShootAndFeed: Parallel(ShootCommand, FeedCommand));
    command!(state, ShootSequence: Sequence(ShootUntilSpunUp, ShootAndFeed).with_trigger(XboxController::a_trigger));

    state.run();
}
