#include "../includes/string.h"
#include "../includes/memory.h" 
#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 
#include "../includes/IDT.h"
#include "../includes/heap.h" 
#include "../includes/stdio.h" 
#include "../../drivers/sound/includes/sound.h" 
#include "../../drivers/PIT/includes/PIT.h"
#include "../../drivers/keyboard/includes/keyboard.h"
#include "../includes/page.h"
#include "../includes/terminal.h"
#include "../includes/data_struct.h" 


void init_systems(){


	init_paging();	
	init_video();
	init_idt();	
	set_page_fault_handler(); 
	init_timer(1000);
	clear_screen() ;
	init_heap() ; 
	kbdriver_init_keyboard();
//	init_terminal(); 

	

}


int compare_int(void* X, void *Y){
	if((int) Y < (int) X)
		return -1 ; 
	if((int) Y > (int) X)
		return 1 ; 
	else
		return 0 ; 

}

void print_int(void* data){
	kprint("%c  " , (char) data); 

}

int search_func(void* X , void* Y){
	if((char) X < (char) Y)
		return 1 ; 
	if((char) X > (char) Y)
		return -1 ;
	else
		return 0 ; 

}

void _start(){
	init_systems() ; 


	int i = 0 ; 
	int* array3 = (int*) kmalloc(6 * sizeof(int));
	for(i = 0 ; i < 6 ; i++)
		array3[i] ='c' ; 
	kfree(array3); 

	int *array = (int*) kmalloc(5 * sizeof(int)); 

	for(i = 0; i < 5 ; i++)
		array[i] = 0xFAFAFAFA ;


	int *array2 = (int*) kmalloc(2 * sizeof(int)); 
	for(i = 0 ; i < 2 ; i++)
		array2[i] = 0xAAAAAAAA ; 


	kprint("\t %h \n" , array) ; 
	for(i = 0 ; i < 5 ; i++) 
		kprint("%h\n" , array[i]); 
	kprint("\n\n"); 

	kprint("\t %h \n" , array2) ; 
	for(i = 0 ; i < 2 ; i++) 
		kprint("%h\n" , array2[i]); 
	kprint("\n\n"); 


	kprint("\t %h \n" , array3) ; 
	for(i = 0 ; i < 6 ; i++) 
		kprint("%c\n" ,(char) array3[i]); 
	kprint("\n\n"); 




}





