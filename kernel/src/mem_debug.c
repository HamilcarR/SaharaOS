#include "../includes/mem_debug.h" 
#include "../../drivers/display/includes/video.h"





/*****************************************************************************************/
/*                This reads memory at location "address_start"
 *                it produces the hexadecimal code in A and the ascii in B
 *		
 *					padding
 *				----------------------
 *  		$3000	  |	53 61 68 FF FF FF FF FF     S a h . . . . .      
 * size * 	$3009	  |	FF FF FF FF FF FF FF FF     . . . . . . . .
 * padding	$3011	  |	FF FF FF FF FF FF FF FF     . . . . . . . . 
 *
 *				 	A			    B
 *
 * "padding" is the number of elements on one line
 * "size" represents total memory read
 *  "erase" erase the screen (bug fix)  
 */

/*****************************************************************************************/


void display_memory (char * address_start , uint8_t padding , uint32_t size ,uint8_t color ,bool erase) {
	set_attribute(0x0) ; 
	if(erase)
		video_write("\0" , true); 
	else
		video_write("\n" , false) ;  
	unsigned char ascii_buffer[8] ={'\0'};
	char* start = address_start ; 
	char temp[2] ={'F'} ; 
		uint32_t i = 0 ; 
		for (i = 0  ; i < size ; i++){
			uint32_t j = 0 ;
			char* hex = hex_address_format((uint32_t) start , BIT_32) ;
			set_attribute(0x04); 
			video_write( hex  , false) ;  
			set_attribute(0x0) ; 
			video_write("  " , false) ; 
			
			/*this writes hexadecimal values of memory ,similar to the "A" section  in the previous comment */
			for(j = 0 ; j < padding ; j++){  
				unsigned char* add_temp =(unsigned char*) start ; 
				read_hex((unsigned char*)start , 8 , temp) ; 
				char display[3] = { temp[0] , temp[1] , '\0'} ; 
				set_attribute(0x0E); 
				video_write(display , false) ;
				ascii_buffer[j] = *add_temp ; 
				video_write("  " , false) ;
				start ++ ; 
			}
			set_attribute(0x00) ; 
			video_write("     "  , false) ;
			
			/*this writes the ascii values of the memory , similar to "B"
			 * any values not representing a readable character (alpha numeric char)  ie ,
			 * <= 0x7E or >= 0x21 are represented by a '.' */

			for(j = 0 ; j < padding ; j++){
				char ascii_temp[2] = {'\0'} ;  
				if((ascii_buffer[j] <= (unsigned char) 0x7E) && (ascii_buffer[j] >= (unsigned char) 0x21))
					ascii_temp[0] = ascii_buffer[j] ; 
				else
					ascii_temp[0] = '.' ; 
				set_attribute(0x05) ; 
				video_write(ascii_temp  , false) ; 	
				set_attribute(0x00) ; 
				video_write(" "  , false) ; 		
			}
			video_write("\n" , false) ;
		}
			
}



/*****************************************************************************************/

void display_byte(char byte , uint8_t color , bool erase ){
	char* hex = to_hex((uint32_t) byte , BIT_8) ; 
	set_attribute(color) ; 
	video_write( hex , false) ; 
}


