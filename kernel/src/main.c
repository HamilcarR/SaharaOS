

#include "../../drivers/display/includes/video.h" 


void main(){
	const unsigned char* welcome = "SaharaOS : Oasis kernel , welcome shithead!" ; 
	clear_screen() ;
	video_write((unsigned char*) welcome  ,  0x0E);
}







