

#include "../../drivers/display/includes/video.h" 


void main(){
	const char* welcome = "SaharaOS : Oasis kernel , welcome shithead!" ; 
	
	clear_screen() ;
	enable_cursor(0 , 0) ; 
	video_write(( char*) welcome  ,  0x0E);
	move_cursor(0 , 10 ) ;

}







