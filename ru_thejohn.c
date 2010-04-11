
#include "ru_thejohn.h"

#include "ru_config.h"
#include "ru_motor.h"
#include "ru_elbow.h"
#include "ru_shoulder.h"
#include "ru_elbow_pickup.h"
#include "ru_elbow_pickup_test.h"
#include "ru_ramp.h"
#include "ru_drive.h"
#include "ru_unfold_test.h"
#include "ru_sample.h"

void The_John_Routine(void)
{
	
	Manual_Tank_Drive_Routine();
	Manual_Shoulder_Routine();
	Manual_Ramp_Routine();
}
