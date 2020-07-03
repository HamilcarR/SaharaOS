#include "../includes/stdio.h"
#include "../../drivers/display/includes/video.h"
#define BUFFER_SIZE 256




void empty_buffer(char* buffer , size_t size){
	int i = 0 ; 
	for(i = 0 ; i < size ; i++)
		buffer[i] = 0 ; 



}

 void add_value(char* buffer , char *c ,  int *buffer_position ){

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

	char *c =(char*) text ; 
	while(*c != '\0'){

		if( *c == '%'){ 
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
				
				default : 

				break ; 


			}
			c++ ; 
		}
		add_value(buffer , c , &buffer_position) ; 

		c++ ; 
	}

	video_write((const char*) buffer  , false) ; 



}





