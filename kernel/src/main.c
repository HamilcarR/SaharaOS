
#include "../includes/memory.h" 
#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 
#include "../includes/IDT.h"


void _start(){


	const char* welcome = "Sahara OS : \t \t \t \t Welcome ! :) " ; 
	init_video(); 
	clear_screen() ;
	video_write((char*) welcome , 0x0E , false) ;  
	display_memory((void*) 0xB8000 , 8 , 16 , 0x0A , false) ; 
	init_idt();
	while(1) ; 
}





