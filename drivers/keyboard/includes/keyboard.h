#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../../ports/includes/IO_ports.h" 
#include "../../../kernel/includes/IDT.h"


 enum STATUS {
	O = (1 << 0) , //output buffer status (0 = empty , 1 = full) 
	I = (1 << 1) , //input buffer status (0 = empty , 1 = full) 
	SF = (1 << 2) , //system flag , cleared on reset .
	CD = (1 << 3) , //command/data (0 = data written to input buffer is for PS/2 device , 1 = PS/2 controller command
	NA1 = (1 << 4) , //unused
	NA2 = (1 << 5) , //unused
	TOERR = (1 << 6) , //time out error (0 = no err , 1 = time out err) 
	PERR = (1 << 7)  //parity error (0 = no error) 

};


typedef enum EVENT_TYPE { PRESSED = 0 , RELEASED = 1} EVENT_TYPE; 


typedef struct KEYCODE{

	uint32_t keycode ; 
	EVENT_TYPE event ; 

}KEYCODE;






void kbdriver_init_keyboard(); 


/* handles keyboard inputs */
void keyboard_handler(reg_struct_t reg); 

char kbdriver_get_char();











#endif 
