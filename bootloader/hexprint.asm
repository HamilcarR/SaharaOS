%ifndef HEX_PRINT_ASM
%define HEX_PRINT_ASM


%include "print.asm"





print_template : 
	mov SI , template
	call print_string
	ret 

;copy DL to AL , and shifts the 4 last bits of AL to the 4 first bits 
al_high : 
	mov AL , DL
	and AL , 0xF0
	shr AL , 4
	ret
al_low : 
	mov AL , DL
	and AL , 0x0F
	ret 



;prints hex value in DL 

hexout_8bits : 

	xor AX , AX
	mov SI , hex_table
	call al_high
	add SI , AX 
	mov AL , [SI]
	call print_char

	xor AX , AX 
	mov SI , hex_table
	call al_low
	add SI , AX 
	mov AL , [SI] 
	call print_char 

	ret


;print hex value of DX

hexout_16bits: 
	push DX 
	mov DL , DH 
	call hexout_8bits 	
	pop DX 

	call hexout_8bits
	ret



hexout_8 : 
	call print_template
	call hexout_8bits
	mov AL , 0x0D
	call print_char
	mov AL , 0x0A
	call print_char
	ret

hexout_16 :
	call print_template
	call hexout_16bits
	mov AL , 0x0D
	call print_char
	mov AL , 0x0A
	call print_char	
	ret


hex_table db "0123456789ABCDEF" 
template db "0x", 0x00

%endif

