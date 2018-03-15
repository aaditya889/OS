[bits 16]

init_16:
mov bx,MSG_16
call print16
ret

MSG_16:
db "INSIDE 16 BIT REAL MODE!",0


