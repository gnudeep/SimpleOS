# SimpleOS

SimpleOS is a minimal operating system designed for educational purposes. It demonstrates the basics of OS development, including bootloading, kernel initialization, and VGA text mode manipulation.

The code is based on the [Bare Bones tutorial](http://wiki.osdev.org/Bare_Bones) from the OSDev Wiki.

## Features
- A simple bootloader and kernel written in assembly and C.
- VGA text mode support for displaying text on the screen.
- Freestanding environment without reliance on standard libraries.

## Prerequisites
To build and run SimpleOS, you need the following tools installed on your system:
- **GCC cross-compiler** targeting `i386-elf`
- **GNU Binutils** for assembling and linking
- **QEMU** for emulating the OS

### Installing Prerequisites on Ubuntu
```bash
sudo apt update
sudo apt install build-essential qemu gcc-multilib
```

## How to Build the Source
Run the `build.sh` script to assemble and compile the source code into a binary:
```bash
./build.sh
```

## How to Run the Binary
Use QEMU to emulate the OS:
```bash
qemu-system-i386 -kernel kernel.bin
```

## File Structure
- `boot.s`: Assembly code for the bootloader.
- `kernel.c`: The main kernel code written in C.
- `linker.ld`: Linker script to control the memory layout of the binary.
- `build.sh`: Script to automate the build process.

## Tested Platforms
SimpleOS has been tested on the following platform:
- **Ubuntu 24.04 amd64**

## Notes
- This project is for educational purposes only and is not intended for production use.
- Ensure you are using a cross-compiler to avoid compatibility issues with your host system's libraries.

## Resources
- [OSDev Wiki](http://wiki.osdev.org): A comprehensive resource for operating system development.
- [Bare Bones Tutorial](http://wiki.osdev.org/Bare_Bones): The tutorial this project is based on.

## License
This project is distributed under the terms of the [MIT License](https://opensource.org/licenses/MIT).

