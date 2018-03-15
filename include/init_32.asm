bits 16

init_32:
cli
lgdt [gdt_descriptor]
mov eax,cr0
or eax,0x01
mov cr0,eax

jmp CODE_SEG:in_32

%include "../include/gdt1.asm"

bits 32

in_32:
mov ax,DATA_SEG
mov ss,ax
mov ds,ax
mov es,ax
mov fs,ax
mov gs,ax

mov ebp,0x90000
mov esp,ebp
mov ebx,MSG_32
call print32

jmp start_code

MSG_32:
db "INSIDE 32 BIT PROTECTED MODE!",0


