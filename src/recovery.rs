use std::backtrace::Backtrace;

extern "C" fn signal_handler(sig: libc::c_int) {
    let sig_name = match sig {
        libc::SIGSEGV => "SIGSEGV (Segmentation Fault)",
        libc::SIGBUS => "SIGBUS (Bus Error / Misaligned Memory)",
        libc::SIGABRT => "SIGABRT (C++ Abort / Uncaught Exception)",
        libc::SIGILL => "SIGILL (Illegal Instruction)",
        _ => "Unknown Signal",
    };

    eprintln!("\n====================================");
    eprintln!("FATAL CRASH: {sig_name}; Signal {sig}.");
    eprintln!("Sorry about this! This probably indicates a bug with the C/C++ bindings.");
    eprintln!("This bug should be reported.");
    eprintln!(
        "If you're at a competition, try to run the program once more, and if it fails switch to a backup."
    );
    eprintln!("====================================\n\n");

    let bt = Backtrace::force_capture();
    eprintln!("{bt}");

    std::process::exit(128 + sig);
}

#[allow(function_casts_as_integer)]
pub fn install_signal_handler() {
    unsafe {
        libc::signal(libc::SIGSEGV, signal_handler as libc::sighandler_t);
        libc::signal(libc::SIGBUS, signal_handler as libc::sighandler_t);
        libc::signal(libc::SIGABRT, signal_handler as libc::sighandler_t);
        libc::signal(libc::SIGILL, signal_handler as libc::sighandler_t);
    }
}
