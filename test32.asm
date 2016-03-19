;[org 0x7c00]

[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

mov edx, VIDEO_MEMORY

mov al, 'X'
mov ah, WHITE_ON_BLACK

mov [edx], ax

jmp $

; include a function
;%include "print_string.asm"


times 510-($-$$) db 0
dw 0xaa55
