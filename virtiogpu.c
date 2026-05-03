#include <stdint.h>
#include "virtiogpu.h"

#define ALIGN(x) (((x) + qalign) & ~qalign);
extern unsigned char cursorwhite[];
extern unsigned int cursorwhite_raw_len;
extern void outl(uint32_t port, uint32_t value);
extern uint32_t inl(uint16_t port);
uint32_t function;


uint32_t pcieFINDVIRTIO_GPU(uint32_t bus, uint32_t device, uint32_t offset, uint32_t value) {
    uint32_t CMD_ADRR = (1 << 31) | (bus << 16) | (device << 11) | (function << 8) | offset;
        inl(0xCF8);
        outl(0xCF8, CMD_ADRR);
        outl(0xCFC, 0x03);
          if (inl(0xCFC) != 0x1AF41050) {
                return 0; // NOT A VIRTIO GPU DEVICE!!!
            }
    
}   
void virtio_main() {
    pcieFINDVIRTIO_GPU(0, 2, 0, 0);
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
uint32_t resource_id = 0;
uint32_t nr_entries = 4;


struct VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM;
  uint64_t offset = (uint64_t)cursorwhite;


struct VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D;
struct virtio_gpu_transfer_to_host_2d transfer_cmd;
uint64_t offset = (uint64_t)cursorwhite;
uint32_t resource_id = 0;
uint32_t padding;


VIRTIO_GPU_CMD_SET_SCANOUT;
VIRTIO_GPU_CMD_RESOURCE_CREATE_2D;
VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING;
VIRTIO_GPU_CMD_RESOURCE_FLUSH;
};
// VIRTIO QUEUE COMMANDS;
static inline unsigned virtq_size(unsigned int qsz)
{
return ALIGN(sizeof(struct virtq_desc)*qsz + sizeof(uint16_t)*(3 + qsz))
+ ALIGN(sizeof(uint16_t)*3 + sizeof(struct virtq_used_elem)*qsz);
}

struct virtq {
struct virtq_desc desc[ Queue Size ];
struct virtq_avail avail;
uint8_t pad[ Padding ];
struct virtq_used used;
};
}