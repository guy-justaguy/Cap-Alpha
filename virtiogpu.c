/**INCLUDE**/


#include <stdint.h>
#include "virtiogpu.h"



/**DECL**/

extern uint64_t cursorwhite[4096];
extern void outl(uint16_t port, uint32_t value);
extern uint32_t inl(uint16_t port);



/**DEFINITIONS**/


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
#define le16_to_cpu(x) (x)



struct virtq_desc {
uint64_t addr;
uint16_t len;
uint16_t width;
uint32_t ring[QUEUE_SIZE];
} __attribute__((__packed__));



struct virtq_used_elem {
uint32_t id;
} __attribute__((__packed__));



struct virtq_avail {
uint16_t flags;
uint16_t idx;
uint16_t ring[QUEUE_SIZE];
uint16_t used_event;
} __attribute__((__packed__));



struct virtq_used {
uint16_t flags;
uint16_t idx;
uint16_t avail_event;
uint16_t ring[QUEUE_SIZE];
} __attribute__((__packed__));



struct virtq {
struct virtq_desc desc[QUEUE_SIZE];
struct virtq_avail avail;
uint8_t pad[3];
struct virtq_used used;
} __attribute__((__packed__));



struct vq {
uint32_t *vq;
uint32_t last_seen_used;
} __attribute__((__packed__));



void virtq_disable_used_buffer_notifications(struct vq *vq) {}


/**FUNCS**/

uint32_t pcieFINDVIRTIO_GPU(uint32_t bus, uint32_t device, uint32_t offset, uint32_t value) {
uint32_t CMD_ADRR = (1 << 31) | (bus << 16) | (device << 11) | (value << 8) | offset;
if (CMD_ADRR == 0x1AF41050) {
return 0; // NOT A VIRTIO GPU DEVICE!!!
}
}

void mb() {

        __asm__ __volatile__ ("mfence" ::: "memory");

}



uint32_t padding = 0;
uint32_t qalign = 4096;
uint32_t qsz = QUEUE_SIZE;
uint32_t added;
uint16_t head;
struct virtq_desc virtq_used;
struct virtq_used virtq_avail;
struct virtq_avail idx;
struct virtq_avail ring;
struct virtq_avail used;
struct virtq_used avail;
uint32_t memtype64_istrue;
uint32_t memtype64_isfalse;
uint32_t memtype32_istrue;
uint32_t memtype32_isfalse;
uint32_t bar_high;
uint64_t bar_low;
uint64_t offset;
uint64_t offset_64;
uint64_t total_offset;
uint64_t doorbelladdr;



 unsigned static virtq_size(unsigned int qsz) {
    uint32_t qalign = 4096; 
return ALIGN(sizeof(struct virtq_desc)*qsz + sizeof(uint16_t)*(3 + qsz)) + 
ALIGN(sizeof(struct virtq_used_elem) * qsz);
virtq_avail.ring[avail.idx % qsz] = head;
virtq_avail.ring[avail.idx + added++ % qsz] = head;
}


uint32_t gpu_offset[0x24];
void pciegpubaroffset() {
bar_low =  pcieFINDVIRTIO_GPU(0, 0, gpu_offset[0x14], 0);
if (bar_low & 1) // low addr mem
if (bar_low == 0x6) {
memtype64_istrue = 1;
}
else {
 memtype64_isfalse = 1;
}

if (memtype64_istrue == 1) {
bar_high =  pcieFINDVIRTIO_GPU(0, 0, gpu_offset[0x15], 0);
if (bar_high & 1) // low addr mem
if ((bar_high == 0x6) == 0x4) {
memtype32_istrue = 1;
bar_low = offset_64;
}
else {
 memtype32_isfalse = 1;
}
}
if (memtype32_istrue == 1) {
bar_high = offset;
}
total_offset = (offset << 32) | (offset_64 & ~0xF);
} 

uint32_t virtio_main() {
pcieFINDVIRTIO_GPU(0, 0, 4, 0);



// VIRTQ STRUCTS //
 


struct vq *vq;

vq = total_offset;
virtq_disable_used_buffer_notifications(vq);

struct virtq_desc virtq_used;
struct virtq_used virtq_avail;
struct virtq_avail idx;
struct virtq_avail ring;
struct virtq virtq;
struct virtq_desc virtq_desc;
struct virtq_desc desc;
struct virtq_avail used;
struct virtq_used avail;

//  INTEGERS IN FUNC //

uint32_t padding = 0;
uint32_t qalign = 4096;
uint32_t qsz = QUEUE_SIZE;
uint32_t added;
uint16_t head;



// VIRTIO-GPU STRUCTS //

struct virtio_gpu_mem_entry cmd_mem_entry;
cmd_mem_entry.addr = (uint64_t)cursorwhite;
cmd_mem_entry.length = 16389;
cmd_mem_entry.padding;


struct virtio_gpu_resource_create_2d create_cmd; 
create_cmd.resource_id = 1;
create_cmd.format = VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM;
create_cmd.width = 64;
create_cmd.height = 64;



struct virtio_gpu_resource_attach_backing cmd_attach;
cmd_attach.resource_id = 1;
cmd_attach.nr_entries = 4;



struct virtio_gpu_update_cursor update_cmd;
update_cmd.resource_id = 1;
update_cmd.hot_x = 0;
update_cmd.hot_y = 0;
update_cmd.padding = 0;



total_offset = (uint64_t)doorbelladdr;



desc.addr = total_offset;
desc.len = 64;
desc.width = 64;



virtq.desc;
virtq.avail = used;
virtq.pad;
virtq.used = avail;



// VIRTIO-GPU COMMANDS //
vq ->last_seen_used++;

VIRTIO_GPU_CMD_SET_SCANOUT;
VIRTIO_GPU_CMD_RESOURCE_CREATE_2D;
VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING;
VIRTIO_GPU_CMD_RESOURCE_FLUSH;



for(;;) {
if (vq->last_seen_used != le16_to_cpu(virtq.used.idx)) {
virtq_disable_used_buffer_notifications(vq);
mb();
if (vq->last_seen_used != le16_to_cpu(virtq.used.idx))
break;
virtq_disable_used_buffer_notifications(vq);
}
}
}