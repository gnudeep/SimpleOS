#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks we are targeting the wrong operating system. */
/*#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif*/

/* This tutorial will only work for the 32-bit ix86 targets. */
/*#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif*/

/* Hardware text mode color constants. These are used to set foreground and background colors. */
enum vga_color {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};

/* Combine foreground and background colors into a single byte. */
uint8_t make_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

/* Create a 16-bit VGA entry for a character with a specific color. */
uint16_t make_vgaentry(char c, uint8_t color) {
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}

/* Calculate the length of a null-terminated string. */
size_t strlen(const char* str) {
    size_t ret = 0;
    while (str[ret] != 0)
        ret++;
    return ret;
}

/* VGA screen dimensions (80x25 characters). */
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

/* Global variables for terminal state. */
size_t terminal_row;          // Current row position of the cursor
size_t terminal_column;       // Current column position of the cursor
uint8_t terminal_color;       // Current color of the text
uint16_t* terminal_buffer;    // Pointer to the VGA text buffer

/* Initialize the terminal by clearing the screen and setting default colors. */
void terminal_initialize() {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK); // Default: light grey text on black background
    // VGA-compatible video controller maps its memory into physical memory starting at 0xB8000
    terminal_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = make_vgaentry(' ', terminal_color); // Fill screen with blank spaces
        }
    }
}

/* Set the current text color for the terminal. */
void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

/* Place a character with a specific color at a specific position on the screen. */
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, color);
}

/* Output a character to the terminal at the current cursor position. */
void terminal_putchar(char c) {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    // Move the cursor to the next position
    if (++terminal_column == VGA_WIDTH) { // If the end of the row is reached
        terminal_column = 0;             // Move to the beginning of the next row
        if (++terminal_row == VGA_HEIGHT) { // If the end of the screen is reached
            terminal_row = 0;             // Wrap back to the top
        }
    }
}

/* Write a null-terminated string to the terminal. */
void terminal_writestring(const char* data) {
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++)
        terminal_putchar(data[i]);
}

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
/* Entry point for the kernel. This is the first function called after booting. */
void kernel_main() {
    /* Initialize terminal interface */
    terminal_initialize();

    /* Write a message to the terminal. Note: '\n' is not supported yet, so it will display as a special character. */
    terminal_writestring("Hello, kernel World!\n");
}
