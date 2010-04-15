
#ifndef _ru_accel_h
#define _ru_accel_h 1

// Impose gradual acceleration on a motor

typedef struct {
	// Config
	int max_jump;
	
	// State
	int target;
	int actual;
	int used;
} accel_t;

void Accel_Init(accel_t *accel, int max_jump);
void Accel_Step(accel_t *accel, int target);
void Accel_Clear(accel_t *accel);
int Accel_Get_Output(accel_t *accel);

#endif
