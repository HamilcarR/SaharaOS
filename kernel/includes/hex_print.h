#ifndef HEX_PRINT_H
#define HEX_PRINT_H
#include <stdint.h>
#include "../includes/Kconstants.h" 




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

/*turns "number" into hex value , depending on HEX_LAYOUT parameter "size" 
*returning back 8,16 or 32 bits hexadecimal representation of "number"
*in "hex_returned"
*/
void to_hex(void *number , HEX_LAYOUT* hex_returned); 




void format_hex(HEX_LAYOUT* hex_layout) ; 
















#endif
