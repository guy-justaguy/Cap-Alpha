# Cap-Alpha
Cap-Alpha is an operating system kernel based on the 64-bit UEFI architecture. This operating system is still in alpha. this OS is not Unix based but, it has PE and ELF support. Thus, the name Cap-Alpha.  This kernel is still in development so everything may not work as expected. This OS is a kernel project and it has a basic mouse cursor. A compsitor will be implemented. If you want to contribute, please read Contribute.md. Running in QEMU OVMF is recommended. You may need to edit some files for your specific configuration.

if you want to compile please follow these instructions:
1. you have to be on Linux to use these commands. 
2. Install GCC if not available. 
3. Install Make if not available.
4. Install LD if not available.
5. Download the source code.
6. Run `mkdir -p kernel` (in any dir)
7. Now extract the source code inside the new dir. Or run this command: `unzip name_of_source_code_file.zip  /kernel`.
8. Now `cd` into the `/kernel` dir.
9. Now run `make`.
10. A file named `kernel.elf` will appear in the dir.
11. Now run `mkdir -p iso_root`.
12. `cp` the 'kernel.elf' file into iso_root.
13. Go back to the `/kernel dir`.
14. Now run `grub2-mkrescue iso_root -o kernel.iso`.
15. An ISO file called `kernel.iso` should appear.
16. Use QEMU OVMF to boot this ISO.
 If you encounter any problems during the compilation process, please contact <aydin.nawaf@gmail.com> or <tungsahuur1234@gmail.com>
