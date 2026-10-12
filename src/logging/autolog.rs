use crate::prelude::*;

pub trait AutoLog {
    fn append_to(self, logger: &mut Logger, path: &str);
}

impl<T: Loggable> AutoLog for T {
    fn append_to(self, logger: &mut Logger, path: &str) {
        logger.append_value(path, self);
    }
}
