
#ifndef _ru_pid_h
#define _ru_pid_h 1

typedef struct {
	float K_P;
	float K_I;
	float K_D;
	
	float MIN_OUTPUT;
	float MAX_OUTPUT;
	
	float p_error;
	float i_error;
	float d_error;
	
	float process;
	float target;
	float last_process;
	
	float output;
	
} pid_t;

void PID_Init(pid_t *pid);
void PID_Step(pid_t *pid, float process, float target, float time_step);

#endif
