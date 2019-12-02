#include "../includes/memory.h"






/*****************************************************************************************/
void * memset ( void* dest , int value , size_t count){
	unsigned char* memory = (unsigned char*) dest ; 
	while(count>0){
		*memory = (unsigned char) value ;  
		memory++ ; 
		count--; 
	}
	return dest ; 
}


/*****************************************************************************************/
void* memcpy ( void* dest , void* src , size_t count){
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
unsigned int strlen(unsigned char* str){
	unsigned char *c = str ; 
	unsigned int size = 0 ; 
	while (*c != '\0') 
		size++ ; 

	return size ; 


}


