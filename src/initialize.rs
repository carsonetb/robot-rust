use std::{
    fmt::Debug,
    ops::{Deref, DerefMut},
};

#[derive(Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum Initialize<T> {
    Uninitialized,
    Initialized(T),
}

impl<T> Initialize<T> {
    pub fn init(&mut self, value: T) {
        *self = Initialize::Initialized(value)
    }
}

impl<T> DerefMut for Initialize<T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        match self {
            Self::Uninitialized => panic!("Uninitialized value."),
            Self::Initialized(value) => value,
        }
    }
}

impl<T> Deref for Initialize<T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        match self {
            Self::Uninitialized => panic!("Uninitialized value."),
            Self::Initialized(value) => value,
        }
    }
}

impl<T: Debug> Debug for Initialize<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.write_str(&format!("{:?}", **self))
    }
}
