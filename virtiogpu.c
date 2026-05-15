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


/**GLOBAL SCOPE INTS**/

uint32_t CMD_ADDR;
uint64_t doorbelladdr;
uint64_t vendorgpuistrue;
uint64_t vendorgpuisfalse;
uint64_t head;
uint64_t added;
uint32_t memtype64_istrue;
uint32_t memtype64_isfalse;
uint32_t memtype32_istrue;
uint32_t memtype32_isfalse;
uint32_t bar_high;
uint64_t bar_low;
uint64_t offset;
uint64_t offset_64;
uint64_t total_offset;
uint64_t vq_deadweight;
uint64_t qsz;
uint64_t biosistrue;
uint64_t uefistrue;
uint64_t mmio_addr;
uint64_t memtype64istrueuefi;
uint64_t memtypeistrueuefi;
uint64_t uefi_bar_low;
uint64_t uefi_bar_high;
uint64_t uefi_totaloffset;
uint64_t uefioffset_64;
uint64_t memtype64isfalseuefi;
uint64_t memtypeisfalseuefi;
uint64_t uefioffset;



/**VIRTQ STRUCTS**/

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




/**FUNCS**/



unsigned static virtq_size(unsigned int qsz) {
uint32_t qalign = 4096; 
return ALIGN(sizeof(struct virtq_desc)*qsz + sizeof(uint16_t)*(3 + qsz)) + 
ALIGN(sizeof(struct virtq_used_elem) * qsz);
}



void virtq_disable_used_buffer_notifications(struct vq *vq) {}



uint32_t PCIGRB_BIOSGPU(uint32_t bus, uint32_t device, uint32_t offset, uint32_t value) {
CMD_ADDR = (1 << 31) | (bus << 16) | (device << 11) | (value << 8) | offset;
outl(CMD_ADDR, 0xCF8);
inl(0xCFC);
if (inl(0xCFC) == 0x1050) {
vendorgpuistrue = 1;
return vendorgpuistrue; // VIRTIOGPU DEVICE FOUND!!!
}
else {
vendorgpuisfalse = 1;
return vendorgpuisfalse; // NOT VIRTIOGPU DEVICE!!!
}
}



uint64_t PCIGRB_UEFIGPU(uint32_t bus, uint32_t device, uint32_t offset, uint32_t value) {
CMD_ADDR = (1 << 31) | (bus << 16) | (device << 11) | (value << 8) | offset;
CMD_ADDR = mmio_addr;

if (mmio_addr == 0x1050) {
vendorgpuistrue = 1;
return vendorgpuistrue; // VIRTIOGPU DEVICE FOUND!!!
}
else {
vendorgpuisfalse = 1;
return vendorgpuisfalse; // NOT VIRTIOGPU DEVICE!!!
}
}



void mb() {

        __asm__ __volatile__ ("mfence" ::: "memory");

}



uint32_t gpu_offset[0x24];
void pciegpubaroffset() {
bar_low = PCIGRB_UEFIGPU(0, 0, gpu_offset[0x14], 0);
if (bar_low == 1) { 
        biosistrue = 1;
}  // BIOS system!!! 
else {
uefistrue = 1;
}
if (bar_low == 0x6) {
memtype64istrueuefi = 1;
}
else {
 memtype64isfalseuefi = 1;
}

if (memtype64istrueuefi == 1) {
uefi_bar_high =  PCIGRB_UEFIGPU(0, 0, gpu_offset[0x15], 0);
if (uefi_bar_high & 1) {// low addr mem
if (uefi_bar_high == 0x6) {
memtypeistrueuefi = 1;
uefi_bar_low = uefioffset_64;
}
}
else {
 memtypeisfalseuefi = 1;
}
}
if (memtypeistrueuefi == 1) {
bar_high = uefioffset;
uefi_totaloffset = (uefioffset << 32) | (uefioffset_64 & ~0xF);
} 
}



uint64_t virtio_main() {

pciegpubaroffset();



if (biosistrue == 1) {
PCIGRB_BIOSGPU(0, 0, 2, 0);
}



if (uefistrue == 1) {
PCIGRB_UEFIGPU(0, 0, 2, 0);
}



// VIRTQ STRUCTS //
 

struct virtq_desc desc;
struct virtq virtq;
static struct virtq_avail avail __attribute__((aligned(4096)));
static struct virtq_used used __attribute__((aligned(4096)));



// VIRTQ COMMANDS //



struct virtio_gpu_mem_entry cmd_mem_entry;
cmd_mem_entry.addr = (uint64_t)cursorwhite;
cmd_mem_entry.length = 16384;
cmd_mem_entry.padding;


struct virtio_gpu_resource_create_2d create_cmd; 
create_cmd.resource_id = 1;
create_cmd.format = VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM;
create_cmd.width = 64;
create_cmd.height = 64;
create_cmd.hdr.type = VIRTIO_GPU_CMD_UPDATE_CURSOR; 



struct virtio_gpu_resource_attach_backing cmd_attach;
cmd_attach.resource_id = 1;
cmd_attach.nr_entries = 4;
cmd_attach.hdr.type = VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING;



struct virtio_gpu_set_scanout scnoutcomm;
scnoutcomm.scanout_id = 0;
scnoutcomm.resource_id = 1;
scnoutcomm.hdr.type = VIRTIO_GPU_CMD_SET_SCANOUT;



struct virtio_gpu_update_cursor update_cmd;
update_cmd.resource_id = 1;
update_cmd.hot_x = 0;
update_cmd.hot_y = 0;
update_cmd.padding = 0;
update_cmd.hdr.type = VIRTIO_GPU_CMD_UPDATE_CURSOR;



// VIRTQ SETUP //

avail.ring[avail.idx % qsz] = head;
avail.ring[(avail.idx + added++) % qsz] = head;



if (biosistrue == 1) {
outl(doorbelladdr, avail.idx);
}



if (uefistrue == 1) {
total_offset = (uint64_t)doorbelladdr;
}



struct vq *vq = (struct vq *)(uintptr_t)vq_deadweight;



desc.addr =(uint64_t)&create_cmd;
desc.len = 64;
desc.width = 64;



virtq.avail = avail;
virtq.pad;
virtq.used = used;



for(;;) {
if (vq->last_seen_used != le16_to_cpu(virtq.used.idx)) {
virtq_disable_used_buffer_notifications(vq);
mb();
if (vq->last_seen_used != le16_to_cpu(virtq.used.idx))
break;
virtq_disable_used_buffer_notifications(vq);
}
}
mb();
*(volatile uint32_t*)(total_offset) = 0;
return total_offset;
}