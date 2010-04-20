
#include "ru_elbow.h"
#include "ru_config.h"
#include "ru_motor.h"

void Set_Elbow_Speed(int s_pwm)
{
	ELBOW = To_U(Flip(s_pwm));
}

void Manual_Elbow_Routine(void)
{
	Set_Elbow_Speed(Bang_Bang(To_S(ELBOW_BUTTON)));
}
