
#ifndef _ru_cruise_h
#define _ru_cruise_h 1

extern int cruise_target_dist;

// Target in meters
void Cruise_Meta_Init(float target_dist);
void Cruise_Meta_Routine(void);

#endif
