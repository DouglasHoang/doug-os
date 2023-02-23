CC = i686-elf-gcc
ASM_1 = i686-elf-as
ASM_2 = nasm
CC_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
BOOT_FILE = boot
KERNEL_FILE = kernel.c
LINK_FILE = linker.ld
LINK_FLAGS = -ffreestanding -O2 -nostdlib ${BOOT_FILE}_2.o kernel.o -lgcc

build: myos.bin

myos.bin: kernel.o boot_1.o boot_2.o
	${CC} -T ${LINK_FILE} -o myos.bin ${LINK_FLAGS}

kernel.o:
	${CC} ${CC_FLAGS} -c ${KERNEL_FILE} -o kernel.o

boot_1.o:
	${ASM_1} ${BOOT_FILE}.s -o ${BOOT_FILE}_1.o

boot_2.o:
	${ASM_2} -felf32 ${BOOT_FILE}.asm -o ${BOOT_FILE}_2.o

qemu: myos.bin
	qemu-system-i386 -kernel myos.bin

clean:
	rm -f *.o
	rm -f *.bin