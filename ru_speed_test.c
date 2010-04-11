
#include "ru_speed_test.h"
#include "ru_config.h"
#include "ru_encoder.h"
#include "ru_motor.h"

void Speed_Test_Init(void)
{
	
}

#define SPEEDUP_WAIT ((int)20)
#define MEASURE_WAIT ((int)50)

void Speed_Test_Routine(void)
{
	static long encoder_count_at_b;
	static int loop_count;
	static int loop_count_at_a = 0;
	static int level = 127;
	static char ascending = 1;
	static char done = 0;
	
	long encoder_count_at_c;
	float speed;
	int encoder_delta;
	
	if (done) {
		return;
	}
	
	if (PWM_in6 < 100) {
		level             = 127;
		ascending       = 1;
		done            = 0;
		loop_count      = 0;
		loop_count_at_a = 0;
		
		printf("starting\n");
	}
	
	if (loop_count == loop_count_at_a + SPEEDUP_WAIT) {
		encoder_count_at_b = encoders[0].count;
	}
	
	if (loop_count == loop_count_at_a + SPEEDUP_WAIT + MEASURE_WAIT) {
		encoder_count_at_c = encoders[0].count;
		encoder_delta = (int) (encoder_count_at_c - encoder_count_at_b);
		speed = encoder_delta / ((float) MEASURE_WAIT * SLOW_LOOP_PERIOD);
		
		printf("measure,%d,%d,%d,%d,%d\n",
			(int) loop_count,
			(int) level,
			(int) Linearize_PWM(level),
			(int) encoder_delta,
			(int) speed );
		
		if (ascending) {
			if (level >= 255) {
				ascending = 0;
				level = 127;
			}
			else {
				level++;
			}
		}
		else {
			if (level <= 0) {
				done = 1;
			}
			else {
				level--;
			}
		}
		
		loop_count_at_a = loop_count;
	}
	
	speed = Encoder_Calc_Spin_Timing(encoders+0);
	
	pwm01 = Linearize_PWM(level);
	
	loop_count++;
}
