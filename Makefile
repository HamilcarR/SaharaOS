
EXEC = SaharaOS
BOOTLOADER = bootloader/bootloader.bin
KERNEL = kernel/kernel.bin


all : run


debug : $(EXEC)
	qemu-system-x86_64 -S  -gdb tcp::9000 $?


run : $(EXEC)
	qemu-system-x86_64 -d guest_errors $?
	
disassemble : $(EXEC)
	ndisasm -b 32 $? | cat


$(EXEC) : assemble

assemble: $(BOOTLOADER) $(KERNEL)
	cat $^ > $(EXEC)
	qemu-img resize $(EXEC) +20K

$(BOOTLOADER): 
	cd bootloader/ && make

$(KERNEL):
	 cd kernel/ && make

total_clean: clean
	rm $(EXEC)

clean : 
	cd kernel/ && make clean
	cd bootloader/ && make clean
