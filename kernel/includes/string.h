#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include "memory.h"









//returns size of string 'str' 
size_t strlen(const char* str) ; 


/* copy from src to dest until '\0' is found 
 * must be pre-allocated
 * returns address of the dest
 */
char* strcpy(char* dest , const char* src) ; 



















#endif 
