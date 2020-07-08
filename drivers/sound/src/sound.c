#include "../includes/sound.h"
#include "../../PIT/includes/PIT.h"




void play_sound(uint32_t freq){
	uint8_t tmp ; 
	uint32_t div ; 
	div = PIT_DEFAULT_FREQUENCY / freq ; 
	port_byte_out(0x43 , 0xB6) ; 
	port_byte_out(0x42 , (uint8_t) div) ; 
	port_byte_out(0x42 , (uint8_t) (div >> 8)) ; 

	tmp = port_byte_in(0x61) ; 
	if(tmp != (tmp | 3)) {
		port_byte_out(0x61 , tmp | 3) ; 
	}
}

static void nosound(){
	uint8_t t = port_byte_in(0x61) & 0xFC ; 
	port_byte_out(0x61 , t) ; 

}


void beep(uint32_t freq , uint32_t time){
	play_sound(freq) ; 
	sys_sleep(time) ; 
	nosound(); 
}











