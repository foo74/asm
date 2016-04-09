######################################################################################
# A makefile for building our custom bootstrapped operating system (from scratch).
# by Foo74 -- April 09, 2016
######################################################################################

# Default target is our custom kernel.
all: os-image

run: all
	qemu-system-x86_64 \
 		-drive file=os-image,format=raw,index=0,media=disk \
    		-drive file=os-image,format=raw,index=1,media=disk

# The binary of our kernel that we will cat with boot sector code.
kernel.bin: kernel_entry.o kernel.o kernel.o
	ld -melf_i386 -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary

# The main kernel code.
kernel.o : kernel.c
	gcc -m32 -ffreestanding -c kernel.c -o kernel.o

# The kernel entry code that ensures we get to our main in kernel.c.
kernel_entry.o : kernel_entry.asm
	nasm kernel_entry.asm -f elf -o kernel_entry.o

# Our custom boot sector code for bootstrapping our kernel.
boot_sect.o : boot_sect.asm
	nasm boot_sect.asm -f bin -o boot_sect.bin

# The main custom kernel that we can then run with Qemu or burn on a boot disk.
os-image: boot_sect.o kernel.bin kernel_entry.o
	cat boot_sect.bin kernel.bin > os-image
	dd if=/dev/zero bs=512 count=60 >> os-image

# Clean all the binary and object files.
clean:
	rm *.bin *.o os-image
