
#include "ru_drive_pid_test.h"
#include "ru_drive_pid.h"
#include "ru_drive.h"
#include "ru_config.h"

void Drive_PID_Test_Routine(void)
{
	Manual_Tank_PID_Drive_Routine();
	
	printf("%d,%d,%d,%d,%d\n",
		(int) (drive_pids[0].pid.target  * 100),
		(int) (drive_pids[0].pid.process * 100),
		(int) (drive_pids[0].pid.p_error * 100),
		(int) (drive_pids[0].pid.i_error * 100),
		(int) (drive_pids[0].pid.output  * 100) );
}
