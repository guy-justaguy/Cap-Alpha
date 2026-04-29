#include "cursorwhite.h"
#include <stdint.h>

extern void outb(unsigned short port, unsigned char value);
extern unsigned char inb(unsigned short port);
uint8_t flags;
uint8_t delta_x;
uint8_t delta_y;
uint32_t savepos;
uint32_t realcourr;
uint32_t screen_width = 1024;
uint32_t offset; // This should be set to the mouse's X and Y position
uint32_t mouse_xy;

// extern bckb lib start
uint32_t BCKB[4096];
uint32_t BCKB1[4096];
uint32_t BCKB2[4096];
uint32_t *framebuffer = (uint32_t*)0xFD000000;
unsigned short status;
unsigned short status2;
// extern bckb lib end



 // ---CORRMOV--//
void initmouse() {
outb (0xA8, 0x64);
outb (0xD4, 0x64);
outb (0xf8, 0x60);
flags = inb(0x60);
}
void delta_xyinfofetcher() {
   status = inb(0x64);
if(status & 0x1) {
delta_x = inb(0x60);
}
status2 = inb(0x64);
if(status2 & 0x1) {
delta_y = inb(0x60);
}
}
static uint32_t real_x = 0;
static uint32_t real_y = 0; 
void calc() {
realcourr = (real_y * 1024) + real_x;
real_x += delta_x;
real_y -= delta_y;
savepos = realcourr;
}
void COURRMOV() {
    delta_xyinfofetcher();
 calc();   
/* --start-- */
mouse_xy = delta_x + delta_y; // calculate the mouse movement
__builtin_memcpy(framebuffer + savepos, cursorwhite, 4096);

/* --end-- */
// holy shit fking 60 lines for a mouse😭😭😭💀
}