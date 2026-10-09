use crate::{Robot, Scheduler, State};

pub trait System<R: Robot>: Sized {
    fn init(&mut self, state: &mut State<R>) {
        let _ = state;
    }
    fn disabled_init(&mut self, scheduler: &mut Scheduler<Self>) {}
    fn teleop_init(&mut self, scheduler: &mut Scheduler<Self>) {}
    fn autonomous_init(&mut self, scheduler: &mut Scheduler<Self>) {}
    fn test_init(&mut self, scheduler: &mut Scheduler<Self>) {}

    fn disabled_exit(&mut self, scheduler: &mut Scheduler<Self>) {}
    fn teleop_exit(&mut self, scheduler: &mut Scheduler<Self>) {}
    fn autonomous_exit(&mut self, scheduler: &mut Scheduler<Self>) {}
    fn test_exit(&mut self, scheduler: &mut Scheduler<Self>) {}

    fn periodic(&mut self, scheduler: &mut Scheduler<Self>) {}
    fn disabled_periodic(&mut self, scheduler: &mut Scheduler<Self>) {}
    fn autonomous_periodic(&mut self, scheduler: &mut Scheduler<Self>) {}
    fn teleop_periodic(&mut self, scheduler: &mut Scheduler<Self>) {}
    fn test_periodic(&mut self, scheduler: &mut Scheduler<Self>) {}
}
