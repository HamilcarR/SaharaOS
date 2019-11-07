#ifndef MEM_DEBUG_H
#define MEM_DEBUG_H

#include <stdint.h> 


/*
 * memory dump
 * padding = 8 , 16 , 32 bits read mode 
 * size = size of mem chunk to read in total = size x padding
 */
void display_memory(char* address_start , uint8_t padding , uint32_t size) ;




#endif
