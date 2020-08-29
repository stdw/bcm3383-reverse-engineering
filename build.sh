mips-linux-gcc main.c -o exe -march=mips32 -mabi=eabi -mno-abicalls -T ./ldscript -fno-builtin -nostdlib -nodefaultlibs -nostartfiles
mips-linux-objcopy -O binary -j .text -j .data -j .rodata exe bin
 
