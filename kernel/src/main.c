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
	char* array = (char*) kmalloc(sizeof(char) * 100) ;
	int i = 0 ; 
	for(i = 0 ; i < 100 ; i++)
		array[i] = 'd'; 
	kfree(array); 
	char* array2 = (char*) kmalloc(sizeof(char) * 99) ; 
	for(i = 0 ; i < 99 ; i++)
		array2[i] = 'c';
	int* lol = kmalloc(sizeof(int) * 10 ) ;
	memset(lol , 'F' , 10 * sizeof(int)); ;
	kfree(lol); 
	char* array3 = (char*) kmalloc(sizeof(char) * 39) ; 
	for(i = 0 ; i < 80 ; i++)
		array3[i] = 'e';
	
	display_memory((char*) (array+90) , 8 , 16, 0x0A , false); 







}





