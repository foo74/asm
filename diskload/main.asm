;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; simple driver example for the diskload function
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
[org 0x7c00]

; the BIOS puts the boot drive value in dl, save it
mov [BOOT_DRIVE], dl

; set the base pointer and stack pointer to somewhere out of the way
mov bp, 0x8000
mov sp, bp

; set 0x9000 as the place where we will read the contents into
mov bx, 0x9000
mov dh, 2
mov dl, [BOOT_DRIVE]

; call the diskload function, bx and dh, and dl are set for it
call diskload

; move the 0x9000 into dx which is where we will read from and then print value in hex
mov dx, [0x9000]
call printaddr

; now print the next sector which is 512 bytes further
mov dx, [0x9000 + 512]
call printaddr

; hang the program, stop
jmp $

; include a function
%include "../printstring/printstring.asm"
%include "../printhex/printaddr.asm"
%include "diskload.asm"

BOOT_DRIVE: db 0
startme: db 'calling diskload...', 0

times 510-($-$$) db 0
dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xface
