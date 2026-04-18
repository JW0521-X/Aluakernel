CC = x86_64-elf-gcc
LD = x86_64-elf-ld
AS = nasm
OBJCOPY = x86_64-elf-objcopy

CFLAGS = -ffreestanding -m64 -O2 -nostdlib -Ikernel/include -mno-sse -mno-sse2 -mno-mmx -mno-80387

LDFLAGS = -T linker.ld

OBJS = \
    build/entry.o \
    build/kernel.o \
    build/font.o

all: build alua.bin

build:
	mkdir -p build

build/entry.o: kernel/entry.asm
	$(AS) -f elf64 $< -o $@

build/kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

build/font.o: cp850-8x16.psf
	$(OBJCOPY) -I binary --set-section-flags .data=alloc,load,contents \
		-O elf64-x86-64 -B i386 $< $@

alua.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

alua.bin: alua.elf
	$(OBJCOPY) -S -O binary $< $@

clean:
	rm -rf build *.elf *.bin
