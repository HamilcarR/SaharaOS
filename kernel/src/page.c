#include "../includes/page.h"
#include "../includes/bitset.h"
#include "../includes/mem_debug.h"
#include "../includes/IDT.h"

#define MEM_CHUNK 0x1000 
#define END_MEMORY 0x10000000

static uint32_t mem_alloc ; 
static uint32_t *frames_bitmap; 
static uint32_t frames_count ; 



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


uint32_t get_first_free_frame(){
	uint32_t i = 0 , j = 0 ;  
	for(i = 0 ; i < frames_count ; i++)
		if(frames_bitmap[i] != 0xFFFFFFFF)
			for(j = 0 ; j < sizeof(uint32_t) * 4 ; j++){
				bool test = test_bit(frames_bitmap , i * sizeof(uint32_t) * 4 + j) ; 
				if(!test) 
					return i * sizeof(uint32_t) * 4 + j ; 

			}
	return 0xFFFFFFFF ; 
}





void page_fault(reg_struct_t reg){
	kprint("\nEAX:%h \nEBX:%h \nECX:%h \nEDX:%h \nESP:%h \nEBP:%h \nESI:%h \nEDI:%h\n",
		 reg.EAX , reg.EBX , reg.ECX , reg.EDX , reg.ESP , reg.EBP , reg.ESI , reg.EDI); 
}



static page_directory_t* kernel_directory ; 

static uint32_t directory[1024] __attribute__((aligned(0x1000))); 




















void init_paging(){
	mem_alloc = (uint32_t) &_END_KERNEL_ADDRESS ; 
	kernel_directory = (page_directory_t*) kmalloc_a(sizeof(page_directory_t)); 
	frames_count = 10 * 1024; 
	frames_bitmap = (uint32_t*) kmalloc_std(frames_count);
	memset(frames_bitmap , 0xEF , frames_count);



	uint32_t i = 0 , j; 
	for(i = 0 ; i < 1024 ; i++){
		kernel_directory->tables[i] = (page_table_t*) kmalloc_a(sizeof(page_table_t)) ;
		for(j = 0 ; j < 1024 ; j++){
			kernel_directory->tables[i]->entries[j] = (j * 0x1000) | 3 ; 

		}
		directory[i] =( (uint32_t)kernel_directory->tables[i]->entries) | 3 ; 
	}






	__asm__("mov %0 , %%CR3" :: "r"(directory )) ; 
	uint32_t cr0 ; 
	__asm__("mov %%CR0 , %0" :"=r"(cr0)); 
	cr0 |= 0x80000001 ; 
	__asm__("mov %0 , %%CR0" :: "r"(cr0)); 



}









void set_page_fault_handler(){
	register_idt_handler(PAGE_FAULT_ERR , &page_fault); 	
}






