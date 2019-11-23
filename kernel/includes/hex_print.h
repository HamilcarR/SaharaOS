#ifndef HEX_PRINT_H
#define HEX_PRINT_H
#include <stdint.h>
#include "../includes/Kconstants.h" 


/* location = pointer location to be read
 * bit_size = size of data to be read : 8 , 16 , 32 bits
 * ret_value = value returned : must be of size 2 , 4 , 8 
 */
void  read_hex (char* location , uint8_t bit_size , char* ret_value) ;























#endif
