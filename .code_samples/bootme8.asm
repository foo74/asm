[org 0x7c00]

mov bx, NEW_LINE
call print_string
mov bx, NEW_LINE
call print_string
mov bx, WELCOME_MSG
call print_string
mov bx, NEW_LINE
call print_string
mov bx, NEW_LINE
call print_string
mov bx, OPTION_ONE
call print_string
mov bx, NEW_LINE
call print_string
mov bx, OPTION_TWO
call print_string
mov bx, NEW_LINE
call print_string
mov bx, OPTION_THREE
call print_string
mov bx, NEW_LINE
call print_string
mov bx, OPTION_FOUR
call print_string


jmp $

%include "print_string.asm"

WELCOME_MSG:
db 'Welcome to foo1 boot program. Chose an option...', 0

NEW_LINE:
db 0x0A, 0x0D,  0x00

OPTION_ONE:
db '1. First option.', 0

OPTION_TWO:
db '2. Second option.', 0

OPTION_THREE:
db '3. Third option.', 0

OPTION_FOUR:
db '4. Fourth option.', 0

times 510-($-$$) db 0
dw 0xaa55
