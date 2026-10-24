# Segmentation Faults

[Segfaults](https://en.wikipedia.org/wiki/Segmentation_fault) are a failure condition that occurs when the program tries to read memory that it doesn't have access to. Most of the time, this means a [pointer](<https://en.wikipedia.org/wiki/Pointer_(computer_programming)>) that should have pointed to data actually pointed to [`NULL`](https://en.wikipedia.org/wiki/Null_pointer). A segfault is similar to the `NullPointerException` in Java.

One frustrating thing about segfaults in compiled programs is that, by default, when they occur no debug information is printed. Only the text `Segmentation fault (core dumped)` prints, and the program exits. After this occured once, I installed a simple signal handler into the library so that instead this is the text you will see:

```
====================================
FATAL CRASH: SIGSEGV (Segmentation Fault); Signal 11.
Sorry about this! This probably indicates a bug with the C/C++ bindings.
This bug should be reported.
If you're at a competition, try to run the program once more, and if it fails, switch to a backup.
====================================

<rust stack trace here>
```

## Causes

In the simplest case, it may be possible that an explicitly null reference is being passed to the function. That should be pretty clear just by looking at the code.

In other cases, it is likely a lifetime issue, which will probably be much harder to debug. When the rust compiler believes a value will no longer be used, it generates code to [drop](https://doc.rust-lang.org/book/ch15-03-drop.html) it. If data still exists that referenced that dropped data, a segfault will occur when it is used.

The safe wrappers do their best to prevent this from happening, for example by tying the lifetime of a configurator to its motor. Unfortunately, they aren't always perfect.

One binding that is specifically of note is the NetworkTables binding. The `NetworkTablesTopic` type should have its lifetime bound to the `NetworkTablesInstance` type, and the `NetworkTablesPublisher` to its topic. To prevent complexity with internal references (fields that reference other data in the same struct) in the `Logger` system, and because these are generally not used by the end-user, these lifetimes don't exist. If you are using these manually, make sure that the instance is not dropped before the topic.

Another possible culprit is the CTRE or REV bindings to devices and their configurators. The configurator bindings are vast and deal with many types of data, often with two layers of bindings. If you have the stack trace, it should be fairly easy to tell if this is the problem.

Hopefully one of these helped. I will be adding more if I encounter more problems as the library goes through more testing.
