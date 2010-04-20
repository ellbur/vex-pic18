
#include "ru_action_test.h"
#include "ru_config.h"
#include "ru_to_wall.h"
#include "ru_big_ball.h"

typedef enum {
	WAITING,
	ACTIVE
} action_test_state_t;

static action_test_state_t action_test_state;

static void Waiting_Init(void);
static void Waiting_Routine(void);

static void Active_Init(void);
static void Active_Routine(void);

void Action_Test_Init(void)
{
	Waiting_Init();
}

void Action_Test_Routine(void)
{
	switch (action_test_state) {
		case WAITING: Waiting_Routine(); printf("waiting\n"); break;
		case ACTIVE:  Active_Routine();  printf("active\n"); break;
	}
}

// ------------------------------------------------------------

static void Waiting_Init(void)
{
	action_test_state = WAITING;
}

static void Waiting_Routine(void)
{
	if (Get_Trigger_Button()) {
		Active_Init();
		return;
	}
}

// ------------------------------------------------------------

static void Active_Init(void)
{
	action_test_state = ACTIVE;
	
	Big_Ball_Meta_Init();
}

static void Active_Routine(void)
{
	if (big_ball_done) {
		Waiting_Init();
		return;
	}
	
	Big_Ball_Meta_Routine();
}
