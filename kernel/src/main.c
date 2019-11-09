

#include "../../drivers/display/includes/video.h" 


void main(){
	const char* welcome = "SaharaOS : Oasis kernel\nwelcome shithead!" ; 
	init_video(); 
	clear_screen() ;
	video_write(( char*) welcome  ,  0x0E);
	while(1) ; 
}







