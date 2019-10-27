%ifndef DEBUG_ASM
%define DEBUG_ASM 
%include "disk_io.asm"

debug_menu:
	mov SI , DEBUG_TEXT
	call print_string


print_registers : 
	mov SI , reg_AX 
	call print_string
	mov DX , AX 
	call hexout_16
	mov SI , ret_char
	call print_string
	mov SI , reg_CX
	call print_string
	mov DX , CX
	call hexout_16
	mov SI , ret_char
	call print_string
	jmp loop




reg_AX db  "AX : " , 0x20 , 0x0 
reg_CX db  "CX : " , 0x20 , 0x0
ret_char db 0x0D , 0x0A , 0x0
DEBUG_TEXT db "Debugging menu" , 0x0D , 0x0A , 0x0












%endif


