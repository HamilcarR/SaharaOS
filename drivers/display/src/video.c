#include "../includes/video.h" 



uint16_t cursorX ; 
uint16_t cursorY ;


void init_video(){
	cursorX = 0 ;
	cursorY = 0 ; 
	enable_cursor(0 , 0 ) ; 

}





void clear_screen(){
	char *c = (char*) VIDEO_MEMORY ; 
	int i = 0 ; 
	for(i=0 ; i < (VIDEO_MEMLIM - VIDEO_MEMORY)/2 ; i++){
		*c='\0' ; 
		c++ ; 
		*c=0x0E ; 
		c++ ; 
	
	}

}


void video_write(char *string , char color ){
	char *p = (char*) string ;
	char *c = (char*) (VIDEO_MEMORY );
	while(*p != '\0')
	{

		if(*p == '\n' || *p == '\r' ) {

			cursorX++ ; 
			cursorY = 0 ;
			c = (char*) VIDEO_MEMORY + cursorX * 0xA0 ; // 80 chars+attr = 160 bytes
			p++ ; 

		}
		
		else{
			*c = *p ; 
			c++ ;
			*c = color ; 
			c++ ;
			p++ ;
			cursorY++ ;
		}
	}
		
	
	if( c >= ((char*) VIDEO_MEMLIM))
		scroll_screen(); 
	else
		move_cursor(cursorX , cursorY ) ; 
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


uint16_t cursor_location(){
	port_byte_out(REGISTER_CTRL , REGISTER_CURSOR_HIGH) ; 
	uint8_t high = port_byte_in(REGISTER_DATA ) ; 
	port_byte_out(REGISTER_CTRL , REGISTER_CURSOR_LOW) ; 
	uint8_t low = port_byte_in(REGISTER_DATA) ; 

	return (high << 8) | low ; 
}


void move_cursor(uint8_t x , uint8_t y) {

	uint16_t loc = COLS * x + y ; 
	port_byte_out(REGISTER_CTRL , REGISTER_CURSOR_HIGH) ; 
	port_byte_out(REGISTER_DATA , loc >> 8 ) ; 
	port_byte_out(REGISTER_CTRL , REGISTER_CURSOR_LOW ) ; 
	port_byte_out(REGISTER_DATA , loc ) ; 

}


void scroll_screen(){

	clear_screen() ; 
	move_cursor(0 , 0) ; 

}


