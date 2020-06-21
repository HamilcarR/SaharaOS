#include "../includes/IDT.h"

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


#define KERNEL_SEG_OFFSET 	0x08




static IDT_ENTRY idt[256] ; 



extern int32_t load_idt(); 
extern int32_t irq0();
extern int32_t irq1(); 
extern int32_t irq2(); 
extern int32_t irq3(); 
extern int32_t irq4(); 
extern int32_t irq5(); 
extern int32_t irq6(); 
extern int32_t irq7(); 
extern int32_t irq8(); 
extern int32_t irq9(); 
extern int32_t irq10(); 
extern int32_t irq11(); 
extern int32_t irq12(); 
extern int32_t irq13(); 
extern int32_t irq14(); 
extern int32_t irq15(); 












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
	idt[val].selector = KERNEL_SEG_OFFSET ; 
	idt[val].zero = 0x00 ; 
	idt[val].type_attr = 0x8E ; // 32 bit interrupt gate 
	idt[val].offset_high = (irq_ptr & 0xFFFF0000) >> 16 ; 


}

void init_idt() {	
	uint32_t idt_address ; 
	uint32_t idt_ptr[2]; 	
	
	init_PIC() ; 
	
	set_gate(32 , irq0); 
	set_gate(33 , irq1); 
	set_gate(34 , irq2); 
	set_gate(35 , irq3); 
	set_gate(36 , irq4); 
	set_gate(37 , irq5); 
	set_gate(38 , irq6); 
	set_gate(39 , irq7); 
	set_gate(40 , irq8); 
	set_gate(41 , irq9); 
	set_gate(42 , irq10); 
	set_gate(43 , irq11); 
	set_gate(44 , irq12); 
	set_gate(45 , irq13); 
	set_gate(46 , irq14); 	
	set_gate(47 , irq15); 

	idt_address = (uint32_t) idt ; 	
	idt_ptr[0] = (sizeof(IDT_ENTRY) * 256) + ((idt_address & 0xffff) << 16) ;  
	idt_ptr[1] = idt_address >> 16 ; 

	load_idt(idt_ptr) ; 
}

void irq0_handler(void) {
}
 
void irq1_handler(void) {
}
 
void irq2_handler(void) {
}
 
void irq3_handler(void) {
}
 
void irq4_handler(void) {
}
 
void irq5_handler(void) {
}
 
void irq6_handler(void) {
}
 
void irq7_handler(void) {
}
 
void irq8_handler(void) {
}
 
void irq9_handler(void) {
}
 
void irq10_handler(void) {
}
 
void irq11_handler(void) {
}
 
void irq12_handler(void) {
}
 
void irq13_handler(void) {
}
 
void irq14_handler(void) {
}
 
void irq15_handler(void) {
}



