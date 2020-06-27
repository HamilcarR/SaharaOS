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


/* returns first occurence of str2 in str1 */
char* strstr(const char* str1 , const char* str2) ; 

/* returns pointer to first occurence of character c if found ,or NULL if not*/
char* strchr(const char* str , int c) ; 


/*returns lowercase of character*/
int tolower(int c) ;

/*returns upper case*/
int toupper(int c) ; 

/*returns uppercase string*/
const char* toupperstr(const char* str) ; 

/*returns lowercase string*/
const char* tolowerstr(const char* str) ; 




#endif 
