#include "../includes/terminal.h"
#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 
#include "../../drivers/keyboard/includes/keyboard.h"
#include "../includes/string.h"
#include "../includes/memory.h"

static INPUT_DISPLAY input ; 
static OUTPUT_DISPLAY output ; 







static const char* commands[] = {
	"mdisplay", 
	"echo",
	"ls"

} ; 

void clear_input_display(){
	uint32_t i = 0 ; 
	for(i = 0 ; i < INPUT_DISPLAY_BUFFER_SIZE ; i++)
		input.input_display_buffer[i] = 0 ; 

}

void flush_input_buffer(){
	memset(input.input_display_buffer , 0 , INPUT_DISPLAY_BUFFER_SIZE) ; 

}

void add_to_input_buffer(char c) {
	int32_t i = 0 ; 
	for(i = INPUT_DISPLAY_BUFFER_SIZE - 2 ; i >= 0 ; i--)
		input.input_display_buffer[i] = input.input_display_buffer[i-1] ; 
	input.input_display_buffer[INPUT_DISPLAY_BUFFER_SIZE - 1] = 0 ; 
	input.input_display_buffer[0] = c ; 

}


bool terminal_quit(){
	
	return strcmp((const char*) input.input_display_buffer , strrev("quit") ) == 0; 

}


void init_terminal(){
	bool loop = true ; 
	while(loop){	
		char c = kbdriver_get_char(); 
		if(c != 0){
			if(c == '\r'){
				loop = !terminal_quit(); 
				flush_input_buffer();
			}
			else{	
				add_to_input_buffer(c) ;
			}
				display_memory((char*) input.input_display_buffer , 8 , 16 , 0 , true);
				putchar(input.input_display_buffer[0]);
			
		}
			
		sys_sleep(1) ; 
	}
	


}
