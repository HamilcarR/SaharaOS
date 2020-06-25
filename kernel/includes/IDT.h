#ifndef IDT_H
#define IDT_H
#include <stdint.h>
#include "IO_ports.h"
#define _BASE_IDT 0x00000000
#define _SIZE_IDT 0xFF 



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
	uint16_t limit ; 
	uint32_t base ; 


}__attribute__((packed)) IDT_PTR ; 

void init_idt() ; 

















#endif 
