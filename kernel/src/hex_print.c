#include "../includes/hex_print.h" 













 void read_hex (unsigned char* location , uint8_t bit_size , char* ret_value){
	
	const unsigned char BASE16[16] = "0123456789ABCDEF" ; 
	unsigned char*  pointer = location ; 
	unsigned char* temp = pointer ; 
	if(bit_size == 8){
		unsigned char high = BASE16[(*temp >> 4)] ; 
		unsigned char low = BASE16[(*temp & 0x0F)] ; 
		ret_value[0] = high ; 
		ret_value[1] = low ; 


	}
	
}



