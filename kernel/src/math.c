#include "../includes/math.h"







int pow (int arg , int exp){
	int i = 0 ; 
	int result = 1 ; 
	for (i = 0 ; i < exp ; i++)
		result = result * arg ; 
	return result ; 
}


