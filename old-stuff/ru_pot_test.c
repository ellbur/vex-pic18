
#include "ru_pot_test.h"
#include "ru_config.h"
#include "ru_motor.h"

void Pot_Test_Init(void)
{
	
}

void Pot_Test_Routine(void)
{
	printf("%d,%d,%d,%d,%d,%d\n",
		(int) Get_Analog_Value(SHOULDER_POT),
		(int) Get_Analog_Value(RAMP_POT) );
}
