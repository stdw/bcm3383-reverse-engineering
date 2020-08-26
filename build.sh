mips-linux-gcc main.c -o exe -Wl,--section-start=.text=0x80810000 -nostdlib -nodefaultlibs -nostartfiles
dd if=exe skip=65536 bs=1 count=272 > bin
