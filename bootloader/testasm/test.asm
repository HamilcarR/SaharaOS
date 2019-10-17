[org 0x7c00]






mov DX , AX
call hexout_16
jmp $




%include "print.asm" 








times 510 - ($-$$) db 0
dw 0xaa55




