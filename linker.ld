ENTRY(_start)

SECTIONS
{
    /* Start at 64 bit 1MB for Multiboot compatibility tho */
    . = 0x200000;

    .text :
    {
        /* Force the header to the absolute start fr */
        KEEP(*(.multiboot))
        *(.text)
    }

    .data : { *(.data) }
    .bss  : { *(.bss)  }

    /* Remove the PHDRS block if it keeps erroring fr */
}