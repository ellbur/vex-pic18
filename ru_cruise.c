
#include "ru_cruise.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_input.h"
#include "ru_drive.h"

#define cruise_fast_speed  ((int)127)
#define cruise_slow_speed   ((int)0)

#define dist_diff_thresh ((int)20) // inches * 10

void Cruise_Meta_Init(void)
{
	
}

void Cruise_Meta_Routine(void)
{
	int side_front_dist;
	int side_rear_dist;
	
	int dist_diff;
	
	side_front_dist = Get_Side_Front_IR();
	side_rear_dist  = Get_Side_Rear_IR();
	
	dist_diff = side_front_dist - side_rear_dist;
	
	if (dist_diff < -dist_diff_thresh) {
		// Turn left
		Set_Tank_Drive(cruise_slow_speed, cruise_fast_speed);
		printf("<<\n");
	}
	else if (dist_diff > +dist_diff_thresh) {
		// Turn right
		Set_Tank_Drive(cruise_fast_speed, cruise_slow_speed);
		printf(">>\n");
	}
	else {
		Set_Tank_Drive(cruise_fast_speed, cruise_fast_speed);
		printf("^^\n");
	}
	printf("%d .cmp. %d\n", dist_diff, dist_diff_thresh);
}

