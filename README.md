# brainfuck-compiler
**A Brainfuck compiler for Linux x86_64**

The primary source code is located under src/

Files used during compilation are located under lib/

Files which the user is intended to interact with are located under bin/

Dependencies:
1. bash
2. nasm
3. ld

Dependencies for building from source:
1. A C compiler (clang is assumed by default)
2. make

To compile:
1. Use bin/bfc \<brainfuck file\>
2. This will create a directory, \<brainfuck file\>.build
3. In this directory your binary can be found, under the same name as \<brainfuck file\>

To build from source:
1. Go to src/
2. make
