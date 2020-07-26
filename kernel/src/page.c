#include "../includes/page.h"
#include "../includes/bitset.h"
#include "../includes/mem_debug.h"
#include "../includes/IDT.h"

#define MEM_CHUNK 0x1000 
#define END_MEMORY 0x10000000

static uint32_t frames_count;
static uint32_t *bit_frames ; 
static uint32_t mem_alloc ; 
static page_directory_t* kernel_directory ; 




uint32_t kmalloc_std(uint32_t size){
	
	uint32_t val = mem_alloc ; 
	mem_alloc += size ; 
	return val ; 
}


uint32_t kmalloc_a(uint32_t size){
	if(mem_alloc & 0x00000FFF){
		mem_alloc &= 0xFFFFF000 ; 
		mem_alloc += MEM_CHUNK ; 
	}
	uint32_t val = mem_alloc ; 
	mem_alloc += size ; 
	return val ; 

}



uint32_t kmalloc_phys(uint32_t size , uint32_t* phys){
	if(mem_alloc & 0x00000FFF){
		mem_alloc &= 0xFFFFF000 ; 
		mem_alloc += MEM_CHUNK ; 
	}
	if(phys)
		*phys = mem_alloc ; 
	uint32_t val = mem_alloc ; 
	mem_alloc += size ; 
	return val ; 

}




int32_t get_first_free_frame(){
	uint32_t i = 0 , j = 0 ; 
	for(; i < (uint32_t)(frames_count/(sizeof(uint32_t) * 8 )) ; i++)
		if(bit_frames[i] != 0xFFFFFFFF)
			for(j = 0 ; j < (sizeof(uint32_t) * 8) ; j++)
				if(!test_bit(bit_frames , i*32+j))
					return i*32 + j ; 
	return -1 ; 
}







void allocate_frame(page_entry_t* page , int kernel_space , int write){
	if(!page->frame_addr){
		int32_t first_frame = get_first_free_frame(); 
		if(first_frame == -1)
			K_PANIC("No free frame" , __func__ , __FILE__ , __LINE__) ; 
		set_bit(bit_frames , first_frame); //set to 1 the first frame we found
		page->P = 1 ; 
		page->RW = write ? 1 : 0; 
		page->US = kernel_space ? 0 : 1 ; 
		page->frame_addr = (uint32_t) first_frame * (uint32_t)MEM_CHUNK; 	
	}
}




void dealloc_frame(page_entry_t* page){
	if(page->frame_addr){
		clear_bit(bit_frames , page->frame_addr/(uint32_t) MEM_CHUNK ) ; 
		page->frame_addr = 0 ; 
	}

}



page_entry_t* get_page(uint32_t address , int make , page_directory_t* dir){
	uint32_t dir_idx_offset = (address & 0xFFC00000) >> 22 ; //tenth highest bits are directory offsets 
	uint32_t table_idx_offset = (address & 0x003FF000) >> 12 ; // next tenth highest bits are table offsets
	bool is_initialized = dir->tables[dir_idx_offset] != NULL ; 

	if(is_initialized){
		page_entry_t* page = &(dir->tables[dir_idx_offset]->entries[table_idx_offset]) ; 
		return page ; 
	}
	if(make){
		uint32_t phys_addr ; 
		dir->tables[dir_idx_offset] = (page_table_t*) kmalloc_phys(sizeof(page_table_t) , &phys_addr) ; 
		memset(dir->tables[dir_idx_offset] , 0 , sizeof(page_table_t));
		dir->table_phys_addr[dir_idx_offset] = phys_addr | 7 ; 
		return &(dir->tables[dir_idx_offset]->entries[table_idx_offset]) ;
	}
	return NULL ; 

}






void init_paging(){
	mem_alloc = (uint32_t) &_END_KERNEL_ADDRESS ; 
	frames_count = END_MEMORY / MEM_CHUNK ; 
	bit_frames = (uint32_t*) kmalloc_std((uint32_t) (frames_count/32)) ; 
	memset(bit_frames , 0 , (frames_count/32)) ; 
	kernel_directory = (page_directory_t*) kmalloc_a(sizeof(page_directory_t)) ; 
	memset(kernel_directory , 0 , sizeof(page_directory_t)); 
	uint32_t i = 0 ; 
	
	kprint("Initializing frames : \n");
	while( i < (uint32_t) END_MEMORY ){
		page_entry_t* page = get_page(i , 1 , kernel_directory); 				
		allocate_frame(page , 0 , 1) ; 
		i += (uint32_t) MEM_CHUNK ;
	
	}
	register_idt_handler(PAGE_FAULT_ERR , &page_fault); 	
	__asm__("mov %0 , %%CR3" :: "r"( &kernel_directory->table_phys_addr )) ; 
	uint32_t cr0 ; 
	__asm__("mov %%CR0 , %0" :"=r"(cr0)); 
	cr0 |= 0x80000001 ; 
	__asm__("mov %0 , %%CR0" :: "r"(cr0)); 
	

}


void page_fault(){


}
















