#ifndef TERMINAL_H
#define TERMINAL_H

#define INPUT_DISPLAY_BUFFER_SIZE 10
#define OUTPUT_DISPLAY_BUFFER_SIZE 1024



typedef struct INPUT_DISPLAY{
	char input_display_buffer[INPUT_DISPLAY_BUFFER_SIZE] ; 
}INPUT_DISPLAY; 



typedef struct OUTPUT_DISPLAY{
	char output_display_buffer[OUTPUT_DISPLAY_BUFFER_SIZE]; 

}OUTPUT_DISPLAY;




void init_terminal(); 

























#endif
