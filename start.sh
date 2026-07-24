set -ex
rm -rf bin/*
mkdir -p bin
nasm src/boot.s -o bin/boot.bin
CFLAGS="-m32 -ffreestanding -fno-pie -nostdlib -fno-stack-protector -DKERNEL_GIT=\"$(git rev-parse --short HEAD)\""

gcc -m32 -c src/kernel.c -o bin/kernel.o $CFLAGS

gcc -m32 -c src/drivers/txtm.c -o bin/txtm.o $CFLAGS
gcc -m32 -c src/drivers/timer.c -o bin/timer.o $CFLAGS
gcc -m32 -c src/drivers/ps2kb.c -o bin/ps2kb.o $CFLAGS

gcc -m32 -c src/util/convert.c -o bin/convert.o $CFLAGS

gcc -m32 -c src/sys/io.c -o bin/io.o $CFLAGS
gcc -m32 -c src/sys/idt.c -o bin/idt.o $CFLAGS
gcc -m32 -c src/sys/pic.c -o bin/pic.o $CFLAGS

gcc -m32 -c src/mm/mmap.c -o bin/mmap.o $CFLAGS
gcc -m32 -c src/mm/paging.c -o bin/paging.o $CFLAGS

nasm -f elf32 src/sys/isr.s -o bin/isr.o

ld -m elf_i386 -T linker.ld bin/kernel.o bin/txtm.o bin/convert.o bin/io.o bin/isr.o bin/idt.o bin/pic.o bin/timer.o bin/ps2kb.o bin/mmap.o \
        bin/paging.o \
        -o bin/kernel.elf

objcopy -O binary bin/kernel.elf bin/kernel.bin
cat bin/boot.bin bin/kernel.bin > bin/image.bin
truncate -s 65536 bin/image.bin
qemu-system-i386 -drive file=bin/image.bin,format=raw -d int -m 2M
