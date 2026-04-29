#include <stdint.h>

void outl(uint32_t value, uint16_t port) {
    __asm__ volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}