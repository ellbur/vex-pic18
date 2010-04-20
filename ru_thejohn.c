
#include "ru_thejohn.h"

#include "ru_config.h"
#include "ru_motor.h"
#include "ru_shoulder.h"
#include "ru_ramp.h"
#include "ru_drive.h"

void The_John_Init(void)
{
	
}

void The_John_Routine(void)
{
	Manual_Tank_Drive_Routine();
	Manual_Shoulder_Routine();
	Manual_Ramp_Routine();
}
