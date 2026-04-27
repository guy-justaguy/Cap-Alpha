bits 64

global _start
extern GLDMAIN
extern LINUZSYS
; Force the section to be allocatable and executable
section .multiboot_header alloc exec write
align 8
header_start:
    dd 0xe85250d6                ; Magic
    dd 0                         ; Architecture 0
    dd header_end - header_start ; Header length
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) ; Checksum

    ; --- Framebuffer Tag (Type 5) ---
    align 8
    dw 5    ; type
    dw 0    ; flags
    dd 20   ; size (tag is 20 bytes)
    dd 1024 ; width
    dd 768  ; height
    dd 32   ; bpp
    
    ; Padding to keep the NEXT tag 8-byte aligned 🥀
    dd 0    

    ; --- End Tag (Type 0) ---
    align 8
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
header_end:
section .text
_start:
    cli
    ; Force the stack to a known good location in our BSS 
    mov rax, stack_top
    mov rsp, rax

    ; 1. Fix EFER (0xC0000080)
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1
    wrmsr

    ; 2. STAR (0xC0000081) - Force clear RDX fr fr 
   ; mov ecx, 0xC0000081
   ; xor rdx, rdx           ; Wipe the whole 64-bit register 
   ; mov eax, 0x001B0008    ; Kernel CS 0x08, User CS 0x1B
 ;   wrmsr

    ; 3. LSTAR (0xC0000082) - Your RIP is ffffffff80000535
    ;mov ecx, 0xC0000082
    ;mov rax, LINUZSYS      ; Handler address
  ;  mov rdx, rax
   ; shr rdx, 32            ; High 32 bits into EDX
  ;  wrmsr                  ; EAX has low 32 bits

    ; 4. SFMASK (0xC0000084) - CRASH POINT 
    ;mov ecx, 0xC0000084
   ; xor rdx, rdx           ; IF RDX IS NOT ZERO HERE, T9550 DIES 🥀
    ;mov eax, 0x200         ; Mask IF bit
  ;  wrmsr
; --- 64-bit SSE Enable for UEFI/Long Mode ---
mov rax, cr0
and ax, 0xFFFB      ; Clear EM (bit 2) 
or ax, 0x2          ; Set MP (bit 1)
mov cr0, rax

mov rax, cr4
or ax, (3 << 9)     ; Set OSFXSR (bit 9) and OSXMMEXCPT (bit 10)
mov cr4, rax

    ; 5. Drop into C
    call GLDMAIN

.hang:
    cli
    hlt
    jmp .hang

section .bss
align 4096
stack_bottom:
    resb 65536             ; Bigger stack just in case 
stack_top: