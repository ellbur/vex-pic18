
#include "ru_noise_tests.h"
#include "ru_io_aliases.h"

#include "printf_lib.h"
#include "ifi_utilities.h"
#include "ifi_aliases.h"
#include "ifi_default.h"
#include "delays.h"

int time_count = 0;

int ir_sensor_1_readings[NUM_READS];
int ir_sensor_2_readings[NUM_READS];
int resistor_readings[NUM_READS];

int noise_level;
int noise_step;
int motor_dir;

void Noise_Test_Routine(void)
{
	Sensor_Read_Routine();
	Motor_Vibrate_Routine();
	Sensor_Print_Routine();
	
	time_count++;
}

void Sensor_Read_Routine(void)
{
	unsigned char i;
	
	for (i=0; i<NUM_READS; i++) {
		ir_sensor_1_readings[i] = Get_Analog_Value(IR_SENSOR_1);
		ir_sensor_2_readings[i] = Get_Analog_Value(IR_SENSOR_2);
		resistor_readings[i]    = Get_Analog_Value(RESISTOR);
		
		if (i < NUM_READS-1) {
			Delay100TCYx(READ_DELAY_100TCY);
		}
	}
}

void Sensor_Print_Routine(void)
{
	unsigned char i;
	
	//printf("%d,%d,%d,", (int) time_count, (int) MOTOR, (int) noise_level);
	
	for (i=0; i<NUM_READS; i++)
		printf("%d,", (int) ir_sensor_1_readings[i]);
	
	for (i=0; i<NUM_READS; i++)
		printf("%d,", (int) ir_sensor_2_readings[i]);
	
	for (i=0; i<NUM_READS; i++)
		printf("%d,", (int) resistor_readings[i]);
}

void Motor_Vibrate_Routine(void)
{
	if (time_count % NOISE_DELAY == 0)
		noise_level += noise_step;
	
	if (noise_level >= NOISE_MAX) noise_step = -1;
	if (noise_level <= NOISE_MIN) noise_step = +1;
	
	if (time_count % MOTOR_DELAY == 0)
		motor_dir = -motor_dir;
	
	// MOTOR = 127 + noise_level * motor_dir;
}
