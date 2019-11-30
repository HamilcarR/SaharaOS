%ifndef MENU1_ASM
%define MENU1_ASM


load_menu:
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
	mov SI , msg_5
	call print_string
	call user_input
	ret













%endif
