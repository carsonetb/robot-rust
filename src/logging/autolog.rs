use crate::prelude::*;

/// Trait for types that are structs of multiple [`Loggable`] types.
///
/// You can automatically implement this using the derive macro of the same
/// name.
pub trait AutoLog {
    /// Append this value to the logger at the path. Subpaths may be used.
    fn append_to(self, logger: &mut Logger, path: &str);
}

impl<T: Loggable> AutoLog for T {
    fn append_to(self, logger: &mut Logger, path: &str) {
        logger.append_value(path, self);
    }
}
