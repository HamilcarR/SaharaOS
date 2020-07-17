#include "../includes/IDT.h"
#include "../../drivers/keyboard/includes/keyboard.h" 
#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 

#define PICM 		0x20 /* master PIC*/
#define PICS 		0xA0 /* slave PIC*/
#define PICM_COMMAND 	PICM 
#define PICM_DATA 	(PICM + 1) 
#define PICS_COMMAND 	PICS
#define PICS_DATA 	(PICS + 1) 
#define PIC_EOI 	0x20 /*end of interrupt (EOI) */
#define ICW1_ICW4  	0x01 //ICW4 not needed
#define ICW1_SINGLE 	0x02 //Single mode
#define ICW1_INTERVAL4	0x04 //call address interval 4
#define ICW1_LEVEL	0x08 //level triggered mode
#define ICW1_INIT	0x10 //initialization required
#define ICW4_8086	0x01 //8086 mode
#define ICW4_AUTO	0x02 //Auto EOI
#define ICW4_BUF_SLAVE  0x08 //buffered mode slave
#define ICW4_BUF_MASTER 0x0C //buffered mode master
#define ICW4_SFNM	0x10 //special fully nested 



const uint16_t KERNEL_CODE_SEG_OFFSET = 0x08 ; //see GDT in bootloader


static IDT_ENTRY idt[256] ; 


extern int32_t load_idt(); 
/* Master PIC
 * EOI only requires writing at PICM_COMMAND
 */
extern int32_t irq0(); //system clock
extern int32_t irq1(); //keyboard
extern int32_t irq2(); //N/A
extern int32_t irq3(); //serial port COM2/COM4
extern int32_t irq4(); //seria port COM1/COM3
extern int32_t irq5(); //LPT2 (sound card)
extern int32_t irq6(); //floppy
extern int32_t irq7(); //LPT1 

/* Slave PIC 
 * EOI requires writing at PICM_COMMAND and PICS_COMMAND
 */
extern int32_t irq8(); //real time clock
extern int32_t irq9(); //N/A
extern int32_t irq10();//N/A
extern int32_t irq11(); //N/A 
extern int32_t irq12(); // PS/2 controller
extern int32_t irq13(); //FPU
extern int32_t irq14(); //HDD 1 IDE
extern int32_t irq15(); //HDD 2 IDE




/*Exceptions*/
extern int32_t _DE(); //divide by zero 
extern int32_t _DB(); //debug
extern int32_t _BP(); //breakpoint
extern int32_t _OF(); //overflow
extern int32_t _BR(); //bound range exceeded
extern int32_t _UD(); //invalid opcode
extern int32_t _NM(); //device not available
extern int32_t _DF(); //double fault
extern int32_t _TS(); //invalid tss 
extern int32_t _NP(); //segment not present
extern int32_t _SS(); //stack segment fault
extern int32_t _GP(); //general protection fault
extern int32_t _PF(); //page fault
extern int32_t _MF(); //x87 floating point exception
extern int32_t _AC(); //alignment check
extern int32_t _MC(); //machine check
extern int32_t _XM(); //simd floating point exception
extern int32_t _VE(); //virtualization exception
extern int32_t _SX(); //security exception






static void init_PIC(){
	port_byte_out(PICM , 0x11) ; //write command to PIC master and slave
	port_byte_out(PICS , 0x11) ; 

	port_byte_out(PICM_DATA , 0x20) ; //remap PICM to 0x20
	port_byte_out(PICS_DATA , 40) ; //remap PICS to 0x28

	port_byte_out(PICM_DATA , 0x04) ; //IRQ2 connection to slave
	port_byte_out(PICS_DATA , 0x02) ; 

	port_byte_out(PICM_DATA , ICW1_ICW4) ; //ICW4 TO PICM
	port_byte_out(PICS_DATA , ICW1_ICW4) ; //ICW4 to PICS

	port_byte_out(PICM_DATA , 0x00) ; //enable all IRQ on master
	port_byte_out(PICS_DATA , 0x00) ; //enable all IRQ on slave
}





static void set_gate(uint8_t val , int32_t (irq_addr)(void) ){
	
	uint32_t irq_ptr = (uint32_t) irq_addr ; 
	idt[val].offset_low = irq_ptr & 0x0000FFFF ; 
	idt[val].selector = KERNEL_CODE_SEG_OFFSET ; 
	idt[val].zero = 0x00 ; 
	idt[val].type_attr = 0x8E ; // 32 bit interrupt gate 
	idt[val].offset_high = (irq_ptr & 0xFFFF0000) >> 16 ; 
}


static void (*IRQ_handlers[256])(void) ; 

void init_idt() {	
	
	init_PIC() ; 
	
	set_gate(DIVIDE_BY_ZERO_ERROR , _DE) ; 
	set_gate(DEBUG , _DB) ; 
	set_gate(BREAKPOINT ,_BP ) ; 
	set_gate(OVERFLOW , _OF) ; 
	set_gate(BOUND_RANGE_EXCEEDED , _BR) ; 
	set_gate(INVALID_OPCODE , _UD) ; 
	set_gate(DEVICE_NOT_AVAILABLE , _NM) ; 
	set_gate(DOUBLE_FAULT , _DF) ; 
	set_gate(INVALID_TSS , _TS) ; 
	set_gate(SEG_NOT_PRESENT , _NP) ; 
	set_gate(STACK_SEG_FAULT , _SS) ; 
	set_gate(GENERAL_PROTECTION_FAULT , _GP) ; 
	set_gate(PAGE_FAULT , _PF) ; 
	set_gate(x87_FLOATING_POINT_EXCEPTION , _MF) ; 
	set_gate(ALIGNMENT_CHECK , _AC) ; 
	set_gate(MACHINE_CHECK , _MC) ; 
	set_gate(SIMD_FLOATING_POINT_EXCEPTION , _XM) ; 
	set_gate(VIRTUALIZATION_EXCEPTION , _VE) ; 
	set_gate(SECURITY_EXCEPTION , _SX) ; 
	
	set_gate(IRQ0 , irq0); 
	set_gate(IRQ1 , irq1); 
	set_gate(IRQ2 , irq2); 
	set_gate(IRQ3 , irq3); 
	set_gate(IRQ4 , irq4); 
	set_gate(IRQ5 , irq5); 
	set_gate(IRQ6 , irq6); 
	set_gate(IRQ7 , irq7); 
	set_gate(IRQ8 , irq8); 
	set_gate(IRQ9 , irq9); 
	set_gate(IRQ10 , irq10); 
	set_gate(IRQ11 , irq11); 
	set_gate(IRQ12 , irq12); 
	set_gate(IRQ13 , irq13); 
	set_gate(IRQ14 , irq14); 	
	set_gate(IRQ15 , irq15); 
	
	IDT_PTR ptr ; 
	ptr.limit = sizeof(IDT_ENTRY) * 256 - 1   ; 
	ptr.base = (uint32_t) &idt ; 
	
	load_idt(&ptr) ; 

	int i = 0 ; 
	for( ; i < 256 ; i++)
		IRQ_handlers[i] = NULL ; 
}






void register_idt_handler(uint8_t irq , void (*function)(void)){

	IRQ_handlers[irq] = function ; 

}


void DE_handler(void){
	
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 

}
void DB_handler(void){
	
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void BP_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void OF_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void BR_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void UD_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void NM_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void DF_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void TS_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void NP_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void SS_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void GP_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void PF_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void MF_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}
void AC_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}
void MC_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}
void XM_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}
void VE_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 
void SX_handler(void){

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
} 

void irq0_handler(void) {
	if(IRQ_handlers[IRQ0] != NULL)
		(*IRQ_handlers[IRQ0])() ; 
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}
 
void irq1_handler(void) {

        char c = keyboard_handler();
	putchar(c) ;
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}
 
void irq2_handler(void) {

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}
 
void irq3_handler(void) {

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}
 
void irq4_handler(void) {

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}
 
void irq5_handler(void) {

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}

void irq6_handler(void) {

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}
 
void irq7_handler(void) {

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}
 
void irq8_handler(void) {

	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
	port_byte_out(PICS_COMMAND , PIC_EOI) ; 
}
 
void irq9_handler(void) {
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
	port_byte_out(PICS_COMMAND , PIC_EOI) ; 

}
 
void irq10_handler(void) {
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
	port_byte_out(PICS_COMMAND , PIC_EOI) ; 

}
 
void irq11_handler(void) {
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
	port_byte_out(PICS_COMMAND , PIC_EOI) ; 

}
 
void irq12_handler(void) {
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
	port_byte_out(PICS_COMMAND , PIC_EOI) ; 

}
 
void irq13_handler(void) {
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
	port_byte_out(PICS_COMMAND , PIC_EOI) ; 

}
 
void irq14_handler(void) {
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
	port_byte_out(PICS_COMMAND , PIC_EOI) ; 

}
 
void irq15_handler(void) {
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
	port_byte_out(PICS_COMMAND , PIC_EOI) ; 

}



