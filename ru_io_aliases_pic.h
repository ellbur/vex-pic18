
#ifndef _ru_io_aliases_pic_h
#define _ru_io_aliases_pic_h 1

// ---------------- The Nitish --------------

#if nitish

#define LEFT_SCISSOR     pwm01
#define RIGHT_SCISSOR    pwm02

#define LEFT_WHEEL_1     pwm03
#define LEFT_WHEEL_2     pwm04
#define RIGHT_WHEEL_1    pwm05
#define RIGHT_WHEEL_2    pwm06

#define LEFT_SHOULDER    pwm07
#define RIGHT_SHOULDER   pwm08

#define SHOULDER_POT     rc_ana_in08

#endif

// ---------------- The John ----------------

#if kevin

#define LEFT_WHEEL        pwm01
#define RIGHT_WHEEL       pwm02
#define RAMP_1            pwm03
#define RAMP_2            pwm04
#define LEFT_SHOULDER_1   pwm05
#define RIGHT_SHOULDER_1  pwm06
#define LEFT_SHOULDER_2   pwm07
#define RIGHT_SHOULDER_2  pwm08

#define SHOULDER_POT      rc_ana_in01
#define RAMP_POT          rc_ana_in02

#define FRONT_IR          rc_ana_in08
#define SIDE_FRONT_IR     rc_ana_in09
#define SIDE_REAR_IR      rc_ana_in10
#define REAR_IR           rc_ana_in11
#define FRONT_LOW_IR      rc_ana_in12

#endif

// OI

#define LEFT_JOY          PWM_in3
#define RIGHT_JOY         PWM_in2

#define SHOULDER_BUTTON   PWM_in6
#define RAMP_BUTTON       PWM_in5

#define TRIGGER_BUTTON    PWM_in6


#endif
