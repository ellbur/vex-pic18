
#include "ru_dump.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_input.h"
#include "ru_drive.h"
#include "ru_ramp.h"

char dump_done;

typedef enum {
	RUNNING,
	LIFTING,
	PAUSING,
	LOWERING,
	DONE
} dump_state_t;

static dump_state_t dump_state;

static void Running_Init(void);
static void Running_Routine(void);

static void Lifting_Init(void);
static void Lifting_Routine(void);

static void Pausing_Init(void);
static void Pausing_Routine(void);

static void Lowering_Init(void);
static void Lowering_Routine(void);

static void Done();

void Dump_Init(void)
{
	dump_done  = 0;
	
	Running_Init();
}

void Dump_Routine(void)
{
	switch (dump_state) {
		case RUNNING:  Running_Routine();  break;
		case LIFTING:  Lifting_Routine();  break;
		case PAUSING:  Pausing_Routine();  break;
		case LOWERING: Lowering_Routine(); break;
		case DONE: return;
	}
}

static void Done(void)
{
	dump_done = 1;
}

// ---------------------------------------------------------

#define RUNNING_Y_SPEED -127

static void Running_Init(void)
{
	dump_state = RUNNING;
}

static void Running_Routine(void)
{
	char bumper;
	
	bumper = Get_Bumper();
	
	if (bumper) {
		Lifting_Init();
		return;
	}
	
	Set_Omni_Drive(0, RUNNING_Y_SPEED, 0);
}

// ---------------------------------------------------------

#define LIFTING_RAMP_SPEED 127
#define LIFTING_Y_SPEED    -50

static void Lifting_Init(void)
{
	dump_state = LIFTING;
}

static void Lifting_Routine(void)
{
	if (! RAMP_SWITCH) {
		Pausing_Init();
		return;
	}
	
	Set_Omni_Drive(0, LIFTING_Y_SPEED, 0);
	Set_Ramp_Speed(LIFTING_RAMP_SPEED);
}

// ---------------------------------------------------------

#define PAUSING_RAMP_SPEED   0
#define PAUSING_TIMEOUT    100

static int pausing_timer;

static void Pausing_Init(void)
{
	dump_state = PAUSING;
	pausing_timer = 0;
}

static void Pausing_Routine(void)
{
	if (pausing_timer >= PAUSING_TIMEOUT) {
		Lowering_Init();
		return;
	}
	
	Set_Ramp_Speed(PAUSING_RAMP_SPEED);
	
	pausing_timer++;
}

// ---------------------------------------------------------

#define LOWERING_RAMP_SPEED  -127
#define LOWERING_TIMEOUT       25

static int lowering_timer;

static void Lowering_Init(void)
{
	dump_state = LOWERING;
	lowering_timer = 0;
}

static void Lowering_Routine(void)
{
	if (lowering_timer >= LOWERING_TIMEOUT) {
		Done();
		return;
	}
	
	Set_Ramp_Speed(LOWERING_RAMP_SPEED);
	
	lowering_timer++;
}

