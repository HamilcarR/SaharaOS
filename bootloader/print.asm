%ifndef PRINT_ASM
%define PRINT_ASM


; move string into SI ... string finishes with Ox00


print_string:
	mov AL , [SI] 
	cmp AL , 0x00
	je end_print
	call print_char
	inc SI
	jmp print_string

end_print:
	ret


;prints char in AL

print_char:
	mov AH , 0x0E
	int 0x10
	ret























%endif
