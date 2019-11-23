#include "../includes/video.h" 



uint8_t cursorX ; 
uint8_t cursorY ;
char* buffer ; 
char* char_buffer ;


void init_video(){
	cursorX = 0 ;
	cursorY = 0 ; 
	enable_cursor(0 , 0 ) ; 
	buffer = (char*) (VIDEO_MEMORY );
	char_buffer = buffer ; 	
}





void clear_screen(){
	buffer = (char*) VIDEO_MEMORY ; 
	int i = 0 ; 
	for(i=0 ; i < (VIDEO_MEMLIM - VIDEO_MEMORY)/2 ; i++){
		*buffer='\0' ; 
		buffer++ ; 
		*buffer=0x0E ; 
		buffer++ ; 
	
	}
	buffer = (char*) VIDEO_MEMORY ; 

}





void new_line(char** string_data) {
	cursorX++ ; 
	cursorY = 0 ;
	buffer = (char*) VIDEO_MEMORY + cursorX * 0xA0 ; // 80 chars+attr = 160 bytes
	(*string_data)++ ; 			

}



void tabulate(char** string_data){

	if((cursorY + (uint8_t) TAB_SIZE) >= COLS - 2){
		uint8_t dist = COLS-2 - cursorY ; 
		cursorY = COLS - 2 ; 
		buffer += dist * 2; 
	}
	else{
		cursorY += (uint8_t) TAB_SIZE ; 
		buffer += TAB_SIZE * 2 ; 


	}
		

	(*string_data)++ ; 
}




void video_write(char *string , char color , bool erase){
	if(erase)
		buffer = (char*) VIDEO_MEMORY;
	
	char *p = (char*) string ;

	while(*p != '\0')
	{

		if(*p == '\n' || *p == '\r' || cursorY == (uint8_t) COLS - 1  ) 
			new_line(&p) ; 

		else if(*p == '\t' ) 
			tabulate(&p) ; 		

		else{
			*buffer = *p ; 
			buffer++ ;
			*buffer = color ; 
			buffer++ ;
			p++ ;
			cursorY++ ;
		}
	}
		
	
	if(cursorX == ROWS)
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


/****************************************************************************/
CUR_LOCATION cursor_location(){
	 CUR_LOCATION C ; 
	 C.cursorX = cursorX ; 
	 C.cursorY = cursorY ; 
	 return C ; 
	 
}


/****************************************************************************/
void move_cursor(uint8_t x , uint8_t y) {

	uint16_t loc = COLS * x + y ; 
	port_byte_out(REGISTER_CTRL , REGISTER_CURSOR_HIGH) ; 
	port_byte_out(REGISTER_DATA , loc >> 8 ) ; 
	port_byte_out(REGISTER_CTRL , REGISTER_CURSOR_LOW ) ; 
	port_byte_out(REGISTER_DATA , loc & 0x00FF ) ; 

}






/****************************************************************************/

void scroll_screen(){

	clear_screen() ;
	
	move_cursor(0 , 0) ; 

}



























