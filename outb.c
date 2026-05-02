#include <stdint.h>

void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("out dx, al" : : "d"(port), "a"(value));
}