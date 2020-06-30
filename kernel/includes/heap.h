#ifndef HEAP_H
#define HEAP_H
#include "Kconstants.h"
#include <stdint.h>





/* Heap implementation */

#define END_HEAP 0x10000




typedef struct KERNEL_MEMORY_ALLOC_HEADER {
	/* descriptor : 
	 * Bit 7 : Used = 1 , free = 0 
	 * Bit 0-6 unused TODO
	 */
	uint8_t descriptor ; 
	size_t size ; /* size of total allocated space in bytes */
	uint32_t *block_pointer ; /*pointer to this block , ie , from header start */
	uint32_t *next_block_pointer ; /*pointer to next block , from next header start*/
	uint32_t *prev_block_pointer ; /*pointer to the previous memory block , from header start*/
	uint32_t *data_pointer ; /*actual pointer returned by kmalloc*/
}__attribute__((packed)) MEM_HEADER ; 





void* kmalloc(size_t size); 

void init_heap() ; 






#endif 
