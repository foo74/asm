;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; function that prints two bytes in hex output
; assumes the value is stored in the dx register
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PRINT_ADDR:
; respect the registers and push the values on the stack
pusha

; make sure the bios interrupt is ready to print
mov ah, 0x0e

; zero out bx so we are sure it is clean start
mov bx, 0x0000
mov cx, 0x0000

; move the first byte into bl and cl, we will be shifting
; to the right so we will destroy the second byte, so we
; store a duplicate in cl so we can get the second byte
mov bl, dh
mov cl, dh
call PRINT_BYTE

mov bx, 0x0000
mov cx, 0x0000

mov bl, dl
mov cl, dl
call PRINT_BYTE

; respect the registers and pop the values off the stack.
popa

ret
