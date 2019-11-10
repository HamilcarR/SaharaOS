

#include "../../drivers/display/includes/video.h" 


void _start(){
	const char* welcome = "SaharaOS : Oasis kernel welcome shithead!" ; 
	init_video(); 
	clear_screen() ;
	video_write(( char*) welcome  ,  0x0E);
	uint16_t loc = cursor_location() ;
	
	while(1) ; 
}







