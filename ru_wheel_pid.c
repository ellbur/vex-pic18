
#include "ru_wheel_pid.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_pid.h"
#include "ru_encoder.h"

#define KP (-0.084622)
#define KI (-0.11496)
#define KD (-0.0)

#define MAX_VEL (11.6)

static pid_t pid;

void Wheel_PID_Init(void)
{
	pid.K_P = KP;
	pid.K_I = KI;
	pid.K_D = KD;
	
	pid.MIN_OUTPUT = -1.0;
	pid.MAX_OUTPUT = +1.0;
	
	PID_Init(&pid);
}

void Wheel_PID_Routine(void)
{
	static int loop_count;
	
	float vel;
	float target;
	int stick;
	int output;
	int pwm;
	
	vel = Encoder_Calc_Spin_Timing(encoders+0) / 360.0 * 2*PI;
	
	stick = -To_S(PWM_in3);
	target = stick/127.0 * MAX_VEL;
	
	PID_Step(&pid, vel, target, SLOW_LOOP_PERIOD);
	
	output = (int) (pid.output * 127.0);
	pwm = Linearize_PWM(-output + (int)127);
	
	printf("%d,%d,%d,%d,%d,%d\n",
		(int) loop_count,
		(int) stick,
		(int) (target * 360.0/(2*PI)),
		(int) (vel    * 360.0/(2*PI)),
		(int) output,
		(int) pwm
	);
	
	pwm01 = pwm;
	loop_count++;
}
