[org 0x7c00]

mov ah, 0x0e
mov al, 'A'
int 0x10

jmp say_hello
return_here:

mov ah, 0x0e
mov al, 'B'
int 0x10

jmp $

say_hello:
mov ah, 0x0e
mov al, 'B'
int 0x10
jmp return_here

 
times 510-($-$$) db 0

dw 0xaa55

