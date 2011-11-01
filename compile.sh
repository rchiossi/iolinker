#!/bin/sh
gcc -c begin.S linker.c
ld -shared -o linker.so begin.o linker.o
gcc -Wl,--dynamic-linker=./linker.so -o target target.c
