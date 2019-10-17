
print_template : 
	mov SI , template
	call print_string
	ret 

;takes value from AH & 0xF0 and puts it in AL & 0x0F
ah_high : 
	and AH , 0xF0
	xor AL , AL 
	mov AL , AH 
	shr AL , 4
	and AX , 0x000F

	ret


;takes value from AH & 0x0F and puts it in AL & 0x0F
ah_low :
	and AH , 0x0F 
	xor AL , AL 
	mov AL , AH
	and AX , 0x000F
	ret

; takes value from AL & 0xF0 and puts it in AL & 0x0F
al_high :
	and AL , 0xF0
	shr AL , 4
	and AX , 0x000F
	ret

;print hex value in DX (16 bits) 
hexout_16:

	call print_template
;OxF000
	xor AX , AX 
	mov AX , DX
	call ah_high
	mov SI , hex_table
	add SI , AX
	call print_char
;0x0F00
	xor AX , AX 
	mov AX , DX
	call ah_low
	mov SI , hex_table
	add SI , AX 
	call print_char
;0x00F0
	xor AX , AX
	mov AX , DX 
	call al_high
	mov SI , hex_table
	add SI , AX
	call print_char

;9x000F
	xor AX , AX 
	mov AX , DX 
	and AX , 0x000F
	mov SI , hex_table
	add SI , AX 
	call print_char

	ret

hex_table db "0123456789ABCDEF" 
template db "0x", 0x00
