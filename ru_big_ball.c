
#include "ru_big_ball.h"
#include "ru_config.h"
#include "ru_hold.h"
#include "ru_pickup.h"
#include "ru_straight.h"
#include "ru_ir.h"
#include "ru_to_wall.h"

typedef enum {
	TO_WALL,
	FORWARD,
	REVERSE,
	PICKUP,
	DONE
} big_ball_state_t;

static big_ball_state_t big_ball_state;
char big_ball_done;

static void To_Wall_Init(void);
static void To_Wall_Routine(void);

static void Forward_Init(void);
static void Forward_Routine(void);

static void Reverse_Init(void);
static void Reverse_Routine(void);

static void Pickup_Init(void);
static void Pickup_Routine(void);

static void Done(void);

void Big_Ball_Meta_Init(void)
{
	big_ball_done = 0;
	To_Wall_Init();
}

void Big_Ball_Meta_Routine(void)
{
	switch (big_ball_state) {
		case TO_WALL: To_Wall_Routine(); break;
		case FORWARD: Forward_Routine(); break;
		case REVERSE: Reverse_Routine(); break;
		case PICKUP:  Pickup_Routine();  break;
		case DONE: return;
	}
}

static void Done(void)
{
	big_ball_state = DONE;
	big_ball_done = 1;
}

// ------------------------------------------------------------

static void To_Wall_Init(void)
{
	big_ball_state = TO_WALL;
	
	To_Wall_Meta_Init();
}

static void To_Wall_Routine(void)
{
	if (to_wall_done) {
		Forward_Init();
		return;
	}
	
	To_Wall_Meta_Routine();
}

// ------------------------------------------------------------

#define dist_thresh ((float)12.0) // inches

static hold_t dist_trigger;

static void Forward_Init(void)
{
	big_ball_state = FORWARD;
	
	Straight_Meta_Init(100, 0.0, 4.0); // speed, dist, timeout
	Hold_Init(&dist_trigger, 3);
}

static void Forward_Routine(void)
{
	float dist;
	
	dist = Get_Front_IR_In();
	Hold_Step(&dist_trigger, dist <= dist_thresh);
	
	if (Hold_Trigger(&dist_trigger)) {
		Reverse_Init();
		return;
	}
	
	Straight_Meta_Routine();
}

// ------------------------------------------------------------

static void Reverse_Init(void)
{
	big_ball_state = REVERSE;
	
	Straight_Meta_Init(-100, 0.20, 2.0);
}

static void Reverse_Routine(void)
{
	if (straight_done) {
		Pickup_Init();
		return;
	}
	
	Straight_Meta_Routine();
}

// ------------------------------------------------------------

static void Pickup_Init(void)
{
	big_ball_state = PICKUP;
	
	Pickup_Meta_Init();
}

static void Pickup_Routine(void)
{
	if (pickup_done) {
		Done();
		return;
	}
	
	Pickup_Meta_Routine();
}

