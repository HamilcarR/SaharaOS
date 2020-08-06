#include "../includes/IDT.h"
#include "../../drivers/keyboard/includes/keyboard.h" 
#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 
#include "../includes/ERR.h"


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



static uint16_t KERNEL_CODE_SEG_OFFSET  = 0x08 ; //see GDT in bootloader



static IDT_ENTRY idt[256] ; 
IDT_PTR idt_ptr ; 

extern int32_t load_idt(); 



extern int32_t irq0(); //timer 
extern int32_t irq1(); //keyboard






/*Exceptions*/
extern int32_t _DE(); //Divide by zero error
extern int32_t _PF(); //Page fault error 
extern int32_t _UD(); //Invalid opcode
extern int32_t _DF(); //Double fault


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

static void init_idt_array(){
	int val = 0 ; 
	for(; val < _SIZE_IDT ; val++){
		idt[val].offset_low = 0 ; 
		idt[val].selector = KERNEL_CODE_SEG_OFFSET ; 
		idt[val].zero = 0 ; 
		idt[val].type_attr = 0x80 ; //see '1' below
		idt[val].offset_high = 0 ; 
	}
}
/* 1 : See "Intel 64 and IA-32 Architectures Software developer's Manual" , Volume 3 , Chapter 6.10: 
 * "Interrupt Descriptor Table" , all empty descriptor slot should have the present flag for the descriptor set to 0 
 */















static void (*IRQ_handlers[256])(reg_struct_t) ; 

void init_idt() {	

	init_PIC() ; 
	init_idt_array(); 
	idt_ptr.limit = sizeof(IDT_ENTRY) * _SIZE_IDT - 1    ; 
	idt_ptr.base = (uint32_t) &idt ; 
	

	//exceptions gates
	set_gate(DIVIDE_BY_ZERO_ERROR , _DE) ; 
	set_gate(PAGE_FAULT_ERR , _PF) ;
	set_gate(INVALID_OPCODE_ERR , _UD);
	set_gate(DOUBLE_FAULT_ERR , _DF) ;

	//interrupt gates
	set_gate(IRQ0 , irq0); 
	set_gate(IRQ1 , irq1); 
	
	load_idt(&idt_ptr) ; 

	int i = 0 ; 
	for( ; i < _SIZE_IDT ; i++)
		IRQ_handlers[i] = NULL ; 
}






void register_idt_handler(uint8_t irq , void (*function)(reg_struct_t)){

	IRQ_handlers[irq] = function ; 

}

const char* EXCEPTIONS_TXT[22] = { "Exception raised : Divide by zero" , //0x00
				   "Exception raised : Debug"          , //0x01
				   0				       , //0x02
				   0,
				   0,
				   0,
				   "Exception raised : Invalid opcode" , //0x06
				   0,//0x07
				   "Exception raised : Double fault",//0x08
				   0,//0x09
				   0,//0x0A
				   0,//0x0B
				   0,//0x0C
				   0,//0x0D
				   "Exception raised : Page fault"      ,//0x0E
				   0,
				   0,
				   0,
				   0,
				   0,
				   0,
				   0
} ; 
/************************************************************************************/

void DE_handler(void) {

	K_PANIC(EXCEPTIONS_TXT[DIVIDE_BY_ZERO_ERROR], __func__ , __FILE__ , __LINE__) ; 
}
void PF_handler(void){
	reg_struct_t a ; 
	if(IRQ_handlers[PAGE_FAULT_ERR] != NULL)
		(*IRQ_handlers[PAGE_FAULT_ERR])(a); 
	K_PANIC(EXCEPTIONS_TXT[PAGE_FAULT_ERR] , __func__ , __FILE__ , __LINE__) ; 

}
void UD_handler(void){
	K_PANIC(EXCEPTIONS_TXT[DOUBLE_FAULT_ERR] , __func__ , __FILE__ , __LINE__); 

}

void DF_handler(void){

	K_PANIC(EXCEPTIONS_TXT[INVALID_OPCODE_ERR] , __func__ , __FILE__ , __LINE__); 

}


void irq0_handler(void){
	reg_struct_t a ; 
	if(IRQ_handlers[IRQ0] != NULL)
		(*IRQ_handlers[IRQ0])(a); 
	port_byte_out(PICM_COMMAND , PIC_EOI); 

}
 
void irq1_handler(void) {
	reg_struct_t a ; 
	if(IRQ_handlers[IRQ1] != NULL)
		(*IRQ_handlers[IRQ1])(a) ; 
	port_byte_out(PICM_COMMAND , PIC_EOI) ; 
}




