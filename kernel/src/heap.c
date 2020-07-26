#include "../includes/heap.h"












bool is_free_block(size_t size ,const MEM_HEADER* block){
	if( block->descriptor & 0x80 )  
		return false ; 
	else {
		if( block->size < size ) 
			return false ; 
		return true ; 
	}

}



/********************************************************************************************/
/* returns the address of a block if ptr is a valid data pointer , ie , belongs to a block*/
uint32_t* is_allocated(uint32_t* ptr ){
	const void* BEGIN_MEMORY = &_END_KERNEL_ADDRESS ; 
	MEM_HEADER* base = (MEM_HEADER*) BEGIN_MEMORY ; 
	
	while(base){

		if(base->data_pointer == ptr) 
			return (uint32_t*) base ; 
		base = (MEM_HEADER*) base->next_block_pointer ; 
	}
	return NULL ; 

}







/********************************************************************************************/

/*returns address of new block*/
uint32_t* allocate_next_block(size_t size ,  MEM_HEADER* block) {
	uint32_t* next_addr =(uint32_t*) ( block->block_pointer + sizeof(MEM_HEADER) + block->size)  ; 
	block->next_block_pointer = next_addr ; 
	if( size > (uint32_t) ((uint32_t*) (END_HEAP) - (next_addr + sizeof(MEM_HEADER)))) 
		return NULL ; 
	MEM_HEADER* new_header = (MEM_HEADER*) next_addr ; 
	new_header->descriptor = 0x80 ; 
	new_header->size = size ; 
	new_header->block_pointer = next_addr ; 
	new_header->next_block_pointer = NULL ; 
	new_header->prev_block_pointer = block->block_pointer ; 
	new_header->data_pointer = sizeof(MEM_HEADER) + next_addr ; 		
	return next_addr ; 

}





/********************************************************************************************/
uint32_t* find_free_block(size_t size , MEM_HEADER *base_mem){
	uint32_t * ptr = base_mem->next_block_pointer ; 
	uint32_t * prev = (uint32_t*) base_mem ; 
	while(ptr){
		const MEM_HEADER *next_header = (const MEM_HEADER*) ptr ; 
		if( is_free_block(size , next_header) )
			return ((MEM_HEADER*) ptr)->data_pointer ; 
		prev = ptr ; 
		ptr = next_header->next_block_pointer ; 
	}
	if(prev != NULL){
		uint32_t* new_ptr =  allocate_next_block(size , (MEM_HEADER*) prev); 
		return ((MEM_HEADER*)new_ptr)->data_pointer ;  	
	}
	else
		return NULL ; 


}





/********************************************************************************************/
void* kmalloc(size_t size) {
	
	const void* BEGIN_MEMORY = &_END_KERNEL_ADDRESS ; 
	MEM_HEADER *base_mem = (MEM_HEADER*) BEGIN_MEMORY ; //first heap memory block after kernel section
	uint32_t* free_addr = find_free_block(size , base_mem) ; 
	return (void*) free_addr ; 

}

















/********************************************************************************************/
void kfree(void* ptr){
	const void* BEGIN_MEMORY = &_END_KERNEL_ADDRESS ; 
	uint32_t* block = is_allocated(ptr) ; 
	if(!block) 
		return ; //interrupt ? TODO
	MEM_HEADER* block_header = (MEM_HEADER*) block ; 
	block_header->descriptor = 0x00 ; 	

}













/********************************************************************************************/
void init_heap(){
	
	const void* BEGIN_MEMORY = &_END_KERNEL_ADDRESS ; 
	MEM_HEADER* base_mem = (MEM_HEADER*) BEGIN_MEMORY ; 
	base_mem->descriptor = 0x80 ; 
	base_mem->size = 1 ; 
	base_mem->block_pointer = (uint32_t*) BEGIN_MEMORY ; 
	base_mem->next_block_pointer = NULL ; 
	base_mem->prev_block_pointer = NULL ; 
	base_mem->data_pointer = (uint32_t*) BEGIN_MEMORY + base_mem->size ; 



}






