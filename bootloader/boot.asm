%ifndef BOOT_ASM
%define BOOT_ASM
%include "bootheader.asm" 







        mov SI , msg
        call print_string
	mov SI , msg_1
	call print_string
	mov SI , msg_2
	call print_string
	mov SI , msg_3
	call print_string
	mov SI , msg_4
	call print_string
	call user_input
	call print_char
		
	jmp $




%include "user_inputs.asm" 





msg db "SaharaOS" ,0x0D, 0x0A, 0x00

msg_1 db "16 bits mode ... Write a memory location (16 bits or 8 bits) :" , 0x0D , 0x0A , 0x0

msg_2 db "1) (y)es" , 0x0D , 0x0A , 0x0

msg_3 db "2) (n)o" , 0x0D , 0x0A , 0x0

msg_4 db "3) (q)uit" , 0x0D , 0x0A , 0x0

ERROR db "choose (y) or (n) , you printed : " , 0x0D , 0x0A , 0x0

QUIT db "no message will be displayed." , 0x0D , 0x0A , 0x0




times 510 - ($-$$) db 0 
dw 0xaa55

%endif 
