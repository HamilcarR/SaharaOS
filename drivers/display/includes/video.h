#ifndef VIDEO_H
#define VIDEO_H
#include <stdint.h>
#include "constants.h" 
#include "../../../kernel/includes/IO_ports.h" 

//write until '\0' is encountered
void video_write(  char *string , char color);
//clear the screen
void clear_screen () ; 
//write to position (COL , ROW) 
void video_write_to( char* string , char color , uint16_t col , uint16_t row); 
//set cursor 
void enable_cursor(uint8_t start , uint8_t end); 
//disable cursor
void disable_cursor();
//get cursor location
uint16_t cursor_location() ; 
//move cursor
void move_cursor(uint8_t x , uint8_t y) ; 








#endif 
