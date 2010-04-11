
#include "ru_pid.h"

void PID_Init(pid_t *pid)
{
	pid->p_error = 0.0f;
	pid->i_error = 0.0f;
	pid->d_error = 0.0f;
}

void PID_Step(pid_t *pid, float process, float target, float time_step)
{
	float old_i_error, error;
	
	pid->process = process;
	pid->target  = target;
	
	error = process - target;
	old_i_error = pid->i_error;
	
	pid->d_error  = (process - pid->last_process) / time_step;
	pid->i_error += error * time_step;
	pid->p_error  = error;
	
	pid->output = pid->K_P*pid->p_error
	            + pid->K_I*pid->i_error
	            + pid->K_D*pid->d_error ;
	
	if (pid->output < pid->MIN_OUTPUT && error > 0) {
		pid->i_error = old_i_error;
	}
	else if (pid->output > pid->MAX_OUTPUT && error < 0) {
		pid->i_error = old_i_error;
	}
	
	pid->last_process = process;
}

