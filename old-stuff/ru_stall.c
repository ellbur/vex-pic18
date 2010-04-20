
#include "ru_config.h"
#include "ru_stall.h"
#include "ru_hold.h"
#include "ru_misc.h"
#include "ru_encoder.h"

void Stall_Detect_Init(stall_detect_t *stall, int thresh)
{
	stall->delta_thresh = thresh;
	Hold_Init(&stall->hold, 5);
}

void Stall_Detect_Step(stall_detect_t *stall, int delta)
{
	Hold_Step(&stall->hold, int_abs(delta) < stall->delta_thresh);
}

char Stall_Detect_Trigger(stall_detect_t *stall)
{
	return Hold_Trigger(&stall->hold);
}

