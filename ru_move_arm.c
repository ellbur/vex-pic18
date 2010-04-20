
#include "ru_move_arm.h"
#include "ru_shoulder.h"
#include "ru_config.h"

typedef enum {
	MOVING,
	DONE
} move_arm_state_t;

static move_arm_state_t move_arm_state;
char move_arm_done;

static int pot_thresh;
static char direction;

static void Moving_Init(void);
static void Moving_Routine(void);

static void Done(void);

void Move_Arm_Meta_Init(int _pot_thresh, char _direction)
{
	pot_thresh = _pot_thresh;
	direction  = _direction;
	
	move_arm_done = 0;
	
	Moving_Init();
}

void Move_Arm_Meta_Routine(void)
{
	switch (move_arm_state) {
		case MOVING: Moving_Routine(); break;
		case DONE: return;
	}
}

static void Done(void)
{
	move_arm_state = DONE;
	move_arm_done = 1;
}

// -------------------------------------------------------------------

#define moving_timeout ((float)2.0)

static int moving_loop_count;

static void Moving_Init(void)
{
	move_arm_state = MOVING;
	
	moving_loop_count = 0;
}

static void Moving_Routine(void)
{
	int pot;
	
	if (moving_loop_count >= moving_timeout/SLOW_LOOP_PERIOD) {
		Done();
		return;
	}
	
	pot = Get_Shoulder_Pot();
	
	if (direction > 0 && pot >= pot_thresh) {
		Done();
		return;
	}
	
	if (direction < 0 && pot <= pot_thresh) {
		Done();
		return;
	}
	
	if (direction > 0) {
		Set_Shoulder_Speed(127);
	}
	
	if (direction < 0) {
		Set_Shoulder_Speed(-127);
	}
	
	moving_loop_count++;
}
