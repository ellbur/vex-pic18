
#include "ru_slow_loop.h"

#include "ru_thejohn.h"
#include "ru_pot_test.h"
#include "ru_elbow_pickup_test.h"
#include "ru_config.h"
#include "ru_motor.h"
#include "ru_shoulder.h"
#include "ru_small_auto.h"
#include "ru_timer.h"
#include "ru_timer_test.h"
#include "ru_encoder_test.h"
#include "ru_encoder_record.h"
#include "ru_encoder.h"
#include "ru_drive.h"
#include "ru_drive_pid_test.h"
#include "ru_drive_pid.h"
#include "ru_speed_test.h"
#include "ru_vel_wave.h"
#include "ru_vel_noise.h"
#include "ru_wheel_pid.h"
#include "ru_trans_proc.h"
#include "ru_ir_test.h"
#include "ru_ir.h"
#include "ru_cruise_test.h"
#include "ru_orbit_test.h"

void RU_Slow_Loop(void)
{
	if (rxdata.rc_receiver_status_byte.allbits) {
		RU_Auto_Slow_Loop();
	}
	else {
		RU_Tele_Slow_Loop();
	}
}

void RU_Init(void)
{
	Timer_Init();
	Encoder_Init();
#if enable_drive_pid
	Drive_PIDs_Init();
#endif
	Drive_Init();
	
// 	/**/ Small_Auto_Init();
// 	/**/ Encoder_Record_Init();
// 	/**/ Encoder_Test_Init();
// 	/**/ Speed_Test_Init();
// 	/**/ Vel_Wave_Init();
// 	/**/ Vel_Noise_Init();
// 	/**/ Wheel_PID_Init();
// 	/**/ Trans_Proc_Init();
// 	/**/ IR_Test_Init();
// 	/**/ Cruise_Test_Init();
	/**/ Orbit_Test_Init();
}

void RU_Auto_Slow_Loop(void)
{
// 	/**/ Small_Auto_Routine();
}

void RU_Tele_Slow_Loop(void)
{
//  /**/ The_John_Routine();
// 	/**/ Drive_PID_Test_Routine();
// 	/**/ Encoder_Record_Routine();
// 	/**/ Encoder_Test_Routine();
// 	/**/ Speed_Test_Routine();
// 	/**/ Vel_Wave_Routine();
// 	/**/ Vel_Noise_Routine();
// 	/**/ Wheel_PID_Routine();
// 	/**/ Trans_Proc_Routine();
// 	/**/ Manual_Tank_Drive_Routine();
// 	/**/ Manual_Tank_PID_Drive_Routine();
// 	/**/ IR_Test_Routine();
// 	/**/ Cruise_Test_Routine();
	/**/ Orbit_Test_Routine();
	
	// This probably should not ultimately be here.
	Encoder_Reset_Delta();
	IR_Filter_Routine();
}

