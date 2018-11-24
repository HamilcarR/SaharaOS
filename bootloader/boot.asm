[org 0x7c00]


	mov si , msg
	call loop
	jmp $


loop:
   strloop:
	mov al , [si]
	cmp al , 0x0
	jne print
	ret
print:
	mov ah , 0x0E
	int 0x10
	add si , 1 
	jmp strloop


msg db "SaharaOS" , 0x0
times 510 - ($-$$) db 0 
dw 0xaa55


