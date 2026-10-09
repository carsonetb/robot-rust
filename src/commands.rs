use std::collections::HashSet;

pub struct Scheduler<T> {
    commands: Vec<Box<dyn Command<T>>>,
}

impl<T> Default for Scheduler<T> {
    fn default() -> Self {
        Self {
            commands: Vec::new(),
        }
    }
}

impl<T: 'static> Scheduler<T> {
    pub(crate) fn new() -> Self {
        Self {
            commands: Vec::new(),
        }
    }

    pub fn schedule(&mut self, system: &mut T, mut command: impl Command<T> + 'static) {
        command.initialize(system);
        self.commands.push(Box::new(command));
    }

    pub fn schedule_run(&mut self, system: &mut T, function: impl FnMut(&mut T) + 'static) {
        self.schedule(system, run(function));
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

impl<T, F: FnMut(&mut T)> Command<T> for F {
    fn execute(&mut self, system: &mut T) {
        self(system);
    }

    fn is_finished(&mut self, _system: &mut T) -> bool {
        false
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
        function: Box::new(function),
    }
}

pub fn run_end<T>(
    run: impl FnMut(&mut T) + 'static,
    end: impl FnMut(&mut T) + 'static,
) -> impl Command<T> {
    RunEnd {
        run: Box::new(run),
        end: Box::new(end),
    }
}

pub fn run_once<T>(run: impl FnMut(&mut T) + 'static) -> impl Command<T> {
    RunOnce { run: Box::new(run) }
}

pub fn parallel<T>(
    commands: impl IntoIterator<Item = impl Command<T> + 'static>,
) -> impl Command<T> {
    Parallel {
        finished: HashSet::new(),
        commands: commands
            .into_iter()
            .map(|c| Box::new(c) as Box<dyn Command<T>>)
            .collect(),
    }
}

pub fn race<T>(commands: impl IntoIterator<Item = impl Command<T> + 'static>) -> impl Command<T> {
    Race {
        finished: false,
        commands: commands
            .into_iter()
            .map(|c| Box::new(c) as Box<dyn Command<T>>)
            .collect(),
    }
}

struct Run<T> {
    function: Box<dyn FnMut(&mut T)>,
}

impl<T> Command<T> for Run<T> {
    fn execute(&mut self, system: &mut T) {
        self.function.as_mut()(system);
    }

    fn is_finished(&mut self, _system: &mut T) -> bool {
        false
    }
}

struct RunEnd<T> {
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
    }
}

struct RunOnce<T> {
    run: Box<dyn FnMut(&mut T)>,
}

impl<T> Command<T> for RunOnce<T> {
    fn initialize(&mut self, system: &mut T) {
        self.run.as_mut()(system);
    }

    fn is_finished(&mut self, _system: &mut T) -> bool {
        true
    }
}

struct Parallel<T> {
    finished: HashSet<usize>,
    commands: Vec<Box<dyn Command<T>>>,
}

impl<T> Command<T> for Parallel<T> {
    fn execute(&mut self, system: &mut T) {
        for (i, command) in self.commands.iter_mut().enumerate() {
            if self.finished.contains(&i) {
                continue;
            }
            if command.is_finished(system) {
                self.finished.insert(i);
                command.end(system, false);
                continue;
            }
            command.execute(system);
        }
    }

    fn is_finished(&mut self, _system: &mut T) -> bool {
        self.finished.len() >= self.commands.len()
    }

    fn end(&mut self, system: &mut T, interrupted: bool) {
        if !self.is_finished(system) && !interrupted {
            panic!("Parallel command ended when unfinished, but not interrupted.");
        }

        if interrupted {
            for command in &mut self.commands {
                command.end(system, true);
            }
        }
    }
}

struct Race<T> {
    finished: bool,
    commands: Vec<Box<dyn Command<T>>>,
}

impl<T> Command<T> for Race<T> {
    fn execute(&mut self, system: &mut T) {
        if self.finished {
            return;
        }

        let mut fid = None;
        for (i, command) in self.commands.iter_mut().enumerate() {
            if command.is_finished(system) {
                self.finished = true;
                command.end(system, false);
                fid = Some(i);
                break;
            }
        }

        if self.finished {
            for (i, command) in self.commands.iter_mut().enumerate() {
                if i == fid.unwrap() {
                    continue;
                }
                command.end(system, true);
            }
        }

        for command in &mut self.commands {
            command.execute(system);
        }
    }

    fn is_finished(&mut self, _system: &mut T) -> bool {
        self.finished
    }

    fn end(&mut self, system: &mut T, interrupted: bool) {
        if !self.finished && !interrupted {
            panic!("Race command ended when unfinished, but not interrupted.");
        }

        if interrupted {
            for command in &mut self.commands {
                command.end(system, true);
            }
        }
    }
}
