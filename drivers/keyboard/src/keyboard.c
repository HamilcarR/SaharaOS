#include "../includes/keyboard.h"
#include "../../display/includes/video.h" 
#include "../../../kernel/includes/IDT.h"

#define DATA_PORT 0x60
#define STATUS_REG 0x64 //in read mode
#define COMMAND_REG 0x64 //in write mode













/* stores alpha numeric characters pressed scancodes , only for testing*/
const char ALPHANUM_PRESSED[] = {
	/*      VOID , ESC                                                           0x0B      */
		'\0' , '\0' , '&' , '~' , '"' ,'\'' , '(' , '-' , '`' , '_' , '^' , '@',
	/*		   BKSP ; TAB							    */	
		')' , '=', '\b' , '\t' , 'a' , 'z' , 'e' , 'r' , 't' , 'y' , 'u' , 'i' ,
	/*				ENTER	CTRLL				    */		
		'o' , 'p' , '^' , '$' , '\r' , '\0' , 'q' , 's' , 'd' , 'f' , 'g' , 'h',
	/*					      LSHIFT			  */
		'j' , 'k' , 'l' , 'm' , '%' , '*' , '\0' , '\\' , 'w' , 'x' , 'c' , 'v' ,
	/*					   RSHIFT  	LALT	      CAPS   F1	    */	
		'b' , 'n' , ',' , ';' , ':' , '!' , '\0' , '*' , '\0' , ' ' , '\0' , '\0' ,
	/*	F2      F3	...       			  F10 ,NUMLOC,SCRLOCK				    */
		'\0' , '\0' ,'\0' ,'\0' ,'\0' ,'\0' ,'\0' ,'\0' ,'\0' ,'\0' ,'\0' , '7' ,
	/*									    */
		'8' , '9' , '-' , '4' , '5' , '6' , '+' , '1' , '2' , '3' , '0' , '.' , 
	/*	  F11	F12							    */	
		 '\0' ,'\0'
};

const uint8_t ALPHANUM_RANGE_BEGIN = 0x00 ; 
const uint8_t ALPHANUM_RANGE_END = 0x58 ; 











void keyboard_handler(){
	uint8_t c = port_byte_in(DATA_PORT) ; 		
	if ( c >= ALPHANUM_RANGE_BEGIN && c <= ALPHANUM_RANGE_END)
		putchar(ALPHANUM_PRESSED[c]) ;
}

void init_keyboard(){
	register_idt_handler(IRQ1 , &keyboard_handler); 

}
