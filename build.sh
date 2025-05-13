#!/bin/sh

# Assemble the boot.s file into a 32-bit object file (boot.o)
gcc -m32 -c boot.s

# Compile the kernel.c file into a 32-bit freestanding object file (kernel.o)
# -m32: Generate 32-bit code
# -std=gnu99: Use the GNU99 standard for C
# -ffreestanding: Indicate that this is a freestanding environment (no standard library)
# -O2: Optimize the code for speed
# -Wall -Wextra: Enable most compiler warnings
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c kernel.c

# Link the boot.o and kernel.o object files into a final binary (kernel.bin)
# -T linker.ld: Use the linker script linker.ld to control the linking process
# -ffreestanding: Ensure the binary is suitable for a freestanding environment
# -nostdlib: Do not link against the standard C library
# -lgcc: Link against GCC's internal library for low-level support
gcc -m32 -T linker.ld -ffreestanding -nostdlib -o kernel.bin boot.o kernel.o -lgcc

# Clean up intermediate object files to keep the directory tidy
rm *.o
