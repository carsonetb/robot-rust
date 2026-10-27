use std::fs::File;
use std::io::{Cursor, copy};
use std::path::{Path, PathBuf};
use std::{env, fs};

const SO_TARGET_DIR: &str = "libraries/linux/athena/shared";

fn download(url: &str, so: &str, extension: &str) {
    let dir = &Path::new(&env::var("OUT_DIR").unwrap()).join(SO_TARGET_DIR);
    if !dir.exists() {
        fs::create_dir_all(dir).unwrap();
    }

    let dest_str = format!("{}/{so}", dir.to_str().unwrap());
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
        if file.name().ends_with(&format!(".{extension}")) {
            let mut out = File::create(&dest).unwrap();
            copy(&mut file, &mut out).unwrap();
            return;
        }
    }
    panic!("Could not find .{extension} file.");
}

fn local(path: &str, so: &str, extension: &str) {
    let dir = Path::new(&env::var("OUT_DIR").unwrap()).join(SO_TARGET_DIR);
    let dest_str = format!("{}/{so}", dir.to_str().unwrap());
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
        if file.name().contains(&format!(".{extension}")) && !file.name().contains(&format!(".{extension}.debug")) {
            let mut out = File::create(&dest).unwrap();
            copy(&mut file, &mut out).unwrap();
            return;
        }
    }
    panic!("Could not find .{extension} file.");
}

fn main() -> miette::Result<()> {
    let target = env::var("TARGET").unwrap();
    let target_os = env::var("CARGO_CFG_TARGET_OS").unwrap();
    let is_roborio = target == "arm-unknown-linux-gnueabi";
    let classifier = if is_roborio {
        "linuxathena"
    } else {
        if target_os == "linux" {
            "linuxx86-64"
        } else if target_os == "macos" {
            "osxuniversal"
        } else {
            "linuxx86-64"
        }
    };
    let extension = if target_os == "linux" {
        "so"
    } else if target_os == "macos" {
        "dylib"
    } else {
        "so"
    };

    println!("cargo::rustc-check-cfg=cfg(simulation)");
    if !is_roborio {
        println!("cargo:rustc-cfg=simulation");
    }

    if is_roborio {
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/api-cpp/26.3.0/api-cpp-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_Phoenix6.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/wpiapi-cpp/26.3.0/wpiapi-cpp-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_Phoenix6_WPI.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/tools/26.3.0/tools-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_PhoenixTools.{extension}"),
            extension,
        );
    } else {
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/wpiapi-cpp-sim/26.3.0/wpiapi-cpp-sim-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_Phoenix6_WPISim.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/tools-sim/26.3.0/tools-sim-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_PhoenixTools_Sim.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/simTalonSRX/26.3.0/simTalonSRX-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_SimTalonSRX.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/simVictorSPX/26.3.0/simVictorSPX-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_SimVictorSPX.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/simPigeonIMU/26.3.0/simPigeonIMU-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_SimPigeonIMU.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/simProTalonFX/26.3.0/simProTalonFX-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_SimProTalonFX.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/simProTalonFXS/26.3.0/simProTalonFXS-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_SimProTalonFXS.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/simProCANcoder/26.3.0/simProCANcoder-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_SimProCANcoder.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/simProPigeon2/26.3.0/simProPigeon2-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_SimProPigeon2.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/simProCANrange/26.3.0/simProCANrange-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_SimProCANrange.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/simProCANdi/26.3.0/simProCANdi-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_SimProCANdi.{extension}"),
            extension,
        );
        download(
            &format!(
                "https://maven.ctr-electronics.com/release/com/ctre/phoenix6/sim/simProCANdle/26.3.0/simProCANdle-26.3.0-{classifier}.zip"
            ),
            &format!("libCTRE_SimProCANdle.{extension}"),
            extension,
        );
    }

    download(
        &format!(
            "https://maven.revrobotics.com/com/revrobotics/frc/RevLibWpiBackendDriver/2026.0.5/RevLibWpiBackendDriver-2026.0.5-{classifier}.zip"
        ),
        &format!("libREVLibWpi.{extension}"),
        extension,
    );
    download(
        &format!(
            "https://maven.revrobotics.com/com/revrobotics/frc/RevLibBackendDriver/2026.0.5/RevLibBackendDriver-2026.0.5-{classifier}.zip"
        ),
        &format!("libBackendDriver.{extension}"),
        extension,
    );
    download(
        &format!(
            "https://maven.revrobotics.com/com/revrobotics/frc/REVLib-driver/2026.0.5/REVLib-driver-2026.0.5-{classifier}.zip"
        ),
        &format!("libREVLibDriver.{extension}"),
        extension,
    );
    download(
        &format!(
            "https://maven.revrobotics.com/com/revrobotics/frc/REVLib-cpp/2026.0.5/REVLib-cpp-2026.0.5-{classifier}.zip"
        ),
        &format!("libREVLib.{extension}"),
        extension,
    );

    local(
        &format!(
            "wpilib/2026/maven/edu/wpi/first/hal/hal-cpp/2026.2.1/hal-cpp-2026.2.1-{classifier}.zip"
        ),
        &format!("libwpiHal.{extension}"),
        extension,
    );
    local(
        &format!(
            "wpilib/2026/maven/edu/wpi/first/wpilibc/wpilibc-cpp/2026.2.1/wpilibc-cpp-2026.2.1-{classifier}.zip"
        ),
        &format!("libwpilibc.{extension}"),
        extension,
    );
    local(
        &format!(
            "wpilib/2026/maven/edu/wpi/first/wpimath/wpimath-cpp/2026.2.1/wpimath-cpp-2026.2.1-{classifier}.zip"
        ),
        &format!("libwpimath.{extension}"),
        extension,
    );
    local(
        &format!(
            "wpilib/2026/maven/edu/wpi/first/wpinet/wpinet-cpp/2026.2.1/wpinet-cpp-2026.2.1-{classifier}.zip"
        ),
        &format!("libwpinet.{extension}"),
        extension,
    );
    local(
        &format!(
            "wpilib/2026/maven/edu/wpi/first/wpiutil/wpiutil-cpp/2026.2.1/wpiutil-cpp-2026.2.1-{classifier}.zip"
        ),
        &format!("libwpiutil.{extension}"),
        extension,
    );
    local(
        &format!(
            "wpilib/2026/maven/edu/wpi/first/ntcore/ntcore-cpp/2026.2.1/ntcore-cpp-2026.2.1-{classifier}.zip"
        ),
        &format!("libntcore.{extension}"),
        extension,
    );
    if is_roborio {
        local(
            &format!(
                "wpilib/2026/maven/edu/wpi/first/ni-libraries/visa/2026.1.2/visa-2026.1.2-{classifier}.zip"
            ),
            &format!("libvisa.{extension}"),
            extension,
        );
        local(
            &format!(
                "wpilib/2026/maven/edu/wpi/first/ni-libraries/chipobject/2026.1.2/chipobject-2026.1.2-{classifier}.zip"
            ),
            &format!("libRoboRIO_FRC_ChipObject.{extension}"),
            extension,
        );
        local(
            &format!(
                "wpilib/2026/maven/edu/wpi/first/ni-libraries/netcomm/2026.1.2/netcomm-2026.1.2-{classifier}.zip"
            ),
            &format!("libFRC_NetworkCommunication.{extension}"),
            extension,
        );

        let dir = Path::new(&env::var("OUT_DIR").unwrap()).join(SO_TARGET_DIR);
        let dest = dir.join("libNiFpgaLv.so");
        if !dest.exists() {
            let home = home::home_dir().unwrap();
            let from = home.join(
            &format!("wpilib/2026/maven/edu/wpi/first/ni-libraries/runtime/2026.1.2/runtime-2026.1.2-{classifier}.zip"),
        );
            if !from.exists() {
                panic!("Couldn't find file, is wpilib 2026 installed?");
            }
            let bytes = fs::read(from).unwrap();
            let mut archive = zip::ZipArchive::new(Cursor::new(bytes)).unwrap();
            for i in 0..archive.len() {
                let mut file = archive.by_index(i).unwrap();
                if file.name().ends_with("libfpgalvshim.so") {
                    let mut out = File::create(&dest).unwrap();
                    copy(&mut file, &mut out).unwrap();
                }
                if file.name().ends_with("libembcanshim.so") {
                    let mut out = File::create(dir.join("libnirio_emb_can.so")).unwrap();
                    copy(&mut file, &mut out).unwrap();
                }
            }
        }
    }

    println!("cargo:rerun-if-changed=src/ffi.rs");
    println!("cargo:rerun-if-changed=include");
    println!("cargo:rerun-if-changed=wrapper.h");

    let target = if is_roborio {
        "arm-linux-gnueabi"
    } else {
        "x86_64-linux-gnu"
    };
    let bindings = bindgen::Builder::default()
        .header("wrapper.h")
        .clang_arg("-Iinclude")
        .clang_arg(&format!("--target={target}"))
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

    let (arg1, arg2, arg3, arg4) = (
        format!(
            "--sysroot={}/wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot",
            home
        ),
        format!(
            "-isystem{}/wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot/usr/include/c++/12",
            home
        ),
        format!(
            "-isystem{}/wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot/usr/include/c++/12/arm-nilrt-linux-gnueabi",
            home
        ),
        format!(
            "-isystem{}/wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot/usr/include",
            home
        ),
    );

    let mut clang_args = vec!["-std=c++20"];
    if is_roborio {
        clang_args.push("--target=arm-linux-gnueabi");
        clang_args.push(&arg1);
        clang_args.push(&arg2);
        clang_args.push(&arg3);
        clang_args.push(&arg4);
    }

    let include_path = PathBuf::from("include");
    let mut builder = autocxx_build::Builder::new("src/ffi.rs", &[&include_path])
        .extra_clang_args(dbg!(&clang_args))
        .build()?;

    builder
        .file("include/rev_helpers.cpp")
        .file("include/chooser_helpers.cpp")
        .flag_if_supported("-std=c++20")
        .flag_if_supported("-Wno-deprecated-declarations")
        .flag_if_supported("-Wno-psabi")
        .warnings(false)
        .compile("ctre_bindings");

    let out_dir = env::var("OUT_DIR").unwrap();
    println!("cargo:rustc-link-search=native={out_dir}/{SO_TARGET_DIR}");
    if is_roborio {
        println!(
            "cargo:rustc-link-search=native={home}/wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot/usr/lib"
        );
        println!(
            "cargo:rustc-link-search=native={home}/wpilib/2026/roborio/arm-nilrt-linux-gnueabi/sysroot/lib"
        );
    }
    if is_roborio {
        println!("cargo:rustc-link-lib=dylib=CTRE_Phoenix6_WPI");
        println!("cargo:rustc-link-lib=dylib=CTRE_Phoenix6");
    } else {
        println!("cargo:rustc-link-lib=dylib=CTRE_Phoenix6_WPISim");
    }
    if is_roborio {
        println!("cargo:rustc-link-lib=dylib=CTRE_PhoenixTools");
    } else {
        println!("cargo:rustc-link-lib=dylib=CTRE_PhoenixTools_Sim");
    }
    println!("cargo:rustc-link-lib=dylib=REVLib");
    println!("cargo:rustc-link-lib=dylib=REVLibWpi");
    println!("cargo:rustc-link-lib=dylib=REVLibDriver");
    println!("cargo:rustc-link-lib=dylib=BackendDriver");

    println!("cargo:rustc-link-lib=dylib=wpilibc");
    println!("cargo:rustc-link-lib=dylib=wpimath");
    println!("cargo:rustc-link-lib=dylib=ntcore");
    println!("cargo:rustc-link-lib=dylib=wpinet");
    println!("cargo:rustc-link-lib=dylib=wpiHal");
    println!("cargo:rustc-link-lib=dylib=wpiutil");

    if is_roborio {
        println!("cargo:rustc-link-lib=dylib=RoboRIO_FRC_ChipObject");
        println!("cargo:rustc-link-lib=dylib=FRC_NetworkCommunication");
        println!("cargo:rustc-link-lib=dylib=visa");
        println!("cargo:rustc-link-lib=dylib=NiFpgaLv");
        println!("cargo:rustc-link-lib=dylib=nirio_emb_can");
    }

    Ok(())
}
