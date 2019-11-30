

#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 





void _start(){
	const char* welcome = "Sahara OS : \t \t \t \t Welcome ! :) " ; 
	init_video(); 
	clear_screen() ;
	video_write((char*) welcome , 0x0E , false) ;  
	display_memory((unsigned char*) VIDEO_MEMORY , 8 , 20 , 0x0E , false) ; 
	
	while(1) ; 
}







