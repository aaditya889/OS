[bits 32]
[extern make_idt]
global _start
_start:
call make_idt
jmp $
