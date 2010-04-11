
#include "ru_pickup.h"
#include "ru_shoulder.h"

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

static void Done();

// --------------------------------------------------------------

void Pickp_Meta_Init(void)
{
	pickup_state = LIFTING;
	pickup_done = 0;
}

void Pickp_Meta_Routine(void)
{
	switch (pickup_state) {
		case LIFTING:   Lifting_Routine();  break;
		case PAUSING:   Pausing_Routine();  break;
		case LOWERING:  Lowering_Routine(); break;
		case DONE: return;
	}
}

static void Done()
{
	pickup_state = DONE;
	pickup_done  = 1;
}

// --------------------------------------------------------------

static void Lifting_Init(void)
{
	pickup_state = LIFTING;
}

static void Lifting_Routine(void)
{
	
}

// --------------------------------------------------------------

static void Pausing_Init(void)
{
	pickup_state = PAUSING;
}

static void Pausing_Routine(void)
{
	
}

// --------------------------------------------------------------

static void Lowering_Init(void)
{
	pickup_state = LOWERING;
}

static void Lowering_Routine(void)
{
	
}
