
#include "ru_accel.h"

void Accel_Init(accel_t *accel, int max_jump)
{
	accel->max_jump = max_jump;
	accel->actual = 0;
	accel->used = 0;
}

void Accel_Step(accel_t *accel, int target)
{
	if (! accel->used) {
		accel->used = 1;
		accel->actual = accel->target = target;
		
		return;
	}
	
	accel->target = target;
	if (accel->actual + accel->max_jump < accel->target) {
		accel->actual += accel->max_jump;
	}
	else if (accel->actual - accel->max_jump > accel->target) {
		accel->actual -= accel->max_jump;
	}
	else {
		accel->actual = accel->target;
	}
}

void Accel_Clear(accel_t *accel)
{
	accel->used = 0;
}

int Accel_Get_Output(accel_t *accel)
{
	return accel->actual;
}
