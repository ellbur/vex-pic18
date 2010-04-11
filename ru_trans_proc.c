
#include <math.h>
#include "ru_trans_proc.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_encoder.h"

#define output_pwm   pwm01
#define encoder_num  0

typedef enum {
	MOVING,
	RESTING,
	DONE
} trans_proc_state_t;

static trans_proc_state_t trans_proc_state;

// Starting phase
static float phi;
static int bunch_number;

static void Moving_Init(void);
static void Moving_Routine(void);

static void Resting_Init(void);
static void Resting_Routine(void);

static void Done(void);

void Trans_Proc_Init(void)
{
	trans_proc_state = RESTING;
	bunch_number = 0;
}

void Trans_Proc_Routine(void)
{
	switch (trans_proc_state) {
		case MOVING:  Moving_Routine();  return;
		case RESTING: Resting_Routine(); return;
		case DONE: return;
	}
	
	// Never get here
	printf("Oh no!!\n");
	Done();
}

static void Done(void)
{
	trans_proc_state = DONE;
}

// --------------------------------------------------------------------

#define moving_duration (10.0) // seconds

#define freq_start (0.1)
#define freq_stop  (3.5)

#define level_offset (80.0) // 127-scale
#define level_amp    (25.0) // 127-scale

static int moving_loop_count;

static float k;
static float t_offset;

static float omega_start;
static float omega_stop;

static float duration;

static void Moving_Init(void)
{
	trans_proc_state = MOVING;
	
	bunch_number = bunch_number + 1;
	moving_loop_count = 0;
	
	phi = fmod(bunch_number*PI*1.69 + encoders[0].count, 2*PI);
	
	omega_start = 2*PI * freq_start;
	omega_stop  = 2*PI * freq_stop;
	
	duration = moving_duration;
	
	k = (omega_stop - omega_start) / (2*duration);
	t_offset = omega_start / (2*k);
	
	printf("starting,%d,\n",
		(int) bunch_number,
		(int) (phi*180/PI) );
}

static void Moving_Routine(void)
{
	float time;
	float theta;
	float level;
	float vel;
	int pwm;
	
	time = moving_loop_count * SLOW_LOOP_PERIOD;
	if (time >= moving_duration) {
		Resting_Init();
		return;
	}
	
	theta = k*(time+t_offset)*(time+t_offset);
	level = level_offset + level_amp*cos(theta + phi);
	
	pwm = Linearize_PWM(-(int)level + 127);
	
	vel = Encoder_Calc_Spin_Timing(&encoders[encoder_num]);
	
	printf("moving,%d,%d,%d,%d,%d,%d\n",
		(int) bunch_number,
		(int) moving_loop_count,
		(int) (time * 100),
		(int) level,
		(int) pwm,
		(int) vel );
	
	output_pwm = pwm;
	
	moving_loop_count++;
}

// --------------------------------------------------------------------

#define resting_duration (10.0) // seconds, baby

static int resting_loop_count;

static void Resting_Init(void)
{
	trans_proc_state = RESTING;
	resting_loop_count = 0;
}

static void Resting_Routine(void)
{
	
	float time;
	
	time = resting_loop_count * SLOW_LOOP_PERIOD;
	if (time >= resting_duration) {
		Moving_Init();
		return;
	}
	
	output_pwm = 127;
	
	resting_loop_count++;
}
