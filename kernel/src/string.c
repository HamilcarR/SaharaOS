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


/*****************************************************************************************/

char* strstr(const char* str1 , const char* str2){
	size_t str1_size = strlen(str1) ; 
	size_t str2_size = strlen(str2) ; 
	
	if( str2_size == 0 ) 
		return (char*) str1 ; 
	if( str2_size > str1_size )
		return NULL ; 
	if ( str2_size == str1_size ){
		int8_t ret = memcmp(str1 , str2 , str1_size) ; 
		return ret == 0 ? (char*) str1 : NULL ; 
	}
	else{	
		while( strlen(str1) > strlen(str2) ) {
			if( !memcmp(str1 , str2 , str2_size) )
				return (char*) str1 ; 
			str1 ++ ; 
		}	
		return NULL ; 
	}
}




/*****************************************************************************************/

char* strchr(const char* str , int c) {
	char ch = (char) c ; 
	while(*str != ch && *str != '\0')
		str++ ; 
	return *str == '\0' ? NULL : (char*) str ; 


}

/*****************************************************************************************/

int tolower(int c){
	char ch = (char) c ; 
	if(ch <= 0x5A && ch >= 0x41) 
		return (int) ( c | 0x20) ; 
	return c ; 
	//TODO EOF ? 
}

/*****************************************************************************************/

int toupper(int c) {
	char ch = (int) c ; 
	if(ch <= 0x7A && ch >= 0x61)
		return (int) ( c & 0xDF) ; 
	return ch ; 
}

/*****************************************************************************************/

const char* toupperstr(const char* str){
	char *c = (char*) str ; 
	while(*c != '\0') {
		*c = (char) toupper((int) *c) ;
		c++ ; 
	}
	return str ; 

}






/*****************************************************************************************/


const char* tolowerstr(const char* str){
	char *c = (char*) str; 
	while(*c != '\0') {
		*c = (char) tolower((int) *c) ; 
		c++ ; 
	}
	return str; 
}


























