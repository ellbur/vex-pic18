
#ifndef _ru_stall_h
#define _ru_stall_h 1

#include "ru_hold.h"

typedef struct {
	int delta_thresh;
	hold_t hold;
} stall_detect_t;

void Stall_Detect_Init(stall_detect_t *stall, int delta_thresh);
void Stall_Detect_Step(stall_detect_t *stall, int delta);
char Stall_Detect_Trigger(stall_detect_t *stall);

#endif
