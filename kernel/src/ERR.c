#include "../includes/ERR.h" 
#include "../includes/stdio.h" 
#include "../../drivers/display/includes/video.h"




void K_PANIC(const char* err , const char* func , const char* file , int line){
//	clear_screen(); 
	set_attribute(0x0E); 
	kprint("Error :%s \nFile :%s\nFunction:%s at line : %d\n" , err , file , func , line) ; 
	while(1)
		__asm__("HLT"); 

	
}
