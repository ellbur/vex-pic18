
#include "ru_cruise.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_drive.h"
#include "ru_ir.h"
#include <math.h>

#define cruise_fast_speed  ((int)127)
#define cruise_slow_speed   ((int)0)

#define sensor_dist ((float)107.0) // inches * 10

#define angle_p ((float)50.0/(30.0/180.0*PI))
#define dist_p  ((float)(10.0/180.0*PI)/(20.0))

#define min_target_angle (-PI/4.0)
#define max_target_angle (+PI/4.0)

static float target_dist;

void Cruise_Meta_Init(float _target_dist)
{
	// meters -> in*10
	target_dist = _target_dist * 393.7;
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
	if (target_angle < min_target_angle) {
		target_angle = min_target_angle;
	}
	if (target_angle > max_target_angle) {
		target_angle = max_target_angle;
	}
	
	angle_effect = -angle_p * (angle - target_angle);
	
	left  = 127.0 - angle_effect;
	right = 127.0 + angle_effect;
	
	Set_Auto_Tank_Drive(left, right);
}

