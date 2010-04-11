
#include "ru_input.h"

unsigned char Read_Interrupt_Digital(char num)
{
	switch (num) {
		case  1:  return rc_dig_int1;
		case  2:  return rc_dig_int2;
		case  3:  return rc_dig_int3;
		case  4:  return rc_dig_int4;
		case  5:  return rc_dig_int5;
		case  6:  return rc_dig_int6;
	}
	
	return -5;
}
