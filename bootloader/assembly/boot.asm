%ifndef BOOT_ASM
%define BOOT_ASM

[org 0x7C00]

KERNEL_OFFSET equ 0x1000

[bits 16]

	mov [BOOT_DRIVE] , dl
	mov BP , 0x9000
	mov SP , BP

	call load_kernel
	call switch_pm

	
%include "print.asm"
%include "hexprint.asm"
%include "disk_io.asm" 
%include "GDT.asm" 


load_kernel :
	mov SI , KERNEL_MSG
	call print_string
	mov BX , KERNEL_OFFSET
	mov DH , 53 
	mov DL , [BOOT_DRIVE]
	call disk_load
	ret



switch_pm:
	cli
	lgdt [gdt_descriptor]
	mov EAX , CR0
	or EAX , 1
	mov CR0 , EAX
	jmp CODE_SEG:PM_init

[bits 32]
PM_init:
	mov AX , DATA_SEG
	mov DS , AX
	mov SS , AX
	mov ES , AX
	mov FS , AX
	mov GS , AX

	mov EBP , 0x105000
	mov ESP , EBP
	
	call BEGIN_PM
	jmp $

BEGIN_PM : 
	call KERNEL_OFFSET
	ret



BOOT_DRIVE: db 0
RM_MSG db "SAHARA OS , Real mode" , 0x0
PM_MSG db "SAHARA OS , Protected mode" , 0x0
KERNEL_MSG db "SaharaOS : Oasis kernel " , 0x0A , 0x0D , 0x0

times 510 - ($-$$) db 0 
dw 0xaa55



%endif 
