use crate::{Robot, Scheduler, State};

pub trait System<R: Robot>: Sized {
    fn init(&mut self, state: &mut State<R>) {
        let _ = state;
    }
    fn disabled_init(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }
    fn teleop_init(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }
    fn autonomous_init(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }
    fn test_init(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }

    fn disabled_exit(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }
    fn teleop_exit(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }
    fn autonomous_exit(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }
    fn test_exit(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }

    fn periodic(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }
    fn disabled_periodic(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }
    fn autonomous_periodic(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }
    fn teleop_periodic(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }
    fn test_periodic(&mut self, scheduler: &mut Scheduler<Self>) {
        let _ = scheduler;
    }
}
