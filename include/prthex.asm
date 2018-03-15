;pass the starting address in si and number of bytes in ch (max 256).

printhex:
pusha
mov ah,0x0e		;BIOS typewriter function.
uloop:
mov cl,[si]
mov dl,2
loop:
mov bh,0x00
mov bl,0xf0
and bl,cl
shr bl,4
mov al,[num_str+bx]
int 0x10
shl cl,4
dec dl
cmp dl,0
je endloop1
jmp loop
endloop1:
dec ch
inc si
cmp ch,0
je endl
mov al,' '
int 0x10
int 0x10
jmp uloop
endl:
popa
ret

num_str:
db '0123456789abcdef'
