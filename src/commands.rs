pub(crate) struct Scheduler<T> {
    commands: Vec<Box<dyn Command<T>>>,
}

impl<T> Scheduler<T> {
    pub(crate) fn new() -> Self {
        Self {
            commands: Vec::new(),
        }
    }

    pub(crate) fn schedule(&mut self, mut command: impl Command<T> + 'static, system: &mut T) {
        command.initialize(system);
        self.commands.push(Box::new(command));
    }

    pub(crate) fn periodic(&mut self, system: &mut T) {
        self.commands.retain_mut(|command| {
            let out = if command.is_finished(system) {
                command.end(system, false);
                false
            } else {
                true
            };
            command.execute(system);
            out
        });
    }
}

type CommandFn<T> = Box<dyn FnMut(&mut T)>;

pub trait Command<T> {
    fn initialize(&mut self, system: &mut T) {
        let _ = system;
    }
    fn execute(&mut self, system: &mut T) {
        let _ = system;
    }
    fn is_finished(&mut self, system: &mut T) -> bool;
    fn end(&mut self, system: &mut T, interrupted: bool);
}

pub fn run<T>(function: impl FnMut(&mut T) + 'static) -> impl Command<T> {
    Run {
        ended: false,
        function: Box::new(function),
    }
}

pub fn run_end<T>(
    run: impl FnMut(&mut T) + 'static,
    end: impl FnMut(&mut T) + 'static,
) -> impl Command<T> {
    RunEnd {
        ended: false,
        run: Box::new(run),
        end: Box::new(end),
    }
}

struct Run<T> {
    ended: bool,
    function: Box<dyn FnMut(&mut T)>,
}

impl<T> Command<T> for Run<T> {
    fn execute(&mut self, system: &mut T) {
        self.function.as_mut()(system);
    }

    fn is_finished(&mut self, _system: &mut T) -> bool {
        false
    }

    fn end(&mut self, _system: &mut T, _interrupted: bool) {
        self.ended = true;
    }
}

struct RunEnd<T> {
    ended: bool,
    run: Box<dyn FnMut(&mut T)>,
    end: Box<dyn FnMut(&mut T)>,
}

impl<T> Command<T> for RunEnd<T> {
    fn execute(&mut self, system: &mut T) {
        self.run.as_mut()(system);
    }

    fn is_finished(&mut self, _system: &mut T) -> bool {
        false
    }

    fn end(&mut self, system: &mut T, _interrupted: bool) {
        self.end.as_mut()(system);
        self.ended = true;
    }
}
