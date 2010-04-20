
#include "ru_encoder.h"
#include "ru_config.h"

float Encoder_Get_Angle(void)
{
	float d1, d2;
	
	d1 = Get_Left_Encoder_Count()  * LEFT_ENCODER_GEAR_RATIO;
	d2 = Get_Right_Encoder_Count() * RIGHT_ENCODER_GEAR_RATIO;
	
	return (d2 - d1) / 2.0 / TICKS_PER_ROBOT_RADIAN;
}

float Encoder_Get_Distance(void)
{
	float d1, d2;
	
	d1 = Get_Left_Encoder_Count()  * LEFT_ENCODER_GEAR_RATIO;
	d2 = Get_Right_Encoder_Count() * RIGHT_ENCODER_GEAR_RATIO;
	
	return (d1 + d2) / 2.0 / TICKS_PER_METER;
}
