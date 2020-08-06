#include "../includes/PIT.h" 
#include "../../../kernel/includes/IDT.h" 

#define PIT_CHANNEL0 0x40
#define PIT_CHANNEL1 0x41
#define PIT_CHANNEL2 0x42
#define PIT_COMMAND  0x43





volatile uint32_t tick ; 

void increment_tick(reg_struct_t reg){
	tick ++ ;
}



void init_timer(uint32_t freq)  {
	tick = 0 ; 
	uint32_t div = PIT_DEFAULT_FREQUENCY / freq ; 
	register_idt_handler(IRQ0 , &increment_tick) ; 	
	port_byte_out(PIT_COMMAND , 0x36) ; 
	port_byte_out(PIT_CHANNEL0 , (uint8_t) div) ; 
	port_byte_out(PIT_CHANNEL0 , (uint8_t) (div >> 8)) ; 
	

}



void sys_sleep(uint32_t time){
	uint32_t end_tick = tick + time ; 
	while(end_tick > tick) 
		__asm__("HLT") ; 

}
