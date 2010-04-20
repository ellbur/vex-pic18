
#include <math.h>
#include "ru_vel_noise.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_encoder.h"

#define omega_start (0.1 * 2*PI)
#define omega_stop  (3.5 * 2*PI)
#define duration    (20.0) // seconds

#define level_offset 80.0
#define level_amp    25.0

static int loop;
static float k;
static float t_offset;
static float phi;

void Vel_Noise_Init(void)
{
	k = (omega_stop - omega_start) / (2*duration);
	t_offset = omega_start / (2*k);
	phi = 1.5024;
	
	loop = 0;
}

void Vel_Noise_Routine(void)
{
	
	float t;
	float theta;
	float level;
	int pwm;
	
	t = loop * SLOW_LOOP_PERIOD + t_offset;
	
	if (t >= duration+t_offset) {
		pwm01 = 127;
		return;
	}
	
	theta = k*t*t + phi;
	level = level_amp*cos(theta) + level_offset;
	
	pwm = Linearize_PWM((int)level + 127);
	
	printf("%d,%d,%d,%d,%d\n",
		(int) loop,
		(int) (t * 100),
		(int) level,
		(int) pwm,
		(int) Encoder_Calc_Spin_Timing(encoders+0) );
	
	pwm01 = pwm;
	loop++;
}
