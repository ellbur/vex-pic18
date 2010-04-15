
#include "ru_config.h"
#include "ru_pickup.h"
#include "ru_shoulder.h"
#include "ru_drive.h"

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

// Get shoulder_lifting_pot_thresh from ru_shoulder.h
#define lifting_timeout    ((float)2.0) // seconds
#define lifting_speed      ((int)127)

static int lifting_loop_count;

static void Lifting_Init(void)
{
	pickup_state = LIFTING;
	
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
	
	pot = Get_Shoulder_Pot();
	
	// Note the sign. Get_Shoulder_Pot() does the flip.
	if (pot >= shoulder_lifting_pot_thresh) {
		Pausing_Init();
		return;
	}
	
	Set_Shoulder_Speed(lifting_speed);
	
	lifting_loop_count++;
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

// Get shoulder_lowering_pot_thresh from ru_shoulder.h
#define lowering_timeout ((float)1.0)

static int lowering_loop_count;

static void Lowering_Init(void)
{
	pickup_state = LOWERING;
	
	lowering_loop_count = 0;
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
	
	pot = Get_Shoulder_Pot();
	if (pot <= shoulder_lowering_pot_thresh) {
		Done();
		return;
	}
}
