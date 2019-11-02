#include "../includes/video.h" 

#define VIDEO_MEMORY 0xB8000 
#define VIDEO_MEMLIM 0xB8FA0


void clear_screen(){
	char *c = (char*) VIDEO_MEMORY ; 
	int i = 0 ; 
	for(i ; i < 4000 ; i++){
		*c='\0' ; 
		c++ ; 
	
	}

}


void video_write(unsigned char *string , char color ){
	unsigned char *p = (unsigned char*) string ;
	char *c = (char*) (VIDEO_MEMORY  );
	int i = 0 ; 
	while(*p != '\0')
	{
		*c = *p ; 
		c++ ;
		*c = color ; 
		c++ ;
		p++ ; 
	}


}
