
#include "ru_io.h"

#include "ru_config_pic.h"
#include "ru_encoder_pic.h"

#include "ru_motor.h"

char Is_Autonomous(void)
{
	return rxdata.rc_receiver_status_byte.allbits != 0;
}

int Get_Trigger_Button(void)
{
	return To_S(TRIGGER_BUTTON) > 10;
}

int Get_Left_Joystick(void)
{
	return Flip(To_S(LEFT_JOY));
}

int Get_Right_Joystick(void)
{
	return Flip(To_S(RIGHT_JOY));
}

// +1, 0, -1
int Get_Ramp_Button(void)
{
	char button;
	
	button = To_S(RAMP_BUTTON);
	if      (button < -10) return -1;
	else if (button > +10) return +1;
	
	return 0;
}

int Get_Shoulder_Button(void)
{
	char button;
	
	button = To_S(SHOULDER_BUTTON);
	if      (button < -10) return -1;
	else if (button > +10) return +1;
	
	return 0;
}

int Get_Analog(int number)
{
	switch (number) {
		case  1: return Get_Analog_Value(rc_ana_in01); break;
		case  2: return Get_Analog_Value(rc_ana_in02); break;
		case  3: return Get_Analog_Value(rc_ana_in03); break;
		case  4: return Get_Analog_Value(rc_ana_in04); break;
		case  5: return Get_Analog_Value(rc_ana_in05); break;
		case  6: return Get_Analog_Value(rc_ana_in06); break;
		case  7: return Get_Analog_Value(rc_ana_in07); break;
		case  8: return Get_Analog_Value(rc_ana_in08); break;
		case  9: return Get_Analog_Value(rc_ana_in09); break;
		case 10: return Get_Analog_Value(rc_ana_in10); break;
		case 11: return Get_Analog_Value(rc_ana_in11); break;
		case 12: return Get_Analog_Value(rc_ana_in12); break;
		case 13: return Get_Analog_Value(rc_ana_in13); break;
		case 14: return Get_Analog_Value(rc_ana_in14); break;
		case 15: return Get_Analog_Value(rc_ana_in15); break;
		case 16: return Get_Analog_Value(rc_ana_in16); break;
	}
	
	return 0;
}

unsigned char Read_Interrupt_Digital(char num)
{
	switch (num) {
		case  1:  return rc_dig_int1;
		case  2:  return rc_dig_int2;
		case  3:  return rc_dig_int3;
		case  4:  return rc_dig_int4;
		case  5:  return rc_dig_int5;
		case  6:  return rc_dig_int6;
	}
	
	return -5;
}

long Get_Left_Encoder_Count(void)
{
	return Encoder_Get_Count(&encoders[0]);
}

long Get_Right_Encoder_Count(void)
{
	return Encoder_Get_Count(&encoders[1]);
}

// ------------------------------------------------------------------

void Set_Ramp_Speed(int spwm)
{
#if kevin
	RAMP_1 = Normalize_PWM(To_U(Flip(spwm)));
	RAMP_2 = Normalize_PWM(To_U(spwm));
#elif nitish
	LEFT_SCISSOR  = Normalize_PWM(To_U(Flip(spwm)));
	RIGHT_SCISSOR = Normalize_PWM(To_U(spwm));
#endif
}

void Set_Shoulder_Speed(int spwm)
{
	LEFT_SHOULDER_1  = Normalize_PWM(To_U(spwm));
	RIGHT_SHOULDER_1 = Normalize_PWM(To_U(Flip(spwm)));
	
	LEFT_SHOULDER_2  = LEFT_SHOULDER_1;
	RIGHT_SHOULDER_2 = RIGHT_SHOULDER_1;
}

void Set_Left_Wheel_Speed(int spwm)
{
	int upwm;
	
	upwm = To_U(spwm);
	
#if kevin
	LEFT_WHEEL = Normalize_PWM(upwm);
#elif nitish
	LEFT_WHEEL_1 = Normalize_PWM(upwm);
	LEFT_WHEEL_2 = Normalize_PWM(upwm);
#endif
}

void Set_Right_Wheel_Speed(int spwm)
{
	int upwm;
	
	upwm = To_U(spwm);
	
#if kevin
	RIGHT_WHEEL = Normalize_PWM(upwm);
#elif nitish
	RIGHT_WHEEL_1 = Normalize_PWM(upwm);
	RIGHT_WHEEL_2 = Normalize_PWM(upwm);
#endif
}

