#!/bin/bash
mips-linux-gnu-gcc src/main.c -o dist/MipsIsCool_not_stripped
mips-linux-gnu-gcc -s src/main.c -o dist/MipsIsCool
# gcc -s src/main.c -o dist/MipsIsCool_linux
