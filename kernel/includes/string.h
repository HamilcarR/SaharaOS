#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include "memory.h"
#include <stdarg.h>


/*characters and string management*/





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

/*reverse string*/
char* strrev(char* str) ; 


/*returns string representation of integer (base 10) */
const char* itostr(int n) ; 

/*returns integer from integer representation in str*/
int stoi(const char* str) ; 

/*returns string representation of f , precision is the number of decimal digits*/
const char* ftostr(double f) ; 

const char* binary_str(uint32_t) ; 


#endif 
