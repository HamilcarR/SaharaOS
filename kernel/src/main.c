#include "../includes/string.h"
#include "../includes/memory.h" 
#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 
#include "../includes/IDT.h"
#include "../includes/heap.h" 
#include "../includes/stdio.h" 
#include "../../drivers/sound/includes/sound.h" 
#include "../../drivers/PIT/includes/PIT.h"

void init_systems(){

	init_idt();	
	init_heap() ; 
	init_video();
	init_timer(1000);
	clear_screen() ;
	
}


void _start(){
	init_systems() ; 
	set_attribute(0x0A);
	display_memory((char*) 0xB8000 , 8 , 16 , 0x0E , false);
	5/0 ; 	

	while(1) ;


		
}





