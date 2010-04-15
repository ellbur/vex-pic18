
#include "ru_drive.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_drive_pid.h"
#include "ru_accel.h"
#include <math.h>

accel_t left_accel;
accel_t right_accel;

void Drive_Init(void)
{
	Accel_Init(&left_accel,  10);
	Accel_Init(&right_accel, 10);
}

void Set_Left_Raw(int upwm)
{
#if kevin
	LEFT_WHEEL = Normalize_PWM(upwm);
#elif nitish
	LEFT_WHEEL_1 = Normalize_PWM(upwm);
	LEFT_WHEEL_2 = Normalize_PWM(upwm);
#endif
}

void Set_Right_Raw(int upwm)
{
#if kevin
	RIGHT_WHEEL = Normalize_PWM(upwm);
#elif nitish
	RIGHT_WHEEL_1 = Normalize_PWM(upwm);
	RIGHT_WHEEL_2 = Normalize_PWM(upwm);
#endif
}

void Set_Left_Sig(int spwm)
{
	Set_Left_Raw(To_U(Flip(spwm)));
	Accel_Clear(&left_accel);
}

void Set_Right_Sig(int spwm)
{
	Set_Right_Raw(To_U(spwm));
	Accel_Clear(&right_accel);
}

int Get_Left_Sig(void)
{
#if kevin
	return Flip(To_S(LEFT_WHEEL));
#elif nitish
	return Flip(To_S(LEFT_WHEEL_1);
#endif
}

int Get_Right_Sig(void)
{
#if kevin
	return To_S(RIGHT_WHEEL);
#elif nitish
	return To_S(RIGHT_WHEEL_1);
#endif
}

void Set_Left_Linear(int speed)
{
	int sig;
	
	speed = Flip(speed);
	sig = Linearize_PWM(speed);
	
	Set_Left_Raw(sig);
	Accel_Clear(&left_accel);
}

void Set_Right_Linear(int speed)
{
	int sig;
	
	sig = Linearize_PWM(speed);
	
	Set_Right_Raw(sig);
	Accel_Clear(&right_accel);
}

void Set_Left_Damped(int speed)
{
	int sig;
	int accel_speed;
	
	Accel_Step(&left_accel, speed);
	accel_speed = Flip(Accel_Get_Output(&left_accel));
	
	sig = Linearize_PWM(accel_speed);
	Set_Left_Raw(sig);
}

void Set_Right_Damped(int speed)
{
	int sig;
	int accel_speed;
	
	Accel_Step(&right_accel, speed);
	accel_speed = Accel_Get_Output(&right_accel);
	
	sig = Linearize_PWM(accel_speed);
	Set_Right_Raw(sig);
}

void Set_Auto_Tank_Drive(float left, float right)
{
	float max;
	
	max = 127.0;
	if (fabs(left)  > max) max = fabs(left);
	if (fabs(right) > max) max = fabs(right);
	
	left  = left  * 127.0 / max;
	right = right * 127.0 / max;
	
	Set_Left_Damped((int) left);
	Set_Right_Damped((int) right);
}

void Set_Tele_Tank_Drive(float left, float right)
{
	Set_Left_Sig((int) left);
	Set_Right_Sig((int) right);
}

void Manual_Tank_Drive_Routine(void)
{
	Set_Tele_Tank_Drive(
		Flip(To_S(LEFT_JOY)),
		Flip(To_S(RIGHT_JOY)) );
}
