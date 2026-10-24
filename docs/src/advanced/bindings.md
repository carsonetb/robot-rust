# Contributing & Writing Bindings

Many features are not yet complete. For some of those, such as the autonomous or simulation systems, it's not feasible to write documentation on how to expand them. Missing bindings to vendor libraries, however, are fairly trivial to write. There are two types of bindings: direct binding, where we call C++ code, and porting, where we entirely rewrite the code. Direct binding is generally used for hardware or some more complex types, while porting is used for types that are simple, or where we can't sacrifice the performance cost of bindings.

For either of these methods, you will need experience in C/C++ and unsafe Rust.

## Direct Bindings

Once you know how to do it, writing direct bindings is definetely the easier, but more tedious, of the two methods.
