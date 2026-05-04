#include <stdint.h>
#include "virtiogpu.h"
#include "cursorwhite.h"
extern void outl(uint16_t port, uint32_t value);
extern uint32_t inl(uint16_t port);

// ---DEFINITIONS---//
#define VIRTQ_DESC_F_AVAIL (1 << 7)
#define VIRTQ_DESC_F_USED (1 << 15)
#define VIRTQ_DESC_F_WRITE 2
#define VIRTQ_DESC_F_NEXT 1
#define VIRTQ_DESC_F_INDIRECT 4
#define ALIGN(x) (((x) + qalign) & ~qalign)
#define RING_EVENT_FLAGS_ENABLE 0x0
#define RING_EVENT_FLAGS_DISABLE 0x1
#define QUEUE_SIZE 128
#define VIRTQ_DESC_F_NEXT 1
#define VIRTQ_DESC_F_WRITE 2
#define VIRTQ_DESC_F_INDIRECT 4
#define VIRTQ_AVAIL_F_NO_INTERRUPT 1
#define RING_EVENT_FLAGS_DESC 0x2
#define VIRTQ_USED_F_NO_NOTIFY 1
// ---STRUCTS---//
    struct virtio_gpu_ctrl_hdr hdr;
struct VIRTIO_GPU_CMD_RESOURCE_CREATE_2D;
struct virtio_gpu_resource_attach_backing attach_cmd;
struct virtio_gpu_resource_attach_backing;
struct indirect_descriptor_table;
struct VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM;
struct VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D;
struct virtio_gpu_transfer_to_host_2d transfer_cmd;
struct pvirtq_desc {
/* Buffer Address. */
uint64_t addr;
/* Buffer Length. */
uint32_t len;
/* Buffer ID */
uint16_t id;
/* The flags depending on descriptor type. */
struct pvirtq_indirect_descriptor_table {
/* The actual descriptor structures (struct pvirtq_desc each) */
};
};
struct virtq {
struct virtq_desc desc[QUEUE_SIZE];
__attribute__((__packed__)) __attribute__((KEEP)) struct virtq_avail;
uint8_t pad[3];
__attribute__((__packed__)) __attribute__((KEEP)) struct virtq_used;
};
__attribute__((__packed__)) __attribute__((KEEP)) struct virtq_desc {
/* Address (guest-physical). */
uint16_t addr;
/* Length. */
uint16_t len;
uint16_t ring[1024];
__attribute__((__packed__)) __attribute__((KEEP)) struct virtq_avail {
uint16_t flags;
uint16_t idx;
uint16_t ring[1024];
};
uint16_t used_event;
};

__attribute__((__packed__)) __attribute__((KEEP)) struct virtq_used {
uint16_t flags;
uint16_t idx;
};

__attribute__((__packed__)) __attribute__((KEEP)) struct virtq_used_elem ring[1024];

__attribute__((__packed__)) __attribute__((KEEP)) struct virtq_used_elem {
    /* Index of start of used descriptor chain. */
uint32_t id;
};
struct vq {
struct virtq *vq;
uint32_t last_seen_used;
uint32_t qsz;
uint32_t qalign;
};
// ---FUNCS---//


int pcieFINDVIRTIO_GPU(uint32_t bus, uint32_t device, uint32_t offset, uint32_t value) {
    uint32_t CMD_ADRR = (1 << 31) | (bus << 16) | (device << 11) | (value << 8) | offset;
        inl(0xCF8);
        outl(0xCF8, CMD_ADRR);
        outl(0xCFC, 0x03);
          if (inl(0xCFC) != 0x1AF41050) {
                return 0; // NOT A VIRTIO GPU DEVICE!!!
            }
}  


void virtio_main() {
 pcieFINDVIRTIO_GPU(0, 0, 2, 0);
 struct vq *vq;
 struct virtq_desc virtq_used;
 struct virtq_avail virtq_avail;
 struct virtq_avail idx;
 struct virtq_avail ring;
 struct virtq virtq;
vq ->last_seen_used++;
process_buffer(e);
uint32_t added;
uint32_t *avail;
uint32_t width = 64;
uint32_t height = 64;
uint64_t offset = (uint64_t)cursorwhite;
uint32_t resource_id = 0;
uint32_t padding = 0;
uint32_t qalign = 4096;
uint32_t qsz = QUEUE_SIZE;
uint32_t len;
uint32_t format = VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM;
virtq_avail.idx += added;
struct pvirtq_desc desc[len = sizeof(pvirtq_desc)];

struct virtq_used_elem *e = virtq_used.ring[vq->last_seen_used%qsz];
attach_cmd.hdr = hdr;
attach_cmd.resource_id = 1;
attach_cmd.nr_entries = 1;
VIRTIO_GPU_CMD_SET_SCANOUT;
VIRTIO_GPU_CMD_RESOURCE_CREATE_2D;
VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING;
VIRTIO_GPU_CMD_RESOURCE_FLUSH;

virtq_disable_used_buffer_notifications(vq);
for(;;) {
if (vq->last_seen_used != le16_to_cpu(virtq.used.idx)) {
virtq_enable_used_buffer_notifications(vq);
mb();
if (vq->last_seen_used != le16_to_cpu(virtq.used.idx))
break;
virtq_disable_used_buffer_notifications(vq);
}
}
unsigned static virtq_size(unsigned int qsz) {
return ALIGN(sizeof(struct virtq_desc)*qsz + sizeof(uint16_t)*(3 + qsz))
+ ALIGN(sizeof(uint16_t)*3 + sizeof(struct virtq_used_elem)*qsz);
avail -> ring[avail->idx % qsz] = head;
avail ->ring[(avail->idx + added++) % qsz] = head;
}
}