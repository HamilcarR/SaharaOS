





; move string into SI ... string finishes with Ox00


print_string:

pusha
	strloop:
	mov AL , [SI]
	cmp AL , 0x0
	jne print
popa
	ret


print:
	mov AH , 0x0E
	int 0x10
	add SI , 1 
	jmp strloop



;prints char in AL

print_char:
	pusha
	mov AH , 0x0E
	int 0x10
	popa
	ret

