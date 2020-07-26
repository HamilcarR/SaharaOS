#include "../includes/stdio.h"
#include "../../drivers/display/includes/video.h"
#include "../includes/hex_print.h" 
#define BUFFER_SIZE 256




static void empty_buffer(char* buffer , size_t size){
	size_t i = 0 ; 
	for(; i < size ; i++)
		buffer[i] = 0 ; 



}

static void add_value(char* buffer , char *c ,  int *buffer_position ){

		if(*buffer_position < BUFFER_SIZE  ) { 
			buffer[*buffer_position] = *c ; 
			*buffer_position += 1 ;
		}
		else{
			/* if buffer is complete , we flush */
			video_write((const char*) buffer , false) ;
			empty_buffer(buffer , BUFFER_SIZE) ;
			*buffer_position = 0 ; 
		}

}



void kprint(const char* text , ... ) {
	va_list args ; 
	va_start( args , text ) ; 
	static char buffer[BUFFER_SIZE] ;  //string buffer, end with '\0'
	empty_buffer(buffer , BUFFER_SIZE) ; 
	int buffer_position = 0 ; 
	set_attribute(0x0E); 
	char *c =(char*) text ; 

	while(*c != '\0'){
		if( *c == '%'){ 
parameter:					// Am I a heretic ? 
			c++ ; 
			switch(*c) {
				case 'd' : ; 	//integer
					
					int number = va_arg(args , int) ; 
					const char* int_to_str = itostr(number) ; 
					char *cc = (char*) int_to_str ; 
					for ( ; *cc != '\0' ; cc++) 
						add_value(buffer , cc , &buffer_position) ; 
						
				break ; 

				case 'f' : ; 	//float
					double numberf = va_arg(args , double) ; 
					const char* float_to_str = ftostr(numberf) ; 
					char *cc2 = (char*) float_to_str ; 
					for ( ; *cc2 != '\0' ; cc2++) 
						add_value(buffer , cc2 , &buffer_position) ; 
				break; 

				case 'p' : ;    //pointer 
					uint32_t *pointer = va_arg(args , uint32_t*) ; 
					const char* hex = (const char*) hex_address_format((uint32_t) pointer , BIT_32) ; 
					char *cc3 = (char*) hex ; 
					for( ; *cc3 != '\0' ; cc3++)
						add_value(buffer , cc3 , &buffer_position) ; 
				break ; 
				
				case 'c' : ; 	//character
					char cc1 = (char) va_arg(args , int) ; 
					add_value(buffer , &cc1 , &buffer_position) ; 
				break ; 
				
				case 's' : ;  	//const char *
					char* str = va_arg(args , char*) ; 
					for( ; *str != '\0' ; str++)
						add_value(buffer , str  , &buffer_position) ; 
				break ; 

				case 'x' :       //hexa integer
					
				break ; 
				
				case 'b' : ;     //binary
					uint32_t val = va_arg(args , uint32_t) ; 
					const char* binary = binary_str(val);
					char* strr =(char*) binary ; 
					for(; *strr !=  '\0' ; strr++)
						add_value(buffer , strr , &buffer_position) ; 
				break;
					   
				default : ;
					char v = '%' ; 
					add_value(buffer , &v , &buffer_position) ; 
					add_value(buffer , c , &buffer_position) ; 
				break ; 


			}
			c++ ;
			if(*c == '%')
				goto parameter ; 
		}
		add_value(buffer , c , &buffer_position) ; 
		
		c++ ; 
	}

	video_write((const char*) buffer  , false) ; 



}











void kprint_err(const char* text){
	set_attribute(0x04) ; 
	kprint(text) ; 
}




















