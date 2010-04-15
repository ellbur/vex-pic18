
#include "ru_shoulder.h"
#include "ru_config.h"
#include "ru_motor.h"

void Set_Shoulder_Speed(int s_pwm)
{
	LEFT_SHOULDER_1  = Normalize_PWM(To_U(Flip(s_pwm)));
	RIGHT_SHOULDER_1 = Normalize_PWM(To_U(s_pwm));
	
	LEFT_SHOULDER_2  = LEFT_SHOULDER_1;
	RIGHT_SHOULDER_2 = RIGHT_SHOULDER_2;
}

void Manual_Shoulder_Routine(void)
{
	Set_Shoulder_Speed(Bang_Bang(To_S(SHOULDER_BUTTON)));
}

int Get_Shoulder_Pot(void)
{
	int pot;
	
	pot = Get_Analog_Value(SHOULDER_POT);
	if (shoulder_pot_reverse) {
		pot = 1023 - pot;
	}
	
	return pot;
}
