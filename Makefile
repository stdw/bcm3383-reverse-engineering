TCPREFIX=mips-linux-
CC=$(TCPREFIX)gcc
OBJCOPY=$(TCPREFIX)objcopy
LDSCRIPT=./ldscript
CFLAGS=-march=mips32 -mabi=eabi -mno-abicalls -fno-builtin -nostdlib -nodefaultlibs -nostartfiles -T $(LDSCRIPT)

default: bin

elf: measure.c
	$(CC) measure.c -o $@ $(CFLAGS)

bin: elf
	$(OBJCOPY) -O binary -j .text -j .data -j .rodata $< $@


.PHONY: clean

clean:
	rm -f elf bin
