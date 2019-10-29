SRC = $(wildcard src/*.c)
INCLUDES = $(wildcard includes/*.h)
OBJ = ${SRC:.c=.o}
OBJ_DIR = ./obj/
SRC_DIR = src/
EXEC = kernel.bin

all : $(EXEC)
	


kernel.bin : src/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary 
	
%.o : %.asm
	nasm -f elf64  $< -o $@

%.o : %.c ${INCLUDES}  
	gcc -ffreestanding -c $< -o $@ 

clean :
	rm -fr *.bin $(SRC_DIR)*.o *.dis 


