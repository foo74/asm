; function to print a byte, assumes byte is in bl and cl both contain the same byte
PRINT_BYTE:
; respect the registers by pushing them all on the stack
pusha

; first isolate the first digit of the byte, we will use bh for this
shr bl, 4
; compare to see if it is a lower case a-f digit.
cmp bl, 0xa
jl CHECK_ZERO_TO_NINE_FIRST_DIGIT
cmp bl, 0xf
jg CHECK_ZERO_TO_NINE_FIRST_DIGIT

; passed the test for a-f, it is a digit between a-f add 0x57 to get the ascii code
add bl, 0x57

; print the ascii code
mov al, bl
int 0x10

jmp SECONDDIGIT

; check if it is between 0-9
CHECK_ZERO_TO_NINE_FIRST_DIGIT:
cmp bl, 0x0
jl ENDFUNC
cmp bl, 0x9
jg ENDFUNC

; passed the test for 0-9, it is a digit between 0-9 add 0x30 to get the ascii code
add bl, 0x30

; print the ascii code
mov al, bl
int 0x10

SECONDDIGIT:

; now isolate the second digit of the byte, we will use cl for this
and cl, 0x0F

; compare to see if it is a lower case a-f digit.
cmp cl, 0xa
jl CHECK_ZERO_TO_NINE_SECOND_DIGIT
cmp cl, 0xf
jg CHECK_ZERO_TO_NINE_SECOND_DIGIT

; passed the test, it is a digit between a-f add 0x57 to get the ascii code
add cl, 0x57
mov al, cl
int 0x10

jmp ENDFUNC

; check if it is between 0-9
CHECK_ZERO_TO_NINE_SECOND_DIGIT:
cmp cl, 0x0
jl ENDFUNC
cmp cl, 0x9
jg ENDFUNC

; passed the test for 0-9, it is a digit between 0-9 add 0x30 to get the ascii code
add cl, 0x30

; print the ascii code
mov al, cl
int 0x10

ENDFUNC:

; respect the registers by popping them all off the stack and return to before call.
popa

ret
