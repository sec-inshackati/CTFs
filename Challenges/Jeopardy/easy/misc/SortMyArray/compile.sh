#!/bin/bash
gcc src/main.c src/sort.c -masm=intel -O0 -o dist/SortMyArray
