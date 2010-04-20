
#include "ru_to_wall.h"
#include "ru_drive.h"
#include "ru_config.h"
#include "ru_move_arm.h"
#include "ru_shoulder.h"
#include "ru_straight.h"
#include "ru_turn.h"
#include "ru_ir.h"
#include "ru_hold.h"

typedef enum {
	RAISE_ARM,
	FORWARD,
	TURN_1,
	ARM_ON_WALL,
	TURN_2,
	LOWER_ARM,
	REVERSE, // in case of panic
	DONE
} to_wall_state_t;

static to_wall_state_t to_wall_state;
char to_wall_done;

static void Raise_Arm_Init(void);
static void Raise_Arm_Routine(void);

static void Forward_Init(void);
static void Forward_Routine(void);

static void Turn_1_Init(void);
static void Turn_1_Routine(void);

static void Arm_On_Wall_Init(void);
static void Arm_On_Wall_Routine(void);

static void Turn_2_Init(void);
static void Turn_2_Routine(void);

static void Lower_Arm_Init(void);
static void Lower_Arm_Routine(void);

static void Reverse_Init(void);
static void Reverse_Routine(void);

static void Done(void);

void To_Wall_Meta_Init(void)
{
	to_wall_done = 0;
	Raise_Arm_Init();
}

void To_Wall_Meta_Routine(void)
{
	switch (to_wall_state) {
		case RAISE_ARM:    Raise_Arm_Routine();    break;
		case FORWARD:      Forward_Routine();      break;
		case TURN_1:       Turn_1_Routine();       break;
		case ARM_ON_WALL:  Arm_On_Wall_Routine();  break;
		case TURN_2:       Turn_2_Routine();       break;
		case LOWER_ARM:    Lower_Arm_Routine();    break;
		case REVERSE:      Reverse_Routine();      break;
		case DONE: return;
	}
}

static void Done(void)
{
	to_wall_state = DONE;
	to_wall_done  = 1;
}

// -------------------------------------------------------------------

static void Raise_Arm_Init(void)
{
	to_wall_state = RAISE_ARM;
	
	Move_Arm_Meta_Init(shoulder_stay_up_pot_thresh, UP);
}

static void Raise_Arm_Routine(void)
{
	if (move_arm_done) {
		Forward_Init();
		return;
	}
	
	Move_Arm_Meta_Routine();
}

// -------------------------------------------------------------------

#define dist_thresh ((float)12.0)

static hold_t dist_trigger;

static void Forward_Init(void)
{
	to_wall_state = FORWARD;
	
	Hold_Init(&dist_trigger, 3);
	
	Straight_Meta_Init(
		127, // speed
		0.0, // no distance
		4.0  // timeout
	);
}

static void Forward_Routine(void)
{
	float dist;
	
	if (straight_done) {
		printf("straight done\n");
		Turn_1_Init();
		return;
	}
	
	dist = Get_Front_Low_IR_In();
	Hold_Step(&dist_trigger, dist <= dist_thresh);
	
	if (Hold_Trigger(&dist_trigger)) {
		printf("dist trigger\n");
		Turn_1_Init();
		return;
	}
	
	Straight_Meta_Routine();
}

// -------------------------------------------------------------------

static void Turn_1_Init(void)
{
	to_wall_state = TURN_1;
	
	Turn_Meta_Init(-PI/2.0 * 0.75);
}

static void Turn_1_Routine(void)
{
	if (turn_done) {
		Arm_On_Wall_Init();
		return;
	}
	
	Turn_Meta_Routine();
}

// -------------------------------------------------------------------

static void Arm_On_Wall_Init(void)
{
	to_wall_state = ARM_ON_WALL;
	
	Move_Arm_Meta_Init(shoulder_on_wall_pot_thresh, DOWN);
}

static void Arm_On_Wall_Routine(void)
{
	if (move_arm_done) {
		Turn_2_Init();
		return;
	}
	
	Move_Arm_Meta_Routine();
}

// -------------------------------------------------------------------

#define turn_2_timeout ((float)2.0)

static int turn_2_loop_count;

static void Turn_2_Init(void)
{
	to_wall_state = TURN_2;
	
	turn_2_loop_count = 0;
}

static void Turn_2_Routine(void)
{
	int pot;
	
	if (turn_2_loop_count >= turn_2_timeout/SLOW_LOOP_PERIOD) {
		Reverse_Init();
		return;
	}
	
	if (pot <= shoulder_off_wall_pot_thresh) {
		Lower_Arm_Init();
		return;
	}
	
	Set_Auto_Tank_Drive(127, -50);
	
	turn_2_loop_count = 0;
}

// -------------------------------------------------------------------

static void Lower_Arm_Init(void)
{
	to_wall_state = LOWER_ARM;
	
	Move_Arm_Meta_Init(shoulder_lowering_pot_thresh, DOWN);
}

static void Lower_Arm_Routine(void)
{
	if (move_arm_done) {
		Done();
	}
	
	Move_Arm_Meta_Routine();
}

// -------------------------------------------------------------------

static void Reverse_Init(void)
{
	to_wall_state = REVERSE;
	
	Straight_Meta_Init(-127, 1.0, 3.0);
}

static void Reverse_Routine(void)
{
	if (straight_done) {
		Done();
		return;
	}
	
	Straight_Meta_Routine();
}

