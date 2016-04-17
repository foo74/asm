######################################################################################
# A makefile for building our custom bootstrapped operating system (from scratch).
# by Foo74 -- April 09, 2016
# In gcc the -c flag is to compile to .o object file. The -Wall flag is for all warnings.
######################################################################################

# Default target is our custom kernel.
all: os-image

run: all
	qemu-system-x86_64 \
 		-drive file=os-image,format=raw,index=0,media=disk \
    		-drive file=os-image,format=raw,index=1,media=disk

# The binary of our kernel that we will cat with boot sector code.
kernel/kernel.bin: kernel/kernel_entry.o kernel/kernel.o drivers/screen.o drivers/low_level.o kernel/util.o
	ld -melf_i386 -o kernel/kernel.bin -Ttext 0x1000 kernel/kernel_entry.o kernel/util.o kernel/kernel.o drivers/screen.o drivers/low_level.o --oformat binary

# Driver for screen IO.
drivers/screen.o : drivers/screen.c
	gcc -m32 -ffreestanding -c drivers/screen.c -o drivers/screen.o

# Driver for low level IO.
drivers/low_level.o : drivers/low_level.c
	gcc -m32 -ffreestanding -c drivers/low_level.c -o drivers/low_level.o

# Driver for kernel utils.
kernel/util.o : kernel/util.c
	gcc -m32 -ffreestanding -c kernel/util.c -o kernel/util.o

# The main kernel code.
kernel/kernel.o : kernel/kernel.c 
	gcc -m32 -ffreestanding -c kernel/kernel.c -o kernel/kernel.o

# The kernel entry code that ensures we get to our main in kernel.c.
kernel/kernel_entry.o : kernel/kernel_entry.asm
	nasm kernel/kernel_entry.asm -f elf -o kernel/kernel_entry.o

# Our custom boot sector code for bootstrapping our kernel.
boot/boot_sect.o : boot/boot_sect.asm
	nasm boot/boot_sect.asm -f bin -o boot/boot_sect.bin

# The main custom kernel that we can then run with Qemu or burn on a boot disk.
os-image: boot/boot_sect.o kernel/kernel.bin kernel/kernel_entry.o kernel/util.o
	cat boot/boot_sect.bin kernel/kernel.bin > os-image
	dd if=/dev/zero bs=512 count=60 >> os-image

# Clean all the binary and object files.
clean:
	rm kernel/*.bin kernel/*.o drivers/*.o boot/*.bin os-image
