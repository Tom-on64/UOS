#!/usr/local/bin/bash

nasm "src/boot.asm" -f bin -o "build/boot.bin"
nasm "src/kernel/entry.asm" -f elf -o "build/kernel_entry.o"
nasm "src/empty.asm" -f bin -o "build/empty.bin"
for file in ./src/kernel/*.c; do
    basename "$file"
    f="$(basename -- $file)"
    i386-elf-gcc -ffreestanding -m32 -g -c "${file}"  -o "build/${f}.o"
done

i386-elf-ld -o "build/full_kernel.bin" -Ttext 0x1000 build/*.o --oformat binary

cat "build/boot.bin" "build/full_kernel.bin" "build/empty.bin" > "build/main.bin"

./run.sh
