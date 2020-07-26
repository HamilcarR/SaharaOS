#include "../includes/PIC.h"
#include "../../ports/includes/IO_ports.h"




#define PICM 		0x20 /* master PIC*/
#define PICS 		0xA0 /* slave PIC*/
#define PICM_COMMAND 	PICM 
#define PICM_DATA 	(PICM + 1) 
#define PICS_COMMAND 	PICS
#define PICS_DATA 	(PICS + 1) 
#define PIC_EOI 	0x20 /*end of interrupt (EOI) */
#define ICW1_ICW4  	0x01 //ICW4 not needed
#define ICW1_SINGLE 	0x02 //Single mode
#define ICW1_INTERVAL4	0x04 //call address interval 4
#define ICW1_LEVEL	0x08 //level triggered mode
#define ICW1_INIT	0x10 //initialization required
#define ICW4_8086	0x01 //8086 mode
#define ICW4_AUTO	0x02 //Auto EOI
#define ICW4_BUF_SLAVE  0x08 //buffered mode slave
#define ICW4_BUF_MASTER 0x0C //buffered mode master
#define ICW4_SFNM	0x10 //special fully nested 










void init_irq_pic(){
	port_byte_out(PICM , 0x11) ; //write command to PIC master and slave
	port_byte_out(PICS , 0x11) ; 

	port_byte_out(PICM_DATA , 0x20) ; //remap PICM to 0x20
	port_byte_out(PICS_DATA , 40) ; //remap PICS to 0x28

	port_byte_out(PICM_DATA , 0x04) ; //IRQ2 connection to slave
	port_byte_out(PICS_DATA , 0x02) ; 

	port_byte_out(PICM_DATA , ICW1_ICW4) ; //ICW4 TO PICM
	port_byte_out(PICS_DATA , ICW1_ICW4) ; //ICW4 to PICS

	port_byte_out(PICM_DATA , 0x00) ; //enable all IRQ on master
	port_byte_out(PICS_DATA , 0x00) ; //enable all IRQ on slave
}















