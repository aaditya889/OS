;store the address of the string in bx register and call print16 to print.
[bits 16]

print16:
pusha
mov ah,0x0e
loop1:
cmp byte [bx],0
je endloop2
mov al,[bx]
int 0x10
inc bx
jmp loop1

endloop2:
popa
ret
