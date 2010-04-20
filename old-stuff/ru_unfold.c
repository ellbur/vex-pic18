
#include "ru_unfold.h"
#include "ru_shoulder.h"
#include "ru_elbow.h"
#include "ru_config.h"
#include "ru_input.h"

char unfold_done;

typedef enum {
	LOWERING,
	OPEN_ELBOW,
	DONE
} unfold_state_t;

static unfold_state_t unfold_state;

static void Lowering_Init(void);
static void Lowering_Routine(void);

static void Open_Elbow_Init(void);
static void Open_Elbow_Routine(void);

void Done(void)
{
	unfold_state = DONE;
	unfold_done = 1;
}

void Unfold_Init(void)
{
	unfold_done = 0;
	
	Lowering_Init();
}

void Unfold_Routine(void)
{
	switch (unfold_state) {
		case LOWERING:   Lowering_Routine();   printf("lower\n"); break;
		case OPEN_ELBOW: Open_Elbow_Routine(); printf("open\n");  break;
		case DONE: return;
	}
}

// -------------------------------------------------------------

#define LOWERING_SHOULDER_POT_THRESH  ((int)4)
#define LOWERING_SHOULDER_SPEED       ((int)-127)
#define LOWERING_ELBOW_SPEED          ((int)0)
#define LOWERING_TIMEOUT              ((int)50)
#define LOWERING_HARD_TIMEOUT         ((int)200)

static int lowering_timer;

static void Lowering_Init(void)
{
	unfold_state = LOWERING;
	lowering_timer = 0;
}

static void Lowering_Routine(void)
{
	int pot;
	
	pot = Get_Shoulder_Pot();
	
	printf("pot = %d (raw = %d)\n", (int) pot,
		(int) Get_Analog_Value(SHOULDER_POT));
	
	if ((lowering_timer >= LOWERING_TIMEOUT)
		&& (pot <= LOWERING_SHOULDER_POT_THRESH))
	{
		Open_Elbow_Init();
		return;
	}
	
	if (lowering_timer >= LOWERING_HARD_TIMEOUT) {
		Open_Elbow_Init();
		return;
	}
	
	Set_Shoulder_Speed(LOWERING_SHOULDER_SPEED);
	Set_Elbow_Speed(LOWERING_ELBOW_SPEED);
	
	lowering_timer++;
}

// -------------------------------------------------------------

#define OPEN_ELBOW_TIMEOUT     ((int)20)
#define OPEN_ELBOW_ELBOW_SPEED ((int)-127)

static int open_elbow_timer;

static void Open_Elbow_Init(void)
{
	unfold_state = OPEN_ELBOW;
	open_elbow_timer = 0;
}

static void Open_Elbow_Routine(void)
{
	if (open_elbow_timer > OPEN_ELBOW_TIMEOUT) {
		Done();
		return;
	}
	
	Set_Elbow_Speed(OPEN_ELBOW_ELBOW_SPEED);
	
	open_elbow_timer++;
}
