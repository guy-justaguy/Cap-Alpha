#include <stdint.h>

extern void outb(unsigned short port, unsigned char value);
extern unsigned char inb(unsigned short port);
extern void COURRMOV();
extern void interrupt_handler_0(); 
// extern void printf(const char* format, ...); fk printf we r going gui
void remapPIC() {
    // Start initialization
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    // Set offsets (Master = 32, Slave = 40)
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    // Tell them how they are connected
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    // Set 8086 mode
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    // Clear masks (Unmask all)
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

// 64-bit IDT entries MUST be 16 bytes each
struct idt_entry_64 {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  ist;
    uint8_t  types_attr;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t reserved;
} __attribute__((packed));

// 64-bit IDT pointer MUST be 10 bytes
struct idt_ptr_64 {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

struct idt_entry_64 idt[256] = {0}; 
struct idt_ptr_64 idt_ptr_struct;

void set_idt_gate(int n, uint64_t handler) {
    idt[n].offset_low  = (uint16_t)(handler & 0xFFFF);
    idt[n].selector    = 0x08; // Matches your GDT64_CODE
    idt[n].ist         = 0;
    idt[n].types_attr  = 0x8E; // Present, Ring 0, Interrupt Gate
    idt[n].offset_mid  = (uint16_t)((handler >> 16) & 0xFFFF);
    idt[n].offset_high = (uint32_t)((handler >> 32) & 0xFFFFFFFF);
    idt[n].reserved    = 0;
}

void IDTLOAD() {
    uint64_t addr = (uint64_t)interrupt_handler_0;
    remapPIC();

    // Map your gates using the 16-byte structure
    set_idt_gate(2, addr);
    set_idt_gate(31, addr);
    set_idt_gate(128, addr);
    set_idt_gate(255, addr);
    set_idt_gate(33, addr);
    set_idt_gate(14, addr);
    set_idt_gate(13, addr);
    set_idt_gate(44, addr);
    if (set_idt_gate == 6) {
        COURRMOV();
  }


    // Setup the 10-byte pointer for 64-bit lidt
    idt_ptr_struct.limit = (sizeof(struct idt_entry_64) * 256) - 1;
    idt_ptr_struct.base  = (uint64_t)&idt;

    // Point lidt to the 10-byte struct and load IDT
    __asm__ __volatile__("lidt %0" :: "m"(idt_ptr_struct));
}

void idt_handler_c() {
  asm volatile("sti");
}