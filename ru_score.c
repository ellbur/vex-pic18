
#include "ru_score.h"
#include "ru_drive.h"
#include "ru_bumper.h"
#include "ru_ramp.h"

typedef enum {
	BACKING_UP,
	LIFTING,
	PAUSING,
	LOWERING,
	DONE
} score_state_t;

static score_state_t score_state;
char score_done;

// ----------------------------------------------------------

static void Backing_Up_Init(void);
static void Backing_Up_Routine(void);

static void Lifting_Init(void);
static void Lifting_Routine(void);

static void Pausing_Init(void);
static void Pausing_Routine(void);

static void Lowering_Init(void);
static void Lowering_Routine(void);

static void Done(void);

// ----------------------------------------------------------

void Score_Meta_Init(void)
{
	Backing_Up_Init();
	score_done  = 0;
}

void Score_Meta_Routine(void)
{
	switch (score_state) {
		case BACKING_UP: Backing_Up_Routine(); break;
		case LIFTING:    Lifting_Routine();    break;
		case PAUSING:    Pausing_Routine();    break;
		case LOWERING:   Lowering_Routine();   break;
		case DONE: return;
	}
}

static void Done(void)
{
	score_state = DONE;
	score_done  = 1;
}

// ----------------------------------------------------------

static void Backing_Up_Init(void)
{
	score_state = BACKING_UP;
}

static void Backing_Up_Routine(void)
{
	
}

// ----------------------------------------------------------

static void Lifting_Init(void)
{
	score_state = LIFTING;
}

static void Lifting_Routine(void)
{
	
}

// ----------------------------------------------------------

static void Pausing_Init(void)
{
	score_state = PAUSING;
}

static void Pausing_Routine(void)
{
	
}

// ----------------------------------------------------------

static void Lowering_Init(void)
{
	score_state = LOWERING;
}

static void Lowering_Routine(void)
{
	
}

