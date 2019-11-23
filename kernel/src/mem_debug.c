#include "../includes/mem_debug.h" 
#include "../../drivers/display/includes/video.h"










char hex_to_ascii(uint8_t* hex , uint8_t size){



}

void display_memory (char * address_start , uint8_t padding , uint32_t size ,uint8_t color ,bool erase) {
	if(erase)
		video_write("\0" , 0x0 , true); 
	else
		video_write("\n" , 0x0 , false) ;  

	char* start = address_start ; 
	char temp[2] ={'F'} ; 
		uint32_t i = 0 ; 
		for (i = 0  ; i < size ; i++){
			uint32_t j = 0 ; 
			for(j = 0 ; j < padding ; j++){
				read_hex(start , 8 , temp) ; 
				char display[3] = { temp[0] , temp[1] , '\0'} ; 
				video_write(display , color , false) ;
				video_write("  " , 0x00 , false) ;
				start ++ ; 
			}
			video_write("\n" , 0x00 , false) ; 
		}
	
			
}





