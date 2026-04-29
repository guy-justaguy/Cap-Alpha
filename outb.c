#include <stdint.h>
void outb(uint16_t port, uint16_t value) {
    __asm__ volatile ( "outb %0, %1" : : "a"(value ), "Nd"(port) );
}