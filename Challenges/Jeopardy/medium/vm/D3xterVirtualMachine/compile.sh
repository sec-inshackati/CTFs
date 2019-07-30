#!/bin/bash
gcc src/main.c src/registers.c -D DEBUG -masm=intel -fno-stack-protector -no-pie -Fno-pie -O0 -o dist/D3xterVirtualMachine_DEBUG
gcc src/main.c src/registers.c -masm=intel -fno-stack-protector -no-pie -Fno-pie -O0 -o dist/D3xterVirtualMachine
