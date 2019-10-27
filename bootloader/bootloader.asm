%ifndef BOOTLOADER_ASM
%define BOOTLOADER_ASM

%include "hexprint.asm"
%include "user_inputs.asm"



load_bootloader:

	mov SI , stby_msg
	call print_string


	ret 





stby_msg db "loading bootloader..." , 0x0D , 0x0A , 0x0


















%endif
