
#include "ru_stall_test.h"
#include "ru_stall.h"
#include "ru_config.h"
#include "ru_straight.h"

typedef enum {
	WAITING,
	FORWARD
} stall_test_state_t;

static stall_test_state_t stall_test_state;

static void Waiting_Init(void);
static void Waiting_Routine(void);

static void Forward_Init(void);
static void Forward_Routine(void);

void Stall_Test_Init(void)
{
	Waiting_Init();
}

void Stall_Test_Routine(void)
{
	switch (stall_test_state) {
		case WAITING: Waiting_Routine(); printf("waiting\n"); break;
		case FORWARD: Forward_Routine(); printf("forward\n"); break;
	}
}

// ------------------------------------------------------------

static void Waiting_Init(void)
{
	stall_test_state = WAITING;
}

static void Waiting_Routine(void)
{
	if ((int)TRIGGER_BUTTON > (int)150) {
		Forward_Init();
		return;
	}
}

// ------------------------------------------------------------

static void Forward_Init(void)
{
	stall_test_state = FORWARD;
	
	Straight_Meta_Init(50, 0.0, 0.0);
}

static void Forward_Routine(void)
{
	if (straight_done) {
		Waiting_Init();
		return;
	}
	
	Straight_Meta_Routine();
}
