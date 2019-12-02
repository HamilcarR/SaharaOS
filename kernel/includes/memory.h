#ifndef MEMORY_H
#define MEMORY_H
#include <stddef.h>



/*
 * Functions for static memory management ,  will erase previous memory contents
 */


//write memory at location 'destination' , to 'destination + count_bytes - 1 ' , with 'value' 
//returns address

void* memset (void* destination , int value , size_t count_bytes) ; 

//copy from 'src' to 'dest' , 'count_bytes' bytes of memory 
//returns address
void* memcpy (void* dest , void* src , size_t count_bytes) ; 

//returns size of string 'str' 
unsigned int strlen(unsigned char* str) ; 












#endif 
