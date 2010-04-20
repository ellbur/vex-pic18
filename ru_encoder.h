
#ifndef _ru_encoder_h
#define _ru_encoder_h 1

#define LEFT_ENCODER_GEAR_RATIO   ((float)0.25)
#define RIGHT_ENCODER_GEAR_RATIO  ((float)0.25)

#define TICKS_PER_METER  ((float) 1088.6) // Wrong. Needs to be measured.
#define TICKS_PER_ROBOT_RADIAN ((float) 150.0) // Wrong. Needs to be measured.

float Encoder_Get_Angle(void);
float Encoder_Get_Distance(void);

#endif
