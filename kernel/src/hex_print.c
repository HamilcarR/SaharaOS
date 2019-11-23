#include "../includes/hex_print.h" 







 void read_hex (char* location , uint8_t bit_size , char* ret_value){
	
	const char BASE16[16] = "0123456789ABCDEF" ; 
	char*  pointer = location ; 
	char* temp = pointer ; 
	if(bit_size == 8){
		char high = BASE16[(*temp >> 4)] ; 
		char low = BASE16[(*temp & 0x0F)] ; 
		ret_value[0] = high ; 
		ret_value[1] = low ; 


	}
	
}



