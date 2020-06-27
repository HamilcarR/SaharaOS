
[bits 32]
[extern _start]
	call _start
	jmp $


global _KERNEL_END

align 16 
	_KEND equ $+4+12
	_KERNEL_END DD _KEND
align 16





