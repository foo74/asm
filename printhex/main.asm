[org 0x7c00]


; test by putting in a hex value to dx register
mov dx, 0x1a3f

call PRINT_ADDR


; jump infinitely
jmp $

; include a function
%include "printaddr.asm"

; pad the boot sector with 0s after our code until the magic 0xaa55
times 510-($-$$) db 0
dw 0xaa55
