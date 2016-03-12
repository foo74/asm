; check if the value is the null, 0, which is the end of our string if is not then print
; the char, otherwise jump to end 
CHECK_IT:
cmp al, 0
jne PRINT_STUFF
jmp THE_END

; BIOS interrupt 0x10 which prints the ascii based on the value in al
; add 1 to the address so we go to the next byte then get the value
; of the next char and put it in al register then jump to check_it
PRINT_STUFF:
int 0x10         ; print the character
add bx, 1
mov al, [bx]
jmp CHECK_IT

