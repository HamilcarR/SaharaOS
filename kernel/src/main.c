

#include "../includes/constants.h" 
#include "../includes/video.h" 



void main(){
	const unsigned char* welcome = "SaharaOS : Oasis kernel" ; 
	clear_screen() ;	
	video_write((char*) welcome  ,  0x0E);
		
}







