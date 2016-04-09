# some
kernel.bin: kernel_entry.o kernel.o kernel.o
	ld -melf_i386 -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary

kernel.o : kernel.c
	gcc -m32 -ffreestanding -c kernel.c -o kernel.o

kernel_entry.o : kernel_entry.asm
	nasm kernel_entry.asm -f elf -o kernel_entry.o

boot_sect.o : boot_sect.asm
	nasm boot_sect.asm -f bin -o boot_sect.bin

os-image: boot_sect.o kernel.bin kernel_entry.o
	cat boot_sect.bin kernel.bin > os-image
	dd if=/dev/zero bs=512 count=60 >> os-image
