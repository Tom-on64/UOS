#!/usr/local/bin/bash

nasm "src/boot.asm" -f bin -o "build/boot.bin"
nasm "src/kernel_entry.asm" -f elf -o "build/kernel_entry.o"
nasm "src/empty.asm" -f bin -o "build/empty.bin"
i386-elf-gcc -ffreestanding -m32 -g -c "src/kernel/main.c" -o "build/kernel.o"

i386-elf-ld -o "build/full_kernel.bin" -Ttext 0x1000 "build/kernel_entry.o" "build/kernel.o" --oformat binary

cat "build/boot.bin" "build/full_kernel.bin" "build/empty.bin"  > "build/main.bin"

./run.sh
