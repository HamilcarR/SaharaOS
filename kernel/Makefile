SRC = $(wildcard src/*.c)
INCLUDES = $(wildcard includes/*.h)
OBJ = ${SRC:.c=.o}
OBJ_DIR = ./obj/
SRC_DIR = src/
EXEC = kernel.bin

all : $(EXEC)
	


kernel.bin : src/kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary 
	
%.o : %.asm
	nasm -f elf32  $< -o $@

%.o : %.c ${INCLUDES}  
	gcc -m32 -g -ffreestanding -c $< -o $@ 

clean :
	rm -fr *.bin $(SRC_DIR)*.o *.dis 


