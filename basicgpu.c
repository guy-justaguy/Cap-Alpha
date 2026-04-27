#include <stdint.h>
// --FORRGPBSC--

void FORRGPBSC() {
uint32_t *framebuffer = (uint32_t*)0x80000000;
for (uint64_t i = 0; i < (2000000); i++) {
        framebuffer[i] = 0xAAAAAAA;
}
}
