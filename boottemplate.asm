[org 0x7c00]

;some code here

jmp $

; include a function
;%include "print_string.asm"


times 510-($-$$) db 0
dw 0xaa55
