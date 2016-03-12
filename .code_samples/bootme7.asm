; let the program know where our code starts from, the BIOS put us here.
[org 0x7c00]

; make sure bx is 0 then load the start address for the string HELLO_STRING
mov bx, 0x0000
mov bx, HELLO_STRING

; the bx register contains the 16-bit address of the start of our string. need to load the
; value at that first address, which is the ascii code of our first char.
; load the value, the ascii code, of the first char in our string into ax low register, al
mov al, [bx]

%include "printstring.asm"


; the end of the program
THE_END:
jmp $

; the string that we want to print and we put a 0 on the end so we know when
; the string is done
HELLO_STRING:
db 'Hello World', 0

; load the magic number with 0's before it, the result is that our
; instructions are from 0x0000 and then all 0's and then the magic
; number for boot which is 0xaa55
times 510-($-$$) db 0
dw 0xaa55
