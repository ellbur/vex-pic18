
#include "ru_drive_pid.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_encoder.h"
#include "ru_drive.h"

drive_pid_t drive_pids[NUM_DRIVE_PIDS] = {
	
	{
		-0.084622,    // K_P
		-0.11496,    // K_I
		0.0,    // K_D
		
		-1.0,   // min out
		+1.0    // max out
	},
	{
		-0.084622,    // K_P
		-0.11496,    // K_I
		0.0,    // K_D
		
		-1.0,   // min out
		+1.0    // max out
	}
};

void Drive_PIDs_Init(void)
{
	char i;
	float ST, FS, r, m, KP, KI;
	
	ST = 0.7344;
	FS = 100. * 2. * 3.14159 / 60.;
	m  = 20 / 2.2;
	r  = 2.0 * 2.54 / 100.;
	
	KP = -3.0;
	KI = -r*ST*(1/FS - r*KP)*(1/FS - r*KP) / (4 * m);
	
	for (i=0; i<NUM_DRIVE_PIDS; i++) {
		Drive_PID_Init(&drive_pids[i]);
		
		drive_pids[i].pid.K_P = KP;
		drive_pids[i].pid.K_I = KI;
		drive_pids[i].pid.K_D = 0.0;
	}
}

void Drive_PID_Init(drive_pid_t *drive)
{
	PID_Init(&drive->pid);
}

void Drive_PID_Step(drive_pid_t *drive, float vel, float target)
{
	PID_Step(&drive->pid, vel, target, SLOW_LOOP_PERIOD);
	
	drive->output_s_pwm = (int) (drive->pid.output * 127.0);
	drive->output_u_pwm = To_U(drive->output_s_pwm);
}

void Drive_PID_Routine(float left_target, float right_target)
{
	Drive_PID_Step(&drive_pids[0],
		Encoder_Calc_Spin_Timing(&encoders[0]) / 360.0 * 2*PI,
		left_target);
	
	Drive_PID_Step(&drive_pids[1],
		Encoder_Calc_Spin_Timing(&encoders[1]) / 360.0 * 2*PI,
		right_target);
	
	Set_Tele_Tank_Drive(
		drive_pids[0].output_s_pwm,
		drive_pids[1].output_s_pwm);
}
