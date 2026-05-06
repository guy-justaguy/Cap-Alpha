# Variables for your tools
CC = gcc
LD = ld --no-gc-sections
AS = nasm

# Compiler flags from your terminal
CFLAGS = -ffreestanding -fno-pie -mcmodel=kernel -mno-red-zone -fno-stack-protector -fno-builtin -nostdlib -fno-tree-loop-distribute-patterns -masm=intel

# All the objects needed for GumballKernel
OBJS = pm_entry.o kernel.o printf.o memory.o malloc.o memcpy.o linux_syscall.o basicgpu.o shell.o strcmp.o idt.o idt_asm.o COURRMOV.o virtiogpu.o inb.o outb.o outl.o inl.o

all: kernel.elf

# Rule to turn your new IDT bridge into an object
idt_asm.o: idt_asm.asm
	$(AS) -f elf64 idt_asm.asm -o idt_asm.o

# Existing assembly rule
pm_entry.o: pm_entry.asm
	$(AS) -f elf64 pm_entry.asm -o pm_entry.o

# Generic rule for all your C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Linking everything into the ELF
kernel.elf: $(OBJS)
	$(LD) -m elf_x86_64 -T linker.ld $(OBJS) -o kernel.elf

clean:
	rm -f *.o *.bin *.elf*