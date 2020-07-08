#include "../includes/hex_print.h" 
#include "../includes/memory.h" 



static const unsigned char BASE16[16] = "0123456789ABCDEF" ; 

/*****************************************************************************************/
static void int_to_hex8(uint8_t number , unsigned char* tab){
	tab[0] = BASE16[(number >> 4)] ; //high 4-bits
	tab[1] = BASE16[(number & 0x0F)] ; //lower 4-bits

}
/*****************************************************************************************/
static void int_to_hex16(uint16_t number , unsigned char* tab){
	unsigned char temp_low[2] ; 
	unsigned char temp_high[2] ; 
	uint8_t high = number >> 8 ;			//ex : number = 01011010 01001010 	
	uint8_t low = number & 0x00FF ; 		// 	         high      low
	int_to_hex8(high , temp_high) ; 		//high = number	>> 8 : 00000000  01011010 
	int_to_hex8(low , temp_low) ; 			//low = number & 0x00FF : 00000000 01001010
	tab[0] = temp_high[0] ;  
	tab[1] = temp_high[1] ; 
	tab[2] = temp_low[0] ; 
	tab[3] = temp_low[1] ; 
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
		tab[i] = temp_high[i] ; 
		tab[i+4] = temp_low[i] ; 
	}
}
/*****************************************************************************************/
static void format_hex(HEX_LAYOUT* hex_layout){ /* we use that function to get the "0x" notation */
	uint8_t i ;
	hex_layout->formated_string[0] = '0';		 
	hex_layout->formated_string[1] = 'x'; 
	int j = 0 ; 
	for(i = 2 ; i < hex_layout->size + 2 ; i++){
		hex_layout->formated_string[i] = hex_layout->value[i-2] ; 
		j = i ; 
	}
	hex_layout->formated_string[j+1] = '\0' ; 

}

/*****************************************************************************************/
char* to_hex(uint32_t number , BITSIZE bit){
	static HEX_LAYOUT ret_value ;
	ret_value.size = bit ; 
	if(ret_value.size == 2){        //returns 8 bits representation
		uint8_t ret_array[2] ; 
		int_to_hex8( (uint8_t)number , ret_array) ;
		ret_value.value[0] = ret_array[0] ; 
		ret_value.value[1] = ret_array[1] ; 
		
	}
	if(ret_value.size == 4){ // 16 bits representation
		uint8_t ret_array[4] ; 
		int_to_hex16( (uint16_t)number , ret_array) ; 
		ret_value.value[0] = ret_array[0] ; 
		ret_value.value[1] = ret_array[1] ; 
		ret_value.value[2] = ret_array[2] ; 
		ret_value.value[3] = ret_array[3] ; 
		
	}

	if(ret_value.size == 8){// 32 bits representation 
		uint8_t ret_array[8] ; 
		int_to_hex32( (uint32_t)number , ret_array) ;
		uint8_t i ; 
		for (i = 0 ; i < ret_value.size ; i++)
			ret_value.value[i] = ret_array[i] ; 

	}

	format_hex(&ret_value) ; 
	return (char*) ret_value.formated_string ; 
	
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

/*****************************************************************************************/


char* hex_address_format(uint32_t number , BITSIZE bit){
		const char* hex = to_hex(number , bit) ; 
		static char address_format[10]	; 
		char *c = (char*)hex + 2 ; 
		for( ; *c == '0' ; c++) ; 
		memset(address_format , 0 , 9) ; 
		memcpy(address_format + 1 , c , 8) ; 
		address_format[0] = '$' ;

		return (char*) address_format ; 
}




