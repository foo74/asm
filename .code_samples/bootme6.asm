[org 0x7c00]

mov ah, 0x0e

mov bx, 50

cmp bx, 4
jle lessorequalto4

cmp bx, 40
jl lessthan40

jmp else

lessorequalto4:
mov al, 'A'
int 0x10
jmp theend

lessthan40:
mov al, 'B'
int 0x10
jmp theend

else:
mov al, 'Z'
int 0x10

theend:

jmp $

times 510-($-$$) db 0
dw 0xaa55
