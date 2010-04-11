
#include "ru_turn.h"
#include "ru_drive.h"
#include "ru_encoder.h"

typedef enum {
	TURNING,
	DONE
} turn_state_t;

static turn_state_t turn_state;
char turn_done;

// ----------------------------------------------------------
// Parameters

double target_amount;

// ----------------------------------------------------------

static void Turning_Init(void);
static void Turning_Routine(void);

static void Done();

// ----------------------------------------------------------

void Turn_Meta_Init(double amount_rad)
{
	Turning_Init();
}

void Turn_Meta_Routine(void)
{
	switch (turn_state) {
		case TURNING: Turning_Routine(); break;
		case DONE: return;
	}
}

static void Done()
{
	turn_state = DONE;
	turn_done  = 1;
}

// ----------------------------------------------------------

static float angle_at_start;
static float target_angle;

static void Turning_Init(void)
{
	turn_state = TURNING;
	
	angle_at_start = Encoder_Get_Angle();
	target_angle   = angle_at_start + target_amount;
}

static void Turning_Routine(void)
{
	float angle;
	float target_angle;
	
	angle = Encoder_Get_Angle();
	
	if (angle <= target_angle && target_amount <= 0) {
		Done();
		return;
	}
	
	if (angle >= target_angle && target_amount >= 0) {
		Done();
		return;
	}
	
	if (target_amount < 0) {
		Set_Tank_Drive(+127, -127);
	}
	else {
		Set_Tank_Drive(-127, +127);
	}
}
