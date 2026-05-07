#include <stdint.h>
#ifndef VIRTIOGPU_H
#define VIRTIO_GPU_EVENT_DISPLAY (1 << 0)
#define VIRTIO_GPU_MAX_SCANOUTS 16
#define VIRTIO_GPU_MAP_CACHE_MASK 0x0f
#define VIRTIO_GPU_MAP_CACHE_NONE 0x00
#define VIRTIO_GPU_MAP_CACHE_CACHED 0x01
#define VIRTIO_GPU_MAP_CACHE_UNCACHED 0x02
#define VIRTIO_GPU_MAP_CACHE_WC 0x03
#define VIRTIO_GPU_FLAG_FENCE (1 << 0)
#define VIRTIO_GPU_FLAG_INFO_RING_IDX (1 << 1)
#define VIRTIO_GPU_CAPSET_VIRGL 1
#define VIRTIO_GPU_CAPSET_VIRGL2 2
#define VIRTIO_GPU_CAPSET_GFXSTREAM 3
#define VIRTIO_GPU_CAPSET_VENUS 4
#define VIRTIO_GPU_CAPSET_CROSS_DOMAIN 5
#define VIRTIO_GPU_BLOB_MEM_GUEST 0x0001
#define VIRTIO_GPU_BLOB_MEM_HOST3D 0x0002
#define VIRTIO_GPU_BLOB_MEM_HOST3D_GUEST 0x0003
#define VIRTIO_GPU_BLOB_FLAG_USE_MAPPABLE 0x0001
#define VIRTIO_GPU_BLOB_FLAG_USE_SHAREABLE 0x0002
#define VIRTIO_GPU_BLOB_FLAG_USE_CROSS_DEVICE 0x0004
#define VIRTIO_GPU_CONTEXT_INIT_CAPSET_ID_MASK 0x000000ff

struct virtio_gpu_rect {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
};
struct virtio_gpu_config {
uint32_t events_read;
uint32_t events_clear;
uint32_t num_scanouts;
uint32_t num_capsets;
};
enum virtio_gpu_shm_id {
VIRTIO_GPU_SHM_ID_UNDEFINED = 0,
 VIRTIO_GPU_SHM_ID_HOST_VISIBLE = 1, 

};
enum virtio_gpu_ctrl_type {
/* 2d commands */
VIRTIO_GPU_CMD_GET_DISPLAY_INFO = 0x0100,
VIRTIO_GPU_CMD_RESOURCE_CREATE_2D,
VIRTIO_GPU_CMD_RESOURCE_UNREF,
VIRTIO_GPU_CMD_SET_SCANOUT,
VIRTIO_GPU_CMD_RESOURCE_FLUSH,
VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D,
VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING,
VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING,
VIRTIO_GPU_CMD_GET_CAPSET_INFO,
VIRTIO_GPU_CMD_GET_CAPSET,
VIRTIO_GPU_CMD_GET_EDID,
VIRTIO_GPU_CMD_RESOURCE_ASSIGN_UUID,
VIRTIO_GPU_CMD_RESOURCE_CREATE_BLOB,
VIRTIO_GPU_CMD_SET_SCANOUT_BLOB,
/* 3d commands */
VIRTIO_GPU_CMD_CTX_CREATE = 0x0200,
VIRTIO_GPU_CMD_CTX_DESTROY,
VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE,
VIRTIO_GPU_CMD_CTX_DETACH_RESOURCE,
VIRTIO_GPU_CMD_RESOURCE_CREATE_3D,
VIRTIO_GPU_CMD_TRANSFER_TO_HOST_3D,
VIRTIO_GPU_CMD_TRANSFER_FROM_HOST_3D,
VIRTIO_GPU_CMD_SUBMIT_3D,
VIRTIO_GPU_CMD_RESOURCE_MAP_BLOB,
VIRTIO_GPU_CMD_RESOURCE_UNMAP_BLOB,
/* cursor commands */
VIRTIO_GPU_CMD_UPDATE_CURSOR = 0x0300,
VIRTIO_GPU_RESP_OK_NODATA = 0x1100,
VIRTIO_GPU_RESP_OK_DISPLAY_INFO,
VIRTIO_GPU_RESP_OK_CAPSET_INFO,
VIRTIO_GPU_RESP_OK_CAPSET,
VIRTIO_GPU_RESP_OK_EDID,
VIRTIO_GPU_RESP_OK_RESOURCE_UUID,
VIRTIO_GPU_RESP_OK_MAP_INFO,
/* error responses */
VIRTIO_GPU_RESP_ERR_UNSPEC = 0x1200,
VIRTIO_GPU_RESP_ERR_OUT_OF_MEMORY,
VIRTIO_GPU_RESP_ERR_INVALID_SCANOUT_ID,
VIRTIO_GPU_RESP_ERR_INVALID_RESOURCE_ID,
VIRTIO_GPU_RESP_ERR_INVALID_CONTEXT_ID,
VIRTIO_GPU_RESP_ERR_INVALID_PARAMETER,
};

struct virtio_gpu_ctrl_hdr {
uint32_t type;
uint32_t flags;
uint64_t fence_id;
uint32_t ctx_id;
uint8_t ring_id;
uint8_t padding[3];
}  __attribute__((__packed__));
struct virtio_gpu_get_edid {
struct virtio_gpu_ctrl_hdr hdr;
    uint32_t size;
    uint32_t padding;
    uint8_t edid[1024];
}  __attribute__((__packed__));
enum virtio_gpu_formats {
VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM = 1,
VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM = 2,
VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM = 3,
VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM = 4,
VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM = 67,
VIRTIO_GPU_FORMAT_X8B8G8R8_UNORM = 68,
VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM = 121,
VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM = 134,
};
struct virtio_gpu_resource_create_2d {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t resource_id;
uint32_t format;
uint32_t width;
uint32_t height; 
}  __attribute__((__packed__));
struct virtio_gpu_resource_unref {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t resource_id;
uint32_t padding;
}  __attribute__((__packed__)) ;
struct virtio_gpu_set_scanout {
struct virtio_gpu_ctrl_hdr hdr;
struct virtio_gpu_rect r;
uint32_t scanout_id;
uint32_t resource_id;
}  __attribute__((__packed__));
struct virtio_gpu_transfer_to_host_2d {
struct virtio_gpu_ctrl_hdr hdr;
struct virtio_gpu_rect r;
uint64_t offset;
uint32_t resource_id;
uint32_t padding;
}  __attribute__((__packed__));
struct virtio_gpu_resource_attach_backing {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t resource_id;
uint32_t nr_entries;
}  __attribute__((__packed__));
struct virtio_gpu_mem_entry {
uint64_t addr;
uint32_t length;
uint32_t padding;
}   __attribute__((__packed__));
struct virtio_gpu_resource_detach_backing {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t resource_id;
uint32_t padding;
}  __attribute__((__packed__));
struct virtio_gpu_get_capset_info {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t capset_index;
uint32_t padding;
}  __attribute__((__packed__));

struct virtio_gpu_resp_capset_info {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t capset_id;
uint32_t capset_max_version;
uint32_t capset_max_size;
uint32_t padding;
}  __attribute__((__packed__));
struct virtio_gpu_get_capset {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t capset_id;
uint32_t capset_version;
}  __attribute__((__packed__));
struct virtio_gpu_resp_capset {
struct virtio_gpu_ctrl_hdr hdr;
uint8_t capset_data[];
}  __attribute__((__packed__));
struct virtio_gpu_resource_assign_uuid {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t resource_id;
uint32_t padding;
}  __attribute__((__packed__));
struct virtio_gpu_resp_resource_uuid {
struct virtio_gpu_ctrl_hdr hdr;
uint8_t uuid[16];
}  __attribute__((__packed__));

struct virtio_gpu_resource_create_blob {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t resource_id;
uint32_t blob_mem;
uint32_t blob_flags;
uint32_t nr_entries;
uint64_t blob_id;
uint64_t size;
} __attribute__((__packed__));
struct virtio_gpu_set_scanout_blob {
struct virtio_gpu_ctrl_hdr hdr;
struct virtio_gpu_rect r;
uint32_t scanout_id;
uint32_t resource_id;
uint32_t width;
uint32_t height;
uint32_t format;
uint32_t padding;
uint32_t strides[4];
uint32_t offsets[4];
} __attribute__((__packed__));

struct virtio_gpu_ctx_create {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t nlen;
uint32_t context_init;
char debug_name[64];
} __attribute__((__packed__));
struct virtio_gpu_resource_map_blob {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t resource_id;
uint32_t padding;
uint64_t offset;
}  __attribute__((__packed__));
struct virtio_gpu_resp_display_info {
struct virtio_gpu_ctrl_hdr hdr;
struct virtio_gpu_display_one {
struct virtio_gpu_rect r;
    uint32_t enabled;
    uint32_t flags; 
} pmodes[VIRTIO_GPU_MAX_SCANOUTS];
} __attribute__((__packed__));

struct virtio_gpu_resp_map_info {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t map_info;
uint32_t padding;
}  __attribute__((__packed__));
struct virtio_gpu_resource_unmap_blob {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t resource_id;
uint32_t padding;
}  __attribute__((__packed__));
struct virtio_gpu_cursor_pos {
uint32_t scanout_id;
uint32_t x;
uint32_t y;
uint32_t padding;
} __attribute__((__packed__));  
struct virtio_gpu_update_cursor {
struct virtio_gpu_ctrl_hdr hdr;
struct virtio_gpu_cursor_pos pos;
uint32_t resource_id;
uint32_t hot_x;
uint32_t hot_y;
uint32_t padding;
} __attribute__((__packed__));
struct virtio_gpu_resource_unmap_blob {
struct virtio_gpu_ctrl_hdr hdr;
uint32_t resource_id;
uint32_t padding;
} __attribute__((__packed__));
struct virtio_gpu_cursor_pos {
uint32_t scanout_id;
uint32_t x;
uint32_t y;
uint32_t padding;
}   __attribute__((__packed__));
#endif /* VIRTIOGPU_H */