#!/bin/sh
gcc -m32 -c boot.s
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c kernel.c
gcc -m32 -T linker.ld -ffreestanding -nostdlib -o kernel.bin boot.o kernel.o -lgcc
rm *.o
