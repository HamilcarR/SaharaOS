#include "../includes/string.h"
#include "../includes/memory.h" 
#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 
#include "../includes/IDT.h"
#include "../includes/heap.h" 
#include "../includes/stdio.h" 



void init_systems(){

	init_idt();	
	init_heap() ; 
	init_video(); 
	clear_screen() ;

}


void _start(){
	init_systems() ; 
	
	set_attribute(0x90); 
	kprint("Displaying memory at $B8000") ;
	display_memory((char*) 0xB8000 , 8 , 16 , 0x0E , false);


	while(1) ; 
}





