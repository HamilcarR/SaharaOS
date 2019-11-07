#include "../includes/video.h" 





void clear_screen(){
	char *c = (char*) VIDEO_MEMORY ; 
	int i = 0 ; 
	for(i=0 ; i < VIDEO_MEMLIM - VIDEO_MEMORY ; i++){
		*c='\0' ; 
		c++ ; 
	
	}

}


void video_write(char *string , char color ){
	char *p = (char*) string ;
	char *c = (char*) (VIDEO_MEMORY  );
	while(*p != '\0')
	{
		*c = *p ; 
		c++ ;
		*c = color ; 
		c++ ;
		p++ ; 
	}


}


//to continue 
void video_write_to(char* string , char color , uint16_t col , uint16_t row) {


}


void enable_cursor(uint8_t start , uint8_t end){
	port_byte_out ( REGISTER_CTRL , REGISTER_CURSOR_START) ; 
	char in = port_byte_in(REGISTER_DATA) & 0xDF ; 
	port_byte_out (REGISTER_CTRL , REGISTER_CURSOR_START ) ; 
	port_byte_out (REGISTER_DATA , in ) ; 
}


void disable_cursor(){

	port_byte_out(REGISTER_CTRL , 0x0A) ;	
}



void move_cursor(uint8_t x , uint8_t y) {

	uint16_t loc = COLS * x + y ; 
	port_byte_out(REGISTER_CTRL , 0x0E) ; 
	port_byte_out(REGISTER_DATA , loc >> 8 ) ; 
	port_byte_out(REGISTER_CTRL , 0x0F ) ; 
	port_byte_out(REGISTER_DATA , loc ) ; 

}





