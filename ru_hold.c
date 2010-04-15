
#include "ru_hold.h"

void Hold_Init(hold_t *hold, int loop_thresh)
{
	hold->loop_thresh = loop_thresh;
	hold->counter = 0;
}

void Hold_Step(hold_t *hold, char active)
{
	if (active) {
		hold->counter++;
	}
	else hold->counter = 0;
}

char Hold_Trigger(hold_t *hold)
{
	return hold->counter >= hold->loop_thresh;
}
