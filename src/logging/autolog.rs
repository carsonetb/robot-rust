use crate::logging::Logger;

pub trait AutoLog {
    fn append_to(&self, logger: &mut Logger, path: &str);
}

impl AutoLog for f64 {
    fn append_to(&self, logger: &mut Logger, path: &str) {
        logger.append_value(path, *self);
    }
}
