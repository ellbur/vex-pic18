
#ifndef _ru_drive_pid_h
#define _ru_drive_pid_h 1

#include "ru_pid.h"

#define NUM_DRIVE_PIDS 2
#define MAX_SPEED 10.0 // rad/s

typedef struct {
	
	pid_t pid;
	
	int output_u_pwm;
	int output_s_pwm;
	
} drive_pid_t;

extern drive_pid_t drive_pids[NUM_DRIVE_PIDS];

void Drive_PIDs_Init(void);
void Drive_PID_Init(drive_pid_t *drive);

void Drive_PID_Step(drive_pid_t *drive, float vel, float target);

void Drive_PID_Routine(float left_target, float right_target);

#endif
