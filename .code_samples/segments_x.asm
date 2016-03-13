; set the high byte of ax for the BIOS interrupt
mov ah, 0x0e

; get the value of the 'real' address at the memory address of the_secret 'X'
; since we don't take into account segment register offset we get nonsense value instead of 'X'
mov al, [the_secret]
int 0x10

; now load 0x7c0 into the bx register and then into the data segment ds register (since
; (we can't load ds directly). The offset of ds is then used 0x7c0 * 16 = 0x7c00
; which is where our data starts. this is the same as using the [org 0x7c00] to set
; our offset. now when we move the value of [the_secret] the offset is correct
; and we get the value we are looking for which is 'X'
mov bx, 0x7c0
mov ds, bx
mov al, [the_secret]
int 0x10

; we can also specify the address with an offset using the data segment ds register
; directly. the notation is a : in between the data segment register ds and the 
; address of our secret 'X'. Since the offset is correct we get the 'X' again. 
mov al, [ds:the_secret]
int 0x10

; we can use other segmentation registers to get to the exact same 'real' memory
; address too. in this case we are using the 'extra' segment register es. since
; the offset is correct we get the 'X' again
mov bx, 0x7c0
mov es, bx
mov al, [es:the_secret]
int 0x10

jmp $

the_secret:
db "X"

times 510-($-$$) db 0
dw 0xaa55
