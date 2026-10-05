use std::env;
use std::path::PathBuf;

fn main() -> miette::Result<()> {
    let include_path = PathBuf::from("include");

    println!("cargo:rustc-link-search=native=libraries/linux/athena/shared");
    println!("cargo:rustc-link-arg=-Wl,-rpath-link=libraries/linux/athena/shared");

    println!("cargo:rustc-link-lib=dylib=wpiHal");
    println!("cargo:rustc-link-lib=dylib=wpiutil");
    println!("cargo:rustc-link-lib=dylib=ntcore");

    println!("cargo:rustc-link-lib=dylib=CTRE_Phoenix6_WPI");
    println!("cargo:rustc-link-lib=dylib=CTRE_PhoenixTools");

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

    // Build CTRE bindings
    let mut builder = autocxx_build::Builder::new("src/ffi.rs", &[&include_path])
        .extra_clang_args(&["--target=aarch64-linux-gnu", "-std=c++20"])
        .build()?;

    builder
        .flag_if_supported("-std=c++20")
        .compile("ctre_bindings");

    Ok(())
}
