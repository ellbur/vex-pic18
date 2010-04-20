
#include "ru_small_auto.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_input.h"
#include "ru_dump.h"
#include "ru_elbow_pickup.h"
#include "ru_unfold.h"
#include "ru_drive.h"

char small_auto_done;

typedef enum {
	BACKUP,
	UNFOLD,
	DUMP,
	DONE
} small_auto_state_t;

static small_auto_state_t small_auto_state;

static void Auto_Backup_Init(void);
static void Auto_Backup_Routine(void);

static void Auto_Unfold_Init(void);
static void Auto_Unfold_Routine(void);

static void Auto_Dump_Init(void);
static void Auto_Dump_Routine(void);

static void Done();

void Small_Auto_Init(void)
{
	small_auto_done = 0;
	Auto_Backup_Init();
}

void Small_Auto_Routine(void)
{
	switch (small_auto_state) {
		case BACKUP: Auto_Backup_Routine(); break;
		case UNFOLD: Auto_Unfold_Routine(); break;
		case DUMP:   Auto_Dump_Routine();   break;
		case DONE: return;
	}
}

static void Done(void)
{
	small_auto_done = 1;
}

// -----------------------------------------------------

#define BACKUP_TIMEOUT ((int)150)
#define BACKUP_Y_SPEED ((int)-127)

static int backup_timer;

static void Auto_Backup_Init(void)
{
	small_auto_state = BACKUP;
	backup_timer = 0;
}

static void Auto_Backup_Routine(void)
{
	if (backup_timer >= BACKUP_TIMEOUT) {
		Auto_Unfold_Init();
		return;
	}
	
	Set_Omni_Drive(0, BACKUP_Y_SPEED, 0);
	
	backup_timer++;
}

// ----------------------------------------------------

static void Auto_Unfold_Init(void)
{
	Unfold_Init();
}

static void Auto_Unfold_Routine(void)
{
	if (unfold_done) {
		Auto_Dump_Init();
		return;
	}
	
	Unfold_Routine();
}

// ----------------------------------------------------

static void Auto_Dump_Init(void)
{
	Dump_Init();
}

static void Auto_Dump_Routine(void)
{
	if (dump_done) {
		Done();
		return;
	}
	
	Dump_Routine();
}
