#ifndef IO_PORTS_H
#define IO_PORTS_H
#include <stdint.h>



//gets 8 bits of data from port identifier "port"  
uint8_t  port_byte_in(uint16_t port) ;
//write 8 bits of data to port
void port_byte_out(uint16_t port , uint8_t data); 
//get 16 bits from port
uint16_t port_word_in(uint16_t port) ; 
//write 16 bits to port
void port_word_out(uint16_t port , uint16_t data ) ; 
//wait one cycle of I/O transfer 
void io_wait(); 







#endif
