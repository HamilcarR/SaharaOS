#include "../includes/mem_debug.h" 
#include "../../drivers/display/includes/video.h"









void display_memory (char * address_start , uint8_t padding , uint32_t size ,uint8_t color ,bool erase) {
	if(erase)
		video_write("\0" , 0x0 , true); 
	else
		video_write("\n" , 0x0 , false) ;  
	unsigned char ascii_buffer[8] ={'\0'};
	char* start = address_start ; 
	char temp[2] ={'F'} ; 
		uint32_t i = 0 ; 
		for (i = 0  ; i < size ; i++){
			uint32_t j = 0 ; 
			for(j = 0 ; j < padding ; j++){
				unsigned char* add_temp =(unsigned char*) start ; 
				read_hex((unsigned char*)start , 8 , temp) ; 
				char display[3] = { temp[0] , temp[1] , '\0'} ; 
				video_write(display , color , false) ;
				ascii_buffer[j] = *add_temp ; 
				video_write("  " , 0x00 , false) ;
				start ++ ; 
			
			}

			video_write("     " , 0x00 , false) ;
			
			for(j = 0 ; j < padding ; j++){
				char ascii_temp[2] = {'\0'} ;  
				if((ascii_buffer[j] <= (unsigned char) 0x7E) && (ascii_buffer[j] >= (unsigned char) 0x21))
					ascii_temp[0] = ascii_buffer[j] ; 
					
				else
					ascii_temp[0] = '.' ; 
				
				video_write(ascii_temp , color , false) ; 	
				video_write(" " , 0x00 , false) ; 		
			}
		

			video_write("\n" , 0x00 , false) ; 
		}
	
			
}





