%include "bootheader.asm" 


	mov SI , msg
	call print_string
	mov SI , msg_1
	call print_string
	mov SI , msg_2
	call print_string
	mov SI , msg_3
	call print_string	
	call user_input
	call print_char
	jmp $

%include "user_inputs.asm" 
msg db "SaharaOS" ,0x0D, 0x0A, 0x0
msg_1 db "16 bits mode ... Write something ?" , 0x0D , 0x0A , 0x0
msg_2 db "1) yes(y)" , 0x0D , 0x0A , 0x0
msg_3 db "2) no(n)" , 0x0D , 0x0A , 0x0
times 510 - ($-$$) db 0 
dw 0xaa55


