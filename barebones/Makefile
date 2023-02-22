CC = i686-elf-gcc
ASM = i686-elf-as
CC_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
BOOT_FILE = boot.s
KERNEL_FILE = kernel.c
LINK_FILE = linker.ld
LINK_FLAGS = -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

build: myos.bin

myos.bin: kernel.o boot.o
	${CC} -T ${LINK_FILE} -o myos.bin ${LINK_FLAGS}

kernel.o:
	${CC} ${CC_FLAGS} -c ${KERNEL_FILE} -o kernel.o

boot.o:
	${ASM} ${BOOT_FILE} -o boot.o

qemu: myos.bin
	qemu-system-i386 -kernel myos.bin

clean:
	rm -f *.o
	rm -f *.bin