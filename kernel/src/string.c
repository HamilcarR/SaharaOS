#include "../includes/string.h"
#include "../includes/math.h"







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



/*****************************************************************************************/
 char* strrev( char* str) {
	int size = strlen(str) ; 
	char temp ; 
	int i = 0 , j = 0 ; 
	for(i = 0 , j = size-1 ; i <= size/2 && j >= size/2 ; i++ , j--){
		temp = str[i] ; 
		str[i] = str[j] ; 
		str[j] = temp ; 
	}

	return str; 

}















/*****************************************************************************************/


static const char* num_table = "0123456789";

const char* itostr(int n) {


	unsigned int div =  n >= 0 ? n : -n ; 
	unsigned int base = 10 ; 
	static char result[13] = {0} ; //max value for a 32bits  integer has 10 digits + '\0' 
	int i = 0 ;
	unsigned int temp = 0 ; 
	while((temp = div/base)){
		result[i] = num_table [div % base ] ; 
		i++;
		div = temp ; 
	}
	result[i] = num_table[div % base ] ;
	const char* p = (const char*) result ;
	strrev((char*) p) ; 
	if( n < 0 ) {
		i = 0 ; 
		size_t size = strlen((const char*) result) ; 
		for(i = size ; i >= 1 ; i--){
			result[i] = result[i-1] ;  
		}

		result[0] = '-' ; 
		result[12] = '\0' ; 


	}

	return (const char*) result ; 

}




/*****************************************************************************************/



int get_number_index(char c) {
	int i = 0 ; 
	for(i = 0 ; i < 10 ; i++)
		if(c == num_table[i]) 
			return i ; 
	return -1 ; 
}
int stoi(const char* str){
	size_t size = strlen(str) ; 
	int i = 0 ; 
	int result = 0 ;
	char* p = (char*) str; 
	for(i = size-1 ; i >= 0 ; i--){
		int number = get_number_index(*p) ; 
		if(number == -1) 
			return 0 ; 
		result += pow(10 , i ) * number;
		p++ ;
	}
	return result ; 

}











