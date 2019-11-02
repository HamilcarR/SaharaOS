#ifndef VIDEO_H
#define VIDEO_H




//write until '\0' is encountered
void video_write( unsigned char *string , char color);
//clear the screen
void clear_screen () ; 
//write to position (COL , ROW) 
void video_write_to(unsigned char* string , char color , uint16_t col , uint16_t row); 










#endif 
