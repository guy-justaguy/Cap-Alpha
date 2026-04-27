// decls
#include <stdint.h>
extern int strcmp(const char *s1, const char *s2);
unsigned long magic;
uint64_t *systemappaddr = (uint64_t*)0x20000000;
uint64_t statusapp;
uint64_t *app_index;
int ptr;
extern void printf(const char *format, ...);
uint64_t array_index[100];
// mem array for apps  
uint64_t EXECUTECOMMAND() {
 if (magic == 0x464c457f) 
    // idk man i dont know hows to code ¯\_(ツ)_/¯ 
    *systemappaddr = *array_index;  
            for (uint64_t i = 0; i < 256; i++) {
                statusapp = 1;
                    if (statusapp == 0)
                        return ptr = 1;
}
}