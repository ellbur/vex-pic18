
#include "ru_shoulder.h"
#include "ru_config.h"
#include "ru_motor.h"

void Set_Shoulder_Speed(int s_pwm)
{
	LEFT_SHOULDER  = Normalize_PWM(To_U(Flip(s_pwm)));
	RIGHT_SHOULDER = Normalize_PWM(To_U(s_pwm));
}

void Manual_Shoulder_Routine(void)
{
	Set_Shoulder_Speed(Bang_Bang(To_S(SHOULDER_BUTTON)));
}

int Get_Shoulder_Pot(void)
{
	int pot;
	
	pot = Get_Analog_Value(SHOULDER_POT);
	if (pot > 900) return 0;
	
	return pot;
}
