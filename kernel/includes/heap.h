#ifndef HEAP_H
#define HEAP_H
#include "Kconstants.h"
#include <stdint.h>





/* dynamic physical memory manager*/
#define START_HEAP 0x106000
#define END_HEAP 0xFFFFFFFF



typedef struct KERNEL_MEMORY_ALLOC_HEADER {
	/* descriptor : 
	 * Bit 7 : Used = 1 , free = 0 
	 * Bit 0-6 unused TODO
	 */
	uint8_t descriptor ; 
	size_t size ; /* size of total allocated space in bytes */
	uint8_t *block_pointer ; /*pointer to this block , ie , from header start */
	uint8_t *next_block_pointer ; /*pointer to next block , from next header start*/
	uint8_t *prev_block_pointer ; /*pointer to the previous memory block , from header start*/
	uint8_t *data_pointer ; /*actual pointer returned by kmalloc*/
}__attribute__((packed , aligned(4) )) MEM_HEADER ; 


typedef struct BLOCK_SIZE{
	size_t size ; 
	MEM_HEADER *block_pointer ; 

}BLOCK_SIZE; 


void* kmalloc(size_t size); 
void kfree(void* ptr) ; 
void init_heap() ; 






#endif 
