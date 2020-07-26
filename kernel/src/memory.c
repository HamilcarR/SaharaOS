#include "../includes/memory.h"






/*****************************************************************************************/
void * memset ( void* dest , int value , size_t count){
	unsigned char* memory = (unsigned char*) dest ; 
	while(count>0){
		*memory = value ;  
		memory++ ; 
		count--; 
	}
	return dest ; 
}


/*****************************************************************************************/
void* memcpy ( void* dest , const void* src , size_t count){
	unsigned char* memory_dest = (unsigned char*) dest ; 
	unsigned char* memory_src = (unsigned char*) src ; 
	while(count > 0 ){
		*memory_dest = *memory_src ; 
		memory_dest ++ ; 
		memory_src ++ ; 
		count-- ; 
	}
	return dest ; 
}

/*****************************************************************************************/


void* memmove(void* dest , const void* src , size_t count_bytes){
	size_t size = 0 ; 
	if( ((uintptr_t *) dest) < ((uintptr_t *) src) )
			return memcpy (dest , src , count_bytes) ; 
	else if ( ((uintptr_t *) dest) > ((uintptr_t *) src) ) {
		size = count_bytes-1 ;
		while(size != 0) {
			*((uint8_t*) dest + size) = *((const uint8_t*) src + size) ;
			if(size == 0) break ;  
			size -- ; 
		}
		return dest ; 
	}
	else
		return dest ; 

}


/*****************************************************************************************/

int memcmp(const void* buff1 , const void* buff2 , size_t count_bytes){

	const uint8_t *ptr1 = (const uint8_t*) buff1 ; 
	const uint8_t *ptr2 = (const uint8_t*) buff2 ; 
	while(count_bytes --){
		if(*ptr1 < *ptr2)
			return -1 ; 
		if(*ptr1 > *ptr2)
			return 1 ; 
		ptr1++ ; 
		ptr2++ ; 
	}
	return 0 ; 


}






































