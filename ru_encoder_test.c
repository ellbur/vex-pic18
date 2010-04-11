
#include "ru_config.h"
#include "ru_encoder_test.h"
#include "ru_encoder.h"

void Encoder_Test_Init(void)
{
}

void Encoder_Test_Routine(void)
{
	static int loop;
	float vel;
	
	printf("%d,%d\n",
		(int) loop,
		(int) encoders[0].count);
	
	loop++;
	
	pwm01 = LEFT_Y;
}
