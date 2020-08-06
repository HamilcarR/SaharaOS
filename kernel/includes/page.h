#ifndef PAGE_H
#define PAGE_H

#include "memory.h"
#include "Kconstants.h"



/* P : present
 * RW : if 0 , write not allowed to the page referenced 
 * US : user/supervisor , if 0 user mode not allowed access to the page referenced
 * PWT : page level write through : determines memory type used to access page referenced
 * PCD : page level cache disable : determines memory type used to access page referenced
 * A : accessed : 1 if software accessed the page referenced
 * D : dirty : 1 if software has written to this entry
 * PAT : if PAT supported 1 , otherwise 0 
 * G : global : if CR4.PGE = 1 , determines whether the translation is global if 1 , otherwise 0
 * UNUS : ignored
 * frame_address : physical address of the 4KB page referenced
 */

typedef struct page_entry_t{
	uint32_t P : 1 ; //lowest bits
	uint32_t RW : 1 ; 
	uint32_t US : 1 ; 
	uint32_t PWT: 1 ; 
	uint32_t PCD: 1 ; 
	uint32_t A : 1 ; 
	uint32_t D : 1 ; 
	uint32_t PAT: 1 ; 
	uint32_t G : 1 ; 
	uint32_t UNUS: 3 ; 
	uint32_t frame_addr : 20 ; //highest bits  

} page_entry_t ; 





typedef struct page_table_t{
	uint32_t entries[1024] ; 

}__attribute__((aligned(0x1000))) page_table_t ; 

typedef struct page_directory_t{
	page_table_t *tables[1024];
}__attribute__((aligned(0x1000))) page_directory_t ; 


void init_paging();



uint32_t kmalloc_std(uint32_t size); 
uint32_t kmalloc_phys(uint32_t size , uint32_t* phys); 
uint32_t kmalloc_a(uint32_t size); 





void page_fault(reg_struct_t reg); 
void set_page_fault_handler(); 
uint32_t get_first_free_frame(); 







#endif
