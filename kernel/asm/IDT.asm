%ifndef IDT_ASM
%define IDT_ASM

[bits 32]




global load_idt
extern idt_ptr


extern DE_handler
global _DE

extern PF_handler
global _PF

extern UD_handler
global _UD

extern irq0_handler
global irq0

extern irq1_handler
global irq1



_DE:
	pusha
	call DE_handler
	popa
	iretd

_PF:
	pusha
	call PF_handler
	popa
	iretd

_UD:
	pusha
	call UD_handler
	popa
	iretd

irq0:
	pusha
	call irq0_handler
	popa
	iretd

irq1:
	pusha
  	call irq1_handler
  	popa
  	iretd

load_idt :
	lidt [idt_ptr]
	sti
	ret





%endif 
