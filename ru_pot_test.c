
#include "ru_pot_test.h"
#include "ru_config.h"
#include "ru_motor.h"

#define NUM_POTS 6

void Pot_Test_Routine(void)
{
	int pots[NUM_POTS];
	
	pots[0] = Get_Analog_Value(rc_ana_in01);
	pots[1] = Get_Analog_Value(rc_ana_in02);
	pots[2] = Get_Analog_Value(rc_ana_in03);
	pots[3] = Get_Analog_Value(rc_ana_in04);
	pots[4] = Get_Analog_Value(rc_ana_in05);
	pots[5] = Get_Analog_Value(rc_ana_in06);
	
	printf("%d,%d,%d,%d,%d,%d\n",
		pots[0], pots[1], pots[2],
		pots[3], pots[4], pots[5] );
}
