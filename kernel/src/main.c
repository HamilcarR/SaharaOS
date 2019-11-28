

#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 

void _start(){
	const char* welcome = "Sahara OS : \t \t \t \t Welcome ! :) " ; 
	init_video(); 
	clear_screen() ;
	video_write((char*) welcome , 0x0E , false) ;  
	display_memory((char*) 0xB8000 , 8 , 20 ,0x0A , false);
	HEX_LAYOUT layout ; 
	layout.size = 8 ; 
	to_hex((void*) (0xB8000) , &layout ) ; 


	while(1) ; 
}







