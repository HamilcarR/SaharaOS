#include "../includes/string.h"
#include "../includes/memory.h" 
#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 
#include "../includes/IDT.h"


void _start(){



	const char* welcome = "So... what does B.B stand for anyway... ?\n Backstabbing bastard ?" ; 
	init_video(); 
	clear_screen() ;
	video_write( welcome , 0x0E , false) ;  
	strcpy((char*) 0xB8070 , welcome) ; 
	display_memory((void*) 0xB8000 , 8 , 16 , 0x0A , false) ; 

	init_idt();

	while(1) ; 
}





