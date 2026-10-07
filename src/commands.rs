use crate::Robot;

pub trait Command<T: Robot> {
    fn initialize(&mut self, robot: &mut T);
    fn execute(&mut self, robot: &mut T);
    fn is_finished(&mut self, robot: &mut T) -> bool;
    fn end(&mut self, robot: &mut T, interrupted: bool);
}
