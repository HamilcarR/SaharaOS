
#ifndef KCONSTANTS_H
#define KCONSTANTS_H

#include <stddef.h>
#include <stdint.h>


typedef enum { false = 0 , true = 1} bool;  
extern const void* _END_KERNEL_ADDRESS ; 


typedef struct reg_struct_t{
	uint32_t EDI , ESI , EBP , ESP , EBX , EDX , ECX , EAX ; 
}reg_struct_t;








#endif
