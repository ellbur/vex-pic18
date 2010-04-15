
#include "ru_score.h"
#include "ru_drive.h"
#include "ru_bumper.h"
#include "ru_ramp.h"

typedef enum {
	BACKING_UP,
	LIFTING,
	PAUSING,
	LOWERING,
	DONE
} score_state_t;

static score_state_t score_state;
char score_done;

// ----------------------------------------------------------

static void Backing_Up_Init(void);
static void Backing_Up_Routine(void);

static void Lifting_Init(void);
static void Lifting_Routine(void);

static void Pausing_Init(void);
static void Pausing_Routine(void);

static void Lowering_Init(void);
static void Lowering_Routine(void);

static void Done(void);

// ----------------------------------------------------------

void Score_Meta_Init(void)
{
	Backing_Up_Init();
	score_done  = 0;
}

void Score_Meta_Routine(void)
{
	switch (score_state) {
		case BACKING_UP: Backing_Up_Routine(); break;
		case LIFTING:    Lifting_Routine();    break;
		case PAUSING:    Pausing_Routine();    break;
		case LOWERING:   Lowering_Routine();   break;
		case DONE: return;
	}
}

static void Done(void)
{
	score_state = DONE;
	score_done  = 1;
}

// ----------------------------------------------------------

#define backing_up_timeout ((float)3.0)

static int backing_up_loop_count;

static void Backing_Up_Init(void)
{
	score_state = BACKING_UP;
	backing_up_loop_count = 0;
}

static void Backing_Up_Routine(void)
{
	float time;
	char bumper;
	
	time = backing_up_loop_count * SLOW_LOOP_PERIOD;
	if (time >= backing_up_timeout) {
		Lifting_Init();
		return;
	}
	
	bumper = Get_Bumper();
	if (bumper) {
		Lifting_Init();
		return;
	}
	
	backing_up_loop_count++;
}

// ----------------------------------------------------------

// get ramp_lifting_pot_thresh from ru_ramp.h
#define lifting_timeout     ((float)2.0)
#define lifting_ramp_speed  ((int)127)

static int lifting_loop_count;

static void Lifting_Init(void)
{
	score_state = LIFTING;
	lifting_loop_count = 0;
}

static void Lifting_Routine(void)
{
	float time;
	int pot;
	
	time = lifting_loop_count * SLOW_LOOP_PERIOD;
	if (time >= lifting_timeout) {
		Done();
		return;
	}
	
	pot = Get_Ramp_Pot();
	if (pot >= ramp_lifting_pot_thresh) {
		Pausing_Init();
		return;
	}
	
	Set_Ramp_Speed(lifting_ramp_speed);
	
	lifting_loop_count++;
}

// ----------------------------------------------------------

#define pausing_timeout ((float)1.0)

static int pausing_loop_count;

static void Pausing_Init(void)
{
	score_state = PAUSING;
	pausing_loop_count = 0;
}

static void Pausing_Routine(void)
{
	float time;
	
	time = pausing_loop_count * SLOW_LOOP_PERIOD;
	if (time >= pausing_timeout) {
		Lowering_Init();
		return;
	}
	
	pausing_loop_count++;
}

// ----------------------------------------------------------

// get ramp_lowering_pot_thresh from ru_ramp.h

#define lowering_timeout ((float)2.0)
#define lowering_ramp_speed ((int)-127)

static int lowering_loop_count;

static void Lowering_Init(void)
{
	score_state = LOWERING;
}

static void Lowering_Routine(void)
{
	float time;
	int pot;
	
	time = lowering_loop_count * SLOW_LOOP_PERIOD;
	if (time >= lowering_timeout) {
		Done();
		return;
	}
	
	pot = Get_Ramp_Pot();
	if (pot <= ramp_lowering_pot_thresh) {
		Done();
		return;
	}
	
	Set_Ramp_Speed(lowering_ramp_speed);
	
	lowering_loop_count++;
}

