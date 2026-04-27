#include <stdint.h>
void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ( "outb %0, %1" : : "a"(value ), "Nd"(port) );
}