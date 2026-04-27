#include <stddef.h>

// This struct keeps track of each memory block
struct block_meta {
    size_t size;
    int free;
    struct block_meta *next;
};

#define META_SIZE sizeof(struct block_meta)

// Start your heap at 2MB to stay clear of the kernel code
void *heap_start = (void*)0x200000;
struct block_meta *global_base = NULL;

// --- MALLOC ---
void *malloc(size_t size) {
    if (size <= 0) return NULL;

    struct block_meta *current = global_base;
    struct block_meta *last = NULL;

    // Search for a free block that's big enough
    while (current) {
        if (current->free && current->size >= size) {
            current->free = 0;
            return (void*)(current + 1);
        }
        last = current;
        current = current->next;
    }

    // No free block found, request more memory (bump the heap)
    struct block_meta *block = (struct block_meta*)heap_start;
    heap_start += (size + META_SIZE);
    
    block->size = size;
    block->next = NULL;
    block->free = 0;

    if (!global_base) {
        global_base = block;
    } else {
        last->next = block;
    }

    return (void*)(block + 1);
}

// --- FREE ---
void free(void *ptr) {
    if (!ptr) return;
    struct block_meta* block = ((struct block_meta*)ptr) - 1;
    block->free = 1; // Just mark it as free so malloc can reuse it fr
}

// --- CALLOC ---
void *calloc(size_t nelem, size_t elsize) {
    size_t size = nelem * elsize;
    void *ptr = malloc(size);
    if (ptr) {
        // Zero out the memory
        unsigned char *p = (unsigned char*)ptr;
        for (size_t i = 0; i < size; i++) {
            p[i] = 0;
        }
    }
    return ptr;
}

// --- REALLOC ---
void *realloc(void *ptr, size_t size) {
    if (!ptr) return malloc(size);
    
    struct block_meta* block = ((struct block_meta*)ptr) - 1;
    if (block->size >= size) return ptr;

    void *new_ptr = malloc(size);
    if (new_ptr) {
        unsigned char *old_p = (unsigned char*)ptr;
        unsigned char *new_p = (unsigned char*)new_ptr;
        for (size_t i = 0; i < block->size; i++) {
            new_p[i] = old_p[i];
        }
        free(ptr);
    }
    return new_ptr;
}
