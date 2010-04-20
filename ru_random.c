
#include "ru_random.h"
#include "ru_config.h"

static unsigned int random_number;

void Random_Init(void)
{
	random_number =
		Get_Analog(FRONT_IR_NUM) ^
		Get_Analog(SIDE_FRONT_IR_NUM) ^
		Get_Analog(SIDE_REAR_IR_NUM) ^
		Get_Analog(REAR_IR_NUM) ;
}

unsigned int Random(void)
{
	random_number = random_number * 7524 + 7777;
	random_number = random_number ^ Get_Analog(REAR_IR_NUM);
	
	return random_number;
}
