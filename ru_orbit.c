
#include "ru_orbit.h"
#include "ru_cruise.h"
#include "ru_ir.h"
#include "ru_motor.h"
#include "ru_hold.h"
#include "ru_pickup.h"
#include "ru_turn.h"
#include "ru_score.h"

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

#define BACK_WALL   ((int)0)
#define RIGHT_WALL  ((int)1)
#define FRONT_WALL  ((int)2)
#define LEFT_WALL   ((int)3)
static int wall;

// Not to be confused with Cruise_Meta_*
static void Cruise_Init(void);
static void Cruise_Routine(void);

static void Pickup_Init(void);
static void Pickup_Routine(void);
static void Decide_Wall(void);

static void Turn_Around_Init(void);
static void Turn_Around_Routine(void);

static void Score_Init(void);
static void Score_Routine(void);

static void Turn_Left_Init(void);
static void Turn_Left_Routine(void);

static void Turn_Right_Init(void);
static void Turn_Right_Routine(void);

// -----------------------------------------------------

void Orbit_Meta_Init(void)
{
	Cruise_Init();
}

void Orbit_Meta_Routine(void)
{
	switch (orbit_state) {
		case CRUISE:      Cruise_Routine();      printf("cruise\n");      break;
		case PICKUP:      Pickup_Routine();      printf("pickup\n");      break;
		case TURN_AROUND: Turn_Around_Routine(); printf("turn around\n"); break;
		case SCORE:       Score_Routine();       printf("score\n");       break;
		case TURN_LEFT:   Turn_Left_Routine();   printf("turn left\n");   break;
		case TURN_RIGHT:  Turn_Right_Routine();  printf("turn right\n");  break;
		case DONE: return;
	}
}

// -----------------------------------------------------

#define front_dist_thresh ((float)18.0)
#define front_dist_time   ((int)5) // loops

hold_t dist_trigger;

static void Cruise_Init(void)
{
	orbit_state = CRUISE;
	
	Cruise_Meta_Init();
	Hold_Init(&dist_trigger, front_dist_time);
}

static void Cruise_Routine(void)
{
	float front_dist;
	
	front_dist = Get_Front_IR_In();
	Hold_Step(&dist_trigger, front_dist > front_dist_thresh);
	
	printf("front = %d (%d)\n",
		(int) front_dist,
		(int) dist_trigger.counter);
	
	if (Hold_Trigger(&dist_trigger)) {
		Pickup_Init();
		return;
	}
	
	Cruise_Meta_Routine();
}

// -----------------------------------------------------

static void Pickup_Init(void)
{
	orbit_state = PICKUP;
	
	Pickup_Meta_Init();
}

static void Pickup_Routine(void)
{
	if (pickup_done) {
		Decide_Wall();
		return;
	}
	
	Pickup_Meta_Routine();
}

static void Decide_Wall(void)
{
	if (wall == FRONT_WALL) {
		Turn_Around_Init();
	}
	else {
		Turn_Left_Init();
	}
}

// -----------------------------------------------------

static void Turn_Around_Init(void)
{
	orbit_state = TURN_AROUND;
	
	Turn_Meta_Init(PI);
}

static void Turn_Around_Routine(void)
{
	if (turn_done) {
		Score_Init();
		return;
	}
	
	Turn_Meta_Routine();
}

// -----------------------------------------------------

static void Score_Init(void)
{
	orbit_state = SCORE;
	
	Score_Meta_Init();
}

static void Score_Routine(void)
{
	if (score_done) {
		Turn_Right_Init();
		return;
	}
	
	Score_Meta_Routine();
}

// -----------------------------------------------------

static void Turn_Left_Init(void)
{
	orbit_state = TURN_LEFT;
	
	Turn_Meta_Init(PI/2.0);
}

static void Turn_Left_Routine(void)
{
	if (turn_done) {
		wall = (wall + 1) % 4;
		Cruise_Init();
	}
	
	Turn_Meta_Routine();
}

// -----------------------------------------------------

static void Turn_Right_Init(void)
{
	orbit_state = TURN_RIGHT;
	
	Turn_Meta_Init(-PI/2.0);
}

static void Turn_Right_Routine(void)
{
	if (turn_done) {
		wall = (wall + 1) % 4;
		Cruise_Init();
	}
	
	Turn_Meta_Routine();
}
