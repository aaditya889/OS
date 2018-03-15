[BITS 16]
BOOTCODE equ 0x1000

load_kernel:
mov ax,0x00
mov es,ax
mov ah,0x00
mov al,7 	;sectors to read
mov dl,[BOOT_DRIVE]
call readdrive
mov bx,SUCCESS
call print16

readdrive:
push ax
mov ah,0x02	;BIOS read function
mov bx,BOOTCODE
mov ch,0x00	;Cylinder
mov dh,0x00	;Head
mov cl,0x02	;Sector (base 1).
int 0x13
jc disk_error1
pop si
mov ah,0x00
cmp si,ax
jne disk_error2
ret

disk_error1:
mov bx,ERROR_MSG
call print16
jmp $

disk_error2:
mov bx,ERROR_MSG2
call print16
jmp $



BOOT_DRIVE:
db 0
ERROR_MSG:
db "1. error reading disk!",0
ERROR_MSG2:
db "2. error reading disk!",0
SUCCESS:
db 'successfully read the kernel code!',0
















