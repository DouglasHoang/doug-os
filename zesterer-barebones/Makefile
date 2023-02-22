CC = i686-elf-gcc
CC_FLAGS = -std=gnu99 -ffreestanding -g -c
LINK_FLAGS = -ffreestanding -nostdlib -g -T

build: kernel.o start.o
	${CC} ${LINK_FLAGS} linker.ld start.o kernel.o -o mykernel.elf -lgcc

kernel.o:
	${CC} ${CC_FLAGS} kernel_1.c -o kernel.o

start.o:
	${CC} ${CC_FLAGS} start.s -o start.o

clean:
	rm -f *.o
	rm -f *.elf