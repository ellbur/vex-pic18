
#ifndef _ru_noise_tests_h
#define _ru_noise_tests_h 1

#define NOISE_DELAY ((int)100)
#define MOTOR_DELAY   ((int)5)
#define NOISE_MAX    ((int)30)
#define NOISE_MIN     ((int)0)

#define READ_DELAY_100TCY 15
#define NUM_READS 4

extern int time_count;

extern int ir_sensor_1_readings[NUM_READS];
extern int ir_sensor_2_readings[NUM_READS];
extern int resistor_readings[NUM_READS];

extern int noise_level;
extern int noise_step;
extern int motor_dir;

void Noise_Test_Routine(void);

void Motor_Vibrate_Routine(void);
void Sensor_Read_Routine(void);
void Sensor_Print_Routine(void);

#endif
