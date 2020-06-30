/*debug script*/
ENTRY(_start) 

OUTPUT_ARCH(i386)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{

	. = 0x1000;

	.text BLOCK(4K) : ALIGN(4K) 
	{
		*(.multiboot)
		*(.text)

	}
	
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
	
	.data BLOCK(4K) : ALIGN(4K) 
	{
		*(.data)
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)

	}




}


_END_KERNEL_ADDRESS = ALIGN(4K) ;  


