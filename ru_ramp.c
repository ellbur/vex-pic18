
#include "ru_ramp.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_sample.h"

void Set_Ramp_Speed(int spwm)
{
#if kevin
	RAMP_1 = Normalize_PWM(To_U(spwm));
	RAMP_2 = RAMP_1;
#elif nitish
	LEFT_SCISSOR  = Normalize_PWM(To_U(Flip(spwm)));
	RIGHT_SCISSOR = Normalize_PWM(To_U(spwm));
#endif
}

void Manual_Ramp_Routine(void)
{
	Set_Ramp_Speed(Flip(Bang_Bang(To_S(RAMP_BUTTON))));
#if kevin
#if _recording
	if (RAMP < 10 || RAMP > 250) {
		recording = 0;
	}
#endif
#endif
}

void Manual_Joy_Ramp_Routine(void)
{
	int joy;
	
	joy = To_S(RIGHT_X);
	
	if (joy < -80) {
		Set_Ramp_Speed(-127);
	}
	else if (joy > 80) {
		Set_Ramp_Speed(127);
	}
	else {
		Set_Ramp_Speed(0);
	}
}

int Get_Ramp_Pot(void)
{
	int pot;
	
	pot = Get_Analog_Value(RAMP_POT);
	if (ramp_pot_reverse)
		pot = 1023 - pot;
	
	return pot;
}
