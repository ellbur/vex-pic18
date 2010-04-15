
#ifndef _ru_hold_h
#define _ru_hold_h 1

typedef struct {
	int loop_thresh;
	int counter;
} hold_t;

void Hold_Init(hold_t *hold, int loop_thresh);
void Hold_Step(hold_t *hold, char active);
char Hold_Trigger(hold_t *hold);

#endif
