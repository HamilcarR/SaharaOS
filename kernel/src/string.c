#include "../includes/string.h"









/*****************************************************************************************/
size_t strlen(const char* str){
	const char *c = str ; 
	size_t  size = 0 ; 
	while (*(c++) != '\0') 
		size++ ; 

	return size ; 
}


/*****************************************************************************************/

char* strcpy(char* dest , const char* src){
	char *base_dest = dest; 
	const char* ptr = src ; 
	while( *ptr != '\0') 
		*(dest++) = *(ptr++) ; 
	*dest = '\0' ; 
	return base_dest ; 


}
