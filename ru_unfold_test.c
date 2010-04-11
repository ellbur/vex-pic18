
#include "ru_unfold_test.h"
#include "ru_config.h"
#include "ru_unfold.h"
#include "ru_motor.h"

typedef enum {
	WAITING,
	ACTIVE
} unfold_test_state_t;

static unfold_test_state_t unfold_test_state;

static void Waiting_Init(void);
static void Waiting_Routine(void);

static void Active_Init(void);
static void Active_Routine(void);

void Unfold_Test_Init(void)
{
	Waiting_Init();
}

void Unfold_Test_Routine(void)
{
	switch (unfold_test_state) {
		case WAITING: Waiting_Routine(); printf("waiting\n"); break;
		case ACTIVE:  Active_Routine();  printf("active\n");  break;
	}
}

static void Waiting_Init(void)
{
	unfold_test_state = WAITING;
}

static void Waiting_Routine(void)
{
	int button;
	
	button = Bang_Bang(To_S(UNFOLD_BUTTON));
	printf("button = %d\n", (int) button);
	
	if (button > 0) {
		Active_Init();
		return;
	}
}

static void Active_Init(void)
{
	unfold_test_state = ACTIVE;
	Unfold_Init();
}

static void Active_Routine(void)
{
	if (unfold_done) {
		Waiting_Init();
		return;
	}
	
	Unfold_Routine();
}
