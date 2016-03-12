print_string:
; the bx register contains the 16-bit address of the start of our string. need to load the
; value at that first address, which is the ascii code of our first char.
; load the value, the ascii code, of the first char in our string into ax low register, al
mov al, [bx]

; set the ah to the code for BIOS printing teletype char to screen
mov ah, 0x0e

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
mov al, 0x0a     ; load ascii code for line feed one line down
int 0x10         ; print out the line feed
mov al, 0x0d     ; load the ascii code for returning carriage to 0, most left
int 0x10         ; print out the carriage return to move back to the most left
add bx, 1
mov al, [bx]
jmp CHECK_IT

; the end of the function
THE_END:
ret
