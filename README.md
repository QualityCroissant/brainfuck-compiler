# brainfuck-compiler
A Brainfuck compiler for Linux x86_64

The primary source code is located under src/
Files used during compilation are located under lib/
Files which the user is intended to interact with are located under bin/

To compile:
1. Use bin/bfc <brainfuck file>
2. This will create a directory, <brainfuck file>.build
3. In this directory your binary can be found, under the same name as <brainfuck file>
