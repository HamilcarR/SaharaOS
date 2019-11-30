#include "../includes/hex_print.h" 




const unsigned char BASE16[16] = "0123456789ABCDEF" ; 

/*****************************************************************************************/
static void int_to_hex8(uint8_t number , unsigned char* tab){
	tab[0] = BASE16[(number >> 4)] ; //high
	tab[1] = BASE16[(number & 0x0F)] ; 

}
/*****************************************************************************************/
static void int_to_hex16(uint16_t number , unsigned char* tab){
	unsigned char temp_low[2] ; 
	unsigned char temp_high[2] ; 
	uint8_t high = number >> 8 ;			//ex : number = 01011010 01001010 	
	uint8_t low = number & 0x00FF ; 		// 	         high      low
	int_to_hex8(high , temp_high) ; 		//high = number	>> 8 : 00000000  01011010 
	int_to_hex8(low , temp_low) ; 			//low = number & 0x00FF : 00000000 01001010
	tab[0] = temp_low[0] ;  
	tab[1] = temp_low[1] ; 
	tab[2] = temp_high[0] ; 
	tab[3] = temp_high[1] ; 
}
/*****************************************************************************************/
static void int_to_hex32(uint32_t number , unsigned char* tab){
	uint8_t temp_low[4] ; 
	uint8_t temp_high[4] ; 
	uint16_t high = number >> 16 ; 
	uint16_t low  = number & 0x0000FFFF ; 
	int_to_hex16(high , temp_high) ; 
	int_to_hex16(low , temp_low) ; 
	uint8_t i = 0 ; 
	for(i = 0 ; i < 4 ; i++){
		tab[i] = temp_low[i] ; 
		tab[i+4] = temp_high[i] ; 
	}
}
/*****************************************************************************************/
void format_hex(HEX_LAYOUT* hex_layout){ /* we use that function to get the "0x" notation */
	uint8_t i ;
	hex_layout->formated_string[0] = '0';		 
	hex_layout->formated_string[1] = 'x'; 

	for(i = 0 ; i < hex_layout->size ; i++){
		hex_layout->formated_string[i+2] = hex_layout->value[i] ; 

	}

}








/*****************************************************************************************/
void to_hex(void *number , HEX_LAYOUT* ret_value){
	if(ret_value->size == 2){
		uint8_t ret_array[2] ; 
		int_to_hex8( *(uint8_t*)number , ret_array) ;
		ret_value->value[0] = ret_array[0] ; 
		ret_value->value[1] = ret_array[1] ; 
		
	}
	if(ret_value->size == 4){
		uint8_t ret_array[4] ; 
		int_to_hex16( *(uint16_t*)number , ret_array) ; 
		ret_value->value[0] = ret_array[0] ; 
		ret_value->value[1] = ret_array[1] ; 
		ret_value->value[2] = ret_array[2] ; 
		ret_value->value[3] = ret_array[3] ; 
		
	}

	if(ret_value->size == 8){
		uint8_t ret_array[8] ; 
		int_to_hex32( *(uint32_t*)number , ret_array) ;
		uint8_t i ; 
		for (i = 0 ; i < ret_value->size ; i++)
			ret_value->value[i] = ret_array[i] ; 

	}

	format_hex(ret_value) ; 
	
}
/*****************************************************************************************/
 void read_hex (unsigned char* location , uint8_t bit_size , char* ret_value){
	

	unsigned char*  pointer = location ; 
	unsigned char* temp = pointer ; 
	if(bit_size == 8){
		unsigned char high = BASE16[(*temp >> 4)] ; 
		unsigned char low = BASE16[(*temp & 0x0F)] ; 
		ret_value[0] = high ; 
		ret_value[1] = low ; 
	}	
}



