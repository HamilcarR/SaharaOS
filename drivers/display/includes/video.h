#ifndef VIDEO_H
#define VIDEO_H
#include <stdint.h>
#include "constants.h" 
#include "../../../kernel/includes/IO_ports.h" 
#include "../../../kernel/includes/Kconstants.h" 


typedef struct CUR_LOCATION {



	uint8_t cursorX ;
	uint8_t cursorY ; 


}CUR_LOCATION; 



//initialize video text mode
void init_video() ; 
//write until '\0' is encountered
void video_write(char *string , char color , bool erase);
//clear the screen
void clear_screen () ; 
//write to position (ROW , COL) 
void video_write_to( char* string , char color , uint16_t col , uint16_t row); 
//set cursor 
void enable_cursor(uint8_t start , uint8_t end); 
//disable cursor
void disable_cursor();
//get cursor location
CUR_LOCATION cursor_location() ; 
//move cursor
void move_cursor(uint8_t x , uint8_t y) ; 
//scroll screen
void scroll_screen() ; 
//new line / carriage return
void new_line(char** string_data) ; 
//tabulation
void tabulate(char** string_data) ; 


#endif 
