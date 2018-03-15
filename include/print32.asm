;PASS THE START ADDRESS OF THE STRING IN EBX AND CALL PRINT32

[bits 32]

VIDEO_MEM equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print32:		;store the start address of the string in ebx
pusha
mov ah,WHITE_ON_BLACK
mov edx,VIDEO_MEM
loopp32:
mov al,[ebx]
cmp al,0
je endloopp32
mov [edx],ax
add edx,2
add ebx,1
jmp loopp32

endloopp32:
popa
ret
