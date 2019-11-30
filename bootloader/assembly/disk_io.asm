%ifndef DISK_IO
%define DISK_IO
%include "print.asm"

reset_floppy:
	mov AH , 0x00
	mov DL , 0x00
	int 0x13
	jc reset_floppy
	ret
	

disk_load:
	mov SI , MSG_DISK_LOADING
	call print_string
	mov AH , 0x02
	mov AL , DH
	mov CH , 0x00
	mov DH , 0x00
	mov CL , 0x02
	int 0x13
	jc disk_error 
	mov SI , DISK_R_OK
	call print_string
	
	ret

disk_error :
	
	mov SI , DISK_R_ERR
	call print_string
	mov DL , AL 
	call hexout_8
	ret




D_SUCCESS db "disk head reset ok" , 0x0D , 0x0A , 0x0

DISK_R_OK db "disk read OK" , 0x0D , 0x0A , 0x0

DISK_R_ERR db "disk read error:" ,  0x0

MSG_DISK_LOADING db "Loading disk ..." , 0x0D , 0x0A , 0x0






%endif
