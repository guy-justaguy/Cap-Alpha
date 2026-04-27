#include <stdint.h>
// --- VGA SETTINGS ---
#define VGA_ADDRESS 0xE0000000
#define VGA_WIDTH 1024
#define VGA_HEIGHT 720

static int cursor_pos = 0;

// --- THE FUNCTION THE LINKER IS MISSING ---
void put_char(char c) {
    unsigned short* vga_buffer = (unsigned short*)VGA_ADDRESS;

    if (c == '\n') {
        cursor_pos += VGA_WIDTH - (cursor_pos % VGA_WIDTH);
    } else {
        // 0x0F is white text on black background
        vga_buffer[cursor_pos] = (unsigned short)c | (0x0F << 8);
        cursor_pos++;
    }

    // Scroll reset if screen is full
    if (cursor_pos >= VGA_WIDTH - VGA_HEIGHT) {
        cursor_pos = 1000;
    }
}

// --- YOUR PRINTF ---
void printf(const char* format, ...) {
    uint64_t *argp = (uint64_t*)&format;
    argp++; 

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            if (format[i] == 'c' || format[i] == 'C') {
                char c = (char)*argp;
                put_char(c); // Linker should see this right above!
                argp++;
            } 
            else if (format[i] == 's') {
                char *s = (char *)*argp;
                while (*s) {
                    put_char(*s++);
                }
                argp++;
            }
        } else {
            put_char(format[i]);
        }
    }
}