#ifndef IDT_H
#define IDT_H
#include <stdint.h>
#include "../../drivers/ports/includes/IO_ports.h"
#include "Kconstants.h"


#define _BASE_IDT 0x00000000
#define _SIZE_IDT 256 






#define DIVIDE_BY_ZERO_ERROR 		0x00
#define DEBUG		     		0x01
#define NON_MASKABLE_IRT     		0x02
#define BREAKPOINT			0x03
#define OVERFLOW 			0x04
#define BOUND_RANGE_EXCEEDED		0x05
#define INVALID_OPCODE_ERR		0x06
#define DEVICE_NOT_AVAILABLE		0x07
#define DOUBLE_FAULT			0x08
#define COPROC_SEG_OVERRUN		0x09
#define INVALID_TSS			0x0A
#define SEG_NOT_PRESENT			0x0B
#define STACK_SEG_FAULT			0x0C
#define GENERAL_PROTECTION_FAULT	0x0D
#define PAGE_FAULT_ERR	     		0x0E
#define x87_FLOATING_POINT_EXCEPTION	0x10
#define ALIGNMENT_CHECK			0x11
#define MACHINE_CHECK			0x12
#define SIMD_FLOATING_POINT_EXCEPTION	0x13
#define VIRTUALIZATION_EXCEPTION	0x14
#define SECURITY_EXCEPTION		0x1E
#define RESERVED			0x1F







#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39 
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47




/*Interrupt descriptor table : IA-32*/
	/*Offset_high : higher part of the offset 
	 *
	 *
	 *Type_attr : 
	 *  7 				0
	 *+---+---+---+---+---+---+---+---+
	 *| P |  DPL  | S |   Gatetype    |
	 *+---+---+---+---+---+---+---+---+
	 *
	 * P : bit 47 : Present : set to 0 for unused interrupts
	 * 
	 * DPL : bits 45-46 : Descriptor privilege level : gate call protection , specifies minimum lvl calling privilege for the
	 * 	calling descriptor / hardware and CPU interrupts protected from being called in userspace
	 *
	 * S : bit 44 : storage segment : set to 0 for interrupt and trap gates
	 *
	 * GateType: bits 40-43 :
	 * 	0x5 = 32 bit task gate
	 *	0x6 = 16 bit interrupt gate
	 *	0x7 = 16 bit trap gate
	 *	0xE = 32 bit interrupt gate
	 *	0xF = 32 bit trap gate
	 *
	 *Zero : is 0 
	 *
	 *Selector : kernel's selector of the interrupt function, DPL field is 0 so iret instruction doesn't throw except
	 * 
	 *Offset_low : lower part of the offset 
	 *
	 */


typedef struct IDT_ENTRY {
	uint16_t offset_low ; 
	uint16_t selector ;   
	uint8_t zero ; 	       
	uint8_t type_attr ;   
	uint16_t offset_high ; 
}__attribute__((packed)) IDT_ENTRY;




typedef struct IDT_PTR{
	uint16_t  limit ; 
	uint32_t  base  ; 


} __attribute__((packed)) IDT_PTR ; 

void init_idt() ; 


void register_idt_handler(uint8_t irq , void (*func)(void)) ; 














#endif 
