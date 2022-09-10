# llvm-update39
Silly example of llvm plugin using the new pass manager

Based on [Adrian Sampson's tutorial](https://www.cs.cornell.edu/~asampson/blog/llvm.html)

The pass will replace the pattern `39 + _` by `39 * _`

Build:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang example.c -Xclang -fpass-plugin=build/src/libUpdate39.so

When running the binary built from `example.c`, the output will be `156` instead of `43`
