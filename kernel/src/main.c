#include "../includes/string.h"
#include "../includes/memory.h" 
#include "../../drivers/display/includes/video.h" 
#include "../includes/mem_debug.h" 
#include "../includes/IDT.h"




extern void* _KERNEL_END ; 



void _start(){

	const char* welcome = "So... what does B.B stand for anyway... ?\n Backstabbing bastard ?\n" ; 
	init_video(); 
	clear_screen() ;
	video_write( welcome , 0x0E , false) ; 
	void* address = &_KERNEL_END ; 


	
	init_idt();

	while(1) ; 
}





