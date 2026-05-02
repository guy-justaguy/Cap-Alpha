#include <stdint.h>

uint8_t inb(uint16_t port) {
    uint8_t result;
    // We use 'al' for the 8-bit result and 'dx' for the port
    __asm__ volatile("in al, dx" : "=a" (result) : "d" (port));
    return result;
}