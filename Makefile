EXEC = SaharaOS

CC = gcc 
CFLAGS =-v -fno-PIC -fno-stack-protector -std=c11 -m32 -g -ffreestanding -pedantic -Wall  

BOOTLOADER_DIR = ./bootloader
BOOTLOADER = $(BOOTLOADER_DIR)/bootloader.bin


KERNEL_ENTRY = $(BOOTLOADER_DIR)/kernel_entry/kernel_entry.o
KERNEL_ENTRY_FILE = $(BOOTLOADER_DIR)/kernel_entry/kernel_entry.asm
KERNEL = ./kernel.bin
KDEBUG = ./symbol-debug-kernel
KERNEL_DIR = ./kernel
KERNEL_SRC_DIR = $(KERNEL_DIR)/src
KERNEL_INC_DIR = $(KERNEL_DIR)/includes
KERNEL_OBJ_DIR = $(KERNEL_DIR)/obj

DRIVERS_DIR = ./drivers
DRIVERS_OBJ_DIR = $(DRIVERS_DIR)/obj


BOOTLOADER_SRC = $(wildcard $(BOOTLOADER_DIR)/*.asm)
KERNEL_OBJ = $(wildcard $(KERNEL_OBJ)/*.o)
KERNEL_SRC = $(wildcard $(KERNEL_SRC_DIR)/*.c)
KERNEL_INC = $(wildcard $(KERNEL_INC_DIR)/*.h)
DRIVERS_SRC = $(wildcard $(DRIVERS_DIR)/*/src/*.c)
DRIVERS_INC = $(wildcard $(DRIVERS_DIR)/*/includes/*.h)

OBJ_K = $(KERNEL_SRC:.c=.o)
OBJ_D = $(DRIVERS_SRC:.c=.o)



all : run


$(EXEC) : assemble

debug : $(EXEC) $(KDEBUG)
	qemu-system-i386 -S -gdb tcp::9000 $<

run : $(EXEC) 
	qemu-system-i386 -d guest_errors $<

disassemble : $(EXEC)
	ndisasm -b 32 $? | cat





assemble : $(BOOTLOADER) $(KERNEL)
	cat $^ > $(EXEC) 
	qemu-img resize $(EXEC) +20K



#Kernel build and drivers

$(KERNEL) : $(KERNEL_ENTRY) $(OBJ_D) $(OBJ_K)   
	ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

$(KDEBUG) : $(KERNEL_ENTRY) $(OBJ_D) $(OBJ_K) 
	ld -melf_i386 -o $@ -Ttext 0x1000 $^ 

%.o : %.c $(KERNEL_INC) $(DRIVERS_INC)
	$(CC) $(CFLAGS) -c $< -o $@


#Bootloader build
KERNEL_ENTRY : $(KERNEL_ENTRY)

BOOTLOADER : $(BOOTLOADER)

$(KERNEL_ENTRY):  
	nasm -f elf32 -F dwarf -g $(KERNEL_ENTRY_FILE) -o $@

$(BOOTLOADER) :
	nasm $(BOOTLOADER_DIR)/boot.asm -i$(BOOTLOADER_DIR)/ -f bin -o $@




#Clean the shit
remove_obj : 
	find . -type f -name "*.o" -delete

remove_kernel : 
	rm $(KERNEL_BIN) 

remove_bootloader : 
	rm $(BOOTLOADER)

remove_exec : 
	rm $(EXEC)


clean : 
	rm -f $(KERNEL)
	rm -f $(KDEBUG)
	rm -f $(BOOTLOADER)
	rm -f $(EXEC)
	find . -type f -name "*.o" -delete

	




