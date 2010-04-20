
#ifndef _ru_straight_h
#define _ru_straight_h 1

extern char straight_done;

void Straight_Meta_Init(
	int speed,
	float target_dist,  // meters  ; 0.0 for no dist
	float timeout       // seconds ; 0.0 for no timeout
);
void Straight_Meta_Routine(void);

#endif
