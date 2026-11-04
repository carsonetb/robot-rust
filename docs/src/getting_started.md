# Getting Started

All you need installed is WPILib. If it's already installed it should appear in your home directory. You can follow the official guide [here](https://docs.wpilib.org/en/stable/docs/zero-to-robot/step-2/wpilib-setup.html). This library officially supports Linux and MacOS, and Windows support is planned.

You will also need to add the WPILib compiler toolchain to your PATH. On Mac and Linux, you have to add some code to the `.zshrc` or `.bashrc` file in your home directory. Open it in a text editor and add this line to the end:

```bash
export PATH="[home directory here]/wpilib/2026/roborio/bin:$PATH"
```

> [!WARNING]
> The home directory cannot be `~`, it must be `/Users/username` on Mac or `/home/username` on Linux.

Thirdly, you will need to install the Rust target for the roboRIO. To do this, you will need [rustup](https://rustup.rs/) installed. Then, run:

```bash
rustup target add arm-unknown-linux-gnueabi
```

## Project setup

Let's create a new project. You can call it whatever you want, but I'm going to call it `robot`. In the directory you want your project directory to go in, run:

```Bash
$ cargo new robot
```

Next, `cd` into the project directory and add the `robot-rust` crate (you don't have to rename it, but it will save you some typing in the future):

```Bash
$ cd robot
$ cargo add robot-rust --rename frc
```

You can now open up the `src/main.rs` file that Cargo generated. You should see the typical "Hello, World" main function. This would be enough if we were running it on our own computer, but we need more code to run it on the robot! First, import the `robot-rust` prelude:

```Rust
use frc::prelude::*;
```

Virtually every type and function you will ever need to use gets imported with the prelude. CTRE and REV each have their own preludes, though.

Now, we need to create a new `State`. In the main function, you will configure this state and then run it. The state is what holds all the resources and systems that you create for your project.

```Rust
fn main() {
    let mut state: State = State::new().unwrap();
}
```

Now, we have to create a system that will run when the robot program starts. Later we'll learn exactly what a system is, but for now just think of it as a function. Outside of `main`, add:

```Rust
fn hello_robot() {
    println!("Hello, Robot!");
}
```

We then give this to `state`, which will handle running it at the right time, and run the program:

```Rust
fn main() {
    // ...
    state.add_systems(Init, hello_robot);
    state.run();
}
```

## Viewing the full code

Each chapter where you learn to write code has a corresponding file in the [examples directory](https://github.com/carsonetb/robot-rust/tree/trunk/examples) on GitHub. For example, this chapter's example is called `hello_robot.rs`.

> [!NOTE]
> In example code the library is not renamed, so it is still `robot_rust` instead of `frc`.

## Deploying code

Provided is a `deploy.sh` script that will automatically build and deploy the program to your robot. You can find it in the [GitHub repository](https://github.com/carsonetb/robot-rust). Download it and put it in your project directory, and run the following command to make it executable:

```Bash
$ chmod +x deploy.sh
```

Use your perferred text editor to open `deploy.sh`

You will need to edit the variables set in the program:

- Update `PROJECT_NAME` to be the name of your project (in this case we called it `robot`).
- Update `TEAM` to be your team number
- Update `ROBOT_IP` to be the IP address of the roboRIO when it is connected to your computer. If the script fails, it is most likely that this is wrong or the robot isn't connected properly. You can run `ping IP_HERE` to test if the address is working.

Once these variables are set properly, save `deploy.sh`. You can run the deploy script, which will handle building, deploying, and running the robot program on the RIO.

```Bash
$ ./deploy.sh
```

If this works, the easiest way to see that the code ran is by looking in the DriverStation. Otherwise, if you know how you can look at the log file on the RIO.

## Viewing documentation

This documentation should be enough to get you understanding everything, but sometimes you need a more specific reference. For various reasons, the docs on [docs.rs](https://docs.rs) can't build, so you need to generate them locally like so:

```Bash
$ cargo doc --package robot-rust --open
```

This will open the documentation in your browser.
