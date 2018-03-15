[bits 16]
[org 0x7c00]

mov ax,0x00
mov ss,ax
mov ds,ax
mov bp,0x9000
mov sp,bp
mov [BOOT_DRIVE],dl 

call init_16

call load_kernel

call init_32

[bits 32]

start_code:		;init_32 jumps to this label instead of using 'ret' as the stack address will be changed, so use this label only.
jmp BOOTCODE			;This is where our 32 bit code starts!


%include "../include/load_kernel.asm"
%include "../include/init_16.asm"
%include "../include/print16.asm"
%include "../include/init_32.asm"
%include "../include/print32.asm"

times 510-($-$$) db 0x00
dw 0xaa55
