#define VIRTIO_GPU_EVENT_DISPLAY (1 << 0)

struct virtio_gpu_config {
uint32_t events_read;
uint32_t events_clear;
uint32_t num_scanouts;
uint32_t num_capsets;
};
enum virtio_gpu_shm_id {
VIRTIO_GPU_SHM_ID_UNDEFINED = 0
VIRTIO_GPU_SHM_ID_HOST_VISIBLE = 1
};