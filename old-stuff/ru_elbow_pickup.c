
#include "ru_elbow_pickup.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_elbow.h"
#include "ru_shoulder.h"

typedef enum {
	RAISE_ELBOW,
	RAISE_ARM,
	RELEASE_ELBOW,
	LOWER_ARM,
	LOWER_ELBOW,
	DONE
} elbow_pickup_state_t;

static elbow_pickup_state_t elbow_pickup_state;
char elbow_pickup_done;

static void Raise_Elbow_Init(void);
static void Raise_Elbow_Routine(void);

static void Raise_Arm_Init(void);
static void Raise_Arm_Routine(void);

static void Release_Elbow_Init(void);
static void Release_Elbow_Routine(void);

static void Lower_Arm_Init(void);
static void Lower_Arm_Routine(void);

static void Lower_Elbow_Init(void);
static void Lower_Elbow_Routine(void);

static void Done(void);

void Elbow_Pickup_Init(void)
{
	elbow_pickup_done = 0;
	
	Raise_Elbow_Init();
}

void Elbow_Pickup_Routine(void)
{
	switch (elbow_pickup_state) {
		case RAISE_ELBOW:    Raise_Elbow_Routine();   printf("re\n");   break;
		case RAISE_ARM:      Raise_Arm_Routine();     printf("ra\n");   break;
		case RELEASE_ELBOW:  Release_Elbow_Routine(); printf("rele\n"); break;
		case LOWER_ARM:      Lower_Arm_Routine();     printf("la\n");   break;
		case LOWER_ELBOW:    Lower_Elbow_Routine();   printf("le\n");   break;
		case DONE: printf("done\n"); return;
	}
	printf("pot = %d\n", (int)Get_Shoulder_Pot());
}

// -------------------------------------------------------------

#define RAISE_ELBOW_TIMEOUT ((int)20) // SL
#define RAISE_ELBOW_ELBOW_SPEED ((int)127) // spwm

static int raise_elbow_timer;

static void Raise_Elbow_Init(void)
{
	elbow_pickup_state = RAISE_ELBOW;
	raise_elbow_timer = 0;
}
static void Raise_Elbow_Routine(void)
{
	if (raise_elbow_timer > RAISE_ELBOW_TIMEOUT) {
		Raise_Arm_Init();
		return;
	}
	
	Set_Elbow_Speed(RAISE_ELBOW_ELBOW_SPEED);
	raise_elbow_timer++;
}

// -------------------------------------------------------------

#define RAISE_ARM_TIMEOUT            ((int)300)
#define RAISE_ARM_POT_THRESH         ((int)500)
#define RAISE_ARM_RELEASE_POT_THRESH ((int)450)
#define RAISE_ARM_SHOULDER_SPEED     ((int)127)
#define RAISE_ARM_ELBOW_SPEED_1      ((int)60)
#define RAISE_ARM_ELBOW_SPEED_2      ((int)-127)

int raise_arm_timer;

static void Raise_Arm_Init(void)
{
	elbow_pickup_state = RAISE_ARM;
	raise_arm_timer = 0;
}
static void Raise_Arm_Routine(void)
{
	int pot;
	
	if (raise_arm_timer > RAISE_ARM_TIMEOUT) {
		// This might to bail
		Done();
		return;
	}
	
	pot = Get_Shoulder_Pot();
	
	if (pot > RAISE_ARM_POT_THRESH) {
		Release_Elbow_Init();
		return;
	}
	
	Set_Shoulder_Speed(RAISE_ARM_SHOULDER_SPEED);
	
	if (pot > RAISE_ARM_RELEASE_POT_THRESH) {
		Set_Elbow_Speed(RAISE_ARM_ELBOW_SPEED_2);
	}
	else {
		Set_Elbow_Speed(RAISE_ARM_ELBOW_SPEED_1);
	}
	
	raise_arm_timer++;
}

// -------------------------------------------------------------

#define RELEASE_ELBOW_TIMEOUT ((int)30)
#define RELEASE_ELBOW_ELBOW_SPEED ((int)-127)
#define RELEASE_ELBOW_SHOULDER_SPEED ((int)50)

static int release_elbow_timer;

static void Release_Elbow_Init(void)
{
	elbow_pickup_state = RELEASE_ELBOW;
	release_elbow_timer = 0;
}
static void Release_Elbow_Routine(void)
{
	if (release_elbow_timer > RELEASE_ELBOW_TIMEOUT) {
		Lower_Arm_Init();
		return;
	}
	
	Set_Elbow_Speed(RELEASE_ELBOW_ELBOW_SPEED);
	Set_Shoulder_Speed(RELEASE_ELBOW_SHOULDER_SPEED);
	
	release_elbow_timer++;
}

// -------------------------------------------------------------

#define LOWER_ARM_POT_THRESH     ((int)5)
#define LOWER_ARM_SHOULDER_SPEED ((int)-127) // spwm

static void Lower_Arm_Init(void)
{
	elbow_pickup_state = LOWER_ARM;
}
static void Lower_Arm_Routine(void)
{
	int pot;
	
	pot = Get_Shoulder_Pot();
	
	if (pot < LOWER_ARM_POT_THRESH) {
		Lower_Elbow_Init();
		return;
	}
	
	Set_Shoulder_Speed(LOWER_ARM_SHOULDER_SPEED);
}

// -------------------------------------------------------------

#define LOWER_ELBOW_TIMEOUT     ((int)20)
#define LOWER_ELBOW_ELBOW_SPEED ((int)-127)

static int lower_elbow_timer;

static void Lower_Elbow_Init(void)
{
	elbow_pickup_state = LOWER_ELBOW;
	lower_elbow_timer = 0;
}
static void Lower_Elbow_Routine(void)
{
	if (lower_elbow_timer > LOWER_ELBOW_TIMEOUT) {
		Done();
		return;
	}
	
	Set_Elbow_Speed(LOWER_ELBOW_ELBOW_SPEED);
	lower_elbow_timer++;
}

// --------------------------------------------------------------

static void Done(void)
{
	elbow_pickup_done = 1;
}
