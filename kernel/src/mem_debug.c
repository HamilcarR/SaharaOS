#include "../includes/mem_debug.h" 
#include "../../drivers/display/includes/video.h"


/*****************************************************************************************/
/*                This reads memory at location "address_start"
 *                it produces the hexadecimal code in A and the ascii in B
 *
 *
 *53 61 68 FF FF FF FF FF     S a h . . . . .      
 *FF FF FF FF FF FF FF FF     . . . . . . . .
 *FF FF FF FF FF FF FF FF     . . . . . . . . 
 *
 *	A			B
 *
 * "padding" is the number of elements on one line
 * "size" represents total memory read
 *  "erase" erase the screen (bugged)  
 */

/*****************************************************************************************/


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
			video_write("  " , 0x00 , false) ; 
			/*this writes hexadecimal values of memory ,similar to the "A" section  in the previous comment */
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
			/*this writes the ascii values of the memory , similar to "B"
			 * any values not representing a readable character ie , <= 0x7E or >= 0x21 are represented
			 * by a '.' */
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





