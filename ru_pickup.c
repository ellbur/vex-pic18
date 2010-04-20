
#include "ru_config.h"
#include "ru_pickup.h"
#include "ru_shoulder.h"
#include "ru_drive.h"
#include "ru_move_arm.h"

typedef enum {
	LIFTING,
	PAUSING,
	LOWERING,
	DONE
} pickup_state_t;

static pickup_state_t pickup_state;
char pickup_done;

static void Lifting_Init(void);
static void Lifting_Routine(void);

static void Pausing_Init(void);
static void Pausing_Routine(void);

static void Lowering_Init(void);
static void Lowering_Routine(void);

static void Done(void);

// --------------------------------------------------------------

void Pickup_Meta_Init(void)
{
	Lifting_Init();
	pickup_done = 0;
}

void Pickup_Meta_Routine(void)
{
	switch (pickup_state) {
		case LIFTING:   Lifting_Routine();  break;
		case PAUSING:   Pausing_Routine();  break;
		case LOWERING:  Lowering_Routine(); break;
		case DONE: return;
	}
}

static void Done(void)
{
	pickup_state = DONE;
	pickup_done  = 1;
}

// --------------------------------------------------------------

static void Lifting_Init(void)
{
	pickup_state = LIFTING;
	
	Move_Arm_Meta_Init(shoulder_pickup_pot_thresh, UP);
}

static void Lifting_Routine(void)
{
	if (move_arm_done) {
		Pausing_Init();
		return;
	}
	
	Move_Arm_Meta_Routine();
}

// --------------------------------------------------------------

#define pausing_timeout ((float)0.30) // seconds

static int pausing_counter;

static void Pausing_Init(void)
{
	pickup_state = PAUSING;
	pausing_counter = 0;
}

static void Pausing_Routine(void)
{
	float time;
	
	time = pausing_counter * SLOW_LOOP_PERIOD;
	if (time >= pausing_timeout) {
		Lowering_Init();
		return;
	}
	
	pausing_counter++;
}

// --------------------------------------------------------------

static void Lowering_Init(void)
{
	pickup_state = LOWERING;
	
	Move_Arm_Meta_Init(shoulder_lowering_pot_thresh, DOWN);
}

static void Lowering_Routine(void)
{
	if (move_arm_done) {
		Done();
		return;
	}
	
	Move_Arm_Meta_Routine();
}
