
#include "ru_shoulder.h"
#include "ru_config.h"
#include "ru_motor.h"

void Manual_Shoulder_Routine(void)
{
	int dir;
	
	dir = Get_Shoulder_Button();
	
	if (dir < 0) {
		Set_Shoulder_Speed(-127);
	}
	else if (dir > 0) {
		Set_Shoulder_Speed(+127);
	}
	else {
		Set_Shoulder_Speed(0);
	}
}

int Get_Shoulder_Pot(void)
{
	int pot;
	
	pot = Get_Analog(SHOULDER_POT_NUM);
	if (shoulder_pot_reverse) {
		pot = (int)1023 - pot;
	}
	
	return pot;
}
