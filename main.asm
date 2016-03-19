; set our segment to 0x7c00
[org 0x7c00]

; move the string into bx and then call printstring
mov bx, BOOTMSG
call printstring

; move the one byte hex into dx and call printaddr
mov dx, 0xd0d0
call printaddr

; hang
jmp $

; include printstring and printaddr functions
%include "printstring/printstring.asm"
%include "printhex/printaddr.asm"

; data
BOOTMSG: db 'booting OS foo...', 0

; pad out 0's to the rest of the 510 bytes in this first
; sector and then put the magic boot number
times 510-($-$$) db 0
dw 0xaa55
