
#include "ru_ramp.h"
#include "ru_config.h"
#include "ru_motor.h"

void Manual_Ramp_Routine(void)
{
	int dir;
	
	dir = Get_Ramp_Button();
	
	if (dir < 0) {
		Set_Ramp_Speed((int)-127);
	}
	else if (dir > 0) {
		Set_Ramp_Speed((int)127);
	}
	else {
		Set_Ramp_Speed((int)0);
	}
}

int Get_Ramp_Pot(void)
{
	int pot;
	
	pot = Get_Analog(RAMP_POT_NUM);
	if (ramp_pot_reverse)
		pot = 1023 - pot;
	
	return pot;
}
