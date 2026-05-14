# Gumball Kernel - Cap-Alpha (GCC Edition)
CC = clang
AS = nasm
LD = ld.lld

# The "Chill" Flags
CFLAGS = -ffreestanding -O2 -std=c11 -mcmodel=kernel -mno-red-zone -fno-stack-protector -fno-builtin -nostdlib -Wall -Wno-unused-variable -Wno-unused-function -masm=intel

# Filtering out the glitch files from your ls output
C_SOURCES = $(filter-out last_seen_used%vsz] 'ring[vq-', $(wildcard *.c))
OBJ = $(C_SOURCES:.c=.o) pm_entry.o idt_asm.o

all: kernel.elf

kernel.elf: $(OBJ)
	$(LD) -T linker.ld -o kernel.elf $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

pm_entry.o: pm_entry.asm
	$(AS) -f elf64 pm_entry.asm -o pm_entry.o

idt_asm.o: idt_asm.asm
	$(AS) -f elf64 idt_asm.asm -o idt_asm.o

clean:
	rm -f *.o kernel.elf