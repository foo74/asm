;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; load DH sectors to ES:BX from drive DL
; assumes ES:BX contains the place to read to
; assumes DH is the number of sectors to read
; assumes DL contains the drive to read from
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
diskload:

; store dx on stack so later we can recall how many sectors were
; requested to be read, even if it is altered in the meantime
push dx

mov ah, 0x02		; BIOS read sector function

mov al, dh		; how many sectors to read

mov ch, 0x00		; cyclinder
mov cl, 0x02		; start reading from this sector
mov dh, 0x00		; the head to use
;mov dl, 0x80		; the drive to read from, BIOS puts the boot drive in dl for us though

; bios interrupt
int 0x13

; jump if error (ie carry flag set)
jc DISK_ERROR1

; pop dx now that we are done using it in the dh for the head. we will
; compare to make sure al is the number expected we wanted to read
pop dx

; check to see if the sectors we are are the number we expected
cmp al, dh
jne DISK_ERROR2

; return to calling function
ret

DISK_ERROR1:
mov bx, DISK_ERROR_MSG1
call printstring

DISK_ERROR2:
mov bx, DISK_ERROR_MSG2
call printstring

; should never get here unless an error message is printed
jmp $

; variables
DISK_ERROR_MSG1: db 'Disk read error! Carry flag set!', 0
DISK_ERROR_MSG2: db 'Disk read error! Did not read the number of sectors exptected!', 0
