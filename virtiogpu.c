#include <stdint.h>
#include "virtiogpu.h"
extern unsigned char cursorwhite[];
extern unsigned int cursorwhite_raw_len;
extern void outl(uint32_t port, uint32_t value);
extern uint32_t inl(uint16_t port);
uint32_t function;


uint32_t pcie(uint32_t bus, uint32_t device, uint32_t offset, uint32_t value) {
    uint32_t CMD_ADRR = (1 << 31) | (bus << 16) | (device << 11) | (function << 8) | offset;
        inl(0xCF8);
        outl(0xCF8, CMD_ADRR);
        outl(0xCFC, 0x03);
          if (inl(0xCFC) != 0x1AF41050) {
                return 0; // NOT A VIRTIO GPU DEVICE!!!
            }
    
}   
void virtio_main() {
    pcie(0, 2, 0, 0);
struct virtiogpu;
{

   struct virtio_gpu_ctrl_hdr hdr;
   hdr.type = VIRTIO_GPU_CMD_RESOURCE_CREATE_2D;
struct VIRTIO_GPU_CMD_RESOURCE_CREATE_2D;
uint32_t resource_id = 0;
uint32_t format = VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM;
uint32_t width = 64;
uint32_t height = 64;
struct virtio_gpu_resource_attach_backing attach_cmd;
attach_cmd.hdr = hdr;
attach_cmd.resource_id = 1;
attach_cmd.nr_entries = 1;
struct virtio_gpu_resource_attach_backing;
struct VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM;
struct VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D;
  uint64_t offset = (uint64_t)cursorwhite;
struct virtio_gpu_transfer_to_host_2d transfer_cmd;
struct VIRTIO_GPU_CMD_SET_SCANOUT;

};

}