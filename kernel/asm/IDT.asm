%ifndef IDT_ASM
%define IDT_ASM


[bits 32]







global _DE
global _DB
global _BP
global _OF
global _BR
global _UD
global _NM
global _DF
global _TS
global _NP
global _SS
global _GP
global _PF
global _MF
global _AC
global _MC
global _XM
global _VE
global _SX







global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7 
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15




global load_idt






extern DE_handler
extern DB_handler
extern BP_handler
extern OF_handler
extern BR_handler
extern UD_handler
extern NM_handler
extern DF_handler
extern TS_handler
extern NP_handler
extern SS_handler
extern GP_handler
extern PF_handler
extern MF_handler
extern AC_handler
extern MC_handler
extern XM_handler
extern VE_handler
extern SX_handler





extern irq0_handler
extern irq1_handler
extern irq2_handler
extern irq3_handler
extern irq4_handler
extern irq5_handler
extern irq6_handler
extern irq7_handler
extern irq8_handler
extern irq9_handler
extern irq10_handler
extern irq11_handler
extern irq12_handler
extern irq13_handler
extern irq14_handler
extern irq15_handler


_DB:
  	pusha
	call DB_handler
	popa
  	iretd


_BP:
  	pusha
	call BP_handler
	popa
  	iretd


_OF:
  	pusha
	call OF_handler
	popa
  	iretd


_BR:
  	pusha
	call BR_handler
	popa
  	iretd


_UD:
  	pusha
	call UD_handler
	popa
  	iretd


_NM:
  	pusha
	call NM_handler
	popa
  	iretd


_DF:
	pusha
	call DF_handler
	popa
  	iretd


_TS:
  	pusha
	call TS_handler
	popa
  	iretd


_NP:
  	pusha
	call NP_handler
	popa
  	iretd


_SS:
  	pusha
	call SS_handler
	popa
  	iretd


_GP:
  	pusha
	call GP_handler
	popa
  	iretd


_MF:
  	pusha
	call MF_handler
	popa
  	iretd


_AC:
  	pusha
	call AC_handler
	popa
  	iretd


_MC:
  	pusha
	call MC_handler
	popa
  	iretd


_XM:
  	pusha
	call XM_handler
	popa
  	iretd


_VE:
  	pusha
	call VE_handler
	popa
  	iretd


_SX:
  	pusha
	call SX_handler
	popa
  	iretd


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

irq2:
	pusha
  	call irq2_handler
  	popa
  	iretd


irq3:
	pusha
  	call irq3_handler
  	popa
  	iretd


irq4:
	pusha
  	call irq4_handler
  	popa
  	iretd


irq5:
	pusha
  	call irq5_handler
  	popa
  	iretd


irq6:
	pusha
  	call irq6_handler
  	popa
  	iretd


irq7:
	pusha
  	call irq7_handler
  	popa
  	iretd


irq8:
	pusha
  	call irq8_handler
  	popa
  	iretd


irq9:
	pusha
  	call irq9_handler
  	popa
  	iretd


irq10:
	pusha
  	call irq10_handler
  	popa
  	iretd


irq11:
	pusha
  	call irq11_handler
  	popa
  	iretd


irq12:
	pusha
  	call irq12_handler
  	popa
  	iretd


irq13:
	pusha
  	call irq13_handler
  	popa
  	iretd


irq14:
	pusha
  	call irq14_handler
  	popa
  	iretd


irq15:
	pusha
  	call irq15_handler
  	popa
  	iretd


load_idt : 
	mov EDX , [ESP + 4] 
	lidt [EDX]
	sti
	ret





%endif 
