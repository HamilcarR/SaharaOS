#include "../includes/string.h"
#include "../includes/memory.h" 
#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 
#include "../includes/IDT.h"
#include "../includes/heap.h" 







void _start(){

	const char* welcome = "So... what does B.B stand for anyway... ?\n Backstabbing bastard ?\n" ; 
	init_video(); 
	clear_screen() ;
	video_write( welcome , 0x0E , false) ;
	init_heap() ; 
	char *ptr = (char*) kmalloc(2 * sizeof(char)) ; 
	if(ptr != NULL) {
		ptr[0] = 0xFB ;
		ptr[1] = 0xAA ; 
	}
	display_memory((char*) ptr , 8 , 16 , 0x0E , false) ; 
	video_write(to_hex((uint8_t) ptr[0] , BIT_8) , 0x0E , false) ; 

	video_write(to_hex((uint8_t) ptr[1] , BIT_8) , 0x0E , false) ; 



	
	init_idt();

	while(1) ; 
}





