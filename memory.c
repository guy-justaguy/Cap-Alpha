#include <stddef.h>

// Tell the compiler malloc exists elsewhere
extern void* malloc(size_t size);

void HYDRMEM() {
    unsigned short *mem_ptr = (unsigned short *)0x0413;
    unsigned short total_kb = *mem_ptr;

    if (total_kb >= 40000000) {
        // Added the semicolon at the end of this line fr
        int *ptr = (int*) malloc(200); 
        
        if (ptr == NULL) {
            while(1) { __asm__ volatile("hlt"); }
        }
    }
}

