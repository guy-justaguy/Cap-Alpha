[bits 32]
extern idt_handler_c  ; This is the function you'll write in C

global idt_common_stub
idt_common_stub:
    pusha             ; Save all registers (eax, ecx, etc.)
    call idt_handler_c ; Jump to your C logic
    popa              ; Restore registers
    iret              ; Interrupt Return (CRITICAL to stop triple faults)

global interrupt_handler_0
interrupt_handler_0:
    push 0            ; Dummy error code
    push 0            ; Interrupt number 0
    jmp idt_common_stub