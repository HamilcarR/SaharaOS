#ifndef VIDEO_H
#define VIDEO_H
#include <stdint.h>
#include "constants.h" 
#include "../../../kernel/includes/Kconstants.h" 
#include "../../ports/includes/IO_ports.h" 

typedef struct CUR_LOCATION {



	uint8_t cursorX ;
	uint8_t cursorY ; 


}CUR_LOCATION; 



//initialize video text mode
void init_video() ; 

//write until '\0' is encountered
void video_write(const char *string , bool erase);

//clear the screen
void clear_screen () ; 

//write to position (ROW , COL) 
void video_write_to(const char* string , uint16_t row , uint16_t col); 

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
void new_line(const char** string_data) ; 

//tabulation
void tabulate(const char** string_data) ; 

void putchar_col(char c , uint8_t color ) ; 

void putchar(char c) ;
/*change vga attribute*/
void set_attribute(uint8_t attrib) ; 



















#endif 
