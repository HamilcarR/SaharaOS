#include "../includes/heap.h"
#include "../includes/data_struct.h"








static binary_tree_t* deallocation_tree ; 






int compare_function(void* X , void* Y) {
	MEM_HEADER* blockX = (MEM_HEADER*) X ; 
	MEM_HEADER* blockY = (MEM_HEADER*) Y ; 
	if(blockX->size < blockY->size)
		return -1 ; 
	if(blockX->size > blockY->size)
		return 1 ; 
	else
		return 0 ; 


}






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
uint8_t* is_allocated(uint8_t* ptr ){
	const void* BEGIN_MEMORY =(void*) START_HEAP ; 
	MEM_HEADER* base = (MEM_HEADER*) BEGIN_MEMORY ; 
	
	while(base){

		if(base->data_pointer == ptr) 
			return (uint8_t*) base ; 
		base = (MEM_HEADER*) base->next_block_pointer ; 
	}
	return NULL ; 

}







/********************************************************************************************/

/*returns address of new block*/
uint8_t* allocate_next_block(size_t size ,  MEM_HEADER* block) {

	uint8_t *next_addr = (uint8_t*) block->block_pointer + (sizeof(MEM_HEADER) + block->size) ; 
	block->next_block_pointer = next_addr ; 
	if(size > (uint32_t) (END_HEAP) - ((uint32_t) next_addr + sizeof(MEM_HEADER))) 
		return NULL ; 
	MEM_HEADER* new_header = (MEM_HEADER*) next_addr ; 
	new_header->descriptor = 0x80 ;
	new_header->size = size ;
	new_header->block_pointer = next_addr ; 
	new_header->next_block_pointer = NULL ; 
	new_header->prev_block_pointer = block->block_pointer ; 
	new_header->data_pointer = next_addr + sizeof(MEM_HEADER)  ; 		
	return next_addr ; 


}





/********************************************************************************************/
uint8_t* find_free_block(size_t size , MEM_HEADER *base_mem){
	uint8_t * ptr = base_mem->next_block_pointer ; 
	uint8_t * prev = (uint8_t*) base_mem ;

	MEM_HEADER temp ; 
	temp.size = size ; 
	//we use a best fit binary search in the tree and retrieve the smallest memory block in which the new allocated resource can fit
	tree_node_t* node = binary_tree_search_smallest(deallocation_tree ,&compare_function , &temp);  
	if(node != NULL){
		MEM_HEADER* ret = (MEM_HEADER*) node->data ;
		kprint("%d  %h\n" , ret->size , ret->data_pointer); 
		ret->descriptor = 0x80 ; 
		binary_tree_node_remove(deallocation_tree , node , &compare_function) ; 
		return ret->data_pointer ; 

	}
	while(ptr){
		const MEM_HEADER *next_header = (const MEM_HEADER*) ptr ; 
		prev = ptr ; 
		ptr = next_header->next_block_pointer ; 
	}
	uint8_t* new_ptr =  allocate_next_block(size , (MEM_HEADER*) prev);
	if(new_ptr != NULL)
		return ((MEM_HEADER*)new_ptr)->data_pointer ;  
	else 
		return NULL ; 


}





/********************************************************************************************/
void* kmalloc(size_t size) {
	
	const void* BEGIN_MEMORY = (void*) START_HEAP ; 
	MEM_HEADER *base_mem = (MEM_HEADER*) BEGIN_MEMORY ; 
	uint8_t* free_addr = find_free_block(size , base_mem) ; 
	return (void*) free_addr ; 

}

















/********************************************************************************************/


void kfree(void* ptr){
	uint8_t* block = is_allocated(ptr) ; 
	if(!block) 
		return ; 
	MEM_HEADER* block_header = (MEM_HEADER*) block ; 
	block_header->descriptor = 0x00 ; 
	tree_node_t* node = binary_tree_node_create((void*) block_header); 
	binary_tree_add(deallocation_tree , node , &compare_function) ;  	

}













/********************************************************************************************/
void init_heap(){
	
	const void* BEGIN_MEMORY = (void*) START_HEAP ; 
	MEM_HEADER* base_mem = (MEM_HEADER*) BEGIN_MEMORY ; 
	base_mem->descriptor = 0x80 ; 
	base_mem->size = 1 ; 
	base_mem->block_pointer = (uint8_t*) BEGIN_MEMORY ; 
	base_mem->next_block_pointer = NULL ; 
	base_mem->prev_block_pointer = NULL ; 
	base_mem->data_pointer = (uint8_t*) BEGIN_MEMORY + base_mem->size ; 
	deallocation_tree = binary_tree_create(); 


}






