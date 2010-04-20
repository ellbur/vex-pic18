
#include "ru_straight.h"
#include "ru_config.h"
#include "ru_drive.h"
#include "ru_encoder.h"

typedef enum {
	FORWARD,
	DONE
} straight_state_t;

static straight_state_t straight_state;
char straight_done;

static int speed;
static float target_dist;
static float timeout;

static void Forward_Init(void);
static void Forward_Routine(void);

static void Done(void);

void Straight_Meta_Init(
	int _speed,
	float _target_dist,
	float _timeout)
{
	speed        = _speed;
	target_dist  = _target_dist;
	timeout      = _timeout;
	
	straight_done = 0;
	Forward_Init();
}

void Straight_Meta_Routine(void)
{
	switch (straight_state) {
		case FORWARD: Forward_Routine(); break;
		case DONE: return;
	}
}

// ------------------------------------------------

static void Done(void)
{
	straight_state = DONE;
	straight_done = 1;
}

// ------------------------------------------------

#define stall_wait    ((float)0.50)

static float starting_dist;
static int forward_loop_count;

static void Forward_Init(void)
{
	straight_state = FORWARD;
	
	starting_dist = Encoder_Get_Distance();
	forward_loop_count = 0;
}

static void Forward_Routine(void)
{
	float dist;
	float time;
	
	printf("forward\n");
	
	time = forward_loop_count * SLOW_LOOP_PERIOD;
	if (timeout > 0.0 && time >= timeout) {
		printf("timeout\n");
		Done();
		return;
	}
	
	dist = Encoder_Get_Distance();
	
	if (target_dist > 0 && dist - starting_dist >= target_dist) {
		printf("disf forward\n");
		Done();
		return;
	}
	
	if (target_dist < 0 && dist - starting_dist <= target_dist) {
		printf("dist reverse\n");
		Done();
		return;
	}
	
	Set_Auto_Tank_Drive(speed, speed);
	
	forward_loop_count++;
}
