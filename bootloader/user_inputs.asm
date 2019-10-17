%ifndef USER_INPUTS_ASM
%define USER_INPUTS_ASM

%include "print.asm" 
%include "hexprint.asm" 




;check AL for scanned key 

user_input:
	mov CL , 0x79 ; 'y' char
	mov CH , 0x6E ; 'n' char
	mov DH , 0x71 ; 'q' char

loop:

	mov AH , 0x0
	int 0x16
	cmp AL , CL
	je do_something
	cmp AL , CH
	je do_nothing
	cmp AL , DH
	je shut_down
	push SI
	mov SI , ERROR
	call print_string
	call print_char
	pop SI
	jmp loop
	
do_nothing:
	push SI
	mov SI , QUIT
	call print_string
	pop SI
	jmp loop	
	
do_something:
	call user_enter_string
	jmp finish
	
	
finish:	
	ret



shut_down:
	mov AX , 0x1000
	mov AX , SS
	mov SP , 0xF000
	mov AX , 0x5307
	mov BX , 0x0001
	mov CX , 0x0003
	int 0x15
		


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
	jmp loop








%endif




