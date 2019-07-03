#!/bin/bash
# gcc aes.c aes_test.c -o dist/test_aes 2>&1 >/dev/null
gcc aes.c main.c -masm=intel -fno-stack-protector -no-pie -Fno-pie -O0 -o dist/SecurePasswordCheck
