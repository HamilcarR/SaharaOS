#ifndef MEMORY_H
#define MEMORY_H
#include <stddef.h>
#include <stdint.h>


/*
 * Functions for static memory management ,  will erase previous memory contents
 */


//initialize each byte from memory 'dest' into 'value' , 'count_bytes' times
//returns destination address

void* memset (void* dest , int value , size_t count_bytes) ; 

//copy from 'src' to 'dest' , 'count_bytes' bytes of memory 
//returns dest address
void* memcpy (void* dest , const void* src , size_t count_bytes) ; 


/*
 * Move 'count_bytes' bytes from src to dest 
 * Returns dest address
 *
 * Case 1 : Src pointer < Dest pointer
 *    DDDDDDDDDD   : dest
 * SSSSSSSSSS      : src
 *
 * we memcpy backward , dest[size-1 --] = src[size-1 --]
 *
 * Case 2 : Src pointer > Dest pointer
 *
 * DDDDDDDDDD      : dest 
 *    SSSSSSSSSS   : src
 *
 *
 * we memcpy forward , dest[0 ++] = src[0] ++
 */
void* memmove(void* dest , const void* src , size_t count_bytes);


/* return 0 if the two buffers are the same
 * return 1 if buffer1 greater
 * return -1 if buffer2 greater
 */
int memcmp(const void *buffer1 , const void *buffer2 , size_t count_bytes); 





#endif 
