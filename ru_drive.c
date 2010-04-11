
#include "ru_drive.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_drive_pid.h"

void Set_Left_Speed(int spwm)
{
#if kevin
	LEFT_WHEEL = Normalize_PWM(To_U(Flip(spwm)));
#elif nitish
	LEFT_WHEEL_1 = Normalize_PWM(To_U(Flip(spwm)));
	LEFT_WHEEL_2 = Normalize_PWM(To_U(Flip(spwm)));
#endif
}

void Set_Right_Speed(int spwm)
{
#if kevin
	RIGHT_WHEEL = Normalize_PWM(To_U(spwm));
#elif nitish
	RIGHT_WHEEL_1 = Normalize_PWM(To_U(spwm));
	RIGHT_WHEEL_2 = Normalize_PWM(To_U(spwm));
#endif
}

void Set_Tank_Drive(int sleft, int sright)
{
	Set_Left_Speed(sleft);
	Set_Right_Speed(sright);
}

void Manual_Tank_Drive_Routine(void)
{
	Set_Left_Speed(Flip(To_S(LEFT_JOY)));
	Set_Right_Speed(Flip(To_S(RIGHT_JOY)));
}

void Manual_Tank_PID_Drive_Routine(void)
{
	float left_target;
	float right_target;
	
	left_target  = Flip(To_S(LEFT_JOY))  / 127.0 * MAX_SPEED;
	right_target = Flip(To_S(RIGHT_JOY)) / 127.0 * MAX_SPEED;
	
	Drive_PID_Routine(left_target, right_target);
}
