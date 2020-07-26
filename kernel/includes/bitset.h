
#ifndef BITSET_H
#define BITSET_H

#include "memory.h"
#include "Kconstants.h"
/* bitmap implementation */



void set_bit(uint32_t* bitset , uint32_t idx); 

void clear_bit(uint32_t* bitset , uint32_t idx) ; 

bool test_bit(uint32_t* bitset , uint32_t idx ) ;  












#endif
