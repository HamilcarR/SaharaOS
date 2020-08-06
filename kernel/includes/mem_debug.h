#ifndef MEM_DEBUG_H
#define MEM_DEBUG_H

#include "../includes/Kconstants.h" 
#include <stdint.h> 
#include "hex_print.h"  
#include "stdio.h"
/*
 * memory dump
 * padding = chunks of bytes to display (4  , or 8)  
 * size = size of mem chunk to read in total = size x padding
 */
void display_memory(char* address_start , uint8_t padding , uint32_t size ,uint8_t color ,bool erase) ;

/*
 * display provided byte
 */
void display_byte(char byte , uint8_t color ) ;




#endif
