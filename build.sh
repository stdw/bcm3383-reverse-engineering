mips-linux-gcc main.c -o exe -mips32 -T ./ldscript -fno-builtin -nostdlib -nodefaultlibs -nostartfiles
mips-linux-objcopy -O binary -j .text -j .data -j .rodata exe bin
 
