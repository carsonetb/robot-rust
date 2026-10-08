pub(crate) struct Scheduler<T> {
    commands: Vec<Box<dyn Command<T>>>,
}

impl<T> Scheduler<T> {
    pub(crate) fn new() -> Self {
        Self {
            commands: Vec::new(),
        }
    }

    pub(crate) fn schedule(&mut self, mut command: impl IntoCommand<T> + 'static, system: &mut T) {
        command.initialize(system);
        self.commands.push(Box::new(command.into_command()));
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

pub trait IntoCommand<T> {
    fn into_command(self) -> impl Command<T>;
}

impl<C: Command, T> IntoCommand<T> for C {
    fn into_command(self) -> impl Command<T> {
        self
    }
}

impl<T, F: FnMut(&mut T)> IntoCommand<T> for F {
    fn into_command(self) -> impl Command<T> {
        run(self)
    }
}

pub trait Command<T> {
    fn initialize(&mut self, system: &mut T) {
        let _ = system;
    }
    fn execute(&mut self, system: &mut T) {
        let _ = system;
    }
    fn is_finished(&mut self, system: &mut T) -> bool;
    fn end(&mut self, system: &mut T, interrupted: bool) {
        let _ = (system, interrupted);
    }
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

pub fn run_once<T>(run: impl FnOnce(&mut T) + 'static) -> impl Command<T> {
    RunOnce { run: Box::new(run) }
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

struct RunOnce<T> {
    run: Box<dyn FnOnce(&mut T)>,
}

impl<T> Command<T> for RunOnce<T> {
    fn initialize(&mut self, system: &mut T) {
        self.run.as_mut()(system);
    }

    fn is_finished(&mut self, _system: &mut T) -> bool {
        true
    }
}
