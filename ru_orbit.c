
#include "ru_orbit.h"
#include "ru_cruise.h"
#include "ru_ir.h"
#include "ru_motor.h"

typedef enum {
	CRUISE,
	PICKUP,
	TURN_AROUND,
	SCORE,
	TURN_LEFT,
	TURN_RIGHT,
	DONE
} orbit_state_t;

static orbit_state_t orbit_state;

// Not to be confused with Cruise_Meta_*
static void Cruise_Init(void);
static void Cruise_Routine(void);

static void Pickup_Init(void);
static void Pickup_Routine(void);

static void Turn_Around_Init(void);
static void Turn_Around_Routine(void);

static void Score_Init(void);
static void Score_Routine(void);

static void Turn_Left_Init(void);
static void Turn_Left_Routine(void);

static void Turn_Right_Init(void);
static void Turn_Right_Routine(void);

static void Done(void);

// -----------------------------------------------------

void Orbit_Meta_Init(void)
{
	Cruise_Init();
}

void Orbit_Meta_Routine(void)
{
	switch (orbit_state) {
		case CRUISE:      Cruise_Routine();      break;
		case PICKUP:      Pickup_Routine();      break;
		case TURN_AROUND: Turn_Around_Routine(); break;
		case SCORE:       Score_Routine();       break;
		case TURN_LFFT:   Turn_Left_Routine();   break;
		case TURN_RIGHT:  Turn_Right_Routine();  break;
		case DONE: return;
	}
}

static void Done(void)
{
	orbit_state = DONE;
}

// -----------------------------------------------------

static void Cruise_Init(void)
{
	orbit_state = CRUISE;
}

static void Cruise_Routine(void)
{
	
}

// -----------------------------------------------------

static void Pickup_Init(void)
{
	orbit_state = PICKUP;
}

static void Pickup_Routine(void)
{
	
}

// -----------------------------------------------------

static void Turn_Around_Init(void)
{
	orbit_state = TURN_AROUND;
}

static void Turn_Around_Routine(void)
{
	
}

// -----------------------------------------------------

static void Score_Init(void)
{
	orbit_state = SCORE;
}

static void Score_Routine(void)
{
	
}

// -----------------------------------------------------

static void Turn_Left_Init(void)
{
	orbit_state = TURN_LEFT;
}

static void Turn_Left_Routine(void)
{
	
}

// -----------------------------------------------------

static void Turn_Right_Init(void)
{
	orbit_state = TURN_RIGHT;
}

static void Turn_Right_Routine(void)
{
	
}
