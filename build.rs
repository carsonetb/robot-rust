use std::env;
use std::path::PathBuf;

fn main() -> miette::Result<()> {
    let include_path = PathBuf::from("include");

    println!("cargo:rustc-link-search=native=libraries/linux/athena/shared");
    println!(
        "cargo:rustc-link-arg=-Wl,-rpath-link=libraries/linux/athena/shared:wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot/usr/lib:wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot/lib"
    );

    println!("cargo:rustc-link-arg=-Wl,--no-as-needed");
    println!("cargo:rustc-link-arg=-lwpiHal");
    println!("cargo:rustc-link-arg=-lwpiutil");
    println!("cargo:rustc-link-arg=-lwpimath");
    println!("cargo:rustc-link-arg=-lntcore");
    println!("cargo:rustc-link-arg=-lCTRE_PhoenixTools");
    println!("cargo:rustc-link-arg=-lCTRE_Phoenix6");
    println!("cargo:rustc-link-arg=-lCTRE_Phoenix6_WPI");
    println!("cargo:rustc-link-arg=-lREVLib");
    println!("cargo:rustc-link-arg=-lREVLibDriver");
    println!("cargo:rustc-link-arg=-Wl,--as-needed");

    println!("cargo:rerun-if-changed=src/ffi.rs");
    println!("cargo:rerun-if-changed=include");

    // Build HAL and C libraries
    println!("cargo:rerun-if-changed=wrapper.h");

    let bindings = bindgen::Builder::default()
        .header("wrapper.h")
        .clang_arg("-Iinclude")
        .clang_arg("--target=arm-linux-gnueabi")
        .parse_callbacks(Box::new(bindgen::CargoCallbacks::new()))
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");

    let home = env::var("HOME")
        .or_else(|_| env::var("USERPROFILE"))
        .unwrap();

    // Build CTRE bindings
    let mut builder = autocxx_build::Builder::new("src/ffi.rs", &[&include_path])
        .extra_clang_args(&[
            "--target=arm-linux-gnueabi",
            "-std=c++20",
            &format!("--sysroot={}/wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot", home),
            &format!("-isystem{}/wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot/usr/include/c++/12", home),
            &format!("-isystem{}/wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot/usr/include/c++/12/arm-nilrt-linux-gnueabi", home),
            &format!("-isystem{}/wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot/usr/include", home),
        ])
        .build()?;

    builder
        .file("include/rev_helpers.cpp")
        .flag_if_supported("-std=c++20")
        .flag_if_supported("-Wno-deprecated-declarations")
        .compile("ctre_bindings");

    Ok(())
}
