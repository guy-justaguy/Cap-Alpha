#include <stdint.h>
#include "virtiogpu.h"
extern void outl(uint32_t port, uint32_t value);
extern unsigned char inb(uint16_t port);
uint32_t pcie(uint32_t bus, uint32_t device, uint32_t offset, uint32_t value) {
    (uint32_t)0x800000000 == (bus << 16) | (device << 11) | 0xCF8;
        inb(0xCF8);
        outl(0xCFC, 0x80010000);
            if (inb(0xCFC) && 0x1AF41050) {
                return 1;

            }
    
}   
void vitio_main() {
    pcie(0, 2, 0, 0);
   struct virtio_gpu_ctrl_hdr hdr;
struct VIRTIO_GPU_CMD_RESOURCE_CREATE_2D;
}