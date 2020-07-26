EXEC = SaharaOS

CC = gcc 
CFLAGS = -fno-PIC -mno-red-zone -fno-stack-protector  -m32 -g -ffreestanding -pedantic -Wall -Wextra 

BOOTLOADER_DIR = ./bootloader
BOOTLOADER = $(BOOTLOADER_DIR)/bootloader.bin

ASM_DIR = ./kernel/asm
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

ASM_SRC = $(wildcard $(ASM_DIR)/*.asm)
BOOTLOADER_SRC = $(wildcard $(BOOTLOADER_DIR)/assembly/*.asm)
KERNEL_OBJ = $(wildcard $(KERNEL_OBJ)/*.o)
KERNEL_SRC = $(wildcard $(KERNEL_SRC_DIR)/*.c)
KERNEL_INC = $(wildcard $(KERNEL_INC_DIR)/*.h)
DRIVERS_SRC = $(wildcard $(DRIVERS_DIR)/*/src/*.c)
DRIVERS_INC = $(wildcard $(DRIVERS_DIR)/*/includes/*.h)

OBJ_K = $(KERNEL_SRC:.c=.o)
OBJ_D = $(DRIVERS_SRC:.c=.o)
OBJ_ASM_K = $(ASM_SRC:.asm=.o) 


all : run


$(EXEC) : assemble

debug : $(EXEC) $(KDEBUG)
	qemu-system-i386  -d int -no-reboot -no-shutdown -soundhw pcspk -S -gdb tcp::9000 $<

run : $(EXEC) 
	qemu-system-i386 -s -soundhw pcspk -d int  -no-reboot -no-shutdown $< 

disassemble : $(KERNEL)
	ndisasm -b 32 $? | cat



assemble : $(BOOTLOADER) $(KERNEL) 
	cat $^ > $(EXEC) 
	qemu-img resize $(EXEC) +150K

OBJDUMP : $(KERNEL_ENTRY) $(OBJ_D) $(OBJ_K) $(OBJ_ASM_K) 
	ld -T dscript.ld -o $@ $^

#Kernel build and drivers

$(KERNEL) : $(KERNEL_ENTRY) $(OBJ_D) $(OBJ_K) $(OBJ_ASM_K)
	ld -T rscript.ld -o $@ $^

$(KDEBUG) : $(KERNEL_ENTRY) $(OBJ_D) $(OBJ_K) $(OBJ_ASM_K) 
	ld -melf_i386 -T dscript.ld -o $@ $^
	ld -T dscript.ld -o $@ $^ 

%.o : %.c $(KERNEL_INC) $(DRIVERS_INC) 
	$(CC) $(CFLAGS) -c $< -o $@

%.o : %.asm 
	nasm -f elf32 -F dwarf -g $< -o $@

#Bootloader build
KERNEL_ENTRY : $(KERNEL_ENTRY)

BOOTLOADER : $(BOOTLOADER)

$(KERNEL_ENTRY):  
	nasm -f elf32 -F dwarf -g $(KERNEL_ENTRY_FILE) -o $@

$(BOOTLOADER) :
	nasm $(BOOTLOADER_DIR)/assembly/boot.asm -i $(BOOTLOADER_DIR)/assembly -f bin -o $@




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
	rm -f OBJDUMP
	find . -type f -name "*.o" -delete

	




