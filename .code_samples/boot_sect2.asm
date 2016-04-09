[org 0x7c00]

; the BIOS puts the boot drive value in dl, save it
mov [BOOT_DRIVE], dl

; set the base pointer and stack pointer to somewhere out of the way
mov bp, 0x8000
mov sp, bp

; set 0x9000 as the place where we will read the contents into
mov bx, 0x9000
mov dh, 3
mov dl, [BOOT_DRIVE]

call disk_load

jmp $


%include "print/print_string.asm"
%include "disk/disk_load.asm"

BOOT_DRIVE db 0

times 510-($-$$) db 0
dw 0xaa55
times 256 dw 0xdada
times 256 dw 0xface
