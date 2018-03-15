[BITS 32]
[extern keyboard_handler]
[extern print]
[global load_idt]
[global keyboard_handler_asm]
load_idt:

mov eax,[esp+4]
lidt [eax]
sti
ret

keyboard_handler_asm:
pushad
cld
call keyboard_handler
popad
iret

