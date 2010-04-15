
#include "ru_cruise.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_input.h"
#include "ru_drive.h"
#include <math.h>

#define cruise_fast_speed  ((int)127)
#define cruise_slow_speed   ((int)0)

#define sensor_dist ((float)107.0) // inches * 10

#define target_dist ((float)100.0)

#define angle_p ((float)50.0/(30.0/180.0*PI))
#define dist_p  ((float)(10.0/180.0*PI)/(20.0))

void Cruise_Meta_Init(void)
{
	
}

void Cruise_Meta_Routine(void)
{
	float side_front_dist;
	float side_rear_dist;
	
	float angle;
	float dist;
	
	float left, right;
	float angle_effect;
	float target_angle;
	
	side_front_dist = Get_Side_Front_IR();
	side_rear_dist  = Get_Side_Rear_IR();
	
	angle = atan(
		(side_front_dist - side_rear_dist) / sensor_dist );
	dist = side_front_dist * cos(angle);
	
	target_angle = -dist_p * (dist - target_dist);
	angle_effect = -angle_p * (angle - target_angle);
	
	left  = 127.0 - angle_effect;
	right = 127.0 + angle_effect;
	
	Set_Auto_Tank_Drive(left, right);
	
	printf("%d %d : angle=%d dist=%d ; angle_effect=%d; "
		   "target_angle=%d, LEFT=%d, RIGHT=%d\n",
		(int) side_front_dist,
		(int) side_rear_dist,
		(int) (angle * 180.0 / PI),
		(int) dist,
		(int) angle_effect,
		(int) (target_angle*180.0/PI),
		(int) Get_Left_Sig(),
		(int) Get_Right_Sig());
}

