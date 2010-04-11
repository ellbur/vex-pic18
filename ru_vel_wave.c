
#include <math.h>
#include "ru_vel_wave.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_encoder.h"

void Vel_Wave_Init(void)
{
	
}

void Vel_Wave_Routine(void)
{
#define omega_start ( 1.6 * 2*PI)
#define omega_stop  (10.5 * 2*PI)
#define omega_step  ( 2.0 * 2*PI)
	
	static float sig_offset = 80.0;
	static float amp   = 25.0;
	static float omega = omega_start;
	static float phi   = 0.0;
	static long loop_count = 0;
	static char index = 0;
	static char done = 0;
	
	float t;
	float theta;
	int sig;
	int pwm;
	
	if (done) {
		return;
	}
	
	t = loop_count * SLOW_LOOP_PERIOD;
	theta = omega*t + phi;
	sig = (int)( amp*sin(omega*t + phi) + sig_offset );
	pwm = Linearize_PWM(sig + 127);
	
	printf("%d,%d,%d,%d,%d,%d\n",
		(int) loop_count,
		(int) ( (omega/(2*PI)) * 100 ),
		(int) (omega * 100),
		(int) sig,
		(int) pwm,
		(int) Encoder_Calc_Spin_Timing(encoders+0) );
	
	if (theta >= 2*PI*6) {
		omega += omega_step;
		loop_count = 0;
		
		if (omega >= omega_stop) {
			done = 1;
		}
	}
	
	pwm01 = pwm;
	
	loop_count++;
}
