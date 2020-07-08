#ifndef HEX_PRINT_H
#define HEX_PRINT_H
#include <stdint.h>
#include "../includes/Kconstants.h" 





typedef enum BITSIZE { BIT_8 = 2 , BIT_16 = 4 , BIT_32 = 8 }BITSIZE ; 





 struct HEX_LAYOUT {
	uint8_t value[16] ; 
	uint8_t formated_string[18] ;
	uint8_t size ; 


};

typedef struct HEX_LAYOUT HEX_LAYOUT ; 





/* location = pointer location to be read
 * bit_size = size of data to be read : 8 , 16 , 32 bits
 * ret_value = value returned : must be of size 2 , 4 , 8 
 */
void  read_hex (unsigned char* location , unsigned char bit_size , char* ret_value) ;

/* 
 * Provide the number to convert to hex , and only hex_returned->size (BIT_8 , BIT_16 , BIT_32) 
 * returned string is under form "0x..." 
 */
char* to_hex(uint32_t number , BITSIZE bit); 

/*
 * same than to_hex , but returns string under form "$..." 
 *
 */
char* hex_address_format(uint32_t number , BITSIZE bit) ; 













#endif
