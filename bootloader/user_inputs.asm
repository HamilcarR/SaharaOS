%include "print.asm" 




;check AL for scanned key 

user_input:
	mov CL , 0x79 ; 'y' char
	mov CH , 0x6E ; 'n' char

loop:

	mov AH , 0x0
	int 0x16
	cmp AL , CL
	je do_something
	cmp AL , CH
	je do_nothing
	push SI
	mov SI , ERROR
	call print_string
	call print_char
	pop SI
	jmp loop
	
do_nothing:
	jmp finish	
	
do_something:
	call user_enter_string
	jmp finish
	
	
finish:	
	ret
		


;store string in DL

user_enter_string:
loop_string:
	mov AH , 0x0
	int 0x16
	call print_char
	cmp AL , 0x0D ; enter key
	je finish_1
	mov DL , AL
	jmp loop_string

finish_1:
	mov DL , 0x0
	jmp finish

ERROR db "choose (y) or (n) , you printed : " , 0x0D , 0x0A , 0x0

