#ifndef PAGE_H
#define PAGE_H

#include "../includes/memory.h"




/* P : set if page is present in memory
 *
 * RW : if set , page is writeable , if unset , read only , doesn't apply in kernel mode
 * 
 * US : set , user mode page , else kernel mode page . user mode can't write or read kernel mode page
 * 
 * RSVD1 : reserved 
 *
 * A : set if page has been accessed (set by cpu) 
 *
 * D : set if page has been written to 
 *
 * AVAIL : unused 
 *
 * F_ADDRESS : page frame address : the high 20 bits of the frame address in physical memory
 *
 */
typedef struct PAGE_ENTRY_TABLE{
	uint32_t P : 1 ; 
	uint32_t RW : 1 ; 
	uint32_t US : 1 ; 
	uint32_t RSVD1 : 2 ; 
	uint32_t A : 1 ; 
	uint32_t D : 1 ; 
	uint32_t RSVD2 : 2 ; 
	uint32_t AVAIL : 3 ; 
	uint32_t F_ADDRESS : 19 ; 
}PAGE_ENTRY_TABLE ; 










#endif
