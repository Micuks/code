ifndef GCCPREFIX
	GCCPREFIX :=x86_64-elf-
endif

AS := nasm
CC := $(GCCPREFIX)gcc
LD := $(GCCPREFIX)ld
OBJCOPY := $(GCCPREFIX)objcopy
CFLAGS := -Wall -m32 -fno-pie
QEMU := qemu-system-i386

OBJS := ipl.bin
IMG := haribote.img

QEMU_FLAGS :=

ifdef DEBUG
	QEMU_FLAGS += -lldb tcp::1234 -S
	CFALGS += -g
endif

all: $(OBJS) image

ipl.bin:
	$(AS) -f bin ipl.asm -o ipl.bin -l ipl.lst

image: ipl.bin
	dd if=ipl.bin of=$(IMG) bs=512 count=1 conv=notrunc

clean:
	rm -rf ipl.bin
	rm -rf $(IMG)

qemu: all
	$(QEMU) -fda $(IMG) $(QEMU_FLAGS)
