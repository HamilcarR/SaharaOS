#ifndef PIT_H
#define PIT_H
#include "../../ports/includes/IO_ports.h" 


#define PIT_DEFAULT_FREQUENCY 1193182

void init_timer(uint32_t freq) ; 

/*Hang for time ms */
void sys_sleep(uint32_t time) ; 







#endif
