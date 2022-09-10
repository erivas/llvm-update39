# llvm-update39
Silly example of llvm plugin using the new pass manager

Based on [Adrian Sampson's tutorial](https://www.cs.cornell.edu/~asampson/blog/llvm.html)

Build:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang example.c -Xclang -fpass-plugin=build/src/libUpdate39.so
