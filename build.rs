use std::fs::File;
use std::io::{Cursor, copy};
use std::path::{Path, PathBuf};
use std::{env, fs};

const SO_TARGET_DIR: &str = "libraries/linux/athena/shared";

fn download(url: &str, so: &str) {
    let dir = Path::new(SO_TARGET_DIR);
    if !dir.exists() {
        fs::create_dir_all(dir).unwrap();
    }

    let dest_str = format!("{SO_TARGET_DIR}/{so}");
    let dest = Path::new(&dest_str);
    if dest.exists() {
        return;
    }

    println!("Downloading {}", url);
    let response = reqwest::blocking::get(url).unwrap();
    let bytes = response.bytes().unwrap();
    let mut archive = zip::ZipArchive::new(Cursor::new(bytes)).unwrap();
    for i in 0..archive.len() {
        let mut file = archive.by_index(i).unwrap();
        if file.name().ends_with(".so") {
            let mut out = File::create(&dest).unwrap();
            copy(&mut file, &mut out).unwrap();
            return;
        }
    }
    panic!("Could not find .so file.");
}

fn local(path: &str, so: &str) {
    let dest_str = format!("{SO_TARGET_DIR}/{so}");
    let dest = Path::new(&dest_str);
    if dest.exists() {
        return;
    }

    println!("Copying {}", path);

    let home = home::home_dir().unwrap();
    let from = home.join(path);
    if !from.exists() {
        panic!("Couldn't find file, is wpilib 2026 installed?")
    }
    let bytes = fs::read(from).unwrap();
    let mut archive = zip::ZipArchive::new(Cursor::new(bytes)).unwrap();
    for i in 0..archive.len() {
        let mut file = archive.by_index(i).unwrap();
        if file.name().contains(".so") && !file.name().contains(".so.debug") {
            let mut out = File::create(&dest).unwrap();
            copy(&mut file, &mut out).unwrap();
            return;
        }
    }
    panic!("Could not find .so file.");
}

fn main() -> miette::Result<()> {
    download(
        "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/api-cpp/25.4.0/api-cpp-25.4.0-linuxathena.zip",
        "libCTRE_Phoenix6.so",
    );
    download(
        "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/wpiapi-cpp/25.4.0/wpiapi-cpp-25.4.0-linuxathena.zip",
        "libCTRE_Phoenix6_WPI.so",
    );
    download(
        "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/tools/25.4.0/tools-25.4.0-linuxathena.zip",
        "libCTRE_PhoenixTools.so",
    );

    download(
        "https://maven.revrobotics.com/com/revrobotics/frc/RevLibWpiBackendDriver/2026.0.5/RevLibWpiBackendDriver-2026.0.5-linuxathena.zip",
        "libREVLibWpi.so",
    );
    download(
        "https://maven.revrobotics.com/com/revrobotics/frc/RevLibBackendDriver/2026.0.5/RevLibBackendDriver-2026.0.5-linuxathena.zip",
        "libBackendDriver.so",
    );
    download(
        "https://maven.revrobotics.com/com/revrobotics/frc/REVLib-driver/2026.0.5/REVLib-driver-2026.0.5-linuxathena.zip",
        "libREVLibDriver.so",
    );
    download(
        "https://maven.revrobotics.com/com/revrobotics/frc/REVLib-cpp/2026.0.5/REVLib-cpp-2026.0.5-linuxathena.zip",
        "libREVLib.so",
    );

    local(
        "wpilib/2026/maven/edu/wpi/first/hal/hal-cpp/2026.2.1/hal-cpp-2026.2.1-linuxathena.zip",
        "libwpiHal.so",
    );
    local(
        "/home/carsonetb/wpilib/2026/maven/edu/wpi/first/wpilibc/wpilibc-cpp/2026.2.1/wpilibc-cpp-2026.2.1-linuxathena.zip",
        "libwpilibc.so",
    );
    local(
        "/home/carsonetb/wpilib/2026/maven/edu/wpi/first/wpimath/wpimath-cpp/2026.2.1/wpimath-cpp-2026.2.1-linuxathena.zip",
        "libwpimath.so",
    );
    local(
        "/home/carsonetb/wpilib/2026/maven/edu/wpi/first/wpinet/wpinet-cpp/2026.2.1/wpinet-cpp-2026.2.1-linuxathena.zip",
        "libwpinet.so",
    );
    local(
        "/home/carsonetb/wpilib/2026/maven/edu/wpi/first/wpiutil/wpiutil-cpp/2026.2.1/wpiutil-cpp-2026.2.1-linuxathena.zip",
        "libwpiutil.so",
    );
    local(
        "/home/carsonetb/wpilib/2026/maven/edu/wpi/first/ntcore/ntcore-cpp/2026.2.1/ntcore-cpp-2026.2.1-linuxathena.zip",
        "libntcore.so",
    );
    local(
        "/home/carsonetb/wpilib/2026/maven/edu/wpi/first/ni-libraries/visa/2026.1.2/visa-2026.1.2-linuxathena.zip",
        "libvisa.so",
    );
    local(
        "/home/carsonetb/wpilib/2026/maven/edu/wpi/first/ni-libraries/chipobject/2026.1.2/chipobject-2026.1.2-linuxathena.zip",
        "libRoboRIO_FRC_ChipObject.so.26",
    );
    local(
        "/home/carsonetb/wpilib/2026/maven/edu/wpi/first/ni-libraries/netcomm/2026.1.2/netcomm-2026.1.2-linuxathena.zip",
        "libFRC_NetworkCommunication.so.25",
    );

    let dest_str = format!("{SO_TARGET_DIR}/libNiFpgaLv.so.13");
    let dest = Path::new(&dest_str);
    if !dest.exists() {
        println!(
            "Copying /home/carsonetb/wpilib/2026/maven/edu/wpi/first/ni-libraries/runtime/2026.1.2/runtime-2026.1.2-linuxathena.zip"
        );

        let home = home::home_dir().unwrap();
        let from = home.join("/home/carsonetb/wpilib/2026/maven/edu/wpi/first/ni-libraries/runtime/2026.1.2/runtime-2026.1.2-linuxathena.zip");
        if !from.exists() {
            panic!("Couldn't find file, is wpilib 2026 installed?")
        }
        let bytes = fs::read(from).unwrap();
        let mut archive = zip::ZipArchive::new(Cursor::new(bytes)).unwrap();
        for i in 0..archive.len() {
            let mut file = archive.by_index(i).unwrap();
            if file.name() == "libfpgalvshim.so" {
                let mut out = File::create(&dest).unwrap();
                copy(&mut file, &mut out).unwrap();
            }
            if file.name() == "libembcanshim.so" {
                let mut out =
                    File::create(&format!("{SO_TARGET_DIR}/libnirio_emb_can.so.23")).unwrap();
                copy(&mut file, &mut out).unwrap();
            }
        }
    }

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
        .flag_if_supported("-Wno-psabi")
        .compile("ctre_bindings");

    Ok(())
}
