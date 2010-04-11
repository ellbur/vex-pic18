
#include "ru_ramp.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_sample.h"

void Set_Ramp_Speed(int spwm)
{
#if kevin
	RAMP = Normalize_PWM(To_U(spwm));
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
