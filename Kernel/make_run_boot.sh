#!/bin/bash

sudo gcc -ffreestanding -m32 -c kernel.c -o kernel.o
sudo gcc -ffreestanding -m32 -c make_idt.c -o make_idt.o
sudo gcc --freestanding -m32 -c ../drivers/display.c -o ../drivers/display.o
nasm ../boot/kernel_entry.asm -f elf -o ../boot/kernel_entry.o
nasm ../boot/bootloader.asm -f bin -o ../boot/bootloader.bin
nasm idt.asm -f elf -o idt.o
ld -o kernel.bin -Ttext 0x1000 -m elf_i386 ../boot/kernel_entry.o ../drivers/display.o idt.o kernel.o make_idt.o --oformat binary
cat ../boot/bootloader.bin kernel.bin>os_image
rm *.o *.bin
sudo makeboot /dev/sdb os_image

echo done!
qemu-system-x86_64 os_image
