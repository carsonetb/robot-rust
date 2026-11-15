# Contributing & Writing Bindings

Many features are not yet complete. For some of those, such as the autonomous or simulation systems, it's not feasible to write documentation on how to expand them. Missing bindings to vendor libraries, however, are fairly trivial to write. There are two types of bindings: direct binding, where we call C++ code, and porting, where we entirely rewrite the code. Direct binding is generally used for hardware or some more complex types, while porting is used for types that are simple, or where we can't sacrifice the performance cost of bindings.

For either of these methods, you will need experience in C/C++ and unsafe Rust.

## Direct Bindings

Once you know how to do it, writing direct bindings is definetely the easier, but more tedious, of the two methods. Depending on the complexity of the type, there are two ways to write direct bindings.

### Simple Direct Bindings

You should try this method first. Inside the `ffi.rs` file, make sure the header file where the class or method you want to bind is is included. Then, add `generate!("path::to::Class")`. Then at the bottom of the file add `pub use ffi::path::to::Class`.

This type probably isn't suitable to be used by user code, so you should then write a wrapper around it. For examples of wrappers, see the types in `ctre.rs` or `rev.rs`.

Some functions might be missing from the type. This could be for many reasons, and you can view the function's documentation to see why. If this happens though, chances are you'll have to use the method in the next section.

### Writing Wrapper Functions

todo

## Rewriting

Find the source code for the C++ class. Now port all of it into rust :sob:
