
#ifndef _ru_io_aliases_h
#define _ru_io_aliases_h 1

/* IR Stuff */
#define IR_SENSOR         rc_ana_in02
#define IR_SENSOR_1       rc_ana_in02
#define IR_SENSOR_2       rc_ana_in04
#define RESISTOR          rc_ana_in06
#define MOTOR_SWITCH      PWM_in6

// -------- The Nitish ------

#if nitish

#define LEFT_SCISSOR     pwm01
#define RIGHT_SCISSOR    pwm02

#define LEFT_WHEEL_1     pwm03
#define LEFT_WHEEL_2     pwm04
#define RIGHT_WHEEL_1    pwm05
#define RIGHT_WHEEL_2    pwm06

#define LEFT_SHOULDER    pwm07
#define RIGHT_SHOULDER   pwm08

#define FRONT_IR         rc_ana_in05
#define SIDE_FRONT_IR    rc_ana_in06
#define SIDE_REAR_IR     rc_ana_in07

#define SHOULDER_POT     rc_ana_in08

#endif

// -------- The John --------

#if kevin

// OMNI
#define LEFT_WHEEL        pwm01
#define RIGHT_WHEEL       pwm02
#define BACK_WHEEL        pwm07
#define BACK_WHEEL_1      pwm07
#define BACK_WHEEL_2      pwm08

// TANK
#define LEFT_WHEEL_1      pwm01
#define RIGHT_WHEEL_1     pwm02
#define LEFT_WHEEL_2      pwm03
#define RIGHT_WHEEL_2     pwm04

#define LEFT_SHOULDER     pwm05
#define RIGHT_SHOULDER    pwm06

#define RAMP              pwm04

#define RAMP_SWITCH       rc_dig_in04
#define SHOULDER_POT      rc_ana_in05
#define BUMPER_SWITCH     rc_dig_in06

#define FRONT_IR          rc_ana_in05
#define SIDE_FRONT_IR     rc_ana_in06
#define SIDE_REAR_IR      rc_ana_in07

#endif

// OI

#define LEFT_JOY          PWM_in3
#define RIGHT_JOY         PWM_in2

#define LEFT_Y            PWM_in3
#define RIGHT_Y           PWM_in2

#define LEFT_X            PWM_in4
#define RIGHT_X           PWM_in1

#define SHOULDER_BUTTON   PWM_in6
#define RAMP_BUTTON       PWM_in5
#define ELBOW_BUTTON      PWM_in5
#define PICKUP_BUTTON     PWM_in6
#define UNFOLD_BUTTON     ((int)255-(int)PWM_in6)

#endif
