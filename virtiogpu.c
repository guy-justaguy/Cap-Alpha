#include <stdint.h>
#include "virtiogpu.h"
uint16_t len;
#define VIRTQ_DESC_F_AVAIL (1 << 7)
#define VIRTQ_DESC_F_USED (1 << 15)
#define VIRTQ_DESC_F_WRITE 2
#define VIRTQ_DESC_F_NEXT 1
/* This means the element contains a table of descriptors. */
#define VIRTQ_DESC_F_INDIRECT 4
#define ALIGN(x) (((x) + qalign) & ~qalign);
/* Enable events */
#define RING_EVENT_FLAGS_ENABLE 0x0
/* Disable events */
#define RING_EVENT_FLAGS_DISABLE 0x1
/*
* Enable events for a specific descriptor
* (as specified by Descriptor Ring Change Event Offset/Wrap Counter).
*/
/* Only valid if VIRTIO_F_EVENT_IDX has been negotiated. */
#define RING_EVENT_FLAGS_DESC 0x2
/* The value 0x3 is reserved */

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
struct virtq_desc {
/* Address (guest-physical). */
uint16_t addr;
/* Length. */
uint16_t len;
/* This marks a buffer as continuing via the next field. */
#define VIRTQ_DESC_F_NEXT 1
/* This marks a buffer as device write-only (otherwise device read-only). */
#define VIRTQ_DESC_F_WRITE 2
/* This means the buffer contains a list of buffer descriptors. */
#define VIRTQ_DESC_F_INDIRECT 4
/* The flags as indicated above. */
uint16_t flags;
/* Next field if flags & NEXT */
uint16_t next;
};
struct indirect_descriptor_table {
/* The actual descriptors (16 bytes each) */
struct virtq_desc desc[len / 16];
};

struct virtq_avail {
#define VIRTQ_AVAIL_F_NO_INTERRUPT 1
uint16_t flags;
uint16_t idx;
uint16_t ring[1024];
};
uint16_t used_event; /* Only if VIRTIO_F_EVENT_IDX */
};
struct virtq_used {
#define VIRTQ_USED_F_NO_NOTIFY 1
uint16_t flags;
uint16_t idx;
struct virtq_used_elem ring[1024];
uint16_t avail_event; /* Only if VIRTIO_F_EVENT_IDX */
};
/* uint32_t is used here for ids for padding reasons. */
struct virtq_used_elem {
    /* Index of start of used descriptor chain. */
uint32_t id;
/*
* The number of bytes written into the device writable portion of
* the buffer described by the descriptor chain.
*/
uint32_t len;
avail -> ring[avail->idx % qsz] = head;
avail->ring[(avail->idx + added++) % qsz] = head;
avail->idx += added;

virtq_disable_used_buffer_notifications(vq);
for (;;) {
if (vq->last_seen_used != le16_to_cpu(virtq->used.idx)) {
virtq_enable_used_buffer_notifications(vq);
mb();
if (vq->last_seen_used != le16_to_cpu(virtq->used.idx))
break;
virtq_disable_used_buffer_notifications(vq);
}
};
struct virtq_used_elem *e = virtq.used->ring[vq->last_seen_used%vsz];
process_buffer(e);
vq->last_seen_used++;

struct pvirtq_indirect_descriptor_table {
/* The actual descriptor structures (struct pvirtq_desc each) */
struct pvirtq_desc desc[len / sizeof(struct pvirtq_desc)];
};
struct pvirtq_desc {
/* Buffer Address. */
uint64_t addr;
/* Buffer Length. */
uint32_t len;
/* Buffer ID. */
uint16_t id;
/* The flags depending on descriptor type. */
uint16_t flags;
};