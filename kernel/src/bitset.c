#include "../includes/bitset.h" 










void set_bit(uint32_t* bitset , uint32_t idx){
	uint32_t seg = idx / (sizeof(uint32_t) * 8) ; 
	uint32_t offset = idx % (sizeof(uint32_t) * 8); 
	bitset[seg] = bitset[seg] | ( 1 << ((sizeof(uint32_t) * 8 - 1)  - offset)) ; 
}




void clear_bit(uint32_t* bitset , uint32_t idx){
	uint32_t seg = idx / (sizeof(uint32_t) * 8) ; 
	uint32_t offset = idx % (sizeof(uint32_t) * 8); 
	bitset[seg] = bitset[seg] & ~( 1 << ((sizeof(uint32_t) * 8 - 1)  - offset)) ; 

}


bool test_bit(uint32_t* bitset , uint32_t idx){
	uint32_t seg = idx / (sizeof(uint32_t) * 8) ; 
	uint32_t offset = idx % (sizeof(uint32_t) * 8); 
	uint8_t value = (bitset[seg] >> ((sizeof(uint32_t) * 8 - 1)  - offset)) & 0x00000001 ; 
	return value != 0 ; 

}


