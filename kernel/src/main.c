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




void init_systems(){


	init_idt();		
	init_video();
	init_timer(1000);
	clear_screen() ;


//	init_heap() ; 
	init_keyboard();

	init_paging();	

}

void _start(){
	init_systems() ; 
}





